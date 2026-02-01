// Function: _SetSeBlockData__FPi
// Entry: 801bd584
// Size: 300 bytes

/* WARNING: Removing unreachable block (ram,0x801bd68c) */

void _SetSeBlockData__FPi(uint *param_1)

{
  uint uVar1;
  undefined *puVar2;
  
  uVar1 = *param_1 & 3;
  if ((&DAT_8032e12c)[*param_1 & 3] != 0) {
    RedDelete__FPv((&DAT_8032e12c)[uVar1]);
    (&DAT_8032e12c)[uVar1] = 0;
  }
  if (param_1[1] != 0) {
    puVar2 = (undefined *)param_1[1];
    *puVar2 = 0x53;
    puVar2[1] = 0x65;
    puVar2[2] = 0x42;
    puVar2[3] = 0x6c;
    puVar2[4] = 0x6f;
    puVar2[5] = 99;
    puVar2[6] = 0x6b;
    (&DAT_8032e12c)[uVar1] = puVar2;
  }
  return;
}

