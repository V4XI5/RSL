#include "GuiSystem.h"
#include "ScriptManager.h"

GuiSystem::GuiSystem()
{

}

GuiSystem::~GuiSystem()
{
	for (const auto& i : GuiList)
	{
		delete i;
	}
}

void GuiSystem::Initialize()
{
	GuiList.push_back(new MenuBarGui(&ShowAppMainMenuBar, "Top Menu Bar"));
	MainMenuBar = (MenuBarGui*)GuiList.back();
	GuiList.push_back(new WelcomeGui(&ShowAppWelcome, "Welcome"));
	Welcome = (WelcomeGui*)GuiList.back();
	GuiList.push_back(new OverlayConsole(&ShowAppConsole, "Lua console"));
	Console = (OverlayConsole*)GuiList.back();
	GuiList.push_back(new ThemeEditorGui(&ShowAppThemeEditor, "Theme editor"));
	ThemeEditor = (ThemeEditorGui*)GuiList.back();
	GuiList.push_back(new TeleportGui(&ShowAppTeleportMenu, "Teleport"));
	Teleport = (TeleportGui*)GuiList.back();
	GuiList.push_back(new IntrospectionGui(&ShowAppIntrospectionMenu, "Introspection"));
	Introspection = (IntrospectionGui*)GuiList.back();
	GuiList.push_back(new GeneralTweaksGui(&ShowAppTweaksMenu, "General tweaks"));
	TweaksMenu = (GeneralTweaksGui*)GuiList.back();
	GuiList.push_back(new TextEditor(&ShowAppScriptEditor, "Script editor"));
	ScriptEditor = (TextEditor*)GuiList.back();
	GuiList.push_back(new ScriptSelectGui(&ShowAppScriptsMenu, "Scripts"));
	ScriptList = (ScriptSelectGui*)GuiList.back();
	GuiList.push_back(new LogWindow(&ShowAppLogWindow , "Logger"));
	LogGui = (LogWindow*)GuiList.back();

	for (const auto& i : GuiList)
	{
		i->Gui = this;
	}

	/*TopMenuBar.ShowAppMainWindow = &ShowAppWelcome;
	TopMenuBar.ShowAppConsole = &ShowAppConsole;
	TopMenuBar.ShowAppThemeEditor = &ShowAppThemeEditor;
	TopMenuBar.ShowAppAbout = &ShowAppAbout;
	TopMenuBar.ShowAppSimpleOverlay = &ShowAppSimpleOverlay;
	TopMenuBar.ShowAppTeleportMenu = &ShowAppTeleportMenu;
	TopMenuBar.ShowAppHelpWindow = &ShowAppHelpWindow;
	TopMenuBar.ShowAppIntrospectionMenu = &ShowAppIntrospectionMenu;
	TopMenuBar.ShowAppTweaksMenu = &ShowAppTweaksMenu;
	TopMenuBar.ShowAppScriptsMenu = &ShowAppScriptsMenu;
	TopMenuBar.ShowAppScriptEditor = &ShowAppScriptEditor;
	TopMenuBar.ShowAppLogWindow = &ShowAppLogWindow;
	TopMenuBar.Initialize(&ShowAppMainMenuBar);

	MainWindow.Initialize(&ShowAppWelcome);
	Console.Initialize(&ShowAppConsole);
	ThemeEditor.Initialize(&ShowAppThemeEditor);
	TeleportMenu.Initialize(&ShowAppTeleportMenu);
	IntrospectionMenu.Initialize(&ShowAppIntrospectionMenu);
	TweaksMenu.Initialize(&ShowAppTweaksMenu);

	ScriptEditor.Initialize(&ShowAppScriptEditor);
	ScriptEditor.SetLanguageDefinition(TextEditor::LanguageDefinition::Lua());

	ScriptsMenu.ScriptEditor = &ScriptEditor;
	ScriptsMenu.ScriptEditorState = &ShowAppScriptEditor;
	ScriptsMenu.Initialize(&ShowAppScriptsMenu);

	LogGui.Initialize(&ShowAppLogWindow);*/
}

/*Should only be doing this once.*/
void GuiSystem::SetScriptManager(ScriptManager* _Scripts)
{
	Scripts = _Scripts;
	for (const auto& i : GuiList)
	{
		i->Scripts = _Scripts;
	}

	/*Scripts = _Scripts;
	MainWindow.Scripts = _Scripts;
	Console.Scripts = _Scripts;
	ScriptsMenu.Scripts = _Scripts;
	ScriptEditor.Scripts = _Scripts;
	TopMenuBar.Scripts = _Scripts;*/
}

void GuiSystem::Draw()
{
	try
	{
		if (!ImGuiInitialized)
		{
			if (DrawPassedOnce)
			{
				throw std::exception("ImGui not initialized! Failed to draw overlay gui!");
			}
			return;
		}
		if (!PlayerPtr)
		{
			if (DrawPassedOnce)
			{
				throw std::exception("Player pointer is null! Failed to draw overlay gui!");
			}
			return;
		}
		if (!Scripts)
		{
			if (DrawPassedOnce)
			{
				throw std::exception("Scripts pointer is null! Failed to draw overlay gui!");
			}
			return;
		}
		//Used on the first successful draw of the gui to insure that each gui element has valid PlayerPtr*, Scripts*, and Gui* values. 
		//Very duct-tapey solution, but it works. Put in place since the values in menus are sometimes not being set properly, causing crashes.
		std::call_once(InitialDrawCheck, [&]()
		{
			for (const auto& i : GuiList)
			{
				i->PlayerPtr = PlayerPtr;
				i->Scripts = Scripts;
				i->Gui = this;

				//This is used to prevent the spamming of failure messages from invalid pointers before they've been set.
				//So, error messages from invalid pointers will only show up after they've all been set properly once.
				//Need to consider if this could obscure bugs in some instances, but for now I've got no better way of doing this.
				DrawPassedOnce = true;
			}
		});

		if (OverlayActive)
		{
			for (const auto& i : GuiList)
			{
				try
				{
					i->Draw();
				}
				catch (const std::exception& Ex)
				{
					std::string ExceptionInfo = Ex.what();
					ExceptionInfo += " \nstd::exception caught when drawing overlay sub-gui! ";
					ExceptionInfo += ", Additional info: ";
					ExceptionInfo += "Sub-gui: ";
					ExceptionInfo += i->Title;
					ExceptionInfo += ", File: ";
					ExceptionInfo += __FILE__;
					ExceptionInfo += ", Function: ";
					ExceptionInfo += __func__;
					ExceptionInfo += ", Line: ";
					ExceptionInfo += __LINE__;
					//Logger::Log(ExceptionInfo, LogError, true, true);
					throw std::exception(ExceptionInfo.c_str());
				}
			}
		}
		if (LuaConsoleActive && !OverlayActive)
		{
			try
			{
				Console->Draw();
			}
			catch (const std::exception& Ex)
			{
				std::string ExceptionInfo = Ex.what();
				ExceptionInfo += " \nstd::exception caught when drawing lone console! ";
				ExceptionInfo += ", Additional info: ";
				ExceptionInfo += "File: ";
				ExceptionInfo += __FILE__;
				ExceptionInfo += ", Function: ";
				ExceptionInfo += __func__;
				ExceptionInfo += ", Line: ";
				ExceptionInfo += __LINE__;
				//Logger::Log(ExceptionInfo, LogError, true, true);
				throw std::exception(ExceptionInfo.c_str());
			}
		}
	}
	catch (const std::exception& Ex)
	{
		std::string ExceptionInfo = Ex.what();
		ExceptionInfo += " \nstd::exception caught when drawing overlay gui! ";
		ExceptionInfo += ", Additional info: ";
		ExceptionInfo += "File: ";
		ExceptionInfo += __FILE__;
		ExceptionInfo += ", Function: ";
		ExceptionInfo += __func__;
		ExceptionInfo += ", Line: ";
		ExceptionInfo += __LINE__;
		Logger::Log(ExceptionInfo, LogError, true, true);
		//MessageBoxA(FindTopWindow(GetProcessID("rfg.exe")), ExceptionInfo.c_str(), "Failed to draw overlay gui!", MB_OK);
	}
	catch (...)
	{
		std::string ExceptionInfo = "Default exception caught when drawing overlay gui! ";
		ExceptionInfo += ", Additional info: ";
		ExceptionInfo += "File: ";
		ExceptionInfo += __FILE__;
		ExceptionInfo += ", Function: ";
		ExceptionInfo += __func__;
		ExceptionInfo += ", Line: ";
		ExceptionInfo += __LINE__;
		Logger::Log(ExceptionInfo, LogError, true, true);
		//MessageBoxA(FindTopWindow(GetProcessID("rfg.exe")), ExceptionInfo.c_str(), "Failed to draw overlay gui!", MB_OK);
	}


	/*if (OverlayActive)
	{
		MainWindow.Draw("Welcome");
		//Console.Draw("Lua Console");
		ThemeEditor.Draw("Theme Editor");
		TeleportMenu.Draw("Teleport Menu");
		IntrospectionMenu.Draw("Introspection Menu");
		TweaksMenu.Draw("General Tweaks Menu");
		ScriptsMenu.Draw("Script Select Menu");
		ScriptEditor.Render(std::string("Script Editor - " + ScriptEditor.ScriptName).c_str());// , ImVec2(400.0f, 400.0f));
		TopMenuBar.Draw("Top Menu Bar");
		LogGui.Draw("Logger");
	}
	if (LuaConsoleActive)
	{
		Console.Draw("Lua Console");
	}*/
}

void GuiSystem::SetPlayerPtr(Player* NewPlayerPtr)
{
	PlayerPtr = NewPlayerPtr;
	for (const auto& i : GuiList)
	{
		i->PlayerPtr = NewPlayerPtr;
	}

	/*PlayerPtr = NewPlayerPtr;
	Console.PlayerPtr = NewPlayerPtr;
	//ThemeEditor.PlayerPtr = NewPlayerPtr;
	TeleportMenu.PlayerPtr = NewPlayerPtr;
	IntrospectionMenu.PlayerPtr = NewPlayerPtr;
	TweaksMenu.PlayerPtr = NewPlayerPtr;*/
}

/*Sets PlayerPtr for all GUI classes which use it.*/
void GuiSystem::SetPlayerPtr(void* NewPlayerPtr)
{
	SetPlayerPtr((Player*)NewPlayerPtr);
}

void GuiSystem::ToggleLuaConsole()
{
	LuaConsoleActive = !LuaConsoleActive;
	ShowAppConsole = !ShowAppConsole;
	/*if (LuaConsoleActive && !ShowAppConsole)
	{
		ShowAppConsole = true;
	}*/
}

bool GuiSystem::IsLuaConsoleActive()
{
	return LuaConsoleActive;
}

void GuiSystem::DeactivateLuaConsole()
{
	LuaConsoleActive = false;
}

void GuiSystem::ActivateLuaConsole()
{
	LuaConsoleActive = true;
}
