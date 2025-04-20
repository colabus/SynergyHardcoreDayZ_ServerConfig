static const string SINGLE_SYN_SPAWN_STUFF = "$mission:storage_%1/data/synsinglespawn.bin";

static void SynSpawnCustomAreas()
{
	int spawnSpot = Math.RandomIntInclusive(1, 2);
	EntityAI dog;
	
	if (spawnSpot == 1) // Near the fire..
		dog = EntityAI.Cast(SpawnObject("Doggo_Stay13", "5777.258789 16.899967 10770.148438", "179.775299 -0.223809 0.224689", 1));
	else if (spawnSpot == 2)
		dog = EntityAI.Cast(SpawnObject("Doggo_Stay13", "5771.737793 16.959957 10767.078125", "105.021355 -0.041453 0.314415", 1));

	if (dog)
	{
		dog.SetAllowDamage(false);
//	 	Dayz_Doggo doggo = Dayz_Doggo.Cast(dog);
//		if (doggo)
//		{
//			doggo.SetAmbient(2);
//		}
	}
	
	// THESE ARE PERSISTENT OBJECTS! ONLY SPAWN ONCE AFTER FRESH WIPE!
	string singleSpawnFileName = string.Format(SINGLE_SYN_SPAWN_STUFF, GetGame().ServerConfigGetInt("instanceId"));
	if (!FileExist(singleSpawnFileName))
	{
		SynSpawn_SingleSpawnStuff();
		
		FileSerializer serializer = new FileSerializer();
		if (serializer.Open(singleSpawnFileName, FileMode.WRITE))
		{
			serializer.Write(1);
			serializer.Close();
		}
	}
	
	float delayTime = 1;
	GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(SynSpawn_Sanctuary, delayTime, false);
	delayTime += 50;
}

static void SynSpawn_SingleSpawnStuff()
{
	// Sanctuary stone oven
	SpawnObject("Syn_EternalStoneOvenFireplace", "5777.181641 16.862873 10771.964844", "-127.392448 0.000000 -0.000000>", 0.999999);
	
	// Community barrels
	SpawnObject("Syn_BarrelHoles_Red", "5759.927246 16.883673 10763.650391", "0 0 0", 1);
}

static void SynSpawn_Sanctuary()
{
	// Sanctuary
	//SpawnObject("Syn_SpotlightObject", "5811.499512 16.750454 10759.947266", "0.000000 -0.000000 -0.000000", 1);
	//SpawnObject("Syn_SpotlightObject", "5788.279785 16.835173 10757.712891", "0.000000 -0.000000 -0.000000", 1);
	//SpawnObject("Syn_SpotlightObject", "5784.108398 16.848587 10758.217773", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("dz/structures/furniture/lighting/fluor_lamp/fluor_lamp.p3d", "5775.987305 25.414631 10796.843750", "1.652580 0.000000 -0.000000", 0.99992);
	SpawnObject("Syn_InteriorLight", "5775.854004 25.018642 10796.854492", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("dz/structures/furniture/lighting/fluor_lamp/fluor_lamp.p3d", "5770.503906 25.448242 10797.190430", "1.652580 0.000000 -0.000000", 0.99992);
	SpawnObject("Syn_InteriorLight", "5770.370605 25.052254 10797.201172", "-0.000602 0.000000 -0.000000", 0.999877);
	SpawnObject("dz/structures/furniture/lighting/fluor_lamp/fluor_lamp.p3d", "5769.984375 21.062061 10793.815430", "0.104877 0.000000 -0.000000", 0.999854);
	SpawnObject("Syn_InteriorLight", "5769.971191 20.666187 10793.685547", "-88.679596 0.000000 -0.000000", 0.999384);
	//SpawnObject("Syn_SpotlightObject", "5776.711426 48.460110 10743.122070", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("Syn_InteriorLight", "5762.137207 21.493420 10750.784180", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("Syn_InteriorLight", "5770.265137 21.558685 10750.145508", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("dz/plants/tree/t_piceaabies_1s.p3d", "5784.503906 16.850029 10795.321289", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("dz/plants_bliss/tree/d_piceaabies_fallene.p3d", "5784.211914 18.751055 10737.970703", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("dz/plants_sakhal/dark/b_piceaabies_1fb_dark.p3d", "5786.856445 18.218155 10738.484375", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("dz/plants_sakhal/clutter/c_piceacluster.p3d", "5787.770020 18.147366 10738.699219", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("dz/plants_bliss/tree/t_piceaabies_1s_summer.p3d", "5783.041016 18.416838 10741.072266", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("dz/plants_bliss/tree/t_piceaabies_1s_summer.p3d", "5770.822754 19.316814 10742.660156", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("dz/plants_bliss/tree/b_piceaabies_1fb_summer.p3d", "5758.817383 18.870079 10744.386719", "-0.000014 0.000000 -0.000000", 0.999916);
	SpawnObject("dz/plants/bush/b_naked_2s.p3d", "5758.671875 19.171005 10745.974609", "-0.000014 0.000000 -0.000000", 0.999915);
	SpawnObject("dz/plants/tree/b_piceaabies_1f.p3d", "5757.988770 18.385172 10748.734375", "-0.000014 0.000000 -0.000000", 0.999916);
	SpawnObject("dz/structures/military/airfield/proxy/mil_radar_mobile_generator.p3d", "5783.335938 16.889942 10751.841797", "0.098517 0.000000 -0.000000", 0.999981);
	SpawnObject("StaticObj_Wall_IndCnc4_Pole", "5753.914063 18.245447 10763.019531", "-175.851242 0.000000 -0.000003", 0.999437);
	SpawnObject("StaticObj_Wall_Tin7_4", "5753.874512 18.054585 10760.798828", "90.358246 -0.000000 -0.000001", 0.999369);
	SpawnObject("StaticObj_Wall_Tin7_4", "5753.841309 18.417561 10756.312500", "90.358238 -0.000000 -0.000001", 0.999369);
	SpawnObject("StaticObj_Wall_IndCnc4_Pole", "5753.895020 18.574377 10758.548828", "-88.193314 0.000002 0.000000", 0.999537);
	SpawnObject("StaticObj_Wall_IndCnc4_Pole", "5753.809082 18.970446 10754.024414", "-88.193314 -0.000003 0.000001", 0.99953);
	SpawnObject("StaticObj_Wall_Tin7_4", "5753.729980 18.704975 10751.841797", "90.358101 -0.000000 -0.000000", 0.999461);
	SpawnObject("StaticObj_Wall_IndCnc4_Pole", "5753.679199 19.093634 10749.674805", "-88.193222 0.000005 0.000001", 0.999372);
	SpawnObject("StaticObj_Wall_Tin7_4", "5753.701660 18.846077 10747.407227", "90.358322 -0.000003 -0.000000", 0.99933);
	SpawnObject("StaticObj_Wall_IndCnc4_Pole", "5753.716309 19.164480 10745.198242", "-88.193123 -0.000002 -0.000000", 0.999502);
	SpawnObject("StaticObj_Wall_Tin7_4", "5753.629395 18.952272 10742.791016", "90.358566 -0.000003 -0.000000", 0.99934);
	SpawnObject("StaticObj_Wall_IndCnc4_Pole", "5761.837891 20.018883 10739.503906", "-170.772034 -0.000001 0.000002", 0.998966);
	SpawnObject("StaticObj_Wall_Tin7_4", "5763.937500 19.729155 10739.219727", "7.780085 0.000002 -0.000002", 0.998887);
	SpawnObject("StaticObj_Wall_Tin7_4", "5755.961914 19.527544 10740.133789", "7.780185 0.000001 0.000003", 0.998927);
	SpawnObject("StaticObj_Wall_IndCnc4_Pole", "5758.009277 19.788664 10739.968750", "-170.772141 0.000000 -0.000000", 0.999136);
	SpawnObject("StaticObj_Wall_Tin7_4", "5759.854004 19.470142 10739.548828", "7.780307 0.000003 0.000005", 0.998902);
	SpawnObject("Land_Mil_Tower_Small", "5754.702148 21.424498 10741.112305", "-123.318321 -0.000002 0.000002", 0.999931);
	SpawnObject("StaticObj_Wall_IndCnc4_Pole", "5765.953125 20.319044 10738.937500", "104.199677 0.000000 -0.000000", 0.998889);
	SpawnObject("StaticObj_Wall_Tin7_4", "5768.006836 20.099092 10738.462891", "9.210999 0.000002 -0.000005", 0.998841);
	SpawnObject("StaticObj_Wall_Tin7_4", "5772.432617 20.013016 10737.743164", "9.210527 0.000002 -0.000000", 0.998847);
	SpawnObject("StaticObj_Wall_IndCnc4_Pole", "5770.230469 20.289473 10738.141602", "-169.341751 0.000001 0.000002", 0.998991);
	SpawnObject("StaticObj_Wall_IndCnc4_Pole", "5774.683594 20.248236 10737.353516", "-169.341873 -0.000003 -0.000000", 0.998993);
	SpawnObject("StaticObj_Wall_Tin7_4", "5776.831543 19.986677 10736.939453", "9.210347 0.000003 -0.000002", 0.998913);
	SpawnObject("StaticObj_Wall_IndCnc4_Pole", "5778.962402 20.304081 10736.554688", "-169.341660 -0.000001 -0.000000", 0.998845);
	SpawnObject("StaticObj_Wall_Tin7_4", "5781.208496 20.068283 10736.231445", "9.210671 0.000002 -0.000002", 0.998813);
	SpawnObject("StaticObj_Wall_IndCnc4_Pole", "5783.399414 20.214188 10735.911133", "-169.341629 -0.000000 -0.000002", 0.998957);
	SpawnObject("StaticObj_Wall_Tin7_4", "5785.622559 19.515936 10735.500000", "9.211030 -0.000000 -0.000000", 0.998872);
	SpawnObject("StaticObj_Wall_IndCnc4_Pole", "5787.788086 19.807905 10735.163086", "-169.341751 -0.000001 -0.000002", 0.998905);
	SpawnObject("StaticObj_Wall_Tin7_4", "5790.026855 19.253038 10734.788086", "9.210682 0.000002 0.000002", 0.998786);
	SpawnObject("StaticObj_Wall_IndCnc4_Pole", "5792.241211 19.337290 10734.427734", "-169.341537 0.000000 0.000002", 0.998958);
	SpawnObject("StaticObj_Wall_Tin7_4", "5794.381348 18.845501 10734.007813", "9.209400 0.000000 -0.000002", 0.99852);
	SpawnObject("StaticObj_Wall_IndCnc4_Pole", "5796.515137 19.115273 10733.625000", "-169.342560 -0.000003 0.000002", 0.998455);
	SpawnObject("StaticObj_Wall_Tin7_4", "5798.756348 18.746067 10733.298828", "9.209952 0.000002 -0.000000", 0.998447);
	SpawnObject("StaticObj_Wall_IndCnc4_Pole", "5800.937500 18.724129 10732.972656", "-169.342941 0.000000 0.000002", 0.998637);
	SpawnObject("StaticObj_Wall_Tin7_4", "5803.169434 18.242750 10732.562500", "9.209298 -0.000000 -0.000005", 0.998384);
	SpawnObject("StaticObj_Wall_IndCnc4_Pole", "5805.336914 18.420218 10732.231445", "-169.342667 -0.000003 0.000002", 0.998574);
	SpawnObject("Land_Mil_Tower_Small", "5810.544434 20.324100 10754.124023", "94.024971 -0.000002 -0.000001", 0.999722);
	SpawnObject("StaticObj_Wreck_BMP1", "5772.882813 19.398043 10718.544922", "152.984406 0.000000 -0.000000", 0.99991);
	SpawnObject("StaticObj_Wreck_BMP2", "5764.073242 19.577696 10718.750977", "174.365295 0.000000 30.741034", 0.999964);
	SpawnObject("StaticObj_Wreck_HMMWV", "5759.694336 19.196075 10706.178711", "12.528627 0.000000 -0.000000", 0.999958);
	SpawnObject("Land_Wreck_Ikarus", "5806.233398 18.311169 10746.020508", "-169.229996 0.000000 -0.000000", 0.999842);
	SpawnObject("StaticObj_Rubble_DirtPile_Medium1", "5762.480957 18.684105 10707.945313", "0.000169 -0.000000 0.000005", 0.999967);
	SpawnObject("StaticObj_Rubble_Wood3", "5768.552734 19.313353 10720.090820", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("Land_Wreck_Volha_Police", "5751.158691 18.597555 10721.619141", "-0.000176 0.000000 -0.000000", 0.999992);
	SpawnObject("Land_Wreck_Volha_Grey", "5752.858398 18.590298 10716.245117", "141.340256 0.000000 -0.000000", 0.999999);
	SpawnObject("Land_Mil_Tower_Small", "5808.782227 20.834919 10732.243164", "122.248100 -0.000000 0.000000", 0.999654);
	SpawnObject("StaticObj_Misc_Hedgehog_Iron", "5813.512695 17.265425 10752.897461", "0.000178 -0.000001 0.000005", 0.99995);
	SpawnObject("StaticObj_Misc_Hedgehog_Iron", "5814.132324 17.250147 10754.756836", "0.000179 -0.000001 -0.000005", 0.999987);
	SpawnObject("StaticObj_Misc_Hedgehog_Iron", "5813.577637 17.180151 10749.376953", "71.957466 -0.000000 -0.000000", 0.999987);
	SpawnObject("StaticObj_Misc_Hedgehog_Iron", "5815.008301 17.079969 10751.238281", "123.181389 -0.000000 0.000000", 0.999989);
	SpawnObject("StaticObj_Wall_IndCnc4_Pole", "5811.238281 17.878395 10749.072266", "96.329086 0.000000 -0.000000", 0.997798);
	SpawnObject("StaticObj_Wall_Tin7_4", "5811.475586 17.596748 10751.326172", "-85.117935 -0.000003 -0.000001", 0.99769);
	SpawnObject("StaticObj_Wall_IndCnc4_Pole", "5811.646484 17.743963 10753.512695", "96.329361 -0.000002 0.000003", 0.997884);
	SpawnObject("StaticObj_Wall_Tin7_4", "5810.672852 17.758511 10742.434570", "-85.118233 -0.000002 -0.000001", 0.997708);
	SpawnObject("StaticObj_Wall_IndCnc4_Pole", "5810.878418 18.026039 10744.582031", "96.329163 0.000003 0.000001", 0.998258);
	SpawnObject("StaticObj_Wall_Tin7_4", "5811.188477 17.667498 10746.850586", "-85.117561 -0.000002 -0.000002", 0.997634);
	SpawnObject("StaticObj_Wall_IndCnc4_Pole", "5810.007813 18.095448 10735.871094", "96.329086 0.000000 -0.000000", 0.997763);
	SpawnObject("StaticObj_Wall_Tin7_4", "5810.245117 17.813725 10738.125000", "-85.117973 -0.000003 -0.000001", 0.99761);
	SpawnObject("StaticObj_Wall_IndCnc4_Pole", "5810.416016 17.960999 10740.311523", "96.329330 -0.000002 0.000003", 0.997865);
	SpawnObject("StaticObj_Wall_Tin7_4", "5809.958008 17.884495 10733.649414", "-85.117455 -0.000002 -0.000002", 0.997579);
	SpawnObject("Land_Misc_Well_Pump_Yellow", "5801.169922 17.564243 10790.303711", "1.591140 0.000000 -0.000000", 0.99993);
	SpawnObject("Land_Workshop_FuelStation", "5797.774414 19.043308 10750.184570", "-173.824738 -0.000003 0.000000", 0.999903);
	SpawnObject("StaticObj_Tank_Medium", "5790.168945 17.953316 10749.235352", "-82.742966 0.000000 -0.000000", 0.99961);
	SpawnObject("Land_Tank_Medium_Stairs", "5787.688477 18.320700 10749.583984", "-82.485222 0.000000 -0.000000", 0.999849);
	SpawnObject("Land_FuelStation_Feed", "5794.520996 17.749655 10756.489258", "5.322750 0.000000 -0.000000", 0.999819);
	SpawnObject("Land_Wreck_Uaz", "5810.207031 17.631128 10780.995117", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("dz/plants/tree/d_quercusrobur_fallenb.p3d", "5755.928223 17.047596 10758.701172", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("StaticObj_Wall_IndCnc4_Pole", "5753.587891 19.263475 10740.952148", "-88.193123 -0.000002 -0.000000", 0.999502);
	SpawnObject("dz/plants/tree/t_piceaabies_1sb.p3d", "5804.142090 17.314196 10747.221680", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("dz/plants/tree/b_piceaabies_1f.p3d", "5807.922363 16.829296 10740.891602", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("StaticObj_Misc_Timbers1", "5801.999023 18.011944 10739.083008", "-82.101540 -0.000000 -0.000000", 0.999946);
	SpawnObject("dz/plants/tree/t_piceaabies_1sb.p3d", "5785.762207 18.023018 10743.927734", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("dz/plants_bliss/bush/b_prunusspinosa_1s_summer.p3d", "5809.227539 16.750854 10740.494141", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("dz/plants/bush/b_naked_2s.p3d", "5804.364258 17.110100 10738.212891", "-0.000001 0.000000 -0.000000", 0.999989);
	SpawnObject("dz/plants_bliss/bush/b_prunusspinosa_1s_summer.p3d", "5790.175781 17.840168 10743.272461", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("Land_Tower_TC1", "5776.693359 33.945862 10743.109375", "5.234837 0.000000 -0.000000", 0.999843);
	SpawnObject("Land_Medical_Tent_Big", "5765.998047 18.845364 10750.566406", "-174.838654 0.000000 -0.000000", 0.999401);
	SpawnObject("StaticObj_Platform2_Stairs_30", "5780.447266 16.583540 10759.069336", "-174.208511 0.000000 -0.000000", 0.999776);
	SpawnObject("dz/plants/tree/b_piceaabies_1f.p3d", "5813.763672 16.756704 10785.605469", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("dz/plants/tree/t_piceaabies_1s.p3d", "5811.224121 16.771280 10786.859375", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("dz/plants_bliss/tree/t_piceaabies_1s_summer.p3d", "5758.670410 17.840370 10750.727539", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("dz/plants_bliss/bush/b_betulanana_1s_summer.p3d", "5778.315918 17.078102 10755.430664", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("dz/plants_bliss/bush/b_caraganaarborescens_2s_summer.p3d", "5776.302734 16.857296 10756.875977", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("dz/plants/tree/b_piceaabies_1f.p3d", "5773.636230 16.862022 10756.899414", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("dz/plants/tree/t_piceaabies_1s.p3d", "5771.965332 16.859993 10760.151367", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("dz/plants_sakhal/dark/t_piceaabies_1f_dark.p3d", "5763.040039 16.918793 10758.196289", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("dz/plants_sakhal/dark/t_piceaabies_2s_dark.p3d", "5788.315918 16.850048 10798.051758", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("dz/plants_sakhal/dark/t_piceaabies_2sb_dark.p3d", "5810.667969 16.777554 10775.871094", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("StaticObj_Rail_Crossing_Block_10", "5803.801758 15.808704 10753.320313", "7.431433 0.000000 -0.000000", 0.999904);
	SpawnObject("StaticObj_Rail_Crossing_Block_10", "5807.058105 15.807652 10752.897461", "7.431560 0.000000 -0.000000", 0.999856);
	SpawnObject("StaticObj_Rail_Crossing_Block_10", "5800.539063 15.802474 10753.745117", "7.431464 0.000000 -0.000000", 0.999768);
	SpawnObject("StaticObj_Rail_Crossing_Block_10", "5797.282715 15.803432 10754.167969", "7.431514 0.000000 -0.000000", 0.99986);
	SpawnObject("StaticObj_Rail_Crossing_Block_10", "5794.032227 15.802459 10754.610352", "7.431616 0.000000 -0.000000", 0.999713);
	SpawnObject("StaticObj_Rail_Crossing_Block_10", "5787.513184 15.797538 10755.458008", "7.432167 0.000000 -0.000000", 0.999216);
	SpawnObject("StaticObj_Rail_Crossing_Block_10", "5784.256836 15.798492 10755.880859", "7.432135 0.000000 -0.000000", 0.999316);
	SpawnObject("StaticObj_Rail_Crossing_Block_10", "5790.775879 15.803493 10755.033203", "7.432276 0.000000 -0.000000", 0.999492);
	SpawnObject("StaticObj_Platform2_Block", "5775.471680 15.457642 10749.634766", "6.340191 0.000000 -0.000000", 0.999983);
	SpawnObject("StaticObj_Platform2_Block", "5765.449707 15.456463 10750.716797", "6.340190 0.000000 -0.000000", 0.999983);
	SpawnObject("Land_misc_chickenCoop", "5812.062012 17.512405 10794.985352", "90.552223 0.000000 -0.000000", 0.999856);
	SpawnObject("Land_misc_chickenCoop", "5812.023926 17.517317 10792.641602", "90.552216 0.000000 -0.000000", 0.999856);
	SpawnObject("Land_Shed_M3", "5812.917480 17.954140 10789.381836", "-178.303207 0.000201 -0.000000", 0.999893);
	SpawnObject("StaticObj_Wall_Tin_5", "5766.505371 17.986149 10769.165039", "93.580994 0.000000 -0.000000", 0.999868);
	SpawnObject("StaticObj_Misc_Timbers_Log2", "5766.689941 15.266920 10771.143555", "-1.143604 89.242294 -94.795570", 1);
	SpawnObject("StaticObj_Misc_BoxWooden", "5761.116699 17.350395 10775.867188", "14.213491 0.000000 -0.000000", 0.99999);
	SpawnObject("StaticObj_Misc_BoxWooden", "5761.050293 18.321095 10775.945313", "-94.969742 0.000000 -0.000000", 0.999954);
	SpawnObject("SynLight_Lamp_City1", "5812.998535 20.949772 10760.781250", "-85.605400 0.000000 -0.000000", 0.99996);
	SpawnObject("SynLight_Lamp_City2", "5786.116211 21.077820 10756.409180", "6.596738 0.000000 -0.000000", 0.999942);
	SpawnObject("SynLight_Lamp_City1", "5753.208008 21.139360 10770.258789", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("SynLight_Lamp_City1", "5805.964844 21.029568 10796.018555", "-84.859650 0.000000 -0.000000", 0.999934);
	SpawnObject("Syn_StreetLight", "5788.407227 25.325436 10757.647461", "0.000000 -0.091675 0.183350", 0.999998);
	SpawnObject("Syn_StreetLight", "5784.208496 25.351852 10758.116211", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("Syn_StreetLight", "5811.461914 25.072021 10760.121094", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("Syn_StreetLight", "5752.146973 25.358240 10771.735352", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("Syn_StreetLight", "5804.470215 25.209410 10795.369141", "0.000000 -0.000000 -0.000000", 1);
	//SpawnObject("Syn_SpotlightObject", "5804.507324 16.806549 10795.183594", "0.000000 -0.000000 -0.000000", 1);
}