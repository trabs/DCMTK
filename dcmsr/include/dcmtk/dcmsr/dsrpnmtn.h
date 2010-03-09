/*
 *
 *  Copyright (C) 2000-2007, OFFIS
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
 *  Module: dcmsr
 *
 *  Author: Joerg Riesmeier
 *
 *  Purpose:
 *    classes: DSRPNameTreeNode
 *
 *  Last Update:      $Author: uli $
 *  Update Date:      $Date: 2009-10-13 14:57:50 $
 *  CVS/RCS Revision: $Revision: 1.15 $
 *  Status:           $State: Exp $
 *
 *  CVS/RCS Log at end of file
 *
 */


#ifndef DSRPNMTN_H
#define DSRPNMTN_H

#include "dcmtk/config/osconfig.h"   /* make sure OS specific configuration is included first */

#include "dcmtk/dcmsr/dsrdoctn.h"
#include "dcmtk/dcmsr/dsrstrvl.h"


/*---------------------*
 *  class declaration  *
 *---------------------*/

/** Class for content item PNAME
 */
class DSRPNameTreeNode
  : public DSRDocumentTreeNode,
    public DSRStringValue
{

  public:

    /** constructor
     ** @param  relationshipType  type of relationship to the parent tree node.
     *                            Should not be RT_invalid or RT_isRoot.
     */
    DSRPNameTreeNode(const E_RelationshipType relationshipType);

    /** constructor
     ** @param  relationshipType  type of relationship to the parent tree node.
     *                            Should not be RT_invalid or RT_isRoot.
     *  @param  stringValue       initial string value to be set
     */
    DSRPNameTreeNode(const E_RelationshipType relationshipType,
                     const OFString &stringValue);

    /** destructor
     */
    virtual ~DSRPNameTreeNode();

    /** clear all member variables.
     *  Please note that the content item might become invalid afterwards.
     */
    virtual void clear();

    /** check whether the content item is valid.
     *  The content item is valid if the two base classes and the concept name are valid.
     ** @return OFTrue if tree node is valid, OFFalse otherwise
     */
    virtual OFBool isValid() const;

    /** print content item.
     *  A typical output looks like this: contains PNAME:(,,"Code")="Riesmeier^Joerg"
     ** @param  stream  output stream to which the content item should be printed
     *  @param  flags   flag used to customize the output (see DSRTypes::PF_xxx)
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition print(STD_NAMESPACE ostream &stream,
                              const size_t flags) const;

    /** write content item in XML format
     ** @param  stream     output stream to which the XML document is written
     *  @param  flags      flag used to customize the output (see DSRTypes::XF_xxx)
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition writeXML(STD_NAMESPACE ostream &stream,
                                 const size_t flags) const;

    // --- static helper function ---

    /** get DICOM Person Name from XML elements.
     *  The five components of a DICOM Person Name (PN) are expected to be stored in the
     *  XML elements "prefix", "first", "middle", "last" and "suffix" as created by
     *  writeXML().
     ** @param  doc        document containing the XML file content
     *  @param  cursor     cursor pointing to the starting node
     *  @param  nameValue  reference to string object in which the value should be stored
     ** @return reference to string object (might be empty)
     */
    static OFString &getValueFromXMLNodeContent(const DSRXMLDocument &doc,
                                                DSRXMLCursor cursor,
                                                OFString &nameValue);


  protected:

    /** read content item (value) from dataset
     ** @param  dataset    DICOM dataset from which the content item should be read
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition readContentItem(DcmItem &dataset);

    /** write content item (value) to dataset
     ** @param  dataset    DICOM dataset to which the content item should be written
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition writeContentItem(DcmItem &dataset) const;

    /** read content item specific XML data
     ** @param  doc     document containing the XML file content
     *  @param  cursor  cursor pointing to the starting node
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition readXMLContentItem(const DSRXMLDocument &doc,
                                           DSRXMLCursor cursor);

    /** render content item (value) in HTML/XHTML format
     ** @param  docStream     output stream to which the main HTML/XHTML document is written
     *  @param  annexStream   output stream to which the HTML/XHTML document annex is written
     *  @param  nestingLevel  current nesting level.  Used to render section headings.
     *  @param  annexNumber   reference to the variable where the current annex number is stored.
     *                        Value is increased automatically by 1 after a new entry has been added.
     *  @param  flags         flag used to customize the output (see DSRTypes::HF_xxx)
     ** @return status, EC_Normal if successful, an error code otherwise
     */
    virtual OFCondition renderHTMLContentItem(STD_NAMESPACE ostream &docStream,
                                              STD_NAMESPACE ostream &annexStream,
                                              const size_t nestingLevel,
                                              size_t &annexNumber,
                                              const size_t flags) const;


  private:

 // --- declaration of default/copy constructor and assignment operator

    DSRPNameTreeNode();
    DSRPNameTreeNode(const DSRPNameTreeNode &);
    DSRPNameTreeNode &operator=(const DSRPNameTreeNode &);
};


#endif


/*
 *  CVS/RCS Log:
 *  $Log: dsrpnmtn.h,v $
 *  Revision 1.15  2009-10-13 14:57:50  uli
 *  Switched to logging mechanism provided by the "new" oflog module.
 *
 *  Revision 1.14  2007-11-15 16:33:30  joergr
 *  Added support for output in XHTML 1.1 format.
 *
 *  Revision 1.13  2006/08/15 16:40:03  meichel
 *  Updated the code in module dcmsr to correctly compile when
 *    all standard C++ classes remain in namespace std.
 *
 *  Revision 1.12  2006/05/11 09:18:21  joergr
 *  Moved containsExtendedCharacters() from dcmsr to dcmdata module.
 *
 *  Revision 1.11  2005/12/08 16:05:12  meichel
 *  Changed include path schema for all DCMTK header files
 *
 *  Revision 1.10  2004/11/22 16:39:09  meichel
 *  Added method that checks if the SR document contains non-ASCII characters
 *    in any of the strings affected by SpecificCharacterSet.
 *
 *  Revision 1.9  2003/09/15 14:18:54  joergr
 *  Introduced new class to facilitate checking of SR IOD relationship content
 *  constraints. Replaced old implementation distributed over numerous classes.
 *
 *  Revision 1.8  2003/08/07 12:44:26  joergr
 *  Added readXML functionality. Added support for Chest CAD SR.
 *
 *  Revision 1.7  2001/11/09 16:10:51  joergr
 *  Added preliminary support for Mammography CAD SR.
 *
 *  Revision 1.6  2001/09/26 13:04:10  meichel
 *  Adapted dcmsr to class OFCondition
 *
 *  Revision 1.5  2001/06/01 15:51:02  meichel
 *  Updated copyright header
 *
 *  Revision 1.4  2000/11/07 18:14:30  joergr
 *  Enhanced support for by-reference relationships.
 *
 *  Revision 1.3  2000/11/01 16:23:23  joergr
 *  Added support for conversion to XML.
 *
 *  Revision 1.2  2000/10/23 15:12:12  joergr
 *  Added clear() method.
 *  Added/updated doc++ comments.
 *
 *  Revision 1.1  2000/10/13 07:49:30  joergr
 *  Added new module 'dcmsr' providing access to DICOM structured reporting
 *  documents (supplement 23).  Doc++ documentation not yet completed.
 *
 *
 */
