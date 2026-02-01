// Function: Set__9CMaterialF11_GXTexMapID
// Entry: 8003da38
// Size: 472 bytes

int Set__9CMaterialF11_GXTexMapID(int param_1,int param_2)

{
  bool bVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  Mtx MStack_58;
  
  PSMTXIdentity(&MStack_58);
  bVar1 = false;
  if ((((*(short *)(param_1 + 0x18) == 2) && (FLOAT_8032faf4 == *(float *)(param_1 + 0x50))) &&
      (FLOAT_8032faf4 == *(float *)(param_1 + 0x54))) &&
     ((FLOAT_8032faf4 != *(float *)(param_1 + 100) || (FLOAT_8032faf4 != *(float *)(param_1 + 0x68))
      ))) {
    bVar1 = true;
  }
  iVar5 = param_1;
  iVar6 = param_1;
  for (iVar4 = 0; iVar4 < (int)(uint)*(ushort *)(param_1 + 0x18); iVar4 = iVar4 + 1) {
    if ((*(CTexture **)(iVar6 + 0x3c) != (CTexture *)0x0) &&
       ((*(char *)(param_1 + 0xa7) == '\0' || (iVar4 < 1)))) {
      SetTexture__11CTextureManF11_GXTexMapIDP8CTexture
                (&TextureMan,param_2,*(CTexture **)(iVar6 + 0x3c));
      param_2 = param_2 + 1;
      if ((FLOAT_8032faf4 != *(float *)(iVar5 + 0x50)) ||
         ((FLOAT_8032faf4 != *(float *)(iVar5 + 0x54) || (bVar1)))) {
        if (iVar4 == 0) {
          MaterialMan._72_4_ = MaterialMan._72_4_ | 0x20;
          MaterialMan._324_4_ = MaterialMan._288_4_;
          MaterialMan._328_4_ = MaterialMan._292_4_;
          MStack_58.value[0][3] = *(float *)(iVar5 + 0x50);
          MStack_58.value[1][3] = *(float *)(iVar5 + 0x54);
          GXLoadTexMtxImm(&MStack_58,MaterialMan._288_4_,1);
          uVar3 = MaterialMan._292_4_;
          uVar2 = MaterialMan._288_4_;
          MaterialMan._288_4_ = MaterialMan._288_4_ + 3;
          MaterialMan._292_4_ = MaterialMan._292_4_ + 1;
          GXSetTexCoordGen2(uVar3,1,4,uVar2,0,0x7d);
        }
        else {
          MaterialMan._72_4_ = MaterialMan._72_4_ | 0x40;
          MaterialMan._336_4_ = MaterialMan._288_4_;
          MaterialMan._340_4_ = MaterialMan._292_4_;
          MStack_58.value[0][3] = *(float *)(iVar5 + 0x50);
          MStack_58.value[1][3] = *(float *)(iVar5 + 0x54);
          GXLoadTexMtxImm(&MStack_58,MaterialMan._288_4_,1);
          uVar3 = MaterialMan._292_4_;
          uVar2 = MaterialMan._288_4_;
          MaterialMan._288_4_ = MaterialMan._288_4_ + 3;
          MaterialMan._292_4_ = MaterialMan._292_4_ + 1;
          GXSetTexCoordGen2(uVar3,1,5,uVar2,0,0x7d);
        }
      }
    }
    iVar6 = iVar6 + 4;
    iVar5 = iVar5 + 0x14;
  }
  return param_2;
}

