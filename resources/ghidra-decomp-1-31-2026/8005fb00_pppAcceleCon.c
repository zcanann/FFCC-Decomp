// Function: pppAcceleCon
// Entry: 8005fb00
// Size: 36 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppAcceleCon(pppAccele *pppAccele,UnkC *param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  uVar1 = DAT_8032fec8;
  puVar2 = (undefined4 *)((int)(&pppAccele->pppPObject + 2) + param_2->m_serializedDataOffsets[1]);
  puVar2[2] = DAT_8032fec8;
  puVar2[1] = uVar1;
  *puVar2 = uVar1;
  return;
}

