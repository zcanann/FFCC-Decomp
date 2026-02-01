// Function: pppFrameYmMelt
// Entry: 800a5a40
// Size: 680 bytes

/* WARNING: Removing unreachable block (ram,0x800a5ccc) */
/* WARNING: Removing unreachable block (ram,0x800a5cc4) */
/* WARNING: Removing unreachable block (ram,0x800a5cbc) */
/* WARNING: Removing unreachable block (ram,0x800a5cb4) */
/* WARNING: Removing unreachable block (ram,0x800a5cac) */
/* WARNING: Removing unreachable block (ram,0x800a5ca4) */
/* WARNING: Removing unreachable block (ram,0x800a5c9c) */
/* WARNING: Removing unreachable block (ram,0x800a5c94) */
/* WARNING: Removing unreachable block (ram,0x800a5a88) */
/* WARNING: Removing unreachable block (ram,0x800a5a80) */
/* WARNING: Removing unreachable block (ram,0x800a5a78) */
/* WARNING: Removing unreachable block (ram,0x800a5a70) */
/* WARNING: Removing unreachable block (ram,0x800a5a68) */
/* WARNING: Removing unreachable block (ram,0x800a5a60) */
/* WARNING: Removing unreachable block (ram,0x800a5a58) */
/* WARNING: Removing unreachable block (ram,0x800a5a50) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFrameYmMelt(pppYmMelt *pppYmMelt,UnkB *param_2,UnkC *param_3)

{
  short sVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  Vec *pVVar6;
  Vec *pVVar7;
  Vec *source;
  int *piVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  Mtx MStack_e8;
  undefined4 local_b8;
  uint uStack_b4;
  undefined4 local_b0;
  uint uStack_ac;
  
  if (DAT_8032ed70 == 0) {
    iVar5 = *(ushort *)((int)&param_2->m_initWOrk + 2) + 1;
    iVar4 = param_3->m_serializedDataOffsets[1];
    piVar8 = (int *)((int)(&pppYmMelt->field0_0x0 + 2) + *param_3->m_serializedDataOffsets);
    dVar12 = (double)(pppMngStPtr->m_matrix).value[1][3];
    if (*piVar8 == 0) {
      iVar5 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                        (iVar5 * iVar5 * 0x10,pppEnvStPtr->m_stagePtr,s_pppYmMelt_cpp_801da048,0xa9)
      ;
      *piVar8 = iVar5;
      pVVar6 = (Vec *)*piVar8;
      iVar5 = rand();
      fVar3 = FLOAT_80330b0c;
      fVar2 = FLOAT_80330b08;
      dVar9 = DOUBLE_80330b00;
      dVar11 = DOUBLE_80330af8;
      sVar1 = *(short *)((int)&param_2->m_arg3 + 2);
      local_b8 = 0x43300000;
      local_b0 = 0x43300000;
      dVar16 = (double)FLOAT_80330af0;
      *(short *)(piVar8 + 1) = (short)iVar5 - (short)(iVar5 / (int)sVar1) * sVar1;
      uStack_b4 = (uint)*(ushort *)((int)&param_2->m_initWOrk + 2);
      dVar13 = (double)(param_2->m_stepValue * fVar2);
      sVar1 = *(short *)(piVar8 + 1);
      uStack_ac = (int)sVar1 ^ 0x80000000;
      dVar14 = (double)(param_2->m_stepValue /
                       (float)((double)CONCAT44(0x43300000,uStack_b4) - dVar11));
      dVar10 = (double)(fVar3 * (float)((double)CONCAT44(0x43300000,uStack_ac) - dVar9));
      dVar9 = -dVar13;
      pVVar7 = pVVar6;
      dVar11 = dVar9;
      for (; source = pVVar7, dVar15 = dVar11, dVar9 <= dVar13;
          dVar9 = (double)(float)(dVar9 + dVar14)) {
        for (; dVar15 <= dVar13; dVar15 = (double)(float)(dVar15 + dVar14)) {
          source->x = (float)dVar15;
          source->y = (float)dVar16;
          source->z = (float)dVar9;
          if (sVar1 != 0) {
            PSMTXRotRad((float)dVar10,&MStack_e8,0x79);
            PSMTXMultVec(&MStack_e8,source,source);
          }
          pVVar7 = (Vec *)&pVVar7[1].y;
          source = (Vec *)&source[1].y;
        }
      }
      CalcPolygonHeight__FP7PYmMeltP11VERTEX_DATAP8_GXColorf
                (dVar12,param_2,pVVar6,&pppYmMelt->field_0x88 + iVar4);
    }
    piVar8[4] = (int)((float)piVar8[4] + (float)piVar8[5]);
    piVar8[3] = (int)((float)piVar8[3] + (float)piVar8[4]);
    if (param_2->m_graphId == (pppYmMelt->field0_0x0).m_graphId) {
      piVar8[3] = (int)((float)piVar8[3] + *(float *)param_2->m_payload);
      piVar8[4] = (int)((float)piVar8[4] + *(float *)(param_2->m_payload + 4));
      piVar8[5] = (int)((float)piVar8[5] + *(float *)(param_2->m_payload + 8));
    }
    if (param_2->m_dataValIndex != 0xffff) {
      pppCalcFrameShape__FPlRsRsRss
                (**(undefined4 **)
                   (*(int *)pppEnvStPtr->m_particleColors[0].m_colorRGBA +
                   param_2->m_dataValIndex * 4),(int)piVar8 + 6,piVar8 + 2,(int)piVar8 + 10,
                 (int)*(short *)&param_2->m_initWOrk);
    }
  }
  return;
}

