// Function: SetMapColorAlpha__9CLightPcsFPA4_f8_GXColor8_GXColorUcfffUc
// Entry: 800494a4
// Size: 696 bytes

/* WARNING: Removing unreachable block (ram,0x80049734) */
/* WARNING: Removing unreachable block (ram,0x8004972c) */
/* WARNING: Removing unreachable block (ram,0x80049724) */
/* WARNING: Removing unreachable block (ram,0x800494c4) */
/* WARNING: Removing unreachable block (ram,0x800494bc) */
/* WARNING: Removing unreachable block (ram,0x800494b4) */

void SetMapColorAlpha__9CLightPcsFPA4_f8_GXColor8_GXColorUcfffUc
               (double param_1,double param_2,undefined8 param_3,int param_4,undefined4 param_5,
               undefined4 *param_6,undefined4 *param_7,char param_8,char param_9)

{
  int iVar1;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  Vec local_ac;
  Vec local_a0;
  Vec local_94;
  Vec local_88;
  Mtx MStack_7c;
  
  local_b0 = *param_6;
  GXSetChanMatColor(4,&local_b0);
  local_b4 = *param_7;
  GXSetChanAmbColor(4,&local_b4);
  if (((param_8 == '\0') || (param_9 == '\0')) || ((double)FLOAT_8032fc80 <= param_1)) {
    MaterialMan._519_1_ = *(undefined *)((int)param_7 + 3);
    GXSetChanCtrl(0,1,1,0,*(undefined4 *)(param_4 + 0xb4),2,1);
    if (*(char *)((int)param_7 + 3) == -1) {
      GXSetChanCtrl(2,0,0,1,0,0,2);
    }
    else {
      GXSetChanCtrl(2,1,0,1,0,0,2);
    }
  }
  else {
    PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_7c);
    local_88.x = (float)CameraPcs._224_4_;
    local_88.y = (float)CameraPcs._228_4_;
    local_88.z = (float)CameraPcs._232_4_;
    local_94.x = (float)CameraPcs._236_4_;
    local_94.y = (float)CameraPcs._240_4_;
    local_94.z = (float)CameraPcs._244_4_;
    PSMTXMultVec(&MStack_7c,&local_88,&local_a0);
    GXInitLightPos((double)local_a0.x,(double)local_a0.y,(double)local_a0.z,param_4 + 0x4370);
    PSMTXMultVecSR(&MStack_7c,&local_94,&local_ac);
    GXInitLightDir((double)local_ac.x,(double)local_ac.y,(double)local_ac.z,param_4 + 0x4370);
    GXInitLightSpot(param_3,param_4 + 0x4370,4);
    GXInitLightAttnK((double)(float)((double)FLOAT_8032fc84 / param_2),
                     (double)(float)((double)FLOAT_8032fc88 / param_1),
                     (double)(float)((double)FLOAT_8032fc8c / param_1),param_4 + 0x4370);
    DAT_8032e620 = CONCAT31(DAT_8032e620._0_3_,param_9);
    local_b8 = DAT_8032e620;
    GXInitLightColor(param_4 + 0x4370,&local_b8);
    if (7 < *(uint *)(param_4 + 0xb0)) {
      *(undefined4 *)(param_4 + 0xb0) = 7;
    }
    iVar1 = 1 << *(int *)(param_4 + 0xb0);
    GXLoadLightObjImm(param_4 + 0x4370,iVar1);
    MaterialMan._519_1_ = 0;
    GXSetChanCtrl(0,1,1,0,*(undefined4 *)(param_4 + 0xb4),2,1);
    GXSetChanCtrl(2,1,0,1,iVar1,0,1);
    *(int *)(param_4 + 0xb0) = *(int *)(param_4 + 0xb0) + 1;
  }
  return;
}

