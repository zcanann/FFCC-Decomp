// Function: pppDrawShp__FP13tagOAN3_SHAPEP12CMaterialSetUc
// Entry: 80065a94
// Size: 224 bytes

void pppDrawShp__FP13tagOAN3_SHAPEP12CMaterialSetUc
               (int param_1,CMaterialSet *materialSet,char param_3)

{
  int iVar1;
  int iVar2;
  
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
  iVar2 = param_1;
  for (iVar1 = 0; iVar1 < *(short *)(param_1 + 2); iVar1 = iVar1 + 1) {
    if (param_3 == -1) {
      pppSetBlendMode__FUc(*(undefined *)(iVar2 + 8));
    }
    GXCallDisplayList(*(undefined4 *)(iVar2 + 0xc),0x60);
    iVar2 = iVar2 + 8;
  }
  return;
}

