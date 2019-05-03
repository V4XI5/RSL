
/* Functions.h/.cpp contain function pointers for many of rfg's functions. They can be used
 * to call rfg's functions for our own use, and also to hook these functions and expand their
 * behavior. These function pointers are initialized in FunctionManager.cpp. The declarations
 * here are only used to define the inputs, calling conventions, and returns of these functions.
 */

#pragma once
#include "ItsyBitsy.h"
//#include "RFGR Structs/KeenNamespace.h"

extern void DisableCameraCode(DWORD AddressY, DWORD AddressZ); //Takes addresses for instructions affecting y and z. Alternatively x and z may work, since one piece seems to be shared between two coords.
extern void RestoreCameraCode();
extern void DisableCameraDirectionCode(DWORD Address1, DWORD Address2, DWORD Address3, DWORD Address4, DWORD Address5);
extern void RestoreCameraDirectionCode();

extern void HideHud(bool Hide);
extern void HideFog(bool Hide);
extern void ToggleHud();
extern void ToggleFog();

using F_Camera_Start_Slew_Mode = void(__cdecl*)();
extern F_Camera_Start_Slew_Mode Camera_Start_Slew_Mode;

using F_Camera_Stop_Slew_Mode = void(__cdecl*)();
extern F_Camera_Stop_Slew_Mode Camera_Stop_Slew_Mode;

using F_Interface_Debug_Mode_Activate = void(__cdecl*)();
extern F_Interface_Debug_Mode_Activate Interface_Debug_Mode_Activate;

using F_Keen_Debug_WriteToLogFile = void(__cdecl*)(char* String);
extern F_Keen_Debug_WriteToLogFile Keen_Debug_WriteToLogFile;

using F_Hud_Display_Distance = void(__cdecl*)(bool Value);
extern F_Hud_Display_Distance Hud_Display_Distance;

//.text:009BCD30 rfg.exe:$18CD30 #18C130 <console_set_console_mode>
using F_console_set_console_mode = void(__cdecl*)(vconsole_mode);
extern F_console_set_console_mode console_set_console_mode;

//.text:009BCD50 rfg.exe:$18CD50 #18C150 <console_get_console_mode>
using F_console_get_console_mode = vconsole_mode(__cdecl*)();
extern F_console_get_console_mode console_get_console_mode;

using F_Console_Init = void(__cdecl*)(vconsole_config* ConsoleInit);
extern F_Console_Init Console_Init;

using F_Console_Activate = void(__cdecl*)();
extern F_Console_Activate Console_Activate;

using F_Console_Deactivate = void(__cdecl*)();
extern F_Console_Deactivate Console_Deactivate;

using F_Console_Printf = void(__cdecl*)(const char* String);
extern F_Console_Printf Console_Printf;

using F_Console_Display_Help = void(__cdecl*)();
extern F_Console_Display_Help Console_Display_Help;

using F_Console_Command_Enable = void(__cdecl*)(const char* String, bool Activate);
extern F_Console_Command_Enable Console_Command_Enable;

using F_Console_Do_Command = void(__cdecl*)(const char* String);
extern F_Console_Do_Command Console_Do_Command;

using F_Camera_First_Person_Pre_Process = void(__cdecl*)();
extern F_Camera_First_Person_Pre_Process Camera_First_Person_Pre_Process;

using F_Camera_Start_Third_Person = void(__cdecl*)();
extern F_Camera_Start_Third_Person Camera_Start_Third_Person;

using F_Game_Print_Screen = void(__cdecl*)(char* String);
extern F_Game_Print_Screen Game_Print_Screen;

using F_camera_free_system_init = void(__cdecl* )();
extern F_camera_free_system_init camera_free_system_init;

using F_camera_free_mode_init = void(__cdecl*)();
extern F_camera_free_mode_init camera_free_mode_init;

using F_console_chat_printf = void(__cdecl*)(const char* String);
extern F_console_chat_printf console_chat_printf;

using F_unused_dcf_r_show_mem_usage = void(__cdecl*)();
extern F_unused_dcf_r_show_mem_usage unused_dcf_r_show_mem_usage;

using F_rfg_dyn_get_active_destruction_frame = unsigned __int16(__cdecl*)();
extern F_rfg_dyn_get_active_destruction_frame rfg_dyn_get_active_destruction_frame;

using F_rfg_dyn_reset_destruction_frame = void(__cdecl*)(unsigned __int16 Frame);
extern F_rfg_dyn_reset_destruction_frame rfg_dyn_reset_destruction_frame;

using F_rfg_dyn_system_shutdown = void(__cdecl*)();
extern F_rfg_dyn_system_shutdown rfg_dyn_system_shutdown;

using F_get_screen_width = int(__cdecl*)();
extern F_get_screen_width get_screen_width;

using F_console_is_active = bool(__cdecl*)();
extern F_console_is_active console_is_active;

using F_debug_spew_projectile = void(__cdecl*)(const char* Format);
extern F_debug_spew_projectile debug_spew_projectile;

using F_debug_spew_game_io = void(__cdecl*)(const char* Format);
extern F_debug_spew_game_io debug_spew_game_io;

using F_rl_render_lib_get_metrics = rl_renderer_metrics*(__cdecl* )();
extern F_rl_render_lib_get_metrics rl_render_lib_get_metrics;

using F_profile_dump_info = void(__cdecl*)();
extern F_profile_dump_info profile_dump_info;

using F_vint_render_text = void(__cdecl*)(int _handle, const unsigned int* _text, unsigned int _first_char, unsigned int _num_chars, matrix23* _xform, 
      vector2* _pos, bool reversed, vint_res_offset _res_offset_x, vint_res_offset _res_offset_y, vint_res_scale _res_scale_x, vint_res_scale _res_scale_y);
extern F_vint_render_text vint_render_text;

using F_xray_effect_start = void(__cdecl*)(xray_effect_types xray_effect_type);
extern F_xray_effect_start xray_effect_start;

using F_xray_effect_stop = void(__cdecl*)(xray_effect_types xray_effect_type);
extern F_xray_effect_stop xray_effect_stop;

using F_camera_start_first_person = void(__cdecl*)(bool Smooth);
extern F_camera_start_first_person camera_start_first_person;

using F_camera_stop_first_person = void(__cdecl*)(bool Smooth);
extern F_camera_stop_first_person camera_stop_first_person;

using F_key_down = void(__cdecl*)(unsigned int Scancode);
extern F_key_down key_down;

using F_game_render_set_bloom_exposure_factor = void(__cdecl*)(float ExposureFactor);
extern F_game_render_set_bloom_exposure_factor game_render_set_bloom_exposure_factor;

using F_game_render_set_hdr_state = void(__cdecl*)(rl_hdr_state* hdr_state);
extern F_game_render_set_hdr_state game_render_set_hdr_state;

using F_game_render_2d_text = void(__cdecl*)(const char* str, vector* text_pos);
extern F_game_render_2d_text game_render_2d_text;

using F_ui_add_debug_text = unsigned int(__cdecl*)(const char *text, debug_text_posn type);
extern F_ui_add_debug_text ui_add_debug_text;

using F_get_depth_of_field_enabled = bool(__thiscall*)(void* ThisCamera); //bool __thiscall rl_camera::get_depth_of_field_enabled(rl_camera *this)
extern F_get_depth_of_field_enabled get_depth_of_field_enabled;

using F_set_depth_of_field_enabled = void(__thiscall*)(void* ThisCamera, bool Enabled); //void __thiscall rl_camera::set_depth_of_field_enabled(rl_camera *this, bool depth_of_field_enabled)
extern F_set_depth_of_field_enabled set_depth_of_field_enabled;

using F_character_controller_set_pos = void(__thiscall*)(void* ThisController, vector* Position); //void __thiscall character_controller::set_pos(character_controller *this, vector *pos)																			   
extern F_character_controller_set_pos character_controller_set_pos; //IDA shows this as using __thiscall, but using that causes the game to immediately crash

using F_fog_of_war_clear = void(__cdecl*)();
extern F_fog_of_war_clear fog_of_war_clear;

using F_Hud_Hide = void(__cdecl*)(bool HideHud);
extern F_Hud_Hide Hud_Hide;

using F_game_render_set_fog_enabled = void(__cdecl*)(bool Enabled);
extern F_game_render_set_fog_enabled game_render_set_fog_enabled;

//typedef void (__cdecl* explosion_create)(explosion_info* ExplosionInfo, object* Source, object* Owner, vector* Position, matrix* Orientation, vector* Directiom, weapon_info* WeaponInfo, bool FromServer)
using F_explosion_create = void(__cdecl*)(explosion_info* ExplosionInfo, void* Source, void* Owner, vector* Position,
                                          matrix* Orientation, vector* Direction, void* WeaponInfo, bool FromServer);
extern F_explosion_create ExplosionCreate;

//.text:0129DD00 rfg.exe:$86DD00 #86D100 <keen::graphics::beginFrame>
using F_keen_graphics_beginframe = void(__cdecl*)(void* GraphicsSystem);
extern F_keen_graphics_beginframe GraphicsBeginFrame;

//.text:00B992B0 rfg.exe:$1692B0 #1686B0 <mouse_generic_auto_centering>
using F_MouseGenericAutoCentering = void(__cdecl*)(bool AutoCentering);
extern F_MouseGenericAutoCentering MouseGenericAutoCentering;

//.text:00D00290 rfg.exe:$2D0290 #2CF690 <camera_view_data::set_view>
using F_CameraViewDataSetView = void(__cdecl*)(CameraViewData* ViewData, CameraViewTableEntry* ViewTableEntry, bool SkipTransition);
extern F_CameraViewDataSetView CameraViewDataSetView;

//.text:00A65A80 rfg.exe:$6D5A80 #6D4E80 <player::do_frame>
using F_PlayerDoFrame = void(__fastcall*)(Player* PlayerPtr);
extern F_PlayerDoFrame PlayerDoFrame;

//.text:00A6ECA0 rfg.exe:$6DECA0 #6DE0A0 <player::player>
using F_PlayerConstructor = void(__fastcall*)(Player* PlayerPtr);
extern F_PlayerConstructor PlayerConstructor;

//.text:007A53D0 rfg.exe:$4153D0 #4147D0 <character_controller::set_pos>
using F_CharacterControllerSetPos = void(__fastcall*)(CharacterController* CharController, vector* Position);
extern F_CharacterControllerSetPos CharacterControllerSetPos;

//.text:00A1C310 rfg.exe:$68C310 #68B710 <object::update_pos_and_orient> //void __thiscall object::update_pos_and_orient(object *this, vector *update_pos, matrix *update_orient, bool set_havok_data)
using F_ObjectUpdatePosAndOrient = void(__fastcall*)(Object*, void*, vector*, matrix*, bool); //2nd arg is edx, needed for __thiscall functions.
extern F_ObjectUpdatePosAndOrient ObjectUpdatePosAndOrient;

//.text:009A4DC0 rfg.exe:$614DC0 #6141C0 <object::update_render> //void __thiscall object::update_render(object *this, rl_renderer *__formal)
//.text:009A4D00 rfg.exe:$614D00 #614100 <object::update_streaming_box> //void __thiscall object::update_streaming_box(object *this)

//.text:007E9530 rfg.exe:$429530 #428930 <havok_body_get_pos_orient>
using F_HavokBodyGetPositionAndOrient = void(__cdecl*)(unsigned int Handle, vector* Position, matrix* Orient);
extern F_HavokBodyGetPositionAndOrient HavokBodyGetPositionAndOrient;

//.text:007D6EA0 rfg.exe:$416EA0 #4162A0 <havok_body_set_position> //void __cdecl havok_body_set_position(unsigned int handle, vector *pos)
using F_HavokBodySetPosition = void(__cdecl*)(unsigned int Handle, vector* Position);
extern F_HavokBodySetPosition HavokBodySetPosition;

//.text:007D6E10 rfg.exe:$416E10 #416210 <havok_body_set_pos_orient>

//.text:007E3700 rfg.exe:$423700 #422B00 <havok_body_set_pos_orient>
using F_HavokBodySetPositionAndOrient = void(__cdecl*)(unsigned int Handle, vector* Position, matrix* Orient);
extern F_HavokBodySetPositionAndOrient HavokBodySetPositionAndOrient;

//.text:00A5AF70 rfg.exe:$69AF70 #69A370 <human::update_pos_and_orient> //void __thiscall human::update_pos_and_orient(human *this, vector *update_pos, matrix *update_orient, bool set_havok_data)
using F_HumanUpdatePosAndOrient = void(__fastcall*)(Human*, void*, vector*, matrix*, bool); //2nd arg is edx, needed for __thiscall functions.
extern F_HumanUpdatePosAndOrient HumanUpdatePosAndOrient;

//.text:00A3C660 rfg.exe:$67C660 #67BA60 <human_teleport_unsafe> //void __cdecl human_teleport_unsafe(human *hp, vector pos, matrix orient)
using F_HumanTeleportUnsafe = void(__cdecl*)(Human* HumanPtr, vector Position, matrix Orientation);
extern F_HumanTeleportUnsafe HumanTeleportUnsafe;

//.text:00A5A7A0 rfg.exe:$69A7A0 #699BA0 <human_teleport>
/*typedef void(__cdecl* F_HumanTeleport)(Human* HumanPtr, vector* Position, matrix* Orientation, float PlacementRange, bool AllowFail);
extern F_HumanTeleport HumanTeleport;*/



/*Start of MP Detection Hooks*/

//.text:00590DD0 rfg.exe:$1D0DD0 #1D01D0 <kaiko::GameLinkLobby::is_valid>
using F_IsValidGameLinkLobbyKaiko = bool(__fastcall*)(void* This); //2nd arg is edx, needed for __thiscall functions.
extern F_IsValidGameLinkLobbyKaiko IsValidGameLinkLobbyKaiko;

//.text:0078C750 rfg.exe:$3CC750 #3CBB50 <gamemusic_multiplayer_start>
using F_GameMusicMultiplayerStart = void(__cdecl*)();
extern F_GameMusicMultiplayerStart GameMusicMultiplayerStart;

//.text:00857740 rfg.exe:$497740 #496B40 <init_multiplayer_data_item_respawn>
using F_InitMultiplayerDataItemRespawn = void(__cdecl*)(void* Item);
extern F_InitMultiplayerDataItemRespawn InitMultiplayerDataItemRespawn;

//.text:008B50B0 rfg.exe:$4F50B0 #4F44B0 <hud_ui_multiplayer_process>
using F_HudUiMultiplayerProcess = void(__cdecl*)(float DeltaTime);
extern F_HudUiMultiplayerProcess HudUiMultiplayerProcess;

//.text:008D6D80 rfg.exe:$516D80 #516180 <hud_ui_multiplayer_enter>
using F_HudUiMultiplayerEnter = void(__cdecl*)();
extern F_HudUiMultiplayerEnter HudUiMultiplayerEnter;

/*End of MP Detection Hooks*/


//bool __cdecl keen::graphics::resizeRenderSwapChain(keen::RenderSwapChain *pSwapChain, unsigned int newWidth, unsigned int newHeight)
//Can map out keen::RenderSwapChain later if data is needed from it, currently just hooking this as a signal init the D3D11 pointers again.
//.text:00C2AB20 rfg.exe:$86AB20 #869F20 <keen::graphics::resizeRenderSwapChain>
using F_KeenGraphicsResizeRenderSwapchain = bool(__cdecl*)(void* KeenSwapchain, unsigned int NewWidth, unsigned int NewHeight);
extern F_KeenGraphicsResizeRenderSwapchain KeenGraphicsResizeRenderSwapchain;

//.text:0122FCF0 rfg.exe:$3BFCF0 #3BF0F0 <gameseq_get_state>
using F_GameseqGetState = GameState(__cdecl*)();
extern F_GameseqGetState GameseqGetState;

//.text:01270C50 rfg.exe:$310C50 #310050 <object::enable_object_outline>
using F_ObjectEnableOutline = void(__thiscall*)(Object* This, int Layer);
extern F_ObjectEnableOutline ObjectEnableOutline;

//.text:01270C60 rfg.exe:$310C60 #310060 <object::disable_object_outline>
using F_ObjectDisableOutline = void(__thiscall*)(Object* This);
extern F_ObjectDisableOutline ObjectDisableOutline;

//.text:0158EE80 rfg.exe:$62EE80 #62E280 <human::enable_object_outline>
using F_HumanEnableOutline = void(__thiscall*)(Human* This, int Layer);
extern F_HumanEnableOutline HumanEnableOutline;

//.text:0158EF00 rfg.exe:$62EF00 #62E300 <human::disable_object_outline>
using F_HumanDisableOutline = void(__thiscall*)(Human* This);
extern F_HumanDisableOutline HumanDisableOutline;

//.text:01695390 rfg.exe:$735390 #734790 <target_outline_add_object>
using F_TargetOutlineAddObject = void(__cdecl*)(unsigned int Handle);
extern F_TargetOutlineAddObject TargetOutlineAddObject;

//.text:00D0A4F0 rfg.exe:$4DA4F0 #4D98F0 <ui_tool_tips_add_tip> //void __cdecl ui_tool_tips_add_tip(const char *name, const int delay_ms, const char *icon_image)
using F_ui_tool_tips_add_tip = void(__cdecl*)(const char* Name, const int DelayMs, const char* IconImage);
extern F_ui_tool_tips_add_tip UiToolTipsAddTip;

//.text:0093DDA0 rfg.exe:$10DDA0 #10D1A0 <rl_draw::tristrip_2d_begin>
using F_rl_draw_tristrip_2d_begin = void(__fastcall*)(void*, void*, rl_primitive_state*); //2nd arg is edx, needed for __thiscall functions.
extern F_rl_draw_tristrip_2d_begin rl_draw_tristrip_2d_begin;

//.text:00985BC0 rfg.exe:$155BC0 #154FC0 <rl_draw::string>
//void __thiscall rl_draw::string(rl_draw *this, float sx, float sy, const char *s, bool centered, int fontnum, rl_primitive_state *state)
using F_rl_draw_string = void(__fastcall*)(void* This, void* edx, float sx, float sy, const char* s, bool centered, int fontnum, rl_primitive_state* state); //2nd arg is edx, needed for __thiscall functions.
extern F_rl_draw_string rl_draw_string;

//.text:015C1690 rfg.exe:$3C1690 #3C0A90 <game_is_paused>
using F_is_game_paused = bool(__cdecl*)();
extern F_is_game_paused IsGamePaused;

//.text:01740AB0 rfg.exe:$540AB0 #53FEB0 <world::do_frame> //bool __thiscall world::do_frame(world *this, bool hard_load)
using F_world_do_frame = void(__fastcall*)(World* This, void* edx, bool HardLoad); //2nd arg is edx, needed for __thiscall functions.
extern F_world_do_frame world_do_frame;

//.text:0171C8A0 rfg.exe:$51C8A0 #51BCA0 <world::get_object_name> //const char *__thiscall world::get_object_name(world *this, object *objp)
using F_world_get_object_name = const char*(__fastcall*)(World* This, void* edx, Object* ObjectPtr); //2nd arg is edx, needed for __thiscall functions.
extern F_world_get_object_name world_get_object_name;



//.text:0171D9F0 rfg.exe:$51D9F0 #51CDF0 <world::get_object_zone_by_index> //obj_zone *__thiscall world::get_object_zone_by_index(world *this, int index)
using F_world_get_object_zone_by_index = obj_zone*(__fastcall*)(World* This, void* edx, int Index); //2nd arg is edx, needed for __thiscall functions.
extern F_world_get_object_zone_by_index world_get_object_zone_by_index;
//.text:0171DA20 rfg.exe:$51DA20 #51CE20 <world::get_object_zone_by_grid_id> //obj_zone *__thiscall world::get_object_zone_by_grid_id(world *this, unsigned __int16 id)
using F_world_get_object_zone_by_grid_id = obj_zone*(__fastcall*)(World* This, void* edx, unsigned __int16 id); //2nd arg is edx, needed for __thiscall functions.
extern F_world_get_object_zone_by_grid_id world_get_object_zone_by_grid_id;

//.text:010DD610 rfg.exe:$35D610 #35CA10 <gsm_get_alert_level> //gfm_alert_levels __cdecl gsm_get_alert_level()
using F_gsm_get_alert_level = gfm_alert_levels(__cdecl*)();
extern F_gsm_get_alert_level gsm_get_alert_level;
//.text:0112A740 rfg.exe:$3AA740 #3A9B40 <gsm_set_alert_level> //void __cdecl gsm_set_alert_level(gfm_alert_levels new_alert_level)
using F_gsm_set_alert_level = void(__cdecl*)(gfm_alert_levels new_alert_level);
extern F_gsm_set_alert_level gsm_set_alert_level;

//.text:010DD630 rfg.exe:$35D630 #35CA30 <gsm_get_alert_value> //float __cdecl gsm_get_alert_value()
using F_gsm_get_alert_value = float(__cdecl*)();
extern F_gsm_get_alert_value gsm_get_alert_value;
//.text:011244B0 rfg.exe:$3A44B0 #3A38B0 <gsm_set_alert_value> //void __cdecl gsm_set_alert_value(float new_alert_value)
using F_gsm_set_alert_value = void(__cdecl*)(float new_alert_value);
extern F_gsm_set_alert_value gsm_set_alert_value;

//.text:010DD680 rfg.exe:$35D680 #35CA80 <gsm_get_alert_level_cap> //void __cdecl gsm_get_alert_level_cap(gfm_alert_levels *min, gfm_alert_levels *max)
using F_gsm_get_alert_level_cap = void(__cdecl*)(gfm_alert_levels* min, gfm_alert_levels* max);
extern F_gsm_get_alert_level_cap gsm_get_alert_level_cap;
//.text:0112A770 rfg.exe:$3AA770 #3A9B70 <gsm_set_alert_level_cap> //void __cdecl gsm_set_alert_level_cap(gfm_alert_levels min, gfm_alert_levels max)
using F_gsm_set_alert_level_cap = void(__cdecl*)(gfm_alert_levels min, gfm_alert_levels max);
extern F_gsm_set_alert_level_cap gsm_set_alert_level_cap;

//.text:01142960 rfg.exe:$3C2960 #3C1D60 <game_render_get_TOD_light> //rl_light *__cdecl fav::game_render_get_TOD_light()
using F_game_render_get_TOD_light = rl_light*(__cdecl*)();
extern F_game_render_get_TOD_light game_render_get_TOD_light;
//.text:01142930 rfg.exe:$3C2930 #3C1D30 <game_render_set_TOD_light> //void __cdecl fav::game_render_set_TOD_light(rl_light *light_p)
using F_game_render_set_TOD_light = void(__cdecl*)(rl_light* light_p);
extern F_game_render_set_TOD_light game_render_set_TOD_light;

//.text:01143000 rfg.exe:$3C3000 #3C2400 <game_render_get_tod_on_off_value> //void __cdecl fav::game_render_get_tod_on_off_value(float *val)
using F_game_render_get_tod_on_off_value = void(__cdecl*)(float* Value);
extern F_game_render_get_tod_on_off_value game_render_get_tod_on_off_value;
//.text:01142FF0 rfg.exe:$3C2FF0 #3C23F0 <game_render_set_tod_on_off_value> //void __cdecl fav::game_render_set_tod_on_off_value(float val)
using F_game_render_set_tod_on_off_value = void(__cdecl*)(float Value);
extern F_game_render_set_tod_on_off_value game_render_set_tod_on_off_value;

//.text:01142990 rfg.exe:$3C2990 #3C1D90 <game_render_set_TOD_light_color> //void __cdecl fav::game_render_set_TOD_light_color(rl_color_float *color)
using F_game_render_set_TOD_light_color = void(__cdecl*)(rl_color_float* color);
extern F_game_render_set_TOD_light_color game_render_set_TOD_light_color;

//.text:011415C0 rfg.exe:$3C15C0 #3C09C0 <game_clock_get_tod_partitioned> //game_clock_tod_partitioned __cdecl fav::game_clock_get_tod_partitioned()
using F_game_clock_get_tod_partitioned = game_clock_tod_partitioned(__cdecl*)();
extern F_game_clock_get_tod_partitioned game_clock_get_tod_partitioned;

//.text:011415E0 rfg.exe:$3C15E0 #3C09E0 <game_clock_get_time_of_day> //game_clock_time_of_day __cdecl fav::game_clock_get_time_of_day()
using F_game_clock_get_time_of_day = game_clock_time_of_day(__cdecl*)();
extern F_game_clock_get_time_of_day game_clock_get_time_of_day;
//.text:01141770 rfg.exe:$3C1770 #3C0B70 <game_clock_set_time> //void __cdecl fav::game_clock_set_time(int hours, int minutes, int seconds)
using F_game_clock_set_time = void(__cdecl*)(int hours, int minutes, int seconds);
extern F_game_clock_set_time game_clock_set_time;

//.text:0115FA10 rfg.exe:$3DFA10 #3DEE10 <game_time_of_day_get_skybox_tod_colors> //void __cdecl game_time_of_day_get_skybox_tod_colors(rl_color_float *colors)
using F_game_time_of_day_get_skybox_tod_colors = void(__cdecl*)(rl_color_float* Colors);
extern F_game_time_of_day_get_skybox_tod_colors game_time_of_day_get_skybox_tod_colors;
//.text:01145880 rfg.exe:$3C5880 #3C4C80 <game_time_of_day_get_weather_settings> //void __cdecl fav::game_time_of_day_get_weather_settings(vector4 *horizon_strengths, vector4 *overhead_strengths)
using F_game_time_of_day_get_weather_settings = void(__cdecl*)(vector4* horizon_strengths, vector4* overhead_strengths);
extern F_game_time_of_day_get_weather_settings game_time_of_day_get_weather_settings;
//.text:011458C0 rfg.exe:$3C58C0 #3C4CC0 <game_time_of_day_get_cloud_scroll_values> //void __cdecl fav::game_time_of_day_get_cloud_scroll_values(float *layer01_scroll, float *layer23_scroll)
using F_game_time_of_day_get_cloud_scroll_values = void(__cdecl*)(float* layer01_scroll, float* layer23_scroll);
extern F_game_time_of_day_get_cloud_scroll_values game_time_of_day_get_cloud_scroll_values;
//.text:011520C0 rfg.exe:$3D20C0 #3D14C0 <game_time_of_day_get_num_orbitals> //int __cdecl fav::game_time_of_day_get_num_orbitals()
using F_game_time_of_day_get_num_orbitals = int(__cdecl*)();
extern F_game_time_of_day_get_num_orbitals game_time_of_day_get_num_orbitals;
//.text:011631B0 rfg.exe:$3E31B0 #3E25B0 <game_time_of_day_get_cloud_lighting> //void __cdecl game_time_of_day_get_cloud_lighting(rl_color_float *horizon_front_ambient, rl_color_float *horizon_back_ambient, rl_color_float *overhead_front_ambient, rl_color_float *overhead_back_ambient, float *backlight_strength, float *backlight_power, vector *light_direction)
using F_game_time_of_day_get_cloud_lighting = void(__cdecl*)(rl_color_float* horizon_front_ambient, rl_color_float* horizon_back_ambient, rl_color_float* overhead_front_ambient, rl_color_float* overhead_back_ambient, float* backlight_strength, float* backlight_power, vector* light_direction);
extern F_game_time_of_day_get_cloud_lighting game_time_of_day_get_cloud_lighting;
//.text:01165400 rfg.exe:$3E5400 #3E4800 <game_time_of_day_get_orbital_params> //void __cdecl game_time_of_day_get_orbital_params(int idx, rl_skybox_orbital_params *params)
using F_game_time_of_day_get_orbital_params = void(__cdecl*)(int Index, rl_skybox_orbital_params* Params);
extern F_game_time_of_day_get_orbital_params game_time_of_day_get_orbital_params;

//.text:011EC4D0 rfg.exe:$46C4D0 #46B8D0 <district_from_name> //district *__cdecl district_from_name(const char *name)
using F_district_from_name = district*(__cdecl*)(const char *name);
extern F_district_from_name district_from_name;

//.text:0129D950 rfg.exe:$51D950 #51CD50 <world::get_world_zone_by_index> //world_zone *__thiscall world::get_world_zone_by_index(world *this, int index)
using F_get_world_zone_by_index = world_zone*(__fastcall*)(World* This, void* edx, int Index); //2nd arg is edx, needed for __thiscall functions.
extern F_get_world_zone_by_index get_world_zone_by_index;
//.text:0129D970 rfg.exe:$51D970 #51CD70 <world::get_world_zone_by_grid_id> //world_zone *__thiscall world::get_world_zone_by_grid_id(world *this, unsigned __int16 id)
using F_get_world_zone_by_grid_id = world_zone*(__fastcall*)(World* This, void* edx, unsigned __int16 id); //2nd arg is edx, needed for __thiscall functions.
extern F_get_world_zone_by_grid_id get_world_zone_by_grid_id;
//.text:0129D9A0 rfg.exe:$51D9A0 #51CDA0 <world::get_world_zone_by_name> //world_zone *__thiscall world::get_world_zone_by_name(world *this, const char *name)
using F_get_world_zone_by_name = world_zone*(__fastcall*)(World* This, void* edx, const char* name); //2nd arg is edx, needed for __thiscall functions.
extern F_get_world_zone_by_name get_world_zone_by_name;
//.text:012A3BA0 rfg.exe:$523BA0 #522FA0 <world::get_world_zone_by_pos> //world_zone *__thiscall world::get_world_zone_by_pos(world *this, vector *pos)
using F_get_world_zone_by_pos = world_zone*(__fastcall*)(World* This, void* edx, vector* Position); //2nd arg is edx, needed for __thiscall functions.
extern F_get_world_zone_by_pos get_world_zone_by_pos;
//.text:012A3C00 rfg.exe:$523C00 #523000 <world::get_world_zone_by_object_handle> //world_zone *__thiscall world::get_world_zone_by_object_handle(world *this, unsigned int handle)
using F_get_world_zone_by_object_handle = world_zone*(__fastcall*)(World* This, void* edx, unsigned int handle); //2nd arg is edx, needed for __thiscall functions.
extern F_get_world_zone_by_object_handle get_world_zone_by_object_handle;

//.text:010924D0 rfg.exe:$3124D0 #3118D0 <rfg_dyn_apply_point_impulse> //void __usercall rfg_dyn_apply_point_impulse(int havok_handle, vector *impulse@<eax>, vector *impulse_pos, float mass@<xmm10>)
using F_rfg_dyn_apply_point_impulse = void(__cdecl*)(int havok_handle, vector* impulse, vector* impulse_pos, float mass); ///Figure out the proper calling convention...
extern F_rfg_dyn_apply_point_impulse rfg_dyn_apply_point_impulse;
//.text:01094820 rfg.exe:$314820 #313C20 <rfg_dyn_repair_sphere> //void __cdecl rfg_dyn_repair_sphere(vector *pos, const float radius, const int duration, human *hp)
using F_rfg_dyn_repair_sphere = void(__cdecl*)(vector* pos, float radius, int duration, Human* hp);
extern F_rfg_dyn_repair_sphere rfg_dyn_repair_sphere;

//.text:00F78A10 rfg.exe:$1F8A10 #1F7E10 <world::object_cast<human>> //human *__thiscall world::object_cast<human>(world *this, object *objp)
//.text:00F78C10 rfg.exe:$1F8C10 #1F8010 <world::object_cast<human>> //human *__thiscall world::object_cast<human>(world *this, object *objp)



extern Human* CastObjectToHuman(Object* ObjectPtr);
extern Player* CastObjectToPlayer(Object* ObjectPtr);
extern obj_zone* CastObjectToObjZone(Object* ObjectPtr);
extern district* CastObjectToDistrict(Object* ObjectPtr);



/*Many of the funcs below were defined above when the code style was different.*/

//.text:00679AC0 rfg.exe:$2C9AC0 #2C8EC0 <camera_start_first_person>
//.text:00679B60 rfg.exe:$2C9B60 #2C8F60 <camera_stop_first_person>

//.text:00694E30 rfg.exe:$2E4E30 #2E4230 <xray_effect_start>
//.text:00694E50 rfg.exe:$2E4E50 #2E4250 <xray_effect_stop>

//.text:00E18AC0 rfg.exe:$168AC0 #167EC0 <key_down>
//.text:01072F10 rfg.exe:$3C2F10 #3C2310 <game_render_set_bloom_exposure_factor>

//.text:0107F210 rfg.exe:$3CF210 #3CE610 <__Game_render_stats::__Game_render_stats>
//.text:01072BB0 rfg.exe:$3C2BB0 #3C1FB0 <game_render_set_hdr_state>

//.text:01232500 rfg.exe:$3C2500 #3C1900 <game_render_2d_text>
//.text:01311C00 rfg.exe:$4A1C00 #4A1000 <ui_add_debug_text>

//.text:00F28B40 rfg.exe:$B8B40 #B7F40 <rl_camera::get_depth_of_field_enabled>
//.text:01231820 rfg.exe:$3C1820 #3C0C20 <rl_camera::set_depth_of_field_enabled>

//.text:00FA53D0 rfg.exe:$4153D0 #4147D0 <character_controller::set_pos>

//.text:00EEF7F0 rfg.exe:$43F7F0 #43EBF0 <fog_of_war_clear>






///POSSIBLE DUPLICATES BELOW

//.text:0075BA80 rfg.exe:$55BA80 #55AE80 <debug_spew_projectile> //Did nothing
//.text:00755EB0 rfg.exe:$555EB0 #5552B0 <debug_spew_game_io>
//.text:01267B60 rfg.exe:$B7B60 #B6F60 <rl_render_lib::get_metrics>

//.text:00684760 rfg.exe:$484760 #483B60 <interface_debug_mode_activate> //Did nothing
//.text:009F48D0 rfg.exe:$7F48D0 #7F3CD0 <keen::debug::writeToLogFile>
//.text:00641A90 rfg.exe:$441A90 #440E90 <hud_hide>
//.text:00641AC0 rfg.exe:$441AC0 #440EC0 <hud_is_hidden>
//.text:00642D80 rfg.exe:$442D80 #442180 <hud_display_distance>
//.text:0038CDB0 rfg.exe:$18CDB0 #18C1B0 <console_enable_chat_window>

//.text:003CD150 rfg.exe:$1CD150 #1CC550 <console_init>
//.text:0038CAC0 rfg.exe:$18CAC0 #18BEC0 <console_activate>
//.text:003AF950 rfg.exe:$1AF950 #1AED50 <console_deactivate>

//.text:003AF470 rfg.exe:$1AF470 #1AE870 <console_printf>
//.text:003C4B50 rfg.exe:$1C4B50 #1C3F50 <console_display_help>
//.text:003C54B0 rfg.exe:$1C54B0 #1C48B0 <console_command_enable>
//.text:003C5000 rfg.exe:$1C5000 #1C4400 <console_do_command>

//.text:004CCB90 rfg.exe:$2CCB90 #2CBF90 <camera_start_satellite_mode> //Caused crash
//.text:00469C80 rfg.exe:$2C9C80 #2C9080 <camera_first_person_pre_process>
//.text:004C9AC0 rfg.exe:$2C9AC0 #2C8EC0 <camera_start_first_person> //Set at masons feet, perhaps could work with some edits
//.text:004CF0C0 rfg.exe:$2CF0C0 #2CE4C0 <camera_start_third_person> //Works
//.text:004D3FE0 rfg.exe:$2D3FE0 #2D33E0 <camera_start_lookaround_mode> //Third person viewed in, not very useful
//.text:77121812 kernelbase.dll:$111812 #110C12 //Camera_first_person_offset. Not sure if this is a function or what

//.text:00560A90 rfg.exe:$3C0A90 #3BFE90 <game_print_screen>
//.text:004705D0 rfg.exe:$2D05D0 #2CF9D0 <camera_set_view_player>
//.text:004645B0 rfg.exe:$2C45B0 #2C39B0 <camera_free_system_init>
//.text:00475610 rfg.exe:$2D5610 #2D4A10 <camera_free_mode_init>
//.text:00464DE0 rfg.exe:$2C4DE0 #2C41E0 <camera_free_render_debug>
//.text:0034F4B0 rfg.exe:$1AF4B0 #1AE8B0 <console_chat_printf>
//.text:0056F220 rfg.exe:$3CF220 #3CE620 <unused_dcf_r_show_mem_usage>
//.text:004B4C40 rfg.exe:$314C40 #314040 <rfg_dyn_get_active_destruction_frame>
//.text:004B4C30 rfg.exe:$314C30 #314030 <rfg_dyn_reset_destruction_frame>
//.text:004B3750 rfg.exe:$313750 #312B50 <rfg_dyn_system_shutdown>
//.text:001F8AE0 rfg.exe:$58AE0 #57EE0 <rl_screen_info::get_screen_width>
//.text:0032CAD0 rfg.exe:$18CAD0 #18BED0 <console_is_active>
//.text:01898690 rfg.exe:$6E8690 #6E7A90 <profile_dump_info>

//.text:01034FE0 rfg.exe:$64FE0 #643E0 <vint_render_text>


//.text:01390450 rfg.exe:$3C0450 #3BF850 <rl_scene::set_time_of_day_value>

//.text:006866E0 rfg.exe:$2D66E0 #2D5AE0 <camera_move>

//.text:0068D250 rfg.exe:$2DD250 #2DC650 <camera_third_person_process>

//.text:00679AC0 rfg.exe:$2C9AC0 #2C8EC0 <camera_start_first_person>
//.text:00679B60 rfg.exe:$2C9B60 #2C8F60 <camera_stop_first_person>
//.text:00679C80 rfg.exe:$2C9C80 #2C9080 <camera_first_person_pre_process>
//.text:0067AA00 rfg.exe:$2CAA00 #2C9E00 <camera_first_person_process>

//.text:0067CB40 rfg.exe:$2CCB40 #2CBF40 <camera_stop_satellite_mode_internal>
//.text:0067CB90 rfg.exe:$2CCB90 #2CBF90 <camera_start_satellite_mode>
//.text:0067CDB0 rfg.exe:$2CCDB0 #2CC1B0 <camera_stop_satellite_mode>
//.text:0068A650 rfg.exe:$2DA650 #2D9A50 <camera_satellite_get_base_height>
//.text:0068A7A0 rfg.exe:$2DA7A0 #2D9BA0 <camera_satellite_process>

//.text:006809B0 rfg.exe:$2D09B0 #2CFDB0 <camera_start_slew_mode>
//.text:006809C0 rfg.exe:$2D09C0 #2CFDC0 <camera_stop_slew_mode>

//.text:006809D0 rfg.exe:$2D09D0 #2CFDD0 <camera_start_cursor_mode>
//.text:006809E0 rfg.exe:$2D09E0 #2CFDE0 <camera_stop_cursor_mode>

//.text:006809F0 rfg.exe:$2D09F0 #2CFDF0 <camera_start_dumb_mode>
//.text:00680A00 rfg.exe:$2D0A00 #2CFE00 <camera_stop_dumb_mode>

//.text:00680A10 rfg.exe:$2D0A10 #2CFE10 <camera_start_turret_mode>
//.text:00680B00 rfg.exe:$2D0B00 #2CFF00 <camera_stop_turret_mode>

//.text:00772C60 rfg.exe:$3C2C60 #3C2060 <game_render_get_fog_enabled>
//.text:00772C70 rfg.exe:$3C2C70 #3C2070 <game_render_set_fog_enabled>

//.text:00694E30 rfg.exe:$2E4E30 #2E4230 <xray_effect_start>
//.text:00694E50 rfg.exe:$2E4E50 #2E4250 <xray_effect_stop>
//.text:00694E70 rfg.exe:$2E4E70 #2E4270 <xray_effect_is_enabled>

//.text:00E18AC0 rfg.exe:$168AC0 #167EC0 <key_down>

//.text:01072F10 rfg.exe:$3C2F10 #3C2310 <game_render_set_bloom_exposure_factor>

//.text:01232500 rfg.exe:$3C2500 #3C1900 <game_render_2d_text>
//.text:01311C00 rfg.exe:$4A1C00 #4A1000 <ui_add_debug_text>

//.text:00F28B40 rfg.exe:$B8B40 #B7F40 <rl_camera::get_depth_of_field_enabled>
//.text:01231820 rfg.exe:$3C1820 #3C0C20 <rl_camera::set_depth_of_field_enabled>

//.text:00FA53D0 rfg.exe:$4153D0 #4147D0 <character_controller::set_pos>

//.text:00EEF7F0 rfg.exe:$43F7F0 #43EBF0 <fog_of_war_clear>

//.text:005B09C0 rfg.exe:$2D09C0 #2CFDC0 <camera_stop_slew_mode>
//.text:005A9AC0 rfg.exe:$2C9AC0 #2C8EC0 <camera_start_first_person>


//void __thiscall rl_camera::render_begin(rl_camera *this, rl_renderer *renderer)
//.text:01027660 rfg.exe:$137660 #136A60 <rl_camera::render_begin>
using F_rl_camera_render_begin = void(__fastcall*)(rl_camera* This, void* edx, void* Renderer); //2nd arg is edx, needed for __thiscall functions.
extern F_rl_camera_render_begin rl_camera_render_begin;

//.text:012B2C40 rfg.exe:$3C2C40 #3C2040 <game_render_set_far_clip_distance> //void __cdecl fav::game_render_set_far_clip_distance(float distance)
using F_game_render_set_far_clip_distance = void(__cdecl*)(float Distance);
extern F_game_render_set_far_clip_distance game_render_set_far_clip_distance;

//.text:012B2C50 rfg.exe:$3C2C50 #3C2050 <game_render_get_far_clip_distance> //float __cdecl fav::game_render_get_far_clip_distance()
using F_game_render_get_far_clip_distance = float(__cdecl*)();
extern F_game_render_get_far_clip_distance game_render_get_far_clip_distance;

//.text:012B2920 rfg.exe:$3C2920 #3C1D20 <game_render_get_main_scene> //rl_scene *__cdecl fav::game_render_get_main_scene()
using F_game_render_get_main_scene = rl_scene*(__cdecl*)();
extern F_game_render_get_main_scene game_render_get_main_scene;

//hkpStepResult __thiscall fav::hkpWorld::stepDeltaTime(hkpWorld *this, float physicsDeltaTime) //0x9E1A70
using F_hkpWorld_stepDeltaTime = void(__fastcall*)(hkpWorld* This, void* edx, float PhysicsDeltaTime); //2nd arg is edx, needed for __thiscall functions.
extern F_hkpWorld_stepDeltaTime hkpWorld_stepDeltaTime;

//.text:0117A880 rfg.exe:$5A880 #59C80 <keen::rfg::Application::updateTime> //void __thiscall fav::keen::rfg::Application::updateTime(keen::rfg::Application *this, float timeStep)
using F_ApplicationUpdateTime = void(__fastcall*)(void* This, void* edx, float TimeStep); //2nd arg is edx, needed for __thiscall functions.
extern F_ApplicationUpdateTime ApplicationUpdateTime;

//.text:0152D040 rfg.exe:$40D040 #40C440 <hkpWorld::getGravity> //hkVector4f *__thiscall fav::hkpWorld::getGravity(hkpWorld* this)
using F_hkpWorldGetGravity = hkVector4f*(__fastcall*)(hkpWorld* This, void* edx); //2nd arg is edx, needed for __thiscall functions.
extern F_hkpWorldGetGravity hkpWorldGetGravity;

//.text:01B00E20 rfg.exe:$9E0E20 #9E0220 <hkpWorld::setGravity> //void __thiscall fav::hkpWorld::setGravity(hkpWorld* this, hkVector4f* gravity)
using F_hkpWorldSetGravity = void(__fastcall* )(hkpWorld* This, void* edx, hkVector4f* Gravity); //2nd arg is edx, needed for __thiscall functions.
extern F_hkpWorldSetGravity hkpWorldSetGravity;

//.text:014306A0 rfg.exe:$3106A0 #30FAA0 <hkVector4f::set> //void __thiscall hkVector4f::set(hkVector4f *this, float a, float b, float c, float d)

//.text:00C720F0 rfg.exe:$620F0 #614F0 <vint_lua_get_state> //lua_State *__cdecl vint_lua_get_state()
using F_vint_lua_get_state = lua_State*(__cdecl*)();
extern F_vint_lua_get_state VintGetLuaState;

//.text:0143FD20 rfg.exe:$82FD20 #82F120 <lua_dobuffer> //int __cdecl lua_dobuffer(lua_State *L, const char *buff, unsigned int size, const char *name)
using F_lua_dobuffer = int(__cdecl*)(lua_State *L, const char *buff, unsigned int size, const char *name);
extern F_lua_dobuffer LuaDoBuffer;

//.text:0125E870 rfg.exe:$40E870 #40DC70 <havok_body_get_pointer> //hkpRigidBody *__cdecl havok_body_get_pointer(unsigned int handle)
using F_havok_body_get_pointer = hkpRigidBody*(__cdecl*)(unsigned int handle);
extern F_havok_body_get_pointer HavokBodyGetPointer;

//.text:012677A0 rfg.exe:$4177A0 #416BA0 <havok_body_apply_linear_impulse> //void __cdecl havok_body_apply_linear_impulse(hkpRigidBody *rb, vector *linear_impulse)
using F_havok_body_apply_linear_impulse_A = void(__cdecl*)(hkpRigidBody* rb, vector* linear_impulse);
extern F_havok_body_apply_linear_impulse_A HavokBodyApplyLinearImpulseA;

//.text:01273C20 rfg.exe:$423C20 #423020 <havok_body_apply_linear_impulse> //void __cdecl havok_body_apply_linear_impulse(unsigned int handle, vector *linear_impulse)
using F_havok_body_apply_linear_impulse_B = void(__cdecl*)(uint handle, vector* linear_impulse);
extern F_havok_body_apply_linear_impulse_B HavokBodyApplyLinearImpulseB;

//.text:0181DD00 rfg.exe:$86DD00 #86D100 <keen::graphics::beginFrame> //keen::GraphicsCommandBuffer *__cdecl keen::graphics::beginFrame(keen::GraphicsSystem *pGraphicsSystem, keen::RenderSwapChain *pSwapChain)
using F_keen_graphics_beginFrame = keen::GraphicsCommandBuffer*(__cdecl*)(keen::GraphicsSystem* pGraphicsSystem, keen::RenderSwapChain* pSwapChain);
extern F_keen_graphics_beginFrame KeenGraphicsBeginFrame;