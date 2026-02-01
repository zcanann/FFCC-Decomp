// Function: SetParticleWorkScale__13CFlatRuntime2Ff
// Entry: 8006a1f8
// Size: 24 bytes

void SetParticleWorkScale__13CFlatRuntime2Ff(double param_1,CFlatRuntime2 *flatRuntime2)

{
  *(float *)&flatRuntime2->field_0x1760 = (float)param_1;
  *(float *)&flatRuntime2->field_0x175c = (float)param_1;
  *(float *)&flatRuntime2->field_0x1758 = (float)param_1;
  *(undefined **)&flatRuntime2->field_0x16d4 = &flatRuntime2->field_0x1758;
  return;
}

