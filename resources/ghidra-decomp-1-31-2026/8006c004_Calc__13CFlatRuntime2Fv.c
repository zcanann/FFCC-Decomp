// Function: Calc__13CFlatRuntime2Fv
// Entry: 8006c004
// Size: 1464 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void Calc__13CFlatRuntime2Fv(CFlatRuntime2 *flatRuntime2)

{
  byte bVar1;
  short sVar2;
  float fVar3;
  void *pvVar4;
  ushort uVar5;
  int iVar6;
  int *piVar7;
  undefined4 uVar8;
  CTextureSet *textureSet;
  uint *ptr;
  uint uVar9;
  int iVar10;
  CFlatRuntime2 *pCVar11;
  uint *puVar12;
  byte bStack_a3;
  byte bStack_a2;
  Vec local_60;
  uint local_54;
  uint local_50;
  uint local_4c;
  uint local_48;
  uint local_44;
  uint local_40;
  uint local_3c;
  uint local_38;
  uint local_34;
  uint local_30;
  uint local_2c;
  uint local_28;
  uint local_24;
  uint local_20;
  uint local_1c;
  
  iVar10 = 0;
  pCVar11 = flatRuntime2;
  do {
    if ((*(CFileCHandle **)&pCVar11->field_0x1778 != (CFileCHandle *)0x0) &&
       (iVar6 = IsCompleted__5CFileFPQ25CFile7CHandle
                          (&File,*(CFileCHandle **)&pCVar11->field_0x1778), iVar6 != 0)) {
      piVar7 = *(int **)&pCVar11->field_0x1774;
      if (piVar7 != (int *)0x0) {
        if (piVar7 != (int *)0x0) {
          (**(code **)(*piVar7 + 8))(piVar7,1);
        }
        *(undefined4 *)&pCVar11->field_0x1774 = 0;
      }
      uVar8 = (**(code **)((int)(flatRuntime2->flatRuntimeBase).vtable + 0x44))(flatRuntime2);
      textureSet = (CTextureSet *)
                   __nw__11CTextureSetFUlPQ27CMemory6CStagePci
                             ((CTextureSet *)0x24,uVar8,s_cflat_runtime2_cpp_801d8fb0,0x335);
      if (textureSet != (CTextureSet *)0x0) {
        textureSet = (CTextureSet *)__ct__11CTextureSetFv(textureSet);
      }
      *(CTextureSet **)&pCVar11->field_0x1774 = textureSet;
      pvVar4 = File.m_readBuffer;
      uVar8 = GET_CHARA_ALLOC_STAGE_S__FiPQ27CMemory6CStage
                        (*(undefined4 *)&pCVar11->field_0x1770,Game.game.m_mainStage);
      Create__11CTextureSetFPvPQ27CMemory6CStageiP13CAmemCacheSetii
                (*(CTextureSet **)&pCVar11->field_0x1774,pvVar4,uVar8,0,0,0,0);
      Close__5CFileFPQ25CFile7CHandle(&File,*(CFileCHandle **)&pCVar11->field_0x1778);
      *(undefined4 *)&pCVar11->field_0x1778 = 0;
    }
    iVar10 = iVar10 + 1;
    pCVar11 = (CFlatRuntime2 *)&(pCVar11->flatRuntimeBase).m_variableValuesPtr;
  } while (iVar10 < 8);
  if (Pad._452_4_ == 0) {
    uVar5 = *(ushort *)
             ((int)&Pad + ((int)(1 - Pad._448_4_ | Pad._448_4_ - 1) >> 0x1f) * -0x54 + 0x36);
  }
  else {
    uVar5 = 0;
  }
  if (((uVar5 & 0x400) != 0) && (*(int *)&flatRuntime2->field_0x10418 != 0)) {
    *(undefined4 *)&flatRuntime2->field_0x10418 = 0;
  }
  if (*(int *)&flatRuntime2->field_0x10418 != 0) {
    Printf__8CGraphicFUlUlPce(&Graphic,2,3,s_SAVE_SCENE_801d9018);
    uVar8 = (**(code **)((int)(flatRuntime2->flatRuntimeBase).vtable + 0x44))(flatRuntime2);
    ptr = (uint *)__nwa__FUlPQ27CMemory6CStagePci(0xffc,uVar8,s_cflat_runtime2_cpp_801d8fb0,0x36f);
    local_38 = CameraPcs._224_4_ << 0x18 | ((uint)CameraPcs._224_4_ >> 8 & 0xff) << 0x10 |
               ((uint)CameraPcs._224_4_ >> 0x10 & 0xff) << 8 | (uint)CameraPcs._224_4_ >> 0x18;
    local_34 = CameraPcs._228_4_ << 0x18 | ((uint)CameraPcs._228_4_ >> 8 & 0xff) << 0x10 |
               ((uint)CameraPcs._228_4_ >> 0x10 & 0xff) << 8 | (uint)CameraPcs._228_4_ >> 0x18;
    local_30 = CameraPcs._232_4_ << 0x18 | ((uint)CameraPcs._232_4_ >> 8 & 0xff) << 0x10 |
               ((uint)CameraPcs._232_4_ >> 0x10 & 0xff) << 8 | (uint)CameraPcs._232_4_ >> 0x18;
    local_2c = CameraPcs._212_4_ << 0x18 | ((uint)CameraPcs._212_4_ >> 8 & 0xff) << 0x10 |
               ((uint)CameraPcs._212_4_ >> 0x10 & 0xff) << 8 | (uint)CameraPcs._212_4_ >> 0x18;
    local_28 = CameraPcs._216_4_ << 0x18 | ((uint)CameraPcs._216_4_ >> 8 & 0xff) << 0x10 |
               ((uint)CameraPcs._216_4_ >> 0x10 & 0xff) << 8 | (uint)CameraPcs._216_4_ >> 0x18;
    local_24 = CameraPcs._220_4_ << 0x18 | ((uint)CameraPcs._220_4_ >> 8 & 0xff) << 0x10 |
               ((uint)CameraPcs._220_4_ >> 0x10 & 0xff) << 8 | (uint)CameraPcs._220_4_ >> 0x18;
    local_20 = CameraPcs._252_4_ << 0x18 | ((uint)CameraPcs._252_4_ >> 8 & 0xff) << 0x10 |
               ((uint)CameraPcs._252_4_ >> 0x10 & 0xff) << 8 | (uint)CameraPcs._252_4_ >> 0x18;
    fVar3 = (FLOAT_80330138 * (float)CameraPcs._264_4_) / FLOAT_8033013c;
    local_1c = (int)fVar3 << 0x18 | ((uint)fVar3 >> 8 & 0xff) << 0x10 |
               ((uint)fVar3 >> 0x10 & 0xff) << 8 | (uint)fVar3 >> 0x18;
    puVar12 = ptr + 8;
    *ptr = local_38;
    ptr[1] = local_34;
    ptr[2] = local_30;
    ptr[3] = local_2c;
    ptr[4] = local_28;
    ptr[5] = local_24;
    ptr[6] = local_20;
    ptr[7] = local_1c;
    for (iVar10 = *(int *)(CFlat._2288_4_ + 0x24); iVar10 != -0x7fd657d4;
        iVar10 = *(int *)(iVar10 + 0x24)) {
      if (-1 < *(short *)(iVar10 + 0x14)) {
        bVar1 = *(byte *)(iVar10 + 0x38);
        if (((-1 < (int)((uint)bVar1 << 0x18)) &&
            (-1 < (int)((uint)bVar1 << 0x19 | (uint)(bVar1 >> 7)))) &&
           (uVar9 = (**(code **)(*(int *)(iVar10 + 0x48) + 0xc))(iVar10), (uVar9 & 5) == 5))
        goto LAB_8006c534;
      }
    }
    iVar10 = 0;
LAB_8006c534:
    if (iVar10 != 0) {
      if (*(int *)(iVar10 + 0xf8) != 0) {
        sVar2 = *(short *)(iVar10 + 0x30);
        bStack_a2 = (byte)((ushort)sVar2 >> 8);
        bStack_a3 = (byte)(sVar2 >> 0xf);
        local_54 = (int)sVar2 << 0x18 | (uint)bStack_a2 << 0x10 | (uint)bStack_a3 << 8 |
                   (uint)bStack_a3;
        local_60.x = *(float *)(iVar10 + 0x15c);
        local_60.y = *(float *)(iVar10 + 0x160);
        local_60.z = *(float *)(iVar10 + 0x164);
        if ((*(byte *)(iVar10 + 0x9a) & 1) != 0) {
          PSVECAdd(&local_60,(Vec *)(*(int *)(iVar10 + 0x18c) + 0x15c),&local_60);
        }
        local_50 = (int)local_60.x << 0x18 | ((uint)local_60.x >> 8 & 0xff) << 0x10 |
                   ((uint)local_60.x >> 0x10 & 0xff) << 8 | (uint)local_60.x >> 0x18;
        local_4c = (int)local_60.y << 0x18 | ((uint)local_60.y >> 8 & 0xff) << 0x10 |
                   ((uint)local_60.y >> 0x10 & 0xff) << 8 | (uint)local_60.y >> 0x18;
        local_48 = (int)local_60.z << 0x18 | ((uint)local_60.z >> 8 & 0xff) << 0x10 |
                   ((uint)local_60.z >> 0x10 & 0xff) << 8 | (uint)local_60.z >> 0x18;
        uVar9 = *(uint *)(iVar10 + 0x1a8);
        local_44 = uVar9 << 0x18 | (uVar9 >> 8 & 0xff) << 0x10 | (uVar9 >> 0x10 & 0xff) << 8 |
                   uVar9 >> 0x18;
        uVar9 = *(uint *)(iVar10 + 0x188);
        local_40 = uVar9 << 0x18 | (uVar9 >> 8 & 0xff) << 0x10 | (uVar9 >> 0x10 & 0xff) << 8 |
                   uVar9 >> 0x18;
        uVar9 = *(uint *)(iVar10 + 0x144);
        local_3c = uVar9 << 0x18 | (uVar9 >> 8 & 0xff) << 0x10 | (uVar9 >> 0x10 & 0xff) << 8 |
                   uVar9 >> 0x18;
        *puVar12 = local_54;
        puVar12[1] = local_50;
        puVar12[2] = local_4c;
        puVar12[3] = local_48;
        puVar12[4] = local_44;
        puVar12[5] = local_40;
        puVar12[6] = local_3c;
        puVar12 = puVar12 + 7;
      }
      for (iVar10 = *(int *)(iVar10 + 0x24); iVar10 != -0x7fd657d4; iVar10 = *(int *)(iVar10 + 0x24)
          ) {
        if (-1 < *(short *)(iVar10 + 0x14)) {
          bVar1 = *(byte *)(iVar10 + 0x38);
          if (((-1 < (int)((uint)bVar1 << 0x18)) &&
              (-1 < (int)((uint)bVar1 << 0x19 | (uint)(bVar1 >> 7)))) &&
             (uVar9 = (**(code **)(*(int *)(iVar10 + 0x48) + 0xc))(iVar10), (uVar9 & 5) == 5))
          goto LAB_8006c534;
        }
      }
      iVar10 = 0;
      goto LAB_8006c534;
    }
    local_54 = 0xffffffff;
    *puVar12 = 0xffffffff;
    puVar12[1] = local_50;
    puVar12[2] = local_4c;
    puVar12[3] = local_48;
    puVar12[4] = local_44;
    puVar12[5] = local_40;
    puVar12[6] = local_3c;
    __dla__FPv(ptr);
  }
  *(undefined4 *)&flatRuntime2->field_0xcd1c = 0;
  memset(&flatRuntime2->field_0x1338,0,0x14);
  return;
}

