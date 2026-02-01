// Function: SetParticleWorkParam__13CFlatRuntime2FiPQ212CFlatRuntime7CObject
// Entry: 8006a1b0
// Size: 32 bytes

void SetParticleWorkParam__13CFlatRuntime2FiPQ212CFlatRuntime7CObject
               (CFlatRuntime2 *flatRuntime2,undefined4 param_2,int param_3)

{
  undefined2 uVar1;
  
  *(undefined4 *)&flatRuntime2->field_0x1710 = param_2;
  if (param_3 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = *(undefined2 *)(param_3 + 0x30);
  }
  *(undefined2 *)&flatRuntime2->field_0x1714 = uVar1;
  return;
}

