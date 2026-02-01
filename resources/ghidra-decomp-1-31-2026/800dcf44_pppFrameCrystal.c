// Function: pppFrameCrystal
// Entry: 800dcf44
// Size: 1080 bytes

/* WARNING: Removing unreachable block (ram,0x800dd360) */
/* WARNING: Removing unreachable block (ram,0x800dd358) */
/* WARNING: Removing unreachable block (ram,0x800dd350) */
/* WARNING: Removing unreachable block (ram,0x800dd348) */
/* WARNING: Removing unreachable block (ram,0x800dd340) */
/* WARNING: Removing unreachable block (ram,0x800dd338) */
/* WARNING: Removing unreachable block (ram,0x800dd330) */
/* WARNING: Removing unreachable block (ram,0x800dd328) */
/* WARNING: Removing unreachable block (ram,0x800dd320) */
/* WARNING: Removing unreachable block (ram,0x800dd318) */
/* WARNING: Removing unreachable block (ram,0x800dd310) */
/* WARNING: Removing unreachable block (ram,0x800dcfa4) */
/* WARNING: Removing unreachable block (ram,0x800dcf9c) */
/* WARNING: Removing unreachable block (ram,0x800dcf94) */
/* WARNING: Removing unreachable block (ram,0x800dcf8c) */
/* WARNING: Removing unreachable block (ram,0x800dcf84) */
/* WARNING: Removing unreachable block (ram,0x800dcf7c) */
/* WARNING: Removing unreachable block (ram,0x800dcf74) */
/* WARNING: Removing unreachable block (ram,0x800dcf6c) */
/* WARNING: Removing unreachable block (ram,0x800dcf64) */
/* WARNING: Removing unreachable block (ram,0x800dcf5c) */
/* WARNING: Removing unreachable block (ram,0x800dcf54) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFrameCrystal(pppCrystal *pppCrystal,UnkB *param_2,UnkC *param_3)

{
  float fVar1;
  uint uVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  undefined uVar6;
  undefined *puVar7;
  int *piVar8;
  int *piVar9;
  uint uVar10;
  uint uVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  double dVar18;
  double dVar19;
  double dVar20;
  double dVar21;
  double dVar22;
  double dVar23;
  undefined4 local_e4;
  undefined4 local_e0;
  int iStack_dc;
  undefined4 local_d8;
  int iStack_d4;
  
  if (DAT_8032ed70 == 0) {
    piVar9 = (int *)((int)(&pppCrystal->field0_0x0 + 2) + param_3->m_serializedDataOffsets[2]);
    if (param_2->m_dataValIndex != 0xffff) {
      local_e4 = 0;
      GetTexture__8CMapMeshFP12CMaterialSetRi
                (pppEnvStPtr->m_mapMeshPtr[param_2->m_dataValIndex],pppEnvStPtr->m_materialSetPtr,
                 &local_e4);
      if (param_2->m_payload[0] == '\0') {
        if (param_2->m_initWOrk == 0xffff) {
          return;
        }
        GetTexture__8CMapMeshFP12CMaterialSetRi
                  (pppEnvStPtr->m_mapMeshPtr[param_2->m_initWOrk],pppEnvStPtr->m_materialSetPtr,
                   &local_e4);
      }
      if ((param_2->m_payload[0] == '\x01') && (*piVar9 == 0)) {
        iVar4 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                          (0x18,pppEnvStPtr->m_stagePtr,s_pppCrystal_cpp_801db600,0xa7);
        *piVar9 = iVar4;
        piVar8 = (int *)*piVar9;
        iVar4 = GXGetTexBufferSize(0x20,0x20,3,0,0);
        iVar5 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                          (iVar4,pppEnvStPtr->m_stagePtr,s_pppCrystal_cpp_801db600,0xac);
        *piVar8 = iVar5;
        piVar8[1] = 3;
        dVar20 = DOUBLE_80330fc8;
        piVar8[2] = 0x20;
        fVar3 = FLOAT_80330fd0;
        piVar8[3] = 0x20;
        fVar1 = FLOAT_80330fd4;
        piVar8[4] = 0x100;
        dVar23 = (double)FLOAT_80330fd8;
        piVar8[5] = iVar4;
        dVar13 = (double)FLOAT_80330ff8;
        iStack_dc = piVar8[2] + -1;
        local_e0 = 0x43300000;
        iStack_d4 = piVar8[3] + -1;
        dVar14 = (double)FLOAT_80331008;
        dVar15 = (double)FLOAT_80331010;
        dVar16 = (double)FLOAT_8033100c;
        local_d8 = 0x43300000;
        dVar21 = (double)(fVar3 / (float)((double)CONCAT44(0x43300000,iStack_dc) - dVar20));
        dVar20 = (double)(fVar3 / (float)((double)CONCAT44(0x43300000,iStack_d4) - dVar20));
        for (uVar10 = 0; dVar19 = (double)fVar1, uVar10 < (uint)piVar8[3]; uVar10 = uVar10 + 1) {
          dVar17 = (double)(float)(dVar19 * dVar19);
          fVar1 = FLOAT_80330fd4;
          for (uVar11 = 0; dVar18 = (double)fVar1, uVar11 < (uint)piVar8[2]; uVar11 = uVar11 + 1) {
            fVar1 = (float)(dVar18 * dVar18 + dVar17);
            dVar22 = (double)fVar1;
            if (dVar22 <= dVar23) {
              if (DOUBLE_80330ff0 <= dVar22) {
                uVar2 = (uint)fVar1 & 0x7f800000;
                if (uVar2 == 0x7f800000) {
                  if (((uint)fVar1 & 0x7fffff) == 0) {
                    iVar4 = 2;
                  }
                  else {
                    iVar4 = 1;
                  }
                }
                else if ((uVar2 < 0x7f800000) && (uVar2 == 0)) {
                  if (((uint)fVar1 & 0x7fffff) == 0) {
                    iVar4 = 3;
                  }
                  else {
                    iVar4 = 5;
                  }
                }
                else {
                  iVar4 = 4;
                }
                if (iVar4 == 1) {
                  dVar22 = (double)DAT_8032ec20;
                }
              }
              else {
                dVar22 = (double)DAT_8032ec20;
              }
            }
            else {
              dVar12 = 1.0 / SQRT(dVar22);
              dVar12 = DOUBLE_80330fe0 * dVar12 * -(dVar22 * dVar12 * dVar12 - DOUBLE_80330fe8);
              dVar12 = DOUBLE_80330fe0 * dVar12 * -(dVar22 * dVar12 * dVar12 - DOUBLE_80330fe8);
              dVar22 = (double)(float)(dVar22 * DOUBLE_80330fe0 * dVar12 *
                                                -(dVar22 * dVar12 * dVar12 - DOUBLE_80330fe8));
            }
            if (dVar13 < dVar22) {
              dVar22 = dVar13;
            }
            dVar12 = (double)fmod(dVar22,DOUBLE_80331000);
            dVar22 = (double)(float)(dVar14 * (double)(float)(dVar22 * (double)(float)dVar12));
            uVar6 = __cvt_fp2unsigned((double)(float)(dVar15 * (double)(float)(dVar18 * dVar22) +
                                                     dVar16));
            puVar7 = (undefined *)
                     (*piVar8 +
                     (uVar10 >> 2) * (piVar8[2] & 0x1ffffffcU) * 8 + (uVar11 & 0x1ffffffc) * 8 +
                     ((uVar11 & 3) + (uVar10 & 3) * 4) * 2);
            *puVar7 = uVar6;
            uVar6 = __cvt_fp2unsigned((double)(float)(dVar15 * (double)(float)(dVar19 * dVar22) +
                                                     dVar16));
            fVar1 = (float)(dVar18 + dVar21);
            puVar7[1] = uVar6;
          }
          fVar1 = (float)(dVar19 + dVar20);
        }
        DCFlushRange(*piVar8,piVar8[5]);
        iVar4 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                          (0x20,pppEnvStPtr->m_stagePtr,s_pppCrystal_cpp_801db600,0xb4);
        piVar9[1] = iVar4;
        GXInitTexObj(piVar9[1],*piVar8,piVar8[2] & 0xffff,piVar8[3] & 0xffff,3,0,0,0);
      }
    }
  }
  return;
}

