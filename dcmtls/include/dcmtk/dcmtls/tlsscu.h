/*
 *
 *  Copyright (C) 2010, OFFIS
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
 *  Module:  dcmtls
 *
 *  Author:  Michael Onken
 *
 *  Purpose: Base class for TLS-enabled Service Class Users (SCUs)
 *
 *  Last Update:      $Author: onken $
 *  Update Date:      $Date: 2010-04-29 16:18:00 $
 *  Source File:      $Source: /share/dicom/cvs-depot/dcmtk/dcmtls/include/dcmtk/dcmtls/tlsscu.h,v $
 *  CVS/RCS Revision: $Revision: 1.1 $
 *  Status:           $State: Exp $
 *
 *  CVS/RCS Log at end of file
 *
 */

#ifndef TLSSCU_H
#define TLSSCU_H

#include "dcmtk/config/osconfig.h" /* make sure OS specific configuration is included first */

#ifdef WITH_OPENSSL
#include "dcmtk/dcmnet/scu.h"
#include "dcmtk/dcmtls/tlstrans.h"
#include "dcmtk/dcmtls/tlslayer.h"

/** Base class for implementing DICOM TLS-enabled Service Class User
 *  functionality. This class is derived from the general DcmSCU class and
 *  just adds the corresponding TLS capabilities.
 *  @warning This class is EXPERIMENTAL. Be careful to use it in production
 *           environment.
 */
class DcmTLSSCU : public DcmSCU
{

public:

  /** Constructor, just initializes internal class members
   */
  DcmTLSSCU();

  /** Initialize SCU with connection peer information
   *  @param peerHost [in] The hostname or IP of the host to talk to
   *  @param peerAETtitle [in] AETitle of peer host to be used
   *  @param portNum [in] TCP/IP port number to talk to
   */
  DcmTLSSCU(const OFString& peerHost,
            const OFString& peerAETitle,
            const Uint16& portNum);

  /** Virtual desctructor 
    */
  virtual ~DcmTLSSCU();
  
  /** Initialize network, i.e. prepare for association negotiation.
   *  @return EC_Normal if initialization was successful, otherwise error code
   */
  virtual OFCondition initNetwork();

  /** Negotiate association by using presentation contexts and parameters
   *  as defined by earlier function calls.
   *  @return EC_Normal if negotiation was successful, otherwise error code
   */
  virtual OFCondition negotiateAssociation();

  /** Closes the association of this SCU. As parameter it needs information
   *  whether the remote peer wants to release/abort the association. Allowed values:
   *  EC_Normal: Let SCU release its association
   *  DUL_PEERABORTEDASSOCIATION: Also releases association on peer's request
   *  DUL_PEERREQUESTEDRELEASE: Aborts associaton on peer's request
   *  Other cases: SCU aborts association.
   *  @param abortOrReleaseRequested [in] Define whether to release or abort
   *                                      the association.
   */
  virtual void closeAssociation(const OFCondition& abortOrReleaseRequested);  

  /** Not documented yet  
   *  @param str [in] Not documented yet
   */
  virtual void addTrustedCertFile(const OFString& str);
  
  /** Not documented yet
   *  @param certDir [in] Not documented yet
   */
  virtual void addTrustedCertDir(const OFString& certDir);

  /** Not documented yet
   *  @param privateKey [in] File with private key to authenticate with
   *  @param certFile [in] File with certificate to authenticate with
   *  @param passphrase [in] Password to access key. NULL asks user 
   *                    on console. "" will send empty password. Default
   *                    is asking the user to enter password.
   *  @param privKeyFormat [in] Format of private key parameter. Default is
   *                       SSL_FILETYPE_PEM.
   *  @param certFormat [in] Format of certificate file parameter. Default is
   *                    SSL_FILETYPE_PEM.
   */  
  virtual void enableAuthentication(const OFString& privateKey,
                                    const OFString& certFile,
                                    const char* passphrase = NULL,
                                    const int& privKeyFormat = SSL_FILETYPE_PEM,
                                    const int& certFormat    = SSL_FILETYPE_PEM);

  /** Disables authentication. However, DcmTLSSCU will try to 
   *  establish secured connection in terms of encrypting data
   *  Default is that authentication is disabled.
   */
  virtual void disableAuthentication();

  /** Not documented yet
   *  @param cs [in] Not documented yet
   */  
  virtual void addCiphersuite(const OFString& cs);

  /** Not documented yet
   *  @param seedFile [in] Not documented yet
   */
  virtual void setReadSeedFile(const OFString& seedFile);

  /** Not documented yet
   *  @param seedFile [in] Not documented yet
   */
  virtual void setWriteSeedFile(const OFString& seedFile);

  /** Set whether peer's certificate must be there, only is checked
   *  if there or is ignored.
   *  @param cert [in] The following values are permitted:
   *              DCV_requireCertificate, DCV_checkCertificate,
   *              DCV_ignoreCertificate
   */
  virtual void setPeerCertVerification(const DcmCertificateVerification& cert);

  /** Not documented yet
   *  @param dhParam [in] Not documented yet
   */
  virtual void setDHParam(const OFString& dhParam);

  /** Returns OFTrue if authentication is enabled.
   *  Not documented yet.
   *  @return Return value OFTrue
   */
  virtual OFBool getAuthenticationParams(OFString& privKeyFile,
                                         OFString& certFile,
                                         const char*& passphrase,
                                         int& privKeyFormat,
                                         int& certFormat) const;

  /** Not documented yet
   *  @param files [out] Not documented yet
   */
  virtual void getTrustedCertFiles(OFList<OFString>& files /*out*/) const;

  /** Not documented yet
   *  @param trustedDirs [out] Not documented yet
   */
  virtual void getTrustedCertDirs(OFList<OFString>& trustedDirs /*out*/) const;

  /** Not documented yet
   *  @return Not documented yet
   */
  virtual OFString getCiphersuites() const;

  /** Not documented yet
   *  @return Not documented yet
   */
  virtual OFString getReadSeedFile() const;

  /** Not documented yet
   *  @return Not documented yet
   */
  virtual OFString getWriteSeedFile() const;

  /** Not documented yet
   *  @return Not documented yet
   */
  virtual OFString getDHParam() const;

private:

  /** Private undefined copy-constructor. Shall never be called.
   *  @param src Source object.
   */
  DcmTLSSCU( const DcmTLSSCU &src );

  /** Private undefined operator=. Shall never be called.
   *  @param src Source object.
   *  @return Reference to this.
   */
  DcmTLSSCU &operator=( const DcmTLSSCU &src );

  /// The TLS layer responsible for all encryption/authentication stuff
  DcmTLSTransportLayer *m_tLayer;

  /// If enabled, authentication of client/server is enabled 
  OFBool m_doAuthenticate;

  /// A list of directories containing trusted certificates (if authentication is enabled)
  OFList<OFString> m_trustedCertDirs;

  /// A list of files containing trusted certificates (if authentication is enabled)
  OFList<OFString> m_trustedCertFiles;

  /// The file containing the private key (if authentication is enabled)
  OFString m_privateKeyFile ;

  /// Might be either "SSL_FILETYPE_PEM" (default) or "SSL_FILETYPE_ASN1"
  int m_privateKeyFileFormat;

  /// File containing the certificate the SCU should use for authentication
  OFString m_certificateFile;

  /// Might be either "SSL_FILETYPE_PEM" (default) or "SSL_FILETYPE_ASN1"
  int m_certKeyFileFormat;

  /// Password used for unlocking the private key file. If NULL, password is
  /// asked from STDIN. If empty string (""), password is sent empty. All others
  /// values are sent as given.
  char* m_passwd;

  /// String containing all ciphersuites being (additionally? TODO) configured
  OFString m_ciphersuites;;

  /// TODO
  OFString m_readSeedFile;

  /// TODO
  OFString m_writeSeedFile;

  /// Denotes how certificates are handled, i.e. whether they are
  /// required, validated or only validated if present.
  DcmCertificateVerification m_certVerification;

  /// File containing Diffie Hellman parameters to be used
  OFString m_dhparam;

};

#endif // WITH_OPENSSL
#endif // TLSSCU_H
/*
** CVS Log
** $Log: tlsscu.h,v $
** Revision 1.1  2010-04-29 16:18:00  onken
** Added new class DcmTLSSCU as base class for developing TLS-enabled SCUs.
**
*/
