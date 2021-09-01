#include "stdafx.h"
#include "CustomHooks.h"
#include <iostream>
#include <detours.h>

#pragma warning(disable : 4996)

static BOOL(WINAPI* TrueSystemParametersInfo)(UINT uiAction, UINT uiParam, PVOID pvParam, UINT fWinInis) = SystemParametersInfoA;

typedef BOOL(*SystemParametersInfo_t)(UINT uiAction, UINT uiParam, PVOID pvParam, UINT fWinIni);

SystemParametersInfo_t OriginalSystemParametersInfo;

BOOL WINAPI SystemParametersInfo_Wrapper(UINT uiAction, UINT uiParam, PVOID pvParam, UINT fWinIni)
{
	std::cout << "I'm here in the function " << uiAction << std::endl;

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
	//freopen("CONIN$", "r", stdin);
	//freopen("CONOUT$", "w", stdout);
	//freopen("CONOUT$", "w", stderr);
	//std::cout << "I'm here" << std::endl;

	//Detour
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)TrueSystemParametersInfo, SystemParametersInfo_Wrapper);
	DetourTransactionCommit();
}

void RemoveHooks()
{
	//std::cout << "I'm here (Remove)" << std::endl;

	//Detour
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach(&(PVOID&)TrueSystemParametersInfo, SystemParametersInfo_Wrapper);
	DetourTransactionCommit();
}

