class CampMission extends SurvivorMissions
{
	//Mission related entities 
	TentBase MissionObject;
	FireplaceBase MissionCampfire;
	Object cc_fireplace;
	Object cc_mtent;
	Grenade_Base BoobyTrap; 
	
	//Mission parameters
	static const int MISSION_TIME = 3600;	// 1 hour
	int MsgDlyFinish = 300;					//seconds, message delay time after player has finished mission
	
	//Mission containers
	ref array<vector> InfectedSpawns = new array<vector>;
	ref array<string> InfectedTypes = new array<string>;

	//Mission variables 
	string SurvivorName;		
	
	bool IsExtended() return false;

	void CampMission()
	{
		ZenModLogger.Log("[STARTED] CampMission started @ " + m_MissionPosition, "missions");
		
		//Mission mission timeout
		m_MissionTimeout = MISSION_TIME;			//seconds, mission duration time
		
		//Mission zones
		m_MissionZoneOuterRadius = 170.0;	//meters (!Do not set lower than 200m), mission activation distance
		m_MissionZoneInnerRadius = 3.0;		//meters (!Do not set outside of 1-5m), mission finishing distance to target object

		//Mission informant
		m_MissionInformant = MissionSettings.GoodBoss;
	
		//Mission person names
		SurvivorName = "Pietrek";
		bool SurvivorMale = Math.RandomIntInclusive(0, 1) == 1;

		if (SurvivorMale)
		{
			SurvivorName = MissionSettings.MaleSurvivorNames.GetRandomElement();
		}
		else
		{
			SurvivorName = MissionSettings.FemaleSurvivorNames.GetRandomElement();
		}

		int x_coord = Math.Round(m_MissionPosition[0]);
		int z_coord = Math.Round(m_MissionPosition[2]);
		
		x_coord += Math.RandomIntInclusive(-300, 300);
		z_coord += Math.RandomIntInclusive(-300, 300);
		
		string coords = " (Approximate Coordinates: " + x_coord.ToString() + " / " + z_coord.ToString() + ")";
		
		//Set mission messages
        m_MissionMessage1 = "I just received an emergency call from one of our soldiers. Their unit was decimated in a fight with bandits, and it seems there was only one survivor.";
        m_MissionMessage2 = "It seems despite the advanced weaponry their unit was carrying, it was no match for these bandits. They were on a recon patrol surveying various ruined towns across Livonia, looking for survivors.";
		m_MissionMessage3 = "Their last known position was at a camp somewhere\n** " + m_MissionLocationDir + " of " + m_MissionLocation + coords + " **\nPlease investigate the camp if you can, we never leave anyone behind!";
		
			
		//Infected spawnpoints
		InfectedSpawns.Insert("-10.5186 0 25.0269");
		InfectedSpawns.Insert("24.9775 0 -10.4146");
		InfectedSpawns.Insert("-30.1726 0 -6.2729");
		InfectedSpawns.Insert("-20.9209 0 4.6636");
		InfectedSpawns.Insert("15.0283 0 -10.3276");
		InfectedSpawns.Insert("7.2461 0 30.5884");
		InfectedSpawns.Insert("-20.6855 0 5.9956");
		InfectedSpawns.Insert("-20.6855 0 -5.9956");
		InfectedSpawns.Insert("20.6855 0 5.9956");
		InfectedSpawns.Insert("-10.6855 0 5.9956");
		
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
	
	void ~CampMission()
	{
		ZenModLogger.Log("[DESTROY] CampMission class destroyed.", "missions");
		
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
		// Clean up place from droped items before new tent spawns 
		bool ItemsAtGround = false; 
		
		GetGame().GetObjectsAtPosition(m_MissionPosition, 4.0, m_ObjectList, NULL);
		for ( int i = 0 ; i < m_ObjectList.Count(); i++ )
		{ 
			Object FoundObject = m_ObjectList.Get(i);
			if ( FoundObject.IsItemBase() )
			{
				ItemsAtGround = true;
				Print("[SMM] BeforeSpawnCleanUp :: Object  " + FoundObject.ToString() + " at new mission position was deleted.");				
				GetGame().ObjectDelete( FoundObject );
			}
		}
		//...and in case move tent pos a bit
		if ( ItemsAtGround )
		{
			float x = Math.RandomFloatInclusive( 1.5 , 3.0 );
			float y = Math.RandomFloatInclusive( 1.5 , 3.0 );
			int Dice = Math.RandomIntInclusive( 0, 9);
			if ( Dice > 4 ) x *= -1.0;
			Dice = Math.RandomIntInclusive( 0, 9);
			if ( Dice < 5 ) y *= -1.0;
			vector NewPosVector = { x, 0, y };
			m_MissionPosition += NewPosVector;
			Print("[SMM] BeforeSpawnCleanUp :: Items on the ground detected. Tent position predictively was moved a bit.");
		}
		
		//Spawn & pitch tent		
		MissionObject = TentBase.Cast( GetGame().CreateObject( "Zen_Mission_MediumTent", m_MissionPosition ) );
		MissionObject.Pitch( true , true );
		MissionObject.PlaceOnSurface();
		MissionObject.SetLifetime(MISSION_TIME);
		MissionObject.SetLifetimeMax(MISSION_TIME);
		
		//Get random loadout 
		int selectedLoadout = Math.RandomIntInclusive(0,9);	//!change randomization limit after adding new loadouts!	

		//Spawn selected loadout items in mission object
		EntityAI weapon;
				
		if (selectedLoadout == 0)
		{
			weapon = MissionObject.GetInventory().CreateInInventory("M4A1_Green");
				weapon.GetInventory().CreateAttachment("M4_RISHndgrd_Green");
				weapon.GetInventory().CreateAttachment("M4_MPBttstck");
				weapon.GetInventory().CreateAttachment("ACOGOptic");
				weapon.GetInventory().CreateAttachment("M4_Suppressor");
			MissionObject.GetInventory().CreateInInventory("Mag_STANAG_30Rnd");
			MissionObject.GetInventory().CreateInInventory("Mag_STANAG_30Rnd");
			MissionObject.GetInventory().CreateInInventory("M4_T3NRDSOptic");
			MissionObject.GetInventory().CreateInInventory("Ammo_556x45");
			MissionObject.GetInventory().CreateInInventory("Ammo_556x45");
			MissionObject.GetInventory().CreateInInventory("CanOpener");
			MissionObject.GetInventory().CreateInInventory("PeachesCan");
			MissionObject.GetInventory().CreateInInventory("Canteen");
			MissionObject.GetInventory().CreateInInventory("Battery9V");
		}
		if (selectedLoadout == 1)
		{
			weapon = MissionObject.GetInventory().CreateInInventory("SVD");
				weapon.GetInventory().CreateAttachment("PSO1Optic");
			MissionObject.GetInventory().CreateInInventory("Mag_SVD_10Rnd");
			MissionObject.GetInventory().CreateInInventory("Mag_SVD_10Rnd");
			MissionObject.GetInventory().CreateInInventory("PSO1Optic");
			MissionObject.GetInventory().CreateInInventory("KazuarOptic");
			MissionObject.GetInventory().CreateInInventory("Ammo_762x54");
			MissionObject.GetInventory().CreateInInventory("Ammo_762x54");
			MissionObject.GetInventory().CreateInInventory("Ammo_762x54");
			MissionObject.GetInventory().CreateInInventory("Ammo_762x54");
			MissionObject.GetInventory().CreateInInventory("Ammo_762x54");
			MissionObject.GetInventory().CreateInInventory("CanOpener");
			MissionObject.GetInventory().CreateInInventory("PeachesCan");
			MissionObject.GetInventory().CreateInInventory("Canteen");
			MissionObject.GetInventory().CreateInInventory("Battery9V");
		}
		if (selectedLoadout == 2)
		{
			weapon = MissionObject.GetInventory().CreateInInventory("AKM");
				weapon.GetInventory().CreateAttachment("AK_RailHndgrd_Green");
				weapon.GetInventory().CreateAttachment("AK_PlasticBttstck_Green");
				weapon.GetInventory().CreateAttachment("PSO1Optic");
				weapon.GetInventory().CreateAttachment("AK_Suppressor");
			MissionObject.GetInventory().CreateInInventory("Mag_AKM_30Rnd");
			MissionObject.GetInventory().CreateInInventory("Mag_AKM_30Rnd");
			MissionObject.GetInventory().CreateInInventory("Ammo_762x39");
			MissionObject.GetInventory().CreateInInventory("Ammo_762x39");
			MissionObject.GetInventory().CreateInInventory("Ammo_762x39");
			MissionObject.GetInventory().CreateInInventory("CanOpener");
			MissionObject.GetInventory().CreateInInventory("PeachesCan");
			MissionObject.GetInventory().CreateInInventory("Canteen");
			MissionObject.GetInventory().CreateInInventory("Battery9V");
		}
		if (selectedLoadout == 3)
		{
			weapon = MissionObject.GetInventory().CreateInInventory("AKM");
				weapon.GetInventory().CreateAttachment("AK_RailHndgrd_Green");
				weapon.GetInventory().CreateAttachment("AK_PlasticBttstck_Green");
				weapon.GetInventory().CreateAttachment("PSO1Optic");
				weapon.GetInventory().CreateAttachment("AK_Suppressor");
			MissionObject.GetInventory().CreateInInventory("FNX45");
			MissionObject.GetInventory().CreateInInventory("Mag_FNX45_15Rnd");
			MissionObject.GetInventory().CreateInInventory("Mag_FNX45_15Rnd");
			MissionObject.GetInventory().CreateInInventory("Ammo_45ACP");
			MissionObject.GetInventory().CreateInInventory("FNP45_MRDSOptic");
			MissionObject.GetInventory().CreateInInventory("PistolSuppressor");
			MissionObject.GetInventory().CreateInInventory("ZenRandomAmmoBox");
			MissionObject.GetInventory().CreateInInventory("Battery9V");
		}	
		if (selectedLoadout == 4)
		{
			weapon = MissionObject.GetInventory().CreateInInventory("SKS");
				weapon.GetInventory().CreateAttachment("PUScopeOptic");
			MissionObject.GetInventory().CreateInInventory("Ammo_762x39");
			MissionObject.GetInventory().CreateInInventory("Ammo_762x39");
			weapon = MissionObject.GetInventory().CreateInInventory("FNX45");
				weapon.GetInventory().CreateAttachment("PistolSuppressor");
				EntityAI weaponlight = weapon.GetInventory().CreateAttachment("TLRLight");
					weaponlight.GetInventory().CreateAttachment("Battery9V");
			MissionObject.GetInventory().CreateInInventory("Mag_FNX45_15Rnd");
			MissionObject.GetInventory().CreateInInventory("Ammo_45ACP");
			MissionObject.GetInventory().CreateInInventory("ZenRandomAmmoBox");
			MissionObject.GetInventory().CreateInInventory("GPSReceiver");
			MissionObject.GetInventory().CreateInInventory(MissionSettings.OldPhotos.GetRandomElement());	
		}	
		if (selectedLoadout == 5)
		{
			weapon = MissionObject.GetInventory().CreateInInventory("Winchester70");
				weapon.GetInventory().CreateAttachment("HuntingOptic");
			MissionObject.GetInventory().CreateInInventory("Ammo_308Win");
			MissionObject.GetInventory().CreateInInventory("Ammo_308Win");
			MissionObject.GetInventory().CreateInInventory("FNX45");
			MissionObject.GetInventory().CreateInInventory("Mag_FNX45_15Rnd");
			MissionObject.GetInventory().CreateInInventory("Ammo_45ACP");
			MissionObject.GetInventory().CreateInInventory("ZenRandomAmmoBox");
			MissionObject.GetInventory().CreateInInventory("PistolSuppressor");
			MissionObject.GetInventory().CreateInInventory("TLRLight");
			MissionObject.GetInventory().CreateInInventory("Battery9V");
			MissionObject.GetInventory().CreateInInventory("GPSReceiver");
		}
		if (selectedLoadout == 6)
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
			MissionObject.GetInventory().CreateInInventory("Battery9V");
			MissionObject.GetInventory().CreateInInventory("Battery9V");
			MissionObject.GetInventory().CreateInInventory("Battery9V");	
			MissionObject.GetInventory().CreateInInventory(MissionSettings.OldPhotos.GetRandomElement());	
		}
		if (selectedLoadout == 7)
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
			MissionObject.GetInventory().CreateInInventory("Battery9V");
			MissionObject.GetInventory().CreateInInventory("Battery9V");				
		}
		if (selectedLoadout == 8)
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
			MissionObject.GetInventory().CreateInInventory("Battery9V");
			MissionObject.GetInventory().CreateInInventory("Battery9V");
			MissionObject.GetInventory().CreateInInventory("Battery9V");	
			MissionObject.GetInventory().CreateInInventory("GPSReceiver");
			MissionObject.GetInventory().CreateInInventory(MissionSettings.OldPhotos.GetRandomElement());				
		}
		if (selectedLoadout == 9)
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
			MissionObject.GetInventory().CreateInInventory("Battery9V");
			MissionObject.GetInventory().CreateInInventory("Battery9V");
			MissionObject.GetInventory().CreateInInventory("Battery9V");
			MissionObject.GetInventory().CreateInInventory("GPSReceiver");
			MissionObject.GetInventory().CreateInInventory("AmmoBox_9x19_25rnd");
			MissionObject.GetInventory().CreateInInventory("AmmoBox_9x19_25rnd");
			MissionObject.GetInventory().CreateInInventory(MissionSettings.OldPhotos.GetRandomElement());	
		}
			
		Print("[SMM] Mission rewards spawned in reward container. Randomly selected loadout was "+selectedLoadout+"." );
				
		//Insert mission tent into mission objects list
		//m_MissionObjects.Insert( MissionObject );
	
		//Clutter Cutter Tent 	
		cc_mtent = GetGame().CreateObject( "MediumTentClutterCutter" , MissionObject.GetPosition() , false );
		cc_mtent.SetOrientation( MissionObject.GetOrientation() );
		GetGame().RemoteObjectCreate( cc_mtent );		 
		m_MissionObjects.Insert( cc_mtent );
		
		//Fireplace
		vector CampfirePosition;
		vector CampfireOrientation;
		vector CampFireDir = MissionObject.GetOrientation();
		float CampFireDist = 4;
			
		GetGame().ObjectDelete( cc_fireplace );
		GetGame().ObjectDelete( MissionCampfire );
		if ( CampFireDir[0] < 0 )	CampFireDir[0] = 360 + CampFireDir[0];
		//some nostalgic code 
		CampfirePosition [0] = m_MissionPosition [0] - Math.Sin( CampFireDir[0] * Math.DEG2RAD ) * CampFireDist;		//x offset
		CampfirePosition [2] = m_MissionPosition [2] - Math.Cos( CampFireDir[0] * Math.DEG2RAD ) * CampFireDist;		//y offset
		MissionCampfire = FireplaceBase.Cast( GetGame().CreateObject( "Fireplace", CampfirePosition ) );
		CampfireOrientation = MissionCampfire.GetOrientation();
		MissionCampfire.Synchronize();
		MissionCampfire.GetInventory().CreateAttachment("Firewood");
		MissionCampfire.GetInventory().CreateAttachment("WoodenStick");
		MissionCampfire.GetInventory().CreateAttachment("Rag");
		MissionCampfire.GetInventory().CreateAttachment("Stone");
		MissionCampfire.StartFire( true );
		m_MissionObjects.Insert( MissionCampfire );
		
		//Cluttercutter fireplace
		cc_fireplace = GetGame().CreateObject( "ClutterCutterFireplace" , MissionCampfire.GetPosition() );
		cc_fireplace.SetOrientation( CampfireOrientation );
		GetGame().RemoteObjectCreate( cc_fireplace );
		m_MissionObjects.Insert( cc_fireplace );
							
		Print("[SMM] Survivor Mission "+ m_selectedMission +" :: "+ m_MissionName +" ...mission deployed!");
	}
	
	void SpawnAIs()
	{	
		int randGuns = Math.RandomIntInclusive(0, 10);
		
		//Spawn dead infected
		vector InfectedPos = MissionObject.ModelToWorld( "0 0 -6" );
		m_MissionAIs.Insert( GetGame().CreateObject( "ZmbM_HikerSkinny_Blue" , InfectedPos , false , true ) );
		DayZInfected InfectedSurvivor = DayZInfected.Cast( m_MissionAIs[0] );
			InfectedSurvivor.GetInventory().CreateAttachment("FlatCap_Blue");
			InfectedSurvivor.GetInventory().CreateAttachment("MountainBag_Blue");
			InfectedSurvivor.GetInventory().CreateAttachment("UKAssVest_Black");
		
		EntityAI weapon;
		if (randGuns == 0)
		{
			weapon = InfectedSurvivor.GetInventory().CreateInInventory("M4A1_Green");
			if (weapon)
			{
				weapon.GetInventory().CreateAttachment("M4_RISHndgrd_Green");
				weapon.GetInventory().CreateAttachment("ACOGOptic");
			}
			InfectedSurvivor.GetInventory().CreateInInventory("M4_MPBttstck");
			InfectedSurvivor.GetInventory().CreateInInventory("Mag_STANAG_30Rnd");
			InfectedSurvivor.GetInventory().CreateInInventory("Mag_STANAG_30Rnd");
			InfectedSurvivor.GetInventory().CreateInInventory("M4_T3NRDSOptic");
			InfectedSurvivor.GetInventory().CreateInInventory("Ammo_556x45");
			InfectedSurvivor.GetInventory().CreateInInventory("Ammo_556x45");
		}
		if (randGuns == 4)
		{ 
			weapon = InfectedSurvivor.GetInventory().CreateInInventory("FNX45");
			if (weapon)
				weapon.GetInventory().CreateAttachment("FNP45_MRDSOptic");
			InfectedSurvivor.GetInventory().CreateInInventory("AmmoBox_45ACP_25rnd");
			InfectedSurvivor.GetInventory().CreateInInventory("AmmoBox_45ACP_25rnd");
			
		}
		if (randGuns == 5)
		{
			weapon = InfectedSurvivor.GetInventory().CreateInInventory("PP19");
			InfectedSurvivor.GetInventory().CreateInInventory("Mag_PP19_64Rnd");
		}
		if (randGuns == 6)
		{
			weapon = InfectedSurvivor.GetInventory().CreateInInventory("Magnum");
			InfectedSurvivor.GetInventory().CreateInInventory("AmmoBox_357_20Rnd");
			InfectedSurvivor.GetInventory().CreateInInventory("AmmoBox_357_20Rnd");
			InfectedSurvivor.GetInventory().CreateInInventory("WeapomCleaningKit");
		}
		if (randGuns == 7)
		{
			weapon = InfectedSurvivor.GetInventory().CreateInInventory("SawedoffB95");
			if (weapon)
				weapon.GetInventory().CreateAttachment("HuntingOptic");
			InfectedSurvivor.GetInventory().CreateInInventory("AmmoBox_308Win_20Rnd");
			InfectedSurvivor.GetInventory().CreateInInventory("WeapomCleaningKit");
		}
		if (randGuns == 8)
		{
			weapon = InfectedSurvivor.GetInventory().CreateInInventory("Derringer_Pink");
			InfectedSurvivor.GetInventory().CreateInInventory("WeapomCleaningKit");
		}
		if (randGuns == 9)
		{
			weapon = InfectedSurvivor.GetInventory().CreateInInventory("Derringer_Black");
			InfectedSurvivor.GetInventory().CreateInInventory("AmmoBox_357_20Rnd");
			InfectedSurvivor.GetInventory().CreateInInventory("WeapomCleaningKit");
		}
		if (randGuns == 10)
		{
			weapon = InfectedSurvivor.GetInventory().CreateInInventory("MakarovIJ70");
			if (weapon)
				weapon.GetInventory().CreateAttachment("PistolSuppressor");
			InfectedSurvivor.GetInventory().CreateInInventory("AmmoBox_380_35rnd");
			InfectedSurvivor.GetInventory().CreateInInventory("AmmoBox_380_35rnd");
			InfectedSurvivor.GetInventory().CreateInInventory("WeapomCleaningKit");
		}
		
		InfectedSurvivor.GetInventory().CreateInInventory("CanOpener");
		InfectedSurvivor.GetInventory().CreateInInventory("PeachesCan");
		InfectedSurvivor.GetInventory().CreateInInventory("Canteen");
		InfectedSurvivor.GetInventory().CreateInInventory("Battery9VLithium");
		InfectedSurvivor.GetInventory().CreateInInventory(MissionSettings.GenericRewards.GetRandomElement());
		
		int rand2 = Math.RandomIntInclusive(1, 5);
		if (rand2 == 1)
		{
			InfectedSurvivor.GetInventory().CreateInInventory("Zen_Canteen_Black");
		}
		if (rand2 == 2)
		{
			InfectedSurvivor.GetInventory().CreateInInventory("Zen_Dye_Black");
		}
		if (rand2 == 3)
		{
			InfectedSurvivor.GetInventory().CreateInInventory("Zen_Dye_Green");
		}
		if (rand2 == 4)
		{
			InfectedSurvivor.GetInventory().CreateInInventory("Spraycan_Black");
		}
		if (rand2 == 5)
		{
			InfectedSurvivor.GetInventory().CreateInInventory("Spraycan_Green");
		}
		
		// Kill infected
		InfectedSurvivor.SetHealth("","",0);
		
		// Spawn landmine on dead infected
		LandMineTrap landmine = LandMineTrap.Cast(GetGame().CreateObjectEx("LandMineTrap", InfectedSurvivor.GetPosition(), ECE_PLACE_ON_SURFACE));
		landmine.StartActivate(NULL);
		m_MissionObjects.Insert(landmine);
		
		//Spawn boobytraped infected
		string RandomInfected = InfectedTypes.GetRandomElement();
		vector InfectedPos1 = MissionObject.ModelToWorld( "0 0 5" );
		
		m_MissionAIs.Insert( GetGame().CreateObject( RandomInfected, InfectedPos1, false, true ) );
		BoobyTrap = Grenade_Base.Cast( GetGame().CreateObject( "M67Grenade" , InfectedPos1, false, false, false ));
		BoobyTrap.ActivateImmediate();
		
		// Spawn zombie trigger
		/*ZenMissionZombiesTrigger trigger = ZenMissionZombiesTrigger.Cast(GetGame().CreateObjectEx("ZenMissionZombiesTrigger", m_MissionPosition, ECE_CREATEPHYSICS));
		if (trigger)
		{
			trigger.SetupZenMissionZombiesTrigger(MISSION_TIME, 300, 20, InfectedTypes, 25);
		}*/
		
		//Spawn infected
		for (int x = 0; x < 20; x++)
		{
			vector xyzRand = m_MissionPosition;
			xyzRand[0] = xyzRand[0] + Math.RandomFloatInclusive(-30, 30);
			xyzRand[2] = xyzRand[2] + Math.RandomFloatInclusive(-30, 30);
			xyzRand[1] = GetGame().SurfaceY(xyzRand[0], xyzRand[2]);
			m_MissionAIs.Insert(GetGame().CreateObject(InfectedTypes.GetRandomElement(), xyzRand, false, true));
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
		ZenModLogger.Log("CampMission completed.", "missions");
		
		//When player enters last mission target zone	
		//Respawn some infected 
		for ( int j = 0 ; j < 2 ; j++ )
		{
    	   	string RandomInfected = InfectedTypes.GetRandomElement();
			vector InfectedPos = MissionObject.ModelToWorld( InfectedSpawns.GetRandomElement() );
			m_MissionAIs.Insert( GetGame().CreateObject( RandomInfected, InfectedPos, false, true ) );			
		}

		//Finish mission
		m_RewardsSpawned = true;
		m_MsgNum = -1;
		m_MsgChkTime = m_MissionTime + MsgDlyFinish;			
	}
	
	void PlayerChecks( PlayerBase player )
	{
		//Check if container gets taken from player
		if ( MissionSettings.Opt_DenyObjTakeaway )
		{		
			if ( m_MissionObjects[0] && m_MissionObjects[0].ClassName() == "Zen_Mission_MediumTent" ) 
			{
				if ( TentBase.Cast( m_MissionObjects[0] ).CanBeManipulated() && !m_ContainerWasTaken )
				{
					m_ContainerWasTaken = true;
					Print("[SMM] Mission tent was packed by a player ...and will be deleted.");
					GetGame().ObjectDelete( m_MissionObjects[0] );
				}
			}
		}	
	}
		
	void UpdateBots(float dt)
	{
		//Test1.OnUpdate(dt);		
	}
	
	bool DeployMission()
	{	
		//When first player enters the mission zone (primary/secondary)
		if ( m_MissionPosition && m_MissionPosition != "0 0 0" )
		{
			//Call spawners	
			GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).Call( this.SpawnObjects );
			GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).Call( this.SpawnAIs );
			return true;		
		}
		else 
		{
			Print("[SMM] ERROR : Mission position was rejected or doesn't exist. MissionPosition is NULL!");
			return false;
		}
	}
}

