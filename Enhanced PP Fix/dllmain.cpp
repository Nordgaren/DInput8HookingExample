// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "DInput8.h"
#include "Hook.h"
#include "CustomHooks.h"
#include <iostream>

void Init(HMODULE Module)
{
	//char DirPath[MAX_PATH];
	//GetModuleFileNameA(Module, DirPath, MAX_PATH);
	// Load the original dinput8.dll from the system directory
	char DInputDllPath[MAX_PATH];
	GetSystemDirectoryA(DInputDllPath, MAX_PATH);
	strcat_s(DInputDllPath, "\\dinput8.dll");
	DInput8DLL = LoadLibraryA(DInputDllPath);
	if (DInput8DLL > (HMODULE)31)
	{
		OriginalFunction = (DirectInput8Create_t)GetProcAddress(DInput8DLL, "DirectInput8Create");
	}
	InitializeHooking();
	SetupHooks();
}

BOOL APIENTRY DllMain(HMODULE Module,
	DWORD  ReasonForCall,
	LPVOID Reserved)
{
	switch (ReasonForCall)
	{
	case DLL_PROCESS_ATTACH:
		Init(Module);
		break;
	case DLL_PROCESS_DETACH:
		RemoveHooks();
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}

