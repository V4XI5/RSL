#include "ScriptManager.h"
#include "BaseTypeLua.h"
#include "VectorLua.h"
#include "MatrixLua.h"
#include "Matrix43Lua.h"
#include "AttachInfoDataLua.h"
#include "ContactNodeLua.h"
#include "ObjectFlagsLua.h"
#include "HavokBPOLua.h"
#include "HkpRigidBodyLua.h"
#include "HkpSolverInfoLua.h"
#include "HumanFlagsLua.h"
#include "HumanMPFlagsLua.h"
#include "InvItemInfoLua.h"
#include "ObjectRenderDistanceLua.h"
#include "HumanRaycastHitInfoLua.h"
#include "CharacterInstanceLua.h"
#include "HumanInfoLua.h"
#include "ObjectLua.h"
#include "HumanLua.h"
#include "PlayerLua.h"
#include "WorldLua.h"

ScriptManager::~ScriptManager()
{
    delete LuaState;
}

/* Resets the script loader lua state and reloads the core libraries.
 * This includes the scripts in the Core folder.
 */
void ScriptManager::Reset()
{
    delete LuaState;
    Initialize();
    UpdateRfgPointers();
}

/* Initializes the lua state and calls all necessary functions and scripts 
 * needed to setup the scripting system. No inputs or outputs. Uses new
 * to allocate a new sol::state at ScriptManager::LuaState
 */
void ScriptManager::Initialize()
{
    LuaState = new sol::state();
    /* Opens the listed lua core libraries
	 * See here: https://sol2.readthedocs.io/en/stable/api/state.html#lib-enum
	 * and here: https://www.lua.org/manual/5.1/manual.html#5 (LuaJIT is 5.1)
	 * For now there is no Lua sandboxing in place to remove as many barriers for creativity that modders might have had otherwise.
	 */
	LuaState->open_libraries
	(
		sol::lib::base,
		sol::lib::package,
		sol::lib::coroutine,
		sol::lib::string,
		sol::lib::os,
		sol::lib::math,
		sol::lib::table,
		sol::lib::debug,
		sol::lib::bit32,
		sol::lib::io,
		sol::lib::ffi,
		sol::lib::jit
	);
	SetupLua();
}

/* Contains all of the binding code for rfg types and functions and any helper functions.
 * Note that many pieces of binding code are in other files. For example, the binding code for Player
 * is in PlayerLua.h/.cpp. This is intended to speed up compilation by splitting up the files 
 * (not sure if that is really accomplished) and also to keep this function from becoming a several 
 * thousand line behemoth.
 */
void ScriptManager::SetupLua()
{
	RunScript(Globals::GetEXEPath(false) + "RFGR Script Loader/Core/CoreInit.lua");
    sol::state& LuaStateRef = *LuaState; //Used for easier access instead of doing weird ass pointer syntax.

    LuaStateRef["print"] = sol::nil;
    
	//Todo: Make necessary vars read only with sol::readonly(&some_class::variable)
	auto RslTable = LuaStateRef["rsl"].get_or_create<sol::table>();
	RslTable["GetVersion"] = Globals::GetScriptLoaderVersion;
	RslTable["LogModuleBase"] = Lua::LogModuleBase;

	auto RfgTable = LuaStateRef["rfg"].get_or_create<sol::table>();
	RfgTable["HideHud"] = HideHud;
	RfgTable["HideFog"] = HideFog;
	RfgTable["ToggleFog"] = ToggleFog;
	RfgTable["ToggleHud"] = ToggleHud;
	RfgTable["SetFarClip"] = game_render_set_far_clip_distance;
	RfgTable["GetFarClip"] = game_render_get_far_clip_distance;
	RfgTable["SetAlertLevel"] = gsm_set_alert_level;
	RfgTable["GetAlertLevel"] = gsm_get_alert_level;
	RfgTable["TeleportHuman"] = HumanTeleportUnsafe;
	RfgTable["GetPlayer"] = Lua::GetPlayer;
	RfgTable["GetWorld"] = Lua::GetWorld;
	RfgTable["GetPhysicsWorld"] = Lua::GetPhysicsWorld;

    RfgTable["GetGravity"] = Lua::GetGravity;
    RfgTable.set_function("SetGravity", sol::overload(
        [](vector& NewGravity) {Lua::SetGravity(NewGravity); },
        [](float x, float y, float z) {Lua::SetGravity(x, y, z); }));
    RfgTable["ResetGravity"] = Lua::ResetGravity;

	RfgTable["HavokBodyGetPointer"] = HavokBodyGetPointer;
	RfgTable.set_function("ApplyLinearImpulse", sol::overload(HavokBodyApplyLinearImpulseA, HavokBodyApplyLinearImpulseB));

	RfgTable.set_function("TeleportPlayer", sol::overload(
 [](vector Position, matrix Orientation) {HumanTeleportUnsafe(Globals::PlayerPtr, Position, Orientation); }, 
		[](vector Position) {HumanTeleportUnsafe(Globals::PlayerPtr, Position, Globals::PlayerPtr->Orientation); }));

	//LogType enums defined in lua
	//auto LoggerTable = LuaStateRef["Logger"].get_or_create<sol::table>();
	RslTable["OpenLogFile"] = Logger::OpenLogFile;
	RslTable["CloseLogFile"] = Logger::CloseLogFile;
	RslTable["CloseAllLogFiles"] = Logger::CloseAllLogFiles;
	RslTable.set_function("Log", sol::overload(
        [](std::string Message) {Logger::Log(Message, LogInfo, false, true); },
        [](std::string Message, LogType Type) {Logger::Log(Message, Type, false, true); },
        [](std::string Message, LogType Type, bool LogTime) {Logger::Log(Message, Type, LogTime, true); },
        [](std::string Message, LogType Type, bool LogTime, bool Newline) {Logger::Log(Message, Type, LogTime, Newline); }
    ));
	RslTable["LogFlagWithColor"] = Logger::LogFlagWithColor;
	RslTable["GetFlagString"] = Logger::GetFlagString;
	RslTable["LogToFile"] = Logger::LogToFile;
	RslTable["GetTimeString"] = Logger::GetTimeString;

	//This warning appears hundreds of times in a row during binding unless disabled. Is harmless due to some lambdas used to grab usertype variables.
	#pragma warning(push)
	#pragma warning(disable : C4172)
	//Use separate files for these so that if one is edited they don't all need to be recompiled.
	//Not necessarily at huge benefit at first, but it'll grow as more usertypes are added.
	Lua::BindRfgBaseArray(LuaStateRef);
	Lua::BindRfgFArray(LuaStateRef);
	Lua::BindTimestamp(LuaStateRef);
	Lua::BindTimestampPercent(LuaStateRef);
	Lua::BindTimestampRealtime(LuaStateRef);
	Lua::BindColor(LuaStateRef);
	Lua::BindVector(LuaStateRef);
	Lua::BindMatrix(LuaStateRef);
	Lua::BindMatrix43(LuaStateRef);
	Lua::BindAttachInfoData(LuaStateRef);
	Lua::BindContactNode(LuaStateRef);
	Lua::BindObjectContactInfo(LuaStateRef);
	Lua::BindObjectFlags(LuaStateRef);
	//Lua::BindRemoteObjectFlags(LuaStateRef);
	Lua::BindHavokBPO(LuaStateRef);
	Lua::BindHkpMaterial(LuaStateRef);
	Lua::BindHkpEntity(LuaStateRef);
	Lua::BindHkpRigidBody(LuaStateRef);
    Lua::BindHkpSolverInfo(LuaStateRef);
	Lua::BindHumanFlags(LuaStateRef); 
	//Lua::BindHumanMPFlags(LuaStateRef);
	Lua::BindHumanInfoFlags(LuaStateRef);
	Lua::BindHumanPropGeneralInfo(LuaStateRef);
	Lua::BindInventoryItem(LuaStateRef);
	Lua::BindChecksumStri(LuaStateRef);
	Lua::BindInvItemInfo(LuaStateRef);
	Lua::BindFootGroundEffects(LuaStateRef);
	Lua::BindCharDefHead(LuaStateRef);
	Lua::BindObjectRenderDistance(LuaStateRef);
	Lua::BindHumanRaycastHitInfo(LuaStateRef);
	Lua::BindCharacterInstance(LuaStateRef);
	Lua::BindWeaponAnimationFlags(LuaStateRef);
	Lua::BindIKJoint(LuaStateRef);
	Lua::BindNanoCallbackInfo(LuaStateRef);
	Lua::BindHumanInfo(LuaStateRef);
	Lua::BindUsableObject(LuaStateRef);
	Lua::BindPlayerFlags(LuaStateRef);
	Lua::BindScriptSpecificData(LuaStateRef);
	Lua::BindVehicleEnterStruct(LuaStateRef);
	Lua::BindPathfindNavInfo(LuaStateRef);
	Lua::BindUpgradeItem(LuaStateRef);
	Lua::BindPlayerMetadata(LuaStateRef);
	Lua::BindObject(LuaStateRef);
	Lua::BindHuman(LuaStateRef);
	Lua::BindPlayer(LuaStateRef);
	//Setting these manually to ensure there's no accidently overwrites
	LuaStateRef["rfg"]["Object"]["AsObject"] = [](Object& Self)->Object* {return &Self; };
	LuaStateRef["rfg"]["Human"]["AsObject"] = [](Human& Self)->Object* {return static_cast<Object*>(&Self); };
	LuaStateRef["rfg"]["Human"]["AsHuman"] = [](Human& Self)->Human* {return static_cast<Human*>(&Self); };
	LuaStateRef["rfg"]["Player"]["AsObject"] = [](Player& Self)->Object* {return static_cast<Object*>(&Self); };
	LuaStateRef["rfg"]["Player"]["AsHuman"] = [](Player& Self)->Human* {return static_cast<Human*>(&Self); };
	LuaStateRef["rfg"]["Player"]["AsPlayer"] = [](Player& Self)->Player* {return &Self; };

	//World & dependent types
	Lua::BindStreamGridCell(LuaStateRef);
	Lua::BindStreamLayerMaskedCell(LuaStateRef);
	Lua::BindStreamLayer(LuaStateRef);
	Lua::BindDistrictFlags(LuaStateRef);
	Lua::BindTDistrict(LuaStateRef);
	Lua::BindTerritory(LuaStateRef);
	Lua::BindStreamGrid(LuaStateRef);
	Lua::BindGameSaveInfoNewData(LuaStateRef);
	Lua::BindGameSaveInfo(LuaStateRef);
	Lua::BindSaveLoadInfo(LuaStateRef);
	Lua::BindWorldStateBuf(LuaStateRef);
	Lua::BindZoneHeader(LuaStateRef);
	Lua::BindWorldZone(LuaStateRef);
	Lua::BindWorld(LuaStateRef);
	#pragma warning(pop) 

    UpdateRfgPointers();
}

/* Used to ensure a few important game pointers are always up to date.
 * Since these can sometimes change when doing things like loading a save
 * it's necessary to update them in the lua state. This function is called
 * by several hooks when they detect that one of these pointers has changed.
 * If you're hooking something that changes often and needs global state, you
 * should probably update it here as well when it changes.
 */
void ScriptManager::UpdateRfgPointers()
{
    sol::state& LuaStateRef = *LuaState;
	auto RfgTable = LuaStateRef["rfg"].get_or_create<sol::table>();

	RfgTable["ActivePlayer"] = Globals::PlayerPtr;
	RfgTable["ActiveWorld"] = Globals::RfgWorldPtr;
	RfgTable["ActivePhysicsWorld"] = Globals::hkpWorldPtr;
    RfgTable["PhysicsSolver"] = &Globals::hkpWorldPtr->m_dynamicsStepInfo.m_solverInfo;
}

/* Scans all files in the Scripts folder. Creates a new script object and adds it to
 * the script vector (ScriptManager::Scripts) if a file is a valid script. 
 */
void ScriptManager::ScanScriptsFolder()
{
	try 
	{
		Scripts.clear();
		const std::string ScriptFolderPath(Globals::GetEXEPath(false) + "RFGR Script Loader/Scripts/");
		for (auto& i : fs::directory_iterator(ScriptFolderPath))
		{
			if (IsValidScriptExtensionFromPath(i.path().string()))
			{
				const std::string ThisScriptPath = i.path().string();
				const std::string ThisScriptFolderPath = GetScriptFolderFromPath(i.path().string());
				const std::string ThisScriptName = GetScriptNameFromPath(i.path().string());
				Scripts.push_back(Script(ThisScriptPath, ThisScriptFolderPath, ThisScriptName));

				//Logger::Log(i.path().string(), LogInfo);
				//Logger::Log("Script Name: " + ThisScriptName, LogInfo);
				//Logger::Log("Script Folder: " + ThisScriptFolderPath, LogInfo);
			}
		}
	}
	catch(std::exception& Ex)
	{
		std::string ExceptionInfo = Ex.what();
		ExceptionInfo += " \nstd::exception when scanning scripts folder, Additional info: ";
		ExceptionInfo += "File: ";
		ExceptionInfo += __FILE__;
		ExceptionInfo += ", Function: ";
		ExceptionInfo += __func__;
		ExceptionInfo += ", Line: ";
		ExceptionInfo += __LINE__;
		Logger::Log(ExceptionInfo, LogFatalError, true, true);
	}
}

/* Tries to run the file at the given path as a lua script. Includes error 
 * detection and handling code for convenience. If an exception occurs an the 
 * script should be stopped and the exception should be safely contained and
 * logged.
 */
bool ScriptManager::RunScript(const std::string& FullPath)                     
{
    sol::state& LuaStateRef = *LuaState;
	if (IsValidScriptExtensionFromPath(FullPath))
	{
		try
		{
			auto CodeResult = LuaStateRef.script_file(FullPath, [](lua_State*, sol::protected_function_result pfr)
			{
				return pfr;
			}, sol::load_mode::text);

			if (!CodeResult.valid())
			{
				sol::error ScriptError = CodeResult;
				std::exception ScriptException(ScriptError.what());
				throw(ScriptException);
			}
			return true;
		}
		catch (std::exception& Exception)
		{
			Logger::Log(std::string("Exception caught when running " + GetScriptNameFromPath(FullPath) + ": " + std::string(Exception.what())), LogLua | LogError);
			return false;
		}
	}
	else
	{
		return false;
	}
}

/* Tries to an already loaded script at the given index of
 * ScriptManager::Scripts. Includes error detection and handling code 
 * for convenience. If an exception occurs an the script should be 
 * stopped and the exception should be safely contained and logged.
 */
bool ScriptManager::RunScript(const size_t Index)
{
    sol::state& LuaStateRef = *LuaState;
	const std::string& FullPath = Scripts[Index].FullPath;
	try
	{
		auto CodeResult = LuaStateRef.script_file(FullPath, [](lua_State*, sol::protected_function_result pfr)
		{
			return pfr;
		}, sol::load_mode::text);

		if (!CodeResult.valid())
		{
			sol::error ScriptError = CodeResult;
			std::exception ScriptException(ScriptError.what());
			throw(ScriptException);
		}
		return true;
	}
	catch (std::exception& Exception)
	{
		Logger::Log(std::string("Exception caught when running " + Scripts[Index].Name + std::string(Exception.what())), LogLua | LogError);
		return false;
	}
}

/* Tries to the provided string as a lua script. Uses the name for 
 * error logging. Includes error detection and handling code
 * for convenience. If an exception occurs an the script should be
 * stopped and the exception should be safely contained and logged.
 */
bool ScriptManager::RunStringAsScript(std::string Buffer, std::string Name)
{
    sol::state& LuaStateRef = *LuaState;
	try
	{
		auto CodeResult = LuaStateRef.script(Buffer, [](lua_State*, sol::protected_function_result pfr)
		{
			return pfr;
		});

		if (!CodeResult.valid())
		{
			sol::error ScriptError = CodeResult;
			std::exception ScriptException(ScriptError.what());
			throw(ScriptException);
		}
		return true;
	}
	catch (std::exception& Exception)
	{
		Logger::Log(std::string("Exception caught when running " + Name + std::string(Exception.what())), LogLua | LogError);
		return false;
	}
}

/* Gets the name of a file given a path as an input. 
 * Includes file extension in name. Returns an empty
 * string if no forward or backslashes are found.
 */
std::string ScriptManager::GetScriptNameFromPath(std::string FullPath) const
{
	for (int i = FullPath.length() - 1; i > 0; i--)
	{
		if (i != FullPath.length())
		{
			if (FullPath.compare(i, 1, "\\") == 0 || FullPath.compare(i, 1, "/") == 0)
			{
				return FullPath.substr(i + 1, FullPath.length() - i);
			}
		}
	}
	return std::string();
}

/* Gets the path of the folder for a file. Takes the full path
 * of a file as input. Basically just cuts the file name off 
 * the end of it's path. Returns an empty string if no forward
 * or backslashes are found.
 */
std::string ScriptManager::GetScriptFolderFromPath(std::string FullPath) const
{
	for (int i = FullPath.length() - 1; i > 0; i--)
	{
		if (i != FullPath.length())
		{
			if (FullPath.compare(i, 1, "\\") == 0 || FullPath.compare(i, 1, "/") == 0)
			{
				return FullPath.substr(0, i + 1);
			}
		}
	}
	return std::string();
}

/* Gets the extension of a file given it's full path. Returns
 * an empty string if no period is found in the name.
 */
std::string ScriptManager::GetScriptExtensionFromPath(std::string FullPath) const
{
	for (int i = FullPath.length() - 1; i > 0; i--)
	{
		if (FullPath.compare(i, 1, ".") == 0)
		{
			return FullPath.substr(i + 1, FullPath.length() - i);
		}
	}
	return std::string();
}

/* Checks if the file at the provided path has a valid script
 * file extension. Returns true if so, and false if not.
 */
bool ScriptManager::IsValidScriptExtensionFromPath(std::string FullPath)
{
	if (IsValidScriptExtension(GetScriptExtensionFromPath(FullPath)))
	{
		return true;
	}
	return false;
}

/* Checks if the provided string is a valid script file extension.
 * Returns true if so, and false if not. Currently "lua" is 
 * considered valid. It converts the inputted string to lowercase
 * before comparison, so case does not matter.
 */
bool ScriptManager::IsValidScriptExtension(std::string Extension) const
{
    //Transform extension to lowercase only for easy comparison.
	std::transform(Extension.begin(), Extension.end(), Extension.begin(), ::tolower);
    return Extension == "lua";
}

