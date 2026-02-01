// Function: draw__8CMenuPcsFv
// Entry: 8009631c
// Size: 972 bytes

void draw__8CMenuPcsFv(CMenuPcs *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  CTexture *texture;
  double dVar3;
  undefined4 local_120;
  undefined4 local_11c;
  undefined4 local_118;
  undefined auStack_114 [4];
  Mtx MStack_110;
  Mat4x4 MStack_e0;
  Mtx MStack_a0;
  Mtx MStack_70;
  undefined4 local_30;
  uint uStack_2c;
  undefined4 local_28;
  uint uStack_24;
  undefined4 local_20;
  uint uStack_1c;
  longlong local_18;
  
  PSMTXIdentity(&MStack_a0);
  GXLoadPosMtxImm(&MStack_a0,0);
  C_MTXOrtho(FLOAT_8033080c,FLOAT_80330860,FLOAT_8033080c,FLOAT_80330864,FLOAT_8033080c,
             FLOAT_80330868,&MStack_70);
  GXSetProjection(&MStack_70,1);
  GXSetNumChans(1);
  GXSetChanCtrl(0,0,0,0,0,2,2);
  GXSetChanCtrl(2,0,0,0,0,2,2);
  puVar2 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_114,0xff,0xff,0xff,0xff);
  local_118 = *puVar2;
  GXSetChanAmbColor(4,&local_118);
  GXSetZCompLoc(0);
  GXSetCurrentMtx(0);
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  GXSetZMode(0,7,0);
  _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6,1,0,7,0);
  GXSetCullMode(0);
  GXSetNumTexGens(1);
  GXSetTexCoordGen2(0,1,4,0x1e,0,0x7d);
  GXClearVtxDesc();
  GXSetVtxDesc(9,1);
  GXSetVtxDesc(0xd,1);
  GXSetVtxAttrFmt(0,9,1,4,0);
  GXSetVtxAttrFmt(0,0xd,1,4,0);
  GXSetChanCtrl(0,0,0,0,0,2,2);
  GXSetChanCtrl(2,0,0,0,0,2,2);
  iVar1 = *(int *)&param_1->field_0x740;
  if (iVar1 == 1) {
    drawWorld__8CMenuPcsFv(param_1);
  }
  else if (iVar1 < 1) {
    if (-1 < iVar1) {
      drawBattle__8CMenuPcsFv(param_1);
      drawVillageMenu__8CMenuPcsFv(param_1);
    }
  }
  else if (iVar1 < 3) {
    drawBonus__8CMenuPcsFv(param_1);
  }
  if (((CFlat._4768_4_ & 0x10) != 0) && (System.m_scenegraphStepMode == 2)) {
    texture = *(CTexture **)&param_1->field_0x190;
    SetTexture__11CTextureManF11_GXTexMapIDP8CTexture(&TextureMan,0,texture);
    uStack_2c = texture->field94_0x64;
    uStack_24 = texture->field95_0x68;
    local_30 = 0x43300000;
    local_28 = 0x43300000;
    PSMTXScale(FLOAT_80330808 / (float)((double)CONCAT44(0x43300000,uStack_2c) - DOUBLE_80330840),
               FLOAT_80330808 / (float)((double)CONCAT44(0x43300000,uStack_24) - DOUBLE_80330840),
               FLOAT_80330808,&MStack_110);
    GXLoadTexMtxImm(&MStack_110,0x1e,1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(0,1,4,0x1e,0,0x7d);
    SetTextureTev__11CTextureManFP8CTexture(&TextureMan,texture);
    local_20 = 0x43300000;
    uStack_1c = System.m_frameCounter ^ 0x80000000;
    dVar3 = (double)sin((double)(FLOAT_80330848 *
                                (float)((double)CONCAT44(0x43300000,uStack_1c) - DOUBLE_80330838)));
    iVar1 = (int)(FLOAT_80330824 * FLOAT_8033084c * (FLOAT_80330808 + (float)dVar3));
    local_18 = (longlong)iVar1;
    __ct__6CColorFUcUcUcUc(&local_11c,0xff,0xff,0xff,iVar1);
    local_120 = local_11c;
    GXSetChanMatColor(4,&local_120);
    DrawRect__8CMenuPcsFUlfffffffff
              ((double)FLOAT_80330810,(double)FLOAT_80330814,(double)FLOAT_80330850,
               (double)FLOAT_80330854,(double)FLOAT_8033080c,(double)FLOAT_8033080c,
               (double)FLOAT_80330808,(double)FLOAT_80330808,param_1,3);
  }
  PSMTX44Copy(&CameraPcs.m_screenMatrix,&MStack_e0);
  GXSetProjection(&MStack_e0,0);
  return;
}

