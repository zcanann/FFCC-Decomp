// Function: pppRyjMegaBirthModelCon
// Entry: 80084260
// Size: 132 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppRyjMegaBirthModelCon(pppRyjMegaBirth *pppRyjMegaBirthModel,UnkC *param_2)

{
  float fVar1;
  float fVar2;
  undefined *puVar3;
  
  puVar3 = (undefined *)
           ((int)(&pppRyjMegaBirthModel->field0_0x0 + 2) + param_2->m_serializedDataOffsets[2]);
  memset(puVar3,0,0xc);
  *(undefined4 *)(puVar3 + 0xc) = 0;
  fVar1 = FLOAT_80330498;
  *(undefined4 *)(puVar3 + 0x10) = 0;
  fVar2 = FLOAT_8033049c;
  *(undefined4 *)(puVar3 + 0x14) = 0;
  *(undefined4 *)(puVar3 + 0x18) = 0;
  *(undefined2 *)(puVar3 + 0x1c) = 10000;
  *(undefined2 *)(puVar3 + 0x1e) = 0;
  *(float *)(puVar3 + 0x20) = fVar1;
  *(float *)(puVar3 + 0x24) = fVar2;
  *(float *)(puVar3 + 0x28) = fVar1;
  *(float *)(puVar3 + 0x2c) = fVar1;
  *(float *)(puVar3 + 0x30) = fVar2;
  *(float *)(puVar3 + 0x34) = fVar1;
  return;
}

