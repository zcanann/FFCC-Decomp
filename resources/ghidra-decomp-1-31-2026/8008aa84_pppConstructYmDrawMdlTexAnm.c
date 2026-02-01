// Function: pppConstructYmDrawMdlTexAnm
// Entry: 8008aa84
// Size: 316 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConstructYmDrawMdlTexAnm(pppYmDrawMdlTexAnm *pppYmDrawMdlTexAnm,UnkC *param_2)

{
  float fVar1;
  double dVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  CMapMesh *pCVar6;
  undefined4 *puVar7;
  
  puVar7 = (undefined4 *)
           ((int)(&pppYmDrawMdlTexAnm->field0_0x0 + 2) + param_2->m_serializedDataOffsets[2]);
  *puVar7 = 0;
  puVar7[1] = 0x200;
  OSReport(&DAT_801d9c54);
  fVar1 = FLOAT_8033054c;
  pCVar6 = *pppEnvStPtr->m_mapMeshPtr;
  puVar7[4] = FLOAT_8033054c;
  puVar7[5] = fVar1;
  dVar2 = DOUBLE_80330550;
  if (pCVar6 != (CMapMesh *)0x0) {
    iVar5 = 0;
    for (iVar4 = 0; iVar4 < (int)(uint)(ushort)pCVar6->field3_0x6; iVar4 = iVar4 + 1) {
      uVar3 = (int)*(short *)(pCVar6->field17_0x38 + iVar5) ^ 0x80000000;
      if ((float)puVar7[4] < (float)((double)CONCAT44(0x43300000,uVar3) - dVar2)) {
        puVar7[4] = (float)((double)CONCAT44(0x43300000,uVar3) - dVar2);
      }
      uVar3 = (int)*(short *)(pCVar6->field17_0x38 + iVar5 + 2) ^ 0x80000000;
      if ((float)puVar7[5] < (float)((double)CONCAT44(0x43300000,uVar3) - dVar2)) {
        puVar7[5] = (float)((double)CONCAT44(0x43300000,uVar3) - dVar2);
      }
      iVar5 = iVar5 + 4;
    }
    OSReport((double)(float)puVar7[4],(double)(float)puVar7[5],s_PerU___0_2f_PerV___0_2f_801d9c38);
  }
  return;
}

