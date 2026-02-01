// Function: SetParticleWorkPos__13CFlatRuntime2FR3Vecf
// Entry: 8006a2fc
// Size: 64 bytes

void SetParticleWorkPos__13CFlatRuntime2FR3Vecf
               (double param_1,CFlatRuntime2 *flatRuntime2,Vec *param_3)

{
  float fVar1;
  double dVar2;
  
  fVar1 = FLOAT_8033013c;
  dVar2 = (double)FLOAT_80330138;
  *(float *)&flatRuntime2->field_0x1740 = param_3->x;
  *(float *)&flatRuntime2->field_0x1744 = param_3->y;
  *(float *)&flatRuntime2->field_0x1748 = param_3->z;
  *(float *)&flatRuntime2->field_0x1750 = (float)(dVar2 * param_1) / fVar1;
  *(undefined **)&flatRuntime2->field_0x16cc = &flatRuntime2->field_0x1740;
  *(undefined **)&flatRuntime2->field_0x16d0 = &flatRuntime2->field_0x174c;
  return;
}

