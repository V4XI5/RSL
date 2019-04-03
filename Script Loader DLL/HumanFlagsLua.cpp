#include "HumanFlagsLua.h"
#include "Functions.h"

void Lua::BindHumanFlags(sol::state & LuaState)
{
	auto RfgTable = LuaState["rfg"].get_or_create<sol::table>();
/*
	RfgTable.new_usertype<HumanFlags>
	(
		"HumanFlags",
		"new", sol::constructors<HumanFlags(), HumanFlags(const HumanFlags&)>(),
		"BoredHeadtrackDisabled", sol::property(itsy_bitsy::read<HumanFlags, 0>, itsy_bitsy::write<HumanFlags, 0>), //int32 - 1
		"Hidden", sol::property(itsy_bitsy::read<HumanFlags, 1>, itsy_bitsy::write<HumanFlags, 1>), //int32 - 1
		"CapSpeed", sol::property(itsy_bitsy::read<HumanFlags, 2>, itsy_bitsy::write<HumanFlags, 2>), //int32 - 1
		"WasRendered", sol::property(itsy_bitsy::read<HumanFlags, 3>, itsy_bitsy::write<HumanFlags, 3>), //int32 - 1
		"LockedController", sol::property(itsy_bitsy::read<HumanFlags, 4>, itsy_bitsy::write<HumanFlags, 4>), //int32 - 1
		"Invulnerable", sol::property(itsy_bitsy::read<HumanFlags, 5>, itsy_bitsy::write<HumanFlags, 5>), //int32 - 1
		"MissionInvulnerable", sol::property(itsy_bitsy::read<HumanFlags, 6>, itsy_bitsy::write<HumanFlags, 6>), //int32 - 1
		"NoDamage", sol::property(itsy_bitsy::read<HumanFlags, 7>, itsy_bitsy::write<HumanFlags, 7>), //int32 - 1
		"ActivityEngage", sol::property(itsy_bitsy::read<HumanFlags, 8>, itsy_bitsy::write<HumanFlags, 8>), //int32 - 1
		"ConsideredArmed", sol::property(itsy_bitsy::read<HumanFlags, 9>, itsy_bitsy::write<HumanFlags, 9>), //int32 - 1
		"RiotShield", sol::property(itsy_bitsy::read<HumanFlags, 10>, itsy_bitsy::write<HumanFlags, 10>), //int32 - 1
		"SafehouseVIP", sol::property(itsy_bitsy::read<HumanFlags, 11>, itsy_bitsy::write<HumanFlags, 11>), //int32 - 1
		"RadioOperator", sol::property(itsy_bitsy::read<HumanFlags, 12>, itsy_bitsy::write<HumanFlags, 12>), //int32 - 1
		"ActivityRaidRequired", sol::property(itsy_bitsy::read<HumanFlags, 13>, itsy_bitsy::write<HumanFlags, 13>), //int32 - 1
		"ActivityRaidOptional", sol::property(itsy_bitsy::read<HumanFlags, 14>, itsy_bitsy::write<HumanFlags, 14>), //int32 - 1
		"ActivateHouseArrestHostage", sol::property(itsy_bitsy::read<HumanFlags, 15>, itsy_bitsy::write<HumanFlags, 15>), //int32 - 1
		"RaidIntroductionLines", sol::property(itsy_bitsy::read<HumanFlags, 16>, itsy_bitsy::write<HumanFlags, 16>), //int32 - 1
		"MinerPersonaLines", sol::property(itsy_bitsy::read<HumanFlags, 17>, itsy_bitsy::write<HumanFlags, 17>), //int32 - 1
		"DamagedByPlayer", sol::property(itsy_bitsy::read<HumanFlags, 18>, itsy_bitsy::write<HumanFlags, 18>), //int32 - 1
		"AiIgnore", sol::property(itsy_bitsy::read<HumanFlags, 19>, itsy_bitsy::write<HumanFlags, 19>), //int32 - 1
		"CastsShadows", sol::property(itsy_bitsy::read<HumanFlags, 20>, itsy_bitsy::write<HumanFlags, 20>),//int32 - 1
		"CastsDropShadows", sol::property(itsy_bitsy::read<HumanFlags, 21>, itsy_bitsy::write<HumanFlags, 21>), //int32 - 1
		"IsTurning", sol::property(itsy_bitsy::read<HumanFlags, 22>, itsy_bitsy::write<HumanFlags, 22>), //int32 - 1 
		"IsFalling", sol::property(itsy_bitsy::read<HumanFlags, 23>, itsy_bitsy::write<HumanFlags, 23>), //int32 - 1 
		"DontDeformBones", sol::property(itsy_bitsy::read<HumanFlags, 24>, itsy_bitsy::write<HumanFlags, 24>), //int32 - 1 
		"DontLodBones", sol::property(itsy_bitsy::read<HumanFlags, 25>, itsy_bitsy::write<HumanFlags, 25>), //int32 - 1 
		"PlayingEquipAnim", sol::property(itsy_bitsy::read<HumanFlags, 26>, itsy_bitsy::write<HumanFlags, 26>), //int32 - 1 
		"PlayingUnequipAnim", sol::property(itsy_bitsy::read<HumanFlags, 27>, itsy_bitsy::write<HumanFlags, 27>), //int32 - 1 
		"DoInstantEquip", sol::property(itsy_bitsy::read<HumanFlags, 28>, itsy_bitsy::write<HumanFlags, 28>), //int32 - 1 
		"AnimDirectBlend", sol::property(itsy_bitsy::read<HumanFlags, 29>, itsy_bitsy::write<HumanFlags, 29>), //int32 - 1 
		"StartJump", sol::property(itsy_bitsy::read<HumanFlags, 30>, itsy_bitsy::write<HumanFlags, 30>), //int32 - 1 
		"SuperJump", sol::property(itsy_bitsy::read<HumanFlags, 31>, itsy_bitsy::write<HumanFlags, 31>), //int32 - 1 
		"ProcessedThisFrame", sol::property(itsy_bitsy::read<HumanFlags, 32>, itsy_bitsy::write<HumanFlags, 32>), //int32 - 1 
		"SilentVehicleStart", sol::property(itsy_bitsy::read<HumanFlags, 33>, itsy_bitsy::write<HumanFlags, 33>), //int32 - 1 
		"SupressFleeOnVehicleExit", sol::property(itsy_bitsy::read<HumanFlags, 34>, itsy_bitsy::write<HumanFlags, 34>), //int32 - 1 
		"DeathFunctionDone", sol::property(itsy_bitsy::read<HumanFlags, 35>, itsy_bitsy::write<HumanFlags, 35>), //int32 - 1 
		"FadingIn", sol::property(itsy_bitsy::read<HumanFlags, 36>, itsy_bitsy::write<HumanFlags, 36>), //int32 - 1 
		"FadingOut", sol::property(itsy_bitsy::read<HumanFlags, 37>, itsy_bitsy::write<HumanFlags, 37>), //int32 - 1 
		"FadingOutFromNano", sol::property(itsy_bitsy::read<HumanFlags, 38>, itsy_bitsy::write<HumanFlags, 38>), //int32 - 1 
		"IsNanoEffectCurrentlyApplied", sol::property(itsy_bitsy::read<HumanFlags, 39>, itsy_bitsy::write<HumanFlags, 39>), //int32 - 1 
		"OnFire", sol::property(itsy_bitsy::read<HumanFlags, 40>, itsy_bitsy::write<HumanFlags, 40>), //int32 - 1 
		"DroppedCash", sol::property(itsy_bitsy::read<HumanFlags, 41>, itsy_bitsy::write<HumanFlags, 41>), //int32 - 1 
		"OnMover", sol::property(itsy_bitsy::read<HumanFlags, 42>, itsy_bitsy::write<HumanFlags, 42>), //int32 - 1 
		"RecalculateAtNode", sol::property(itsy_bitsy::read<HumanFlags, 43>, itsy_bitsy::write<HumanFlags, 43>), //int32 - 1 
		"SpinebendingDone", sol::property(itsy_bitsy::read<HumanFlags, 44>, itsy_bitsy::write<HumanFlags, 44>), //int32 - 1 
		"LastDestinationInRepulsor", sol::property(itsy_bitsy::read<HumanFlags, 45>, itsy_bitsy::write<HumanFlags, 45>), //int32 - 1 
		"JumpingFromBuilding", sol::property(itsy_bitsy::read<HumanFlags, 46>, itsy_bitsy::write<HumanFlags, 46>), //int32 - 1 
		"IsOnLadder", sol::property(itsy_bitsy::read<HumanFlags, 47>, itsy_bitsy::write<HumanFlags, 47>), //int32 - 1 
		"LadderForceSlide", sol::property(itsy_bitsy::read<HumanFlags, 48>, itsy_bitsy::write<HumanFlags, 48>), //int32 - 1 
		"LadderForceExit", sol::property(itsy_bitsy::read<HumanFlags, 49>, itsy_bitsy::write<HumanFlags, 49>), //int32 - 1 
		"LadderReEquipWeapon", sol::property(itsy_bitsy::read<HumanFlags, 50>, itsy_bitsy::write<HumanFlags, 50>), //int32 - 1 
		"AllowFlyingEquips", sol::property(itsy_bitsy::read<HumanFlags, 51>, itsy_bitsy::write<HumanFlags, 51>), //int32 - 1 
		"CorpseSpotted", sol::property(itsy_bitsy::read<HumanFlags, 52>, itsy_bitsy::write<HumanFlags, 52>), //int32 - 1 
		"CorpseSpottedByEnemy", sol::property(itsy_bitsy::read<HumanFlags, 53>, itsy_bitsy::write<HumanFlags, 53>), //int32 - 1 
		"DeathReported", sol::property(itsy_bitsy::read<HumanFlags, 54>, itsy_bitsy::write<HumanFlags, 54>), //int32 - 1 
		"RaidDeathAck", sol::property(itsy_bitsy::read<HumanFlags, 55>, itsy_bitsy::write<HumanFlags, 55>), //int32 - 1 
		"AnchorOrient", sol::property(itsy_bitsy::read<HumanFlags, 56>, itsy_bitsy::write<HumanFlags, 56>), //int32 - 1 
		"BonesTransformedThisFrame", sol::property(itsy_bitsy::read<HumanFlags, 57>, itsy_bitsy::write<HumanFlags, 57>), //int32 - 1 
		"UseCurrentVelocity", sol::property(itsy_bitsy::read<HumanFlags, 58>, itsy_bitsy::write<HumanFlags, 58>), //int32 - 1 
		"UseAsFinalVelocity", sol::property(itsy_bitsy::read<HumanFlags, 59>, itsy_bitsy::write<HumanFlags, 59>), //int32 - 1 
		"AimAtPos", sol::property(itsy_bitsy::read<HumanFlags, 60>, itsy_bitsy::write<HumanFlags, 60>), //int32 - 1 
		"BlockForcedMovement", sol::property(itsy_bitsy::read<HumanFlags, 61>, itsy_bitsy::write<HumanFlags, 61>), //int32 - 1 
		"CancellingMeleeAttack", sol::property(itsy_bitsy::read<HumanFlags, 62>, itsy_bitsy::write<HumanFlags, 62>), //int32 - 1 
		"DoContinuousMeleeDamage", sol::property(itsy_bitsy::read<HumanFlags, 63>, itsy_bitsy::write<HumanFlags, 63>), //int32 - 1 
		"InAirMelee", sol::property(itsy_bitsy::read<HumanFlags, 64>, itsy_bitsy::write<HumanFlags, 64>), //int32 - 1 
		"CantHitWithMelee", sol::property(itsy_bitsy::read<HumanFlags, 65>, itsy_bitsy::write<HumanFlags, 65>), //int32 - 1 
		"InvulnerableToDebris", sol::property(itsy_bitsy::read<HumanFlags, 66>, itsy_bitsy::write<HumanFlags, 66>), //int32 - 1 
		"OverrideDefaultAnimState", sol::property(itsy_bitsy::read<HumanFlags, 67>, itsy_bitsy::write<HumanFlags, 67>), //int32 - 1 
		"OverrideDefaultFireAnim", sol::property(itsy_bitsy::read<HumanFlags, 68>, itsy_bitsy::write<HumanFlags, 68>), //int32 - 1 
		"MovingAndTransitioningStates", sol::property(itsy_bitsy::read<HumanFlags, 69>, itsy_bitsy::write<HumanFlags, 69>), //int32 - 1 
		"CheckForCover", sol::property(itsy_bitsy::read<HumanFlags, 70>, itsy_bitsy::write<HumanFlags, 70>), //int32 - 1 
		"JumpTakeOff", sol::property(itsy_bitsy::read<HumanFlags, 71>, itsy_bitsy::write<HumanFlags, 71>), //int32 - 1 
		"RotateInternalHeadingUpdated", sol::property(itsy_bitsy::read<HumanFlags, 72>, itsy_bitsy::write<HumanFlags, 72>), //int32 - 1 
		"CrouchCover", sol::property(itsy_bitsy::read<HumanFlags, 73>, itsy_bitsy::write<HumanFlags, 73>), //int32 - 1 
		"CoverCrouchHighOnly", sol::property(itsy_bitsy::read<HumanFlags, 74>, itsy_bitsy::write<HumanFlags, 74>), //int32 - 1 
		"CoverCrouchNoLean", sol::property(itsy_bitsy::read<HumanFlags, 75>, itsy_bitsy::write<HumanFlags, 75>), //int32 - 1 
		"SideFiring", sol::property(itsy_bitsy::read<HumanFlags, 76>, itsy_bitsy::write<HumanFlags, 76>), //int32 - 1 
		"SideFiringWalkBack", sol::property(itsy_bitsy::read<HumanFlags, 77>, itsy_bitsy::write<HumanFlags, 77>), //int32 - 1 
		"RagdollOnImpactAllCollisions", sol::property(itsy_bitsy::read<HumanFlags, 78>, itsy_bitsy::write<HumanFlags, 78>), //int32 - 1 
		"RagdollOnImpactUseRagdollPos", sol::property(itsy_bitsy::read<HumanFlags, 79>, itsy_bitsy::write<HumanFlags, 79>), //int32 - 1 
		"DiveCapsule", sol::property(itsy_bitsy::read<HumanFlags, 80>, itsy_bitsy::write<HumanFlags, 80>), //int32 - 1 
		"MaintainAmbientProps", sol::property(itsy_bitsy::read<HumanFlags, 81>, itsy_bitsy::write<HumanFlags, 81>), //int32 - 1 
		"LeaningDisabled", sol::property(itsy_bitsy::read<HumanFlags, 82>, itsy_bitsy::write<HumanFlags, 82>), //int32 - 1 
		"OverrideSterringHeadingOffset", sol::property(itsy_bitsy::read<HumanFlags, 83>, itsy_bitsy::write<HumanFlags, 83>), //int32 - 1 
		"PushesOtherHumans", sol::property(itsy_bitsy::read<HumanFlags, 84>, itsy_bitsy::write<HumanFlags, 84>), //int32 - 1 
		"PushesDebrisScripted", sol::property(itsy_bitsy::read<HumanFlags, 85>, itsy_bitsy::write<HumanFlags, 85>), //int32 - 1 
		"AllowSteepSlopes", sol::property(itsy_bitsy::read<HumanFlags, 86>, itsy_bitsy::write<HumanFlags, 86>), //int32 - 1 
		"ExternalForceApplied", sol::property(itsy_bitsy::read<HumanFlags, 87>, itsy_bitsy::write<HumanFlags, 87>), //int32 - 1 
		"RagdollShot", sol::property(itsy_bitsy::read<HumanFlags, 88>, itsy_bitsy::write<HumanFlags, 88>), //int32 - 1 
		"SavedPushesDebrisScripted", sol::property(itsy_bitsy::read<HumanFlags, 89>, itsy_bitsy::write<HumanFlags, 89>), //int32 - 1 
		"FilterHandleValid", sol::property(itsy_bitsy::read<HumanFlags, 90>, itsy_bitsy::write<HumanFlags, 90>), //int32 - 1 
		"JustGotUpFromRagdoll", sol::property(itsy_bitsy::read<HumanFlags, 91>, itsy_bitsy::write<HumanFlags, 91>), //int32 - 1 
		"DisablePathSmoothingForRequest", sol::property(itsy_bitsy::read<HumanFlags, 92>, itsy_bitsy::write<HumanFlags, 92>), //int32 - 1 
		"DisableAllPathSmoothing", sol::property(itsy_bitsy::read<HumanFlags, 93>, itsy_bitsy::write<HumanFlags, 93>), //int32 - 1 
		"InFetalPosition", sol::property(itsy_bitsy::read<HumanFlags, 94>, itsy_bitsy::write<HumanFlags, 94>), //int32 - 1 
		"DisallowVehicleExit", sol::property(itsy_bitsy::read<HumanFlags, 95>, itsy_bitsy::write<HumanFlags, 95>), //int32 - 1 
		"LimitedVehicleExit", sol::property(itsy_bitsy::read<HumanFlags, 96>, itsy_bitsy::write<HumanFlags, 96>), //int32 - 1 
		"DriverlessExitOnly", sol::property(itsy_bitsy::read<HumanFlags, 97>, itsy_bitsy::write<HumanFlags, 97>), //int32 - 1 
		"StuckInVehicle", sol::property(itsy_bitsy::read<HumanFlags, 98>, itsy_bitsy::write<HumanFlags, 98>), //int32 - 1 
		"ConvoyVehicleExit", sol::property(itsy_bitsy::read<HumanFlags, 99>, itsy_bitsy::write<HumanFlags, 99>), //int32 - 1 
		"DisallowVehicleEntry", sol::property(itsy_bitsy::read<HumanFlags, 100>, itsy_bitsy::write<HumanFlags, 100>), //int32 - 1 
		"DisallowVehicleDrive", sol::property(itsy_bitsy::read<HumanFlags, 101>, itsy_bitsy::write<HumanFlags, 101>), //int32 - 1 
		"AmbientEDF", sol::property(itsy_bitsy::read<HumanFlags, 102>, itsy_bitsy::write<HumanFlags, 102>), //int32 - 1 
		"BashedCharacterController", sol::property(itsy_bitsy::read<HumanFlags, 103>, itsy_bitsy::write<HumanFlags, 103>), //int32 - 1 
		"HeadLoaded", sol::property(itsy_bitsy::read<HumanFlags, 104>, itsy_bitsy::write<HumanFlags, 104>), //int32 - 1 
		"LodHeadLoaded", sol::property(itsy_bitsy::read<HumanFlags, 105>, itsy_bitsy::write<HumanFlags, 105>), //int32 - 1 
		"InVehicleInvisible", sol::property(itsy_bitsy::read<HumanFlags, 106>, itsy_bitsy::write<HumanFlags, 106>), //int32 - 1 
		"HighPriorityTarget", sol::property(itsy_bitsy::read<HumanFlags, 107>, itsy_bitsy::write<HumanFlags, 107>), //int32 - 1 
		"HealthChangeWasNegative", sol::property(itsy_bitsy::read<HumanFlags, 108>, itsy_bitsy::write<HumanFlags, 108>), //int32 - 1 
		"VoiceLinePlay2D", sol::property(itsy_bitsy::read<HumanFlags, 109>, itsy_bitsy::write<HumanFlags, 109>), //int32 - 1 
		"VoiceLinePainOnly", sol::property(itsy_bitsy::read<HumanFlags, 110>, itsy_bitsy::write<HumanFlags, 110>), //int32 - 1 
		"KilledByKillzone", sol::property(itsy_bitsy::read<HumanFlags, 111>, itsy_bitsy::write<HumanFlags, 111>), //int32 - 1 
		"FirstTimeStreamed", sol::property(itsy_bitsy::read<HumanFlags, 112>, itsy_bitsy::write<HumanFlags, 112>), //int32 - 1 
		"Tired", sol::property(itsy_bitsy::read<HumanFlags, 113>, itsy_bitsy::write<HumanFlags, 113>), //int32 - 1 
		"UseBigsteps", sol::property(itsy_bitsy::read<HumanFlags, 114>, itsy_bitsy::write<HumanFlags, 114>), //int32 - 1 
		"Stuck", sol::property(itsy_bitsy::read<HumanFlags, 115>, itsy_bitsy::write<HumanFlags, 115>), //int32 - 1 
		"LastPfFailed", sol::property(itsy_bitsy::read<HumanFlags, 116>, itsy_bitsy::write<HumanFlags, 116>), //int32 - 1 
		"ExtendedStuck", sol::property(itsy_bitsy::read<HumanFlags, 117>, itsy_bitsy::write<HumanFlags, 117>), //int32 - 1 
		"XrayVisible", sol::property(itsy_bitsy::read<HumanFlags, 118>, itsy_bitsy::write<HumanFlags, 118>), //int32 - 1 
		"WasGibbed", sol::property(itsy_bitsy::read<HumanFlags, 119>, itsy_bitsy::write<HumanFlags, 119>), //int32 - 1 
		"PreventRagdollSfx", sol::property(itsy_bitsy::read<HumanFlags, 120>, itsy_bitsy::write<HumanFlags, 120>), //int32 - 1 
		"AlwaysShowOnMinimap", sol::property(itsy_bitsy::read<HumanFlags, 121>, itsy_bitsy::write<HumanFlags, 121>), //int32 - 1 
		"UsedDeathBuffer", sol::property(itsy_bitsy::read<HumanFlags, 122>, itsy_bitsy::write<HumanFlags, 122>), //int32 - 1 
		"DoNotConvertToGuerrilla", sol::property(itsy_bitsy::read<HumanFlags, 123>, itsy_bitsy::write<HumanFlags, 123>), //int32 - 1 
		"DoNotPlayAmbientOrGreetLines", sol::property(itsy_bitsy::read<HumanFlags, 124>, itsy_bitsy::write<HumanFlags, 124>), //int32 - 1 
		"DisallowFlinchesAndRagdolls", sol::property(itsy_bitsy::read<HumanFlags, 125>, itsy_bitsy::write<HumanFlags, 125>), //int32 - 1 
		"OnlyUseActionNodes", sol::property(itsy_bitsy::read<HumanFlags, 126>, itsy_bitsy::write<HumanFlags, 126>), //int32 - 1 
		"ComplainWhenShot", sol::property(itsy_bitsy::read<HumanFlags, 127>, itsy_bitsy::write<HumanFlags, 127>) //int32 - 1 
	);*/
}