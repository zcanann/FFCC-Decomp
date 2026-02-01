// Function: InitCharaInfo__8CMenuPcsFv
// Entry: 80101444
// Size: 532 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void InitCharaInfo__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  short sVar9;
  int iVar10;
  short sVar11;
  int iVar12;
  short sVar13;
  int iVar14;
  
  fVar2 = FLOAT_803314a4;
  fVar1 = FLOAT_803313dc;
  iVar10 = 0;
  iVar12 = 0x20;
  sVar11 = 0x66;
  do {
    iVar4 = iVar12 * 0x50;
    sVar13 = 0x68;
    iVar14 = 2;
    do {
      sVar9 = sVar11;
      if (iVar10 != 0) {
        sVar9 = sVar11 + 8;
      }
      *(short *)(*(int *)&menuPcs->field_0x814 + iVar4 + 8) = sVar13 + -0xa0;
      *(short *)(*(int *)&menuPcs->field_0x814 + iVar4 + 10) = sVar9 + -0x70;
      *(undefined2 *)(*(int *)&menuPcs->field_0x814 + iVar4 + 0xc) = 0x140;
      *(undefined2 *)(*(int *)&menuPcs->field_0x814 + iVar4 + 0xe) = 0xe0;
      *(float *)(*(int *)&menuPcs->field_0x814 + iVar4 + 0x10) = fVar1;
      *(float *)(*(int *)&menuPcs->field_0x814 + iVar4 + 0x14) = fVar1;
      *(float *)(*(int *)&menuPcs->field_0x814 + iVar4 + 0x18) = fVar2;
      sVar9 = sVar11;
      if (iVar10 != 0) {
        sVar9 = sVar11 + 8;
      }
      *(short *)(*(int *)&menuPcs->field_0x814 + iVar4 + 0x58) = sVar13 + -0x10;
      iVar8 = iVar4 + 0x5c;
      iVar7 = iVar4 + 0x5e;
      iVar6 = iVar4 + 0x60;
      *(short *)(*(int *)&menuPcs->field_0x814 + iVar4 + 0x5a) = sVar9 + -0x70;
      iVar5 = iVar4 + 100;
      iVar3 = iVar4 + 0x68;
      iVar4 = iVar4 + 0xa0;
      sVar13 = sVar13 + 0x120;
      *(undefined2 *)(*(int *)&menuPcs->field_0x814 + iVar8) = 0x140;
      *(undefined2 *)(*(int *)&menuPcs->field_0x814 + iVar7) = 0xe0;
      *(float *)(*(int *)&menuPcs->field_0x814 + iVar6) = fVar1;
      *(float *)(*(int *)&menuPcs->field_0x814 + iVar5) = fVar1;
      *(float *)(*(int *)&menuPcs->field_0x814 + iVar3) = fVar2;
      iVar14 = iVar14 + -1;
    } while (iVar14 != 0);
    iVar10 = iVar10 + 1;
    sVar11 = sVar11 + 0xb8;
    iVar12 = iVar12 + 4;
  } while (iVar10 < 2);
  iVar10 = -0x7fde1140;
  iVar12 = 0;
  iVar4 = 4;
  do {
    iVar14 = *(int *)&menuPcs->field_0x824 + iVar12;
    if (*(int *)(iVar10 + 0x1794) == 0) {
      *(undefined4 *)(iVar14 + 8) = 0xffffffff;
    }
    else {
      iVar3 = (uint)*(ushort *)(iVar10 + 0x17d0) * 200;
      iVar5 = iVar3 + 100;
      if (*(short *)(iVar10 + 0x17d2) != 0) {
        iVar5 = iVar3 + 200;
      }
      *(uint *)(iVar14 + 8) = iVar5 + (uint)*(ushort *)(iVar10 + 0x17d4);
    }
    iVar14 = *(int *)&menuPcs->field_0x824 + iVar12 + 0x34;
    if (*(int *)(iVar10 + 0x23c4) == 0) {
      *(undefined4 *)(iVar14 + 8) = 0xffffffff;
    }
    else {
      iVar3 = (uint)*(ushort *)(iVar10 + 0x2400) * 200;
      iVar5 = iVar3 + 100;
      if (*(short *)(iVar10 + 0x2402) != 0) {
        iVar5 = iVar3 + 200;
      }
      *(uint *)(iVar14 + 8) = iVar5 + (uint)*(ushort *)(iVar10 + 0x2404);
    }
    iVar10 = iVar10 + 0x1860;
    iVar12 = iVar12 + 0x68;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  return;
}

