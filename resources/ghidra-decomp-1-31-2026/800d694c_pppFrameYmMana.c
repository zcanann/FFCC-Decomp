// Function: pppFrameYmMana
// Entry: 800d694c
// Size: 2804 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFrameYmMana(pppYmMana *pppYmMana,UnkB *param_2,UnkC *param_3)

{
  uint8_t uVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  int iVar5;
  CCharaPcsCHandle *handle;
  int iVar6;
  undefined4 uVar7;
  CTexture *pCVar8;
  undefined4 uVar9;
  float *pfVar10;
  int iVar11;
  uint uVar12;
  undefined *puVar13;
  undefined2 *puVar14;
  float *pfVar15;
  undefined2 *puVar16;
  float *pfVar17;
  float *pfVar18;
  CTexture *pCVar19;
  undefined4 *puVar20;
  void *dstBuffer;
  int iVar21;
  CGObject *gObject;
  int iVar22;
  uint uVar23;
  undefined4 *puVar24;
  
  if (DAT_8032ed70 == 0) {
    gObject = (CGObject *)(pppMngStPtr->m_velocity).x;
    iVar5 = param_3->m_serializedDataOffsets[1];
    puVar24 = (undefined4 *)
              ((int)(&pppYmMana->field0_0x0 + 2) + param_3->m_serializedDataOffsets[2]);
    if (gObject != (CGObject *)0x0) {
      handle = (CCharaPcsCHandle *)GetCharaHandlePtr__FP8CGObjectl(gObject,0);
      iVar6 = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
      puVar24[0x1d] = param_2;
      if (Game.game.m_currentMapId == 0x21) {
        param_2->m_payload[0x24] = '\0';
      }
      if ((*(byte *)&gObject->m_weaponNodeFlags & 1) != 0) {
        puVar24[0x3e] = gObject->m_attachOwner;
      }
      *(undefined4 **)(iVar6 + 0xe4) = puVar24;
      *(UnkB **)(iVar6 + 0xe8) = param_2;
      dVar4 = DOUBLE_80330eb0;
      *(code **)(iVar6 + 0xf0) = Mana_BeforeDrawCallback__FPQ26CChara6CModelPvPvPA4_fi;
      *(code **)(iVar6 + 0xfc) = Mana_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f;
      MaterialMan._228_1_ =
           (undefined)
           (int)((float)((double)CONCAT44(0x43300000,(uint)(byte)(&pppYmMana->field_0x8b)[iVar5]) -
                        dVar4) * gObject->m_lookAtTimer);
      if (Game.game.m_currentMapId == 0x21) {
        MaterialMan._228_1_ =
             (undefined)
             (int)(gObject->m_lookAtTimer *
                  (float)((double)CONCAT44(0x43300000,(uint)(byte)(&pppYmMana->field_0x8b)[iVar5]) -
                         dVar4));
      }
      *(undefined *)(puVar24 + 0x3a) = MaterialMan._228_1_;
      if ((pppYmMana->field0_0x0).m_graphId == 0) {
        *puVar24 = gObject;
        *(undefined4 **)(iVar6 + 0xe4) = puVar24;
        *(UnkB **)(iVar6 + 0xe8) = param_2;
        *(code **)(iVar6 + 0xf0) = Mana_BeforeDrawCallback__FPQ26CChara6CModelPvPvPA4_fi;
        *(code **)(iVar6 + 0xfc) = Mana_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f;
        uVar7 = GetTextureFromRSD__FiP9_pppEnvSt(param_2->m_stepValue,pppEnvStPtr);
        puVar24[2] = uVar7;
        uVar7 = GetTextureFromRSD__FiP9_pppEnvSt(param_2->m_initWOrk,pppEnvStPtr);
        puVar24[3] = uVar7;
        uVar7 = GetTextureFromRSD__FiP9_pppEnvSt(param_2->m_dataValIndex,pppEnvStPtr);
        puVar24[4] = uVar7;
        uVar7 = GetTextureFromRSD__FiP9_pppEnvSt(param_2->m_arg3,pppEnvStPtr);
        puVar24[5] = uVar7;
        uVar7 = GetTextureFromRSD__FiP9_pppEnvSt(*(undefined4 *)param_2->m_payload,pppEnvStPtr);
        puVar24[6] = uVar7;
        uVar7 = GetTextureFromRSD__FiP9_pppEnvSt
                          (*(undefined4 *)(param_2->m_payload + 4),pppEnvStPtr);
        puVar24[7] = uVar7;
        uVar7 = GetTextureFromRSD__FiP9_pppEnvSt
                          (*(undefined4 *)(param_2->m_payload + 0x10),pppEnvStPtr);
        puVar24[0x1f] = uVar7;
        uVar7 = GetTextureFromRSD__FiP9_pppEnvSt
                          (*(undefined4 *)(param_2->m_payload + 0x14),pppEnvStPtr);
        puVar24[0x20] = uVar7;
        pCVar8 = (CTexture *)puVar24[0x1f];
        pCVar19 = (CTexture *)puVar24[0x20];
        pCVar8->field96_0x6c = 0;
        InitTexObj__8CTextureFv(pCVar8);
        pCVar19->field96_0x6c = 0;
        InitTexObj__8CTextureFv(pCVar19);
        if (puVar24[0x1e] == 0) {
          uVar7 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                            (0xc0,pppEnvStPtr->m_stagePtr,s_pppYmMana_cpp_801db4d8,0x38f);
          puVar24[0x1e] = uVar7;
        }
        if (puVar24[10] == 0) {
          uVar7 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                            (0x20,pppEnvStPtr->m_stagePtr,s_pppYmMana_cpp_801db4d8,0x395);
          puVar24[10] = uVar7;
        }
        if (puVar24[0xb] == 0) {
          uVar7 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                            (0x20,pppEnvStPtr->m_stagePtr,s_pppYmMana_cpp_801db4d8,0x399);
          puVar24[0xb] = uVar7;
        }
        uVar7 = GXGetTexBufferSize(0x80,0x80,4,0,0);
        if (puVar24[0xc] == 0) {
          uVar9 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                            (uVar7,pppEnvStPtr->m_stagePtr,s_pppYmMana_cpp_801db4d8,0x3a1);
          puVar24[0xc] = uVar9;
        }
        if (puVar24[0xd] == 0) {
          uVar7 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                            (uVar7,pppEnvStPtr->m_stagePtr,s_pppYmMana_cpp_801db4d8,0x3a3);
          puVar24[0xd] = uVar7;
        }
        GXInitTexObj(puVar24[10],puVar24[0xc],0x80,0x80,4,1,1,0);
        GXInitTexObj(puVar24[0xb],puVar24[0xd],0x80,0x80,4,1,1,0);
        if (puVar24[8] == 0) {
          uVar7 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                            (0xc0,pppEnvStPtr->m_stagePtr,s_pppYmMana_cpp_801db4d8,0x3b0);
          puVar24[8] = uVar7;
        }
        dstBuffer = (void *)puVar24[8];
        iVar5 = 0;
        puVar20 = puVar24;
        do {
          pCVar8 = (CTexture *)puVar20[2];
          pCVar8->field96_0x6c = 0;
          InitTexObj__8CTextureFv(pCVar8);
          memcpy(dstBuffer,&pCVar8->field_0x28,0x20);
          iVar5 = iVar5 + 1;
          dstBuffer = (void *)((int)dstBuffer + 0x20);
          puVar20 = puVar20 + 1;
        } while (iVar5 < 6);
        pCVar8 = (CTexture *)puVar24[0x1f];
        pCVar19 = (CTexture *)puVar24[0x20];
        pCVar8->field96_0x6c = 0;
        InitTexObj__8CTextureFv(pCVar8);
        pCVar19->field96_0x6c = 0;
        InitTexObj__8CTextureFv(pCVar19);
        if (puVar24[9] == 0) {
          uVar7 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                            (0xa5e8,pppEnvStPtr->m_stagePtr,s_pppYmMana_cpp_801db4d8,0x3cb);
          puVar24[9] = uVar7;
          genParaboloidMap__FPvPUlUs9_GXVtxFmt(puVar24[9],puVar24 + 0x3b,0x1e,7);
        }
        iVar5 = *(int *)(iVar6 + 0xac);
        if (((puVar24[0xf] == 0) && (puVar24[0x10] == 0)) && (puVar24[0x12] == 0)) {
          for (uVar23 = 0; uVar23 < *(uint *)(*(int *)(iVar6 + 0xa4) + 0xc); uVar23 = uVar23 + 1) {
            iVar22 = *(int *)(iVar5 + 8);
            if ((((param_2->m_payload[8] == '\x01') &&
                 (iVar11 = strcmp(iVar22,&DAT_80330e88), iVar11 == 0)) ||
                ((param_2->m_payload[8] == '\x02' &&
                 (iVar11 = strcmp(iVar22,&DAT_80330e90), iVar11 == 0)))) ||
               ((param_2->m_payload[8] == '\x03' &&
                (iVar11 = strcmp(iVar22,&DAT_80330e98), iVar11 == 0)))) {
              if (puVar24[0x19] == 0) {
                uVar7 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                                  (*(int *)(iVar22 + 0x14) * 0xc,pppEnvStPtr->m_stagePtr,
                                   s_pppYmMana_cpp_801db4d8,1000);
                puVar24[0x19] = uVar7;
                fVar2 = FLOAT_80330e4c;
                pfVar10 = (float *)puVar24[0x19];
                for (uVar12 = 0; uVar12 < *(uint *)(iVar22 + 0x14); uVar12 = uVar12 + 1) {
                  pfVar10[2] = fVar2;
                  pfVar10[1] = fVar2;
                  *pfVar10 = fVar2;
                  pfVar10 = pfVar10 + 3;
                }
              }
              if (puVar24[0x1a] == 0) {
                uVar7 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                                  (*(int *)(iVar22 + 0x14) << 2,pppEnvStPtr->m_stagePtr,
                                   s_pppYmMana_cpp_801db4d8,0x3f1);
                puVar24[0x1a] = uVar7;
                puVar13 = (undefined *)puVar24[0x1a];
                for (uVar12 = 0; uVar12 < *(uint *)(iVar22 + 0x14); uVar12 = uVar12 + 1) {
                  *puVar13 = 0xff;
                  puVar13[1] = 0xff;
                  puVar13[2] = 0xff;
                  puVar13[3] = 0xff;
                  puVar13 = puVar13 + 4;
                }
              }
              if (puVar24[0x1b] == 0) {
                uVar7 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                                  (*(int *)(iVar22 + 0x14) * 6,pppEnvStPtr->m_stagePtr,
                                   s_pppYmMana_cpp_801db4d8,0x3fa);
                puVar24[0x1b] = uVar7;
                uVar7 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                                  (*(int *)(iVar22 + 0x14) * 6,pppEnvStPtr->m_stagePtr,
                                   s_pppYmMana_cpp_801db4d8,0x3fb);
                puVar24[0x1c] = uVar7;
                puVar14 = (undefined2 *)puVar24[0x1b];
                puVar16 = (undefined2 *)puVar24[0x1c];
                for (uVar12 = 0; uVar12 < *(uint *)(iVar22 + 0x14); uVar12 = uVar12 + 1) {
                  puVar14[1] = 0;
                  *puVar14 = 0;
                  puVar14 = puVar14 + 3;
                  puVar16[1] = 0;
                  *puVar16 = 0;
                  puVar16 = puVar16 + 3;
                }
              }
              uVar7 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                                (*(int *)(iVar22 + 0x4c) << 2,pppEnvStPtr->m_stagePtr,
                                 s_pppYmMana_cpp_801db4d8,0x407);
              puVar24[0x18] = uVar7;
              puVar20 = *(undefined4 **)(iVar22 + 0x50);
              iVar21 = *(int *)(iVar22 + 0x4c) + -1;
              iVar11 = iVar21 * 4;
              for (; -1 < iVar21; iVar21 = iVar21 + -1) {
                uVar7 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                                  (*puVar20,pppEnvStPtr->m_stagePtr,s_pppYmMana_cpp_801db4d8,0x411);
                *(undefined4 *)(puVar24[0x18] + iVar11) = uVar7;
                *(uint *)(puVar24[0x18] + iVar11) =
                     *(int *)(puVar24[0x18] + iVar11) + 0x1fU & 0xffffffe0;
                puVar24[0x3c] = *puVar20;
                memcpy(*(void **)(puVar24[0x18] + iVar11),puVar20[1],*puVar20);
                DCFlushRange(*(undefined4 *)(puVar24[0x18] + iVar11),*puVar20);
                ReWriteDisplayList__5CUtilFPvUlUl
                          ((CUtil *)&DAT_8032ec70,*(undefined4 *)(puVar24[0x18] + iVar11),*puVar20,3
                          );
                iVar11 = iVar11 + -4;
                puVar20 = puVar20 + 3;
              }
            }
            if (((param_2->m_payload[8] == '\x01') &&
                (iVar11 = strcmp(iVar22,&DAT_80330ea0), iVar11 == 0)) ||
               ((param_2->m_payload[8] == '\x02' &&
                (iVar22 = strcmp(iVar22,&DAT_80330ea8), iVar22 == 0)))) {
              uVar7 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                                (0xd8c,pppEnvStPtr->m_stagePtr,s_pppYmMana_cpp_801db4d8,0x427);
              puVar24[0xf] = uVar7;
              uVar7 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                                (0xd8c,pppEnvStPtr->m_stagePtr,s_pppYmMana_cpp_801db4d8,0x428);
              puVar24[0x10] = uVar7;
              uVar7 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                                (0x484,pppEnvStPtr->m_stagePtr,s_pppYmMana_cpp_801db4d8,0x429);
              puVar24[0x17] = uVar7;
              uVar7 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                                (0x908,pppEnvStPtr->m_stagePtr,s_pppYmMana_cpp_801db4d8,0x42a);
              puVar24[0x15] = uVar7;
              uVar7 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                                (0x908,pppEnvStPtr->m_stagePtr,s_pppYmMana_cpp_801db4d8,0x42b);
              puVar24[0x16] = uVar7;
              uVar7 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                                (0x484,pppEnvStPtr->m_stagePtr,s_pppYmMana_cpp_801db4d8,0x42c);
              puVar24[0x12] = uVar7;
              uVar7 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                                (0x484,pppEnvStPtr->m_stagePtr,s_pppYmMana_cpp_801db4d8,0x42d);
              puVar24[0x13] = uVar7;
              uVar7 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                                (0xc00,pppEnvStPtr->m_stagePtr,s_pppYmMana_cpp_801db4d8,0x42e);
              puVar24[0x14] = uVar7;
              uVar7 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                                (0xd8c,pppEnvStPtr->m_stagePtr,s_pppYmMana_cpp_801db4d8,0x42f);
              puVar24[0x11] = uVar7;
              fVar2 = FLOAT_80330e4c;
              uVar12 = 0;
              pfVar17 = (float *)puVar24[0x12];
              pfVar18 = (float *)puVar24[0x13];
              iVar22 = 0xc;
              pfVar10 = pfVar17;
              pfVar15 = pfVar18;
              do {
                *pfVar10 = fVar2;
                uVar12 = uVar12 + 0x18;
                *pfVar15 = fVar2;
                pfVar10[1] = fVar2;
                pfVar15[1] = fVar2;
                pfVar10[2] = fVar2;
                pfVar15[2] = fVar2;
                pfVar10[3] = fVar2;
                pfVar15[3] = fVar2;
                pfVar10[4] = fVar2;
                pfVar15[4] = fVar2;
                pfVar10[5] = fVar2;
                pfVar15[5] = fVar2;
                pfVar10[6] = fVar2;
                pfVar15[6] = fVar2;
                pfVar10[7] = fVar2;
                pfVar15[7] = fVar2;
                pfVar10[8] = fVar2;
                pfVar15[8] = fVar2;
                pfVar10[9] = fVar2;
                pfVar15[9] = fVar2;
                pfVar10[10] = fVar2;
                pfVar15[10] = fVar2;
                pfVar10[0xb] = fVar2;
                pfVar15[0xb] = fVar2;
                pfVar10[0xc] = fVar2;
                pfVar15[0xc] = fVar2;
                pfVar10[0xd] = fVar2;
                pfVar15[0xd] = fVar2;
                pfVar10[0xe] = fVar2;
                pfVar15[0xe] = fVar2;
                pfVar10[0xf] = fVar2;
                pfVar15[0xf] = fVar2;
                pfVar10[0x10] = fVar2;
                pfVar15[0x10] = fVar2;
                pfVar10[0x11] = fVar2;
                pfVar15[0x11] = fVar2;
                pfVar10[0x12] = fVar2;
                pfVar15[0x12] = fVar2;
                pfVar10[0x13] = fVar2;
                pfVar15[0x13] = fVar2;
                pfVar10[0x14] = fVar2;
                pfVar15[0x14] = fVar2;
                pfVar10[0x15] = fVar2;
                pfVar15[0x15] = fVar2;
                pfVar10[0x16] = fVar2;
                pfVar15[0x16] = fVar2;
                pfVar10[0x17] = fVar2;
                pfVar10 = pfVar10 + 0x18;
                pfVar15[0x17] = fVar2;
                fVar3 = FLOAT_80330e4c;
                pfVar15 = pfVar15 + 0x18;
                iVar22 = iVar22 + -1;
              } while (iVar22 != 0);
              iVar22 = 0x121 - uVar12;
              pfVar17 = pfVar17 + uVar12;
              pfVar18 = pfVar18 + uVar12;
              if (uVar12 < 0x121) {
                do {
                  *pfVar17 = fVar3;
                  pfVar17 = pfVar17 + 1;
                  uVar12 = uVar12 + 1;
                  *pfVar18 = fVar3;
                  pfVar18 = pfVar18 + 1;
                  iVar22 = iVar22 + -1;
                } while (iVar22 != 0);
              }
              CreateWaterMesh__FP3VecP3VecP5Vec2dPUsf
                        ((double)*(float *)(param_2->m_payload + 0x18),puVar24[0xf],puVar24[0x10],
                         puVar24[0x15],puVar24[0x14],uVar12);
            }
            iVar5 = iVar5 + 0x14;
          }
        }
        if ((param_2->m_payload[8] == '\x01') || (param_2->m_payload[8] == '\x02')) {
          if (puVar24[0x12] != 0) {
            *(undefined4 *)(puVar24[0x12] + 0x240) = *(undefined4 *)(param_2->m_payload + 0x20);
          }
        }
      }
      uVar1 = param_2->m_payload[8];
      if (uVar1 != '\0') {
        if ((uVar1 == '\x01') || (uVar1 == '\x02')) {
          UpdateWaterMesh__FP7VYmMana(puVar24);
        }
        iVar5 = *(int *)(iVar6 + 0xac);
        for (uVar23 = 0; uVar23 < *(uint *)(*(int *)(iVar6 + 0xa4) + 0xc); uVar23 = uVar23 + 1) {
          iVar22 = *(int *)(iVar5 + 8);
          if ((((param_2->m_payload[8] == '\x01') &&
               (iVar11 = strcmp(iVar22,&DAT_80330e88), iVar11 == 0)) ||
              ((param_2->m_payload[8] == '\x02' &&
               (iVar11 = strcmp(iVar22,&DAT_80330e90), iVar11 == 0)))) ||
             ((param_2->m_payload[8] == '\x03' &&
              (iVar11 = strcmp(iVar22,&DAT_80330e98), iVar11 == 0)))) {
            iVar21 = *(int *)(iVar22 + 0x4c) + -1;
            iVar11 = iVar21 * 4;
            for (; -1 < iVar21; iVar21 = iVar21 + -1) {
              CalcReflectionVector2__FP3VecP6S16VecP6S16VeclUlUlPA4_fPvUlP8_GXColorP8S16Vec2dP8S16Vec2dPQ26CChara5CNodeP7PYmManaP7VYmMana
                        (puVar24[0x19],*(undefined4 *)(iVar22 + 0x18),*(undefined4 *)(iVar22 + 0x20)
                         ,*(undefined4 *)(iVar22 + 0x14),
                         *(undefined4 *)(*(int *)(iVar6 + 0xa4) + 0x34),
                         *(undefined4 *)(*(int *)(iVar6 + 0xa4) + 0x38),iVar6 + 8,
                         *(undefined4 *)(puVar24[0x18] + iVar11),puVar24[0x3c],puVar24[0x1a],
                         puVar24[0x1b],puVar24[0x1c],
                         *(int *)(iVar6 + 0xa8) + *(int *)(iVar22 + 0x5c) * 0xc0,param_2,puVar24);
              iVar11 = iVar11 + -4;
            }
          }
          iVar5 = iVar5 + 0x14;
        }
      }
    }
  }
  return;
}

