
/* Hooks.h/.cpp contain all the function hooks used by the script loader. These hooks are
 * created and enabled by the HookManager class. Hooks are a very powerful tool. They are 
 * basically some additional code stuck on front of a function. This lets you do things like
 * intercept their arguments and use them later, change them, or have events that occur when 
 * a specific function is called.
 */

#pragma once
#include "Functions.h"

#define DebugDrawTestEnabled false

namespace Hooks
{
    LRESULT __stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    extern LRESULT ProcessInput(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    extern void UpdateDebugDrawRenderInterfaceValues();

    typedef HRESULT(__stdcall* D3D11Present)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
    extern D3D11Present D3D11PresentFuncPtr;

    HRESULT __stdcall D3D11PresentHook(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
    bool __cdecl KeenGraphicsResizeRenderSwapchainHook(keen::RenderSwapChain* KeenSwapchain, unsigned int NewWidth, unsigned int NewHeight);
    keen::GraphicsCommandBuffer* __cdecl KeenGraphicsBeginFrameHook(keen::GraphicsSystem* pGraphicsSystem, keen::RenderSwapChain* pSwapChain);
    void __fastcall PlayerDoFrameHook(Player* PlayerPtr);
    void __cdecl ExplosionCreateHook(explosion_info* ExplosionInfo, void* Source, void* Owner, vector* Position, matrix* Orientation, vector* Direction, void* WeaponInfo, bool FromServer);
    extern bool UpdateD3D11Pointers;
    void __fastcall hkpWorld_stepDeltaTime_hook(hkpWorld* This, void* edx, float PhysicsDeltaTime);
    void __fastcall rl_camera_render_begin_hook(rl_camera* This, void* edx, rl_renderer* Renderer);
    void __fastcall ApplicationUpdateTimeHook(void* This, void* edx, float TimeStep);
    void __fastcall world_do_frame_hook(World* This, void* edx, bool HardLoad);
    int __cdecl LuaDoBufferHook(lua_State* L, const char* buff, unsigned int size, const char* name);
    void __fastcall ObjectUpdatePosAndOrientHook(Object* ObjectPtr, void* edx, vector* UpdatedPosition, matrix* UpdatedOrientation, bool SetHavokData);
    void __fastcall StreamGridDoFrameHook(stream_grid* This, void* edx, vector* StreamPos, bool SingleZoneMode);
    //vehicle* __cdecl CutsceneSpawnVehicleHook(vehicle_info* v_info, vector* pos, matrix* orient);
    bool __cdecl peg_load_wrapper_hook(const char* filename, unsigned int srid, char* cpu_preload, int cpu_size, char* gpu_preload, int gpu_size);


    /*Start of MP Detection Hooks*/
    bool __fastcall IsValidGameLinkLobbyKaikoHook(void* This);
    void __cdecl GameMusicMultiplayerStartHook();
    void __cdecl InitMultiplayerDataItemRespawnHook(void* Item);
    void __cdecl HudUiMultiplayerProcessHook(float DeltaTime);
    void __cdecl HudUiMultiplayerEnterHook();
    /*End of MP Detection Hooks*/
}

