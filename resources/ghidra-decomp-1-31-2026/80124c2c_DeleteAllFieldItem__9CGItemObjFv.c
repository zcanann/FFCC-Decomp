// Function: DeleteAllFieldItem__9CGItemObjFv
// Entry: 80124c2c
// Size: 140 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DeleteAllFieldItem__9CGItemObjFv(void)

{
  byte bVar1;
  CGItemObj *gItemObj;
  
  for (gItemObj = (CGItemObj *)FindGItemObjFirst__13CFlatRuntime2Fv((CFlatRuntime2 *)&CFlat);
      gItemObj != (CGItemObj *)0x0;
      gItemObj = (CGItemObj *)
                 FindGItemObjNext__13CFlatRuntime2FP9CGItemObj((CFlatRuntime2 *)&CFlat,gItemObj)) {
    if ((*(int *)&gItemObj->field_0x550 == 0) &&
       (bVar1 = (gItemObj->prgObj).object.m_stateFlags0,
       (int)((uint)bVar1 << 0x1c | (uint)(bVar1 >> 4)) < 0)) {
      (gItemObj->prgObj).object.base_object.object.m_flags =
           (gItemObj->prgObj).object.base_object.object.m_flags & 0x7f | 0x80;
    }
  }
  return;
}

