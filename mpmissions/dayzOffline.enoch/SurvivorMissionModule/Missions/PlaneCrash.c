class PlaneCrashMission extends SurvivorMissions
{
	//Mission related entities 
	EntityAI CrashedC130;
	ItemBase MissionObject;

	//Mission parameters
	static const int MISSION_TIME = 7200; // 2 hours
	int MsgDlyFinish = 180;			// 3mins - seconds, message delay time after player has finished mission
	int MissionType = 0;			// 0 = meds, 1 = basebuilding, 2 = ammo & weapons
	int ZombieCount = 12; 			// 12 zeds

	//Mission containers
	ref array<vector> ContainerSpawns = new ref array<vector>;
	ref array<string> InfectedTypes = new ref array<string>;

	ref static const array<string> BaseBuildingLoot =
	{
		"RFSolarPanelKit",
		"bl_pallet",
		"bl_anatolian_carpet_1_Kit",
		"bl_anatolian_carpet_2_Kit",
		"bl_old_fridge_Kit",
		"MetalPlate",
		"bl_pallet_bed_s_Kit",
		"bl_pallet_bed_m_Kit",
		"bl_pallet_cabinet_s_Kit",
		"bl_pallet_cabinet_l_Kit",
		"bl_pallet_cabinet_m_Kit",
		"bl_pallet_table_s_Kit",
		"bl_rain_collector_prefab_Kit",
		"bl_old_crate",
		"bl_stove_prefab_Kit",
		"bl_pallet_box_1_Kit",
		"bl_pallet_box_2_Kit",
		"bl_pallet_box_3_Kit",
		"bl_pallet_box_4_Kit",
		"LargeTent",
		"MediumTent",
		"CarTent",
		"ZenJameson",
		"Vodka",
		"ZSh3PilotHelmet",
		"HandSaw",
		"NailBox",
		"BarbedWire",
		"ExpansionCodeLock"
	};

	ref static const array<string> MedicalLoot =
	{
		"Chips",
		"Crackers",
		"Honey",
		"Marmalade",
		"PeachesCan",
		"Rice",
		"SpaghettiCan",
		"TacticalBaconCan",
		"Vodka",
		"BeerCan_XXXX",
		"BeerCan_VB",
		"BeerCan_Corona",
		"ZSh3PilotHelmet",
		"ExpansionCodeLock",
		"InjectorZivirol",
		"InjectorAmoksivan",
		"InjectorPromedol",
		"InjectorKetorol",
		"AmpouleAmitriptyline",
		"InjectorTopoizomeraza",
		"AmpouleFlemoclav",
		"InjectorRadioprotector",
		"TabletsB190",
		"AmpouleNeiroks",
		"InjectorNeiroks",
		"InjectorErytropoenin",
		"AmpouleAdrenalin30",
		"SurgicalKit",
		"MedContainerSmall",
		"MedContainerMedium",
		"MedContainerLarge",
		"ZenDefibrillator"
	};

	ref static const array<string> MilitaryLoot =
	{
		"TacticalBaconCan",
		"GP5GasMask",
		"WeaponCleaningKit",
		"LandMineTrap",
		"NVGoggles",
		"Zen_Mich2001Helmet_Black",
		"Zen_Mich2001Helmet_Camo",
		"Zen_Mich2001Helmet_DarkCamo",
		"Vodka",
		"Zen_MountainBag_Black",
		"Mag_AK101_30Rnd",
		"Mag_AK74_45Rnd",
		"Mag_AKM_Drum75Rnd",
		"Mag_Aug_30Rnd",
		"Mag_CMAG_40Rnd",
		"Mag_STANAG_60Rnd",
		"Mag_Saiga_Drum20Rnd",
		"Saiga",
		"ZSh3PilotHelmet",
		"PistolSuppressor",
		"M4_Suppressor",
		"AK_Suppressor",
		"Plastic_Explosive",
		"ClaymoreMine",
		"Ammo_40mm_Explosive",
		"ExpansionCodeLock"
	};

	//Mission variables 
	string SurvivorName;

	bool IsExtended() return false;

	void PlaneCrashMission()
	{
		ZenModLogger.Log("[STARTED] PlaneCrashMission started @ " + m_MissionPosition, "missions");

		//Mission mission timeout
		m_MissionTimeout = MISSION_TIME;			//seconds, mission duration time
		MissionType = Math.RandomIntInclusive(0, 2); // 0 = meds, 1 = basebuilding, 2 = ammo & weapons

		//Mission zones
		m_MissionZoneOuterRadius = 500.0;		//meters (!Do not set lower than 200m), mission activation distance
		m_MissionZoneInnerRadius = 10.0;		//meters (!Do not set outside of 1-5m), mission finishing distance to target object

		//Mission informant
		m_MissionInformant = MissionSettings.GoodBoss;

		string SurvivorDescription = "";

		if (MissionType == 0)
		{
			SurvivorDescription = "One of our most senior UN scientists was onboard, and it seems she had some important information about the cure for this disease";
			InfectedTypes.Insert("ZmbM_UN_doctor_WHO_F");
			InfectedTypes.Insert("ZmbM_UN_doctor_WHO_M");
			InfectedTypes.Insert("ZmbM_UN_nurse_WHO_F");
			InfectedTypes.Insert("ZmbM_UN_WHO_WesternNBCSuit");
			InfectedTypes.Insert("ZmbM_UN_WHO_WesternNBCSuit");
			InfectedTypes.Insert("ZmbM_UN_WHO_WesternNBCSuit");
		}

		if (MissionType == 1)
		{
			SurvivorDescription = "One of our chief UN engineers was onboard and she's carrying important plans and building materials with her";
			InfectedTypes.Insert("ZmbM_US_Army_UCP_BDU");
			InfectedTypes.Insert("ZmbM_US_Army_M81_BDU");
			InfectedTypes.Insert("ZmbM_US_Army_OCP_BDU");
			InfectedTypes.Insert("ZmbM_CDF_Olive_EasternNBCSuit");
			InfectedTypes.Insert("ZmbM_CDF_Olive_EasternNBCSuit");
			InfectedTypes.Insert("ZmbM_CDF_Olive_EasternNBCSuit");
		}

		if (MissionType == 2)
		{
			SurvivorDescription = "Our best special operations team was onboard and they were carrying important intel and military equipment with them";
			InfectedTypes.Insert("ZmbM_CDF_Dubok_GorkaSuit");
			InfectedTypes.Insert("ZmbM_CDF_DubokAlt_GorkaSuit");
			InfectedTypes.Insert("ZmbM_LDF_Woodland_Officer");
			InfectedTypes.Insert("ZmbM_US_M81_WesternNBCSuit");
			InfectedTypes.Insert("ZmbM_US_M81_WesternNBCSuit");
			InfectedTypes.Insert("ZmbM_US_M81_WesternNBCSuit");
		}

		//Set mission messages
		m_MissionMessage1 = "Can anyone read me? If you're receiving this message we need your help. One of our planes just stopped responding to our calls and dropped off radar.";
		
		int x_coord = Math.Round(m_MissionPosition[0]);
		int z_coord = Math.Round(m_MissionPosition[2]);
		
		x_coord += Math.RandomIntInclusive(-150, 150);
		z_coord += Math.RandomIntInclusive(-150, 150);
		
		string coords = " (Approximate Coordinates: " + x_coord.ToString() + " / " + z_coord.ToString() + ")";

		m_MissionMessage2 =  SurvivorDescription + ". They were flying over Livonia on their way to the U.N. headquarters in Chernarus.";
		m_MissionMessage3 = "The pilot was talking incoherently, I'm afraid he might be infected, and he tried to emergency land somewhere in the fields\n** " + m_MissionLocationDir + " of " + m_MissionLocation + coords + " **\nPlease secure the cargo before any savages find it. They were carrying explosive chemical materials onboard, so it would be wise to bring a gas mask.";

		//Container spawnpoints
		ContainerSpawns.Insert("0.87 -4.5 -2.5");
		ContainerSpawns.Insert("0.87 -4.47 -0.5");

		//Infected types - males
		InfectedTypes.Insert("ZmbM_LDF_Woodland_PilotCoveralls");
		InfectedTypes.Insert("ZmbM_US_Airforce_Olive_PilotCoveralls");
	}

	void ~PlaneCrashMission()
	{
		ZenModLogger.Log("[DESTROY] PlaneCrashMission class destroyed.", "missions");

		// Despawn all remaining mission objects
		if (m_MissionObjects)
		{
			Print("[SMM] Despawning " + m_MissionObjects.Count() + " mission objects from old mission...");
			for (int i = 0; i < m_MissionObjects.Count(); i++)
			{
				if (!m_MissionObjects.Get(i)) continue;
				else GetGame().ObjectDelete(m_MissionObjects.Get(i));
			}

			m_MissionObjects.Clear();
		}

		// Despawn mission AI's
		if (m_MissionAIs)
		{
			if (m_MissionAIs.Count() > 0)
			{
				Print("[SMM] Despawning " + m_MissionAIs.Count() + " mission AI's from old mission...");
				for (int k = 0; k < m_MissionAIs.Count(); k++)
				{
					GetGame().ObjectDelete(m_MissionAIs.Get(k));
				}

				m_MissionAIs.Clear();
			}
			else Print("[SMM] No mission AI's to despawn.");
		}
	}

	void SpawnObjects()
	{
		//Spawn crashed plane crashed C130 
		int PlaneOriConversion;
		string PlaneOrientation;

		PlaneOriConversion = m_MissionDescription[3].ToInt() - 180;
		if (PlaneOriConversion < 0) 
			PlaneOriConversion += 360;

		PlaneOrientation = PlaneOriConversion.ToString() + " 0 0";

		// Spawn plane
		CrashedC130 = EntityAI.Cast(GetGame().CreateObject("ZenMission_Wreck_C130J", m_MissionPosition));
		CrashedC130.SetOrientation(PlaneOrientation.ToVector());
		CrashedC130.PlaceOnSurface();
		CrashedC130.SetLifetime(MISSION_TIME);

		// Spawn gas cloud
		EntityAI m_GasCloud = EntityAI.Cast(GetGame().CreateObjectEx("SyberiaObjectiveZone_Toxic100", CrashedC130.GetPosition(), ECE_PLACE_ON_SURFACE | ECE_INITAI | ECE_SETUP));
		if (m_GasCloud)
			m_GasCloud.SetLifetime(MISSION_TIME);

		// Align to surface
		vector transform[4];
		CrashedC130.GetTransform(transform);
		vector ground_position, ground_dir; 
		int component;
		DayZPhysics.RaycastRV(transform[3], transform[3] + transform[1] * -100, ground_position, ground_dir, component, null, null, null, false, true);
		vector surface_normal = GetGame().SurfaceGetNormal(ground_position[0], ground_position[2]);
		vector local_ori = CrashedC130.GetDirection();
		transform[0] = surface_normal * local_ori;
		transform[1] = surface_normal;
		transform[2] = surface_normal * (local_ori * vector.Up);
		CrashedC130.SetTransform(transform);
		CrashedC130.Update();
		

		if (MissionType == 0) // Meds
		{
			//Spawn containers 
			int medsLoadout = 0;
			for (int i = 0; i < ContainerSpawns.Count(); i++)
			{
				MissionObject = ItemBase.Cast(GetGame().CreateObject("Zen_Mission_WoodenCrate", CrashedC130.ModelToWorld(ContainerSpawns.Get(i))));

				//Get random loadout 
				//selectedLoadout = Math.RandomIntInclusive(0,1);	//!change randomization limit after adding new loadouts!	

				//Spawn selected loadout items in mission object
				if (medsLoadout == 0)
				{
					SpawnItemRandom(MissionObject, "CannabisSeedsPack", 1, 0.9);
					SpawnItemRandom(MissionObject, "GPSReceiver", 1, 0.5);
					SpawnItemRandom(MissionObject, "Battery9VLithium", 5, 0.9);
					SpawnItemRandom(MissionObject, "BandageDressing", 2, 0.9);
					SpawnItemRandom(MissionObject, "BloodTestKit", 10, 0.33);
					SpawnItemRandom(MissionObject, "AmmoBox_762x39Tracer_20Rnd", 5, 0.33);
					SpawnItemRandom(MissionObject, "AmmoBox_762x54Tracer_20Rnd", 5, 0.33);
				}
				if (medsLoadout == 1)
				{
					SpawnItemRandom(MissionObject, "BandageDressing", 2, 0.9);
					SpawnItemRandom(MissionObject, "GasMask_Filter", 2, 0.5);
					SpawnItemRandom(MissionObject, "NBCBootsGray", 1, 0.75);
					SpawnItemRandom(MissionObject, "NBCGlovesGray", 1, 0.75);
					SpawnItemRandom(MissionObject, "NBCHoodGray", 1, 0.75);
					SpawnItemRandom(MissionObject, "NBCJacketGray", 1, 0.75);
					if (Math.RandomIntInclusive(0, 1) == 1)
					{
						SpawnItemRandom(MissionObject, "NBCPantsGray");
					}
					else
					{
						SpawnItemRandom(MissionObject, "ExpansionCodeLock");
					}
					
					SpawnItemRandom(MissionObject, MissionSettings.OldPhotos.GetRandomElement());
					SpawnItemRandom(MissionObject, "Zen_AirStrikeSmokeGrenade", 2, 0.75);
					SpawnItemRandom(MissionObject, "BloodTestKit", 10, 0.33);
					SpawnItemRandom(MissionObject, "BloodBagIV", 5, 0.33);
					SpawnItemRandom(MissionObject, "Pen_Black", 1, 0.5);
					SpawnItemRandom(MissionObject, "CannabisSeedsPack", 2, 0.5);
					SpawnItemRandom(MissionObject, "PumpkinSeedsPack", 1, 0.5);
					SpawnItemRandom(MissionObject, "Battery9VLithium", 1, 0.5);
				}

				Print("[SMM] Plane Medical Mission rewards spawned in reward container" + i + ". Randomly selected loadout was " + medsLoadout + ".");

				//Insert mission container into mission objects list
				m_MissionObjects.Insert(MissionObject);
				medsLoadout++;
			}

			ItemBase meditem;
			for (int i3 = 0; i3 < 12; i3++)
			{
				if (Math.RandomFloat01() < 0.25) // 25% chance to spawn sweet loot
					continue;

				vector randomPosM = CrashedC130.GetPosition();
				randomPosM[0] = randomPosM[0] + Math.RandomFloatInclusive(-5, 5);
				randomPosM[2] = randomPosM[2] + Math.RandomFloatInclusive(-5, 5);
				randomPosM[1] = GetGame().SurfaceY(randomPosM[0], randomPosM[2]);
				meditem = ItemBase.Cast(GetGame().CreateObjectEx(MedicalLoot.GetRandomElement(), randomPosM, ECE_PLACE_ON_SURFACE));

				if (!meditem)
					continue;

				meditem.PlaceOnSurface();
			}
		}
		else
			if (MissionType == 1) // Basebuilding
			{
				//Spawn containers 
				int bbLoadout = 0;
				for (int i2 = 0; i2 < ContainerSpawns.Count(); i2++)
				{
					MissionObject = ItemBase.Cast(GetGame().CreateObject("Zen_Mission_WoodenCrate", CrashedC130.ModelToWorld(ContainerSpawns.Get(i2))));

					//Spawn selected loadout items in mission object
					if (bbLoadout == 0)
					{
						SpawnItemRandom(MissionObject, "NailBox", 3, 0.75);
						SpawnItemRandom(MissionObject, "NailBox_250", 1, 0.1);
						SpawnItemRandom(MissionObject, "Hatchet");
						SpawnItemRandom(MissionObject, "ExpansionCodeLock", 0.50);
						SpawnItemRandom(MissionObject, "MetalWire", 1, 0.50);
						SpawnItemRandom(MissionObject, "Hacksaw", 1, 1.0);
						SpawnItemRandom(MissionObject, "MetalWire", 1, 0.50);
						SpawnItemRandom(MissionObject, "Whetstone", 5, 0.75);
						SpawnItemRandom(MissionObject, MissionSettings.OldPhotos.GetRandomElement());
						SpawnItemRandom(MissionObject, "EpoxyPutty", 5, 0.5);
					}
					if (bbLoadout == 1)
					{
						SpawnItemRandom(MissionObject, "NailBox_250");
						SpawnItemRandom(MissionObject, "Flag_LivoniaArmy");
						SpawnItemRandom(MissionObject, "Pliers");
						SpawnItemRandom(MissionObject, "FenceKit");
						SpawnItemRandom(MissionObject, "Cabin_Kit");
						SpawnItemRandom(MissionObject, "FieldShovel");
						SpawnItemRandom(MissionObject, "CombatKnife", 1, 0.75);
						SpawnItemRandom(MissionObject, "Whetstone", 1, 0.75);
						SpawnItemRandom(MissionObject, "Battery9VLithium", 5, 0.5);
						SpawnItemRandom(MissionObject, MissionSettings.OldPhotos.GetRandomElement());
					}

					Print("[SMM] Plane Base-Building Mission rewards spawned in reward container" + i2 + ". Randomly selected loadout was " + bbLoadout + ".");

					//Insert mission container into mission objects list
					m_MissionObjects.Insert(MissionObject);
					bbLoadout++;
				}

				ItemBase bbitem;
				for (int i4 = 0; i4 < 6; i4++)
				{
					if (Math.RandomFloat01() < 0.25) // 25% chance to spawn sweet loot
						continue;

					vector randomPosBB = CrashedC130.GetPosition();
					randomPosBB[0] = randomPosBB[0] + Math.RandomFloatInclusive(-10, 10);
					randomPosBB[2] = randomPosBB[2] + Math.RandomFloatInclusive(-10, 10);
					randomPosBB[1] = GetGame().SurfaceY(randomPosBB[0], randomPosBB[2]);
					bbitem = ItemBase.Cast(GetGame().CreateObjectEx(BaseBuildingLoot.GetRandomElement(), randomPosBB, ECE_PLACE_ON_SURFACE));

					if (!bbitem)
						continue;

					bbitem.PlaceOnSurface();
					Print("[SMM] Survivor Mission Plane Crash - dropped: " + bbitem.GetType());
				}
			}
			else
			if (MissionType == 2) // Military guns & ammo
			{
				//Spawn containers 
				int milLoadout = 0;
				EntityAI weapon;
				for (int i5 = 0; i5 < ContainerSpawns.Count(); i5++)
				{
					MissionObject = ItemBase.Cast(GetGame().CreateObject("Zen_Mission_WoodenCrate", CrashedC130.ModelToWorld(ContainerSpawns.Get(i5))));

					//Spawn selected loadout items in mission object
					if (milLoadout == 0)
					{
						int gunType = Math.RandomIntInclusive(0, 3);
						if (gunType == 0 || gunType == 1)
						{
							weapon = MissionObject.GetInventory().CreateInInventory("SVD");
							weapon.GetInventory().CreateAttachment("PSO1Optic");
							weapon.GetInventory().CreateAttachment("Mag_SVD_10Rnd");
						}
						else
						if (gunType == 2)
						{
							weapon = MissionObject.GetInventory().CreateInInventory("M4A1");
							weapon.GetInventory().CreateAttachment("ACOGOptic");
							weapon.GetInventory().CreateAttachment("Mag_STANAG_30Rnd");
							weapon.GetInventory().CreateAttachment("M4_Suppressor");
						}
						else 
						if (gunType == 3)
						{
							weapon = MissionObject.GetInventory().CreateInInventory("ExpansionSatchel");
						}

						SpawnItemRandom(MissionObject, "M67Grenade", 2, 0.5);
						SpawnItemRandom(MissionObject, "RGD5Grenade", 2, 0.5);
						SpawnItemRandom(MissionObject, "Zen_AirStrikeSmokeGrenade", 2, 0.5);
						SpawnAmmoRandomStack(MissionObject, "Ammo_00buck", 10, 0.5);
						SpawnAmmoRandomStack(MissionObject, "Ammo_12gaSlug", 10, 0.5);
						SpawnAmmoRandomStack(MissionObject, "Ammo_22", 10, 0.5);
						SpawnAmmoRandomStack(MissionObject, "Ammo_357", 10, 0.5);
						SpawnAmmoRandomStack(MissionObject, "Ammo_380", 10, 0.5);
						SpawnAmmoRandomStack(MissionObject, "Ammo_9x39", 10, 0.5);
					}
					else
					if (milLoadout == 1)
					{
						SpawnItemRandom(MissionObject, "WeaponCleaningKit");
						SpawnItemRandom(MissionObject, MissionSettings.OldPhotos.GetRandomElement());
						SpawnAmmoRandomStack(MissionObject, "Ammo_308WinTracer", 10, 0.5);
						SpawnAmmoRandomStack(MissionObject, "Ammo_545x39Tracer", 10, 0.5);
						SpawnAmmoRandomStack(MissionObject, "Ammo_556x45Tracer", 10, 0.5);
						SpawnAmmoRandomStack(MissionObject, "Ammo_762x39Tracer", 10, 0.5);
						SpawnAmmoRandomStack(MissionObject, "Ammo_762x54Tracer", 10, 0.5);
						SpawnAmmoRandomStack(MissionObject, "Ammo_9x39AP", 10, 0.5);
						SpawnItemRandom(MissionObject, "HuntingOptic", 1, 0.5);
						SpawnItemRandom(MissionObject, "PistolSuppressor");
						SpawnAmmoRandomStack(MissionObject, "Ammo_45ACP", 10, 0.5);
					}

					Print("[SMM] Plane Military Mission rewards spawned in reward container" + i5 + ". Randomly selected loadout was " + milLoadout + ".");

					//Insert mission container into mission objects list
					m_MissionObjects.Insert(MissionObject);
					milLoadout++;
				}

				ItemBase militem;
				for (int i6 = 0; i6 < 6; i6++)
				{
					if (Math.RandomFloat01() < 0.25) // 75% chance to spawn sweet loot
						continue;

					vector randomPosMil = CrashedC130.GetPosition();
					randomPosMil[0] = randomPosMil[0] + Math.RandomFloatInclusive(-5, 5);
					randomPosMil[2] = randomPosMil[2] + Math.RandomFloatInclusive(-5, 5);
					randomPosMil[1] = GetGame().SurfaceY(randomPosMil[0], randomPosMil[2]);
					militem = ItemBase.Cast(GetGame().CreateObjectEx(MilitaryLoot.GetRandomElement(), randomPosMil, ECE_PLACE_ON_SURFACE));

					if (!militem)
						continue

					militem.PlaceOnSurface();
					Print("[SMM] Survivor Mission Plane Crash - dropped: " + militem.GetType());
				}
			}

		Print("[SMM] Survivor Mission " + m_selectedMission + " :: " + m_MissionName + " ...mission deployed!");
	}

	void SpawnItemRandom(ItemBase container, string type, int count = 1, float chance = 0.9)
	{
		for (int i = 0; i < count; i++)
		{
			if (Math.RandomFloat01() < chance)
			{
				container.GetInventory().CreateInInventory(type);
			}
		}
	}

	void SpawnAmmoRandomStack(ItemBase container, string type, int count = 1, float chance = 0.9)
	{
		for (int i = 0; i < count; i++)
		{
			if (Math.RandomFloat01() < chance)
			{
				Ammunition_Base ammo = Ammunition_Base.Cast(container.GetInventory().CreateInInventory(type));
				if (ammo)
				{
					ammo.ServerSetAmmoCount(Math.RandomIntInclusive(5, ammo.GetAmmoMax()));
					if (Math.RandomFloat01() < 0.25)
						ammo.SetHealth(70);
				}
			}
		}
	}

	void SpawnAIs()
	{
		//Spawn infected pilot
		vector InfectedPos = CrashedC130.ModelToWorld("3 0 -9");
		m_MissionAIs.Insert(GetGame().CreateObject("ZmbM_CommercialPilotOld_Olive", InfectedPos, false, true));
		DayZInfected InfectedSurvivor = DayZInfected.Cast(m_MissionAIs[0]);
		InfectedSurvivor.GetInventory().CreateAttachment("ZSh3PilotHelmet_Green");
		InfectedSurvivor.GetInventory().CreateAttachment("UKAssVest_Olive");
		InfectedSurvivor.GetInventory().CreateInInventory("Glock19");
		InfectedSurvivor.GetInventory().CreateInInventory("Mag_Glock_15Rnd");
		InfectedSurvivor.GetInventory().CreateInInventory("Battery9V");
		InfectedSurvivor.GetInventory().CreateInInventory("Battery9V");
		InfectedSurvivor.GetInventory().CreateInInventory("Battery9V");
		InfectedSurvivor.SetHealth("", "", 15);

		// Spawn zombie trigger
		ZenMissionZombiesTrigger trigger = ZenMissionZombiesTrigger.Cast(GetGame().CreateObjectEx("ZenMissionZombiesTrigger", m_MissionPosition, ECE_CREATEPHYSICS));
		if (trigger)
		{
			trigger.SetupZenMissionZombiesTrigger(MISSION_TIME, 300, ZombieCount, InfectedTypes, 25);
		}
	}

	void ObjDespawn()
	{
		//Despawn nothing
	}

	void MissionFinal(PlayerBase player)
	{	
		ZenModLogger.Log("PlaneCrash completed.", "missions");
		//When player enters last mission target zone	

		bool madeWolf = false;
		int randomX = Math.RandomFloatInclusive(-200, 200);
		int randomY = Math.RandomFloatInclusive(-200, 200);

		if (randomX < 0) // Minimum 50m distance
			randomX -= 50;
		else
			randomX += 50;

		if (randomY < 0)
			randomY -= 50;
		else
			randomY += 50;

		vector xyzRand;

		vector hitPosition, hitNormal;
		vector to = xyzRand + "0 25 0";
		Object hitObject;
		float hitFraction;
		PhxInteractionLayers collisionLayerMask = PhxInteractionLayers.ITEM_LARGE | PhxInteractionLayers.BUILDING | PhxInteractionLayers.VEHICLE;

		// Spawn an infected wolf randomly
		if (Math.RandomFloat01() <= 0.5)
		{
			xyzRand = CrashedC130.GetPosition();
			xyzRand[0] = xyzRand[0] + randomX; // Minimum range 100-250m, maximum range -250 - +250m on top of that
			xyzRand[2] = xyzRand[2] + randomY;
			xyzRand[1] = GetGame().SurfaceY(xyzRand[0], xyzRand[2]); // change to find surface

			// Check if wolf is NOT inside a building or object
			if (!DayZPhysics.RayCastBullet(xyzRand, to, collisionLayerMask, null, hitObject, hitPosition, hitNormal, hitFraction))
			{
				GetGame().CreateObject("Animal_CanisPestis", xyzRand, false, true, true);
				madeWolf = true;
			}
		}

		// Spawn a blood bear randomly
		if (!madeWolf)
		{
			xyzRand = CrashedC130.GetPosition();
			xyzRand[0] = xyzRand[0] + randomX; // Minimum range 100-250m, maximum range -250 - +250m on top of that
			xyzRand[2] = xyzRand[2] + randomY;
			xyzRand[1] = GetGame().SurfaceY(xyzRand[0], xyzRand[2]); // change to find surface

			// Check if wolf is NOT inside a building or object
			if (!DayZPhysics.RayCastBullet(xyzRand, to, collisionLayerMask, null, hitObject, hitPosition, hitNormal, hitFraction))
			{
				GetGame().CreateObject("bear_blood", xyzRand, false, true, true);
			}
		}

		//Finish mission
		MissionSettings.TargetFoundMsg = "You have found the cargo!";
		MissionSettings.FinishingMsg = "Thank you for securing the cargo survivor.\nYou seem reliable, and we could really use the help. Stay tuned to this radio channel if you're willing to help us.\nIt's going to be a hard fight to win back Livonia from this plague.\nOver and out.";
		m_RewardsSpawned = true;
		m_MsgNum = -1;
		m_MsgChkTime = m_MissionTime + MsgDlyFinish;
	}

	void PlayerChecks(PlayerBase player)
	{

	};

	void UpdateBots(float dt)
	{
		// no bots
	}

	bool DeployMission()
	{	
		//When first player enters the mission zone (primary/secondary)
		if (m_MissionPosition && m_MissionPosition != "0 0 0")
		{
			//Call spawners	
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).Call(this.SpawnObjects);
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).Call(this.SpawnAIs);
			return true;
		}
		else
		{
			Print("[SMM] ERROR : Mission position was rejected or doesn't exist. MissionPosition is NULL!");
			return false;
		}
	}

	/*void SendDebugMsg(string msg)
	{
		array<Man> players = new array<Man>;
		GetGame().GetWorld().GetPlayerList(players);
		for (int x = 0; x < players.Count(); x++)
		{
			PlayerBase pb = PlayerBase.Cast(players.Get(x));
			if (pb)
			{
				pb.Zen_SendMessage(msg);
			}
		}
	}*/
}

