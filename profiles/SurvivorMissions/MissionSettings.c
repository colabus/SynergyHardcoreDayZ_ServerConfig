//This file was created to make a "Multi Server" setup possible. Change mission and map for this server if needed. 
//Modify between "$CurrentDir:\\mpmissions\\      and 		\\SurvivorMissionModule\\...
#include "$CurrentDir:\\mpmissions\\dayzOffline.enoch\\SurvivorMissionModule\\EventsWorldData.c"
#include "$CurrentDir:\\mpmissions\\dayzOffline.enoch\\SurvivorMissionModule\\Missions\\AAA_Missions.h"

class MissionSettings
{	
	//Survivor Stories path (Do not change unless you are using a different folder name!) The second part of the file name gets added by SMM internally
	static string StoriesFilePath = "$profile:\\SurvivorMissions\\SurvivorStories_";
	
	//DebugMode ( Useful for creating your own missions )
	const bool DebugMode = false;				//1 = Enables debug functions and advanced script logging
	const bool DebugShowInfo = true;			//1 = Displays additional information on the client in debug mode
	const bool DebugRCbuild = false;			//1 = Raycast map after server start for desired building type, prints all found buildings to script log	
	const string RCbuildType = "Land_City_School";					//Building type for map wide raycast
	const bool CheckEWD = false;				//1 = Performs a check on MissionBuildings of events data at server start. Disable when check ran once successfully
	
	const int DebugMission = 53;				//select mission by number (array index of EWD), set -1 to let SurvivorMissionModule select the mission
	
	//Mission options
	static bool Opt_OnStartCleanUp = false;		//1 = Clean up previous mission position from any items at server start, 0 = deactivate OnStartCleanUp
	static bool Opt_BuildStatics = false;		//1 = Spawn additional static buildings on startup(check EventsWorldData file), 0 = deploy only missions 
	static bool Opt_SendStoryOnDisconn = false;	//1 = Player gets SurvivorStories displayed in main menu after disconnecting, 0 = deactivate SurvivorStories 
	static bool Opt_DenyObjTakeaway = false;	//1 = mission object container gets deleted if manipulated, 0 = allow takeaway
	static bool Opt_MsgTypeRadio = true; 		//1 = messages on radio for listeners only, 0 = server message broadcast to all clients
	static bool Opt_ServerMsgFreq = false;		//1 = server informs all players of radio frequency, 0 = deactivate radio frequency information
												// ( You can also use server MOTD instead! )  
	static bool Opt_RPmode = false;				//1 = chronological mission selection for role play purposes, 0 = random mission selection 
	static ref TIntArray Opt_RPlist = {0,130};
	//insert your chronological mission selection by the mission number (array index in EWD)
	
	//Module messages (you can translate into your language)
	static string ZoneEnterMsg = "You have entered the mission zone!";
	static string TimeLeftMsg = " minutes left until the mission is failed.";	//keep first character as space
	static string ZoneLeaveMsg = "You have left the mission zone!";	
	static string StartingMsgDefault = "Can anybody hear me? Over!";
	static string StartingMsg = "";	//(Message 0)
	static string TargetFoundMsg = "You have found the target!";
	static string Message3Ext = " minutes left to complete the task before we'll assume you are dead and move on.\nOver and out!";		//keep first character as space
	static string FinishingMsg = "Thank you for solving that survivor.\nYou seem reliable, and we could really use the help. Stay tuned to this radio channel if you're willing to support us - we'll make it worth your while.\nIt's going to be a hard fight to win back Livonia from this plague.\nOver and out.";	//(Message -1)
	static string TimeoutMsg = "You're too late! The mission is failed.\nI'm disappointed. We expected more of you, survivor.\nOver and out.";	//(Message -2)
		
	//Mission module settings
	static int DelayTime = 1200; 				// 15-30mins - seconds (!Do not set lower than 300 seconds), delay time of first and between previous and next mission
	static int MsgFreqDlyTime = 1200;			//seconds (!Do not set lower than 900 seconds), radio frequency information delay time
	static int MsgWaitTime = 420;				//seconds (!Do not set lower than 300 seconds), message interval, cycle duration time


	// Debug settings
	/*
	static int DelayTime = 90; 					// 15-30mins - seconds (!Do not set lower than 300 seconds), delay time of first and between previous and next mission
	static int MsgFreqDlyTime = 60;				//seconds (!Do not set lower than 900 seconds), radio frequency information delay time
	static int MsgWaitTime = 60;				//seconds (!Do not set lower than 300 seconds), message interval, cycle duration time
	*/


	static int CleanUpDlyTime = 180;										//seconds (!Do not set lower than 180 seconds), delay time of OnStartCleanup executed once after mpmission is loaded by the server
	static float RadioFrequency = 87.8;										//Mhz (!Do only set a frequency from channels used ingame), radio frequency of mission channel
	static int MsgCutoffTime = 2;											//minutes, time of messaging cutoff before mission ends

	
	
	static string GetStoriesFilePath() return StoriesFilePath;
	
	static float GetRadioFrequency() return RadioFrequency;	
	
	static const string GoodBoss	= "U.N. Secretary-General Mikolaj";
static const string BadBoss		= "Prophet Ezekiel";

	ref static const array<string> MaleSurvivorNames =
	{
		"Piotr",
		"Pietrek",
		"Patryk",
		"Rafal",
		"Rajmund",
		"Zarek",
		"Tolek",
		"Stanislas",
		"Sergiusz",
		"Nikolai",
		"Aleksandr",
		"Aleksy",
		"Andnej",
		"Armandek",
		"Armand",
		"Augustyn",
		"Aureli",
		"Bazyli",
		"Borys",
		"Cyryl",
		"Budzyk",
		"Dionizy",
		"Dorek",
		"Dobromierz",
		"Dobromil",
		"Dyzek",
		"Czcibor",
		"Edek",
		"Egidiusz",
		"Elek",
		"Eljasz",
		"Erek",
		"Emmilian",
		"Eryk",
		"Eufemiusz",
		"Eustachy",
		"Feliks",
		"Florian",
		"Frandszk",
		"Fryderyk",
		"Gerik",
		"Henryk",
		"Jacek",
		"Janah",
		"Jarek",
		"Jedrek",
		"Jedrick",
		"Jedrus",
		"Josep",
		"Kaspar",
		"Kazimierz",
		"Kazimir",
		"Kazmer",
		"Krzysztof",
		"Liuz",
		"Konstancji",
		"Ludwik",
		"Lukasz",
		"Marcin",
		"Marcinek",
		"Marek",
		"Michal",
		"Mikolai"
	};// 62 names

	ref static const array<string> FemaleSurvivorNames =
	{
		"Olesia",
		"Rasine",
		"Zotia",
		"Valeska",
		"Tesia",
		"Alina",
		"Felcia",
		"Tola",
		"Magdalena",
		"Krystyna",
		"Anna",
		"Maria",
		"Katarzyna",
		"Ewa",
		"Joanna",
		"Aleksandra",
		"Monika",
		"Zofia",
		"Teresa",
		"Danuta",
		"Natalia",
		"Karolina",
		"Marta",
		"Maja",
		"Agnieszka",
		"Alicja",
		"Agata",
		"Adrianna",
		"Adelajda",
		"Elzbieta",
		"Hanna",
		"Henrieta",
		"Inga",
		"Irena",
		"Izabela",
		"Jadzia",
		"Jolanta",
		"Justyna",
		"Kasia",
		"Karina",
		"Ksenia",
		"Lena",
		"Lilianna",
		"Marcelina",
		"Miroslawa",
		"Oliwia",
		"Patrycja",
		"Renia",
		"Roza",
		"Stefcia",
		"Urszula",
		"Wisia",
		"Wislawa",
		"Zuzanna",
		"Zosia",
		"Zlota",
		"Ziva",
		"Zdzislawa",
		"Zaneta",
		"Zaklina",
		"Veronika",
		"Teodozja",
		"Sabina"
	};// 62 names
	
	ref static const array<string> OldPhotos =
	{
		"ZenTreasure_Photo01",
		"ZenTreasure_Photo02",
		"ZenTreasure_Photo03",
		"ZenTreasure_Photo04",
		"ZenTreasure_Photo05",
		"ZenTreasure_Photo06",
		"ZenTreasure_Photo07",
		"ZenTreasure_Photo08",
		"ZenTreasure_Photo09",
		"ZenTreasure_Photo10",
		"ZenTreasure_Photo11",
		"ZenTreasure_Photo12",
		"ZenTreasure_Photo13",
		"ZenTreasure_Photo14",
		"ZenTreasure_Photo15",
		"ZenTreasure_Photo16",
		"ZenTreasure_Photo17",
		"ZenTreasure_Photo18",
		"ZenTreasure_Photo19",
		"ZenTreasure_Photo20",
		"ZenTreasure_Photo21",
		"ZenTreasure_Photo22",
		"ZenTreasure_Photo23",
		"ZenTreasure_Photo24",
		"ZenTreasure_Photo25"
	};

	ref static const array<string> GenericRewards =
	{
		"Expansion_Ammo_FlareSupplyRed",
		"ExpansionCodeLock",
		"NailBox_250",
		"ZenRandomAmmoBox",
		"NVGoggles",
		"Paper"
	};
}