// Function: drawMenu__11CDbgMenuPcsFPQ211CDbgMenuPcs3CDM
// Entry: 8012c8d8
// Size: 488 bytes

/* WARNING: Removing unreachable block (ram,0x8012ca98) */
/* WARNING: Removing unreachable block (ram,0x8012c8e8) */

void drawMenu__11CDbgMenuPcsFPQ211CDbgMenuPcs3CDM(int param_1,int *param_2)

{
  int iVar1;
  undefined *puVar2;
  int *piVar3;
  int *piVar4;
  double dVar5;
  
  piVar3 = param_2;
  dVar5 = DOUBLE_80331ca0;
  do {
    *(int **)(param_1 + 0x2a5c) = piVar3;
    GXSetViewport((double)(float)((double)CONCAT44(0x43300000,piVar3[0xf] ^ 0x80000000) - dVar5),
                  (double)(float)((double)CONCAT44(0x43300000,piVar3[0x10] ^ 0x80000000) - dVar5),
                  (double)FLOAT_80331ca8,(double)FLOAT_80331cac,(double)FLOAT_80331c98,
                  (double)FLOAT_80331cb0);
    iVar1 = *piVar3;
    if (iVar1 == 2) {
      drawWindow__11CDbgMenuPcsFiiiiiPc
                (param_1,(-piVar3[0xc] | piVar3[0xc]) >> 0x1f & 2,1,1,0x1e,0xe,0);
      if (piVar3[0xc] == 1) {
        puVar2 = &DAT_80331cb4;
      }
      else {
        puVar2 = &DAT_80331cbc;
        if (piVar3[0xc] == 0) {
          puVar2 = &DAT_80331cb8;
        }
      }
      drawFont__11CDbgMenuPcsFiiiPc(param_1,9,0x10,8,puVar2);
    }
    else if (iVar1 < 2) {
      if (iVar1 == 0) {
        drawWindow__11CDbgMenuPcsFiiiiiPc(param_1,piVar3[3],0,0,piVar3[6],piVar3[7],piVar3[9]);
      }
      else if (-1 < iVar1) {
        drawFont__11CDbgMenuPcsFiiiPc(param_1,piVar3[3],0,0,piVar3[9]);
      }
    }
    else if (iVar1 < 4) {
      drawWindow__11CDbgMenuPcsFiiiiiPc
                (param_1,(-piVar3[0xc] | piVar3[0xc]) >> 0x1f & 2,1,1,0x1e,0xe,0);
    }
    piVar3 = (int *)piVar3[0x12];
    piVar4 = param_2;
  } while (piVar3 != param_2);
  do {
    if (piVar4[0x14] != 0) {
      drawMenu__11CDbgMenuPcsFPQ211CDbgMenuPcs3CDM(param_1);
    }
    piVar3 = piVar4 + 0x12;
    piVar4 = (int *)*piVar3;
  } while ((int *)*piVar3 != param_2);
  return;
}

