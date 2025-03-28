class FixWellsMission extends SurvivorMissions
{
	//Mission related entities
	ItemBase MissionObject;
	bool debugOn = false;

	//Mission parameters
	int MsgDlyFinish	= 10;			// 3mins - seconds, message delay time after player has finished mission
	int MissionType		= 0;			// 0 = meds, 1 = basebuilding, 2 = ammo & weapons
	int InfectedCount	= 12;			// 12 ZEDS
	int ExtendedTimout	= 3000;			//seconds, mission duration time for extended mission

	//Mission containers
	ref array<string> InfectedTypes = new array<string>;

	//Mission variables 
	string SurvivorName;
	ref RepairableWell TargetWell;
	bool AirdropCalled = false;
	bool SpawnedAI = false;

	bool IsExtended() return true;

	void FixWellsMission()
	{
		ZenModLogger.Log("[STARTED] FixWellsMission started.", "missions");

		//Select primary mission
		m_MissionExtended = false;
		AirdropCalled = false;

		//Mission timeout
		m_MissionTimeout = 3600;			//seconds, primary mission duration time

		//Mission zones
		m_MissionZoneOuterRadius = 100;		//meters (!Do not set lower than 200m), mission activation distance
		m_MissionZoneInnerRadius = -1;		//meters (!Do not set outside of 1-5m), mission finishing distance to target object

		//Mission informant
		m_MissionInformant = MissionSettings.GoodBoss;

		// Find a well
		SetMissionPosition();

		//Set mission messages for primary mission
		m_MissionMessage1 = "Attention survivors, we need your help with a humanitarian mission. The water wells are breaking down and Livonians are dying of thirst. We need someone to help us fix them.";
		m_MissionMessage2 = "Our scientists are advising me on the matter. They want you to find a wrench.";
		m_MissionMessage3 = "Travel to \n\n** " + m_MissionLocation + " **\n\nFix the well there. We'll reward you for your work by sending in an airdrop care package. Good luck survivor.";

		//Infected types for secondary mission position
		//Male												//Female
		InfectedTypes.Insert("ZmbM_CitizenASkinny_Brown");	InfectedTypes.Insert("ZmbF_JournalistNormal_White");
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
		InfectedTypes.Insert("ZmbF_ShortSkirt_yellow");		InfectedTypes.Insert("ZmbF_Clerk_Normal_White");
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

	void ~FixWellsMission()
	{
		ZenModLogger.Log("[DESTROY] FixWellsMission class destroyed.", "missions");

		//Despawn all remaining mission objects
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

		//Despawn mission AI's
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

		//Delete PlayersInZone list & reset container takeaway
		if (m_PlayersInZone)		m_PlayersInZone.Clear();
		if (m_ContainerWasTaken)	m_ContainerWasTaken = false;
	}

	void SpawnObjects()
	{
	}

	void SpawnAIs()
	{
		//Spawn infected
		for (int x = 0; x < InfectedCount; x++)
		{
			vector xyzRand = m_MissionPosition;
			xyzRand[0] = xyzRand[0] + Math.RandomFloatInclusive(-10, 10);
			xyzRand[2] = xyzRand[2] + Math.RandomFloatInclusive(-10, 10);
			xyzRand[1] = GetGame().SurfaceY(xyzRand[0], xyzRand[2]);

			float hitFraction;
			vector hitPosition, hitNormal;
			vector to = xyzRand + "0 10 0";
			Object hitObject;
			PhxInteractionLayers collisionLayerMask = PhxInteractionLayers.ITEM_LARGE | PhxInteractionLayers.BUILDING | PhxInteractionLayers.VEHICLE;
			if (DayZPhysics.RayCastBullet(xyzRand, to, collisionLayerMask, null, hitObject, hitPosition, hitNormal, hitFraction))
			{
				continue; // Don't spawn zeds inside buildings or objects
			}

			DayZInfected Zed = DayZInfected.Cast(GetGame().CreateObject(InfectedTypes.GetRandomElement(), xyzRand, false, true));
			if (Zed)
			{
				DayZInfectedCommandMove moveCommandZ = Zed.GetCommand_Move();
				if (moveCommandZ)
					moveCommandZ.SetIdleState(2);
			}

			m_MissionAIs.Insert(Zed);
		}


		SpawnedAI = true;
	}

	void ObjDespawn()
	{
		//Despawn nothing
	}

	void MissionFinal(PlayerBase player)
	{
		ZenModLogger.Log("FixWellsMission completed.", "missions");
	}

	void SetMissionPosition()
	{
		int i;
		array<int> brokenWells = new array<int>;

		// scan through well config and find a broken well. If we can't find one, break a random one.
		for (i = 0; i < GetZenWellsConfig().RepairableWells.Count(); i++)
		{
			TargetWell = GetZenWellsConfig().RepairableWells.Get(i);

			if (!TargetWell.Repaired && !TargetWell.Invincible)
			{
				brokenWells.Insert(i);
			}
		}

		if (brokenWells.Count() == 0)
		{
			vector Topolin = "1958.608398 221.026443 7020.782227";
			int wellIdx = GetZenWellsConfig().GetRepairableWellIndex(Topolin);

			// If no broken wells are found, 
			if (wellIdx == -1)
			{
				RepairableWell brokenWell = new RepairableWell(Topolin, false, 0);
				GetZenWellsConfig().RepairableWells.Insert(brokenWell);
				brokenWells.Insert(0);
			}
			else
			{
				GetZenWellsConfig().SetWellRepaired(wellIdx, Topolin, false, true);
				brokenWells.Insert(wellIdx);

				array<Object> nearestObjects = new array<Object>;
				GetGame().GetObjectsAtPosition(Topolin, 1.0, nearestObjects, null);

				foreach(Object nearestObject : nearestObjects)
				{
					Well well = Well.Cast(nearestObject);
					if (well)
					{
						well.SetRepaired(false);
						break;
					}
				}
			}			
		}

		// pick a random index
		i = brokenWells.GetRandomElement();
		TargetWell = GetZenWellsConfig().RepairableWells.Get(i);
		m_MissionLocation = "Well @ Coordinates: " + Math.Round(TargetWell.Location[0]).ToString() + " / " + Math.Round(TargetWell.Location[2]).ToString();
		m_MissionPosition = TargetWell.Location;
	}

	void ExtendMission(PlayerBase player)
	{
	}

	float m_PlayerChecks = 0;
	void PlayerChecks(PlayerBase player)
	{
		// Spawn AI as soon as player enters 100m of Well
		if (!SpawnedAI)
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).Call(this.SpawnAIs);

		m_PlayerChecks++;
		if (m_PlayerChecks < 5000) // 5 secs
			return;

		m_PlayerChecks = 0;

		if (TargetWell.Repaired)
		{
			// spawn airdrop and finish mission
			if (!AirdropCalled)
			{
				MissionSettings.FinishingMsg = "Thank you for your help survivor.\nI'm sure your work will help save lives.\nHold your position for the next 10 minutes - we're sending in an airdrop full of valuable supplies.\nWe'll be in touch soon, stay tuned to this frequency. Over and out.";
				ExpansionMissionModule.s_Instance.CallAirdrop(m_MissionPosition);
				ZMPrint("[FixWellsMission] Spawned air drop @ m_MissionPosition as reward.");
				SpawnWolves(m_MissionPosition);
				AirdropCalled = true;
				m_RewardsSpawned = true;
				m_MsgNum = -1;
				m_MsgChkTime = m_MissionTime + MsgDlyFinish;
				m_MissionZoneInnerRadius = m_MissionZoneOuterRadius; // This triggers the mission finished
				m_MissionPosition = vector.Zero; // This moves the mission zone and triggers the end of the mission after airdrop has been called in
			}
		}
	}

	void SpawnWolves(vector loc)
	{
		for (int i = 0; i < 3; i++)
		{
			vector xyzRand = loc;

			int MinDistance = Math.RandomFloatInclusive(100, 150);
			if (Math.RandomFloat01() <= 0.5)
				MinDistance = Math.RandomFloatInclusive(-100, -150);

			xyzRand[0] = xyzRand[0] + Math.RandomFloatInclusive(-100, 100) + MinDistance; // Minimum range 100-250m, maximum range -250 - +250m on top of that
			xyzRand[2] = xyzRand[2] + Math.RandomFloatInclusive(-100, 100) + MinDistance;
			xyzRand[1] = GetGame().SurfaceY(xyzRand[0], xyzRand[2]); // change to find surface

			// Check if wolf is NOT inside a building or object
			float hitFraction;
			vector hitPosition, hitNormal;
			vector to = xyzRand + "0 25 0";
			Object hitObject;
			PhxInteractionLayers collisionLayerMask = PhxInteractionLayers.ITEM_LARGE | PhxInteractionLayers.BUILDING | PhxInteractionLayers.VEHICLE;
			if (!DayZPhysics.RayCastBullet(xyzRand, to, collisionLayerMask, null, hitObject, hitPosition, hitNormal, hitFraction))
			{
				GetGame().CreateObject("Animal_CanisPestis", xyzRand, false, true, true);
			}
		}
	}

	void UpdateBots(float dt)
	{
		//no bots involved in this mission		
	}

	bool DeployMission()
	{
		//GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).Call(this.SpawnAIs);
		return true;
	}
}