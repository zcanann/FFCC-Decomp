// Function: pppFrameMana2
// Entry: 80107ea4
// Size: 2556 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFrameMana2(pppMana2 *pppMana2,UnkB *param_2,UnkC *param_3)

{
  uint8_t uVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  CCharaPcsCHandle *handle;
  int iVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  CTexture *texture;
  float *pfVar8;
  int iVar9;
  uint uVar10;
  undefined *puVar11;
  undefined2 *puVar12;
  float *pfVar13;
  float *pfVar14;
  float *pfVar15;
  CTexture *texture_00;
  void *dstBuffer;
  undefined4 *puVar16;
  CGObject *gObject;
  int iVar17;
  int iVar18;
  uint uVar19;
  undefined4 *puVar20;
  
  if (DAT_8032ed70 == 0) {
    gObject = (CGObject *)(pppMngStPtr->m_velocity).y;
    iVar4 = param_3->m_serializedDataOffsets[1];
    puVar20 = (undefined4 *)((int)(&pppMana2->field0_0x0 + 2) + param_3->m_serializedDataOffsets[2])
    ;
    if (gObject != (CGObject *)0x0) {
      handle = (CCharaPcsCHandle *)GetCharaHandlePtr__FP8CGObjectl(gObject,0);
      iVar5 = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
      param_2->m_payload[0x24] = '\0';
      puVar20[0x1c] = param_2;
      if (Game.game.m_currentMapId == 0x21) {
        param_2->m_payload[0x24] = '\0';
      }
      *(undefined4 **)(iVar5 + 0xe4) = puVar20;
      *(UnkB **)(iVar5 + 0xe8) = param_2;
      *(code **)(iVar5 + 0xf0) = Mana2_BeforeDrawCallback__FPQ26CChara6CModelPvPvPA4_fi;
      *(code **)(iVar5 + 0xfc) = Mana2_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f;
      MaterialMan._228_1_ = (&pppMana2->field_0x8b)[iVar4];
      *(undefined *)(puVar20 + 0x38) = MaterialMan._228_1_;
      if ((pppMana2->field0_0x0).m_graphId == 0) {
        *puVar20 = gObject;
        *(undefined4 **)(iVar5 + 0xe4) = puVar20;
        *(UnkB **)(iVar5 + 0xe8) = param_2;
        *(code **)(iVar5 + 0xf0) = Mana2_BeforeDrawCallback__FPQ26CChara6CModelPvPvPA4_fi;
        *(code **)(iVar5 + 0xfc) = Mana2_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f;
        uVar6 = GetTextureFromRSD__FiP9_pppEnvSt(param_2->m_dataValIndex,pppEnvStPtr);
        puVar20[2] = uVar6;
        uVar6 = GetTextureFromRSD__FiP9_pppEnvSt(param_2->m_initWOrk,pppEnvStPtr);
        puVar20[3] = uVar6;
        uVar6 = GetTextureFromRSD__FiP9_pppEnvSt(param_2->m_stepValue,pppEnvStPtr);
        puVar20[4] = uVar6;
        uVar6 = GetTextureFromRSD__FiP9_pppEnvSt(param_2->m_arg3,pppEnvStPtr);
        puVar20[5] = uVar6;
        uVar6 = GetTextureFromRSD__FiP9_pppEnvSt(*(undefined4 *)param_2->m_payload,pppEnvStPtr);
        puVar20[6] = uVar6;
        uVar6 = GetTextureFromRSD__FiP9_pppEnvSt
                          (*(undefined4 *)(param_2->m_payload + 4),pppEnvStPtr);
        puVar20[7] = uVar6;
        uVar6 = GetTextureFromRSD__FiP9_pppEnvSt
                          (*(undefined4 *)(param_2->m_payload + 0x10),pppEnvStPtr);
        puVar20[0x1e] = uVar6;
        uVar6 = GetTextureFromRSD__FiP9_pppEnvSt
                          (*(undefined4 *)(param_2->m_payload + 0x14),pppEnvStPtr);
        puVar20[0x1f] = uVar6;
        if (puVar20[0x1d] == 0) {
          uVar6 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                            (0xc0,pppEnvStPtr->m_stagePtr,s_pppMana2_cpp_801dc4e0,0x1d7);
          puVar20[0x1d] = uVar6;
        }
        if (puVar20[10] == 0) {
          uVar6 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                            (0x20,pppEnvStPtr->m_stagePtr,s_pppMana2_cpp_801dc4e0,0x1dd);
          puVar20[10] = uVar6;
        }
        if (puVar20[0xb] == 0) {
          uVar6 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                            (0x20,pppEnvStPtr->m_stagePtr,s_pppMana2_cpp_801dc4e0,0x1e1);
          puVar20[0xb] = uVar6;
        }
        uVar6 = GXGetTexBufferSize(0x80,0x80,4,0,0);
        if (puVar20[0xc] == 0) {
          uVar7 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                            (uVar6,pppEnvStPtr->m_stagePtr,s_pppMana2_cpp_801dc4e0,0x1e9);
          puVar20[0xc] = uVar7;
        }
        if (puVar20[0xd] == 0) {
          uVar6 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                            (uVar6,pppEnvStPtr->m_stagePtr,s_pppMana2_cpp_801dc4e0,0x1eb);
          puVar20[0xd] = uVar6;
        }
        GXInitTexObj(puVar20[10],puVar20[0xc],0x80,0x80,4,1,1,0);
        GXInitTexObj(puVar20[0xb],puVar20[0xd],0x80,0x80,4,1,1,0);
        if (puVar20[8] == 0) {
          uVar6 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                            (0xc0,pppEnvStPtr->m_stagePtr,s_pppMana2_cpp_801dc4e0,0x1f6);
          puVar20[8] = uVar6;
        }
        dstBuffer = (void *)puVar20[8];
        iVar4 = 0;
        puVar16 = puVar20;
        do {
          memcpy(dstBuffer,puVar16[2] + 0x28,0x20);
          iVar4 = iVar4 + 1;
          dstBuffer = (void *)((int)dstBuffer + 0x20);
          puVar16 = puVar16 + 1;
        } while (iVar4 < 6);
        texture = (CTexture *)puVar20[0x1e];
        texture_00 = (CTexture *)puVar20[0x1f];
        texture->field96_0x6c = 0;
        InitTexObj__8CTextureFv(texture);
        texture_00->field96_0x6c = 0;
        InitTexObj__8CTextureFv(texture_00);
        if (puVar20[9] == 0) {
          uVar6 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                            (0xa5e8,pppEnvStPtr->m_stagePtr,s_pppMana2_cpp_801dc4e0,0x211);
          puVar20[9] = uVar6;
          genParaboloidMap__FPvPUlUs9_GXVtxFmt(puVar20[9],puVar20 + 0x39,0x1e,7);
        }
        iVar4 = *(int *)(iVar5 + 0xac);
        if (((puVar20[0xf] == 0) && (puVar20[0x10] == 0)) && (puVar20[0x12] == 0)) {
          for (uVar19 = 0; uVar19 < *(uint *)(*(int *)(iVar5 + 0xa4) + 0xc); uVar19 = uVar19 + 1) {
            iVar17 = *(int *)(iVar4 + 8);
            if ((((param_2->m_payload[8] == '\x01') &&
                 (iVar9 = strcmp(iVar17,&DAT_803318d4), iVar9 == 0)) ||
                ((param_2->m_payload[8] == '\x02' &&
                 (iVar9 = strcmp(iVar17,&DAT_803318dc), iVar9 == 0)))) ||
               ((param_2->m_payload[8] == '\x03' &&
                (iVar9 = strcmp(iVar17,&DAT_803318e4), iVar9 == 0)))) {
              if (puVar20[0x19] == 0) {
                uVar6 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                                  (*(int *)(iVar17 + 0x14) * 0xc,pppEnvStPtr->m_stagePtr,
                                   s_pppMana2_cpp_801dc4e0,0x232);
                puVar20[0x19] = uVar6;
                fVar2 = FLOAT_80331898;
                pfVar8 = (float *)puVar20[0x19];
                for (uVar10 = 0; uVar10 < *(uint *)(iVar17 + 0x14); uVar10 = uVar10 + 1) {
                  pfVar8[2] = fVar2;
                  pfVar8[1] = fVar2;
                  *pfVar8 = fVar2;
                  pfVar8 = pfVar8 + 3;
                }
              }
              if (puVar20[0x1a] == 0) {
                uVar6 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                                  (*(int *)(iVar17 + 0x14) << 2,pppEnvStPtr->m_stagePtr,
                                   s_pppMana2_cpp_801dc4e0,0x23b);
                puVar20[0x1a] = uVar6;
                puVar11 = (undefined *)puVar20[0x1a];
                for (uVar10 = 0; uVar10 < *(uint *)(iVar17 + 0x14); uVar10 = uVar10 + 1) {
                  *puVar11 = 0xff;
                  puVar11[1] = 0xff;
                  puVar11[2] = 0xff;
                  puVar11[3] = 0xff;
                  puVar11 = puVar11 + 4;
                }
              }
              if (puVar20[0x1b] == 0) {
                uVar6 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                                  (*(int *)(iVar17 + 0x14) * 6,pppEnvStPtr->m_stagePtr,
                                   s_pppMana2_cpp_801dc4e0,0x244);
                puVar20[0x1b] = uVar6;
                puVar12 = (undefined2 *)puVar20[0x1b];
                for (uVar10 = 0; uVar10 < *(uint *)(iVar17 + 0x14); uVar10 = uVar10 + 1) {
                  puVar12[1] = 0;
                  *puVar12 = 0;
                  puVar12 = puVar12 + 3;
                }
              }
              uVar6 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                                (*(int *)(iVar17 + 0x4c) << 2,pppEnvStPtr->m_stagePtr,
                                 s_pppMana2_cpp_801dc4e0,0x24b);
              puVar20[0x18] = uVar6;
              puVar16 = *(undefined4 **)(iVar17 + 0x50);
              iVar18 = *(int *)(iVar17 + 0x4c) + -1;
              iVar9 = iVar18 * 4;
              for (; -1 < iVar18; iVar18 = iVar18 + -1) {
                uVar6 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                                  (*puVar16,pppEnvStPtr->m_stagePtr,s_pppMana2_cpp_801dc4e0,0x255);
                *(undefined4 *)(puVar20[0x18] + iVar9) = uVar6;
                *(uint *)(puVar20[0x18] + iVar9) =
                     *(int *)(puVar20[0x18] + iVar9) + 0x1fU & 0xffffffe0;
                puVar20[0x3a] = *puVar16;
                memcpy(*(void **)(puVar20[0x18] + iVar9),puVar16[1],*puVar16);
                DCFlushRange(*(undefined4 *)(puVar20[0x18] + iVar9),*puVar16);
                ReWriteDisplayList__5CUtilFPvUlUl
                          ((CUtil *)&DAT_8032ec70,*(undefined4 *)(puVar20[0x18] + iVar9),*puVar16,1)
                ;
                iVar9 = iVar9 + -4;
                puVar16 = puVar16 + 3;
              }
            }
            if (((param_2->m_payload[8] == '\x01') &&
                (iVar9 = strcmp(iVar17,&DAT_803318ec), iVar9 == 0)) ||
               ((param_2->m_payload[8] == '\x02' &&
                (iVar17 = strcmp(iVar17,&DAT_803318f4), iVar17 == 0)))) {
              uVar6 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                                (0xd8c,pppEnvStPtr->m_stagePtr,s_pppMana2_cpp_801dc4e0,0x26a);
              puVar20[0xf] = uVar6;
              uVar6 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                                (0xd8c,pppEnvStPtr->m_stagePtr,s_pppMana2_cpp_801dc4e0,0x26b);
              puVar20[0x10] = uVar6;
              uVar6 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                                (0x484,pppEnvStPtr->m_stagePtr,s_pppMana2_cpp_801dc4e0,0x26c);
              puVar20[0x17] = uVar6;
              uVar6 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                                (0x908,pppEnvStPtr->m_stagePtr,s_pppMana2_cpp_801dc4e0,0x26d);
              puVar20[0x15] = uVar6;
              uVar6 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                                (0x908,pppEnvStPtr->m_stagePtr,s_pppMana2_cpp_801dc4e0,0x26e);
              puVar20[0x16] = uVar6;
              uVar6 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                                (0x484,pppEnvStPtr->m_stagePtr,s_pppMana2_cpp_801dc4e0,0x26f);
              puVar20[0x12] = uVar6;
              uVar6 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                                (0x484,pppEnvStPtr->m_stagePtr,s_pppMana2_cpp_801dc4e0,0x270);
              puVar20[0x13] = uVar6;
              uVar6 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                                (0xc00,pppEnvStPtr->m_stagePtr,s_pppMana2_cpp_801dc4e0,0x271);
              puVar20[0x14] = uVar6;
              uVar6 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                                (0xd8c,pppEnvStPtr->m_stagePtr,s_pppMana2_cpp_801dc4e0,0x272);
              puVar20[0x11] = uVar6;
              fVar2 = FLOAT_80331898;
              uVar10 = 0;
              pfVar14 = (float *)puVar20[0x12];
              pfVar15 = (float *)puVar20[0x13];
              iVar17 = 0xc;
              pfVar8 = pfVar14;
              pfVar13 = pfVar15;
              do {
                *pfVar8 = fVar2;
                uVar10 = uVar10 + 0x18;
                *pfVar13 = fVar2;
                pfVar8[1] = fVar2;
                pfVar13[1] = fVar2;
                pfVar8[2] = fVar2;
                pfVar13[2] = fVar2;
                pfVar8[3] = fVar2;
                pfVar13[3] = fVar2;
                pfVar8[4] = fVar2;
                pfVar13[4] = fVar2;
                pfVar8[5] = fVar2;
                pfVar13[5] = fVar2;
                pfVar8[6] = fVar2;
                pfVar13[6] = fVar2;
                pfVar8[7] = fVar2;
                pfVar13[7] = fVar2;
                pfVar8[8] = fVar2;
                pfVar13[8] = fVar2;
                pfVar8[9] = fVar2;
                pfVar13[9] = fVar2;
                pfVar8[10] = fVar2;
                pfVar13[10] = fVar2;
                pfVar8[0xb] = fVar2;
                pfVar13[0xb] = fVar2;
                pfVar8[0xc] = fVar2;
                pfVar13[0xc] = fVar2;
                pfVar8[0xd] = fVar2;
                pfVar13[0xd] = fVar2;
                pfVar8[0xe] = fVar2;
                pfVar13[0xe] = fVar2;
                pfVar8[0xf] = fVar2;
                pfVar13[0xf] = fVar2;
                pfVar8[0x10] = fVar2;
                pfVar13[0x10] = fVar2;
                pfVar8[0x11] = fVar2;
                pfVar13[0x11] = fVar2;
                pfVar8[0x12] = fVar2;
                pfVar13[0x12] = fVar2;
                pfVar8[0x13] = fVar2;
                pfVar13[0x13] = fVar2;
                pfVar8[0x14] = fVar2;
                pfVar13[0x14] = fVar2;
                pfVar8[0x15] = fVar2;
                pfVar13[0x15] = fVar2;
                pfVar8[0x16] = fVar2;
                pfVar13[0x16] = fVar2;
                pfVar8[0x17] = fVar2;
                pfVar8 = pfVar8 + 0x18;
                pfVar13[0x17] = fVar2;
                fVar3 = FLOAT_80331898;
                pfVar13 = pfVar13 + 0x18;
                iVar17 = iVar17 + -1;
              } while (iVar17 != 0);
              iVar17 = 0x121 - uVar10;
              pfVar14 = pfVar14 + uVar10;
              pfVar15 = pfVar15 + uVar10;
              if (uVar10 < 0x121) {
                do {
                  *pfVar14 = fVar3;
                  pfVar14 = pfVar14 + 1;
                  uVar10 = uVar10 + 1;
                  *pfVar15 = fVar3;
                  pfVar15 = pfVar15 + 1;
                  iVar17 = iVar17 + -1;
                } while (iVar17 != 0);
              }
              CreateWaterMesh__FP3VecP3VecP5Vec2dPUsf
                        ((double)*(float *)(param_2->m_payload + 0x18),puVar20[0xf],puVar20[0x10],
                         puVar20[0x15],puVar20[0x14],uVar10);
            }
            iVar4 = iVar4 + 0x14;
          }
        }
        if ((param_2->m_payload[8] == '\x01') || (param_2->m_payload[8] == '\x02')) {
          if (puVar20[0x12] != 0) {
            *(undefined4 *)(puVar20[0x12] + 0x240) = *(undefined4 *)(param_2->m_payload + 0x20);
          }
        }
      }
      uVar1 = param_2->m_payload[8];
      if (uVar1 != '\0') {
        if ((uVar1 == '\x01') || (uVar1 == '\x02')) {
          UpdateWaterMesh__FP6VMana2(puVar20);
        }
        iVar4 = *(int *)(iVar5 + 0xac);
        for (uVar19 = 0; uVar19 < *(uint *)(*(int *)(iVar5 + 0xa4) + 0xc); uVar19 = uVar19 + 1) {
          iVar17 = *(int *)(iVar4 + 8);
          if ((((param_2->m_payload[8] == '\x01') &&
               (iVar9 = strcmp(iVar17,&DAT_803318d4), iVar9 == 0)) ||
              ((param_2->m_payload[8] == '\x02' &&
               (iVar9 = strcmp(iVar17,&DAT_803318dc), iVar9 == 0)))) ||
             ((param_2->m_payload[8] == '\x03' && (iVar9 = strcmp(iVar17,&DAT_803318e4), iVar9 == 0)
              ))) {
            iVar18 = *(int *)(iVar17 + 0x4c) + -1;
            iVar9 = iVar18 * 4;
            for (; -1 < iVar18; iVar18 = iVar18 + -1) {
              CalcReflectionVector2__FP3VecP6S16VecP6S16VeclUlUlPA4_fPvUlP8_GXColorP8S16Vec2dPQ26CChara5CNode
                        (puVar20[0x19],*(undefined4 *)(iVar17 + 0x18),*(undefined4 *)(iVar17 + 0x20)
                         ,*(undefined4 *)(iVar17 + 0x14),
                         *(undefined4 *)(*(int *)(iVar5 + 0xa4) + 0x34),
                         *(undefined4 *)(*(int *)(iVar5 + 0xa4) + 0x38),iVar5 + 8,
                         *(undefined4 *)(puVar20[0x18] + iVar9),puVar20[0x3a],puVar20[0x1a],
                         puVar20[0x1b],*(int *)(iVar5 + 0xa8) + *(int *)(iVar17 + 0x5c) * 0xc0);
              iVar9 = iVar9 + -4;
            }
          }
          iVar4 = iVar4 + 0x14;
        }
      }
    }
  }
  return;
}

