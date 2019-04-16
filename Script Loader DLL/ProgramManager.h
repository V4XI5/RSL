#pragma once
#include "ScriptManager.h"

class ProgramManager
{
public:
	ProgramManager(HMODULE hModule);
	~ProgramManager();

	void Initialize();
	void OpenConsole();
	bool LoadDataFromConfig();
	void SetMemoryLocations();

	void CreateGameHooks(bool EnableNow);
	void CreateD3D11Hooks(bool EnableNow);

	bool ShouldClose();
	void ProcessInput();
	void Update();
	///MSG msg;
	
	void CloseConsole();
	void Exit();

	HMODULE ScriptLoaderModule;
	HWND GameWindowHandle = nullptr;

	CameraWrapper Camera;
	FunctionManager Functions;
	ScriptManager Scripts;
	HookManager Hooks;

	bool LoadFailed = false;
	bool PreExistingConsole = true;
	DWORD PID = 0;
	uintptr_t ModuleBase = 0;
	unsigned int ExitKeysPressCount = 0;

	bool SuccessfulExit = false;
};

