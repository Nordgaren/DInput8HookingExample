#include "stdafx.h"
#include "CustomHooks.h"
#include <iostream>
#include <detours.h>

static BOOL(WINAPI* TrueSystemParametersInfo)(UINT uiAction, UINT uiParam, PVOID pvParam, UINT fWinInis) = SystemParametersInfoA;

BOOL WINAPI SystemParametersInfo_Wrapper(UINT uiAction, UINT uiParam, PVOID pvParam, UINT fWinIni)
{
	//std::cout << "I'm here in the function " << uiAction << std::endl;

	// Stop touching my mouse you fucks
	if (uiAction == SPI_SETMOUSE)
		return true;

	// Call the original SystemParametersInfo function
	return TrueSystemParametersInfo(uiAction, uiParam, pvParam, fWinIni);
}


void SetupHooks()
{
	// Create a console for Debug output
	//AllocConsole();
	//FILE* fstdin = stdin, *fstdout = stdout, *fstderr = stderr;
	//freopen_s(&fstdin,"CONIN$", "r", stdin);
	//freopen_s(&fstdout,"CONOUT$", "w", stdout);
	//freopen_s(&fstderr,"CONOUT$", "w", stderr);
	//std::cout << "I'm here" << std::endl;

	// Detour
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)TrueSystemParametersInfo, SystemParametersInfo_Wrapper);
	DetourTransactionCommit();
}

void RemoveHooks()
{
	//std::cout << "I'm here (Remove)" << std::endl;

	// End Detour
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach(&(PVOID&)TrueSystemParametersInfo, SystemParametersInfo_Wrapper);
	DetourTransactionCommit();
}

