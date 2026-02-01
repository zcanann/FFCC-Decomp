// Function: Create__8CMesMenuFv
// Entry: 8009dfd0
// Size: 300 bytes

void Create__8CMesMenuFv(int *param_1)

{
  float fVar1;
  uint uVar2;
  uint uVar3;
  
  (**(code **)(*param_1 + 0x10))();
  Create__5CMenuFv(param_1);
  fVar1 = FLOAT_803308d8;
  param_1[0xf5e] = (int)FLOAT_803308d8;
  param_1[0xf5d] = (int)fVar1;
  param_1[2] = 0;
  param_1[3] = 4;
  param_1[0xf7d] = 0;
  param_1[0xf7e] = 0;
  if (param_1[6] < 4) {
    uVar2 = 0x10;
    if ((param_1[6] & 1U) != 0) {
      uVar2 = 0x270;
    }
    uVar3 = 0x18;
    param_1[0xf5b] = (int)(float)((double)CONCAT44(0x43300000,uVar2 ^ 0x80000000) - DOUBLE_80330900)
    ;
    fVar1 = FLOAT_803308d8;
    if ((param_1[6] & 2U) != 0) {
      uVar3 = 0x1b0;
    }
    param_1[0xf5c] = (int)(float)((double)CONCAT44(0x43300000,uVar3 ^ 0x80000000) - DOUBLE_80330900)
    ;
    param_1[0xf5f] = (int)fVar1;
    param_1[0xf60] = (int)fVar1;
    param_1[0xf61] = (int)fVar1;
    param_1[0xf62] = 0;
    param_1[0xf63] = 0;
    param_1[0xf6a] = 0;
    param_1[0xf6b] = 0;
    memset(param_1 + 0xf6c,0,0x20);
    memset(param_1 + 0xf74,0,0x20);
    param_1[0xf7c] = 0;
  }
  param_1[0xf66] = 0;
  param_1[0xf65] = 0;
  return;
}

