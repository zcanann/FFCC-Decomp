// Function: pppFrameYmDrawMdlTexAnm
// Entry: 8008a604
// Size: 820 bytes

/* WARNING: Removing unreachable block (ram,0x8008a918) */
/* WARNING: Removing unreachable block (ram,0x8008a910) */
/* WARNING: Removing unreachable block (ram,0x8008a61c) */
/* WARNING: Removing unreachable block (ram,0x8008a614) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFrameYmDrawMdlTexAnm(pppYmDrawMdlTexAnm *pppYmDrawMdlTexAnm,UnkB *param_2,UnkC *param_3)

{
  double dVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  CMapMesh *pCVar5;
  uint *puVar6;
  double dVar7;
  double dVar8;
  undefined8 local_50;
  undefined8 local_38;
  
  puVar6 = (uint *)((int)(&pppYmDrawMdlTexAnm->field0_0x0 + 2) + param_3->m_serializedDataOffsets[2]
                   );
  if (DAT_8032ed70 == 0) {
    puVar6[1] = puVar6[1] - *(int *)param_2->m_payload;
    puVar6[2] = *(uint *)(param_2->m_payload + 4);
    puVar6[3] = *(uint *)(param_2->m_payload + 8);
    dVar1 = DOUBLE_80330550;
    if ((int)puVar6[1] < 1) {
      dVar8 = (double)(float)puVar6[4];
      dVar7 = (double)(float)puVar6[5];
      pCVar5 = pppEnvStPtr->m_mapMeshPtr[param_2->m_dataValIndex];
      if ((dVar8 == (double)FLOAT_8033054c) || (dVar7 == (double)FLOAT_8033054c)) {
        if (pCVar5 == (CMapMesh *)0x0) {
          return;
        }
        iVar3 = 0;
        for (iVar2 = 0; iVar2 < (int)(uint)(ushort)pCVar5->field3_0x6; iVar2 = iVar2 + 1) {
          uVar4 = (int)*(short *)(pCVar5->field17_0x38 + iVar3) ^ 0x80000000;
          if ((float)puVar6[4] < (float)((double)CONCAT44(0x43300000,uVar4) - dVar1)) {
            puVar6[4] = (uint)(float)((double)CONCAT44(0x43300000,uVar4) - dVar1);
          }
          uVar4 = (int)*(short *)(pCVar5->field17_0x38 + iVar3 + 2) ^ 0x80000000;
          if ((float)puVar6[5] < (float)((double)CONCAT44(0x43300000,uVar4) - dVar1)) {
            puVar6[5] = (uint)(float)((double)CONCAT44(0x43300000,uVar4) - dVar1);
          }
          iVar3 = iVar3 + 4;
        }
        OSReport((double)(float)puVar6[4],(double)(float)puVar6[5],
                 s_PerU___0_2f_PerV___0_2f_801d9c38);
      }
      dVar1 = DOUBLE_80330550;
      iVar2 = 0;
      *puVar6 = *puVar6 + 1;
      puVar6[1] = 0x200;
      for (iVar3 = 0; iVar3 < (int)(uint)(ushort)pCVar5->field3_0x6; iVar3 = iVar3 + 1) {
        *(short *)(pCVar5->field17_0x38 + iVar2) =
             (short)(int)((double)(float)((double)CONCAT44(0x43300000,
                                                           (int)*(short *)(pCVar5->field17_0x38 +
                                                                          iVar2) ^ 0x80000000) -
                                         dVar1) + dVar8);
        uVar4 = *(uint *)(param_2->m_payload + 4);
        if (*puVar6 == (*puVar6 / uVar4) * uVar4) {
          local_50 = (double)CONCAT44(0x43300000,uVar4);
          *(short *)(pCVar5->field17_0x38 + iVar2) =
               (short)(int)-(float)(dVar8 * (double)(float)(local_50 - DOUBLE_80330558) -
                                   (double)(float)((double)CONCAT44(0x43300000,
                                                                    (int)*(short *)(pCVar5->
                                                  field17_0x38 + iVar2) ^ 0x80000000) - dVar1));
          *(short *)(pCVar5->field17_0x38 + iVar2 + 2) =
               (short)(int)((double)(float)((double)CONCAT44(0x43300000,
                                                             (int)*(short *)(pCVar5->field17_0x38 +
                                                                            iVar2 + 2) ^ 0x80000000)
                                           - dVar1) + dVar7);
        }
        if ((uint)(*(int *)(param_2->m_payload + 4) * *(int *)(param_2->m_payload + 8)) <= *puVar6)
        {
          local_38 = (double)CONCAT44(0x43300000,*(int *)(param_2->m_payload + 8));
          *(short *)(pCVar5->field17_0x38 + iVar2 + 2) =
               (short)(int)-(float)(dVar7 * (double)(float)(local_38 - DOUBLE_80330558) -
                                   (double)(float)((double)CONCAT44(0x43300000,
                                                                    (int)*(short *)(pCVar5->
                                                  field17_0x38 + iVar2 + 2) ^ 0x80000000) -
                                                  DOUBLE_80330550));
        }
        iVar2 = iVar2 + 4;
      }
      DCFlushRange(pCVar5->field17_0x38,(uint)(ushort)pCVar5->field3_0x6 << 2);
      if ((uint)(*(int *)(param_2->m_payload + 4) * *(int *)(param_2->m_payload + 8)) <= *puVar6) {
        *puVar6 = 0;
      }
    }
  }
  return;
}

