// Function: DispAllFieldItem__9CGItemObjFi
// Entry: 80124b88
// Size: 164 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DispAllFieldItem__9CGItemObjFi(int param_1)

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
      if (param_1 == 0) {
        (gItemObj->prgObj).object.m_displayFlags =
             (gItemObj->prgObj).object.m_displayFlags | 0x400000;
      }
      else {
        (gItemObj->prgObj).object.m_displayFlags =
             (gItemObj->prgObj).object.m_displayFlags & 0xffbfffff;
      }
    }
  }
  return;
}

