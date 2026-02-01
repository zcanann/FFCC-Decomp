// Function: AddRef__13CAmemCacheSetFs
// Entry: 8001cd48
// Size: 360 bytes

void AddRef__13CAmemCacheSetFs(CAmemCacheSet *amemCacheSet,short param_2)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  
  iVar4 = param_2 * 0x1c;
  iVar2 = *(int *)&amemCacheSet->field_0x58 + iVar4;
  *(short *)(iVar2 + 0xc) = *(short *)(iVar2 + 0xc) + 1;
  if (*(short *)(*(int *)&amemCacheSet->field_0x58 + iVar4 + 0xc) == -1) {
    if (2 < (uint)System.m_execParam) {
      Printf__7CSystemFPce(&System,s__________________________________801d64f4);
    }
    iVar2 = 0;
    for (iVar5 = 0; iVar5 < *(int *)&amemCacheSet->field_0x3c; iVar5 = iVar5 + 1) {
      piVar3 = (int *)(*(int *)&amemCacheSet->field_0x58 + iVar2);
      if (((*(byte *)((int)piVar3 + 0xe) != 0) || (*piVar3 != 0)) && (2 < (uint)System.m_execParam))
      {
        uVar1 = countLeadingZeros((uint)*(byte *)((int)piVar3 + 0xe));
        Printf__7CSystemFPce
                  (&System,s__03d__s_type__s_RefCnt__d_prio___801d6580,iVar5,
                   *(undefined4 *)((int)&PTR_s_USE_8032e410 + (uVar1 >> 3 & 0x1ffffffc)),
                   (&PTR_s_TEXTURE_801e8470)[*(byte *)((int)piVar3 + 0xf)],
                   *(undefined2 *)(piVar3 + 3),piVar3[4],*piVar3);
      }
      iVar2 = iVar2 + 0x1c;
    }
    if (2 < (uint)System.m_execParam) {
      Printf__7CSystemFPce(&System,&DAT_8032f7c8);
    }
    if (*(code **)&amemCacheSet->field_0x50 != (code *)0x0) {
      (**(code **)&amemCacheSet->field_0x50)((int)param_2);
    }
  }
  *(undefined4 *)(*(int *)&amemCacheSet->field_0x58 + iVar4 + 0x10) = 0x7ffffff0;
  return;
}

