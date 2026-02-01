// Function: onDestroy__10CGPartyObjFv
// Entry: 80124840
// Size: 100 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onDestroy__10CGPartyObjFv(CGCharaObj *param_1)

{
  if ((int)((uint)(byte)param_1->field_0x6b8 << 0x1d | (uint)((byte)param_1->field_0x6b8 >> 3)) < 0)
  {
    addHp__10CGCharaObjFiP8CGPrgObj
              (param_1,(uint)*(ushort *)((int)(param_1->gPrgObj).object.m_scriptHandle + 0x1a),
               (CGPrgObj *)0x0);
    param_1->field_0x6b8 = param_1->field_0x6b8 & 0xfb;
  }
  onDestroy__10CGCharaObjFv(param_1);
  return;
}

