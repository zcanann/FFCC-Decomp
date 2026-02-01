// Function: pppConstructRain
// Entry: 800ddacc
// Size: 44 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConstructRain(pppRain *pppRain,UnkC *param_2)

{
  float fVar1;
  undefined4 *puVar2;
  
  fVar1 = FLOAT_80331018;
  puVar2 = (undefined4 *)((int)(&pppRain->field0_0x0 + 2) + param_2->m_serializedDataOffsets[2]);
  *puVar2 = 0;
  puVar2[3] = fVar1;
  puVar2[2] = fVar1;
  puVar2[1] = fVar1;
  return;
}

