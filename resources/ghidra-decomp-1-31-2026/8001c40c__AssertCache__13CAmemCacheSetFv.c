// Function: ?AssertCache__13CAmemCacheSetFv
// Entry: 8001c40c
// Size: 288 bytes

void _AssertCache__13CAmemCacheSetFv(CAmemCacheSet *amemCacheSet)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  
  if (2 < (uint)System.m_execParam) {
    Printf__7CSystemFPce(&System,s__________________________________801d64f4);
  }
  iVar4 = 0;
  for (iVar3 = 0; iVar3 < *(int *)&amemCacheSet->field_0x3c; iVar3 = iVar3 + 1) {
    piVar2 = (int *)(*(int *)&amemCacheSet->field_0x58 + iVar4);
    if (((*(byte *)((int)piVar2 + 0xe) != 0) || (*piVar2 != 0)) && (2 < (uint)System.m_execParam)) {
      uVar1 = countLeadingZeros((uint)*(byte *)((int)piVar2 + 0xe));
      Printf__7CSystemFPce
                (&System,s__03d__s_type__s_RefCnt__d_prio___801d6580,iVar3,
                 *(undefined4 *)((int)&PTR_s_USE_8032e410 + (uVar1 >> 3 & 0x1ffffffc)),
                 (&PTR_s_TEXTURE_801e8470)[*(byte *)((int)piVar2 + 0xf)],*(undefined2 *)(piVar2 + 3)
                 ,piVar2[4],*piVar2);
    }
    iVar4 = iVar4 + 0x1c;
  }
  if (2 < (uint)System.m_execParam) {
    Printf__7CSystemFPce(&System,&DAT_8032f7c8);
  }
  return;
}

