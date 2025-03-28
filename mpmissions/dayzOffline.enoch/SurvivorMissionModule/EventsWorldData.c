class ZenMissionType
{
	string missionType;
	vector missionPosition;

	void ZenMissionType(string t, vector p)
	{
		missionType = t;
		missionPosition = p;
	}
};

class EventsWorldData extends SurvivorMissions
{
	const string EWD_MAP_NAME = "enoch";
	const string EWD_SCRIPT_VERSION = "0.85";
	static ref array<string> MissionEvents = new array<string>;
	static ref array<vector> MissionPositions = new array<vector>;
	static ref array<Object> ObjectList = new array<Object>; 
	static ref array<CargoBase> ObjectCargoList = new array<CargoBase>;
	
	// Zen missions
	static ref array<ref ZenMissionType> ZenMissions_Camp = new array<ref ZenMissionType>;
	static ref array<ref ZenMissionType> ZenMissions_Gardens = new array<ref ZenMissionType>;
	static ref array<ref ZenMissionType> ZenMissions_FixWells = new array<ref ZenMissionType>;
	static ref array<ref ZenMissionType> ZenMissions_FixPumps = new array<ref ZenMissionType>;
	static ref array<ref ZenMissionType> ZenMissions_HordeHummer = new array<ref ZenMissionType>;
	static ref array<ref ZenMissionType> ZenMissions_HordeHeli = new array<ref ZenMissionType>;
	static ref array<ref ZenMissionType> ZenMissions_PlaneCrash = new array<ref ZenMissionType>;
	static ref array<ref ZenMissionType> ZenMissions_CrocodileFish = new array<ref ZenMissionType>;
	static ref array<ref ZenMissionType> ZenMissions_LandMines = new array<ref ZenMissionType>;

	void EventsWorldData()
	{
		// Camps
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Lukow west MedTent_1", "3399.8 260.1 11760.1"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Lukow east MedTent_1", "4293.6 234.9 11666.2"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Polana south MedTent_1", "3315.9 470.7 1922.5"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Polana north MedTent_1", "3201.9 527.2 2294.3"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Polana east MedTent_1", "3658.5 538.3 2041.4"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Zalesie west MedTent_1", "502.5 287.5 5367.9"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Zalesie southeast MedTent_1", "1126.3 250.5 5140.9"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Sitnik east MedTent_1", "12040.5 230.6 9503.8"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Topolin west MedTent_1", "838 175.3 7568.7"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Wrzeszcz northeast MedTent_2", "9186.98 339.56 4597.68"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Tymbark northwest MedTent_2", "2460.11 442.42 1447.26"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Widok northeast MedTent_2", "10494.68 301.58 2315.76"));
		// Original camps
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Adamow west MedTent_1", "2717.5 281.5 6725.3"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Adamow east MedTent_1", "3407.5 226.9 6811.3 "));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Adamow southwest MedTent_1", "2906.6 309.6 6425.6 "));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Adamow east MedTent_1", "3407.5 226.9 6811.3"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Adamow northeast MedTent_1", "3532.1 214.6 7356.4"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Bielawa west MedTent_1", "1071.9 296.4 9630.2 3407.5 226.9 6811.3"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Bielawa south MedTent_1", "1245.4 274.9 9039.2"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Bielawa south MedTent_2", "1417.8 264.2 9364"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Bielawa south MedTent_3", "1464.6 265.2 9392.2"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Bielawa southeast MedTent_1", "1898.4 236.8 9339"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Bielawa southeast MedTent_2", "2028.2 241.6 9335.5"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Branzow_Castle west MedTent_1", "846.1 430.5 11368.4"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Branzow_Castle northwest MedTent_1", "7767.7 423.5 11597.7"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Branzow_Castle north MedTent_1", "981.1 369.8 11691.1"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Branzow_Castle south MedTent_1", "1047.7 352.8 11100.1"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Branzow_Castle northeast MedTent_1", "1199 334.7 11798"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Branzow_Castle east MedTent_1", "1708.1 304.6 11441.4"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Brena northwest MedTent_1", "6153.8 197.5 11493.6"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Brena southwest MedTent_1", "6260.2 171.5 10867.6"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Brena north MedTent_1", "6417.2 208 11677.4"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Brena east MedTent_1", "6825 179.9 11432.6"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Gliniska northwest MedTent_1", "4676.6 211.3 10127.9"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Gliniska east MedTent_1", "5530.8 171.1 9957.6"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Gliniska southeast MedTent_1", "5323.3 173.6 9534.2"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Grabin west MedTent_1", "10304.2 187.7 11041.6"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Grabin northwest MedTent_1", "10521.3 171.9 11332.7"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Grabin north MedTent_1", "10846.1 172.2 11283.8"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Grabin northeast MedTent_1", "11193.6 170.9 11230.7"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Kolembrody southwest MedTent_1", "8210.7 174.4 11925.9"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Kolembrody northwest MedTent_1", "8290.6 184.3 12098.6"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Kolembrody southeast MedTent_1", "8623.2 174.3 11962.3"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Lukow west MedTent_1", "3399.8 260.1 11760.1"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Lukow northwest MedTent_1", "3370.6 250.9 11897.6"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Lukow north MedTent_1", "3700 236 12561.5"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Lukow north MedTent_2", "3867.5 232 12244.7"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Lukow east MedTent_1", "4293.6 234.9 11666.2"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Lukow southwest MedTent_1", "3424.5 243.7 11079.6"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Nadbor west MedTent_1", "5530.3 400.1 4155.6"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Nadbor south MedTent_1", "5897.6 404.5 3838.5"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Nadbor southeast MedTent_1", "6123.6 375.5 3667.4"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Nadbor east MedTent_1", "6561.8 346.8 4224.4"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Olszanka north MedTent_1", "4881 262.1 7987.7"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Olszanka southeast MedTent_1", "5147.3 297.6 7360.5"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Polana north MedTent_1", "3201.9 527.2 2294.3"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Polana south MedTent_1", "3315.9 470.7 1922.5"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Polana east MedTent_1", "3658.5 538.3 2041.4"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Radacz west MedTent_1", "3500.5 197 8006.7"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Radacz north MedTent_1", "3966.4 195.6 8368.6"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Radacz south MedTent_1", "4067.3 231.2 7558.7"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Sitnik west MedTent_1", "11068.3 179.9 9671.1"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Sitnik northwest MedTent_1", "11241.8 182.9 9818.9"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Sitnik north MedTent_1", "11395.2 171 10124"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Sitnik southeast MedTent_1", "11871.7 196.7 9193.2"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Sitnik southeast MedTent_2", "11770.2 190.3 9091.9"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Sitnik east MedTent_1", "12040.5 230.6 9503.8"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Sobotka northwest MedTent_1", "5926.2 174.4 10391.3"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Sobotka northwest MedTent_2", "6045.4 177.6 10338.3"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Sobotka north MedTent_1", "6166.6 174.2 10634.3"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Sobotka north MedTent_2", "6346.5 170.3 10747.8"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Sobotka northeast MedTent_1", "6550.7 193.9 10451.6"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Tarnow west MedTent_1", "8816.9 252.3 10779.5"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Tarnow northwest MedTent_1", "9135.6 178 11446.1"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Tarnow northeast MedTent_1", "9703 183.4 11198.6"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Tarnow east MedTent_1", "9782.8 215.3 10788.5"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Tarnow southeast MedTent_1", "9753.9 260.8 10105.2"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Topolin west MedTent_1", "838 175.3 7568.7"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Topolin northwest MedTent_1", "900.1 172.1 7631.3"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Topolin northwest MedTent_2", "1106.4 191.8 7850.3"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Topolin southwest MedTent_1", "1392.6 230.3 7109.3"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Topolin north MedTent_1", "1440.3 192.7 7821.8"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Topolin south MedTent_1", "1667.6 241.2 7006.6"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Topolin east MedTent_1", "2119.5 226.2 7320.7"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Topolin east MedTent_2", "2619.2 230.5 7485.1"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Topolin northeast MedTent_1", "2181.9 171 7922.2"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Zalesie northwest MedTent_1", "453 288.7 5560.9"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Zalesie west MedTent_1", "502.5 287.5 5367.9"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Zalesie north MedTent_1", "1037 279.8 5898.4"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Zalesie southeast MedTent_1", "1126.3 250.5 5140.9"));
		ZenMissions_Camp.Insert(new ZenMissionType("Camp Zalesie northeast MedTent_1", "1258.4 283 5680.6"));

		// Plane Crash Missions
		ZenMissions_PlaneCrash.Insert(new ZenMissionType("PlaneCrash Nadbor south", "5864.22 410.49 3678.22"));
		ZenMissions_PlaneCrash.Insert(new ZenMissionType("PlaneCrash Gliniska north", "4551.51 219.70 10751.26"));
		ZenMissions_PlaneCrash.Insert(new ZenMissionType("PlaneCrash Zalesie east", "1127.59 271.96 5519.49"));
		ZenMissions_PlaneCrash.Insert(new ZenMissionType("PlaneCrash Polana southeast", "3806.87 518.67 1623.73"));
		ZenMissions_PlaneCrash.Insert(new ZenMissionType("PlaneCrash Dambog east", "1231.50 598.23 1093.91"));
		ZenMissions_PlaneCrash.Insert(new ZenMissionType("PlaneCrash Swarog southeast", "6851.05 402.40 1761.46"));
		ZenMissions_PlaneCrash.Insert(new ZenMissionType("PlaneCrash Dolnik northeast", "11935.13 318.53 944.09"));
		ZenMissions_PlaneCrash.Insert(new ZenMissionType("PlaneCrash Dolnik southwest", "10966.68 289.10 300.18"));
		ZenMissions_PlaneCrash.Insert(new ZenMissionType("PlaneCrash Kulno northeast", "11607.23 335.07 3186.33"));
		ZenMissions_PlaneCrash.Insert(new ZenMissionType("PlaneCrash Gieraltow northeast", "11394.50 298.19 5119.21"));
		ZenMissions_PlaneCrash.Insert(new ZenMissionType("PlaneCrash Lembork south", "9053.83 283.70 6182.35"));
		ZenMissions_PlaneCrash.Insert(new ZenMissionType("PlaneCrash Olszanka east", "5206.01 308.54 7723.14"));
		ZenMissions_PlaneCrash.Insert(new ZenMissionType("PlaneCrash Adamow north", "3117.72 239.33 7611.63"));
		ZenMissions_PlaneCrash.Insert(new ZenMissionType("PlaneCrash Topolin north", "1710.89 231.16 8498.72"));
		ZenMissions_PlaneCrash.Insert(new ZenMissionType("PlaneCrash Bielawa northwest", "1093.42 314.37 10070.15"));
		ZenMissions_PlaneCrash.Insert(new ZenMissionType("PlaneCrash Sitnik northeast", "11919.36 184.80 10219.73"));
		ZenMissions_PlaneCrash.Insert(new ZenMissionType("PlaneCrash Grabin northeast", "11283.79 173.52 11373.37"));
		ZenMissions_PlaneCrash.Insert(new ZenMissionType("PlaneCrash Gliniska northeast", "5444.83 177.83 10163.83"));
		ZenMissions_PlaneCrash.Insert(new ZenMissionType("PlaneCrash Brena northeast", "6848.12 176.52 11638.53"));
		ZenMissions_PlaneCrash.Insert(new ZenMissionType("PlaneCrash KopaPrison southeast", "5754.04 262.65 8364.79"));
		ZenMissions_PlaneCrash.Insert(new ZenMissionType("PlaneCrash Lukow west", "2850.18 283.82 12034.53"));
		ZenMissions_PlaneCrash.Insert(new ZenMissionType("PlaneCrash Lukow east", "4896.90 220.22 11566.60"));
		ZenMissions_PlaneCrash.Insert(new ZenMissionType("PlaneCrash Nadbor northwest", "5285.40 375.65 4714.04"));

		// Garden Mission
		ZenMissions_Gardens.Insert(new ZenMissionType("GardensAtWell Topolin", "0 0 0"));
		ZenMissions_Gardens.Insert(new ZenMissionType("GardensAtWell Kolembrody", "0 0 0"));
		ZenMissions_Gardens.Insert(new ZenMissionType("GardensAtWell Gliniska", "0 0 0"));
		ZenMissions_Gardens.Insert(new ZenMissionType("GardensAtWell Bielawa", "0 0 0"));
		ZenMissions_Gardens.Insert(new ZenMissionType("GardensAtWell Radacz", "0 0 0"));
		ZenMissions_Gardens.Insert(new ZenMissionType("GardensAtWell Olszanka", "0 0 0"));
		ZenMissions_Gardens.Insert(new ZenMissionType("GardensAtWell Sitnik", "0 0 0"));
		ZenMissions_Gardens.Insert(new ZenMissionType("GardensAtWell Brena", "0 0 0"));
		ZenMissions_Gardens.Insert(new ZenMissionType("GardensAtWell Grabin", "0 0 0"));
		
		// Hordes
		ZenMissions_HordeHeli.Insert(new ZenMissionType("HordeHeli Gliniska SouthWest WhatsThis", "4817.159180 176.272461 9109.655273"));
		ZenMissions_HordeHeli.Insert(new ZenMissionType("HordeHeli Radacz NorthEast WhatsThis", "4460.278809 186.064316 8438.410156"));
		ZenMissions_HordeHeli.Insert(new ZenMissionType("HordeHeli Bielawa NorthWest WhatsThis", "1104.69 0 10031.25"));
		ZenMissions_HordeHeli.Insert(new ZenMissionType("HordeHeli Bielawa East WhatsThis", "2800.00 0 9901.56"));
		ZenMissions_HordeHeli.Insert(new ZenMissionType("HordeHeli Topolin East WhatsThis", "3028.13 0 7662.50"));
		ZenMissions_HordeHeli.Insert(new ZenMissionType("HordeHeli Sitnik NorthEast WhatsThis", "11892.19 0 10200.00"));
		ZenMissions_HordeHeli.Insert(new ZenMissionType("HordeHeli Grabin SouthWest WhatsThis", "10381.25 0 10603.13"));
		ZenMissions_HordeHeli.Insert(new ZenMissionType("HordeHeli Tarnow South WhatsThis", "9262.50 0 10065.63"));
		ZenMissions_HordeHeli.Insert(new ZenMissionType("HordeHeli Tarnow SouthEast WhatsThis", "9945.31 0 9787.50"));
		ZenMissions_HordeHeli.Insert(new ZenMissionType("HordeHeli Borek East WhatsThis", "10504.69 0 8506.25"));
		ZenMissions_HordeHeli.Insert(new ZenMissionType("HordeHeli Sobotka South_East WhatsThis", "6637.50 0 9967.19"));
		ZenMissions_HordeHeli.Insert(new ZenMissionType("HordeHeli Brena NorthEast WhatsThis", "6637.50 0 9967.19"));
		ZenMissions_HordeHeli.Insert(new ZenMissionType("HordeHeli Nadbor East WhatsThis", "6561.72 0 3890.63"));
		ZenMissions_HordeHeli.Insert(new ZenMissionType("HordeHeli Nadbor SouthWest WhatsThis", "5863.28 0 3767.19"));
		ZenMissions_HordeHeli.Insert(new ZenMissionType("HordeHeli Nadbor SouthWest WhatsThis", "4501.56 0 7362.50"));
		ZenMissions_HordeHeli.Insert(new ZenMissionType("HordeHeli Lukow South WhatsThis", "3500.00 0 11351.56"));
		ZenMissions_HordeHeli.Insert(new ZenMissionType("HordeHeli Krsnik SouthWest WhatsThis", "7620.31 0 9943.75"));
		ZenMissions_HordeHummer.Insert(new ZenMissionType("HordeHummer Branzow DIRECTION WhatsThis", "2229.592041 283.048218 10694.083008"));
		ZenMissions_HordeHummer.Insert(new ZenMissionType("HordeHummer Krsnik DIRECTION WhatsThis", "7878.262695 320.536133 9810.842773"));
		ZenMissions_HordeHummer.Insert(new ZenMissionType("HordeHummer Lembork DIRECTION WhatsThis", "9176.176758 295.182617 6679.515625"));
		ZenMissions_HordeHummer.Insert(new ZenMissionType("HordeHummer Muratyn DIRECTION WhatsThis", "4383.537598 316.888641 6780.313965"));
		ZenMissions_HordeHummer.Insert(new ZenMissionType("HordeHummer Nadbor DIRECTION WhatsThis", "5561.923828 421.591705 3870.604736"));
		ZenMissions_HordeHummer.Insert(new ZenMissionType("HordeHummer Swarog DIRECTION WhatsThis", "5115.285645 505.156311 2164.364746"));
		ZenMissions_HordeHummer.Insert(new ZenMissionType("HordeHummer Rodzanica DIRECTION WhatsThis", "8879.224609 468.503113 2094.059570"));
		ZenMissions_HordeHummer.Insert(new ZenMissionType("HordeHummer Dambog DIRECTION WhatsThis", "894.588135 530.099976 1191.105957"));
		
		// Family car
		ZenMissions_CrocodileFish.Insert(new ZenMissionType("CrocodileFish Karlin northeast", "12309.312500 225.196518 7963.136719"));
		ZenMissions_CrocodileFish.Insert(new ZenMissionType("CrocodileFish Karlin northeast", "11801.679688 188.198639 9006.2519530"));
		ZenMissions_CrocodileFish.Insert(new ZenMissionType("CrocodileFish Karlin northeast", "11623.408203 171.638824 10499.048828"));
		ZenMissions_CrocodileFish.Insert(new ZenMissionType("CrocodileFish Karlin northeast", "12264.320313 170.662582 10995.285156"));
		ZenMissions_CrocodileFish.Insert(new ZenMissionType("CrocodileFish Karlin northeast", "10603.063477 171.199524 11390.070313"));
		ZenMissions_CrocodileFish.Insert(new ZenMissionType("CrocodileFish Karlin northeast", "9760.9794920 171.589066 11764.537109"));
		ZenMissions_CrocodileFish.Insert(new ZenMissionType("CrocodileFish Karlin northeast", "8292.3583980 170.999542 11908.896484"));
		ZenMissions_CrocodileFish.Insert(new ZenMissionType("CrocodileFish Karlin northeast", "6816.0546880 172.758011 11029.018555"));
		ZenMissions_CrocodileFish.Insert(new ZenMissionType("CrocodileFish Karlin northeast", "6082.8925780 171.797272 10663.297852"));
		ZenMissions_CrocodileFish.Insert(new ZenMissionType("CrocodileFish Karlin northeast", "4394.2983400 171.597427 8690.4472660"));
		ZenMissions_CrocodileFish.Insert(new ZenMissionType("CrocodileFish Karlin northeast", "3699.1401370 170.936356 9021.2529300"));
		ZenMissions_CrocodileFish.Insert(new ZenMissionType("CrocodileFish Karlin northeast", "2745.6599120 174.621109 8332.3125000"));
		ZenMissions_CrocodileFish.Insert(new ZenMissionType("CrocodileFish Karlin northeast", "639.567444 171.053757 7601.560547"));
		ZenMissions_CrocodileFish.Insert(new ZenMissionType("CrocodileFish Karlin northeast", "747.692871 222.655701 8509.220703"));
		ZenMissions_CrocodileFish.Insert(new ZenMissionType("CrocodileFish Karlin northeast", "1769.349609 304.962524 11424.663086"));
		ZenMissions_CrocodileFish.Insert(new ZenMissionType("CrocodileFish Karlin northeast", "3702.380371 235.591431 12559.516602"));
		ZenMissions_CrocodileFish.Insert(new ZenMissionType("CrocodileFish Karlin northeast", "11315.505859 253.269043 12525.094727"));
		ZenMissions_CrocodileFish.Insert(new ZenMissionType("CrocodileFish Karlin northeast", "10595.360352 232.54280 1376.095093"));
		ZenMissions_CrocodileFish.Insert(new ZenMissionType("CrocodileFish Karlin northeast", "4249.100098 381.559113 3067.340088"));
		ZenMissions_CrocodileFish.Insert(new ZenMissionType("CrocodileFish Karlin northeast", "1164.723022 249.291687 5206.353516"));
		ZenMissions_CrocodileFish.Insert(new ZenMissionType("CrocodileFish Karlin northeast", "6851.519531 208.927032 8154.929688"));
		ZenMissions_CrocodileFish.Insert(new ZenMissionType("CrocodileFish Karlin northeast", "6664.194824 205.276917 8840.819336"));
		ZenMissions_CrocodileFish.Insert(new ZenMissionType("CrocodileFish Karlin northeast", "8142.251465 246.343964 5407.369141"));
		ZenMissions_CrocodileFish.Insert(new ZenMissionType("CrocodileFish Karlin northeast", "11425.244141 229.905548 1056.244873"));
		ZenMissions_CrocodileFish.Insert(new ZenMissionType("CrocodileFish Karlin northeast", "10911.898438 185.342087 9249.338867"));

		// Land mines 
		ZenMissions_LandMines.Insert(new ZenMissionType("LandMines Where", "4850.00 0 11725.00"));
		ZenMissions_LandMines.Insert(new ZenMissionType("LandMines Where", "1656.25 0 8518.75"));
		ZenMissions_LandMines.Insert(new ZenMissionType("LandMines Where", "5278.13 0 7490.63"));
		ZenMissions_LandMines.Insert(new ZenMissionType("LandMines Where", "943.75 0 4860.94"));
		ZenMissions_LandMines.Insert(new ZenMissionType("LandMines Where", "5948.44 0 3626.56"));
		ZenMissions_LandMines.Insert(new ZenMissionType("LandMines Where", "11051.56 0 4749.22"));
		ZenMissions_LandMines.Insert(new ZenMissionType("LandMines Where", "10953.13 0 8684.38"));
		ZenMissions_LandMines.Insert(new ZenMissionType("LandMines Where", "12025.00 0 10330.47"));
		ZenMissions_LandMines.Insert(new ZenMissionType("LandMines Where", "8889.84 0 12114.84"));
		ZenMissions_LandMines.Insert(new ZenMissionType("LandMines Where", "3857.81 0 10918.75"));
		ZenMissions_LandMines.Insert(new ZenMissionType("LandMines Where", "357.81 0 10845.31"));
		ZenMissions_LandMines.Insert(new ZenMissionType("LandMines Where", "271.09 0 8931.25"));
		ZenMissions_LandMines.Insert(new ZenMissionType("LandMines Where", "11856.25 0 954.69"));
		ZenMissions_LandMines.Insert(new ZenMissionType("LandMines Where", "3750.00 0 1589.06"));
		ZenMissions_LandMines.Insert(new ZenMissionType("LandMines Where", "2566.41 0 5125.00"));
		ZenMissions_LandMines.Insert(new ZenMissionType("LandMines Where", "9474.22 0 8377.34"));
		ZenMissions_LandMines.Insert(new ZenMissionType("LandMines Where", "8267.19 0 11553.13"));
		ZenMissions_LandMines.Insert(new ZenMissionType("LandMines Where", "6999.22 0 12154.69"));
		ZenMissions_LandMines.Insert(new ZenMissionType("LandMines Where", "5962.50 0 9756.25"));
		ZenMissions_LandMines.Insert(new ZenMissionType("LandMines Where", "4509.38 0 8428.13"));
		ZenMissions_LandMines.Insert(new ZenMissionType("LandMines Where", "968.75 0 6921.88"));
		ZenMissions_LandMines.Insert(new ZenMissionType("LandMines Where", "3085.94 0 7671.88"));
		ZenMissions_LandMines.Insert(new ZenMissionType("LandMines Where", "11521.88 0 7503.13"));
		ZenMissions_LandMines.Insert(new ZenMissionType("LandMines Where", "12320.31 0 7318.75"));
		ZenMissions_LandMines.Insert(new ZenMissionType("LandMines Where", "12070.31 0 5892.19"));
		ZenMissions_LandMines.Insert(new ZenMissionType("LandMines Where", "11050.00 0 507.81"));
		ZenMissions_LandMines.Insert(new ZenMissionType("LandMines Where", "7809.38 0 6392.19"));
		
		// Repair wells 
		ZenMissions_FixWells.Insert(new ZenMissionType("FixWells Well", "894.588135 530.099976 1191.105957"));
		
		// Repair pumps 
		//ZenMissions_FixPumps.Insert(new ZenMissionType("FixPumps Pump", "0 0 0"));

		// Insert a random mission from each category

		// Hummer heli
		ZenMissionType heliHordeMission = ZenMissions_HordeHeli.GetRandomElement();
		MissionEvents.Insert(heliHordeMission.missionType);
		MissionPositions.Insert(heliHordeMission.missionPosition);

		// Hummer horde
		ZenMissionType hummerHordeMission = ZenMissions_HordeHummer.GetRandomElement();
		MissionEvents.Insert(hummerHordeMission.missionType);
		MissionPositions.Insert(hummerHordeMission.missionPosition);

		// Wells
		ZenMissionType fixWellMission = ZenMissions_FixWells.GetRandomElement();
		MissionEvents.Insert(fixWellMission.missionType);
		MissionPositions.Insert(fixWellMission.missionPosition);

		// Camps
		ZenMissionType campsMission = ZenMissions_Camp.GetRandomElement();
		MissionEvents.Insert(campsMission.missionType);
		MissionPositions.Insert(campsMission.missionPosition);

		if (!IsWinter())
		{
			// gardens
			ZenMissionType gardenMission = ZenMissions_Gardens.GetRandomElement();
			MissionEvents.Insert(gardenMission.missionType);
			MissionPositions.Insert(gardenMission.missionPosition);
			
			// land mines in grass
			ZenMissionType LandMines = ZenMissions_LandMines.GetRandomElement();
			MissionEvents.Insert(LandMines.missionType);
			MissionPositions.Insert(LandMines.missionPosition);
		}
		
		// Plane Crash
		ZenMissionType planeMission = ZenMissions_PlaneCrash.GetRandomElement();
		MissionEvents.Insert(planeMission.missionType);
		MissionPositions.Insert(planeMission.missionPosition);

		
		// Crocodiles or Polar Bears
		ZenMissionType CrocodileFish = ZenMissions_CrocodileFish.GetRandomElement();
		MissionEvents.Insert(CrocodileFish.missionType);
		MissionPositions.Insert(CrocodileFish.missionPosition);
	}
	
	static void BuildInstance()
	{
		if (m_MissionType == "Camp")				m_MissionInstance = new CampMission();
		if (m_MissionType == "GardensAtWell")		m_MissionInstance = new GardensAtWellMission();
		if (m_MissionType == "FixWells")			m_MissionInstance = new FixWellsMission();
		if (m_MissionType == "HordeHummer")			m_MissionInstance = new HordeHummerMission();
		if (m_MissionType == "HordeHeli")			m_MissionInstance = new HordeHeliMission();
		if (m_MissionType == "PlaneCrash")			m_MissionInstance = new PlaneCrashMission();
		if (m_MissionType == "CrocodileFish")		m_MissionInstance = new CrocodileFishMission();
		if (m_MissionType == "FixPumps")			m_MissionInstance = new FixPumpsMission();
		if (m_MissionType == "LandMines")			m_MissionInstance = new LandMinesMission();
	}
		
	static bool GetBuildingsAtLoc( string MBuilding, string MLocation, out array<vector> BuildingPosList )
	{
		//Get positions of a unique mission building by the town/village name
		BuildingPosList = new array<vector>;
		
		if ( MBuilding == "Land_Village_PoliceStation_Enoch")
		{
			if ( MLocation == "Brena") 						BuildingPosList.Insert("6488.9 195.6 11373.7");
			else if ( MLocation == "Dolnik")				BuildingPosList.Insert("11531.1 219.3 505.9");
			else if ( MLocation == "Gieraltow")				BuildingPosList.Insert("11466.6 336.7 4559.7");
			else if ( MLocation == "Grabin") 				BuildingPosList.Insert("10545.3 186.7 11120.1");
			else if ( MLocation == "Lukow") 				BuildingPosList.Insert("3671 258.9 11778.3");
			else if ( MLocation == "Nadbor") 				BuildingPosList.Insert("5956.5 403.8 4130");
			else if ( MLocation == "Sitnik") 				BuildingPosList.Insert("11646.5 195.4 9614.5");
			else if ( MLocation == "Tarnow") 				BuildingPosList.Insert("9297.3 206.6 10848.3");
			else return false;			//No match by location						
		}
		else if ( MBuilding == "Land_FuelStation_Build_Enoch" || MBuilding == "Land_FuelStation_Build")
		{
			if ( MLocation == "Brena")						BuildingPosList.Insert("6383.8 176.3 11003.4");
			else if ( MLocation == "Nadbor")				BuildingPosList.Insert("6253.5 384.3 3941.2");
			else if ( MLocation == "Polana")				BuildingPosList.Insert("3328.7 488.8 2041.5");
			else if ( MLocation == "Sitnik")				BuildingPosList.Insert("11532.8 182.9 9463.4");
			else if ( MLocation == "Topolin")				BuildingPosList.Insert("2014.8 209.9 7364.9");
			else if ( MLocation == "Widok")					BuildingPosList.Insert("10227 244.3 2161.8");
			else return false;			//No match by location
		}
		else if ( MBuilding == "Land_Misc_TrailRoof_Small")
		{
			if ( MLocation == "Gieraltow")					BuildingPosList.Insert("11106.3 347.2 4332.4");
			else if ( MLocation == "Jantar_Lake")			BuildingPosList.Insert("3661.9 184.3 8910.9");
			else if ( MLocation == "Kolembrody")			BuildingPosList.Insert("8403.8 175.5 11829");
			else if ( MLocation == "Nadbor")				BuildingPosList.Insert("5944.6 395.4 3954.8");
			else if ( MLocation == "Radacz")				BuildingPosList.Insert("4042.1 209.4 7937.6");
			else if ( MLocation == "Swarog")				BuildingPosList.Insert("5143.8 476 2357.4");
			else return false;			//No match by location
		}		
		else if ( MBuilding == "Land_City_School")
		{
			if ( MLocation == "Berezino")					BuildingPosList.Insert("12168.3 17.1 9757.0");
			else if ( MLocation == "Elektrozavodsk")		BuildingPosList.Insert("10223.2 29.2 2574.0");
			else if ( MLocation == "NovayaPetrovka")		BuildingPosList.Insert("3246.1 208.7 13045.8");	
			else if ( MLocation == "Severograd")			BuildingPosList.Insert("8658.1 110.5 12803.7");	
			else if ( MLocation == "Vysotovo")				BuildingPosList.Insert("5695.7 76.7 2562.8");
			else return false;			//No match by location	
		}
		else	
			return false;		//No match by building type. Keep this line after last building check!
		
		return true;
	}
	
	static void CheckEWD()
	{
		int ErrorCount = 0;
		
		for ( int i=0; i < MissionPositions.Count(); i++)
		{
			string Description[4];
			string EventName = MissionEvents.Get(i);
			vector Position = MissionPositions.Get(i);
			
			EventName.ParseString( Description );
			string Type = Description[0];
			string Location = Description[1];
			string LocDirection = Description[2];
			string Secondary = Description[3];
			
			//check for primary MissionBuilding, exclude missions with no primary MissionBuilding 
			if ( !PrimaryMissionCHK( Type, Position, i )) 
			{
				ErrorCount++;
				Print("[SEM] EWD Check additional mission Info : Type: "+ Type +" mission, location: "+ LocDirection +" of "+ Location +", Secondary mission:"+ Secondary );
			}
			//check for secondary MissionBuilding, exclude missions with no secondary MissionBuilding
			else if ( !SecondaryMissionCHK( Type, Secondary, i )) 
			{
				ErrorCount++;
				Print("[SEM] EWD Check additional mission Info : Type: "+ Type +" mission, location: "+ LocDirection +" of "+ Location +", Secondary mission:"+ Secondary );
			}						
		}
		if ( ErrorCount == 0 ) Print("[SEM] EWD check...OK");
		else Print("[SEM] EWD Check Summary: "+ ErrorCount +" missions have incorrect EventsWorldData. Check coordinates in debug mode!");	
	}
	
	static bool PrimaryMissionCHK( string type, vector position , int nr )
	{
		//List all mission types with no prim. MissionBuilding here!
		array<string> ExcludedTypes = new array<string>;
		ExcludedTypes.InsertArray( {"Camp","Psilos","Graveyard","BearHunt","PlaneCrash","Horde"} );	
		string building;
		bool BuildingFound;
				
		for ( int i=0; i < ExcludedTypes.Count(); i++)	{ if ( type == ExcludedTypes.Get(i) ) return true;}
		
		//Add new mission type and building type for primary mission here!
		if ( type == "Apartment")					building = "Land_Tenement_Small";
		else if ( type == "CityMall")				building = "Land_City_Store";
		else if ( type == "FreePigs")				building = "Land_Farm_CowshedA";
		else if ( type == "Ganja")					building = "Land_Garage_Row_Small";
		else if ( type == "UrbanMall")				building = "Land_City_Store_WithStairs";
		else 
		{
			Print("[SEM] EWD Check WARNING : Mission "+ nr +" - Mission type "+ type +" is undefined in EventsWorldData!");
			return false;
		}
				
		BuildingFound = false;
		
		GetGame().GetObjectsAtPosition( position, 1.0, ObjectList, ObjectCargoList);
		for ( int j=0; j < ObjectList.Count(); j++)
		{
			Object FoundObject = ObjectList.Get(j);
			if ( FoundObject.GetType() != building )
			continue;
			else 
			{
				BuildingFound = true;
				break;
			}						
		}
		if ( !BuildingFound ) 
		{
			Print("[SEM] EWD Check WARNING :: Mission "+ nr +" - Can't find "+ building +" @ "+ position );
			return false;		
		}
		else return true;		
	}	
	
	static bool SecondaryMissionCHK( string type, string location, int nr )
	{
		//List all mission types with no sec. MissionBuilding here!
		array<string> ExcludedTypes = new array<string>;
		ExcludedTypes.InsertArray( {"Apartment","Camp","Graveyard","PlaneCrash","Horde"} );
		
		array<vector> ExtendedPosList = new array<vector>;
		string building;
		bool BuildingFound;
		
		for ( int i=0; i < ExcludedTypes.Count(); i++)	{ if ( type == ExcludedTypes.Get(i) ) return true;}
		
		//Add new mission type and building type for secondary mission here!
		if ( type == "BearHunt")					building = "Land_City_School";
		else if ( type == "CityMall")				building = "Land_Village_PoliceStation";
		else if ( type == "FreePigs")				building = "Land_Misc_TrailRoof_Small";
		else if ( type == "Psilos")					building = "Land_Village_PoliceStation_Enoch";
		else if ( type == "Ganja")
		{
			if ( location == "Widok")				building = "Land_FuelStation_Build";
			else 									building = "Land_FuelStation_Build_Enoch";
		}
		else if ( type == "UrbanMall")				building = "Land_City_PoliceStation";
		else
		{
			Print("[SEM] EWD Check WARNING :: Mission "+ nr +" - Mission type "+ type +" is undefined in EventsWorldData!");
			return false;
		}
		
		if ( GetBuildingsAtLoc( building, location, ExtendedPosList ))
		{
			for ( int k=0; k < ExtendedPosList.Count(); k++)
			{
				BuildingFound = false;
				
				vector pos = ExtendedPosList.Get(k);
				
				GetGame().GetObjectsAtPosition( pos, 1.0, ObjectList, ObjectCargoList);
				for ( int j=0; j < ObjectList.Count(); j++)
				{
					Object FoundObject = ObjectList.Get(j);
					if ( FoundObject.GetType() != building )
					continue;
					else 
					{
						BuildingFound = true;
						break;
					}							
				}
				if ( !BuildingFound ) 
				{
					Print("[SEMM] EWD Check WARNING :: Mission "+ nr +" - Can't check back "+ building +" at position: "+ pos );								
					return false;
				}
			}
			return true;			
		}
		else 
		{
			Print("[SEM] EWD Check WARNING :: Mission "+ nr +" - Can't check back "+ building +" at location: "+ location );
			return false;
		}
	}
	
	void BuildStatics()
	{
		//add static buildings / objects here. This function must be activated in MissionSettings!
	}
	
	static void ShowDebugInfo( PlayerBase player)
	{
		//Display as server message to player: if found, Modelvector & buildingtype else actual position of player
		Param1<string> Msg1;
		array<Object> OBJLST1 = new array<Object>;
		array<CargoBase> PROXYLST1 = new array<CargoBase>;
			
		GetGame().GetObjectsAtPosition( player.GetPosition() , 30.0 , OBJLST1 , PROXYLST1 );		
		for ( int j = 0 ; j < OBJLST1.Count(); j++ )
		{ 
			Object FoundObject = OBJLST1.Get(j);
			if (FoundObject.GetType() == "Land_City_Store") 
			{
				Msg1 = new Param1<string> ("City_Store, Pos.: " + FoundObject.GetPosition().ToString() + " Modelvector: " + (FoundObject.WorldToModel( player.GetPosition())).ToString());
				GetGame().RPCSingleParam( player, ERPCs.RPC_USER_ACTION_MESSAGE, Msg1, true, player.GetIdentity());
				break;
			}
			else if (FoundObject.GetType() == "Land_City_School")
			{
				Msg1 = new Param1<string> ("City_School, Pos.: " + FoundObject.GetPosition().ToString() + " Modelvector: " + (FoundObject.WorldToModel( player.GetPosition())).ToString());
				GetGame().RPCSingleParam( player, ERPCs.RPC_USER_ACTION_MESSAGE, Msg1, true, player.GetIdentity());
				break;
			}			
			else if (FoundObject.GetType() == "Land_Farm_CowshedA")
			{
				Msg1 = new Param1<string> ("CowshedA, Pos.: " + FoundObject.GetPosition().ToString() + " Modelvector: " + (FoundObject.WorldToModel( player.GetPosition())).ToString());
				GetGame().RPCSingleParam( player, ERPCs.RPC_USER_ACTION_MESSAGE, Msg1, true, player.GetIdentity());
				break;
			}			
			else if (FoundObject.GetType() == "Land_Tenement_Small")
			{
				Msg1 = new Param1<string> ("Tenement_Small, Pos.: " + FoundObject.GetPosition().ToString() + " Modelvector: " + (FoundObject.WorldToModel( player.GetPosition())).ToString());
				GetGame().RPCSingleParam( player, ERPCs.RPC_USER_ACTION_MESSAGE, Msg1, true, player.GetIdentity());
				break;
			}			
			else if (FoundObject.GetType() == "Land_Tenement_Big")
			{
				Msg1 = new Param1<string> ("Tenement_Big, Pos.: " + FoundObject.GetPosition().ToString() + " Modelvector: " + (FoundObject.WorldToModel( player.GetPosition())).ToString());
				GetGame().RPCSingleParam( player, ERPCs.RPC_USER_ACTION_MESSAGE, Msg1, true, player.GetIdentity());
				break;
			}
			else if (FoundObject.GetType() == "Land_Garage_Row_Small")
			{
				Msg1 = new Param1<string> ("Garage_Row_Small, Pos.: " + FoundObject.GetPosition().ToString() + " Modelvector: " + (FoundObject.WorldToModel( player.GetPosition())).ToString());
				GetGame().RPCSingleParam( player, ERPCs.RPC_USER_ACTION_MESSAGE, Msg1, true, player.GetIdentity());
				break;
			}
			else if (FoundObject.GetType() == "Land_Garage_Row_Big")
			{
				Msg1 = new Param1<string> ("Garage_Row_Big, Pos.: " + FoundObject.GetPosition().ToString() + " Modelvector: " + (FoundObject.WorldToModel( player.GetPosition())).ToString());
				GetGame().RPCSingleParam( player, ERPCs.RPC_USER_ACTION_MESSAGE, Msg1, true, player.GetIdentity());
				break;
			}
			else if (FoundObject.GetType().Contains("Land_"))
			{
				Msg1 = new Param1<string> ( FoundObject.GetType() +", Pos.: " + FoundObject.GetPosition().ToString() + " Modelvector: " + (FoundObject.WorldToModel( player.GetPosition())).ToString());
				GetGame().RPCSingleParam( player, ERPCs.RPC_USER_ACTION_MESSAGE, Msg1, true, player.GetIdentity());
				//break;
			}									
		}
		
		if ( j == OBJLST1.Count() )
		{
			Msg1 = new Param1<string> ("My position is: " + player.GetPosition().ToString() );
			GetGame().RPCSingleParam( player, ERPCs.RPC_USER_ACTION_MESSAGE, Msg1, true, player.GetIdentity());
			
			vector ori = player.GetOrientation();
			float heading = ori[0];
			if ( heading < 0 ) heading += 360;
			
			Msg1 = new Param1<string> ("Heading: "+ heading.ToString() +"°" );
			GetGame().RPCSingleParam( player, ERPCs.RPC_USER_ACTION_MESSAGE, Msg1, true, player.GetIdentity());				
			j = 0;
		} 			
	}
	
	static void RCMapByBuilding( string MBuilding )
	{
		//Runs a raycast from the middle of the map and prints all buildings of desired type 
		array<Object> Objects = new array<Object>;
		array<CargoBase> ObjectCargos = new array<CargoBase>;
		float vertex;
		vector Center = "7680 0 7680";		//Livonia terrain center position
				
		if ( Center[0] < Center[2] ) vertex = Center[2];
		else vertex = Center[0];
		
		Print("[SEM] DEBUG MODE: Map wide raycast for:  "+ MBuilding );	
		
		float Rad = vertex * 1.414214;
				
		Print("[SEM] Map: "+ GetGame().GetWorldName() +" Center: "+ Center +", Radius: "+ Rad ); 
		 
		GetGame().GetObjectsAtPosition( Center, Rad, Objects, ObjectCargos );
		for ( int i=0; i < Objects.Count(); i++ )
		{
			Object FoundObject = Objects.Get(i);
			if ( FoundObject && FoundObject.GetType() == MBuilding )
			{
				Print("[SEM] Found building "+ MBuilding +" @ "+ FoundObject.GetPosition().ToString() );
			}
		}
		Print("[SEM] DEBUG MODE: Map wide raycast END");		
	}
}