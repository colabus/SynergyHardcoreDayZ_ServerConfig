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
	SpawnObject("StaticObj_Wall_Tin7_4", "5807.533691 18.151474 10731.840820", "9.210157 -0.000001 0.000000", 0.99844);
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
	SpawnObject("Land_Medical_Tent_Big", "5765.998047 18.845364 10750.566406", "-174.838669 0.000000 -0.000000", 0.999401);
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
	SpawnObject("StaticObj_Misc_BoxWooden", "5770.696289 17.346643 10766.981445", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("StaticObj_Misc_BoxWooden", "5771.854004 17.346649 10766.942383", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("StaticObj_Misc_BoxWooden", "5771.414551 18.319975 10767.031250", "-94.969742 0.000000 -0.000000", 0.999954);
	SpawnObject("SynLight_Lamp_City1", "5812.827637 20.958307 10761.118164", "-84.483337 0.000000 -0.000000", 0.999927);
	SpawnObject("SynLight_Lamp_City2", "5804.421387 21.034092 10796.403320", "8.524765 0.000000 -0.000000", 0.999935);
	SpawnObject("SynLight_Lamp_City3", "5791.065918 21.062298 10765.151367", "-153.134186 0.000657 0.000000", 0.999956);
	SpawnObject("Syn_StreetLight", "5811.446777 25.144291 10760.509766", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("SynLight_Lamp_City1", "5756.798828 21.106035 10771.286133", "-84.483322 0.000000 -0.000000", 0.999927);
	SpawnObject("Syn_StreetLight", "5755.417969 25.291624 10770.677734", "-0.000088 0.000000 -0.000000", 0.999991);
	SpawnObject("Syn_StreetLight", "5788.939941 25.209612 10763.896484", "0.000000 0.000000 -0.000000", 0.999948);
	SpawnObject("Syn_StreetLight", "5792.207520 25.202436 10764.174805", "0.000000 0.000000 -0.000000", 0.999941);
	SpawnObject("Syn_StreetLight", "5790.458984 25.248226 10767.003906", "0.000000 0.000000 -0.000000", 1);
	SpawnObject("Syn_StreetLight", "5806.512207 25.205488 10797.454102", "0.000000 0.000000 -0.000000", 1);
	SpawnObject("Syn_StreetLight", "5802.733887 25.183575 10798.027344", "0.000000 0.000000 -0.000000", 1);
	SpawnObject("StaticObj_Furniture_fluor_lamp", "5800.108887 21.199608 10746.419922", "95.135857 0.000000 -0.000000", 0.999961);
	SpawnObject("StaticObj_Furniture_fluor_lamp", "5799.899902 21.110374 10743.825195", "95.135849 0.000000 -0.000000", 0.999961);
	SpawnObject("StaticObj_Furniture_fluor_lamp", "5800.358398 21.282616 10748.828125", "95.135849 0.000000 -0.000000", 0.999961);
	SpawnObject("StaticObj_Furniture_fluor_lamp", "5794.762695 21.199091 10746.983398", "95.135849 0.000000 -0.000000", 0.999939);
	SpawnObject("StaticObj_Furniture_fluor_lamp", "5794.581055 21.119213 10744.659180", "95.135918 0.000000 -0.000000", 0.999898);
	SpawnObject("StaticObj_Furniture_fluor_lamp", "5795.087402 21.284782 10749.461914", "95.135902 0.000000 -0.000000", 0.999917);
	SpawnObject("Syn_InteriorLight", "5795.031250 20.948822 10749.459961", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("Syn_InteriorLight", "5794.696289 20.886219 10746.995117", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("Syn_InteriorLight", "5794.481445 20.799973 10744.667969", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("Syn_InteriorLight", "5800.296387 21.077055 10748.834961", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("Syn_InteriorLight", "5800.011719 20.868603 10746.455078", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("Syn_InteriorLight", "5799.781250 20.800703 10743.873047", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("Syn_InteriorLight", "5799.514648 20.521311 10765.646484", "0.000000 0.000000 -0.000000", 0.999942);
	SpawnObject("Syn_InteriorLight", "5799.913086 20.458014 10769.332031", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("vbldr_light_kitchen_03", "5795.206543 18.374107 10780.760742", "0.000000 0.000000 -0.000000", 1);
	SpawnObject("Syn_InteriorLight", "5795.225586 18.971514 10780.754883", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("StaticObj_Furniture_fluor_lamp", "5762.961914 22.111704 10750.836914", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("StaticObj_Furniture_fluor_lamp", "5769.011230 22.134535 10750.294922", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("Syn_InteriorLight", "5763.008789 21.787718 10750.818359", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("Syn_InteriorLight", "5768.948242 21.781878 10750.301758", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("StaticObj_Furniture_fluor_lamp", "5770.405762 20.852041 10769.925781", "5.226837 0.000000 -0.000000", 0.999954);
	SpawnObject("Syn_InteriorLight", "5770.427246 20.527685 10769.916992", "0.000000 0.000000 -0.000000", 1);
	SpawnObject("StaticObj_Furniture_fluor_lamp", "5762.911133 20.856195 10770.648438", "5.227020 0.000000 -0.000000", 0.999971);
	SpawnObject("Syn_InteriorLight", "5762.932617 20.531843 10770.639648", "0.000350 0.000000 -0.000000", 0.999963);
	SpawnObject("StaticObj_Furniture_fluor_lamp", "5769.884766 20.418287 10764.223633", "5.553943 13.804276 -2.038043", 0.999905);
	SpawnObject("Syn_InteriorLight", "5769.903809 20.092442 10764.201172", "-0.020689 -1.667224 0.000148", 0.999985);
	SpawnObject("StaticObj_Furniture_fluor_lamp", "5773.733398 20.448536 10763.827148", "5.553954 13.802333 -2.038259", 0.999698);
	SpawnObject("Syn_InteriorLight", "5773.752441 20.122658 10763.804688", "-0.021047 -1.668273 0.000372", 0.999951);
	SpawnObject("StaticObj_Furniture_fluor_lamp", "5766.062988 20.529921 10764.573242", "5.553308 13.797035 -2.038286", 0.999718);
	SpawnObject("Syn_InteriorLight", "5766.082031 20.203903 10764.550781", "-0.021047 -1.668190 0.000372", 0.999951);
	SpawnObject("StaticObj_Furniture_fluor_lamp", "5774.239746 20.892347 10769.630859", "5.226904 0.000000 -0.000000", 0.999907);
	SpawnObject("Syn_InteriorLight", "5774.261230 20.567991 10769.622070", "0.000379 0.000000 -0.000000", 0.999928);
	SpawnObject("StaticObj_Furniture_fluor_lamp", "5762.424805 20.277773 10765.000977", "5.553082 13.792362 -2.038335", 0.99969);
	SpawnObject("Syn_InteriorLight", "5762.443848 19.951756 10764.978516", "-0.021047 -1.668108 0.000372", 0.999951);
	SpawnObject("Syn_SpotlightObject", "5753.384766 23.025385 10763.697266", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("Syn_SpotlightObject", "5754.011719 23.162912 10762.776367", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("Syn_SpotlightObject", "5753.166016 23.908134 10741.095703", "0.000000 0.000000 -0.000000", 1);
	SpawnObject("Syn_SpotlightObject", "5753.047852 23.992376 10739.950195", "0.000000 0.000000 -0.000000", 1);
	SpawnObject("Syn_SpotlightObject", "5754.747559 23.911669 10740.006836", "0.000000 0.000000 -0.000000", 1);
	SpawnObject("Syn_SpotlightObject", "5809.459473 23.309336 10730.885742", "0.000000 0.000000 -0.000000", 1);
	SpawnObject("Syn_SpotlightObject", "5810.663086 23.522726 10731.249023", "0.000000 0.000000 -0.000000", 1);
	SpawnObject("Syn_SpotlightObject", "5809.754883 23.295885 10732.802734", "0.000000 0.000000 -0.000000", 1);
	SpawnObject("Syn_SpotlightObject", "5811.789551 22.814524 10753.186523", "0.000000 0.000000 -0.000000", 1);
	SpawnObject("Syn_SpotlightObject", "5812.631348 22.849234 10754.105469", "0.000000 0.000000 -0.000000", 1);
	SpawnObject("Syn_SpotlightObject", "5811.212402 22.792442 10755.023438", "0.000000 0.000000 -0.000000", 1);
	SpawnObject("Syn_SpotlightObject", "5755.184570 23.049778 10764.018555", "0.000000 0.000000 -0.000000", 1);
	SpawnObject("Syn_SpotlightObject", "5760.347656 22.925520 10804.926758", "0.000000 0.000000 -0.000000", 1);
	SpawnObject("Syn_SpotlightObject", "5759.890137 23.029840 10806.569336", "0.000000 0.000000 -0.000000", 1);
	SpawnObject("Syn_SpotlightObject", "5761.147949 22.923843 10806.708984", "0.000000 0.000000 -0.000000", 1);
	SpawnObject("StaticObj_Furniture_fluor_lamp", "5770.285156 21.010382 10793.224609", "5.226837 0.000000 -0.000000", 0.999953);
	SpawnObject("Syn_InteriorLight", "5770.306641 20.686026 10793.215820", "0.000137 0.000000 -0.000000", 0.999976);
	SpawnObject("StaticObj_Furniture_fluor_lamp", "5770.608398 25.280760 10797.177734", "94.909058 0.000000 -0.000000", 0.999941);
	SpawnObject("Syn_InteriorLight", "5770.597168 24.956404 10797.155273", "89.682564 0.000000 -0.000000", 0.999962);
	SpawnObject("StaticObj_Furniture_fluor_lamp", "5775.831543 25.379841 10796.896484", "94.909058 0.000000 -0.000000", 0.999941);
	SpawnObject("Syn_InteriorLight", "5775.820313 25.055485 10796.874023", "89.682648 0.000000 -0.000000", 0.999938);
	SpawnObject("StaticObj_Furniture_Light_BathRoom", "5780.367676 25.401577 10794.677734", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("Syn_InteriorLight", "5780.387207 25.029652 10794.665039", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("StaticObj_Furniture_Light_BathRoom", "5775.935059 25.378691 10792.446289", "0.000000 0.000000 -0.000000", 0.999987);
	SpawnObject("Syn_InteriorLight", "5775.954590 25.006762 10792.433594", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("StaticObj_Furniture_fluor_lamp", "5798.990234 20.452587 10741.076172", "95.135902 0.000000 -90.508003", 1);
	SpawnObject("Syn_InteriorLight", "5799.007324 20.317339 10740.973633", "-0.000052 0.000000 -0.000000", 0.999994);
	SpawnObject("Syn_PowerControlPanel", "5795.933105 16.840181 10778.181641", "94.640495 0.000000 -0.000000", 0.999886);
	SpawnObject("StaticObj_Furniture_fluor_lamp", "5774.692871 19.315447 10773.427734", "95.135902 0.000000 -90.508003", 1);
	SpawnObject("Syn_InteriorLight", "5774.694824 19.180199 10773.602539", "-0.000052 0.000000 -0.000000", 0.999994);
	SpawnObject("StaticObj_Furniture_fluor_lamp", "5766.955566 19.371128 10774.201172", "95.135902 0.000000 -90.508003", 1);
	SpawnObject("Syn_InteriorLight", "5766.957520 19.235880 10774.375977", "-0.000052 0.000000 -0.000000", 0.999994);
	SpawnObject("Syn_InteriorLightDim", "5777.839355 49.322136 10743.998047", "0.000000 -0.000000 -0.000000", 1);
	SpawnObject("Syn_InteriorLightDim", "5797.441895 43.240749 10790.338867", "0.000000 -0.000000 -0.000000", 1);
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
	SpawnObject("Land_House_2W04_Blue", "5773.915039 22.928637 10790.854492", "4.952258 -0.000001 -0.000003", 0.999916);
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
}