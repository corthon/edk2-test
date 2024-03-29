/** @file
  Header file for Md5.

Copyright (c) 2004 - 2008, Intel Corporation. All rights reserved.<BR>
SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#ifndef _MD5_H_
#define _MD5_H_
 
#define MD5_HASHSIZE  16

typedef struct _MD5_CTX {
  EFI_STATUS  Status;
  UINT64      Length;
  UINT32      States[MD5_HASHSIZE / sizeof (UINT32)];
  UINT8       M[64];
  UINTN       Count;
} MD5_CTX;

/**
  Initialize four 32-bits chaining variables and use them to do the Md5 transform.

  @param[out]  Md5Ctx The data structure of Md5.

  @retval EFI_SUCCESS Initialization is ok.
**/
EFI_STATUS
MD5Init (
  OUT MD5_CTX  *Md5Ctx
  );

/**
  the external interface of Md5 algorithm

  @param[in, out]  Md5Ctx  The data structure of storing the original data
                           segment and the final result.
  @param[in]       Data    The data wanted to be transformed.
  @param[in]       DataLen The length of data.

  @retval EFI_SUCCESS The transform is ok.
  @retval Others      Other errors as indicated.
**/
EFI_STATUS
MD5Update (
  IN  OUT MD5_CTX  *Md5Ctx,
  IN  VOID         *Data,
  IN  UINTN        DataLen
  );

/**
  Accumulate the MD5 value of every data segment and generate the finial
  result according to MD5 algorithm.

  @param[in, out]   Md5Ctx  The data structure of storing the original data
                            segment and the final result.
  @param[out]      HashVal  The final 128-bits output.

  @retval EFI_SUCCESS  The transform is ok.
  @retval Others       Other errors as indicated.
**/
EFI_STATUS
MD5Final (
  IN  OUT MD5_CTX  *Md5Ctx,
  OUT UINT8        *HashVal
  );

#endif 
