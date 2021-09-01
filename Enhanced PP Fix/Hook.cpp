#include "stdafx.h"
#include "Hook.h"

PROCESS_BASIC_INFORMATION BasicProcessInfo;

void InitializeHooking()
{
	// Get our Process Handle
	const HANDLE Process = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, false, GetCurrentProcessId());

	// Find out our base address, where the Executable image is loaded in memory
	NtQueryInformationProcess(Process, ProcessBasicInformation, &BasicProcessInfo, sizeof(BasicProcessInfo), nullptr);
}

