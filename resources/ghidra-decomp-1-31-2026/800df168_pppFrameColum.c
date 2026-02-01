// Function: pppFrameColum
// Entry: 800df168
// Size: 324 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFrameColum(pppColum *pppColum,UnkB *param_2,UnkC *param_3)

{
  undefined4 uVar1;
  undefined uVar2;
  int iVar3;
  undefined *puVar4;
  float *pfVar5;
  double dVar6;
  
  if (DAT_8032ed70 == 0) {
    puVar4 = (undefined *)((int)(&pppColum->field0_0x0 + 2) + param_3->m_serializedDataOffsets[3]);
    if (*(int *)(puVar4 + 8) == 0) {
      uVar1 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                        ((uint)*(byte *)((int)&param_2->m_arg3 + 1) * 0xc,pppEnvStPtr->m_stagePtr,
                         s_pppColum_cpp_801db638,0x7d);
      *(undefined4 *)(puVar4 + 8) = uVar1;
      pfVar5 = *(float **)(puVar4 + 8);
      for (iVar3 = 0; iVar3 < (int)(uint)*(byte *)((int)&param_2->m_arg3 + 1); iVar3 = iVar3 + 1) {
        dVar6 = (double)RandF__5CMathFf((double)*(float *)(param_2->m_payload + 4),&Math);
        *pfVar5 = (float)dVar6;
        *pfVar5 = *pfVar5 + *(float *)param_2->m_payload;
        dVar6 = (double)RandF__5CMathFf((double)*(float *)(param_2->m_payload + 0xc),&Math);
        pfVar5[1] = (float)dVar6;
        pfVar5[1] = pfVar5[1] + *(float *)(param_2->m_payload + 8);
        uVar2 = GetNoise__5CUtilFUc((CUtil *)&DAT_8032ec70,(uint)param_2->m_payload[0x16]);
        *(undefined *)(pfVar5 + 2) = uVar2;
        uVar2 = GetNoise__5CUtilFUc((CUtil *)&DAT_8032ec70,(uint)param_2->m_payload[0x17]);
        *(undefined *)((int)pfVar5 + 9) = uVar2;
        uVar2 = GetNoise__5CUtilFUc((CUtil *)&DAT_8032ec70,(uint)param_2->m_payload[0x18]);
        *(undefined *)((int)pfVar5 + 10) = uVar2;
        pfVar5 = pfVar5 + 3;
      }
    }
    if (param_2->m_dataValIndex != 0xffff) {
      pppCalcFrameShape__FPlRsRsRss
                (**(undefined4 **)
                   (*(int *)pppEnvStPtr->m_particleColors[0].m_colorRGBA +
                   param_2->m_dataValIndex * 4),puVar4,puVar4 + 2,puVar4 + 4,
                 (int)*(short *)&param_2->m_initWOrk);
    }
  }
  return;
}

