class GardensAtWellMission extends SurvivorMissions
{
	//Mission related entities
	ItemBase MissionObject;
	static bool debugOn = false;

	//Mission parameters
	static ref array<Object> objectsNearGarden = new array<Object>; 
	static int MISSION_TIME = 3600;
	int MsgDlyFinish	= 10;			// 3mins - seconds, message delay time after player has finished mission
	int MissionType		= 0;			// 0 = meds, 1 = basebuilding, 2 = ammo & weapons
	int InfectedCount	= 12;			// 12 ZEDS
	int ExtendedTimout	= MISSION_TIME;			//seconds, mission duration time for extended mission

	//Mission containers
	ref array<string> InfectedTypes = new array<string>;

	//Mission variables 
	string SurvivorName;

	bool IsExtended() return true;

	ref static const array<string> MissionLine1 =
	{
		
	};

	void GardensAtWellMission()
	{
		ZenModLogger.Log("GardensAtWellMission started.", "missions");
		
		MissionSettings.Message3Ext = " minutes left to complete the task before we'll assume you are dead and move on.\nOver and out!"; // mins left msg

		//Select primary mission
		m_MissionExtended = true;
		airdropCalled = false;

		//Mission timeout
		m_MissionTimeout = MISSION_TIME;			//seconds, primary mission duration time

		//Mission zones
		m_MissionZoneOuterRadius = 30;		//meters (!Do not set lower than 200m), mission activation distance
		m_MissionZoneInnerRadius = -1;		//meters (!Do not set outside of 1-5m), mission finishing distance to target object

		//Mission informant
		m_MissionInformant = MissionSettings.GoodBoss;

		if (m_MissionLocation.Contains("Topolin"))
		{
			if (Math.RandomIntInclusive(1, 2) == 1)
			{
				m_MissionLocation = "South Topolin";
			}
			else
			{
				m_MissionLocation = "the North Topolin Farm";
			}
		}
		else
		if (m_MissionLocation.Contains("Gliniska"))
			m_MissionLocation = "Southern Gliniska";
		else
		if (m_MissionLocation.Contains("Bielawa"))
			m_MissionLocation = "Eastern Bielawa";
		else
		if (m_MissionLocation.Contains("Brena"))
			m_MissionLocation = "Eastern Brena";
		else
		if (m_MissionLocation.Contains("Grabin"))
			m_MissionLocation = "Northern Grabin";

		SetMissionPosition();

		//Mission person names
		bool maleSurvivor = Math.RandomIntInclusive(0, 1) == 1;

		if (maleSurvivor)
			SurvivorName = MissionSettings.MaleSurvivorNames.GetRandomElement();
		else
			SurvivorName = MissionSettings.FemaleSurvivorNames.GetRandomElement();

		string SurvivorDescription = "";

		if (maleSurvivor)
			SurvivorDescription = "He's a UN scientist and he";
		else
			SurvivorDescription = "She's a UN scientist and she";

		//Set mission messages for primary mission
		m_MissionMessage1 = "Attention survivors, we need your help with a humanitarian mission. Starvation is killing thousands of Livonians. We need a more sustainable source of food.";
		m_MissionMessage2 = "Our scientists are advising me on the matter. They want you to plant vegetable crops in the northern towns.";
		m_MissionMessage3 = "Travel to \n** " + m_MissionLocation + " **\nPlant some vegetables near the well there. We'll reward you for your help. Good luck survivor.";

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

	void ~GardensAtWellMission()
	{
		ZenModLogger.Log("GardensAtWellMission class destroyed.", "missions");

		//Delete PlayersInZone list & reset container takeaway
		if (m_PlayersInZone)		m_PlayersInZone.Clear();
		if (m_ContainerWasTaken)	m_ContainerWasTaken = false;
	}

	void SpawnObjects()
	{
	}

	void SpawnAIs()
	{
		// Spawn zombie trigger
		ZenMissionZombiesTrigger trigger = ZenMissionZombiesTrigger.Cast(GetGame().CreateObjectEx("ZenMissionZombiesTrigger", m_MissionPosition, ECE_CREATEPHYSICS));
		if (trigger)
		{
			trigger.SetupZenMissionZombiesTrigger(MISSION_TIME, 300, InfectedCount, InfectedTypes, 25);
		}
	}

	void ObjDespawn()
	{
		//Despawn nothing
	}

	void MissionFinal(PlayerBase player)
	{	
		ZenModLogger.Log("GardensAtWell completed.", "missions");
		//When player enters last mission target zone	
	}

	vector m_AirDropLocation;
	void SetMissionPosition()
	{
		if (m_MissionLocation.Contains("South Topolin"))
		{
			m_MissionPosition[0] = 1958.459473;
			m_MissionPosition[1] = 221.026443;
			m_MissionPosition[2] = 7020.745605;
			
			m_AirDropLocation[0] = 2183.202637;
			m_AirDropLocation[1] = 246.265213;
			m_AirDropLocation[2] = 7104.706055;
		} 
		else if (m_MissionLocation.Contains("Topolin"))
		{
			m_MissionPosition[0] = 1247.142700;
			m_MissionPosition[1] = 217.766052;
			m_MissionPosition[2] = 8069.689941;
			
			m_AirDropLocation[0] = 1896.778687;
			m_AirDropLocation[1] = 186.442429;
			m_AirDropLocation[2] = 7513.986816;
		}
		else if (m_MissionLocation.Contains("Kolembrody"))
		{
			m_MissionPosition[0] = 8435.943359;
			m_MissionPosition[1] = 178.309570;
			m_MissionPosition[2] = 12024.891602;
			
			m_AirDropLocation[0] = 8665.843750;
			m_AirDropLocation[1] = 179.572601;
			m_AirDropLocation[2] = 12059.131836;
		}
		else if (m_MissionLocation.Contains("Gliniska"))
		{
			m_MissionPosition[0] = 5072.662598;
			m_MissionPosition[1] = 183.346176;
			m_MissionPosition[2] = 9746.017578;
	
			m_AirDropLocation[0] = 4926.268555;
			m_AirDropLocation[1] = 193.968430;
			m_AirDropLocation[2] = 9633.931641;
		}
		else if (m_MissionLocation.Contains("Bielawa"))
		{
			m_MissionPosition[0] = 1676.754517;
			m_MissionPosition[1] = 265.056458;
			m_MissionPosition[2] = 9746.058594;
			
			m_AirDropLocation[0] = 1645.325317;
			m_AirDropLocation[1] = 254.088211;
			m_AirDropLocation[2] = 9466.955078;
		}
		else if (m_MissionLocation.Contains("Radacz"))
		{
			m_MissionPosition[0] = 4049.143555;
			m_MissionPosition[1] = 208.838928;
			m_MissionPosition[2] = 7939.045410;
			
			m_AirDropLocation[0] = 4199.292480;
			m_AirDropLocation[1] = 217.600479;
			m_AirDropLocation[2] = 8011.151855;
		}
		else if (m_MissionLocation.Contains("Olszanka"))
		{
			m_MissionPosition[0] = 4807.734375;
			m_MissionPosition[1] = 292.386292;
			m_MissionPosition[2] = 7622.491211;
			
			m_AirDropLocation[0] = 4645.365234;
			m_AirDropLocation[1] = 293.359344;
			m_AirDropLocation[2] = 7464.632324;
		}
		else if (m_MissionLocation.Contains("Sitnik"))
		{
			m_MissionPosition[0] = 11247.609375;
			m_MissionPosition[1] = 186.337585;
			m_MissionPosition[2] = 9549.436523;
			
			m_AirDropLocation[0] = 11264.262695;
			m_AirDropLocation[1] = 180.575897;
			m_AirDropLocation[2] = 9226.904297;
		}
		else if (m_MissionLocation.Contains("Brena"))
		{
			m_MissionPosition[0] = 6540.581543;
			m_MissionPosition[1] = 184.912842;
			m_MissionPosition[2] = 11268.017578;
			
			m_AirDropLocation[0] = 6661.343750;
			m_AirDropLocation[1] = 186.194901;
			m_AirDropLocation[2] = 11423.615234;
		}
		else if (m_MissionLocation.Contains("Grabin"))
		{
			m_MissionPosition[0] = 10969.187500;
			m_MissionPosition[1] = 174.921936;
			m_MissionPosition[2] = 11203.603516;
			
			m_AirDropLocation[0] = 11006.461914;
			m_AirDropLocation[1] = 176.176010;
			m_AirDropLocation[2] = 10860.357422;
		}
	}
	
	ref static const array<string> LocationsList =
	{
		"in South Topolin",
		"North of Topolin",
		"in South Gliniska",
		"in Kolembrody",
		"in Eastern Bielawa",
		"in Radacz",
		"in Olszanka",
		"in Sitnik",
		"in Eastern Brena",
		"in Northern Grabin"
	};

	void ExtendMission(PlayerBase player)
	{	
		//When player enters mission target zone at primary mission
		string m_SecondaryLocation = "";
		for (int i = 0; i < 1000; i++)
		{
			m_SecondaryLocation = LocationsList.GetRandomElement();
			if (m_SecondaryLocation != m_MissionLocation)
				break;
		}

		//Set messages for secondary mission
		m_MissionMessage1 = "Alright, thanks survivor. Our satellite imagery confirms that you've planted some crops in " + m_MissionLocation;
		m_MissionMessage2 = "The job isn't finished yet though. Now we need you to plant some more crops near the well \n** " + m_SecondaryLocation + " **";
		m_MissionMessage3 = "Once we confirm that there are crops growing there, we'll send an airdrop full of valuable supplies to your location.";
		m_MissionLocation = m_SecondaryLocation;

		vector OldLocation = m_MissionPosition;
		SetMissionPosition();
		float MissionDistance = vector.Distance(OldLocation, m_MissionPosition);
		ExtendedTimout = MissionDistance; // 1 minute per meter

		//init Messenger for new messages
		m_MsgNum = 1;					//skip msg 0, begin with msg 1
		m_MsgChkTime = m_MissionTime;
		MsgCutoff = false;
		m_MissionExtended = false;

		//increase mission MissionTimeout for secondary mission
		m_MissionTimeout = m_MissionTime + ExtendedTimout;

		//deployment settings & init for secondary mission		
		m_MissionZoneOuterRadius = 30.0;
		m_MissionZoneInnerRadius = -1;

		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).Call(this.SpawnAIs);
	}

	bool airdropCalled = false;

	float m_PlayerChecks = 0;
	void PlayerChecks(PlayerBase player)
	{
		//ZenM_SendMessage("CHECK! - " + m_PlayerChecks);
		m_PlayerChecks++;
		if (m_PlayerChecks < 5000)
			return;

		m_PlayerChecks = 0;

		ZenM_SendMessage( "Check gardens");
		
		if (!m_MissionExtended) // Last stage of mission
		{
			float extra_offset = 0;
			
			if (m_MissionLocation.Contains("Sitnik") || m_MissionLocation.Contains("Brena"))
				extra_offset = 20;

			GetGame().GetObjectsAtPosition(m_MissionPosition, m_MissionZoneOuterRadius + extra_offset, objectsNearGarden, NULL);

			// Scan for garden plots
			for (int i = 0; i < objectsNearGarden.Count(); i++)
			{
				Object FoundObject1 = objectsNearGarden.Get(i);
				if (FoundObject1.GetType() == "GardenPlot" || FoundObject1.GetType() == "GardenPlotGreenhouse" || FoundObject1.GetType() == "GardenPlotPolytunnel")
				{
					GardenBase gb1 = GardenBase.Cast(FoundObject1);

					if (!gb1)
					{
						ZenM_SendMessage( "Garden base not found! - " + FoundObject1.GetType());
						continue;
					}

					int slots_count1 = gb1.GetGardenSlotsCount();
					int plantsFound1 = 0;
					for (int x = 0; x < slots_count1; x++)
					{
						Slot slot1 = gb1.GetSlotByIndex(x);
						if (slot1.GetPlant() && (slot1.GetPlant().GetPlantState() == PlantBase.STATE_GROWING || slot1.GetPlant().GetPlantState() == PlantBase.STATE_MATURE))
							plantsFound1++;
					}

					ZenM_SendMessage( "Garden base found! - " + FoundObject1.GetType() + " slots=" + slots_count1 + " plants=" + plantsFound1);

					if (plantsFound1 >= slots_count1)
					{
						MissionSettings.FinishingMsg = "Thank you for your help survivor.\nI'm sure your work will help save lives.\nHold your position - we're sending in an airdrop full of valuable supplies.\nWe'll be in touch soon, stay tuned to this frequency. Over and out.";
						ZenM_SendMessage( "Airdrop sent, mission finished");

						m_RewardsSpawned = true;
						m_MsgNum = -1;
						m_MsgChkTime = m_MissionTime + MsgDlyFinish;
						m_MissionZoneInnerRadius = m_MissionZoneOuterRadius; // This triggers the mission finished

						if (!airdropCalled)
						{
							ExpansionMissionModule.s_Instance.CallAirdrop(m_AirDropLocation);
							SpawnWolves(m_MissionPosition);
							airdropCalled = true;
						}
						else
						{
							m_MissionPosition[0] = 1; // This moves the mission zone and triggers the end of the mission after airdrop has been called in
							m_MissionPosition[1] = 1;
							m_MissionPosition[2] = 1;
						}

						break;
					}
				}
			}
		}
		else // First stage of mission
		{
			GetGame().GetObjectsAtPosition(m_MissionPosition, m_MissionZoneOuterRadius, objectsNearGarden, NULL);

			// Scan for garden plots
			for (int j = 0; j < objectsNearGarden.Count(); j++)
			{
				Object FoundObject2 = objectsNearGarden.Get(j);
				if (FoundObject2.GetType() == "GardenPlot" || FoundObject2.GetType() == "GardenPlotGreenhouse" || FoundObject2.GetType() == "GardenPlotPolytunnel")
				{
					GardenBase gb2 = GardenBase.Cast(FoundObject2);

					if (!gb2)
						continue;

					int slots_count2 = gb2.GetGardenSlotsCount();
					int plantsFound2 = 0;

					for (int y = 0; y < slots_count2; y++)
					{
						Slot slot2 = gb2.GetSlotByIndex(y);
						if (slot2.GetPlant() && (slot2.GetPlant().GetPlantState() == PlantBase.STATE_GROWING || slot2.GetPlant().GetPlantState() == PlantBase.STATE_MATURE))
							plantsFound2++;
					}

					ZenM_SendMessage( "Garden base found! - " + FoundObject2.GetType() + " slots=" + slots_count2 + " plants=" + plantsFound2);

					if (plantsFound2 >= slots_count2)
					{
						ExtendMission();
						DeployMission();
						break;
					}
				}
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

	void ZenM_SendMessage(string message)
	{
		if (!debugOn)
			return;

		ZenFunctions.SendGlobalMessage(message);
	}

	void UpdateBots(float dt)
	{
		//no bots involved in this mission		
	}

	bool DeployMission()
	{
		if (objectsNearGarden)
			objectsNearGarden.Clear();

		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).Call(this.SpawnAIs);
		return true;
	}
}