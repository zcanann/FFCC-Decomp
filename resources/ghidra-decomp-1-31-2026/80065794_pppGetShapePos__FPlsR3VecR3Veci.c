// Function: pppGetShapePos__FPlsR3VecR3Veci
// Entry: 80065794
// Size: 120 bytes

void pppGetShapePos__FPlsR3VecR3Veci
               (int param_1,short param_2,Vec *param_3,Vec *param_4,int param_5)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + *(short *)(param_1 + param_2 * 8 + 0x10) + 0xc + param_5 * 8);
  memcpy(param_3,iVar1 + 3,0xc);
  memcpy(param_4,iVar1 + 0x2b,0xc);
  return;
}

