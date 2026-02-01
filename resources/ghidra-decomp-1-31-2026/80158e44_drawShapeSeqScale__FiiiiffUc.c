// Function: drawShapeSeqScale__FiiiiffUc
// Entry: 80158e44
// Size: 720 bytes

/* WARNING: Removing unreachable block (ram,0x801590f8) */
/* WARNING: Removing unreachable block (ram,0x801590f0) */
/* WARNING: Removing unreachable block (ram,0x80158e5c) */
/* WARNING: Removing unreachable block (ram,0x80158e54) */

void drawShapeSeqScale__FiiiiffUc
               (double param_1,double param_2,int param_3,int param_4,uint param_5,uint param_6,
               undefined param_7)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  Mtx local_bc;
  Mtx MStack_8c;
  undefined4 local_48;
  uint uStack_44;
  undefined4 local_40;
  uint uStack_3c;
  
  PSMTXIdentity(&local_bc);
  uStack_44 = param_5 ^ 0x80000000;
  uStack_3c = param_6 ^ 0x80000000;
  local_48 = 0x43300000;
  local_bc.value[0][3] = (float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_80332d20);
  local_40 = 0x43300000;
  local_bc.value[0][0] = (float)param_1;
  local_bc.value[1][3] = (float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80332d20);
  local_bc.value[1][1] = (float)-param_2;
  local_bc.value[2][2] = FLOAT_80332d78;
  GXLoadPosMtxImm(&local_bc,0);
  GXSetCurrentMtx(0);
  C_MTXOrtho(FLOAT_80332d9c,FLOAT_80332dec,FLOAT_80332d9c,FLOAT_80332df0,FLOAT_80332d9c,
             FLOAT_80332d28,&MStack_8c);
  MStack_8c.value[2][3] = MStack_8c.value[2][3] + FLOAT_80332d9c;
  GXSetProjection(&MStack_8c,1);
  iVar1 = **(int **)(*(int *)pppEnvStPtr->m_particleColors[0].m_colorRGBA + param_3 * 4);
  local_c8 = CONCAT31((int3)((uint)DAT_80332d00 >> 8),param_7);
  iVar1 = iVar1 + *(short *)(iVar1 + param_4 * 8 + 0x10);
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
  local_c4 = DAT_80332cfc;
  GXSetChanAmbColor(4,&local_c4);
  local_c0 = local_c8;
  GXSetChanMatColor(4,&local_c0);
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,5);
  _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(7,0,0,7,0xff);
  GXSetZCompLoc(1);
  GXSetNumChans(1);
  GXSetChanCtrl(0,0,0,0,0,2,2);
  GXSetChanCtrl(2,0,0,0,0,2,2);
  MaterialMan._296_4_ = MaterialMan._284_4_;
  MaterialMan._300_4_ = MaterialMan._288_4_;
  MaterialMan._304_4_ = MaterialMan._292_4_;
  MaterialMan._64_4_ = MaterialMan._72_4_;
  SetMaterialMenu__12CMaterialManFP12CMaterialSetii
            (&MaterialMan,pppEnvStPtr->m_materialSetPtr,(uint)*(byte *)(iVar1 + 10),0);
  GXClearVtxDesc();
  GXSetVtxDesc(9,1);
  GXSetVtxDesc(0xb,1);
  GXSetVtxDesc(0xd,1);
  iVar2 = iVar1;
  for (iVar3 = 0; iVar3 < *(short *)(iVar1 + 2); iVar3 = iVar3 + 1) {
    GXCallDisplayList(*(undefined4 *)(iVar2 + 0xc),0x60);
    iVar2 = iVar2 + 8;
  }
  return;
}

