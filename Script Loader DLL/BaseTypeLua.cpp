#include "BaseTypeLua.h"
#include "Functions.h"

void Lua::BindNanoCallbackInfo(sol::state & LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<nano_callback_info>();
	Utype.set("TargetHandle", &nano_callback_info::target_handle);
	Utype.set("KilledByNano", &nano_callback_info::killed_by_nano);
	Utype.set("HumanNanoIndex", &nano_callback_info::human_nano_index);
	LuaState.set_usertype("NanoCallbackInfo", Utype);
}

void Lua::BindTimestamp(sol::state& LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
	auto Utype = RfgTable.create_simple_usertype<Timestamp>();
	Utype.set("new", sol::no_constructor);
	Utype.set("Value", &Timestamp::value);
	LuaState.set_usertype("Timestamp", Utype);
}