// Function: SetMaterialCharaShadow__12CMaterialManFP9CMaterial
// Entry: 8003fb4c
// Size: 676 bytes

void SetMaterialCharaShadow__12CMaterialManFP9CMaterial(int param_1,int param_2)

{
  uint uVar1;
  
  uVar1 = *(uint *)(param_2 + 0x24);
  if (*(int *)(param_2 + 0x28) == 0) {
    if ((uVar1 & 0x20002) == 0) {
      if ((uVar1 & 1) == 0) {
        if (*(char *)(param_1 + 0x4c) != '\0') {
          GXClearVtxDesc();
          GXSetVtxDesc(9,3);
          GXSetVtxDesc(10,3);
          GXSetVtxDesc(0xb,3);
          GXSetVtxDesc(0xd,3);
          *(undefined *)(param_1 + 0x4c) = 0;
        }
        GXSetArray(10,*(undefined4 *)(param_1 + 4),6);
      }
      else {
        if (*(char *)(param_1 + 0x4c) != '\x03') {
          GXClearVtxDesc();
          GXSetVtxDesc(9,3);
          GXSetVtxDesc(10,3);
          GXSetVtxDesc(0xb,3);
          *(undefined *)(param_1 + 0x4c) = 3;
        }
        GXSetArray(10,*(undefined4 *)(param_1 + 4),6);
      }
    }
    else {
      if (*(char *)(param_1 + 0x4c) != '\x02') {
        GXClearVtxDesc();
        GXSetVtxDesc(9,3);
        GXSetVtxDesc(10,3);
        GXSetVtxDesc(0xb,3);
        GXSetVtxDesc(0xd,3);
        GXSetVtxDesc(0xe,3);
        *(undefined *)(param_1 + 0x4c) = 2;
      }
      GXSetArray(10,*(undefined4 *)(param_1 + 4),6);
    }
  }
  else if ((*(char *)(param_2 + 0xa2) == '\x03') || (*(char *)(param_2 + 0xa2) == '\x02')) {
    if ((uVar1 & 0x20002) == 0) {
      if (*(char *)(param_1 + 0x4c) != '\0') {
        GXClearVtxDesc();
        GXSetVtxDesc(9,3);
        GXSetVtxDesc(10,3);
        GXSetVtxDesc(0xb,3);
        GXSetVtxDesc(0xd,3);
        *(undefined *)(param_1 + 0x4c) = 0;
      }
      GXSetArray(10,*(undefined4 *)(param_1 + 4),6);
    }
    else {
      if (*(char *)(param_1 + 0x4c) != '\x02') {
        GXClearVtxDesc();
        GXSetVtxDesc(9,3);
        GXSetVtxDesc(10,3);
        GXSetVtxDesc(0xb,3);
        GXSetVtxDesc(0xd,3);
        GXSetVtxDesc(0xe,3);
        *(undefined *)(param_1 + 0x4c) = 2;
      }
      GXSetArray(10,*(undefined4 *)(param_1 + 4),6);
    }
  }
  else {
    if (*(char *)(param_1 + 0x4c) != '\x01') {
      GXClearVtxDesc();
      GXSetVtxDesc(9,3);
      GXSetVtxDesc(0x19,3);
      GXSetVtxDesc(0xb,3);
      GXSetVtxDesc(0xd,3);
      *(undefined *)(param_1 + 0x4c) = 1;
    }
    GXSetArray(10,*(undefined4 *)(param_1 + 4),0x12);
  }
  return;
}

