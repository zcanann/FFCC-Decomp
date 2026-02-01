// Function: StreamPlay__9CRedSoundFPviii
// Entry: 801cd5d8
// Size: 224 bytes

int StreamPlay__9CRedSoundFPviii
              (CRedSound *redSound,char *param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  
  iVar1 = 0;
  if (((*param_2 == 'S') && (param_2[1] == 'T')) && (param_2[2] == 'R')) {
    iVar1 = GetAutoID__9CRedSoundFv(redSound);
    StreamPlay__10CRedDriverFiPviii(&CRedDriver_8032f4c0,iVar1,param_2,param_3,param_4,param_5);
  }
  else if (DAT_8032f408 != 0) {
    OSReport(s__s_sSTREAM___This_data_was_not___801e80ca,&DAT_801e801b,&DAT_80333d98,&DAT_80333da0);
    fflush(&DAT_8021d1a8);
  }
  return iVar1;
}

