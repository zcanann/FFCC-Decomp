// Function: Init__9CRedSoundFPviii
// Entry: 801ccafc
// Size: 528 bytes

uint Init__9CRedSoundFPviii(CRedSound *redSound,uint param_2,uint param_3,uint param_4,uint param_5)

{
  int iVar1;
  
  memset(&DAT_8032e17c,0,0x100);
  if (((int)param_3 < 1) || ((int)param_5 < 1)) {
    param_3 = 0;
    if (DAT_8032f408 != 0) {
      OSReport(s__s_sSound_Driver_Initialize_ERRO_801e80a2,&DAT_801e801b,&DAT_80333d98,&DAT_80333da0
              );
      fflush(&DAT_8021d1a8);
    }
  }
  else if (((param_2 & 0x1f) == 0) && ((param_3 & 0x1f) == 0)) {
    if (((param_4 & 0x1f) == 0) && ((param_5 & 0x1f) == 0)) {
      iVar1 = ARCheckInit();
      if (iVar1 == 0) {
        if (DAT_8032f408 != 0) {
          OSReport(s__s_AR__was_not_initialized__s_801e8060,&DAT_801e801b,&DAT_80333d98,
                   &DAT_80333da0);
          fflush(&DAT_8021d1a8);
        }
        param_3 = 0;
      }
      else {
        AIReset();
        AIInit(0);
        AXInit();
        AXARTInit();
        Init__10CRedMemoryFiiii(&DAT_8032f480,param_2,param_3,param_4,param_5);
        Init__9CRedEntryFv(&DAT_8032e154);
        Start__9CRedSoundFv(redSound);
        Init__10CRedDriverFv(&CRedDriver_8032f4c0);
        if (DAT_8032f408 != 0) {
          OSReport(s__s_sSound_Driver_Initialize_OK___801e807f,&DAT_801e801b,&DAT_80333da5,
                   &DAT_80333da0);
          fflush(&DAT_8021d1a8);
        }
      }
    }
    else {
      if (DAT_8032f408 != 0) {
        OSReport(s__s_sA_Memory_Setting_Error_____0_801e802d,&DAT_801e801b,&DAT_80333d98,param_4,
                 param_5,&DAT_80333da0);
        fflush(&DAT_8021d1a8);
      }
      param_3 = 0;
    }
  }
  else {
    if (DAT_8032f408 != 0) {
      OSReport(s__s_s_Memory_Setting_Error_____0x_801e7fe8,&DAT_801e801b,&DAT_80333d98,param_2,
               param_3,&DAT_80333da0);
      fflush(&DAT_8021d1a8);
    }
    param_3 = 0;
  }
  return param_3;
}

