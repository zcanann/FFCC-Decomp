// Function: pppFrameCrystal2
// Entry: 8013eb50
// Size: 924 bytes

/* WARNING: Removing unreachable block (ram,0x8013eed0) */
/* WARNING: Removing unreachable block (ram,0x8013eec8) */
/* WARNING: Removing unreachable block (ram,0x8013eec0) */
/* WARNING: Removing unreachable block (ram,0x8013eeb8) */
/* WARNING: Removing unreachable block (ram,0x8013eeb0) */
/* WARNING: Removing unreachable block (ram,0x8013eea8) */
/* WARNING: Removing unreachable block (ram,0x8013eea0) */
/* WARNING: Removing unreachable block (ram,0x8013ee98) */
/* WARNING: Removing unreachable block (ram,0x8013ee90) */
/* WARNING: Removing unreachable block (ram,0x8013ee88) */
/* WARNING: Removing unreachable block (ram,0x8013eba8) */
/* WARNING: Removing unreachable block (ram,0x8013eba0) */
/* WARNING: Removing unreachable block (ram,0x8013eb98) */
/* WARNING: Removing unreachable block (ram,0x8013eb90) */
/* WARNING: Removing unreachable block (ram,0x8013eb88) */
/* WARNING: Removing unreachable block (ram,0x8013eb80) */
/* WARNING: Removing unreachable block (ram,0x8013eb78) */
/* WARNING: Removing unreachable block (ram,0x8013eb70) */
/* WARNING: Removing unreachable block (ram,0x8013eb68) */
/* WARNING: Removing unreachable block (ram,0x8013eb60) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFrameCrystal2(pppCrystal2 *pppCrystal2,UnkB *param_2,UnkC *param_3)

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
  
  if (((DAT_8032ed70 == 0) &&
      (piVar9 = (int *)((int)(&pppCrystal2->field0_0x0 + 2) + param_3->m_serializedDataOffsets[2]),
      param_2->m_payload[0] != '\0')) && (*piVar9 == 0)) {
    iVar4 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                      (0x18,pppEnvStPtr->m_stagePtr,s_pppCrystal2_cpp_801dd650,0xa8);
    *piVar9 = iVar4;
    piVar8 = (int *)*piVar9;
    iVar4 = GXGetTexBufferSize(0x20,0x20,3,0,0);
    iVar5 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                      (iVar4,pppEnvStPtr->m_stagePtr,s_pppCrystal2_cpp_801dd650,0xad);
    *piVar8 = iVar5;
    piVar8[1] = 3;
    dVar19 = DOUBLE_80332018;
    piVar8[2] = 0x20;
    fVar3 = FLOAT_80331fe0;
    piVar8[3] = 0x20;
    fVar1 = FLOAT_80331fe4;
    piVar8[4] = 0x100;
    dVar22 = (double)FLOAT_80331fe8;
    piVar8[5] = iVar4;
    dVar13 = (double)FLOAT_80332008;
    dVar14 = (double)FLOAT_80332010;
    dVar15 = (double)FLOAT_8033200c;
    dVar20 = (double)(fVar3 / (float)((double)CONCAT44(0x43300000,piVar8[2] + -1) - dVar19));
    dVar19 = (double)(fVar3 / (float)((double)CONCAT44(0x43300000,piVar8[3] + -1) - dVar19));
    for (uVar10 = 0; dVar18 = (double)fVar1, uVar10 < (uint)piVar8[3]; uVar10 = uVar10 + 1) {
      dVar16 = (double)(float)(dVar18 * dVar18);
      fVar1 = FLOAT_80331fe4;
      for (uVar11 = 0; dVar17 = (double)fVar1, uVar11 < (uint)piVar8[2]; uVar11 = uVar11 + 1) {
        fVar1 = (float)(dVar17 * dVar17 + dVar16);
        dVar21 = (double)fVar1;
        if (dVar21 <= dVar22) {
          if (DOUBLE_80332000 <= dVar21) {
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
              dVar21 = (double)DAT_8032ec20;
            }
          }
          else {
            dVar21 = (double)DAT_8032ec20;
          }
        }
        else {
          dVar12 = 1.0 / SQRT(dVar21);
          dVar12 = DOUBLE_80331ff0 * dVar12 * -(dVar21 * dVar12 * dVar12 - DOUBLE_80331ff8);
          dVar12 = DOUBLE_80331ff0 * dVar12 * -(dVar21 * dVar12 * dVar12 - DOUBLE_80331ff8);
          dVar21 = (double)(float)(dVar21 * DOUBLE_80331ff0 * dVar12 *
                                            -(dVar21 * dVar12 * dVar12 - DOUBLE_80331ff8));
        }
        if (dVar13 < dVar21) {
          dVar21 = dVar13;
        }
        uVar6 = __cvt_fp2unsigned((double)(float)(dVar14 * (double)(float)(dVar17 * dVar21) + dVar15
                                                 ));
        puVar7 = (undefined *)
                 (*piVar8 +
                 (uVar10 >> 2) * (piVar8[2] & 0x1ffffffcU) * 8 + (uVar11 & 0x1ffffffc) * 8 +
                 ((uVar11 & 3) + (uVar10 & 3) * 4) * 2);
        *puVar7 = uVar6;
        uVar6 = __cvt_fp2unsigned((double)(float)(dVar14 * (double)(float)(dVar18 * dVar21) + dVar15
                                                 ));
        fVar1 = (float)(dVar17 + dVar20);
        puVar7[1] = uVar6;
      }
      fVar1 = (float)(dVar18 + dVar19);
    }
    DCFlushRange(*piVar8,piVar8[5]);
    iVar4 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                      (0x20,pppEnvStPtr->m_stagePtr,s_pppCrystal2_cpp_801dd650,0xb5);
    piVar9[1] = iVar4;
    GXInitTexObj(piVar9[1],*piVar8,piVar8[2] & 0xffff,piVar8[3] & 0xffff,3,1,1,0);
  }
  return;
}

