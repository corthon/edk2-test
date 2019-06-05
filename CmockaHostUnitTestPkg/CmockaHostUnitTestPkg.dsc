## @file CmockaHostUnitTestPkg.dsc
# 
# Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>
# This program and the accompanying materials
# are licensed and made available under the terms and conditions of the BSD License
# which accompanies this distribution.  The full text of the license may be found at
# http://opensource.org/licenses/bsd-license.php.
#
# THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
# WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
#
##

[Defines]
  PLATFORM_NAME                  = CmockaHostUnitTestPkg
  PLATFORM_GUID                  = 3d1bcbb4-7edf-416e-a14c-cda32eefa141
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  OUTPUT_DIRECTORY               = Build/CmockaHostUnitTestPkg
  SUPPORTED_ARCHITECTURES        = IA32|X64
  BUILD_TARGETS                  = DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT


[PcdsFixedAtBuild]


[LibraryClasses]
  BaseLib|MdePkg/Library/BaseLibHost/BaseLibHost.inf
  BaseMemoryLib|MdePkg/Library/BaseMemoryLibHost/BaseMemoryLibHost.inf
  MemoryAllocationLib|MdePkg/Library/MemoryAllocationLibHost/MemoryAllocationLibHost.inf
  DebugLib|MdePkg/Library/DebugLibHost/DebugLibHost.inf

  PeiServicesLib|MdePkg/Library/PeiServicesLib/PeiServicesLib.inf

  PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
  PerformanceLib|MdePkg/Library/BasePerformanceLibNull/BasePerformanceLibNull.inf
  ReportStatusCodeLib|MdePkg/Library/BaseReportStatusCodeLibNull/BaseReportStatusCodeLibNull.inf
  SafeIntLib|MdePkg/Library/BaseSafeIntLib/BaseSafeIntLib.inf

  UefiLib|MdePkg/Library/UefiLib/UefiLib.inf
  PrintLib|MdePkg/Library/BasePrintLib/BasePrintLib.inf

  SecurityManagementLib|MdeModulePkg/Library/DxeSecurityManagementLib/DxeSecurityManagementLib.inf
  TpmMeasurementLib|SecurityPkg/Library/DxeTpmMeasurementLib/DxeTpmMeasurementLib.inf
  PeCoffLib|MdePkg/Library/BasePeCoffLib/BasePeCoffLib.inf
  PeCoffExtraActionLib|MdePkg/Library/BasePeCoffExtraActionLibNull/BasePeCoffExtraActionLibNull.inf
  DxeServicesLib|MdePkg/Library/DxeServicesLib/DxeServicesLib.inf

  OsServiceLib|UnitTestPkg/Library/OsServiceLibHost/OsServiceLibHost.inf

  UnitTestLib|CmockaHostUnitTestPkg/Library/UnitTestLib/UnitTestLibcmocka.inf
  UnitTestAssertLib|CmockaHostUnitTestPkg/Library/UnitTestAssertLib/UnitTestAssertLibcmocka.inf

  NULL|CmockaHostUnitTestPkg/Library/CmockaLib/CmockaLib.inf

[LibraryClasses.common.USER_DEFINED]

[Components]
  CmockaHostUnitTestPkg/Sample/SampleUnitTestHost/SampleUnitTestHost.inf {
  <LibraryClasses>
    NULL|CmockaHostUnitTestPkg/Library/CmockaLib/CmockaLib.inf
  }
    
  CmockaHostUnitTestPkg/Sample/SampleUnitTestDirect/SampleUnitTestcmocka.inf {
  <LibraryClasses>
    NULL|CmockaHostUnitTestPkg/Library/CmockaLib/CmockaLib.inf
  }


!include CmockaHostUnitTestPkg/CmockaHostUnitTestBuildOption.dsc
