// Function: calcRegist__10CGCharaObjFiiRiRiRii
// Entry: 8010f248
// Size: 884 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void calcRegist__10CGCharaObjFiiRiRiRii
               (int param_1,int param_2,int param_3,uint *param_4,uint *param_5,uint *param_6,
               int param_7)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = 0;
  if (((*(ushort *)(Game.game.unkCFlatData0[2] + param_3 * 0x48 + 0x32) & 1) != 0) || (param_7 != 0)
     ) {
    iVar2 = 1;
  }
  *param_4 = 3;
  if (param_2 == 9) {
    *param_4 = (uint)*(ushort *)(*(int *)(param_1 + 0x58) + 0x32);
  }
  else if (param_2 < 9) {
    if (param_2 == 4) {
      *param_4 = (uint)*(ushort *)(*(int *)(param_1 + 0x58) + 0x2e);
    }
    else if (param_2 < 4) {
      if (param_2 == 1) {
        *param_4 = (uint)*(ushort *)(*(int *)(param_1 + 0x58) + 0x2a);
      }
      else if (param_2 < 1) {
        if (-1 < param_2) {
          *param_4 = (uint)*(ushort *)(*(int *)(param_1 + 0x58) + 0x2c);
        }
      }
      else if (param_2 < 3) {
        *param_4 = (uint)*(ushort *)(*(int *)(param_1 + 0x58) + 0x38);
      }
      else {
        *param_4 = (uint)*(ushort *)(*(int *)(param_1 + 0x58) + 0x3c);
      }
    }
    else if (param_2 != 7) {
      if (param_2 < 7) {
        if (5 < param_2) {
          *param_4 = (uint)*(ushort *)(*(int *)(param_1 + 0x58) + 0x3a);
        }
      }
      else {
        *param_4 = (uint)*(ushort *)(*(int *)(param_1 + 0x58) + 0x30);
      }
    }
  }
  else {
    if (param_2 < 0x26) {
      if (param_2 == 0x1c) {
        *param_4 = (uint)*(ushort *)(*(int *)(param_1 + 0x58) + 0x36);
        goto LAB_8010f3f4;
      }
      if (param_2 < 0x1c) {
        if (param_2 < 0xb) {
          *param_4 = (uint)*(ushort *)(*(int *)(param_1 + 0x58) + 0x34);
        }
        goto LAB_8010f3f4;
      }
      if (param_2 < 0x24) goto LAB_8010f3f4;
    }
    else if (param_2 < 0x69) {
      if (param_2 != 100) goto LAB_8010f3f4;
    }
    else if (0x6b < param_2) goto LAB_8010f3f4;
    *param_4 = (uint)*(ushort *)(*(int *)(param_1 + 0x58) + 0x28);
  }
LAB_8010f3f4:
  if ((((*(short *)(*(int *)(param_1 + 0x58) + 0x76) == 0) &&
       (uVar1 = (**(code **)(*(int *)(param_1 + 0x48) + 0xc))(param_1), (uVar1 & 0xad) == 0xad)) &&
      ((*(ushort *)(*(int *)(*(int *)(param_1 + 0x58) + 0x24) + 0xfe) & 1) != 0)) &&
     (param_2 != 0x1c)) {
    uVar1 = 2;
    if (1 < (int)*param_4) {
      uVar1 = *param_4;
    }
    *param_4 = uVar1;
  }
  uVar1 = (**(code **)(*(int *)(param_1 + 0x48) + 0xc))(param_1);
  if ((((uVar1 & 0xad) == 0xad) &&
      ((*(ushort *)(*(int *)(*(int *)(param_1 + 0x58) + 0x24) + 0xfe) & 4) != 0)) &&
     (*(short *)(*(int *)(param_1 + 0x58) + 0x52) == 0)) {
    uVar1 = 2;
    if (1 < (int)*param_4) {
      uVar1 = *param_4;
    }
    *param_4 = uVar1;
  }
  uVar1 = (**(code **)(*(int *)(param_1 + 0x48) + 0xc))(param_1);
  if ((((uVar1 & 0xad) == 0xad) && (*(int *)(*(int *)(param_1 + 0x58) + 0x10) == 0x7f)) &&
     ((int)((uint)SoundBuffer[0x4fc] << 0x18) < 0)) {
    *param_4 = 3;
  }
  if (*(short *)(*(int *)(param_1 + 0x58) + 0x74) != 0) {
    *param_4 = 3;
  }
  Printf__7CSystemFPce(&System,&DAT_801dc8cc,*param_4);
  uVar1 = *param_4;
  if (uVar1 == 1) {
    *param_5 = (uint)-iVar2 >> 0x1f;
  }
  else if (((int)uVar1 < 1) && (-1 < (int)uVar1)) {
    *param_5 = 1;
  }
  else {
    *param_5 = 0;
  }
  *param_6 = ((int)(*param_4 ^ 3) >> 1) - ((*param_4 ^ 3) & 3) >> 0x1f;
  return;
}

