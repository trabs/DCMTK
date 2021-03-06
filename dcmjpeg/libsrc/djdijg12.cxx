/*
 *
 *  Copyright (C) 2001-2009, OFFIS
 *
 *  This software and supporting documentation were developed by
 *
 *    Kuratorium OFFIS e.V.
 *    Healthcare Information and Communication Systems
 *    Escherweg 2
 *    D-26121 Oldenburg, Germany
 *
 *  THIS SOFTWARE IS MADE AVAILABLE,  AS IS,  AND OFFIS MAKES NO  WARRANTY
 *  REGARDING  THE  SOFTWARE,  ITS  PERFORMANCE,  ITS  MERCHANTABILITY  OR
 *  FITNESS FOR ANY PARTICULAR USE, FREEDOM FROM ANY COMPUTER DISEASES  OR
 *  ITS CONFORMITY TO ANY SPECIFICATION. THE ENTIRE RISK AS TO QUALITY AND
 *  PERFORMANCE OF THE SOFTWARE IS WITH THE USER.
 *
 *  Module:  dcmjpeg
 *
 *  Author:  Norbert Olges, Marco Eichelberg
 *
 *  Purpose: decompression routines of the IJG JPEG library configured for 12 bits/sample.
 *
 *  Last Update:      $Author: uli $
 *  Update Date:      $Date: 2010-02-22 11:39:54 $
 *  Source File:      $Source: /share/dicom/cvs-depot/dcmtk/dcmjpeg/libsrc/djdijg12.cc,v $
 *  CVS/RCS Revision: $Revision: 1.17 $
 *  Status:           $State: Exp $
 *
 *  CVS/RCS Log at end of file
 *
 */

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmjpeg/djdijg12.h"
#include "dcmtk/dcmjpeg/djcparam.h"

#define INCLUDE_CSTDIO
#define INCLUDE_CSETJMP
#define INCLUDE_CSTRING
#include "dcmtk/ofstd/ofstdinc.h"

// These two macros are re-defined in the IJG header files.
// We undefine them here and hope that IJG's configure has
// come to the same conclusion that we have...
#ifdef HAVE_STDLIB_H
#undef HAVE_STDLIB_H
#endif
#ifdef HAVE_STDDEF_H
#undef HAVE_STDDEF_H
#endif

BEGIN_EXTERN_C
#define boolean ijg_boolean
#include "jpeglib12.h"
#include "jerror12.h"
#undef boolean

// disable any preprocessor magic the IJG library might be doing with the "const" keyword
#ifdef const
#undef const
#endif

#ifdef USE_STD_CXX_INCLUDES
// Solaris defines longjmp() in namespace std, other compilers don't...
namespace std { }
using namespace std;
#endif

// private error handler struct
struct DJDIJG12ErrorStruct
{
  // the standard IJG error handler object
  struct jpeg_error_mgr pub;

  // our jump buffer
  jmp_buf setjmp_buffer;

  // pointer to this
  DJDecompressIJG12Bit *instance;
};

// private source manager struct
struct DJDIJG12SourceManagerStruct
{
  // the standard IJG source manager object
  struct jpeg_source_mgr pub;

  // number of bytes to skip at start of buffer
  long skip_bytes;

  // buffer from which reading will continue as soon as the current buffer is empty
  Uint8 *next_buffer;

  // buffer size
  Uint32 next_buffer_size;
};

// callback forward declarations
void DJDIJG12ErrorExit(j_common_ptr);
void DJDIJG12EmitMessage(j_common_ptr cinfo, int msg_level);
void DJDIJG12initSource(j_decompress_ptr);
ijg_boolean DJDIJG12fillInputBuffer(j_decompress_ptr);
void DJDIJG12skipInputData(j_decompress_ptr, long);
void DJDIJG12termSource(j_decompress_ptr);

END_EXTERN_C


// error handler, executes longjmp
void DJDIJG12ErrorExit(j_common_ptr cinfo)
{
  DJDIJG12ErrorStruct *myerr = (DJDIJG12ErrorStruct *)cinfo->err;
  longjmp(myerr->setjmp_buffer, 1);
}

// message handler for warning messages and the like
void DJDIJG12EmitMessage(j_common_ptr cinfo, int msg_level)
{
  DJDIJG12ErrorStruct *myerr = (DJDIJG12ErrorStruct *)cinfo->err;
  myerr->instance->emitMessage(msg_level);
}


// methods for decompress-source-manager

void DJDIJG12initSource(j_decompress_ptr /* cinfo */)
{
}

ijg_boolean DJDIJG12fillInputBuffer(j_decompress_ptr cinfo)
{
  DJDIJG12SourceManagerStruct *src = (DJDIJG12SourceManagerStruct *)(cinfo->src);

  // if we already have the next buffer, switch buffers
  if (src->next_buffer)
  {
    src->pub.next_input_byte    = src->next_buffer;
    src->pub.bytes_in_buffer    = (unsigned int) src->next_buffer_size;
    src->next_buffer            = NULL;
    src->next_buffer_size       = 0;

    // The suspension was caused by DJDIJG12skipInputData iff src->skip_bytes > 0.
    // In this case we must skip the remaining number of bytes here.
    if (src->skip_bytes > 0)
    {
      if (src->pub.bytes_in_buffer < (unsigned long) src->skip_bytes)
      {
        src->skip_bytes            -= src->pub.bytes_in_buffer;
        src->pub.next_input_byte   += src->pub.bytes_in_buffer;
        src->pub.bytes_in_buffer    = 0;
        // cause a suspension return
        return FALSE;
      }
      else
      {
        src->pub.bytes_in_buffer   -= (unsigned int) src->skip_bytes;
        src->pub.next_input_byte   += src->skip_bytes;
        src->skip_bytes             = 0;
      }
    }
    return TRUE;
  }

  // otherwise cause a suspension return
  return FALSE;
}

void DJDIJG12skipInputData(
  j_decompress_ptr cinfo,
  long num_bytes)
{
  DJDIJG12SourceManagerStruct *src = (DJDIJG12SourceManagerStruct *)(cinfo->src);

  if (src->pub.bytes_in_buffer < (size_t)num_bytes)
  {
    src->skip_bytes             = num_bytes - src->pub.bytes_in_buffer;
    src->pub.next_input_byte   += src->pub.bytes_in_buffer;
    src->pub.bytes_in_buffer    = 0; // causes a suspension return
  }
  else
  {
    src->pub.bytes_in_buffer   -= (unsigned int) num_bytes;
    src->pub.next_input_byte   += num_bytes;
    src->skip_bytes             = 0;
  }
}

void DJDIJG12termSource(j_decompress_ptr /* cinfo */)
{
}


DJDecompressIJG12Bit::DJDecompressIJG12Bit(const DJCodecParameter& cp, OFBool isYBR)
: DJDecoder()
, cparam(&cp)
, cinfo(NULL)
, suspension(0)
, jsampBuffer(NULL)
, dicomPhotometricInterpretationIsYCbCr(isYBR)
, decompressedColorModel(EPI_Unknown)
{
}

DJDecompressIJG12Bit::~DJDecompressIJG12Bit()
{
  cleanup();
}


OFCondition DJDecompressIJG12Bit::init()
{
  suspension = 0;
  decompressedColorModel = EPI_Unknown;
  cleanup(); // prevent double initialization

  cinfo = new jpeg_decompress_struct();
  if (cinfo)
  {
    volatile DJDIJG12SourceManagerStruct *src = NULL;
    volatile DJDIJG12ErrorStruct *jerr = new DJDIJG12ErrorStruct();
    if (jerr)
    {
      src = new DJDIJG12SourceManagerStruct();
      if (src)
      {
        // Specify the source of the compressed data
        src->pub.init_source       = DJDIJG12initSource;
        src->pub.fill_input_buffer = DJDIJG12fillInputBuffer;
        src->pub.skip_input_data   = DJDIJG12skipInputData;
        src->pub.resync_to_restart = jpeg_resync_to_restart;
        src->pub.term_source       = DJDIJG12termSource;
        src->pub.bytes_in_buffer   = 0;
        src->pub.next_input_byte   = NULL;
        src->skip_bytes             = 0;
        src->next_buffer            = NULL;
        src->next_buffer_size       = 0;
      }
      else
      {
        delete OFconst_cast(DJDIJG12ErrorStruct *, jerr);
        delete cinfo;
        cinfo = NULL;
        return EC_MemoryExhausted;
      }
      cinfo->err = jpeg_std_error(& OFconst_cast(DJDIJG12ErrorStruct *, jerr)->pub);
      jerr->instance = this;
      jerr->pub.error_exit = DJDIJG12ErrorExit;
      jerr->pub.emit_message = DJDIJG12EmitMessage;
      if (setjmp(OFconst_cast(DJDIJG12ErrorStruct *, jerr)->setjmp_buffer))
      {
        // the IJG error handler will cause the following code to be executed
        char buffer[JMSG_LENGTH_MAX];
        (*cinfo->err->format_message)((jpeg_common_struct *)cinfo, buffer); /* Create the message */
        cleanup();
        return makeOFCondition(OFM_dcmjpeg, EJCode_IJG12_Decompression, OF_error, buffer);
      }
    }
    else
    {
      delete cinfo;
      cinfo = NULL;
      return EC_MemoryExhausted;
    }
    jpeg_create_decompress(cinfo);
    cinfo->src = &OFconst_cast(DJDIJG12SourceManagerStruct *, src)->pub;
  } else return EC_MemoryExhausted;

  // everything OK
  return EC_Normal;
}


void DJDecompressIJG12Bit::cleanup()
{
  if (cinfo)
  {
    jpeg_destroy_decompress(cinfo);
    delete (DJDIJG12ErrorStruct *)(cinfo->err);
    delete (DJDIJG12SourceManagerStruct *)(cinfo->src);
    delete cinfo;
    cinfo = NULL;
  }
}


OFCondition DJDecompressIJG12Bit::decode(
  Uint8 *compressedFrameBuffer,
  Uint32 compressedFrameBufferSize,
  Uint8 *uncompressedFrameBuffer,
  Uint32 uncompressedFrameBufferSize,
  OFBool isSigned)
{

  if (cinfo==NULL || compressedFrameBuffer==NULL || uncompressedFrameBuffer==NULL) return EC_IllegalCall;

  if (setjmp(((DJDIJG12ErrorStruct *)(cinfo->err))->setjmp_buffer))
  {
     // the IJG error handler will cause the following code to be executed
     char buffer[JMSG_LENGTH_MAX];
     (*cinfo->err->format_message)((jpeg_common_struct *)cinfo, buffer); /* Create the message */
     cleanup();
     return makeOFCondition(OFM_dcmjpeg, EJCode_IJG12_Decompression, OF_error, buffer);
  }

  // feed compressed buffer into cinfo structure.
  // The buffer will be activated by the next call to DJDIJG12fillInputBuffer.
  DJDIJG12SourceManagerStruct *src = (DJDIJG12SourceManagerStruct *)(cinfo->src);
  src->next_buffer            = compressedFrameBuffer;
  src->next_buffer_size       = compressedFrameBufferSize;

  // Obtain image info
  if (suspension < 2)
  {
    if (JPEG_SUSPENDED == jpeg_read_header(cinfo, TRUE))
    {
      suspension = 1;
      return EJ_Suspension;
    }

    // check if color space conversion is enabled
    OFBool colorSpaceConversion = OFFalse;
    switch(cparam->getDecompressionColorSpaceConversion())
    {
        case EDC_photometricInterpretation: // color space conversion if DICOM photometric interpretation is YCbCr
          colorSpaceConversion = dicomPhotometricInterpretationIsYCbCr;
          break;
        case EDC_lossyOnly: // color space conversion if lossy JPEG
          if (cinfo->process != JPROC_LOSSLESS) colorSpaceConversion = OFTrue;
          break;
        case EDC_always: // always do color space conversion
          colorSpaceConversion = OFTrue;
          break;
        case EDC_never: // never do color space conversion
          break;
    }
    // Decline color space conversion to RGB for signed pixel data, because IJG can handle only unsigned
    if ( colorSpaceConversion && isSigned )
      return EJ_UnsupportedColorConversion;

    // Set color space for decompression
    if (colorSpaceConversion)
    {
      switch (cinfo->out_color_space)
      {
        case JCS_GRAYSCALE:
          decompressedColorModel = EPI_Monochrome2;
          break;
        case JCS_YCbCr: // enforce conversion YCbCr to RGB
          cinfo->jpeg_color_space = JCS_YCbCr;
          cinfo->out_color_space = JCS_RGB;
          decompressedColorModel = EPI_RGB;
          break;
        case JCS_RGB: // enforce conversion YCbCr to RGB
          cinfo->jpeg_color_space = JCS_YCbCr;
          decompressedColorModel = EPI_RGB;
          break;
        default:
          decompressedColorModel = EPI_Unknown;
          break;
      }
    }
    else
    {
#ifdef DETERMINE_OUTPUT_COLOR_SPACE_FROM_IJG_GUESS
      // let the IJG library guess the JPEG color space
      // and use it as the value for decompressedColorModel.
      switch (cinfo->jpeg_color_space)
      {
        case JCS_GRAYSCALE:
          decompressedColorModel = EPI_Monochrome2;
          break;
        case JCS_YCbCr:
          decompressedColorModel = EPI_YBR_Full;
          break;
        case JCS_RGB:
          decompressedColorModel = EPI_RGB;
          break;
        default:
          decompressedColorModel = EPI_Unknown;
          break;
      }
#else
      decompressedColorModel = EPI_Unknown;
#endif

      // prevent the library from performing any color space conversion
      cinfo->jpeg_color_space = JCS_UNKNOWN;
      cinfo->out_color_space = JCS_UNKNOWN;
    }
  }

  JSAMPARRAY buffer = NULL;
  int bufsize = 0;
  size_t rowsize = 0;

  if (suspension < 3)
  {
    if (FALSE == jpeg_start_decompress(cinfo))
    {
      suspension = 2;
      return EJ_Suspension;
    }
    bufsize = cinfo->output_width * cinfo->output_components; // number of JSAMPLEs per row
    rowsize = bufsize * sizeof(JSAMPLE); // number of bytes per row
    buffer = (*cinfo->mem->alloc_sarray)((j_common_ptr)cinfo, JPOOL_IMAGE, bufsize, 1);
    if (buffer == NULL) return EC_MemoryExhausted;
    jsampBuffer = buffer;
  }
  else
  {
    bufsize = cinfo->output_width * cinfo->output_components;
    rowsize = bufsize * sizeof(JSAMPLE);
    buffer = (JSAMPARRAY)jsampBuffer;
  }

  if (uncompressedFrameBufferSize < rowsize * cinfo->output_height) return EJ_IJG12_FrameBufferTooSmall;

  while (cinfo->output_scanline < cinfo->output_height)
  {
    if (0 == jpeg_read_scanlines(cinfo, buffer, 1))
    {
      suspension = 3;
      return EJ_Suspension;
    }
    memcpy(uncompressedFrameBuffer + (cinfo->output_scanline-1) * rowsize, *buffer, rowsize);
  }

  if (FALSE == jpeg_finish_decompress(cinfo))
  {
    suspension = 4;
    return EJ_Suspension;
  }

  return EC_Normal;
}

void DJDecompressIJG12Bit::emitMessage(int msg_level) const
{
  // This is how we map the message levels:
  // -1 - 0: Warning (could also be errors, but no way to find out)
  //  1    : Debug
  // Everything else: Trace (No point in splitting this further up)
  OFLogger::LogLevel level;

  switch (msg_level)
  {
  case -1:
  case 0:
    level = OFLogger::WARN_LOG_LEVEL;
    break;
  case 1:
    level = OFLogger::DEBUG_LOG_LEVEL;
    break;
  default:
    level = OFLogger::TRACE_LOG_LEVEL;
    break;
  }

  if (cinfo && DCM_dcmjpegGetLogger().isEnabledFor(level))
  {
    char buffer[JMSG_LENGTH_MAX];
    (*cinfo->err->format_message)((jpeg_common_struct *)cinfo, buffer); /* Create the message */
    DCM_dcmjpegGetLogger().forcedLog(level, buffer, __FILE__, __LINE__);
  }
}


/*
 * CVS/RCS Log
 * $Log: djdijg12.cc,v $
 * Revision 1.17  2010-02-22 11:39:54  uli
 * Remove some unneeded includes.
 *
 * Revision 1.16  2009-11-18 16:17:54  uli
 * Use more than just the INFO log level.
 *
 * Revision 1.15  2009-10-07 12:44:33  uli
 * Switched to logging mechanism provided by the "new" oflog module.
 *
 * Revision 1.14  2009-08-19 12:19:19  meichel
 * Unlike some other compilers, Sun Studio 11 on Solaris
 *   declares longjmp() in namespace std. Added code to handle this case.
 *
 * Revision 1.13  2006-08-16 16:30:21  meichel
 * Updated all code in module dcmjpeg to correctly compile when
 *   all standard C++ classes remain in namespace std.
 *
 * Revision 1.12  2005/12/08 15:43:36  meichel
 * Changed include path schema for all DCMTK header files
 *
 * Revision 1.11  2005/11/30 14:08:50  onken
 * Added check to decline automatic IJG color space conversion of signed pixel
 * data, because IJG lib only handles unsigned input for conversions.
 *
 * Revision 1.10  2005/11/14 17:09:39  meichel
 * Changed some function return types from int to ijg_boolean, to avoid
 *   compilation errors if the ijg_boolean type is ever changed.
 *
 * Revision 1.9  2004/05/07 10:45:13  meichel
 * Added explicit typecast to volatile variables, needed for MSVC
 *
 * Revision 1.8  2004/05/05 14:10:24  joergr
 * Added explicit typecast to volatile variables to compiler with gcc 3.2.
 *
 * Revision 1.7  2004/05/05 11:50:06  meichel
 * Declared a few local variables as volatile that might otherwise
 *   be clobbered by longjmp.
 *
 * Revision 1.6  2003/10/13 13:25:49  meichel
 * Added workaround for name clash of typedef "boolean" in the IJG header files
 *   and the standard headers for Borland C++.
 *
 * Revision 1.5  2002/11/27 15:39:59  meichel
 * Adapted module dcmjpeg to use of new header file ofstdinc.h
 *
 * Revision 1.4  2001/12/20 10:41:51  meichel
 * Fixed warnings reported by Sun CC 2.0.1
 *
 * Revision 1.3  2001/12/18 09:48:56  meichel
 * Modified configure test for "const" support of the C compiler
 *   in order to avoid a macro recursion error on Sun CC 2.0.1
 *
 * Revision 1.2  2001/11/19 15:13:30  meichel
 * Introduced verbose mode in module dcmjpeg. If enabled, warning
 *   messages from the IJG library are printed on ofConsole, otherwise
 *   the library remains quiet.
 *
 * Revision 1.1  2001/11/13 15:58:28  meichel
 * Initial release of module dcmjpeg
 *
 *
 */
