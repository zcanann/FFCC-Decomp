// Function: __sinit_p_light_cpp
// Entry: 8004a348
// Size: 344 bytes

void __sinit_p_light_cpp(void)

{
  LightPcs.process.manager.vtable = (CManager)&PTR_PTR_s_CLightPcs_801ea460;
  __construct_array(LightPcs.lightsA,__ct__Q29CLightPcs6CLightFv,0,0xb0,8);
  __construct_array(LightPcs.lightsB,__ct__Q29CLightPcs6CLightFv,0,0xb0,0x20);
  __construct_array(LightPcs.bumpLights,__ct__Q29CLightPcs10CBumpLightFv,0,0x138,0x20);
  DAT_801ea2d8 = DAT_801ea298;
  DAT_801ea2dc = DAT_801ea29c;
  DAT_801ea2e0 = PTR_create__9CLightPcsFv_801ea2a0;
  DAT_801ea2e4 = DAT_801ea2a4;
  DAT_801ea2e8 = DAT_801ea2a8;
  DAT_801ea2ec = PTR_destroy__9CLightPcsFv_801ea2ac;
  DAT_801ea2f0 = DAT_801ea2b0;
  DAT_801ea2f4 = DAT_801ea2b4;
  DAT_801ea2f8 = PTR_calc__9CLightPcsFv_801ea2b8;
  DAT_801ea304 = DAT_801ea2bc;
  DAT_801ea308 = DAT_801ea2c0;
  DAT_801ea30c = PTR_draw__9CLightPcsFv_801ea2c4;
  DAT_801ea318 = DAT_801ea2c8;
  DAT_801ea31c = DAT_801ea2cc;
  DAT_801ea320 = PTR_MakeLightMap__9CLightPcsFv_801ea2d0;
  return;
}

