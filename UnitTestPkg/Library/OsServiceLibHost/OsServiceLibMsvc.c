/**@file

Copyright (c) 2019, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <stdio.h>
#include <WinNtInclude.h>

VOID *
AllocateExecutableMemory (
  IN UINTN  Size
  )
{
  VOID        *Buffer;
  SIZE_T      FinalSize;
  UINT32      PageSize;
  SYSTEM_INFO SystemInfo;

  GetSystemInfo(&SystemInfo);
  PageSize = SystemInfo.dwPageSize;

  FinalSize = (Size + PageSize - 1) / PageSize * PageSize;

  Buffer = VirtualAlloc(NULL, FinalSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
  if (Buffer == NULL) {
    return NULL;
  }

  return Buffer;
}

VOID
FreeExecutableMemory (
  IN VOID   *Buffer,
  IN UINTN  Size
  )
{
  VirtualFree(Buffer, 0, MEM_RELEASE);
}
