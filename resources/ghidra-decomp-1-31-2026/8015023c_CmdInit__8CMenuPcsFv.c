// Function: CmdInit__8CMenuPcsFv
// Entry: 8015023c
// Size: 396 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void CmdInit__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  uint32_t uVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  uint32_t uVar6;
  undefined2 *puVar7;
  int iVar8;
  
  uVar1 = Game.game.m_scriptFoodBase[0];
  memset(*(undefined4 *)&menuPcs->field_0x850,0,0x1008);
  fVar2 = FLOAT_80332a70;
  iVar5 = *(int *)&menuPcs->field_0x850 + 8;
  iVar8 = 8;
  do {
    *(float *)(iVar5 + 0x14) = fVar2;
    *(float *)(iVar5 + 0x54) = fVar2;
    *(float *)(iVar5 + 0x94) = fVar2;
    *(float *)(iVar5 + 0xd4) = fVar2;
    *(float *)(iVar5 + 0x114) = fVar2;
    *(float *)(iVar5 + 0x154) = fVar2;
    *(float *)(iVar5 + 0x194) = fVar2;
    *(float *)(iVar5 + 0x1d4) = fVar2;
    fVar4 = FLOAT_80332ad0;
    fVar3 = FLOAT_80332ab0;
    iVar5 = iVar5 + 0x200;
    iVar8 = iVar8 + -1;
  } while (iVar8 != 0);
  puVar7 = (undefined2 *)(*(int *)&menuPcs->field_0x850 + 8);
  iVar5 = 0;
  iVar8 = 8;
  uVar6 = uVar1;
  do {
    if (iVar5 < *(short *)(uVar1 + 0xbaa)) {
      *(undefined4 *)(puVar7 + 0xe) = 0x2d;
    }
    else {
      *(undefined4 *)(puVar7 + 0xe) = 0xffffffff;
    }
    puVar7[2] = 200;
    puVar7[3] = 0x20;
    *puVar7 = 0x74;
    puVar7[1] = (short)iVar5 * puVar7[3] + 0x28;
    *(float *)(puVar7 + 4) = fVar3;
    *(float *)(puVar7 + 6) = fVar4;
    if ((1 < iVar5) && (*(short *)(uVar6 + 0x204) < 0)) {
      *(float *)(puVar7 + 6) =
           *(float *)(puVar7 + 6) +
           (float)((double)CONCAT44(0x43300000,(int)(short)puVar7[3] ^ 0x80000000) - DOUBLE_80332a80
                  );
    }
    *(int *)(puVar7 + 0x12) = iVar5;
    uVar6 = uVar6 + 2;
    iVar5 = iVar5 + 1;
    *(undefined4 *)(puVar7 + 0x14) = 3;
    puVar7 = puVar7 + 0x20;
    iVar8 = iVar8 + -1;
  } while (iVar8 != 0);
  **(undefined2 **)&menuPcs->field_0x850 = 8;
  CmdInit1__8CMenuPcsFv(menuPcs);
  GetCmdItem__8CMenuPcsFv(menuPcs);
  *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x26) = 2;
  *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xb) = 1;
  return;
}

