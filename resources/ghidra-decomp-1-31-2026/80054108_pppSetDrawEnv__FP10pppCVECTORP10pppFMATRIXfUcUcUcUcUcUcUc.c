// Function: pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc
// Entry: 80054108
// Size: 752 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc
               (float depth,pppCVector *pppCVector,pppFMATRIX *pppFMtx,byte lightTarget,
               byte fogIndex,byte fogParam,char cullMode,byte zEnable,byte colorUpdate,char zWrite)

{
  uint uVar1;
  undefined3 in_register_00000014;
  undefined3 in_register_00000024;
  undefined3 in_register_00000028;
  double dVar2;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  
  dVar2 = (double)depth;
  if (DOUBLE_8032fdf0 != dVar2) {
    dVar2 = (double)((float)(dVar2 * (double)FLOAT_8032fdf8) / -pppMngStPtr->m_sortDepth);
  }
  if ((double)FLOAT_8032ed8c != dVar2) {
    FLOAT_8032ed8c = (float)dVar2;
    ppvScreenMatrix.value[2][3] = (float)((double)FLOAT_8032ed60 + dVar2);
    GXSetProjection(&ppvScreenMatrix,0);
  }
  MaterialMan._72_4_ = 0xace0f;
  MaterialMan._68_4_ = 0xffffffff;
  MaterialMan._76_1_ = 0xff;
  MaterialMan._284_4_ = 0;
  MaterialMan._288_4_ = 0x1e;
  MaterialMan._292_4_ = 0;
  MaterialMan._517_1_ = 0xff;
  MaterialMan._518_1_ = 0xff;
  MaterialMan._88_4_ = 0;
  MaterialMan._92_4_ = 0;
  MaterialMan._520_1_ = 0;
  MaterialMan._296_4_ = 0;
  MaterialMan._300_4_ = 0x1e;
  MaterialMan._304_4_ = 0;
  MaterialMan._64_4_ = 0xace0f;
  if (DAT_8032ed84 != lightTarget) {
    DAT_8032ed84 = lightTarget;
    SetPart__9CLightPcsFQ29CLightPcs6TARGETPvUc
              (&LightPcs,2,pppMngStPtr,CONCAT31(in_register_00000014,lightTarget));
  }
  if ((pppFMtx != (pppFMATRIX *)0x0) && (GXLoadPosMtxImm(pppFMtx,0), lightTarget != 0)) {
    local_64 = pppFMtx->value[0][0];
    local_54 = pppFMtx->value[1][0];
    local_44 = pppFMtx->value[2][0];
    local_60 = pppFMtx->value[0][1];
    local_50 = pppFMtx->value[1][1];
    local_40 = pppFMtx->value[2][1];
    local_5c = pppFMtx->value[0][2];
    local_4c = pppFMtx->value[1][2];
    local_3c = pppFMtx->value[2][2];
    local_58 = FLOAT_8032fddc;
    local_48 = FLOAT_8032fddc;
    local_38 = FLOAT_8032fddc;
    GXLoadNrmMtxImm(&local_64,0);
  }
  local_68 = DAT_8032fdd8;
  if (lightTarget < 2) {
    if (pppCVector != (pppCVector *)0x0) {
      local_6c = *(undefined4 *)pppCVector->m_rgba;
      GXSetChanAmbColor(4,&local_6c);
    }
    local_70 = local_68;
    GXSetChanMatColor(4,&local_70);
  }
  else {
    if (pppCVector != (pppCVector *)0x0) {
      local_74 = *(undefined4 *)pppCVector->m_rgba;
      GXSetChanMatColor(4,&local_74);
    }
    local_78 = local_68;
    GXSetChanAmbColor(4,&local_78);
  }
  if ((DAT_8032ed86 != fogIndex) || (DAT_8032ed87 != fogParam)) {
    uVar1 = fogParam - 1 & 0xff;
    DAT_8032ed86 = fogIndex;
    DAT_8032ed87 = fogParam;
    SetFog__8CGraphicFii(&Graphic,(uint)fogIndex,(uint)((int)((~uVar1 | 1) - (1 - uVar1 >> 1)) < 0))
    ;
  }
  if (DAT_8032ed88 != cullMode) {
    DAT_8032ed88 = cullMode;
    GXSetCullMode();
  }
  if ((DAT_8032ed89 != zEnable) || (DAT_8032ed8b != zWrite)) {
    DAT_8032ed8b = zWrite;
    DAT_8032ed89 = zEnable;
    GXSetZMode(CONCAT31(in_register_00000024,zEnable),3,zWrite);
  }
  if (DAT_8032ed8a != colorUpdate) {
    DAT_8032ed8a = colorUpdate;
    GXSetColorUpdate(CONCAT31(in_register_00000028,colorUpdate));
  }
  return;
}

