// Function: SetParticleWorkNo__13CFlatRuntime2Fi
// Entry: 8006a33c
// Size: 20 bytes

void SetParticleWorkNo__13CFlatRuntime2Fi(CFlatRuntime2 *flatRuntime2,uint param_2)

{
  *(int *)&flatRuntime2->field_0x1738 = (int)param_2 >> 8;
  *(uint *)&flatRuntime2->field_0x173c = param_2 & 0xff;
  return;
}

