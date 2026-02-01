// Function: __get_file_modes
// Entry: 801b5a18
// Size: 380 bytes

undefined4 __get_file_modes(char *mode,ushort *modes)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  int in_r8;
  
  cVar1 = *mode;
  *modes = *modes & 0xfe3f | 0x40;
  uVar2 = (uint)cVar1;
  *(byte *)((int)modes + 1) = *(byte *)((int)modes + 1) & 0xcf;
  *(byte *)((int)modes + 1) = *(byte *)((int)modes + 1) & 0xf7;
  if (uVar2 == 0x72) {
    iVar3 = 0;
LAB_801b5a90:
    cVar1 = mode[1];
    *(byte *)modes = (byte)(iVar3 << 6) | *(byte *)modes & 0x3f;
    if (cVar1 == 'b') {
      cVar1 = mode[2];
      *(byte *)((int)modes + 1) = *(byte *)((int)modes + 1) & 0xf7 | 8;
      if (cVar1 == '+') {
        uVar2 = uVar2 << 8 | 0x2b;
      }
    }
    else if (((cVar1 < 'b') && (cVar1 == '+')) && (uVar2 = uVar2 << 8 | 0x2b, mode[2] == 'b')) {
      *(byte *)((int)modes + 1) = *(byte *)((int)modes + 1) & 0xf7 | 8;
    }
    if (uVar2 == 0x612b) {
      in_r8 = 7;
    }
    else if ((int)uVar2 < 0x612b) {
      if (uVar2 == 0x72) {
        in_r8 = 1;
      }
      else if ((int)uVar2 < 0x72) {
        if (uVar2 == 0x61) {
          in_r8 = 6;
        }
      }
      else if (uVar2 == 0x77) {
        in_r8 = 2;
      }
    }
    else if (uVar2 == 0x772b) {
      in_r8 = 3;
    }
    else if (((int)uVar2 < 0x772b) && (uVar2 == 0x722b)) {
      in_r8 = 3;
    }
    *(byte *)modes = (byte)(in_r8 << 3) & 0x38 | *(byte *)modes & 199;
    return 1;
  }
  if ((int)uVar2 < 0x72) {
    if (uVar2 == 0x61) {
      iVar3 = 1;
      goto LAB_801b5a90;
    }
  }
  else if (uVar2 == 0x77) {
    iVar3 = 2;
    goto LAB_801b5a90;
  }
  return 0;
}

