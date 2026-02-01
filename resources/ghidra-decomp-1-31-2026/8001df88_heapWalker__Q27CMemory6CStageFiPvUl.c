// Function: heapWalker__Q27CMemory6CStageFiPvUl
// Entry: 8001df88
// Size: 848 bytes

int heapWalker__Q27CMemory6CStageFiPvUl(CStage *stage,uint param_2,undefined4 param_3,int param_4)

{
  byte bVar1;
  undefined *puVar2;
  undefined uVar3;
  undefined2 uVar4;
  undefined *puVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  
  if (stage->m_allocationMode == 2) {
    iVar14 = stage->field269_0x110;
  }
  else {
    iVar14 = *(int *)(stage->field269_0x110 + 8);
  }
  if (param_2 == 0xffffffff) {
    Printf__7CSystemFPce(&System,&DAT_8032f7e8);
    Printf__7CSystemFPce(&System,s_Stage_Name____s_801d680c,&stage->m_allocationSourceStr);
    Printf__7CSystemFPce(&System,s_No_Flag_Level_Size_Total_Address_801d6820);
    Printf__7CSystemFPce(&System,s__________________________________801d687c);
  }
  iVar13 = 0;
  iVar12 = 0;
  iVar11 = 0;
  iVar10 = 0;
  iVar9 = 0;
  if (stage->m_allocationMode == 2) {
    iVar6 = *(int *)&stage->field_0x8;
    for (iVar15 = 0; iVar15 <= *(int *)&stage->field_0x120; iVar15 = iVar15 + 1) {
      if (*(int *)&stage->field_0x120 == iVar15) {
        iVar8 = *(int *)&stage->field_0xc;
      }
      else {
        iVar8 = *(int *)(iVar14 + 4);
      }
      iVar7 = iVar8 - iVar6;
      if (iVar7 != 0) {
        if ((param_2 & 1) != 0) {
          Printf__7CSystemFPce
                    (&System,s__3d__s__5d__7d__7d__08x__08x__08_801d68d8,iVar9,&DAT_8032f7ec,0,
                     iVar6 - iVar8,iVar13,0,0,0,&DAT_8032f7d4,0);
        }
        iVar11 = iVar11 + iVar7;
        iVar13 = iVar13 + iVar7;
        iVar9 = iVar9 + 1;
      }
      if (iVar15 < *(int *)&stage->field_0x120) {
        iVar6 = *(int *)(iVar14 + 8) - *(int *)(iVar14 + 4);
        if ((param_2 & 2) != 0) {
          Printf__7CSystemFPce
                    (&System,s__3d__s__5d__7d__7d__08x__08x__08_801d68d8,iVar10,&DAT_8032f7f4,
                     *(undefined *)(iVar14 + 3),iVar6,iVar13,*(int *)(iVar14 + 4),0,0,iVar14 + 0x1a,
                     *(undefined2 *)(iVar14 + 0x18));
        }
        iVar12 = iVar12 + iVar6;
        iVar13 = iVar13 + iVar6;
        iVar6 = iVar8 + iVar6;
        iVar10 = iVar10 + 1;
      }
      iVar14 = iVar14 + 0x40;
    }
  }
  else {
    while (bVar1 = *(byte *)(iVar14 + 2), (bVar1 & 2) == 0) {
      if ((param_4 == -1) || (param_4 == *(int *)(iVar14 + 0x14))) {
        if ((((bVar1 & 4) != 0) && ((param_2 & 2) != 0)) ||
           (((bVar1 & 4) == 0 && ((param_2 & 1) != 0)))) {
          if ((bVar1 & 4) == 0) {
            uVar4 = 0;
          }
          else {
            uVar4 = *(undefined2 *)(iVar14 + 0x18);
          }
          if ((bVar1 & 4) == 0) {
            puVar5 = &DAT_8032f7d4;
          }
          else {
            puVar5 = (undefined *)(iVar14 + 0x1a);
          }
          if ((bVar1 & 4) == 0) {
            uVar3 = 0;
          }
          else {
            uVar3 = *(undefined *)(iVar14 + 3);
          }
          puVar2 = &DAT_8032f7ec;
          if ((bVar1 & 4) != 0) {
            puVar2 = &DAT_8032f7f4;
          }
          iVar6 = iVar9;
          if ((bVar1 & 4) != 0) {
            iVar6 = iVar10;
          }
          Printf__7CSystemFPce
                    (&System,s__3d__s__5d__7d__7d__08x__08x__08_801d68d8,iVar6,puVar2,uVar3,
                     *(undefined4 *)(iVar14 + 0x10),iVar13,iVar14 + 0x40,*(undefined4 *)(iVar14 + 4)
                     ,*(undefined4 *)(iVar14 + 8),puVar5,uVar4);
        }
      }
      if ((param_4 == -1) || (param_4 == *(int *)(iVar14 + 0x14))) {
        if ((*(byte *)(iVar14 + 2) & 4) == 0) {
          iVar9 = iVar9 + 1;
          iVar11 = iVar11 + *(int *)(iVar14 + 0x10);
        }
        else {
          iVar10 = iVar10 + 1;
          iVar12 = iVar12 + *(int *)(iVar14 + 0x10);
        }
      }
      iVar13 = iVar13 + (*(int *)(iVar14 + 8) - iVar14);
      iVar14 = *(int *)(iVar14 + 8);
    }
  }
  if (param_2 == 0xffffffff) {
    Printf__7CSystemFPce(&System,s___________________________________801d6904);
    Printf__7CSystemFPce(&System,s_USE____d_UNUSE____d_801d6958,iVar12,iVar11);
  }
  return iVar12;
}

