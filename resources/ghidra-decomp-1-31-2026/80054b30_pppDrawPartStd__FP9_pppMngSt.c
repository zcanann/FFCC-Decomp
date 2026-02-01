// Function: pppDrawPartStd__FP9_pppMngSt
// Entry: 80054b30
// Size: 296 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppDrawPartStd__FP9_pppMngSt(_pppMngSt *pppMngSt)

{
  code *pcVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  int iVar9;
  int iVar10;
  
  iVar9 = 0;
  iVar10 = 0;
  while( true ) {
    if (pppMngSt->m_numPrograms <= iVar9) break;
    piVar8 = (int *)((int)&pppMngSt->m_pppPDataVals->m_pppProgramSetDef + iVar10);
    if (piVar8 != (int *)0x0) {
      iVar7 = *piVar8;
      if (((iVar7 != 0) && (-1 < (int)((uint)*(byte *)(iVar7 + 0xc) << 0x18))) &&
         (*(short *)(piVar8 + 3) != 0)) {
        iVar5 = 0;
        iVar6 = iVar7;
        for (iVar4 = 0; iVar4 < *(short *)(iVar7 + 0x26); iVar4 = iVar4 + 1) {
          if (*(int *)(iVar6 + 0x28) == 0) {
            printf(s_ERROR_____prog_NULL_801d8204);
          }
          else {
            pcVar1 = *(code **)(*(int *)(iVar6 + 0x28) + 0xc);
            piVar2 = (int *)piVar8[1];
            if (pcVar1 != (code *)0x0) {
              uVar3 = (uint)*(ushort *)(piVar8 + 3);
              do {
                if (*(char *)(piVar2 + 0x1f) == '\0') {
                  (*pcVar1)(piVar2,*(undefined4 *)((int)piVar2 + *(int *)(iVar7 + 0x20) + iVar5),
                            iVar6 + 0x28);
                }
                uVar3 = uVar3 - 1;
                piVar2 = (int *)*piVar2;
              } while (uVar3 != 0);
              SetDrawDoneDebugDataPartControl__8CGraphicFi(&Graphic,0x7fff);
            }
          }
          iVar6 = iVar6 + 0x10;
          iVar5 = iVar5 + 4;
        }
      }
    }
    iVar10 = iVar10 + 0x10;
    iVar9 = iVar9 + 1;
  }
  return;
}

