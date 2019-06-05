/** @file
  Provides a library function that can be customized to set the platform to boot from USB on the next boot.  
  This allows the test framework to reboot back to USB.  Since boot managers are not all the same creating a lib to 
  support platform customization will make porting to new code base/platform easier.  

  Copyright (c) 2016, Microsoft Corporation. All rights reserved.<BR>
  Copyright (c) 2019, Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php.

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef __UNIT_TEST_BOOT_LIB_H__
#define __UNIT_TEST_BOOT_LIB_H__

/**
Set the boot manager to boot from a specific device on the next boot. 
This should be set only for the next boot and shouldn't
require any manual clean up
**/
EFI_STATUS
EFIAPI
SetBootNextDevice ( VOID );


#endif