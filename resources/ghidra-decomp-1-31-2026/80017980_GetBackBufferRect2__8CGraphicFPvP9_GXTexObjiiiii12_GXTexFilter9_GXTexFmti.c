// Function: GetBackBufferRect2__8CGraphicFPvP9_GXTexObjiiiii12_GXTexFilter9_GXTexFmti
// Entry: 80017980
// Size: 432 bytes

void GetBackBufferRect2__8CGraphicFPvP9_GXTexObjiiiii12_GXTexFilter9_GXTexFmti
               (CGraphic *graphic,int param_2,int param_3,uint param_4,uint param_5,uint param_6,
               uint param_7,int param_8,undefined4 param_9,undefined4 param_10,undefined param_11)

{
  undefined4 uVar1;
  uint uVar2;
  double dVar3;
  
  uVar2 = param_5 + param_7;
  if ((((((-1 < (int)(param_4 + param_6)) && (-1 < (int)uVar2)) &&
        ((int)param_4 <= (int)(uint)*(ushort *)(*(int *)&graphic->field_0x71e0 + 4))) &&
       ((-1 < (int)uVar2 &&
        ((int)param_5 <= (int)(uint)*(ushort *)(*(int *)&graphic->field_0x71e0 + 6))))) &&
      ((0 < (int)param_6 && ((0 < (int)param_7 && (param_4 + param_6 != param_4)))))) &&
     (uVar2 != param_5)) {
    uVar1 = GXGetTexBufferSize(param_6 & 0xffff,param_7 & 0xffff,param_10,0,0);
    uVar2 = param_2 + (param_8 + 0x1fU & 0xffffffe0) + 0x1f & 0xffffffe0;
    GXSetTexCopySrc(param_4 & 0xffff,param_5 & 0xffff,param_6 & 0xffff,param_7 & 0xffff);
    GXSetTexCopyDst(param_6 & 0xffff,param_7 & 0xffff,param_10,0);
    DCInvalidateRange(uVar2,uVar1);
    GXCopyTex(uVar2,param_11);
    GXPixModeSync();
    GXInvalidateTexAll();
    switch(param_10) {
    case 0x20:
    case 0x22:
      param_10 = 0;
      break;
    case 0x23:
    case 0x27:
    case 0x28:
    case 0x29:
    case 0x2a:
      param_10 = 1;
      break;
    case 0x2b:
    case 0x2c:
      param_10 = 3;
    }
    if (param_3 != 0) {
      GXInitTexObj(param_3,uVar2,param_6 & 0xffff,param_7 & 0xffff,param_10,0,0,0);
      dVar3 = (double)FLOAT_8032f6c0;
      GXInitTexObjLOD(dVar3,dVar3,dVar3,param_3,param_9,param_9,0,0,0);
    }
  }
  return;
}

