// Function: SetParticleWorkTarget__13CFlatRuntime2FR3Vec
// Entry: 8006a2d8
// Size: 36 bytes

void SetParticleWorkTarget__13CFlatRuntime2FR3Vec(CFlatRuntime2 *flatRuntime2,Vec *vec)

{
  *(float *)&flatRuntime2->field_0x1764 = vec->x;
  *(float *)&flatRuntime2->field_0x1768 = vec->y;
  *(float *)&flatRuntime2->field_0x176c = vec->z;
  *(undefined **)&flatRuntime2->field_0x16d8 = &flatRuntime2->field_0x1764;
  return;
}

