# Unit Test Support Repo

## About

This repository contains optional components for the EDK2 UnitTestPkg framework. It allows for
host-based testing and contains additional functionality for Shell-based testing.

### CmockaHostUnitTestPkg

This package contains all libs and external dependencies required to build tests against the
Cmocka testing library.

### HostBasedUnitTestPkg

#### OsServiceLibHost

This library abstracts host-based memory allocation/manipulation to the host-based EDK2 unit tests.

### ShellBasedUnitTestPkg

#### UnitTestBootLib

One of the unique features of the unit test framework is to be able to save text context
and reboot the system.  Since unit tests are generally run from a bootable usb key the framework
has library calls to set boot next for usb.  There is numerous ways this could be done on a given
platform / BDS implementation and therefore this simple library allows customization if needed. 
This package supplies two instances:

* UsbClass Lib: This uses the Usb Class boot option as defined in the UEFI spec and leveraged 
by industry standard USB applications.  
* UsbMicrosoft Lib: This uses a private boot option found in Microsoft UEFI to boot to usb 

## Copyright

Copyright (c) Microsoft Corporation.
SPDX-License-Identifier: BSD-2-Clause-Patent
 