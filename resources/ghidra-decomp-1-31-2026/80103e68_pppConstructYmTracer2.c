// Function: pppConstructYmTracer2
// Entry: 80103e68
// Size: 88 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConstructYmTracer2(pppYmTracer2 *pppYmTracer2,UnkC *param_2)

{
  float fVar1;
  uint8_t *puVar2;
  
  fVar1 = FLOAT_80331840;
  puVar2 = pppYmTracer2->m_serializedData + *param_2->m_serializedDataOffsets;
  *(float *)(puVar2 + 0x28) = 0.0;
  *(float *)(puVar2 + 0x24) = 0.0;
  *(float *)(puVar2 + 0x20) = 0.0;
  puVar2[0x2c] = '\0';
  puVar2[0x2d] = '\0';
  *(float *)(puVar2 + 0xc) = fVar1;
  *(float *)(puVar2 + 8) = fVar1;
  *(float *)(puVar2 + 4) = fVar1;
  *(float *)puVar2 = fVar1;
  *(float *)(puVar2 + 0x1c) = fVar1;
  *(float *)(puVar2 + 0x18) = fVar1;
  *(float *)(puVar2 + 0x14) = fVar1;
  *(float *)(puVar2 + 0x10) = fVar1;
  puVar2[0x2e] = '\0';
  puVar2[0x2f] = '\0';
  puVar2[0x30] = '\0';
  puVar2[0x31] = '\0';
  puVar2[0x32] = '\0';
  puVar2[0x33] = '\0';
  return;
}

