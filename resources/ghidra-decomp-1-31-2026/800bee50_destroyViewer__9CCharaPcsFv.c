// Function: destroyViewer__9CCharaPcsFv
// Entry: 800bee50
// Size: 580 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void destroyViewer__9CCharaPcsFv(int param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  Destroy__6CCharaFv(&Chara);
  DestroyBumpLightAll__9CLightPcsFQ29CLightPcs6TARGET(&LightPcs,0);
  DAT_8032edc0 = 0;
  piVar1 = *(int **)(param_1 + 0x1a0);
  if (piVar1 != (int *)0x0) {
    iVar2 = piVar1[1];
    piVar1[1] = iVar2 + -1;
    if ((iVar2 + -1 == 0) && (piVar1 != (int *)0x0)) {
      (**(code **)(*piVar1 + 8))(piVar1,1);
    }
    *(undefined4 *)(param_1 + 0x1a0) = 0;
  }
  uVar4 = 0;
  iVar2 = param_1;
  do {
    piVar1 = *(int **)(iVar2 + 400);
    if (piVar1 != (int *)0x0) {
      iVar3 = piVar1[1];
      piVar1[1] = iVar3 + -1;
      if ((iVar3 + -1 == 0) && (piVar1 != (int *)0x0)) {
        (**(code **)(*piVar1 + 8))(piVar1,1);
      }
      *(undefined4 *)(iVar2 + 400) = 0;
    }
    piVar1 = *(int **)(iVar2 + 0x198);
    if (piVar1 != (int *)0x0) {
      iVar3 = piVar1[1];
      piVar1[1] = iVar3 + -1;
      if ((iVar3 + -1 == 0) && (piVar1 != (int *)0x0)) {
        (**(code **)(*piVar1 + 8))(piVar1,1);
      }
      *(undefined4 *)(iVar2 + 0x198) = 0;
    }
    piVar1 = *(int **)(iVar2 + 0x2b0);
    if (piVar1 != (int *)0x0) {
      iVar3 = piVar1[1];
      piVar1[1] = iVar3 + -1;
      if ((iVar3 + -1 == 0) && (piVar1 != (int *)0x0)) {
        (**(code **)(*piVar1 + 8))(piVar1,1);
      }
      *(undefined4 *)(iVar2 + 0x2b0) = 0;
    }
    uVar4 = uVar4 + 1;
    iVar2 = iVar2 + 4;
  } while (uVar4 < 2);
  piVar1 = *(int **)(param_1 + 0x2b8);
  if (piVar1 != (int *)0x0) {
    iVar2 = piVar1[1];
    piVar1[1] = iVar2 + -1;
    if ((iVar2 + -1 == 0) && (piVar1 != (int *)0x0)) {
      (**(code **)(*piVar1 + 8))(piVar1,1);
    }
    *(undefined4 *)(param_1 + 0x2b8) = 0;
  }
  uVar4 = 0;
  iVar2 = param_1;
  do {
    piVar1 = *(int **)(iVar2 + 0x1b0);
    if (piVar1 != (int *)0x0) {
      iVar3 = piVar1[1];
      piVar1[1] = iVar3 + -1;
      if ((iVar3 + -1 == 0) && (piVar1 != (int *)0x0)) {
        (**(code **)(*piVar1 + 8))(piVar1,1);
      }
      *(undefined4 *)(iVar2 + 0x1b0) = 0;
    }
    uVar4 = uVar4 + 1;
    iVar2 = iVar2 + 4;
  } while (uVar4 < 0x40);
  DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory,*(undefined4 *)(param_1 + 0xcc));
  DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory,*(undefined4 *)(param_1 + 0xd0));
  DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory,*(undefined4 *)(param_1 + 0xd4));
  return;
}

