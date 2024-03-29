/**

Implement UnitTestBootLib using internal microsoft uefi boot usb boot option 

Copyright (c) Microsoft
**/

#include <PiDxe.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/BaseLib.h>
#include <Library/PrintLib.h>

EFI_STATUS
EFIAPI
SetBootNextDevice (
  VOID
  )
{
  EFI_STATUS  Status;
  INT16        BootOptionIndex;
  CHAR16      BootOptionName[30];
  CHAR16      *BootOptionIndexChar = NULL;
  UINT8       *OptionBuffer = NULL;
  UINTN       OptionBufferSize = 0, VariableSize = 0;
  BOOLEAN     IsUsbOptionFound = FALSE;

  StrCpyS(BootOptionName, sizeof(BootOptionName)/sizeof(CHAR16), L"Boot000");
  BootOptionIndexChar = BootOptionName + StrLen(BootOptionName);

  //
  // Walk through each of the first 10 boot options looking for the
  // generic USB boot option.
  for (BootOptionIndex = 0; BootOptionIndex < 10; BootOptionIndex++)
  {
    // Construct the BootOption name for this boot option.
    // Do this by altering the last character of the name.
    UnicodeValueToStringS(BootOptionIndexChar, sizeof(BootOptionName) - sizeof(L"Boot000"), 0, (INT64)BootOptionIndex, 1);

    // Attempt to retrieve the option.
    DEBUG(( DEBUG_VERBOSE, "%a - Checking for %s...\n",__FUNCTION__ , BootOptionName ));
    VariableSize = OptionBufferSize;
    Status = gRT->GetVariable( BootOptionName,
                               &gEfiGlobalVariableGuid,
                               NULL,
                               &VariableSize,
                               OptionBuffer );
    // If we need a larger buffer, let's do that now.
    if (Status == EFI_BUFFER_TOO_SMALL)
    {
      // Free the existing buffer.
      if (OptionBuffer != NULL)
      {
        FreePool( OptionBuffer );
      }
      // Allocate a larger buffer.
      OptionBuffer = AllocatePool( VariableSize );
      // If you fail to... we've gotta get out of here.
      if (OptionBuffer == NULL)
      {
        DEBUG(( DEBUG_ERROR, "%a - Failed to allocate memory for Boot option variable %s...\n", __FUNCTION__, BootOptionName ));
        return EFI_OUT_OF_RESOURCES;
      }
      OptionBufferSize = VariableSize;

      // Now that we've got a larger buffer, try that again.
      Status = gRT->GetVariable( BootOptionName,
                                 &gEfiGlobalVariableGuid,
                                 NULL,
                                 &VariableSize,
                                 OptionBuffer );
    }

    // If we failed to retrieve this option... move on with your life.
    if (EFI_ERROR( Status ))
    {
      DEBUG(( DEBUG_VERBOSE, "%a - Failed to locate option (%r). Moving on.\n", __FUNCTION__, Status ));
      continue;
    }

    // If we found the option, check to see whether this is the generic USB option.
    // For now... we're lazy... just check the last four bytes (which should be the
    // optional data) and see whether it's "USB".
    if (VariableSize > 4 &&
        OptionBuffer[VariableSize - 4] == 'U' && OptionBuffer[VariableSize - 3] == 'S' &&
        OptionBuffer[VariableSize - 2] == 'B' && OptionBuffer[VariableSize - 1] == 0x00 )
    {
      IsUsbOptionFound = TRUE;
      break;
    }
  }

  //
  // If the correct boot option was found,
  // set it to the BootNext variable.
  if (IsUsbOptionFound)
  {
    Status = gRT->SetVariable( L"BootNext",
                               &gEfiGlobalVariableGuid,
                               (EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE),
                               sizeof( BootOptionIndex ),
                               &BootOptionIndex );
    DEBUG(( DEBUG_VERBOSE, "%a - Set BootNext Status (%r)\n", __FUNCTION__, Status ));
  }
  else
  {
    DEBUG(( DEBUG_WARN, "%a - Could not find generic USB boot option.\n", __FUNCTION__ ));
    Status = EFI_NOT_FOUND;
  }

  // Always put away your toys.
  if (OptionBuffer != NULL)
  {
    FreePool( OptionBuffer );
  }

  return Status;  
} // SetBootNextDevice()
