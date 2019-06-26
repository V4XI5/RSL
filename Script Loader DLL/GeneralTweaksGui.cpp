#include "GeneralTweaksGui.h"

GeneralTweaksGui::GeneralTweaksGui(bool* OpenState_, std::string Title_)
{
	OpenState = OpenState_;
	Title = Title_;

	strcpy_s(CustomExplosionInfo.m_name, "Custom Explosion");
	CustomExplosionInfo.m_unique_id = 303; //A value of 255 caused explosions to cause no damage. Want to make sure it's actually unique to avoid issues.
	CustomExplosionInfo.m_name_crc_str = 1234535;
	CustomExplosionInfo.flags = 1;
	CustomExplosionInfo.m_radius = 4.0f;
	CustomExplosionInfo.m_secondary_radius = 6.0f;
	CustomExplosionInfo.m_knockdown_radius = 3.0f;
	CustomExplosionInfo.m_flinch_radius = 4.0f;
	CustomExplosionInfo.m_ai_sound_radius = 2.0f;
	CustomExplosionInfo.m_human_min_damage_hitpoints = 30;
	CustomExplosionInfo.m_human_max_damage_hitpoints = 40;
	CustomExplosionInfo.m_vehicle_min_damage_hitpoints = 40;
	CustomExplosionInfo.m_vehicle_max_damage_hitpoints = 50;
	CustomExplosionInfo.player_damage_mult = 0.1f;
	CustomExplosionInfo.player_veh_damage_mult = 0.1f;
	CustomExplosionInfo.player_vehicle_impulse_mult = 1.0f;
	CustomExplosionInfo.m_impulse_magnitude = 40000.0f;
	CustomExplosionInfo.m_structural_damage = 12000;
	CustomExplosionInfo.expanding_explosion_duration = 0;
	CustomExplosionInfo.expanding_explosion_delay = 0;
	CustomExplosionInfo.m_num_effects = 1;
	CustomExplosionInfo.m_effects[0] = 444;
	CustomExplosionInfo.m_effects[1] = 0;
	CustomExplosionInfo.m_effects[2] = 0;
	CustomExplosionInfo.m_effects[3] = 0;
	CustomExplosionInfo.m_num_material_effects = 0;
	CustomExplosionInfo.m_material_effects[0] = 0;
	CustomExplosionInfo.m_material_effects[1] = 0;
	CustomExplosionInfo.m_material_effects[2] = 0;
	CustomExplosionInfo.m_material_effects[3] = 0;
	CustomExplosionInfo.m_material_effects[4] = 0;
	CustomExplosionInfo.m_material_effects[5] = 0;
	CustomExplosionInfo.m_material_effects[6] = 0;
	CustomExplosionInfo.m_material_effects[7] = 0;
	CustomExplosionInfo.m_material_referenece[0] = 0;
	CustomExplosionInfo.m_material_referenece[1] = 0;
	CustomExplosionInfo.m_material_referenece[2] = 0;
	CustomExplosionInfo.m_material_referenece[3] = 0;
	CustomExplosionInfo.m_material_referenece[4] = 0;
	CustomExplosionInfo.m_material_referenece[5] = 0;
	CustomExplosionInfo.m_material_referenece[6] = 0;
	CustomExplosionInfo.m_material_referenece[7] = 0;
	CustomExplosionInfo.salvage_material = SALVAGE_MATERIAL_METAL;
	CustomExplosionInfo.salvage_max_pieces = 0;
	CustomExplosionInfo.salvage_probability = 1.0f;
	CustomExplosionInfo.time_between_breaks = 1;
	CustomExplosionInfo.half_angle_dot = 0.8f;
	CustomExplosionInfo.blast_decal_radius = 2.0f;
	strcpy_s(CustomExplosionInfo.camera_shake_type, "");
	CustomExplosionInfo.camera_shake_multiplier = 1.0f;
	CustomExplosionInfo.camera_shake_falloff = 1.0f;
	CustomExplosionInfo.ignore_orientation = false;
	CustomExplosionInfo.always_ragdoll = false;

	CustomTimeOfDayLightColor.red = 0.0f;
	CustomTimeOfDayLightColor.green = 0.0f;
	CustomTimeOfDayLightColor.blue = 0.0f;
	CustomTimeOfDayLightColor.alpha = 0.0f;

	CustomAlertLevel = ALERT_LEVEL_GREEN;
	CustomPlayerImpulseApply.SetAll(0.0f);
}

void GeneralTweaksGui::Draw()
{
	if (!*OpenState)
	{
		return;
	}
	ImGui::SetNextWindowSize(ImVec2(600.0f, 700.0f), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin(Title.c_str(), OpenState))
	{
		ImGui::End();
		return;
	}

	ImGui::PushFont(Globals::FontBig);
	ImGui::Text("General tweaks:");
	ImGui::PopFont();
	ImGui::Separator();

	if (ImGui::Button("Toggle Hud"))
	{
		ToggleHud();
	}
	if (ImGui::Button("Toggle Fog"))
	{
		ToggleFog();
	}
	ImGui::Separator();


	//ImGui::Separator();
	
	ImGui::Text("Alert level: ");
	ImGui::SameLine();
	gfm_alert_levels AlertCheck = gsm_get_alert_level();
	if (AlertCheck == ALERT_LEVEL_GREEN)
	{
		ImGui::TextColored(Globals::ColorGreen, std::string(std::string(ICON_FA_SMILE_BEAM) + u8" Green").c_str());
	}
	else if (AlertCheck == ALERT_LEVEL_YELLOW)
	{
		ImGui::TextColored(Globals::ColorYellow, std::string(std::string(ICON_FA_MEH) + u8" Yellow").c_str());
	}
	else if (AlertCheck == ALERT_LEVEL_ORANGE)
	{
		ImGui::TextColored(Globals::ColorOrange, std::string(std::string(ICON_FA_FROWN) + u8" Orange").c_str());
	}
	else if (AlertCheck == ALERT_LEVEL_RED)
	{
		ImGui::TextColored(Globals::ColorRed, std::string(std::string(ICON_FA_DUMPSTER_FIRE) + u8" Red").c_str());
	}
	else
	{
		ImGui::TextColored(Globals::SecondaryTextColor, std::string(std::string(ICON_FA_QUESTION) + u8" Invalid").c_str());
	}
	ImGui::RadioButton("Green", reinterpret_cast<int*>(&CustomAlertLevel), ALERT_LEVEL_GREEN);
	ImGui::SameLine();
	ImGui::RadioButton("Yellow", reinterpret_cast<int*>(&CustomAlertLevel), ALERT_LEVEL_YELLOW);
	ImGui::SameLine();
	ImGui::RadioButton("Orange", reinterpret_cast<int*>(&CustomAlertLevel), ALERT_LEVEL_ORANGE);
	ImGui::SameLine();
	ImGui::RadioButton("Red", reinterpret_cast<int*>(&CustomAlertLevel), ALERT_LEVEL_RED);
	ImGui::SameLine();
	if (ImGui::Button("Set alert level"))
	{
		gsm_set_alert_level(CustomAlertLevel);
	}
	ImGui::SameLine();
	ImGui::Checkbox("Lock", &LockAlertLevel);
	ImGui::Separator();

	ImGui::Text("Xray Effect Mode: ");
	ImGui::SameLine(); ImGui::RadioButton("Backpack", &XrayEffectMode, 0);
	ImGui::SameLine(); ImGui::RadioButton("Rail Driver", &XrayEffectMode, 1);
	ImGui::Text("Selected mode value: "); ImGui::SameLine();
	ImGui::TextColored(Globals::SecondaryTextColor, std::to_string(XrayEffectMode).c_str());
	if (ImGui::Button("Toggle Selected Xray Mode"))
	{
		if (XrayEffectMode == 0)
		{
			if (XrayModeOn)
			{
				xray_effect_stop(XET_VISION_BACKPACK);
				XrayModeOn = false;
			}
			else
			{
				xray_effect_start(XET_VISION_BACKPACK);
				XrayModeOn = true;
			}
		}
		else if (XrayEffectMode == 1)
		{
			if (XrayModeOn)
			{
				xray_effect_stop(XET_RAIL_DRIVER);
				XrayModeOn = false;
			}
			else
			{
				xray_effect_start(XET_RAIL_DRIVER);
				XrayModeOn = true;
			}
		}
	}
	ImGui::Checkbox("Infinite jetpack", &Globals::InfiniteJetpack);
	if (ImGui::Checkbox("Invulnerability", &Invulnerable))
	{
		PlayerPtr->HitPoints = PlayerPtr->MaxHitPoints;
	}
	if (!Invulnerable)
	{
		PlayerPtr->Flags.invulnerable = false;
	}
	if (ImGui::Checkbox("Ignored by AI", &AiIgnore))
	{
		//Have to manually set rather than sticking in checkbox call because bitfields addresses can't be captured.
		PlayerPtr->Flags.ai_ignore = !PlayerPtr->Flags.ai_ignore;
		AiIgnore = PlayerPtr->Flags.ai_ignore;
	}
	if(ImGui::Checkbox("Disable player ragdoll", &DisablePlayerRagdoll))
	{
		PlayerPtr->Flags.disallow_flinches_and_ragdolls = !PlayerPtr->Flags.disallow_flinches_and_ragdolls;
		DisablePlayerRagdoll = PlayerPtr->Flags.disallow_flinches_and_ragdolls;
	}
    ImGui::SetNextItemWidth(230.0f);
	ImGui::InputInt("Salvage", &PlayerPtr->Metadata.Salvage);
    ImGui::SetNextItemWidth(230.0f);
	ImGui::InputInt("Mining count", &PlayerPtr->Metadata.MiningCount);
    ImGui::SetNextItemWidth(230.0f);
	ImGui::InputInt("Supply crate count", &PlayerPtr->Metadata.SupplyCrateCount);

	//Doesn't work quite yet, couldn't properly grab the players rigid body.
	//ImGui::Separator();
	//ImGui::Text("Player rigid body");
	//ImGui::Separator();
	//ImGui::PushItemWidth(230.0f);
	//ImGui::InputFloat3("Linear impulse to apply", (float*)&CustomPlayerImpulseApply, 3);
	//if(GlobalPlayerRigidBody)
	//{
	//	ImGui::PushItemWidth(230.0f);
	//	ImGui::InputFloat("Friction", &GlobalPlayerRigidBody->m_material.m_friction);
	//	ImGui::PushItemWidth(230.0f);
	//	ImGui::InputFloat("Restitution", &GlobalPlayerRigidBody->m_material.m_restitution);
	//	if (ImGui::Button("Apply impulse by hkpRigidBody*"))
	//	{
	//		HavokBodyApplyLinearImpulseA(GlobalPlayerRigidBody, &CustomPlayerImpulseApply);
	//	}
	//}
	//else
	//{
	//	ImGui::Text("Player rigid body pointer is null! Can't display gui section.");
	//}
	//if (ImGui::Button("Apply impulse by handle"))
	//{
	//	HavokBodyApplyLinearImpulseB(PlayerPtr->Handle, &CustomPlayerImpulseApply);
	//}
	//if (ImGui::Button("Apply impulse by havok handle"))
	//{
	//	HavokBodyApplyLinearImpulseB(PlayerPtr->HavokHandle, &CustomPlayerImpulseApply);
	//}
	//ImGui::Separator();

/*
	ImGui::InputInt("Unlimited ammo", &CustomUnlimitedAmmo);
	ImGui::InputFloat("Stealth percent", &CustomStealthPercent);
	ImGui::InputFloat("Render alpha", &CustomRenderAlpha);
	ImGui::Checkbox("Temp use customs", &TempUseCustoms);*/
	/*if (ImGui::Checkbox("Unlimited ammo", &UnlimitedAmmo))
	{
		PlayerPtr->PFlags.UnlimitedAmmo = true;
	}
	else
	{
		PlayerPtr->PFlags.UnlimitedAmmo = false;
	}*/

	//ImGui::InputInt("District hash", (int*)&PlayerPtr->Metadata.DistrictHash);
	//ImGui::InputInt("District time", &PlayerPtr->Metadata.DistrictTime);
	//ImGui::InputInt("Upgrades array", &PlayerPtr->Metadata.upgrades);
	//ImGui::InputInt("Play time", &PlayerPtr->Metadata.PlayTime);
	//ImGui::InputInt("Last death time", &PlayerPtr->Metadata.LastDeathTime);
/*
	if (ImGui::CollapsingHeader("Upgrades array"))
	{
		for (int i = 0; i < 128; i++)
		{
			ImGui::Text(std::string("Index" + std::to_string(i)).c_str());
			ImGui::PushItemWidth(300.0f);
			ImGui::InputInt("Current level (0 to 255)", (int*)&PlayerPtr->Metadata.upgrades[i].current_level);
			ImGui::PushItemWidth(300.0f);
			ImGui::InputInt("Availability bitfield (0 to 65,535)", (int*)&PlayerPtr->Metadata.upgrades[i].availability_bitfield);
			ImGui::PushItemWidth(300.0f);
			ImGui::InputInt("Unlocked notified bitfield (0 to 65,535)", (int*)&PlayerPtr->Metadata.upgrades[i].unlocked_notified_bitfield);
			ImGui::PushItemWidth(300.0f);
			ImGui::InputInt("New notified bitfield (0 to 65,535)", (int*)&PlayerPtr->Metadata.upgrades[i].new_notified_bitfield);
		}
	}*/

	//ImGui::Text("Code driven jump height:"); ImGui::SameLine();
	//ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->CodeDrivenJumpHeight).c_str());
    ImGui::SetNextItemWidth(230.0f);
	ImGui::InputFloat("Custom player jump height", &CustomJumpHeight, 0.5f, 2.0f, 3); ImGui::SameLine();
	ImGui::Checkbox("##Custom Player Jump Height", &NeedCustomJumpHeightSet);

	//ImGui::Text("Player move speed:"); ImGui::SameLine();
	//ImGui::TextColored(SecondaryTextColor, std::to_string(PlayerPtr->MoveSpeed).c_str());
    ImGui::SetNextItemWidth(230.0f);
	ImGui::InputFloat("Player move speed", &CustomPlayerMoveSpeed, 1.0f, 5.0f, 3);
	ImGui::SameLine();
	ImGui::Checkbox("##Player move speed checkbox", &NeedCustomMoveSpeedSet);
	
    ImGui::SetNextItemWidth(230.0f);
	ImGui::InputFloat("Player max speed", &CustomPlayerMaxSpeed, 1.0f, 5.0f, 3);
	ImGui::SameLine();
	ImGui::Checkbox("##Player max move speed checkbox", &NeedCustomMaxMoveSpeedSet);
	ImGui::Separator();

	if (!UseCustomLevelAmbientLight)
	{
		CustomLevelAmbientLight.x = Globals::RfgWorldPtr->level_ambient.x;
		CustomLevelAmbientLight.y = Globals::RfgWorldPtr->level_ambient.y;
		CustomLevelAmbientLight.z = Globals::RfgWorldPtr->level_ambient.z;
	}
	if (!UseCustomLevelBackgroundAmbientLight)
	{
		CustomLevelBackgroundAmbientLight.x = Globals::RfgWorldPtr->level_back_ambient.x;
		CustomLevelBackgroundAmbientLight.y = Globals::RfgWorldPtr->level_back_ambient.y;
		CustomLevelBackgroundAmbientLight.z = Globals::RfgWorldPtr->level_back_ambient.z;
	}
	if (!UseCustomTimeOfDayLight)
	{
		CustomTimeOfDayLightColor.red = Globals::TODLightPtr->m_color.red;
		CustomTimeOfDayLightColor.green = Globals::TODLightPtr->m_color.green;
		CustomTimeOfDayLightColor.blue = Globals::TODLightPtr->m_color.blue;
		CustomTimeOfDayLightColor.alpha = Globals::TODLightPtr->m_color.alpha;
	}

    ImGui::SetNextItemWidth(230.0f);
	ImGui::InputFloat3("Level ambient light", (float*)&CustomLevelAmbientLight, 3);
	ImGui::SameLine();
	ImGui::Checkbox("##ToggleLevelAmbientLight", &UseCustomLevelAmbientLight);
    ImGui::SetNextItemWidth(230.0f);
	ImGui::InputFloat3("Level background ambient light", (float*)&CustomLevelBackgroundAmbientLight, 3);
	ImGui::SameLine();
	ImGui::Checkbox("##ToggleLevelBackgroundAmbientLight", &UseCustomLevelBackgroundAmbientLight);
	ImGui::Separator();

	//ImGui::InputInt("Middle mouse spawns per second", &MiddleMouseExplosionsPerSecond);
	//Utilities::GUI::TooltipOnPrevious("Used to determine how many time per second and explosion or repair sphere can be spawned per second by the middle mouse. Used to prevent lag from 100's of explosions per second.");
	if (ImGui::CollapsingHeader("Custom explosion spawn settings"))
	{
		ImGui::Separator();
		ImGui::PushFont(Globals::FontBig);
		ImGui::Text("Explosion info:");
		ImGui::PopFont();
		ImGui::Separator();

		ImGui::Checkbox("Spawn explosion with middle mouse?", &MiddleMouseBoomActive);
		ImGui::InputInt("Middle mouse explosions per second limit", &MiddleMouseExplosionsPerSecond);
		ImGui::SameLine();
		Utilities::GUI::ShowHelpMarker("Used to prevent lag from 100s of explosions per second since the script loader thread is currently uncapped.");
		if (ImGui::Button("Boom"))
		{
			ExplosionCreate(&CustomExplosionInfo, PlayerPtr, PlayerPtr, &PlayerPtr->aim_pos, &PlayerPtr->Orientation, &PlayerPtr->aim_pos, NULL, false);
		}
		ImGui::SameLine();
		Utilities::GUI::ShowHelpMarker("Spawns an explosion with the values entered below where the player is aiming. The middle mouse button option is much more convenient.");
		ImGui::Separator();

		ImGui::InputText("Name", (char*)&CustomExplosionInfo.m_name, 32);
		ImGui::InputInt("Unique ID", &CustomExplosionInfo.m_unique_id);
		ImGui::SameLine();
		Utilities::GUI::ShowHelpMarker("Make sure that you use a unique value for the unique id variable or you might get behavior not matching the variables you've set. I believe that all of the games explosions use the lower unique id values. So if you just use a value larger than 1000 you shouldn't have an issue.");
		ImGui::InputInt("Name CRC", (int*)&CustomExplosionInfo.m_name_crc_str); //Todo: Need to make a wrapper for this so the range isn't limited to the signed range.
		ImGui::SameLine();
		Utilities::GUI::ShowHelpMarker("You also need to be careful that this value is unique. Currently there's no easy way to check that, but the default value never seems to have issues.");
		ImGui::InputFloat("Radius", &CustomExplosionInfo.m_radius);
		ImGui::InputFloat("Secondary radius", &CustomExplosionInfo.m_secondary_radius);
		ImGui::InputFloat("Knockdown radius", &CustomExplosionInfo.m_knockdown_radius);
		ImGui::InputFloat("Flinch radius", &CustomExplosionInfo.m_flinch_radius);
		ImGui::InputFloat("AI sound radius", &CustomExplosionInfo.m_ai_sound_radius);
		ImGui::InputInt("Human min damage hitpoints", (int*)&CustomExplosionInfo.m_human_min_damage_hitpoints);
		ImGui::InputInt("Human max damage hitpoints", (int*)&CustomExplosionInfo.m_human_max_damage_hitpoints);
		ImGui::InputInt("Vehicle min damage hitpoints", (int*)&CustomExplosionInfo.m_vehicle_min_damage_hitpoints);
		ImGui::InputInt("Vehicle max damage hitpoints", (int*)&CustomExplosionInfo.m_vehicle_max_damage_hitpoints);
		ImGui::InputFloat("Player damage multiplier", &CustomExplosionInfo.player_damage_mult);
		ImGui::InputFloat("Player vehicle damage multiplier", &CustomExplosionInfo.player_veh_damage_mult);
		ImGui::InputFloat("Player vehicle impulse multiplier", &CustomExplosionInfo.player_vehicle_impulse_mult);
		ImGui::InputFloat("Impulse magnitude", &CustomExplosionInfo.m_impulse_magnitude);
		ImGui::InputInt("Structural damage", &CustomExplosionInfo.m_structural_damage);

		ImGui::InputInt("Expanding explosion duration", (int*)&CustomExplosionInfo.expanding_explosion_duration);
		ImGui::InputInt("Expanding explosion delay", (int*)&CustomExplosionInfo.expanding_explosion_delay);
		ImGui::InputInt("Number of effects", (int*)&CustomExplosionInfo.m_num_effects);
		ImGui::InputInt("Effect 0", (int*)&CustomExplosionInfo.m_effects[0]);
		ImGui::SameLine();
		Utilities::GUI::ShowHelpMarker("Try some of the values up in the hundreds. You can try checking the values in EffectsInfo.txt, but they don't seem to match up with these values. I'll try to figure out a better way to choose an explosion effect other than guessing.");
		ImGui::InputInt("Effect 1", (int*)&CustomExplosionInfo.m_effects[1]);
		ImGui::InputInt("Effect 2", (int*)&CustomExplosionInfo.m_effects[2]);
		ImGui::InputInt("Effect 3", (int*)&CustomExplosionInfo.m_effects[3]);
		ImGui::InputInt("Number of material effects", (int*)&CustomExplosionInfo.m_num_material_effects);
		ImGui::InputInt("Material effect 0", (int*)&CustomExplosionInfo.m_material_effects[0]);
		ImGui::InputInt("Material effect 1", (int*)&CustomExplosionInfo.m_material_effects[1]);
		ImGui::InputInt("Material effect 2", (int*)&CustomExplosionInfo.m_material_effects[2]);
		ImGui::InputInt("Material effect 3", (int*)&CustomExplosionInfo.m_material_effects[3]);
		ImGui::InputInt("Material effect 4", (int*)&CustomExplosionInfo.m_material_effects[4]);
		ImGui::InputInt("Material effect 5", (int*)&CustomExplosionInfo.m_material_effects[5]);
		ImGui::InputInt("Material effect 6", (int*)&CustomExplosionInfo.m_material_effects[6]);
		ImGui::InputInt("Material effect 7", (int*)&CustomExplosionInfo.m_material_effects[7]);
		//Material reference array

		ImGui::Text("Salvage material type:");
		ImGui::RadioButton("Invalid Material", (int*)&CustomExplosionInfo.salvage_material, INVALID_SALVAGE_MATERIAL);
		ImGui::SameLine();
		ImGui::RadioButton("Metal", (int*)&CustomExplosionInfo.salvage_material, SALVAGE_MATERIAL_METAL);
		ImGui::SameLine();
		ImGui::RadioButton("Ore", (int*)&CustomExplosionInfo.salvage_material, SALVAGE_MATERIAL_ORE);
		ImGui::SameLine();
		ImGui::RadioButton("Chemical", (int*)&CustomExplosionInfo.salvage_material, SALVAGE_MATERIAL_CHEMICAL);

		ImGui::InputInt("Salvage max pieces", &CustomExplosionInfo.salvage_max_pieces);
		ImGui::InputFloat("Salvage probability", &CustomExplosionInfo.salvage_probability);
		ImGui::InputInt("Time between breaks", &CustomExplosionInfo.time_between_breaks);
		ImGui::InputFloat("Half angle dot", &CustomExplosionInfo.half_angle_dot);
		ImGui::InputFloat("Blast decal radius", &CustomExplosionInfo.blast_decal_radius);
		//camera_shake_type[32]
		ImGui::InputFloat("Camera shake multiplier", &CustomExplosionInfo.camera_shake_multiplier);
		ImGui::InputFloat("Camera shake falloff", &CustomExplosionInfo.camera_shake_falloff);
		ImGui::Checkbox("Ignore orientation", &CustomExplosionInfo.ignore_orientation);
		ImGui::Checkbox("Always ragdoll", &CustomExplosionInfo.always_ragdoll);
	}
	ImGui::Separator();

	/*if (ImGui::CollapsingHeader("Repair sphere"))
	{
		ImGui::Checkbox("Spawn repair sphere with middle mouse?", &MiddleMouseRepairSphereActive);
		ImGui::InputFloat("Radius", &RepairRadius);
		ImGui::InputInt("Duration", &RepairDuration);
		
		ImGui::Text("Spawn position:");
		ImGui::RadioButton("Player position", &RepairPosition, 0);
		ImGui::SameLine();
		ImGui::RadioButton("Aim position", &RepairPosition, 1);
	}
	ImGui::Separator();*/

	ImGui::Separator();
	ImGui::PushFont(Globals::FontBig);
	ImGui::Text("Experimental settings:");
	ImGui::PopFont();
	ImGui::Separator();

	if (ImGui::CollapsingHeader("Info dumps"))
	{
		//all_zones and global_zone_grid in rfg::world are always empty. 
		static int ZoneScanRange = 2000;
		ImGui::InputInt("Zone scan range", &ZoneScanRange);
		ImGui::SameLine();
		Utilities::GUI::ShowHelpMarker("Only used by the first 2 buttons below this. A working list of zones in the games memory hasn't been found yet, so instead, a function that grabs zones by index is used to check every zone in this range. 2000 seems to be a good default, and setting it higher I never found any more zones.");
		static float CustomMinWindSpeed = 0.0f;
		static float CustomMaxWindSpeed = 0.0f;
		ImGui::InputFloat("Custom min wind speed", &CustomMinWindSpeed);
		ImGui::InputFloat("Custom max wind speed", &CustomMaxWindSpeed);
		if (ImGui::Button("Set all zone wind speeds"))
		{
			if (Globals::RfgWorldPtr)
			{
				int ValidWorldZoneCount = 0;
				int ValidObjectZoneCount = 0;
				for (int i = 0; i < ZoneScanRange; i++)
				{
					world_zone* CurrentWorldZone = get_world_zone_by_index(Globals::RfgWorldPtr, NULL, i);
					if (CurrentWorldZone)
					{
						ValidWorldZoneCount++;
						if (CurrentWorldZone->zone_objp)
						{
							ValidObjectZoneCount++;
							CurrentWorldZone->zone_objp->wind_min_speed = CustomMinWindSpeed;
							CurrentWorldZone->zone_objp->wind_max_speed = CustomMaxWindSpeed;
						}
					}
				}
				Logger::Log("Done setting zone wind speeds", LogInfo);
				Logger::Log(std::string("# of valid world zones: " + std::to_string(ValidWorldZoneCount)), LogInfo);
				Logger::Log(std::string("# of valid object zones: " + std::to_string(ValidObjectZoneCount)), LogInfo);
			}
		}
		ImGui::SameLine();
		Utilities::GUI::ShowHelpMarker("Sets the min and max wind speed values you've chosen in any zones it finds in the range you've chosen. Added for experimentation. I haven't see any changes from this.");

		if (ImGui::Button("Dump zone info"))
		{
			if (Globals::RfgWorldPtr)
			{
				int NumberOfWorldZonesFound = 0;
				int NumberOfObjectZonesFound = 0;
				std::ofstream ZoneDump(Globals::GetEXEPath(false) + "RFGR Script Loader/ZoneInfoDump.txt", std::ios_base::trunc);
				ZoneDump << "\nPrinting all world zone names...\n";
				Logger::Log("\nPrinting all world zone names...\n", LogInfo);
				for (int i = 0; i < ZoneScanRange; i++)
				{
					world_zone* CurrentWorldZone = get_world_zone_by_index(Globals::RfgWorldPtr, NULL, i);
					if (CurrentWorldZone)
					{
						NumberOfWorldZonesFound++;
						ZoneDump << "Index: " << i << "\n";
						ZoneDump << "Zone name: " << CurrentWorldZone->name << "\n";
						ZoneDump << "srid: " << CurrentWorldZone->srid << "\n";
						ZoneDump << "gid: " << CurrentWorldZone->gid << "\n";
						ZoneDump << "Border zone: " << CurrentWorldZone->is_border_zone << "\n";
						if (CurrentWorldZone->zone_objp)
						{
							NumberOfObjectZonesFound++;
							ZoneDump << "Object zone:\n";
							ZoneDump << "    All index: " << CurrentWorldZone->zone_objp->AllIndex << "\n";
							ZoneDump << "    Min wind speed: " << CurrentWorldZone->zone_objp->wind_min_speed << "\n";
							ZoneDump << "    Max wind speed: " << CurrentWorldZone->zone_objp->wind_max_speed << "\n";
							ZoneDump << "    Handle: " << CurrentWorldZone->zone_objp->Handle << "\n";
							ZoneDump << "    Havok handle: " << CurrentWorldZone->zone_objp->HavokHandle << "\n";
							ZoneDump << "    Terrain filename: " << CurrentWorldZone->zone_objp->terrain->filename << "\n\n";
						}
						else
						{
							ZoneDump << "--Invalid object zone--\n\n";
						}
					}
				}
				Logger::Log("Done printing all world zone info. Check ZoneInfoDump.txt in the script loader folder.", LogInfo);
				Logger::Log(std::string("Number of world zones found: " + std::to_string(NumberOfWorldZonesFound)), LogInfo);
				Logger::Log(std::string("Number of object zones found: " + std::to_string(NumberOfObjectZonesFound)), LogInfo);
				ZoneDump << "Done printing all world zone info\n";
				ZoneDump << "Number of zones found: " << NumberOfWorldZonesFound;
				ZoneDump << "Number of zones found: " << NumberOfObjectZonesFound;
			}
			else
			{
				Logger::Log("Could not print zone names, the world pointer is null!\n", LogError);
			}
		}
		ImGui::SameLine();
		Utilities::GUI::ShowHelpMarker("Prints info about the any world_zones it finds to ZoneInfoDump.txt. Many zone indices don't have a valid zone, and so the range set above is scanned through and only valid zones are printed to the file.");
		ImGui::Separator();

		if (ImGui::Button("Print misc world values"))
		{
			std::cout << "\nPrinting all misc world values...\n";
			std::ofstream WorldDump(Globals::GetEXEPath(false) + "RFGR Script Loader/WorldInfoDump.txt", std::ios_base::trunc);
			if (Globals::RfgWorldPtr)
			{
				WorldDump << "Max world objects: " << Globals::RfgWorldPtr->max_world_objects << "\n";
				WorldDump << "Tech level: " << Globals::RfgWorldPtr->tech_level << "\n";
				WorldDump << "Tech level max: " << Globals::RfgWorldPtr->tech_level_max << "\n";
				WorldDump << "Pending filename: " << Globals::RfgWorldPtr->pending_filename << "\n";
				WorldDump << "Object list capacity: " << Globals::RfgWorldPtr->all_objects.Capacity() << "\n";
				WorldDump << "Object list size: " << Globals::RfgWorldPtr->all_objects.Size() << "\n";
				WorldDump << "Num territory zones: " << Globals::RfgWorldPtr->num_territory_zones << "\n";
			}
			else
			{
				WorldDump << "Could not print misc world values, the world pointer is null!\n";
				Logger::Log("Could not print misc world values, the world pointer is null!\n", LogError);
			}
			std::cout << "Done!\n";
		}
		ImGui::SameLine();
		Utilities::GUI::ShowHelpMarker("Prints info about the rfg world to WorldInfoDump.txt. Much shorter than the other info dumps.");

        static bool OnlyDumpNamedObjects = false;
        ImGui::Checkbox("Only dump named objects", &OnlyDumpNamedObjects);
		if (ImGui::Button("Dump all object info"))
		{
			if (Globals::RfgWorldPtr)
			{
				Globals::CreateDirectoryIfNull(Globals::GetEXEPath(false) + "RFGR Script Loader/Info dumps/");
				Globals::CreateDirectoryIfNull(Globals::GetEXEPath(false) + "RFGR Script Loader/Info dumps/Object info dumps/");
				/*std::string DumpFileName = Logger::GetTimeString(false);
				DumpFileName = DumpFileName.substr(1, DumpFileName.size() - 2);
				DumpFileName += ".txt";
				for (auto& i : DumpFileName)
				{
					if (i == '/' || i == '\\')
					{
						i = '-';
					}
					if (i == ':')
					{
						i = '\0';
					}
				}*/
				std::string DumpFileName = "ObjectInfoDump - ";
				DumpFileName += std::to_string(time(NULL));
				DumpFileName += ".txt";
				std::cout << "Dump file name: " << DumpFileName << "\n";
				std::cout << "Dump file path: " << Globals::GetEXEPath(false) + "RFGR Script Loader/Info dumps/Object info dumps/" + DumpFileName << "\n";
				Logger::Log(std::string("\nDumping all object info to /RFGR Script Loader/Info dumps/Object info dumps/") + std::string(DumpFileName) + std::string(".\n"), LogInfo);
				std::ofstream PositionsDump(Globals::GetEXEPath(false) + "RFGR Script Loader/Info dumps/Object info dumps/" + DumpFileName.c_str(), std::ios_base::trunc);
				PositionsDump << "Start of object info dump...\n";
				PositionsDump << "Objects array capacity: " << Globals::RfgWorldPtr->all_objects.Capacity() << "\n";
				PositionsDump << "Objects array objects contained: " << Globals::RfgWorldPtr->all_objects.Size() << "\n";
				//PositionsDump << "Sector name: " << Globals::RfgWorldPtr->territory_name << "\n\n";

				for (int i = 0; i < Globals::RfgWorldPtr->all_objects.Size(); i++)
				{
					if (Globals::RfgWorldPtr->all_objects[i])
					{
                        const char* TempName = world_get_object_name(Globals::RfgWorldPtr, NULL, Globals::RfgWorldPtr->all_objects[i]);
                        std::string ObjectName(TempName);
                        if(OnlyDumpNamedObjects)
                        {
                            if(TempName == nullptr || ObjectName.length() < 3)
                            {
                                break;
                            }
                        }
						PositionsDump << "Index: " << i << "\n";
						PositionsDump << "Name: " << ObjectName << "\n";
						PositionsDump << "Type: " << (int)(*Globals::RfgWorldPtr->all_objects[i]).ObjectType << "\n"; //Todo: Add type name string
						PositionsDump << "Subtype: " << (int)(*Globals::RfgWorldPtr->all_objects[i]).SubType << "\n"; //Todo: Add subtype name string
						PositionsDump << "Position:\n";
						PositionsDump << "    x: " << (*Globals::RfgWorldPtr->all_objects[i]).Position.x << "\n";
						PositionsDump << "    y: " << (*Globals::RfgWorldPtr->all_objects[i]).Position.y << "\n";
						PositionsDump << "    z: " << (*Globals::RfgWorldPtr->all_objects[i]).Position.z << "\n";

						world_zone* ObjectWorldZone = GetWorldZoneByObjectHandle(Globals::RfgWorldPtr, NULL, (*Globals::RfgWorldPtr->all_objects[i]).Handle);
						if (ObjectWorldZone)
						{
							PositionsDump << "Zone:\n";
							PositionsDump << "    Name: " << ObjectWorldZone->name << "\n\n";
						}
						else
						{
							PositionsDump << "--Invalid world zone--\n\n";
						}
					}
					else
					{
						PositionsDump << "Skipping object at index " << i << ", invalid pointer.\n\n";
					}
				}
				PositionsDump << "End of object info dump.";
				Logger::Log("Finished dumped all object into to ObjectInfoDump.txt!", LogInfo);
				PositionsDump.close();
			}
			else
			{
				Logger::Log("Could not print zone names, the world pointer is null!", LogError);
			}
		}
		ImGui::SameLine();
		Utilities::GUI::ShowHelpMarker("Prints info about all rfg objects into ObjectInfoDump.txt. Overwrites data from the previous write each time.");
	}

	if (ImGui::CollapsingHeader("Time of day light")) //Todo: Add rl_scene_entity and rl_3d_entity info to this.
	{
		if (Globals::TODLightPtr)
		{
			ImGui::Text("Light type:");
			ImGui::RadioButton("Directional", (int*)&Globals::TODLightPtr->m_light_type, LIGHT_TYPE_DIRECTIONAL);
			ImGui::SameLine();
			ImGui::RadioButton("Point", (int*)&Globals::TODLightPtr->m_light_type, LIGHT_TYPE_POINT);
			ImGui::SameLine();
			ImGui::RadioButton("Spot light", (int*)&Globals::TODLightPtr->m_light_type, LIGHT_TYPE_SPOT_LIGHT);
			ImGui::SameLine();
			ImGui::RadioButton("Force size of int", (int*)&Globals::TODLightPtr->m_light_type, LIGHT_TYPE_FORCE_SIZEOF_INT);

			ImGui::Text("Color:");
			ImGui::Checkbox("Use custom color", &UseCustomTimeOfDayLight);
			Utilities::GUI::TooltipOnPrevious("This needs to be checked for your values to be properly set");
			ImGui::InputFloat("Red", &CustomTimeOfDayLightColor.red, 0.01, 0.1, 3);
			ImGui::InputFloat("Green", &CustomTimeOfDayLightColor.green, 0.01, 0.1, 3);
			ImGui::InputFloat("Blue", &CustomTimeOfDayLightColor.blue, 0.01, 0.1, 3);
			ImGui::InputFloat("Alpha", &CustomTimeOfDayLightColor.alpha, 0.01, 0.1, 3);

			ImGui::InputFloat("Attenuation start", &Globals::TODLightPtr->m_attenuation_start, 0.01, 0.1, 3);
			ImGui::InputFloat("Attenuation end", &Globals::TODLightPtr->m_attenuation_end, 0.01, 0.1, 3);
			ImGui::InputFloat("Hotspot falloff size", &Globals::TODLightPtr->m_hotspot_falloff_size, 0.01, 0.1, 3);
			ImGui::InputFloat("Hotspot size", &Globals::TODLightPtr->m_hotspot_size, 0.01, 0.1, 3);

			ImGui::Text("Clip minimum:");
			ImGui::InputFloat("x", &Globals::TODLightPtr->m_clip_min.x, 0.01, 0.1, 3);
			ImGui::InputFloat("y", &Globals::TODLightPtr->m_clip_min.y, 0.01, 0.1, 3);
			ImGui::InputFloat("z", &Globals::TODLightPtr->m_clip_min.z, 0.01, 0.1, 3);

			ImGui::Text("Clip maximum:");
			ImGui::InputFloat("x", &Globals::TODLightPtr->m_clip_max.x, 0.01, 0.1, 3);
			ImGui::InputFloat("y", &Globals::TODLightPtr->m_clip_max.y, 0.01, 0.1, 3);
			ImGui::InputFloat("z", &Globals::TODLightPtr->m_clip_max.z, 0.01, 0.1, 3);

			ImGui::Text("Light direction:");
			ImGui::InputFloat("x", &Globals::TODLightPtr->m_light_direction.x, 0.01, 0.1, 3);
			ImGui::InputFloat("y", &Globals::TODLightPtr->m_light_direction.y, 0.01, 0.1, 3);
			ImGui::InputFloat("z", &Globals::TODLightPtr->m_light_direction.z, 0.01, 0.1, 3);

			//Todo: Add the following vars:
			//rl_renderable_instance *m_clip_mesh;
			//unsigned __int16 m_vis_pass_index;
			//unsigned __int16 m_shadow_vis_pass_index;
		}
		else
		{
			ImGui::Text("TOD Light pointer is null");
		}
	}
	else
	{
		ImGui::SameLine();
		ImGui::TextColored(Globals::ColorRed, "[Experimental]");
	}

	if (Globals::MainScenePtr)
	{
		//Todo: Mess with main scene settings
		if (Globals::MainSceneRendererPtr)
		{
			//ImGui::PushFont(FontBig);
			ImGui::Text("Main scene renderer settings:");
			//ImGui::PopFont();
			ImGui::Separator();

			ImGui::InputInt("Shadow map width", &Globals::MainSceneRendererPtr->m_shadow_map_width);
			ImGui::InputInt("Shadow map height", &Globals::MainSceneRendererPtr->m_shadow_map_height);

			//None of the options in this are changeable.
			/*if (GlobalMainSceneRendererPtr->m_part2_params.p_shadow_render_params)
			{
				ImGui::InputInt("Shadows enabled", (int*)&GlobalMainSceneRendererPtr->m_part2_params.p_shadow_render_params->shadows_enabled);
				ImGui::InputInt("Use clb shadows", (int*)&GlobalMainSceneRendererPtr->m_part2_params.p_shadow_render_params->use_clb_shadows);
				ImGui::InputInt("Shadow AA enabled", (int*)&GlobalMainSceneRendererPtr->m_part2_params.p_shadow_render_params->shadow_aa_enabled);

				ImGui::InputFloat("Shadow max distance", &GlobalMainSceneRendererPtr->m_part2_params.p_shadow_render_params->shadow_max_dist, 10.0f, 100.0f, 3);
				ImGui::InputFloat("Shadow fade start", &GlobalMainSceneRendererPtr->m_part2_params.p_shadow_render_params->shadow_fade_start, 10.0f, 100.0f, 3);
				ImGui::InputFloat("Shadow percent", &GlobalMainSceneRendererPtr->m_part2_params.p_shadow_render_params->shadow_percent, 10.0f, 100.0f, 3);
				ImGui::InputFloat("Shadow percent bias", &GlobalMainSceneRendererPtr->m_part2_params.p_shadow_render_params->shadow_percent_bias, 10.0f, 100.0f, 3);
			}*/
		}
	}

	ImGui::End();
}