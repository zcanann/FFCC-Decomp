// Function: pppConstructChangeTex
// Entry: 8013f744
// Size: 64 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConstructChangeTex(pppChangeTex *pppChangeTex,UnkC *param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  uVar1 = DAT_80332040;
  puVar2 = (undefined4 *)
           ((int)(&pppChangeTex->field0_0x0 + 2) + param_2->m_serializedDataOffsets[2]);
  *puVar2 = DAT_80332040;
  puVar2[2] = uVar1;
  puVar2[1] = uVar1;
  puVar2[6] = 0;
  puVar2[9] = pppMngStPtr;
  puVar2[7] = 0;
  puVar2[3] = 0;
  puVar2[4] = 0;
  return;
}

