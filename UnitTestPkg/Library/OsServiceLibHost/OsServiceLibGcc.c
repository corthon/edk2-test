/**@file

Copyright (c) 2019, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <sys/mman.h>

VOID *
AllocateExecutableMemory (
  IN UINTN  Size
  )
{
  VOID        *Buffer;
  size_t      FinalSize;
  size_t      PageSize;

  PageSize = getpagesize();

  FinalSize = (Size + PageSize - 1) / PageSize * PageSize;

  Buffer = mmap(NULL, FinalSize, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
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
  size_t     FinalSize;
  size_t     PageSize;

  PageSize = getpagesize();

  FinalSize = (Size + PageSize - 1) / PageSize * PageSize;

  munmap (Buffer, FinalSize);
}
