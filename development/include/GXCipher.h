//
// --------------------------------------------------------------------------
//  Gurux Ltd
//
//
//
// Filename:        $HeadURL$
//
// Version:         $Revision$,
//                  $Date$
//                  $Author$
//
// Copyright (c) Gurux Ltd
//
//---------------------------------------------------------------------------
//
//  DESCRIPTION
//
// This file is a part of Gurux Device Framework.
//
// Gurux Device Framework is Open Source software; you can redistribute it
// and/or modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; version 2 of the License.
// Gurux Device Framework is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// More information of Gurux products: http://www.gurux.org
//
// This code is licensed under the GNU General Public License v2.
// Full text may be retrieved at http://www.gnu.org/licenses/gpl-2.0.txt
//---------------------------------------------------------------------------

#ifndef GXCIPHER_H
#define GXCIPHER_H

#include <stdbool.h>

#include "GXBytebuffer.h"

//This is reserved for internal use to save block info.
typedef struct
{   unsigned long c0;
    unsigned long c1;
    unsigned long c2;
    unsigned long c3;
    // How many bytes are not crypted/encrypted.
    int bytesRemaining;
    long totalLength;
    CGXByteBuffer tag;

} CGXGMacBlock;

extern void CGXGMacBlock_(CGXGMacBlock *p);

extern void CGXGMacBlock_d(CGXGMacBlock *p);

typedef struct
{
    DLMS_SECURITY m_Security;
    /**
    * System title.
    */
    CGXByteBuffer m_SystemTitle;

    /**
    * Is data encrypted.
    */
    bool m_Encrypt;

    /**
    *  Block cipher key.
    */
    CGXByteBuffer m_BlockCipherKey;
    /**
    *  Block Authentication key.
    */
    CGXByteBuffer m_AuthenticationKey;

    /**
     * Frame counter. AKA Invocation counter.
     */
    unsigned long m_FrameCounter;

    /**
    * Working key is counted only once from block cipher key.
    */
    unsigned long *m_WorkingKey;
    CGXByteBuffer m_H;
    CGXByteBuffer m_J0;
    CGXByteBuffer m_S;
    CGXByteBuffer m_Counter;
    unsigned long *m_mArray;

} CGXCipher;

/**
* Constructor.
*/
extern void CGXCipher_1(CGXCipher *p, CGXByteBuffer* systemTitle);

/**
* Constructor.
*/
extern void CGXCipher_2(CGXCipher *p, const char* systemTitle);

/**
* Constructor.
*/
extern void CGXCipher_3(CGXCipher *p,
                        unsigned char* systemTitle,
                        unsigned char count);

/**
* Destructor.
*/
extern void CGXCipher_d(CGXCipher *p);

/**
     * Encrypt PDU.
    *
    * @param tag
    *            Tag.
    * @param systemTitle
    *            System Title.
    * @param data
    *            Data to encrypt.
    * @param reply
    *            Encrypted data.
    */
extern int CGXCipher_Encrypt(CGXCipher *p,
                             DLMS_SECURITY security,
                             DLMS_COUNT_TYPE type,
                             unsigned long frameCounter,
                             unsigned char tag,
                             CGXByteBuffer* systemTitle,
                             CGXByteBuffer* plainText,
                             CGXByteBuffer* encrypted);

/**
     * Decrypt data.
    *
    * @param systemTitle
    *            System Title.
    * @param data
    *            Decrypted data.
    * @param security
    *            Used security level.
    */
extern int CGXCipher_Decrypt(CGXCipher *p,
                             CGXByteBuffer* title,
                             CGXByteBuffer* data,
                             DLMS_SECURITY* security);

/**
 * Encrypt data using AES.
 *
 * @param data
 *            Encrypted data.
 * @param offset
 *            Data offset.
 * @param secret
 *            Secret.
 */
extern int CGXCipher_Aes1Encrypt(CGXByteBuffer* data,
                                 unsigned short offset,
                                 CGXByteBuffer* secret);

/**
 * @return Is ciphering used.
 */
extern bool CGXCipher_IsCiphered(CGXCipher *p);

/**
 * @return Used security.
 */
extern DLMS_SECURITY CGXCipher_GetSecurity(CGXCipher *p);

/**
* @param value
*            Used security.
*/
extern void CGXCipher_SetSecurity(CGXCipher *p, DLMS_SECURITY value);

/**
 * @return System title.
 */
extern CGXByteBuffer* CGXCipher_GetSystemTitle(CGXCipher *p);

/**
*  @param value System title.
*/
extern void CGXCipher_SetSystemTitle(CGXCipher *p, CGXByteBuffer* value);

/**
 * @return Block cipher key.
 */
extern CGXByteBuffer* CGXCipher_GetBlockCipherKey(CGXCipher *p);

/**
*  @param value Block cipher key.
*/
extern void CGXCipher_SetBlockCipherKey(CGXCipher *p, CGXByteBuffer* value);

/**
 * @return Authentication key.
 */
extern CGXByteBuffer* CGXCipher_GetAuthenticationKey(CGXCipher *p);

/**
 * @param value
 *            Authentication key.
 */
extern void CGXCipher_SetAuthenticationKey(CGXCipher *p, CGXByteBuffer* value);

/**
 * @return Frame counter. Invocation counter.
 */
extern unsigned long CGXCipher_GetFrameCounter(CGXCipher *p);

extern void CGXCipher_SetFrameCounter(CGXCipher *p, unsigned long value);

extern void CGXCipher_Reset_2(CGXCipher *p);

#endif //GXCIPHER_H
