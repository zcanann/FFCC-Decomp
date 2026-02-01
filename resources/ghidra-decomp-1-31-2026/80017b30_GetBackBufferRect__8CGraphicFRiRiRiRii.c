// Function: GetBackBufferRect__8CGraphicFRiRiRiRii
// Entry: 80017b30
// Size: 716 bytes

undefined *
GetBackBufferRect__8CGraphicFRiRiRiRii
          (CGraphic *graphic,uint *param_2,uint *param_3,uint *param_4,uint *param_5,
          undefined param_6)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  double dVar6;
  
  uVar2 = *param_2;
  if ((uVar2 & 1 ^ uVar2 >> 0x1f) != uVar2 >> 0x1f) {
    *param_2 = uVar2 - 1;
  }
  uVar2 = *param_3;
  if ((uVar2 & 1 ^ uVar2 >> 0x1f) != uVar2 >> 0x1f) {
    *param_3 = uVar2 - 1;
  }
  uVar2 = *param_2 + *param_4;
  uVar1 = *param_3 + *param_5;
  if ((uVar2 & 1 ^ uVar2 >> 0x1f) != uVar2 >> 0x1f) {
    uVar2 = uVar2 + 1;
    *param_4 = *param_4 + 1;
  }
  if ((uVar1 & 1 ^ uVar1 >> 0x1f) != uVar1 >> 0x1f) {
    uVar1 = uVar1 + 1;
    *param_5 = *param_5 + 1;
  }
  if ((-1 < (int)uVar2) && (-1 < (int)uVar1)) {
    uVar3 = (uint)*(ushort *)(*(int *)&graphic->field_0x71e0 + 4);
    if ((((int)*param_2 <= (int)uVar3) &&
        (((-1 < (int)uVar1 &&
          ((int)*param_3 <= (int)(uint)*(ushort *)(*(int *)&graphic->field_0x71e0 + 6))) &&
         (0 < (int)*param_4)))) && (0 < (int)*param_5)) {
      if ((int)uVar3 < (int)uVar2) {
        *param_4 = *param_4 - (uVar2 - uVar3);
        uVar2 = (uint)*(ushort *)(*(int *)&graphic->field_0x71e0 + 4);
      }
      if ((int)*param_2 < 0) {
        *param_4 = *param_4 + *param_2;
        *param_2 = 0;
      }
      if ((int)*param_3 < 0) {
        *param_5 = *param_5 + *param_3;
        *param_3 = 0;
      }
      uVar3 = (uint)*(ushort *)(*(int *)&graphic->field_0x71e0 + 6);
      if ((int)uVar3 < (int)uVar1) {
        *param_5 = *param_5 - (uVar1 - uVar3);
        uVar1 = (uint)*(ushort *)(*(int *)&graphic->field_0x71e0 + 6);
      }
      if ((uVar2 != *param_2) && (uVar1 != *param_3)) {
        uVar5 = 6;
        iVar4 = *param_4 * *param_5 * 4;
        if ((int)((*(ushort *)(*(int *)&graphic->field_0x71e0 + 4) + 0xf & 0xfff0) *
                  (uint)*(ushort *)(*(int *)&graphic->field_0x71e0 + 6) * 2 + 0x46000) < iVar4) {
          uVar5 = 4;
          iVar4 = iVar4 / 2;
        }
        GXSetTexCopySrc(*param_2 & 0xffff,*param_3 & 0xffff,*param_4 & 0xffff,*param_5 & 0xffff);
        GXSetTexCopyDst(*param_4 & 0xffff,*param_5 & 0xffff,uVar5,0);
        DCInvalidateRange(graphic->tempBuffer,iVar4);
        GXCopyTex(graphic->tempBuffer,param_6);
        GXPixModeSync();
        GXInvalidateTexAll();
        GXInitTexObj(&graphic->field_0x720c,graphic->tempBuffer,*param_4 & 0xffff,*param_5 & 0xffff,
                     uVar5,0,0,0);
        dVar6 = (double)FLOAT_8032f6c0;
        GXInitTexObjLOD(dVar6,dVar6,dVar6,&graphic->field_0x720c,1,1,0,0,0);
        return &graphic->field_0x720c;
      }
      return (undefined *)0x0;
    }
  }
  return (undefined *)0x0;
}

