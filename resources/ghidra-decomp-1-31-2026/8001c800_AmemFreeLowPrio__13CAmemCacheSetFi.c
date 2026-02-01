// Function: AmemFreeLowPrio__13CAmemCacheSetFi
// Entry: 8001c800
// Size: 1012 bytes

void AmemFreeLowPrio__13CAmemCacheSetFi(CAmemCacheSet *amemCacheSet,int param_2)

{
  int iVar1;
  int iVar2;
  char cVar3;
  int *piVar4;
  int iVar5;
  int *piVar6;
  uint uVar7;
  
  uVar7 = 0x7ffffff1;
  iVar5 = param_2;
LAB_8001c840:
  while( true ) {
    iVar1 = *(int *)&amemCacheSet->field_0x3c;
    piVar6 = (int *)0x0;
    iVar2 = 0;
    if (0 < iVar1) {
      do {
        piVar4 = (int *)(*(int *)&amemCacheSet->field_0x58 + iVar2);
        if ((((*(char *)((int)piVar4 + 0xe) != '\0') && (*(short *)(piVar4 + 3) == 0)) &&
            (*(char *)((int)piVar4 + 0x1a) != '\0')) &&
           (((*piVar4 != 0 && (iVar5 <= piVar4[2])) && ((uint)piVar4[4] < uVar7)))) {
          piVar6 = piVar4;
          uVar7 = piVar4[4];
        }
        iVar2 = iVar2 + 0x1c;
        iVar1 = iVar1 + -1;
      } while (iVar1 != 0);
    }
    if (piVar6 != (int *)0x0) {
      iVar1 = *piVar6;
      if (iVar1 != 0) {
        if ((*(short *)(iVar1 + -0x40) != 0x4b41) || (*(short *)(iVar1 + -2) != 0x4d49)) {
          Printf__7CSystemFPce
                    (&System,&DAT_801d6648,iVar1,iVar1 + -0x26,*(undefined2 *)(iVar1 + -0x28));
        }
        *(byte *)(iVar1 + -0x3e) = *(byte *)(iVar1 + -0x3e) & 0xfb;
        if ((*(byte *)(*(int *)(iVar1 + -0x38) + 2) & 4) == 0) {
          *(int *)(iVar1 + -0x30) =
               *(int *)(*(int *)(iVar1 + -0x38) + 0x10) + *(int *)(iVar1 + -0x30) + 0x40;
          *(int *)(*(int *)(*(int *)(iVar1 + -0x38) + 8) + 4) = iVar1 + -0x40;
          *(undefined4 *)(iVar1 + -0x38) = *(undefined4 *)(*(int *)(iVar1 + -0x38) + 8);
        }
        iVar2 = *(int *)(iVar1 + -0x3c);
        if ((*(byte *)(iVar2 + 2) & 4) == 0) {
          *(int *)(iVar2 + 0x10) = *(int *)(iVar1 + -0x30) + *(int *)(iVar2 + 0x10) + 0x40;
          *(undefined4 *)(*(int *)(iVar1 + -0x3c) + 8) = *(undefined4 *)(iVar1 + -0x38);
          *(undefined4 *)(*(int *)(iVar1 + -0x38) + 4) = *(undefined4 *)(iVar1 + -0x3c);
        }
        *(int *)(*(int *)(iVar1 + -0x34) + 0x124) = *(int *)(*(int *)(iVar1 + -0x34) + 0x124) + -1;
      }
      *piVar6 = 0;
    }
    iVar1 = alloc__Q27CMemory6CStageFUlPcUli
                      (amemCacheSet->m_stage,param_2,s_memory_cpp_801d6690,0x86d,1);
    if (iVar1 != 0) {
      if (iVar1 != 0) {
        if ((*(short *)(iVar1 + -0x40) != 0x4b41) || (*(short *)(iVar1 + -2) != 0x4d49)) {
          Printf__7CSystemFPce
                    (&System,&DAT_801d6648,iVar1,iVar1 + -0x26,*(undefined2 *)(iVar1 + -0x28));
        }
        *(byte *)(iVar1 + -0x3e) = *(byte *)(iVar1 + -0x3e) & 0xfb;
        if ((*(byte *)(*(int *)(iVar1 + -0x38) + 2) & 4) == 0) {
          *(int *)(iVar1 + -0x30) =
               *(int *)(*(int *)(iVar1 + -0x38) + 0x10) + *(int *)(iVar1 + -0x30) + 0x40;
          *(int *)(*(int *)(*(int *)(iVar1 + -0x38) + 8) + 4) = iVar1 + -0x40;
          *(undefined4 *)(iVar1 + -0x38) = *(undefined4 *)(*(int *)(iVar1 + -0x38) + 8);
        }
        iVar5 = *(int *)(iVar1 + -0x3c);
        if ((*(byte *)(iVar5 + 2) & 4) == 0) {
          *(int *)(iVar5 + 0x10) = *(int *)(iVar1 + -0x30) + *(int *)(iVar5 + 0x10) + 0x40;
          *(undefined4 *)(*(int *)(iVar1 + -0x3c) + 8) = *(undefined4 *)(iVar1 + -0x38);
          *(undefined4 *)(*(int *)(iVar1 + -0x38) + 4) = *(undefined4 *)(iVar1 + -0x3c);
        }
        *(int *)(*(int *)(iVar1 + -0x34) + 0x124) = *(int *)(*(int *)(iVar1 + -0x34) + 0x124) + -1;
        return;
      }
      return;
    }
    if (iVar5 == 0) break;
    iVar5 = iVar5 - param_2 / 2;
    if (iVar5 < 0) {
      iVar5 = 0;
    }
  }
  if (uVar7 == 0xffffffff) goto code_r0x8001cab0;
  goto LAB_8001cbc8;
code_r0x8001cab0:
  if ((*(code **)&amemCacheSet->field_0x40 == (code *)0x0) ||
     (cVar3 = (**(code **)&amemCacheSet->field_0x40)(*(undefined4 *)&amemCacheSet->field_0x44),
     cVar3 == '\0')) {
    (**(code **)&amemCacheSet->field_0x48)(*(undefined4 *)&amemCacheSet->field_0x4c);
    if (2 < (uint)System.m_execParam) {
      Printf__7CSystemFPce(&System,s__________________________________801d64f4);
    }
    iVar1 = 0;
    for (iVar2 = 0; iVar2 < *(int *)&amemCacheSet->field_0x3c; iVar2 = iVar2 + 1) {
      piVar6 = (int *)(*(int *)&amemCacheSet->field_0x58 + iVar1);
      if (((*(byte *)((int)piVar6 + 0xe) != 0) || (*piVar6 != 0)) && (2 < (uint)System.m_execParam))
      {
        uVar7 = countLeadingZeros((uint)*(byte *)((int)piVar6 + 0xe));
        Printf__7CSystemFPce
                  (&System,s__03d__s_type__s_RefCnt__d_prio___801d6580,iVar2,
                   *(undefined4 *)((int)&PTR_s_USE_8032e410 + (uVar7 >> 3 & 0x1ffffffc)),
                   (&PTR_s_TEXTURE_801e8470)[*(byte *)((int)piVar6 + 0xf)],
                   *(undefined2 *)(piVar6 + 3),piVar6[4],*piVar6);
      }
      iVar1 = iVar1 + 0x1c;
    }
    if (2 < (uint)System.m_execParam) {
      Printf__7CSystemFPce(&System,&DAT_8032f7c8);
    }
    heapWalker__Q27CMemory6CStageFiPvUl(amemCacheSet->m_stage,0xffffffff,0,0xffffffff);
LAB_8001cbc8:
    uVar7 = 0xffffffff;
  }
  goto LAB_8001c840;
}

