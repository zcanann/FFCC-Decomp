// Function: pppCalcPartStd__FP9_pppMngSt
// Entry: 80054c58
// Size: 304 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppCalcPartStd__FP9_pppMngSt(_pppMngSt *pppMngSt)

{
  int *piVar1;
  int iVar2;
  code *pcVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  
  iVar9 = 0;
  for (iVar8 = 0; iVar8 < pppMngSt->m_numPrograms; iVar8 = iVar8 + 1) {
    piVar7 = (int *)((int)&pppMngSt->m_pppPDataVals->m_pppProgramSetDef + iVar9);
    if (((piVar7 != (int *)0x0) && (iVar6 = *piVar7, iVar6 != 0)) &&
       (DAT_8032ed80 = DAT_8032ed80 + (uint)*(ushort *)(piVar7 + 3), *(short *)(piVar7 + 3) != 0)) {
      iVar10 = 0;
      iVar11 = iVar6;
      for (iVar5 = 0; iVar5 < *(short *)(iVar6 + 0x26); iVar5 = iVar5 + 1) {
        if (*(int *)(iVar11 + 0x28) == 0) {
          printf(s_ERROR_____prog_NULL_801d8204);
        }
        else {
          pcVar3 = *(code **)(*(int *)(iVar11 + 0x28) + 8);
          if (pcVar3 != (code *)0x0) {
            uVar4 = (uint)*(ushort *)(piVar7 + 3);
            piVar1 = (int *)piVar7[1];
            do {
              if (*(char *)(piVar1 + 0x1f) == '\0') {
                iVar2 = *piVar1;
                (*pcVar3)(piVar1,*(undefined4 *)((int)piVar1 + *(int *)(iVar6 + 0x20) + iVar10),
                          iVar11 + 0x28);
              }
              else {
                iVar2 = *piVar1;
              }
              uVar4 = uVar4 - 1;
              piVar1 = (int *)iVar2;
            } while (uVar4 != 0);
          }
        }
        iVar11 = iVar11 + 0x10;
        iVar10 = iVar10 + 4;
      }
    }
    iVar9 = iVar9 + 0x10;
  }
  if (pppMngSt->m_prioTime != 0xffff) {
    pppMngSt->m_prioTime = pppMngSt->m_prioTime + 1;
  }
  return;
}

