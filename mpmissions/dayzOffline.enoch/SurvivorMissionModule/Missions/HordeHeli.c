class HordeHeliMission extends SurvivorMissions
{
	//Mission related entities
	ItemBase MissionObject;
	EntityAI CrashedHeli;
	vector m_airdropLocation;
	
	//Mission parameters
	static const int MISSION_TIME = 3600; // 1 hour
	int MsgDlyFinish = 300;					//seconds, message delay time after player has finished mission
	int HordeDensity = 50;					//infected, spawned in circle
	
	//Mission containers
	ref array<string> InfectedTypes = new ref array<string>;

	//Mission variables 
	bool IsExtended() return false;
	
	void HordeHeliMission()
	{
		ZenModLogger.Log("[STARTED] HordeHeliMission started @ " + m_MissionPosition, "missions");
		
		//Mission mission timeout
		m_MissionTimeout = MISSION_TIME;			//seconds, mission duration time

		m_MissionPosition[1] = GetGame().SurfaceY(m_MissionPosition[0], m_MissionPosition[2]);
		m_airdropLocation = m_MissionPosition;
		
		//Mission zones
		m_MissionZoneOuterRadius = 500.0;	//meters (!Do not set lower than 200m), mission activation distance
		m_MissionZoneInnerRadius = 5.0;	//meters (!Do not set outside of 1-5m), mission finishing distance to target object
				
		//Mission informant
		m_MissionInformant = MissionSettings.BadBoss;
		
		int x_coord = Math.Round(m_MissionPosition[0]);
		int z_coord = Math.Round(m_MissionPosition[2]);
		
		x_coord += Math.RandomIntInclusive(-150, 150);
		z_coord += Math.RandomIntInclusive(-150, 150);
		
		string coords = " (Approximate Coordinates: " + x_coord.ToString() + " / " + z_coord.ToString() + ")";
		
		//Set mission messages
		MissionSettings.StartingMsg = "Can anybody read me? Over?";
		m_MissionMessage1 = "Once again, we have foiled your plans, " + MissionSettings.GoodBoss + ". The military helicopter you sent to scout our location has been destroyed.";
		m_MissionMessage2 = "The pilot was alive, but we were able to remedy that situation rather quickly. It seems a single man is no match for a horde of hungry infected.";
		m_MissionMessage3 = "For any remaining survivors out there, feel free to scavange the wreckage for supplies. The crash site is swarming with infected\n\n** " + m_MissionLocationDir + " of " + m_MissionLocation + coords + " **\n\nGood luck, if anyone is stupid enough to take up the challenge.";

		//Infected types
		//Male												//Female
		InfectedTypes.Insert("ZmbM_CitizenASkinny_Brown");	InfectedTypes.Insert("ZmbF_JournalistNormal_White");
		InfectedTypes.Insert("ZmbM_priestPopSkinny");		InfectedTypes.Insert("ZmbF_Clerk_Normal_White");
		InfectedTypes.Insert("ZmbM_HermitSkinny_Beige");	InfectedTypes.Insert("ZmbF_CitizenANormal_Blue");
		InfectedTypes.Insert("ZmbM_CitizenBFat_Red");		InfectedTypes.Insert("ZmbF_CitizenBSkinny");
		InfectedTypes.Insert("ZmbM_FishermanOld_Green");	InfectedTypes.Insert("ZmbF_HikerSkinny_Grey");
		InfectedTypes.Insert("ZmbM_HunterOld_Autumn");		InfectedTypes.Insert("ZmbF_SurvivorNormal_Orange");
		InfectedTypes.Insert("ZmbM_CitizenBFat_Blue");		InfectedTypes.Insert("ZmbF_HikerSkinny_Green");
		InfectedTypes.Insert("ZmbM_MotobikerFat_Black");	InfectedTypes.Insert("ZmbF_JoggerSkinny_Green");
		InfectedTypes.Insert("ZmbM_JoggerSkinny_Red");		InfectedTypes.Insert("ZmbF_SkaterYoung_Striped");
		InfectedTypes.Insert("ZmbM_MechanicSkinny_Grey");	InfectedTypes.Insert("ZmbF_BlueCollarFat_Red");
		InfectedTypes.Insert("ZmbM_HandymanNormal_Green");	InfectedTypes.Insert("ZmbF_MechanicNormal_Beige");
		InfectedTypes.Insert("ZmbM_HeavyIndustryWorker");	InfectedTypes.Insert("ZmbF_PatientOld");
		InfectedTypes.Insert("ZmbM_Jacket_black");			InfectedTypes.Insert("ZmbF_ShortSkirt_beige");
		InfectedTypes.Insert("ZmbM_Jacket_stripes");		InfectedTypes.Insert("ZmbF_VillagerOld_Red");
		InfectedTypes.Insert("ZmbM_HikerSkinny_Blue");		InfectedTypes.Insert("ZmbF_JoggerSkinny_Red");
		InfectedTypes.Insert("ZmbM_HikerSkinny_Yellow");	InfectedTypes.Insert("ZmbF_MilkMaidOld_Beige");
		InfectedTypes.Insert("ZmbM_PolicemanFat");			InfectedTypes.Insert("ZmbF_VillagerOld_Green");
		InfectedTypes.Insert("ZmbM_PatrolNormal_Summer");	InfectedTypes.Insert("ZmbF_ShortSkirt_yellow");
		InfectedTypes.Insert("ZmbM_JoggerSkinny_Blue");		InfectedTypes.Insert("ZmbF_NurseFat");
		InfectedTypes.Insert("ZmbM_VillagerOld_White");		InfectedTypes.Insert("ZmbF_PoliceWomanNormal");
		InfectedTypes.Insert("ZmbM_SkaterYoung_Brown");		InfectedTypes.Insert("ZmbF_HikerSkinny_Blue");
		InfectedTypes.Insert("ZmbM_MechanicSkinny_Green");	InfectedTypes.Insert("ZmbF_ParamedicNormal_Green");
		InfectedTypes.Insert("ZmbM_DoctorFat");				InfectedTypes.Insert("ZmbF_JournalistNormal_Red");
		InfectedTypes.Insert("ZmbM_PatientSkinny");			InfectedTypes.Insert("ZmbF_SurvivorNormal_White");
		InfectedTypes.Insert("ZmbM_ClerkFat_Brown");		InfectedTypes.Insert("ZmbF_JoggerSkinny_Brown");
		InfectedTypes.Insert("ZmbM_ClerkFat_White");		InfectedTypes.Insert("ZmbF_MechanicNormal_Grey");
		InfectedTypes.Insert("ZmbM_Jacket_magenta");		InfectedTypes.Insert("ZmbF_BlueCollarFat_Green");
		InfectedTypes.Insert("ZmbM_PolicemanSpecForce");	InfectedTypes.Insert("ZmbF_DoctorSkinny");
	}
	
	void ~HordeHeliMission()
	{
		ZenModLogger.Log("[DESTROY] HordeHeliMission class destroyed.", "missions");
		
		//Despawn all remaining mission objects
		if ( m_MissionObjects )
		{	
			Print("[SMM] Despawning "+ m_MissionObjects.Count() +" mission objects from old mission...");				
			for ( int i = 0; i < m_MissionObjects.Count(); i++ )
			{ 
				if ( !m_MissionObjects.Get(i) ) continue;
				else
				{
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

		if (CrashedHeli)
			CrashedHeli.SetLifetime(3);
	}
	
	void SpawnObjects()
	{		
		// Crashed helicopter/hummer
		vector heliPos = m_MissionPosition;
		heliPos[0] = heliPos[0] + 10;
		heliPos[2] = heliPos[2] - 10;
		CrashedHeli = EntityAI.Cast(GetGame().CreateObject("ZenMission_Wreck_Heli", heliPos));

		if (CrashedHeli)
		{
			CrashedHeli.PlaceOnSurface();
			CrashedHeli.SetLifetime(MISSION_TIME);
			
			// Align to surface
			vector transform[4];
			CrashedHeli.GetTransform(transform);
			vector ground_position, ground_dir; 
			int component;
			DayZPhysics.RaycastRV(transform[3], transform[3] + transform[1] * -100, ground_position, ground_dir, component, null, null, null, false, true);
			vector surface_normal = GetGame().SurfaceGetNormal(ground_position[0], ground_position[2]);
			vector local_ori = CrashedHeli.GetDirection();
			transform[0] = surface_normal * local_ori;
			transform[1] = surface_normal;
			transform[2] = surface_normal * (local_ori * vector.Up);
			CrashedHeli.SetTransform(transform);
			CrashedHeli.Update();
		}
		
		//Mission object is pilot bag
		MissionObject = ItemBase.Cast( GetGame().CreateObject("AliceBag_Camo", m_MissionPosition ) );
		MissionObject.PlaceOnSurface();
		//MissionObject.SetPosition( m_MissionPosition + "0 0.2 0" );
		
		//Get random loadout 			
		int selectedLoadout = Math.RandomIntInclusive(0,11);	//!Change randomization limit after adding new loadouts!
		
		//Spawn selected loadout items in mission object
		EntityAI weapon;
								
		if (selectedLoadout == 0)
		{
			weapon = MissionObject.GetInventory().CreateInInventory("M4A1_Green");
			if (weapon)
			{
				weapon.GetInventory().CreateAttachment("M4_RISHndgrd_Green");
				weapon.GetInventory().CreateAttachment("M4_MPBttstck");
				weapon.GetInventory().CreateAttachment("M4_Suppressor");
				weapon.GetInventory().CreateAttachment("ACOGOptic");
			}
			
				//weapon.GetInventory().CreateAttachment("M4_T3NRDSOptic");
			MissionObject.GetInventory().CreateInInventory("Mag_STANAG_30Rnd");
			MissionObject.GetInventory().CreateInInventory("Ammo_556x45");
			MissionObject.GetInventory().CreateInInventory("Ammo_556x45");
			MissionObject.GetInventory().CreateInInventory("HuntingKnife");
			MissionObject.GetInventory().CreateInInventory("BakedBeansCan");
			MissionObject.GetInventory().CreateInInventory("Canteen");
			MissionObject.GetInventory().CreateInInventory("Battery9VLithium");
		}
		if (selectedLoadout == 1)
		{
			weapon = MissionObject.GetInventory().CreateInInventory("SVD");
			if (weapon)
			{
				weapon.GetInventory().CreateAttachment("PSO11Optic");
			}
				//weapon.GetInventory().CreateAttachment("PSO1Optic");
				//weapon.GetInventory().CreateAttachment("KazuarOptic");
			MissionObject.GetInventory().CreateInInventory("Mag_SVD_10Rnd");
			MissionObject.GetInventory().CreateInInventory("Mag_SVD_10Rnd");
			MissionObject.GetInventory().CreateInInventory("Ammo_762x54");
			MissionObject.GetInventory().CreateInInventory("Ammo_762x54");
			MissionObject.GetInventory().CreateInInventory("CanOpener");
			MissionObject.GetInventory().CreateInInventory("PeachesCan");
			MissionObject.GetInventory().CreateInInventory("WaterBottle"); 
			MissionObject.GetInventory().CreateInInventory("Battery9VLithium");
		}
		if (selectedLoadout == 2)
		{
			weapon = MissionObject.GetInventory().CreateInInventory("AKM");
			if (weapon)
			{
				weapon.GetInventory().CreateAttachment("AK_RailHndgrd_Green");
				weapon.GetInventory().CreateAttachment("AK_Suppressor");
				weapon.GetInventory().CreateAttachment("AK_PlasticBttstck_Green");
				weapon.GetInventory().CreateAttachment("PSO1Optic");
			}
				//weapon.GetInventory().CreateAttachment("KobraOptic");
			MissionObject.GetInventory().CreateInInventory("Mag_AKM_30Rnd");
			MissionObject.GetInventory().CreateInInventory("Ammo_762x39");
			MissionObject.GetInventory().CreateInInventory("Ammo_762x39");
			MissionObject.GetInventory().CreateInInventory("KitchenKnife");
			MissionObject.GetInventory().CreateInInventory("SardinesCan");
			MissionObject.GetInventory().CreateInInventory("Canteen");
			MissionObject.GetInventory().CreateInInventory("Battery9VLithium");
		}
		if (selectedLoadout == 3)
		{
			weapon = MissionObject.GetInventory().CreateInInventory("FAL");
			if (weapon)
			{
				weapon.GetInventory().CreateAttachment("Fal_OeBttstck");
				weapon.GetInventory().CreateAttachment("M4_Suppressor");
				weapon.GetInventory().CreateAttachment("M68Optic");
			}
				//weapon.GetInventory().CreateAttachment("ReflexOptic");
			MissionObject.GetInventory().CreateInInventory("Mag_FAL_20Rnd");
			MissionObject.GetInventory().CreateInInventory("Mag_FAL_20Rnd");
			MissionObject.GetInventory().CreateInInventory("WaterBottle");
			MissionObject.GetInventory().CreateInInventory("MilitaryBelt");	
			MissionObject.GetInventory().CreateInInventory("M18SmokeGrenade_Yellow");	
			MissionObject.GetInventory().CreateInInventory("TacticalBaconCan");
			MissionObject.GetInventory().CreateInInventory("SteakKnife");
		}	
		if (selectedLoadout == 4)
		{
			weapon = MissionObject.GetInventory().CreateInInventory("SKS");
			if (weapon)
			{
				weapon.GetInventory().CreateAttachment("PUScopeOptic");
				weapon.GetInventory().CreateAttachment("SKS_Bayonet");
			}
			MissionObject.GetInventory().CreateInInventory("Ammo_762x39");
			MissionObject.GetInventory().CreateInInventory("Ammo_762x39");
			weapon = MissionObject.GetInventory().CreateInInventory("FNX45");
			if (weapon)
			{
				weapon.GetInventory().CreateAttachment("PistolSuppressor");
				weapon.GetInventory().CreateAttachment("FNP45_MRDSOptic");
				weapon.GetInventory().CreateAttachment("TLRLight");
			}
			MissionObject.GetInventory().CreateInInventory("Mag_FNX45_15Rnd");
			MissionObject.GetInventory().CreateInInventory("Ammo_45ACP");
			MissionObject.GetInventory().CreateInInventory("WaterBottle");			
			MissionObject.GetInventory().CreateInInventory("Battery9VLithium");
		}
		if (selectedLoadout == 5)
		{			
			weapon = MissionObject.GetInventory().CreateInInventory("Winchester70");
			if (weapon)
			{
				weapon.GetInventory().CreateAttachment("HuntingOptic");		
			}
			MissionObject.GetInventory().CreateInInventory("Ammo_308Win");
			MissionObject.GetInventory().CreateInInventory("Ammo_308Win");
		
			weapon = MissionObject.GetInventory().CreateInInventory("CZ75");
			if (weapon)
			{
				weapon.GetInventory().CreateAttachment("PistolSuppressor");
				weapon.GetInventory().CreateAttachment("FNP45_MRDSOptic");
			}
			MissionObject.GetInventory().CreateInInventory("Mag_CZ75_15Rnd");
			MissionObject.GetInventory().CreateInInventory("Ammo_45ACP");
					
			weapon = MissionObject.GetInventory().CreateInInventory("NVGHeadstrap");
			if (weapon)
			{
				weapon.GetInventory().CreateInInventory("NVGoggles");
			}
			MissionObject.GetInventory().CreateInInventory("Battery9VLithium");
			MissionObject.GetInventory().CreateInInventory("PsilocybeMushroom");
			MissionObject.GetInventory().CreateInInventory("WaterBottle");	
			MissionObject.GetInventory().CreateInInventory("SpaghettiCan");
			MissionObject.GetInventory().CreateInInventory("StoneKnife");
			MissionObject.GetInventory().CreateInInventory("M67Grenade");					
		}
		if (selectedLoadout == 6)
		{			
			weapon = MissionObject.GetInventory().CreateInInventory("UMP45");
			if (weapon)
			{
				weapon.GetInventory().CreateAttachment("M68Optic");
				weapon.GetInventory().CreateAttachment("PistolSuppressor");		
			}				
			MissionObject.GetInventory().CreateInInventory("Mag_UMP_25Rnd");
			MissionObject.GetInventory().CreateInInventory("Mag_UMP_25Rnd");
			MissionObject.GetInventory().CreateInInventory("Ammo_45ACP");
			MissionObject.GetInventory().CreateInInventory("Battery9VLithium");
			MissionObject.GetInventory().CreateInInventory("Cannabis");
			MissionObject.GetInventory().CreateInInventory("CannabisSeedsPack");
			MissionObject.GetInventory().CreateInInventory("WaterBottle");	
			MissionObject.GetInventory().CreateInInventory("TunaCan");
			MissionObject.GetInventory().CreateInInventory("RDG5Grenade");					
		}	
		if (selectedLoadout == 7)
		{			
			weapon = MissionObject.GetInventory().CreateInInventory("VSS");
			if (weapon)
			{
				weapon.GetInventory().CreateAttachment("PSO11Optic");
			}
				//weapon.GetInventory().CreateAttachment("PistolSuppressor");			
			MissionObject.GetInventory().CreateInInventory("Mag_VSS_10Rnd");
			MissionObject.GetInventory().CreateInInventory("Mag_VSS_10Rnd");
			MissionObject.GetInventory().CreateInInventory("AmmoBox_9x39_20Rnd");
			MissionObject.GetInventory().CreateInInventory("Battery9VLithium");
			MissionObject.GetInventory().CreateInInventory("GardenLime");
			MissionObject.GetInventory().CreateInInventory("CannabisSeedsPack");
			MissionObject.GetInventory().CreateInInventory("WaterBottle");	
			MissionObject.GetInventory().CreateInInventory("SardinesCan");
			MissionObject.GetInventory().CreateInInventory("M18SmokeGrenade_Green");					
		}
		if (selectedLoadout == 8)
		{			
			weapon = MissionObject.GetInventory().CreateInInventory("MP5K");
			if (weapon)
			{
				weapon.GetInventory().CreateAttachment("MP5_RailHndgrd");
				weapon.GetInventory().CreateAttachment("MP5k_StockBttstck");
				weapon.GetInventory().CreateAttachment("M68Optic");
				weapon.GetInventory().CreateAttachment("PistolSuppressor");		
			}				
			MissionObject.GetInventory().CreateInInventory("Mag_MP5_30Rnd");
			MissionObject.GetInventory().CreateInInventory("Mag_MP5_30Rnd");
			MissionObject.GetInventory().CreateInInventory("AmmoBox_9x19_25rnd");
			MissionObject.GetInventory().CreateInInventory("GP5GasMask");
			MissionObject.GetInventory().CreateInInventory("NBCGlovesGray");
			MissionObject.GetInventory().CreateInInventory("WaterBottle");	
			MissionObject.GetInventory().CreateInInventory("SpaghettiCan");
			MissionObject.GetInventory().CreateInInventory("M18SmokeGrenade_Red");
			MissionObject.GetInventory().CreateInInventory("Battery9VLithium");
			MissionObject.GetInventory().CreateInInventory("Battery9VLithium");
			MissionObject.GetInventory().CreateInInventory("Battery9VLithium");				
		}
		if (selectedLoadout == 9)
		{			
			weapon = MissionObject.GetInventory().CreateInInventory("AK74");
			if (weapon)
			{
				weapon.GetInventory().CreateAttachment("AK_RailHndgrd");
				weapon.GetInventory().CreateAttachment("AK74_WoodBttstck");	
				weapon.GetInventory().CreateAttachment("KashtanOptic");
				weapon.GetInventory().CreateAttachment("AK_Suppressor");	
			}				
			MissionObject.GetInventory().CreateInInventory("Mag_AK74_30Rnd");
			MissionObject.GetInventory().CreateInInventory("Mag_AK74_30Rnd");
			MissionObject.GetInventory().CreateInInventory("Headtorch_Grey");
			MissionObject.GetInventory().CreateInInventory("NBCBootsGray");
			MissionObject.GetInventory().CreateInInventory("Canteen");	
			MissionObject.GetInventory().CreateInInventory("TacticalBaconCan");
			MissionObject.GetInventory().CreateInInventory("Tomato");
			MissionObject.GetInventory().CreateInInventory("Battery9VLithium");
			MissionObject.GetInventory().CreateInInventory("Battery9VLithium");				
		}
		if (selectedLoadout == 10)
		{			
			weapon = MissionObject.GetInventory().CreateInInventory("AKS74U");
			if (weapon)
			{
				weapon.GetInventory().CreateAttachment("AKS74U_Bttstck");		
			}				
			MissionObject.GetInventory().CreateInInventory("Mag_AK74_30Rnd");
			MissionObject.GetInventory().CreateInInventory("Mag_AK74_30Rnd");
			MissionObject.GetInventory().CreateInInventory("M67Grenade");
			MissionObject.GetInventory().CreateInInventory("M67Grenade");
			MissionObject.GetInventory().CreateInInventory("Matchbox");
			MissionObject.GetInventory().CreateInInventory("Canteen");	
			MissionObject.GetInventory().CreateInInventory("PortableGasStove");
			MissionObject.GetInventory().CreateInInventory("SmallGasCanister");
			MissionObject.GetInventory().CreateInInventory("Battery9VLithium");
			MissionObject.GetInventory().CreateInInventory("Battery9VLithium");
			MissionObject.GetInventory().CreateInInventory("Battery9VLithium");			
		}
		if (selectedLoadout == 11)
		{			
			weapon = MissionObject.GetInventory().CreateInInventory("Glock19");
			if (weapon)
			{
				weapon.GetInventory().CreateAttachment("PistolSuppressor");		
			}				
			MissionObject.GetInventory().CreateInInventory("Mag_Glock_15Rnd");
			MissionObject.GetInventory().CreateInInventory("Mag_Glock_15Rnd");
			MissionObject.GetInventory().CreateInInventory("FishingRod");
			MissionObject.GetInventory().CreateInInventory("Carp");
			MissionObject.GetInventory().CreateInInventory("Hook");
			MissionObject.GetInventory().CreateInInventory("Worm");
			MissionObject.GetInventory().CreateInInventory("CombatKnife");
			MissionObject.GetInventory().CreateInInventory("FieldShovel");
			MissionObject.GetInventory().CreateInInventory("Canteen");	
			MissionObject.GetInventory().CreateInInventory("MackerelFilletMeat");
			MissionObject.GetInventory().CreateInInventory("Battery9VLithium");
			MissionObject.GetInventory().CreateInInventory("Battery9VLithium");
			MissionObject.GetInventory().CreateInInventory("Battery9VLithium");			
		}
			
		Print("[SMM] Mission rewards spawned in reward container. Randomly selected loadout was "+ selectedLoadout +"." );
		
		MissionObject.SetLifetime(MISSION_TIME);
		Print("[SMM] Survivor Mission "+ m_selectedMission +" :: "+ m_MissionName +" ...mission deployed!");
	}
	
	void SpawnAIs()
	{	
		//Spawn pilot
		DayZInfected InfectedPilot = DayZInfected.Cast( GetGame().CreateObject( "ZmbM_CommercialPilotOld_Olive" , m_MissionPosition , false , true ));
			InfectedPilot.SetPosition( m_MissionPosition );
		//InfectedPilot.PlaceOnSurface();
			InfectedPilot.GetInventory().CreateAttachment("Zen_NavHelmet");
			InfectedPilot.GetInventory().CreateInInventory("M67Grenade");
			InfectedPilot.GetInventory().CreateInInventory("CanOpener");
			InfectedPilot.GetInventory().CreateInInventory("BandageDressing");
			InfectedPilot.GetInventory().CreateInInventory("PeachesCan");
			InfectedPilot.GetInventory().CreateInInventory("Canteen");
			InfectedPilot.GetInventory().CreateAttachment("UKAssVest_Olive");
			InfectedPilot.GetInventory().CreateInInventory("PersonalRadio");
			InfectedPilot.GetInventory().CreateInInventory("Battery9VLithium");
			InfectedPilot.GetInventory().CreateInInventory("Battery9VLithium");
			InfectedPilot.GetInventory().CreateInInventory("Battery9VLithium");
			if (Math.RandomFloat01() <= 0.5)
				InfectedPilot.GetInventory().CreateInInventory("PunchedCard");
			else
				InfectedPilot.GetInventory().CreateInInventory("InjectorExpBoost2x");
			
		//Pilot is dead
		InfectedPilot.SetHealth("","",0);
		InfectedPilot.SetLifetime(MISSION_TIME);
		m_MissionAIs.Insert( InfectedPilot );

		// Spawn zombie trigger
		ZenMissionZombiesTrigger trigger = ZenMissionZombiesTrigger.Cast(GetGame().CreateObjectEx("ZenMissionZombiesTrigger", m_MissionPosition, ECE_CREATEPHYSICS));
		if (trigger)
		{
			trigger.SetupZenMissionZombiesTrigger(MISSION_TIME, 300, HordeDensity, InfectedTypes, 25);
		}
	}

	void ObjDespawn() 
	{	
		//nothing to despawn
	}
	
	void MissionFinal(PlayerBase player)
	{	
		ZenModLogger.Log("HordeHeli completed.", "missions");
		//When player enters last mission target zone	

		//Alert infected 
		for ( int j = 1 ; j < m_MissionAIs.Count(); j++ )
		{
			DayZInfected Zed = DayZInfected.Cast( m_MissionAIs.Get(j));
			if (Zed && Zed.IsAlive())
			{
				DayZInfectedCommandMove moveCommandZ = Zed.GetCommand_Move();
				
				if (moveCommandZ)
					moveCommandZ.SetIdleState(2);
			}
		}
		
		//Finish mission
		m_RewardsSpawned = true;
		m_MsgNum = -1;
		m_MsgChkTime = 10;
		m_MissionInformant = MissionSettings.GoodBoss;
		MissionSettings.FinishingMsg = "Thank you for trying to help rescue our pilot, survivor. It's a shame they didn't make it. We've dispatched an airdrop as a reward. If you're still listening to this frequency " + MissionSettings.BadBoss + ", sleep with one eye open. Your days are numbered.";

		// Call in airdrop
		ExpansionMissionModule.s_Instance.CallAirdrop(m_MissionPosition);
		//GetAirdropBase().EOnCallAirdrop(true, m_airdropLocation, player);
	}
	
	void PlayerChecks( PlayerBase player )
	{
	}
		
	void UpdateBots(float dt)
	{
	}
	
	bool DeployMission()
	{
		if ( m_MissionPosition && m_MissionPosition != "0 0 0" )
		{
			//Call spawners	
			GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).Call( this.SpawnObjects );
			GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater( this.SpawnAIs, 1000, false );
			return true;		
		}
		else 
		{
			Print("[SMM] ERROR : Mission position was rejected or doesn't exist. MissionPosition is NULL!");
			return false;
		}
	}
}

