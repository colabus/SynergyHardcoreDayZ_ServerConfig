class CrocodileFishMission extends SurvivorMissions
{
	//Mission related entities 
	Zen_Mission_MediumTent MissionTent;

	//Mission parameters
	static const int MISSION_TIME = 3600;	// 1 hour
	int MsgDlyFinish = 300;					//seconds, message delay time after player has finished mission
	
	//Mission containers
	ref array<vector> InfectedSpawns = new array<vector>;
	ref array<string> InfectedTypes = new array<string>;

	bool IsExtended() return false;

	void CrocodileFishMission()
	{
		ZenModLogger.Log("[STARTED] CrocodileFishMission started @ " + m_MissionPosition, "mission");
		
		//Mission mission timeout
		m_MissionTimeout = MISSION_TIME;			//seconds, mission duration time
		
		//Mission zones
		m_MissionZoneOuterRadius = 250.0;	//meters (!Do not set lower than 200m), mission activation distance
		m_MissionZoneInnerRadius = 5.0;		//meters (!Do not set outside of 1-5m), mission finishing distance to target object

		//Mission informant
		m_MissionInformant = "Lost Child";
		MissionSettings.StartingMsg = "Is anybody out there?";

		int x_coord = Math.Round(m_MissionPosition[0]);
		int z_coord = Math.Round(m_MissionPosition[2]);
		
		x_coord += Math.RandomIntInclusive(-300, 300);
		z_coord += Math.RandomIntInclusive(-300, 300);
		
		string coords = " (Approximate Coordinates: " + x_coord.ToString() + " / " + z_coord.ToString() + ")";
		
		//Set mission messages
		if (IsWinter())
			m_MissionMessage1 = "Please help me! My parents were killed by polar bears. We were fishing and we got swarmed! The bears ate their faces and there is blood and guts everywhere! I'm so scared!";
		else 
			m_MissionMessage1 = "Please help me! My parents were killed by crocodiles. We were fishing and we got swarmed! The crocodiles ate their faces and there is blood and guts everywhere! I'm so scared!";
        
        m_MissionMessage2 = "They're trying to get into our tent to eat me too! Please come quickly! I don't want to die like my parents.";
		m_MissionMessage3 = "We were fishing at a lake near \n** " + coords + " **\nHelp me!";
		
		if (!IsWinter())
		{
			//Crocodiles
			InfectedTypes.Insert("Animal_Crocodile");
			InfectedTypes.Insert("Animal_Crocodile_Green");
			InfectedTypes.Insert("Animal_Crocodile_Brown");
			InfectedTypes.Insert("Animal_Crocodile_Grey");
		}
		else 
		{
			InfectedTypes.Insert("Animal_ZenUrsusMaritimus");
			InfectedTypes.Insert("Animal_ZenUrsusMaritimusRed");
		}
	}
	
	void ~CrocodileFishMission()
	{
		ZenModLogger.Log("[DESTROY] CrocodileFishMission class destroyed.", "mission");
		
		//Despawn all remaining mission objects
		if ( m_MissionObjects )
		{	
			Print("[SMM] Despawning "+ m_MissionObjects.Count() +" mission objects from old mission...");				
			for ( int i = 0; i < m_MissionObjects.Count(); i++ )
			{
				if ( !m_MissionObjects.Get(i) ) continue;
				else
				{
					//Delete Object clientside first
					if ( m_MissionObjects.Get(i).GetType() == "ClutterCutterFireplace" )
					GetGame().RemoteObjectDelete( m_MissionObjects.Get(i) );				
					
					//Delete Object serverside
					GetGame().ObjectDelete( m_MissionObjects.Get(i) );
				}		
			}
			m_MissionObjects.Clear();
		}
		
		//Despawn mission AI's
		if ( m_MissionAIs )
		{
			if ( m_MissionAIs.Count() > 0 )
			{
				Print("[SMM] Despawning "+ m_MissionAIs.Count() +" mission AI's from old mission...");
				for ( int k = 0; k < m_MissionAIs.Count(); k++ )
				{
					GetGame().ObjectDelete( m_MissionAIs.Get(k) );
				}
				m_MissionAIs.Clear();			
			}
			else Print("[SMM] No mission AI's to despawn.");
		}
		
		//Delete PlayersInZone list & reset container takeaway
		if ( m_PlayersInZone )	m_PlayersInZone.Clear();
		if ( m_ContainerWasTaken ) m_ContainerWasTaken = false;
	}
	
	void SpawnObjects()
	{
		//Spawn & pitch tent		
		MissionTent = Zen_Mission_MediumTent.Cast(GetGame().CreateObject("Zen_Mission_MediumTent", m_MissionPosition));
		MissionTent.Pitch(true, true);
		MissionTent.PlaceOnSurface();
		MissionTent.SetLifetime(MISSION_TIME);
		GetGame().CreateObject("LargeTentClutterCutter", MissionTent.GetPosition(), false);

		// Spawn tent loot
		string lootType = CRATE_TYPES.GetRandomElement();
		ExpansionLootContainer container;
		for (int i = 0; i < GetExpansionSettings().GetAirdrop().Containers.Count(); i++)
		{
			container = GetExpansionSettings().GetAirdrop().Containers[i];
			if (container.Container == lootType)
				break;
		}

		ExpansionLootSpawner.SpawnLoot(MissionTent, container.Loot, container.ItemCount);

		//Get random loadout 
		int selectedLoadout = Math.RandomIntInclusive(0,5);

		//Spawn selected loadout items in mission object
		/*EntityAI weapon;
		if (selectedLoadout == 3)
		{
			weapon = MissionObject.GetInventory().CreateInInventory("Scar_Tanbrown");
			MissionObject.GetInventory().CreateInInventory("Mag_STANAG_30Rnd");
			MissionObject.GetInventory().CreateInInventory("Mag_STANAG_30Rnd");
			MissionObject.GetInventory().CreateInInventory("M4_Suppressor");
			MissionObject.GetInventory().CreateInInventory("ACOGOptic");
			MissionObject.GetInventory().CreateInInventory("FNX45");
			MissionObject.GetInventory().CreateInInventory("Mag_FNX45_15Rnd");
			MissionObject.GetInventory().CreateInInventory("Mag_FNX45_15Rnd");
			MissionObject.GetInventory().CreateInInventory("Ammo_45ACP");
			MissionObject.GetInventory().CreateInInventory("FNP45_MRDSOptic");
			MissionObject.GetInventory().CreateInInventory("PistolSuppressor");
			MissionObject.GetInventory().CreateInInventory("ZenRandomAmmoBox");
			MissionObject.GetInventory().CreateInInventory("Battery9V");
		}*/

		//Fireplace
		vector CampfirePosition = m_MissionPosition;
		vector CampfireOrientation;
		vector CampFireDir = MissionTent.GetOrientation();
		float CampFireDist = 4;
			
		if ( CampFireDir[0] < 0 )	
			CampFireDir[0] = 360 + CampFireDir[0];

		CampfirePosition [0] = m_MissionPosition [0] - Math.Sin( CampFireDir[0] * Math.DEG2RAD ) * CampFireDist;
		CampfirePosition [2] = m_MissionPosition [2] - Math.Cos( CampFireDir[0] * Math.DEG2RAD ) * CampFireDist;
		FireplaceBase MissionCampfire = FireplaceBase.Cast( GetGame().CreateObject( "Zen_EternalFireplace", CampfirePosition ) );
		CampfireOrientation = MissionCampfire.GetOrientation();
		MissionCampfire.Synchronize();
		MissionCampfire.GetInventory().CreateAttachment("Firewood");
		MissionCampfire.GetInventory().CreateAttachment("WoodenStick");
		MissionCampfire.GetInventory().CreateAttachment("Rag");
		MissionCampfire.StartFire( true );
		MissionCampfire.SetLifetimeMax(m_MissionTimeout);
		MissionCampfire.SetLifetime(m_MissionTimeout);
		
		//Cluttercutter fireplace
		GetGame().CreateObject("ClutterCutterFireplace", MissionCampfire.GetPosition(), false);
			
		Print("[SMM] Mission rewards spawned in reward container. Randomly selected loadout was " + selectedLoadout + ".");	
		Print("[SMM] Survivor Mission "+ m_selectedMission +" :: "+ m_MissionName +" ...mission deployed!");
	}

	static const ref array<string> CRATE_TYPES =
	{
		"ExpansionAirdropContainer",
		"ExpansionAirdropContainer_Medical",
		"ExpansionAirdropContainer_Basebuilding"
	};

	static const ref array<string> MALE_PARENTS =
	{
		"SurvivorM_Mirek",
		"SurvivorM_Boris",
		"SurvivorM_Cyril",
		"SurvivorM_Denis",
		"SurvivorM_Elias",
		"SurvivorM_Francis",
		"SurvivorM_Guo",
		"SurvivorM_Hassan",
		"SurvivorM_Indar",
		"SurvivorM_Jose",
		"SurvivorM_Kaito",
		"SurvivorM_Lewis",
		"SurvivorM_Manua",
		"SurvivorM_Niki",
		"SurvivorM_Oliver",
		"SurvivorM_Peter",
		"SurvivorM_Quinn",
		"SurvivorM_Rolf",
		"SurvivorM_Seth",
		"SurvivorM_Taiki"
	};

	static const ref array<string> FEMALE_PARENTS =
	{
		"SurvivorF_Eva",
		"SurvivorF_Frida",
		"SurvivorF_Gabi",
		"SurvivorF_Helga",
		"SurvivorF_Irena",
		"SurvivorF_Judy",
		"SurvivorF_Keiko",
		"SurvivorF_Linda",
		"SurvivorF_Maria",
		"SurvivorF_Naomi",
		"SurvivorF_Baty"
	};

	static const ref array<string> HATS = 
	{
		"FlatCap_Blue",
		"BeanieHat_Beige",
		"BeanieHat_Black",
		"BeanieHat_Blue",
		"BeanieHat_Brown",
		"BeanieHat_Green",
		"BeanieHat_Grey",
		"BeanieHat_Pink",
		"BeanieHat_Red",
		"CowboyHat_Brown",
		"CowboyHat_black",
		"CowboyHat_darkBrown",
		"CowboyHat_green",
		"BaseballCap_Beige",
		"BaseballCap_Black",
		"BaseballCap_Blue",
		"BaseballCap_CMMG_Black",
		"BaseballCap_CMMG_Pink",
		"BaseballCap_Camo",
		"BaseballCap_Olive",
		"BaseballCap_Pink",
		"BaseballCap_Red"
	};

	static const ref array<string> BAGS = 
	{
		"MountainBag_Blue",
		"MountainBag_Green",
		"MountainBag_Orange",
		"MountainBag_Red",
		"HuntingBag",
		"ImprovisedBag",
		"TaloonBag_Blue",
		"TaloonBag_Green",
		"TaloonBag_Orange",
		"TaloonBag_Violet",
		"Zen_HuntingBag_Black",
		"HipPack_Black",
		"HipPack_Green",
		"HipPack_Party"
	};

	static const ref array<string> VESTS = 
	{
		"HuntingVest",
		"LeatherStorageVest_Black",
		"Zen_HuntingVest_Black"
	};

	static const ref array<string> SHIRTS =
	{
		"Shirt_BlueCheck",
		"Shirt_BlueCheckBright",
		"Shirt_GreenCheck",
		"Shirt_PlaneBlack",
		"Shirt_RedCheck",
		"Shirt_WhiteCheck",
		"TShirt_Beige",
		"TShirt_Black",
		"TShirt_Blue",
		"TShirt_Green",
		"TShirt_Grey",
		"TShirt_OrangeWhiteStripes",
		"TShirt_Red",
		"TShirt_RedBlackStripes",
		"TShirt_White",
		"HikingJacket_Black",
		"HikingJacket_Blue",
		"HikingJacket_Green",
		"HikingJacket_Red"
	};

	static const ref array<string> PANTS =
	{
		"Jeans_Black",
		"Jeans_Blue",
		"Jeans_BlueDark",
		"Jeans_Brown",
		"Jeans_Green",
		"Jeans_Grey"
	};

	static const ref array<string> SHOES =
	{
		"AthleticShoes_Blue",
		"AthleticShoes_Black",
		"AthleticShoes_Brown",
		"AthleticShoes_Green",
		"AthleticShoes_Grey",
		"HikingBootsLow_Beige",
		"HikingBootsLow_Black",
		"HikingBootsLow_Blue",
		"HikingBootsLow_Grey",
		"Sneakers_Black",
		"Sneakers_Gray",
		"Sneakers_Green",
		"Sneakers_Red",
		"Sneakers_White",
		"HikingBoots_Black",
		"HikingBoots_Brown",
		"JoggingShoes_Black",
		"JoggingShoes_Blue",
		"JoggingShoes_Red",
		"JoggingShoes_Violet",
		"JoggingShoes_White"
	};

	static const ref array<string> RANDOM_LOOT = 
	{
		"Zen_Canteen_Black",
		"Zen_Dye_Black",
		"Zen_Dye_Green",
		"Spraycan_Black",
		"Spraycan_Green",
		"NailBox",
		"ExpansionCodeLock",
		"ZenRandomAmmoBox",
		"ZenTreasure_RandomPhoto",
		"CigarettePack_Chernamorka",
		"CigarettePack_Merkur",
		"CigarettePack_Partyzanka",
		"Vodka",
		"BeerCan_Corona",
		"BeerCan_VB",
		"BeerCan_XXXX",
		"Kvass",
		"Fraochan",
		"BlackGroat",
		"AuldBroon",
		"Laboureuse",
		"Boilermaker",
		"PilgrimsPale",
		"Handfasted",
		"CreuseWit",
		"Forgeronne",
		"Caoranach",
		"BakedBeansCan_Opened",
		"InjectorExpBoost2x",
		"CanOpener",
		"PeachesCan",
		"Canteen",
		"Battery9VLithium"
	};

	static const ref array<string> HUMAN_REMAINS = 
	{
		"HumanSteakMeat",
		"Guts"
	};

	static const ref array<string> BLOOD_DECALS = 
	{
		"BloodDecal",
		"BloodDecal1",
		"BloodDecal2",
		"BloodDecal3",
		"BloodDecal4"
	};

	void SpawnDeadParents(bool female)
	{
		string deadParent = MALE_PARENTS.GetRandomElement();
		if (female)
			deadParent = FEMALE_PARENTS.GetRandomElement();

		vector InfectedPos = MissionTent.ModelToWorld( "0 0 -6" );
		if (female)
			InfectedPos = MissionTent.ModelToWorld( "-6 0 0" );

		SurvivorBase DeadSurvivor = SurvivorBase.Cast(GetGame().CreateObject(deadParent, InfectedPos, false, true));
		if (!DeadSurvivor)
			return;

		if (Math.RandomFloat01() < 0.75)
			DeadSurvivor.GetInventory().CreateAttachment(HATS.GetRandomElement());
		if (Math.RandomFloat01() < 0.75)
			DeadSurvivor.GetInventory().CreateAttachment(BAGS.GetRandomElement());
		if (Math.RandomFloat01() < 0.75)
			DeadSurvivor.GetInventory().CreateAttachment(VESTS.GetRandomElement());
		DeadSurvivor.GetInventory().CreateAttachment(SHIRTS.GetRandomElement());
		DeadSurvivor.GetInventory().CreateAttachment(PANTS.GetRandomElement());
		DeadSurvivor.GetInventory().CreateAttachment(SHOES.GetRandomElement());
		
		int randGuns = Math.RandomIntInclusive(0, 10);

		EntityAI weapon;
		if (randGuns == 0)
		{
			weapon = DeadSurvivor.GetInventory().CreateInInventory("M4A1_Green");
				weapon.GetInventory().CreateAttachment("M4_RISHndgrd_Green");
				weapon.GetInventory().CreateAttachment("M4_MPBttstck");
				weapon.GetInventory().CreateAttachment("ACOGOptic");
			DeadSurvivor.GetInventory().CreateInInventory("Mag_STANAG_30Rnd");
			DeadSurvivor.GetInventory().CreateInInventory("Mag_STANAG_30Rnd");
			DeadSurvivor.GetInventory().CreateInInventory("M4_T3NRDSOptic");
			DeadSurvivor.GetInventory().CreateInInventory("Ammo_556x45");
			DeadSurvivor.GetInventory().CreateInInventory("Ammo_556x45");
		}
		if (randGuns == 4)
		{ 
			weapon = DeadSurvivor.GetInventory().CreateInInventory("FNX45");
				weapon.GetInventory().CreateAttachment("FNP45_MRDSOptic");
			DeadSurvivor.GetInventory().CreateInInventory("AmmoBox_45ACP_25rnd");
			DeadSurvivor.GetInventory().CreateInInventory("AmmoBox_45ACP_25rnd");
			
		}
		if (randGuns == 5)
		{
			weapon = DeadSurvivor.GetInventory().CreateInInventory("PP19");
			DeadSurvivor.GetInventory().CreateInInventory("Mag_PP19_64Rnd");
		}
		if (randGuns == 6)
		{
			weapon = DeadSurvivor.GetInventory().CreateInInventory("Magnum");
			DeadSurvivor.GetInventory().CreateInInventory("AmmoBox_357_20Rnd");
			DeadSurvivor.GetInventory().CreateInInventory("AmmoBox_357_20Rnd");
			DeadSurvivor.GetInventory().CreateInInventory("WeapomCleaningKit");
		}
		if (randGuns == 7)
		{
			weapon = DeadSurvivor.GetInventory().CreateInInventory("SawedoffB95");
				weapon.GetInventory().CreateAttachment("HuntingOptic");
			DeadSurvivor.GetInventory().CreateInInventory("AmmoBox_308Win_20Rnd");
			DeadSurvivor.GetInventory().CreateInInventory("WeapomCleaningKit");
		}
		if (randGuns == 8)
		{
			weapon = DeadSurvivor.GetInventory().CreateInInventory("Derringer_Pink");
			DeadSurvivor.GetInventory().CreateInInventory("WeapomCleaningKit");
		}
		if (randGuns == 9)
		{
			weapon = DeadSurvivor.GetInventory().CreateInInventory("Derringer_Black");
			DeadSurvivor.GetInventory().CreateInInventory("AmmoBox_357_20Rnd");
			DeadSurvivor.GetInventory().CreateInInventory("WeapomCleaningKit");
		}
		if (randGuns == 10)
		{
			weapon = DeadSurvivor.GetInventory().CreateInInventory("MakarovIJ70");
				weapon.GetInventory().CreateAttachment("PistolSuppressor");
			DeadSurvivor.GetInventory().CreateInInventory("AmmoBox_380_35rnd");
			DeadSurvivor.GetInventory().CreateInInventory("AmmoBox_380_35rnd");
			DeadSurvivor.GetInventory().CreateInInventory("WeapomCleaningKit");
		}
		
		int lootCount = Math.RandomIntInclusive(3, 5);
		for (int i = 0; i < lootCount; i++)
		{
			DeadSurvivor.GetInventory().CreateInInventory(RANDOM_LOOT.GetRandomElement());
		}

		if (Math.RandomFloat01() < 0.5)
			DeadSurvivor.GetHumanInventory().CreateInHands("FishingRod");
		else
			DeadSurvivor.GetInventory().CreateInInventory("FishingRod");


		vector ori = DeadSurvivor.GetOrientation();
		ori[1] = ori[1] + Math.RandomFloatInclusive(0, 45);
		DeadSurvivor.SetOrientation(ori);
		DeadSurvivor.SetHealth(10);
		SpawnCroc(DeadSurvivor.GetPosition(), 1);

		Object blood = GetGame().CreateObject(BLOOD_DECALS.GetRandomElement(), DeadSurvivor.GetPosition(), false, false, false);
		if (blood)
		{
			blood.PlaceOnSurface();
			blood.SetPosition(blood.GetPosition() + "0 0.05 0");
		}

		m_MissionObjects.Insert(GetGame().CreateObject("LargeTentClutterCutter", DeadSurvivor.GetPosition(), false));
	}
	
	void SpawnAIs()
	{
		// Spawn parents
		SpawnDeadParents(false);
		SpawnDeadParents(true);

		int i;
		vector xyzRand;

		//Spawn infected
		ZenMissionZombiesTrigger trigger = ZenMissionZombiesTrigger.Cast(GetGame().CreateObjectEx("ZenMissionZombiesTrigger", m_MissionPosition, ECE_CREATEPHYSICS));
		if (trigger)
		{
			if (IsWinter())
				trigger.SetupZenMissionZombiesTrigger(MISSION_TIME, 100, 4, InfectedTypes, 10);
			else
				trigger.SetupZenMissionZombiesTrigger(MISSION_TIME, 100, 6, InfectedTypes, 10);
		}

		// Spawn human meat and guts nearby
		ItemBase item;
		for (i = 0; i < 12; i++)
		{
			xyzRand = m_MissionPosition;
			xyzRand[0] = xyzRand[0] + Math.RandomFloatInclusive(-10, 10);
			xyzRand[2] = xyzRand[2] + Math.RandomFloatInclusive(-10, 10);
			xyzRand[1] = GetGame().SurfaceY(xyzRand[0], xyzRand[2]);

			item = ItemBase.Cast(GetGame().CreateObject(HUMAN_REMAINS.GetRandomElement(), xyzRand, false, false, false));
			if (item)
			{
				item.PlaceOnSurface();
				item.SetLifetime(MISSION_TIME);
			}
		}

		// Spawn blood
		Object blood;
		for (i = 0; i < 10; i++)
		{
			xyzRand = m_MissionPosition;
			xyzRand[0] = xyzRand[0] + Math.RandomFloatInclusive(-10, 10);
			xyzRand[2] = xyzRand[2] + Math.RandomFloatInclusive(-10, 10);
			xyzRand[1] = GetGame().SurfaceY(xyzRand[0], xyzRand[2]);

			blood = GetGame().CreateObject(BLOOD_DECALS.GetRandomElement(), xyzRand, false, false, false);
			if (blood)
			{
				blood.PlaceOnSurface();
				blood.SetPosition(blood.GetPosition() + "0 0.05 0");
			}
		}

		item = ItemBase.Cast(GetGame().CreateObject("PersonalRadio", m_MissionPosition, false, false, false));
		if (item)
		{
			item.PlaceOnSurface();
			item.SetLifetime(MISSION_TIME);
			item.GetInventory().CreateAttachment("Battery9V");
		}
	}

	void SpawnCroc(vector pos, int offset)
	{
		vector xyzRand	= pos;
		xyzRand[0]		= xyzRand[0] + Math.RandomFloatInclusive(-offset, offset);
		xyzRand[2]		= xyzRand[2] + Math.RandomFloatInclusive(-offset, offset);
		xyzRand[1]		= GetGame().SurfaceY(xyzRand[0], xyzRand[2]);

		AnimalBase croc = AnimalBase.Cast(GetGame().CreateObject(InfectedTypes.GetRandomElement(), xyzRand, false, true));
		if (croc)
		{
			croc.m_MissionAnimal = true;
			m_MissionAIs.Insert(croc);
		}
	}
	
	void ObjDespawn() 
	{	
		if (!m_MissionObjects)
			return;
		
		//Despawn all mission objects at mission timeout except those retains until next mission
		for ( int i = 0; i < m_MissionObjects.Count(); i++ )
		{
			if ( !m_MissionObjects.Get(i))
				continue;
			
			//Exception: Fireplace & ClutterCutterFireplace will remain
			if ( m_MissionObjects.Get(i).GetType() == "Fireplace" || m_MissionObjects.Get(i).GetType() == "ClutterCutterFireplace" )	
			{
				Print("[SMM] "+ m_MissionObjects.Get(i).GetType() +" was excluded from pre-deletion.");
				continue;
			}
			
			//Delete Object clientside first
			if ( m_MissionObjects.Get(i).GetType() == "MediumTentClutterCutter" ) GetGame().RemoteObjectDelete( m_MissionObjects.Get(i) );
			
			//Delete Object serverside
			GetGame().ObjectDelete( m_MissionObjects.Get(i) );
		}
	}
	
	void MissionFinal(PlayerBase player)
	{
		ZenModLogger.Log("CrocodileFishMission completed.", "mission");
		
		//Finish mission
		m_RewardsSpawned = true;
		m_MsgNum = -1;
		m_MsgChkTime = m_MissionTime + MsgDlyFinish;			
	}
	
	void PlayerChecks( PlayerBase player )
	{
	}
		
	void UpdateBots(float dt)
	{	
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
}
