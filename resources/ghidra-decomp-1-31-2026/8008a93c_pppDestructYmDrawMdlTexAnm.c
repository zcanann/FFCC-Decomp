// Function: pppDestructYmDrawMdlTexAnm
// Entry: 8008a93c
// Size: 328 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppDestructYmDrawMdlTexAnm(pppYmDrawMdlTexAnm *pppYmDrawMdlTexAnm,UnkC *param_2)

{
  double dVar1;
  int iVar2;
  int iVar3;
  CMapMesh *pCVar4;
  int iVar5;
  uint uVar6;
  uint *puVar7;
  
  dVar1 = DOUBLE_80330550;
  puVar7 = (uint *)((int)(&pppYmDrawMdlTexAnm->field0_0x0 + 2) + param_2->m_serializedDataOffsets[2]
                   );
  if ((*puVar7 != 0) && (pCVar4 = *pppEnvStPtr->m_mapMeshPtr, pCVar4 != (CMapMesh *)0x0)) {
    iVar3 = 0;
    for (iVar5 = 0; iVar5 < (int)(uint)(ushort)pCVar4->field3_0x6; iVar5 = iVar5 + 1) {
      iVar2 = iVar3 + 2;
      uVar6 = *puVar7 / puVar7[2];
      *(short *)(pCVar4->field17_0x38 + iVar3) =
           (short)(int)-((float)((double)CONCAT44(0x43300000,
                                                  *puVar7 - uVar6 * puVar7[2] ^ 0x80000000) - dVar1)
                         * (float)puVar7[4] -
                        (float)((double)CONCAT44(0x43300000,
                                                 (int)*(short *)(pCVar4->field17_0x38 + iVar3) ^
                                                 0x80000000) - dVar1));
      iVar3 = iVar3 + 4;
      *(short *)(pCVar4->field17_0x38 + iVar2) =
           (short)(int)-((float)((double)CONCAT44(0x43300000,uVar6 ^ 0x80000000) - dVar1) *
                         (float)puVar7[5] -
                        (float)((double)CONCAT44(0x43300000,
                                                 (int)*(short *)(pCVar4->field17_0x38 + iVar2) ^
                                                 0x80000000) - dVar1));
    }
    DCFlushRange(pCVar4->field17_0x38,(uint)(ushort)pCVar4->field3_0x6 << 2);
  }
  *puVar7 = 0;
  puVar7[3] = 0;
  puVar7[2] = 0;
  puVar7[1] = 0x200;
  return;
}

