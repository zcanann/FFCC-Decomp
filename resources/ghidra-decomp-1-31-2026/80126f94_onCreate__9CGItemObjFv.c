// Function: onCreate__9CGItemObjFv
// Entry: 80126f94
// Size: 116 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onCreate__9CGItemObjFv(CGItemObj *gItemObj)

{
  undefined4 uVar1;
  
  onCreate__8CGPrgObjFv(&gItemObj->prgObj);
  (gItemObj->prgObj).m_flags = (gItemObj->prgObj).m_flags & 0x7f;
  *(undefined4 *)&gItemObj->field_0x550 = 0;
  *(undefined4 *)&gItemObj->field_0x558 = 0;
  *(undefined2 *)&gItemObj->field_0x560 = 0;
  *(undefined2 *)&gItemObj->field_0x562 = 0;
  *(undefined4 *)&gItemObj->field_0x564 = 0;
  *(undefined4 *)&gItemObj->field_0x56c = 0;
  memset(&gItemObj->field_0x570,0,0xc);
  uVar1 = GetFreeParticleSlot__13CFlatRuntime2Fv(&CFlat);
  *(undefined4 *)&gItemObj->field_0x55c = uVar1;
  return;
}

