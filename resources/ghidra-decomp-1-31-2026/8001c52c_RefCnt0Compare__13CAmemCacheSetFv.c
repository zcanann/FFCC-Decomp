// Function: RefCnt0Compare__13CAmemCacheSetFv
// Entry: 8001c52c
// Size: 260 bytes

void RefCnt0Compare__13CAmemCacheSetFv(CAmemCacheSet *amemCacheSet)

{
  uint uVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  
  if (2 < (uint)System.m_execParam) {
    Printf__7CSystemFPce(&System,s__________________________________801d65b4);
  }
  iVar3 = 0;
  for (iVar4 = 0; iVar4 < *(int *)&amemCacheSet->field_0x3c; iVar4 = iVar4 + 1) {
    puVar2 = (undefined4 *)(*(int *)&amemCacheSet->field_0x58 + iVar3);
    if (((*(byte *)((int)puVar2 + 0xe) != 0) && (*(short *)(puVar2 + 3) != 0)) &&
       (2 < (uint)System.m_execParam)) {
      uVar1 = countLeadingZeros((uint)*(byte *)((int)puVar2 + 0xe));
      Printf__7CSystemFPce
                (&System,s__03d__s_type__s_RefCnt__d_prio___801d6580,iVar4,
                 *(undefined4 *)((int)&PTR_s_USE_8032e410 + (uVar1 >> 3 & 0x1ffffffc)),
                 (&PTR_s_TEXTURE_801e8470)[*(byte *)((int)puVar2 + 0xf)],*(short *)(puVar2 + 3),
                 puVar2[4],*puVar2);
    }
    iVar3 = iVar3 + 0x1c;
  }
  if (2 < (uint)System.m_execParam) {
    Printf__7CSystemFPce(&System,s__________________________________801d65ec);
  }
  return;
}

