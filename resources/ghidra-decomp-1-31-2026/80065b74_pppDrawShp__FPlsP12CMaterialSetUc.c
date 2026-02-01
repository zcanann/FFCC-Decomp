// Function: pppDrawShp__FPlsP12CMaterialSetUc
// Entry: 80065b74
// Size: 248 bytes

void pppDrawShp__FPlsP12CMaterialSetUc
               (int param_1,short param_2,CMaterialSet *materialSet,char param_4)

{
  int iVar1;
  int iVar2;
  
  param_1 = param_1 + *(short *)(param_1 + param_2 * 8 + 0x10);
  MaterialMan._296_4_ = MaterialMan._284_4_;
  MaterialMan._300_4_ = MaterialMan._288_4_;
  MaterialMan._304_4_ = MaterialMan._292_4_;
  MaterialMan._64_4_ = MaterialMan._72_4_;
  SetMaterialPart__12CMaterialManFP12CMaterialSetii
            (&MaterialMan,materialSet,(uint)*(byte *)(param_1 + 10),0);
  GXClearVtxDesc();
  GXSetVtxDesc(9,1);
  GXSetVtxDesc(0xb,1);
  GXSetVtxDesc(0xd,1);
  iVar1 = param_1;
  for (iVar2 = 0; iVar2 < *(short *)(param_1 + 2); iVar2 = iVar2 + 1) {
    if (param_4 == -1) {
      pppSetBlendMode__FUc(*(undefined *)(iVar1 + 8));
    }
    GXCallDisplayList(*(undefined4 *)(iVar1 + 0xc),0x60);
    iVar1 = iVar1 + 8;
  }
  return;
}

