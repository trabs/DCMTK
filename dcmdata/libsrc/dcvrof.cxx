/*
 *
 *  Copyright (C) 2002, OFFIS
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
 *  Module:  dcmdata
 *
 *  Author:  Joerg Riesmeier
 *
 *  Purpose: Implementation of class DcmOtherFloat
 *
 *  Last Update:      $Author: uli $
 *  Update Date:      $Date: 2009-11-04 09:58:11 $
 *  Source File:      $Source: /share/dicom/cvs-depot/dcmtk/dcmdata/libsrc/dcvrof.cc,v $
 *  CVS/RCS Revision: $Revision: 1.4 $
 *  Status:           $State: Exp $
 *
 *  CVS/RCS Log at end of file
 *
 */


#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */

#include "dcmtk/dcmdata/dcvrof.h"
#include "dcmtk/dcmdata/dcvrfl.h"


// ********************************


DcmOtherFloat::DcmOtherFloat(const DcmTag &tag,
                             const Uint32 len)
  : DcmFloatingPointSingle(tag, len)
{
}


DcmOtherFloat::DcmOtherFloat(const DcmOtherFloat &old)
  : DcmFloatingPointSingle(old)
{
}


DcmOtherFloat::~DcmOtherFloat()
{
}


DcmOtherFloat &DcmOtherFloat::operator=(const DcmOtherFloat &obj)
{
    DcmFloatingPointSingle::operator=(obj);
    return *this;
}


OFCondition DcmOtherFloat::copyFrom(const DcmObject& rhs)
{
  if (this != &rhs)
  {
    if (rhs.ident() != ident()) return EC_IllegalCall;
    *this = (DcmOtherFloat&) rhs;
  }
  return EC_Normal;
}

// ********************************


DcmEVR DcmOtherFloat::ident() const
{
    return EVR_OF;
}


unsigned long DcmOtherFloat::getVM()
{
    /* value multiplicity for OF is defined as 1 */
    return 1;
}


/*
 * CVS/RCS Log:
 * $Log: dcvrof.cc,v $
 * Revision 1.4  2009-11-04 09:58:11  uli
 * Switched to logging mechanism provided by the "new" oflog module
 *
 * Revision 1.3  2008-07-17 10:31:32  onken
 * Implemented copyFrom() method for complete DcmObject class hierarchy, which
 * permits setting an instance's value from an existing object. Implemented
 * assignment operator where necessary.
 *
 * Revision 1.2  2005-12-08 15:41:58  meichel
 * Changed include path schema for all DCMTK header files
 *
 * Revision 1.1  2002/12/06 12:07:02  joergr
 * Added support for new value representation Other Float String (OF).
 *
 *
 */
