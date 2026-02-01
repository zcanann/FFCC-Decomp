// Function: searchCombi__10CGCharaObjFiPP10CGPartyObjRi
// Entry: 8010b690
// Size: 552 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

int searchCombi__10CGCharaObjFiPP10CGPartyObjRi(int param_1,int *param_2,undefined4 *param_3)

{
  bool bVar1;
  int iVar2;
  ushort *puVar3;
  int iVar4;
  ushort *puVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  int iVar9;
  int iVar10;
  ushort *puVar11;
  int iVar12;
  
  iVar2 = -1;
  iVar4 = 0;
  *param_3 = 0;
  puVar3 = (ushort *)Game.game.unk_flat3_field_1C_0xc7d8;
LAB_8010b8a0:
  if ((int)Game.game.unk_flat3_count_0xc7d4 <= iVar4) {
    return iVar2;
  }
  iVar9 = 0;
  if ((((*puVar3 != 0) && (iVar9 = 1, puVar3[3] != 0)) && (iVar9 = 2, puVar3[6] != 0)) &&
     (iVar9 = 3, puVar3[9] != 0)) {
    iVar9 = 4;
  }
  if (param_1 < iVar9) {
    return iVar2;
  }
  iVar12 = 0;
  puVar5 = puVar3;
  piVar8 = param_2;
  for (iVar10 = iVar9; iVar10 != 0; iVar10 = iVar10 + -1) {
    iVar6 = *piVar8;
    if (*(int *)(iVar6 + 0x660) == 0) {
      iVar10 = iVar9 - iVar12;
      puVar11 = puVar5;
      if (iVar12 < iVar9) goto LAB_8010b758;
      goto LAB_8010b7e0;
    }
    if ((((iVar12 == param_1 + -1) &&
         (*(short *)(Game.game.unkCFlatData0[2] + *(uint *)(iVar6 + 0x560) * 0x48) == 0x1f8)) &&
        (*puVar5 == 0x1f8)) || (*(uint *)(iVar6 + 0x560) == (uint)*puVar5)) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    if (!bVar1) break;
    iVar7 = *(int *)(*param_2 + 0x660) - *(int *)(iVar6 + 0x660);
    if ((*param_2 == iVar6) || (((int)(uint)puVar5[1] <= iVar7 && (iVar7 <= (int)(uint)puVar5[2]))))
    {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    if (!bVar1) break;
    if (iVar12 == iVar9 + -1) {
      iVar2 = iVar4;
    }
    piVar8 = piVar8 + 1;
    iVar12 = iVar12 + 1;
    puVar5 = puVar5 + 3;
  }
  goto LAB_8010b898;
LAB_8010b758:
  do {
    if ((((iVar12 == param_1 + -1) &&
         (*(short *)(Game.game.unkCFlatData0[2] + *(uint *)(iVar6 + 0x560) * 0x48) == 0x1f8)) &&
        (*puVar11 == 0x1f8)) || (*(uint *)(iVar6 + 0x560) == (uint)*puVar11)) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    if (bVar1) {
      if ((*param_2 == iVar6) || (*(int *)(*param_2 + 0x660) <= (int)(uint)puVar5[2])) {
        bVar1 = true;
      }
      else {
        bVar1 = false;
      }
      if (bVar1) break;
    }
    iVar12 = iVar12 + 1;
    puVar11 = puVar11 + 3;
    iVar10 = iVar10 + -1;
  } while (iVar10 != 0);
LAB_8010b7e0:
  if (iVar12 < param_1) {
    *param_3 = 1;
    return iVar2;
  }
LAB_8010b898:
  iVar4 = iVar4 + 1;
  puVar3 = puVar3 + 0xd;
  goto LAB_8010b8a0;
}

