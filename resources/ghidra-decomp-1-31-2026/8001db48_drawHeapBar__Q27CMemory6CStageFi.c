// Function: drawHeapBar__Q27CMemory6CStageFi
// Entry: 8001db48
// Size: 1088 bytes

void drawHeapBar__Q27CMemory6CStageFi(CStage *stage,uint param_2)

{
  bool bVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  byte *pbVar10;
  uint uVar11;
  undefined4 local_228;
  undefined4 local_224;
  undefined4 local_220;
  undefined4 local_21c;
  undefined4 local_218;
  undefined4 local_214;
  undefined4 local_210;
  undefined4 local_20c;
  undefined4 local_208;
  undefined *local_204;
  undefined4 local_200;
  undefined4 local_1fc;
  undefined4 local_1f8;
  undefined *local_1f4;
  undefined4 local_1f0;
  undefined4 local_1ec;
  undefined4 local_1e8;
  byte local_1e4 [388];
  undefined4 local_60;
  uint uStack_5c;
  undefined4 local_58;
  uint uStack_54;
  undefined4 local_50;
  uint uStack_4c;
  undefined4 local_48;
  uint uStack_44;
  undefined4 local_40;
  uint uStack_3c;
  undefined4 local_38;
  uint uStack_34;
  undefined4 local_30;
  uint uStack_2c;
  undefined4 local_28;
  uint uStack_24;
  
  local_224 = DAT_801d64a8;
  local_220 = DAT_801d64ac;
  local_21c = DAT_801d64b0;
  local_218 = DAT_801d64b4;
  local_214 = DAT_801d64b8;
  local_210 = DAT_801d64bc;
  local_20c = DAT_801d64c0;
  local_208 = DAT_801d64c4;
  local_204 = PTR_DAT_801d64c8;
  local_200 = DAT_801d64cc;
  local_1fc = DAT_801d64d0;
  local_1f8 = DAT_801d64d4;
  local_1f4 = PTR_DAT_801d64d8;
  local_1f0 = DAT_801d64dc;
  local_1ec = DAT_801d64e0;
  local_1e8 = DAT_801d64e4;
  if (stage->m_allocationMode == 2) {
    iVar4 = stage->field269_0x110;
  }
  else {
    iVar4 = *(int *)(stage->field269_0x110 + 8);
  }
  iVar9 = *(int *)(iVar4 + 4);
  memset(local_1e4,0xff,0x17d);
  iVar3 = *(int *)&stage->field_0x8;
  iVar6 = (*(int *)&stage->field_0xc + -0x40) - iVar3;
  do {
    iVar8 = iVar4;
    bVar2 = *(byte *)(iVar8 + 2);
    if ((bVar2 & 2) != 0) {
      uVar5 = (uint)local_1e4[0];
      pbVar10 = local_1e4;
      iVar4 = 0;
      iVar9 = 0;
      do {
        if ((uVar5 != *pbVar10) || (iVar9 == 0x17b)) {
          if (uVar5 == 0xff) {
            if (stage->m_allocationMode == 0) {
              local_228 = 0x4080;
            }
            else {
              local_228 = 0x400080;
            }
          }
          else if (stage->m_allocationMode == 0) {
            iVar3 = uVar5 * 4;
            local_228 = CONCAT31(CONCAT21(CONCAT11(*(undefined *)(&local_224 + uVar5),
                                                   *(undefined *)((int)&local_224 + iVar3 + 1)),
                                          *(undefined *)((int)&local_224 + iVar3 + 2)),
                                 *(undefined *)((int)&local_224 + iVar3 + 3));
          }
          else {
            iVar3 = uVar5 * 4;
            local_228 = CONCAT31(CONCAT21(CONCAT11(*(undefined *)(&local_224 + uVar5),
                                                   *(undefined *)((int)&local_224 + iVar3 + 1)),
                                          *(undefined *)((int)&local_224 + iVar3 + 2)),
                                 *(undefined *)((int)&local_224 + iVar3 + 3));
          }
          GXBegin(0x98,0,4);
          uStack_5c = iVar4 + 0x80U ^ 0x80000000;
          uStack_54 = param_2 ^ 0x80000000;
          uStack_4c = iVar9 + 0x80U ^ 0x80000000;
          local_60 = 0x43300000;
          uStack_34 = param_2 + 8 ^ 0x80000000;
          local_58 = 0x43300000;
          DAT_cc008000 = (float)((double)CONCAT44(0x43300000,uStack_5c) - DOUBLE_8032f7e0);
          local_50 = 0x43300000;
          DAT_cc008000 = (float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_8032f7e0);
          DAT_cc008000 = FLOAT_8032f7dc;
          DAT_cc008000 = local_228;
          uStack_44 = uStack_54;
          local_48 = 0x43300000;
          DAT_cc008000 = (float)((double)CONCAT44(0x43300000,uStack_4c) - DOUBLE_8032f7e0);
          uStack_3c = uStack_5c;
          local_40 = 0x43300000;
          DAT_cc008000 = (float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_8032f7e0);
          DAT_cc008000 = FLOAT_8032f7dc;
          DAT_cc008000 = local_228;
          local_38 = 0x43300000;
          DAT_cc008000 = (float)((double)CONCAT44(0x43300000,uStack_5c) - DOUBLE_8032f7e0);
          uStack_2c = uStack_4c;
          local_30 = 0x43300000;
          DAT_cc008000 = (float)((double)CONCAT44(0x43300000,uStack_34) - DOUBLE_8032f7e0);
          DAT_cc008000 = FLOAT_8032f7dc;
          DAT_cc008000 = local_228;
          uStack_24 = uStack_34;
          local_28 = 0x43300000;
          DAT_cc008000 = (float)((double)CONCAT44(0x43300000,uStack_4c) - DOUBLE_8032f7e0);
          DAT_cc008000 = (float)((double)CONCAT44(0x43300000,uStack_34) - DOUBLE_8032f7e0);
          DAT_cc008000 = FLOAT_8032f7dc;
          DAT_cc008000 = local_228;
          uVar5 = (uint)*pbVar10;
          iVar4 = iVar9;
        }
        iVar9 = iVar9 + 1;
        pbVar10 = pbVar10 + 1;
      } while (iVar9 < 0x17c);
      return;
    }
    bVar1 = false;
    if (((bVar2 & 4) != 0) && ((bVar2 & 3) == 0)) {
      bVar1 = true;
    }
    if (bVar1) {
      iVar7 = ((*(int *)(iVar8 + 8) - iVar3) * 0x17c) / iVar6;
      iVar4 = (((iVar8 + 0x40) - iVar3) * 0x17c) / iVar6;
      pbVar10 = local_1e4 + iVar4;
      uVar5 = (iVar7 + 1) - iVar4;
      if (iVar4 <= iVar7) {
        uVar11 = uVar5 >> 3;
        if (uVar11 != 0) {
          do {
            *pbVar10 = (byte)((int)(uint)*(byte *)(iVar8 + 2) >> 4);
            pbVar10[1] = (byte)((int)(uint)*(byte *)(iVar8 + 2) >> 4);
            pbVar10[2] = (byte)((int)(uint)*(byte *)(iVar8 + 2) >> 4);
            pbVar10[3] = (byte)((int)(uint)*(byte *)(iVar8 + 2) >> 4);
            pbVar10[4] = (byte)((int)(uint)*(byte *)(iVar8 + 2) >> 4);
            pbVar10[5] = (byte)((int)(uint)*(byte *)(iVar8 + 2) >> 4);
            pbVar10[6] = (byte)((int)(uint)*(byte *)(iVar8 + 2) >> 4);
            pbVar10[7] = (byte)((int)(uint)*(byte *)(iVar8 + 2) >> 4);
            pbVar10 = pbVar10 + 8;
            uVar11 = uVar11 - 1;
          } while (uVar11 != 0);
          uVar5 = uVar5 & 7;
          if (uVar5 == 0) goto LAB_8001dd1c;
        }
        do {
          *pbVar10 = (byte)((int)(uint)*(byte *)(iVar8 + 2) >> 4);
          pbVar10 = pbVar10 + 1;
          uVar5 = uVar5 - 1;
        } while (uVar5 != 0);
      }
    }
LAB_8001dd1c:
    if ((*(int *)(iVar8 + 0x10) != *(int *)(iVar8 + 8) - (iVar8 + 0x40)) ||
       (bVar1 = *(int *)(iVar8 + 4) != iVar9, iVar4 = *(int *)(iVar8 + 8), iVar9 = iVar8, bVar1)) {
      if (System.m_execParam != 0) {
        Printf__7CSystemFPce(&System,&DAT_801d67d8);
      }
      return;
    }
  } while( true );
}

