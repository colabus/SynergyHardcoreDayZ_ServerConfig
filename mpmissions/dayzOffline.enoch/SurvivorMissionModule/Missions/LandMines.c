class LandMinesMission extends SurvivorMissions
{
	//Mission related entities
	ItemBase MissionObject;
	
	//Mission parameters
	static const int MISSION_RADIUS_METERS = 10;
	static const int MISSION_TIME = 2700;
	static const int LANDMINE_COUNT_OUTER = 50;
	static const int LANDMINE_COUNT_INNER = 200;
	static const float LANDMINE_OUTER_RADIUS = 20;
	static const float LANDMINE_INNER_RADIUS = 15;
	int MsgDlyFinish = 300;

	//Mission variables 
	bool IsExtended()
	{
		return false;
	}
	
	void LandMinesMission()
	{
		ZenModLogger.Log("[STARTED] LandMinesMission started @ " + m_MissionPosition, "missions");
		
		//Mission mission timeout
		m_MissionTimeout = MISSION_TIME;			//seconds, mission duration time

		m_MissionPosition = ZenFunctions.GetRandomPointInCircle(m_MissionPosition, MISSION_RADIUS_METERS);
		m_MissionPosition[1] = GetGame().SurfaceY(m_MissionPosition[0], m_MissionPosition[2]);
		
		//Mission zones
		m_MissionZoneOuterRadius = 250.0;	//meters (!Do not set lower than 200m), mission activation distance
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
		m_MissionMessage1 = "Are you there, " + MissionSettings.GoodBoss + "? We've set up a little game you might like to play.";
		m_MissionMessage2 = "You sent a scout to our location a few days ago, I'm sure you've noticed him missing by now.";
		m_MissionMessage3 = "Well, if you want him back, you'll find him tied up in the center of a minefield at\n\n** " + coords + " **\n\nWe left him there with all his valuable gear, so you might want to check on him soon.";
	}
	
	void ~LandMinesMission()
	{
		ZenModLogger.Log("[DESTROY] LandMinesMission class destroyed.", "missions");
		
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
		
		//Delete PlayersInZone list & reset container takeaway
		if ( m_PlayersInZone )	m_PlayersInZone.Clear();
		if ( m_ContainerWasTaken ) m_ContainerWasTaken = false;
	}
	
	void SpawnObjects()
	{
		//Mission object is pilot bag
		MissionObject = ItemBase.Cast( GetGame().CreateObject("AliceBag_Camo", m_MissionPosition ) );
		MissionObject.PlaceOnSurface();
		
		//Get random loadout 			
		int selectedLoadout = Math.RandomIntInclusive(0,11);	//!Change randomization limit after adding new loadouts!
		
		//Spawn selected loadout items in mission object
		EntityAI weapon;
								
		if (selectedLoadout == 0)
		{
			weapon = MissionObject.GetInventory().CreateInInventory("M4A1_Green");
				weapon.GetInventory().CreateAttachment("M4_RISHndgrd_Green");
				weapon.GetInventory().CreateAttachment("M4_MPBttstck");
				weapon.GetInventory().CreateAttachment("M4_Suppressor");
				weapon.GetInventory().CreateAttachment("ACOGOptic");
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
				weapon.GetInventory().CreateAttachment("PSO11Optic");
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
				weapon.GetInventory().CreateAttachment("AK_RailHndgrd_Green");
				weapon.GetInventory().CreateAttachment("AK_Suppressor");
				weapon.GetInventory().CreateAttachment("AK_PlasticBttstck_Green");
				weapon.GetInventory().CreateAttachment("PSO1Optic");
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
				weapon.GetInventory().CreateAttachment("Fal_OeBttstck");
				weapon.GetInventory().CreateAttachment("M4_Suppressor");
				weapon.GetInventory().CreateAttachment("M68Optic");
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
				weapon.GetInventory().CreateAttachment("PUScopeOptic");
				weapon.GetInventory().CreateAttachment("SKS_Bayonet");
			MissionObject.GetInventory().CreateInInventory("Ammo_762x39");
			MissionObject.GetInventory().CreateInInventory("Ammo_762x39");
			weapon = MissionObject.GetInventory().CreateInInventory("FNX45");
				weapon.GetInventory().CreateAttachment("PistolSuppressor");
				weapon.GetInventory().CreateAttachment("FNP45_MRDSOptic");
				weapon.GetInventory().CreateAttachment("TLRLight");
			MissionObject.GetInventory().CreateInInventory("Mag_FNX45_15Rnd");
			MissionObject.GetInventory().CreateInInventory("Ammo_45ACP");
			MissionObject.GetInventory().CreateInInventory("WaterBottle");			
			MissionObject.GetInventory().CreateInInventory("Battery9VLithium");
		}
		if (selectedLoadout == 5)
		{			
			weapon = MissionObject.GetInventory().CreateInInventory("Winchester70");
				weapon.GetInventory().CreateAttachment("HuntingOptic");		
			MissionObject.GetInventory().CreateInInventory("Ammo_308Win");
			MissionObject.GetInventory().CreateInInventory("Ammo_308Win");
		
			weapon = MissionObject.GetInventory().CreateInInventory("CZ75");
				weapon.GetInventory().CreateAttachment("PistolSuppressor");
				weapon.GetInventory().CreateAttachment("FNP45_MRDSOptic");
			MissionObject.GetInventory().CreateInInventory("Mag_CZ75_15Rnd");
			MissionObject.GetInventory().CreateInInventory("Ammo_45ACP");
					
			weapon = MissionObject.GetInventory().CreateInInventory("NVGHeadstrap");
				weapon.GetInventory().CreateInInventory("NVGoggles");
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
				weapon.GetInventory().CreateAttachment("M68Optic");
				weapon.GetInventory().CreateAttachment("PistolSuppressor");			
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
				weapon.GetInventory().CreateAttachment("PSO11Optic");
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
				weapon.GetInventory().CreateAttachment("MP5_RailHndgrd");
				weapon.GetInventory().CreateAttachment("MP5k_StockBttstck");
				weapon.GetInventory().CreateAttachment("M68Optic");
				weapon.GetInventory().CreateAttachment("PistolSuppressor");			
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
				weapon.GetInventory().CreateAttachment("AK_RailHndgrd");
				weapon.GetInventory().CreateAttachment("AK74_WoodBttstck");	
				weapon.GetInventory().CreateAttachment("KashtanOptic");
				weapon.GetInventory().CreateAttachment("AK_Suppressor");			
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
				weapon.GetInventory().CreateAttachment("AKS74U_Bttstck");			
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
				weapon.GetInventory().CreateAttachment("PistolSuppressor");			
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

		ItemBase casinoChips = ItemBase.Cast(MissionObject.GetInventory().CreateInInventory("ZenCasinoChips_Red"));
		if (casinoChips)
			casinoChips.SetQuantity(Math.RandomIntInclusive(5, 250));

		// Spawn landmines 
		SpawnLandmines();
			
		Print("[SMM] Mission rewards spawned in reward container. Randomly selected loadout was "+ selectedLoadout +"." );
		
		MissionObject.SetLifetime(MISSION_TIME);
		Print("[SMM] Survivor Mission "+ m_selectedMission +" :: "+ m_MissionName +" ...mission deployed!");
	}
	
	void SpawnLandmines()
	{
		//Spawn pilot
		DayZInfected InfectedPilot = DayZInfected.Cast( GetGame().CreateObject("ZmbM_CommercialPilotOld_Olive", m_MissionPosition, false, true));
			InfectedPilot.SetPosition( m_MissionPosition );
			InfectedPilot.GetInventory().CreateInInventory("M67Grenade");
			InfectedPilot.GetInventory().CreateInInventory("CanOpener");
			InfectedPilot.GetInventory().CreateInInventory("BandageDressing");
			InfectedPilot.GetInventory().CreateInInventory("PeachesCan_Opened");
			InfectedPilot.GetInventory().CreateInInventory("Canteen");
			InfectedPilot.GetInventory().CreateAttachment("UKAssVest_Olive");
			InfectedPilot.GetInventory().CreateInInventory("PersonalRadio");
			InfectedPilot.GetInventory().CreateInInventory("Battery9VLithium");
			InfectedPilot.GetInventory().CreateInInventory("Battery9VLithium");
			InfectedPilot.GetInventory().CreateInInventory("Battery9VLithium");

		if (Math.RandomFloat01() < 0.5)
			InfectedPilot.GetInventory().CreateInInventory("PunchedCard");
		else
			InfectedPilot.GetInventory().CreateInInventory("InjectorExpBoost5x");

		if (Math.RandomFloat01() < 0.75)
			InfectedPilot.GetInventory().CreateInInventory("ExpansionCircuitBoard_Airdrop");
		else
			InfectedPilot.GetInventory().CreateInInventory("Expansion_Ammo_FlareSupplyRed");
			
		//Pilot is dead
		InfectedPilot.SetHealth("","",0);
		InfectedPilot.SetLifetime(MISSION_TIME);

		// Outer Landmines
		LandMineTrap itsAtrap;
		int i;

		for (i = 0; i < LANDMINE_COUNT_OUTER; i++)
		{
			itsAtrap = LandMineTrap.Cast(GetGame().CreateObject("LandMineTrap", ZenFunctions.GetRandomPointInCircle(m_MissionPosition, LANDMINE_OUTER_RADIUS, LANDMINE_INNER_RADIUS)));
			if (itsAtrap != NULL)
			{
				GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(itsAtrap.StartActivate, Math.RandomFloatInclusive(100, 1000));
				itsAtrap.SetLifetimeMax(MISSION_TIME);
				itsAtrap.SetLifetime(MISSION_TIME);
				itsAtrap.isMissionObject = true;
			}
		}

		// Inner Landmines 
		for (i = 0; i < LANDMINE_COUNT_INNER; i++)
		{
			itsAtrap = LandMineTrap.Cast(GetGame().CreateObject("LandMineTrap", ZenFunctions.GetRandomPointInCircle(m_MissionPosition, LANDMINE_INNER_RADIUS, 0)));
			if (itsAtrap != NULL)
			{
				GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(itsAtrap.StartActivate, Math.RandomFloatInclusive(100, 1000));
				itsAtrap.SetLifetimeMax(MISSION_TIME);
				itsAtrap.SetLifetime(MISSION_TIME);
				itsAtrap.isMissionObject = true;
			}
		}

		itsAtrap = LandMineTrap.Cast(GetGame().CreateObject("LandMineTrap", ZenFunctions.GetRandomPointInCircle(m_MissionPosition, LANDMINE_INNER_RADIUS)));
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(itsAtrap.StartActivate, 100);
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(itsAtrap.Asplode, 1000);

	}

	void ObjDespawn() 
	{	
		//nothing to despawn
	}
	
	void MissionFinal(PlayerBase player)
	{	
		ZenModLogger.Log("LandMines completed.", "missions");
		//When player enters last mission target zone	
		
		//Finish mission
		m_RewardsSpawned = true;
		m_MsgNum = -1;
		m_MsgChkTime = 10;
		MissionSettings.FinishingMsg = "";
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
			return true;		
		}
		else 
		{
			Print("[SMM] ERROR : Mission position was rejected or doesn't exist. MissionPosition is NULL!");
			return false;
		}
	}
}

