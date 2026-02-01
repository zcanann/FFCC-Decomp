// Function: Quit__7CMemoryFv
// Entry: 8001f198
// Size: 1832 bytes

void Quit__7CMemoryFv(int param_1)

{
  int iVar1;
  int iVar2;
  bool bVar4;
  int iVar3;
  CStage *pCVar5;
  CStage *pCVar6;
  int iVar7;
  CStage *stage;
  
  pCVar6 = *(CStage **)(param_1 + 0x7790);
  iVar7 = param_1 + pCVar6->m_allocationMode * 0x27d8 + 4;
  if (pCVar6->m_allocationMode == 2) {
    iVar1 = pCVar6->field269_0x110;
    if (iVar1 != 0) {
      if ((iVar1 != 0) && (iVar1 != 0x10)) {
        if ((*(short *)(iVar1 + -0x50) != 0x4b41) || (*(short *)(iVar1 + -0x12) != 0x4d49)) {
          Printf__7CSystemFPce
                    (&System,&DAT_801d6648,iVar1 + -0x10,iVar1 + -0x36,
                     *(undefined2 *)(iVar1 + -0x38));
        }
        *(byte *)(iVar1 + -0x4e) = *(byte *)(iVar1 + -0x4e) & 0xfb;
        if ((*(byte *)(*(int *)(iVar1 + -0x48) + 2) & 4) == 0) {
          *(int *)(iVar1 + -0x40) =
               *(int *)(*(int *)(iVar1 + -0x48) + 0x10) + *(int *)(iVar1 + -0x40) + 0x40;
          *(int *)(*(int *)(*(int *)(iVar1 + -0x48) + 8) + 4) = iVar1 + -0x50;
          *(undefined4 *)(iVar1 + -0x48) = *(undefined4 *)(*(int *)(iVar1 + -0x48) + 8);
        }
        iVar2 = *(int *)(iVar1 + -0x4c);
        if ((*(byte *)(iVar2 + 2) & 4) == 0) {
          *(int *)(iVar2 + 0x10) = *(int *)(iVar1 + -0x40) + *(int *)(iVar2 + 0x10) + 0x40;
          *(undefined4 *)(*(int *)(iVar1 + -0x4c) + 8) = *(undefined4 *)(iVar1 + -0x48);
          *(undefined4 *)(*(int *)(iVar1 + -0x48) + 4) = *(undefined4 *)(iVar1 + -0x4c);
        }
        *(int *)(*(int *)(iVar1 + -0x44) + 0x124) = *(int *)(*(int *)(iVar1 + -0x44) + 0x124) + -1;
      }
      pCVar6->field269_0x110 = 0;
    }
  }
  else {
    bVar4 = false;
    for (iVar1 = *(int *)(pCVar6->field269_0x110 + 8); (*(byte *)(iVar1 + 2) & 2) == 0;
        iVar1 = *(int *)(iVar1 + 8)) {
      if ((*(byte *)(iVar1 + 2) & 4) != 0) {
        bVar4 = true;
      }
    }
    if (bVar4) {
      Printf__7CSystemFPce(&System,&DAT_801d6a7c,&pCVar6->m_allocationSourceStr);
      heapWalker__Q27CMemory6CStageFiPvUl(pCVar6,0xffffffff,0,0xffffffff);
    }
  }
  pCVar5 = (CStage *)(param_1 + 4);
  *(undefined4 *)(*(int *)pCVar6 + 4) = *(undefined4 *)&pCVar6->field_0x4;
  **(undefined4 **)&pCVar6->field_0x4 = *(undefined4 *)pCVar6;
  *(undefined4 *)&pCVar6->field_0x4 = *(undefined4 *)(iVar7 + 0x130);
  *(CStage **)(iVar7 + 0x130) = pCVar6;
  for (iVar7 = 0; iVar7 < 3; iVar7 = iVar7 + 1) {
    if ((iVar7 != 1) || (iVar1 = OSGetConsoleSimulatedMemSize(), iVar1 == 0x3000000)) {
      pCVar6 = *(CStage **)&pCVar5->field_0x4;
      while (stage = pCVar6, stage != pCVar5) {
        pCVar6 = *(CStage **)&stage->field_0x4;
        if (iVar7 == 0) {
          if (stage != *(CStage **)(param_1 + 0x778c)) {
            Printf__7CSystemFPce(&System,&DAT_801d6c58,&stage->m_allocationSourceStr);
            iVar1 = param_1 + stage->m_allocationMode * 0x27d8 + 4;
            if (stage->m_allocationMode == 2) {
              iVar2 = stage->field269_0x110;
              if (iVar2 != 0) {
                if ((iVar2 != 0) && (iVar2 != 0x10)) {
                  if ((*(short *)(iVar2 + -0x50) != 0x4b41) || (*(short *)(iVar2 + -0x12) != 0x4d49)
                     ) {
                    Printf__7CSystemFPce
                              (&System,&DAT_801d6648,iVar2 + -0x10,iVar2 + -0x36,
                               *(undefined2 *)(iVar2 + -0x38));
                  }
                  *(byte *)(iVar2 + -0x4e) = *(byte *)(iVar2 + -0x4e) & 0xfb;
                  if ((*(byte *)(*(int *)(iVar2 + -0x48) + 2) & 4) == 0) {
                    *(int *)(iVar2 + -0x40) =
                         *(int *)(*(int *)(iVar2 + -0x48) + 0x10) + *(int *)(iVar2 + -0x40) + 0x40;
                    *(int *)(*(int *)(*(int *)(iVar2 + -0x48) + 8) + 4) = iVar2 + -0x50;
                    *(undefined4 *)(iVar2 + -0x48) = *(undefined4 *)(*(int *)(iVar2 + -0x48) + 8);
                  }
                  iVar3 = *(int *)(iVar2 + -0x4c);
                  if ((*(byte *)(iVar3 + 2) & 4) == 0) {
                    *(int *)(iVar3 + 0x10) = *(int *)(iVar2 + -0x40) + *(int *)(iVar3 + 0x10) + 0x40
                    ;
                    *(undefined4 *)(*(int *)(iVar2 + -0x4c) + 8) = *(undefined4 *)(iVar2 + -0x48);
                    *(undefined4 *)(*(int *)(iVar2 + -0x48) + 4) = *(undefined4 *)(iVar2 + -0x4c);
                  }
                  *(int *)(*(int *)(iVar2 + -0x44) + 0x124) =
                       *(int *)(*(int *)(iVar2 + -0x44) + 0x124) + -1;
                }
                stage->field269_0x110 = 0;
              }
            }
            else {
              bVar4 = false;
              for (iVar2 = *(int *)(stage->field269_0x110 + 8); (*(byte *)(iVar2 + 2) & 2) == 0;
                  iVar2 = *(int *)(iVar2 + 8)) {
                if ((*(byte *)(iVar2 + 2) & 4) != 0) {
                  bVar4 = true;
                }
              }
              if (bVar4) {
                Printf__7CSystemFPce(&System,&DAT_801d6a7c,&stage->m_allocationSourceStr);
                heapWalker__Q27CMemory6CStageFiPvUl(stage,0xffffffff,0,0xffffffff);
              }
            }
            *(undefined4 *)(*(int *)stage + 4) = *(undefined4 *)&stage->field_0x4;
            **(undefined4 **)&stage->field_0x4 = *(undefined4 *)stage;
            *(undefined4 *)&stage->field_0x4 = *(undefined4 *)(iVar1 + 0x130);
            *(CStage **)(iVar1 + 0x130) = stage;
          }
        }
        else {
          Printf__7CSystemFPce(&System,&DAT_801d6c58,&stage->m_allocationSourceStr);
          iVar1 = param_1 + stage->m_allocationMode * 0x27d8 + 4;
          if (stage->m_allocationMode == 2) {
            iVar2 = stage->field269_0x110;
            if (iVar2 != 0) {
              if ((iVar2 != 0) && (iVar2 != 0x10)) {
                if ((*(short *)(iVar2 + -0x50) != 0x4b41) || (*(short *)(iVar2 + -0x12) != 0x4d49))
                {
                  Printf__7CSystemFPce
                            (&System,&DAT_801d6648,iVar2 + -0x10,iVar2 + -0x36,
                             *(undefined2 *)(iVar2 + -0x38));
                }
                *(byte *)(iVar2 + -0x4e) = *(byte *)(iVar2 + -0x4e) & 0xfb;
                if ((*(byte *)(*(int *)(iVar2 + -0x48) + 2) & 4) == 0) {
                  *(int *)(iVar2 + -0x40) =
                       *(int *)(*(int *)(iVar2 + -0x48) + 0x10) + *(int *)(iVar2 + -0x40) + 0x40;
                  *(int *)(*(int *)(*(int *)(iVar2 + -0x48) + 8) + 4) = iVar2 + -0x50;
                  *(undefined4 *)(iVar2 + -0x48) = *(undefined4 *)(*(int *)(iVar2 + -0x48) + 8);
                }
                iVar3 = *(int *)(iVar2 + -0x4c);
                if ((*(byte *)(iVar3 + 2) & 4) == 0) {
                  *(int *)(iVar3 + 0x10) = *(int *)(iVar2 + -0x40) + *(int *)(iVar3 + 0x10) + 0x40;
                  *(undefined4 *)(*(int *)(iVar2 + -0x4c) + 8) = *(undefined4 *)(iVar2 + -0x48);
                  *(undefined4 *)(*(int *)(iVar2 + -0x48) + 4) = *(undefined4 *)(iVar2 + -0x4c);
                }
                *(int *)(*(int *)(iVar2 + -0x44) + 0x124) =
                     *(int *)(*(int *)(iVar2 + -0x44) + 0x124) + -1;
              }
              stage->field269_0x110 = 0;
            }
          }
          else {
            bVar4 = false;
            for (iVar2 = *(int *)(stage->field269_0x110 + 8); (*(byte *)(iVar2 + 2) & 2) == 0;
                iVar2 = *(int *)(iVar2 + 8)) {
              if ((*(byte *)(iVar2 + 2) & 4) != 0) {
                bVar4 = true;
              }
            }
            if (bVar4) {
              Printf__7CSystemFPce(&System,&DAT_801d6a7c,&stage->m_allocationSourceStr);
              heapWalker__Q27CMemory6CStageFiPvUl(stage,0xffffffff,0,0xffffffff);
            }
          }
          *(undefined4 *)(*(int *)stage + 4) = *(undefined4 *)&stage->field_0x4;
          **(undefined4 **)&stage->field_0x4 = *(undefined4 *)stage;
          *(undefined4 *)&stage->field_0x4 = *(undefined4 *)(iVar1 + 0x130);
          *(CStage **)(iVar1 + 0x130) = stage;
        }
      }
    }
    pCVar5 = pCVar5 + 0x22;
  }
  pCVar6 = *(CStage **)(param_1 + 0x778c);
  param_1 = param_1 + pCVar6->m_allocationMode * 0x27d8 + 4;
  if (pCVar6->m_allocationMode == 2) {
    iVar7 = pCVar6->field269_0x110;
    if (iVar7 != 0) {
      if ((iVar7 != 0) && (iVar7 != 0x10)) {
        if ((*(short *)(iVar7 + -0x50) != 0x4b41) || (*(short *)(iVar7 + -0x12) != 0x4d49)) {
          Printf__7CSystemFPce
                    (&System,&DAT_801d6648,iVar7 + -0x10,iVar7 + -0x36,
                     *(undefined2 *)(iVar7 + -0x38));
        }
        *(byte *)(iVar7 + -0x4e) = *(byte *)(iVar7 + -0x4e) & 0xfb;
        if ((*(byte *)(*(int *)(iVar7 + -0x48) + 2) & 4) == 0) {
          *(int *)(iVar7 + -0x40) =
               *(int *)(*(int *)(iVar7 + -0x48) + 0x10) + *(int *)(iVar7 + -0x40) + 0x40;
          *(int *)(*(int *)(*(int *)(iVar7 + -0x48) + 8) + 4) = iVar7 + -0x50;
          *(undefined4 *)(iVar7 + -0x48) = *(undefined4 *)(*(int *)(iVar7 + -0x48) + 8);
        }
        iVar1 = *(int *)(iVar7 + -0x4c);
        if ((*(byte *)(iVar1 + 2) & 4) == 0) {
          *(int *)(iVar1 + 0x10) = *(int *)(iVar7 + -0x40) + *(int *)(iVar1 + 0x10) + 0x40;
          *(undefined4 *)(*(int *)(iVar7 + -0x4c) + 8) = *(undefined4 *)(iVar7 + -0x48);
          *(undefined4 *)(*(int *)(iVar7 + -0x48) + 4) = *(undefined4 *)(iVar7 + -0x4c);
        }
        *(int *)(*(int *)(iVar7 + -0x44) + 0x124) = *(int *)(*(int *)(iVar7 + -0x44) + 0x124) + -1;
      }
      pCVar6->field269_0x110 = 0;
    }
  }
  else {
    bVar4 = false;
    for (iVar7 = *(int *)(pCVar6->field269_0x110 + 8); (*(byte *)(iVar7 + 2) & 2) == 0;
        iVar7 = *(int *)(iVar7 + 8)) {
      if ((*(byte *)(iVar7 + 2) & 4) != 0) {
        bVar4 = true;
      }
    }
    if (bVar4) {
      Printf__7CSystemFPce(&System,&DAT_801d6a7c,&pCVar6->m_allocationSourceStr);
      heapWalker__Q27CMemory6CStageFiPvUl(pCVar6,0xffffffff,0,0xffffffff);
    }
  }
  *(undefined4 *)(*(int *)pCVar6 + 4) = *(undefined4 *)&pCVar6->field_0x4;
  **(undefined4 **)&pCVar6->field_0x4 = *(undefined4 *)pCVar6;
  *(undefined4 *)&pCVar6->field_0x4 = *(undefined4 *)(param_1 + 0x130);
  *(CStage **)(param_1 + 0x130) = pCVar6;
  return;
}

