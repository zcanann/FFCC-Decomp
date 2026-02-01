// Function: SetParticleWorkCol__13CFlatRuntime2Fiif
// Entry: 8006a1e8
// Size: 16 bytes

void SetParticleWorkCol__13CFlatRuntime2Fiif
               (double param_1,CFlatRuntime2 *flatRuntime2,undefined4 param_3,undefined4 param_4)

{
  *(undefined4 *)&flatRuntime2->field_0x16e8 = param_3;
  *(undefined4 *)&flatRuntime2->field_0x16ec = param_4;
  *(float *)&flatRuntime2->field_0x16f4 = (float)param_1;
  return;
}

