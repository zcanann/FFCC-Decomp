// Function: calcCastTime__10CGCharaObjFi
// Entry: 8010c2f0
// Size: 964 bytes

/* WARNING: Removing unreachable block (ram,0x8010c68c) */
/* WARNING: Removing unreachable block (ram,0x8010c300) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

uint calcCastTime__10CGCharaObjFi(int param_1,int param_2)

{
  short sVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint unaff_r30;
  uint uVar6;
  double dVar7;
  undefined8 local_38;
  double local_30;
  
  uVar3 = (**(code **)(*(int *)(param_1 + 0x48) + 0xc))();
  if (((((uVar3 & 0x6d) == 0x6d) && (Game.game.m_gameWork.m_menuStageMode != '\0')) &&
      (Game.game.m_gameWork.m_bossArtifactStageIndex < 0xf)) &&
     ((uVar3 = (**(code **)(*(int *)(param_1 + 0x48) + 0xc))(param_1), (uVar3 & 0x6d) == 0x6d &&
      (*(int *)(*(int *)(param_1 + 0x58) + 0x3b4) != 0)))) {
    unaff_r30 = 0;
  }
  else {
    iVar5 = *(int *)(param_1 + 0x58);
    param_2 = param_2 * 0x48;
    uVar3 = (uint)*(ushort *)(Game.game.unkCFlatData0[2] + param_2 + 0x2e);
    if (*(short *)(iVar5 + 0x4e) == 0) {
      if (*(short *)(iVar5 + 0x4c) == 0) {
        dVar7 = (double)FLOAT_80331964;
      }
      else {
        local_38 = (double)CONCAT44(0x43300000,
                                    (uint)*(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + 2));
        dVar7 = (double)(FLOAT_80331984 * (float)(local_38 - DOUBLE_80331978) + FLOAT_80331980);
      }
    }
    else {
      local_38 = (double)CONCAT44(0x43300000,(uint)*(ushort *)Game.game.unk_flat3_field_8_0xc7dc);
      dVar7 = (double)(FLOAT_80331984 * (float)(local_38 - DOUBLE_80331978) + FLOAT_80331980);
    }
    sVar1 = *(short *)(Game.game.unkCFlatData0[2] + param_2 + 0xe);
    if ((*(short *)(Game.game.unkCFlatData0[2] + param_2) == 0x1f8) || (sVar1 != 2)) {
      if (sVar1 == 3) {
        Printf__7CSystemFPce(&System,&DAT_801dc5e4,uVar3);
        unaff_r30 = uVar3;
      }
      else if (sVar1 == 4) {
        Printf__7CSystemFPce(&System,&DAT_801dc5f8,uVar3);
        unaff_r30 = uVar3;
      }
      else if (*(short *)(Game.game.unkCFlatData0[2] + param_2) == 0x1f8) {
        uVar6 = (uint)*(ushort *)(*(int *)(iVar5 + 0x24) + 0x196);
        uVar4 = (**(code **)(*(int *)(param_1 + 0x48) + 0xc))(param_1);
        uVar4 = countLeadingZeros(0x6d - (uVar4 & 0x6d));
        if ((uVar4 >> 5 & 0xff) == 0) {
          uVar4 = 0;
        }
        else {
          uVar4 = (uint)*(byte *)(*(int *)(param_1 + 0x58) + 0xbd9);
        }
        local_30 = (double)(CONCAT44(0x43300000,(uVar3 + uVar6) - uVar4) ^ 0x80000000);
        uVar4 = (uint)(dVar7 * (double)(float)(local_30 - DOUBLE_80331968));
        unaff_r30 = uVar4 & ~((int)uVar4 >> 0x1f);
        Printf__7CSystemFPce(dVar7,&System,&DAT_801dc60c,uVar3,uVar6);
      }
    }
    else {
      uVar6 = (uint)*(ushort *)(*(int *)(iVar5 + 0x24) + 0x194);
      uVar4 = (**(code **)(*(int *)(param_1 + 0x48) + 0xc))(param_1);
      if ((uVar4 & 0xad) == 0xad) {
        if (Game.game.m_gameWork.m_bossArtifactStageIndex < 0xf) {
          iVar2 = Game.game.m_gameWork.m_bossArtifactStageTable
                  [Game.game.m_gameWork.m_bossArtifactStageIndex];
          iVar5 = 2;
          if (iVar2 < 2) {
            iVar5 = iVar2;
          }
        }
        else {
          iVar5 = 0;
        }
        if (0 < iVar5) {
          uVar6 = uVar6 - *(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + iVar5 * 2 + 0x58);
          uVar6 = uVar6 & ~((int)uVar6 >> 0x1f);
        }
      }
      uVar4 = (**(code **)(*(int *)(param_1 + 0x48) + 0xc))(param_1);
      uVar4 = countLeadingZeros(0x6d - (uVar4 & 0x6d));
      if ((uVar4 >> 5 & 0xff) == 0) {
        uVar4 = 0;
      }
      else {
        uVar4 = (uint)*(byte *)(*(int *)(param_1 + 0x58) + 0xbd8);
      }
      local_38 = (double)(CONCAT44(0x43300000,(uVar3 + uVar6) - uVar4) ^ 0x80000000);
      uVar4 = (uint)(dVar7 * (double)(float)(local_38 - DOUBLE_80331968));
      Printf__7CSystemFPce(dVar7,&System,&DAT_801dc5bc,uVar3,uVar6);
      unaff_r30 = uVar4 & ~((int)uVar4 >> 0x1f);
    }
  }
  return unaff_r30;
}

