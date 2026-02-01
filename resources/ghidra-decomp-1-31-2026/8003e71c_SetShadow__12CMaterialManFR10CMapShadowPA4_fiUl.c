// Function: SetShadow__12CMaterialManFR10CMapShadowPA4_fiUl
// Entry: 8003e71c
// Size: 488 bytes

void SetShadow__12CMaterialManFR10CMapShadowPA4_fiUl
               (int param_1,int param_2,Mtx *param_3,undefined param_4,uint param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  Mtx MStack_48;
  
  iVar1 = __vc__22CPtrArray<P9CMaterial>FUl(MapMng._136148_4_ + 8,*(undefined2 *)(param_2 + 4));
  param_5 = param_5 & *(uint *)(iVar1 + 0x24) & 0x8000;
  if (param_5 == 0) {
    if (4 < *(int *)(param_1 + 0x5c)) {
      return;
    }
  }
  else if (3 < *(int *)(param_1 + 0x5c)) {
    return;
  }
  if ((((*(uint *)(param_1 + 0x11c) & 0xff) < 8) && ((*(uint *)(param_1 + 0x120) & 0xff) < 0x3c)) &&
     ((*(uint *)(param_1 + 0x124) & 0xff) < 8)) {
    *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) | 0x10;
    *(undefined *)(param_1 + *(int *)(param_1 + 0x58) + 0x4d) = *(undefined *)(param_2 + 8);
    *(undefined *)(param_1 + *(int *)(param_1 + 0x58) + 0x20e) = param_4;
    *(undefined4 *)(param_1 + *(int *)(param_1 + 0x58) * 4 + 0x158) =
         *(undefined4 *)(param_1 + 0x11c);
    *(undefined4 *)(param_1 + *(int *)(param_1 + 0x58) * 4 + 0x16c) =
         *(undefined4 *)(param_1 + 0x120);
    *(undefined4 *)(param_1 + *(int *)(param_1 + 0x58) * 4 + 0x180) =
         *(undefined4 *)(param_1 + 0x124);
    PSMTXConcat((Mtx *)(param_2 + 0x78),param_3,&MStack_48);
    GXLoadTexMtxImm(&MStack_48,*(undefined4 *)(param_1 + 0x120),0);
    iVar3 = *(int *)(param_1 + 0x120);
    *(int *)(param_1 + 0x120) = iVar3 + 3;
    iVar2 = *(int *)(param_1 + 0x124);
    *(int *)(param_1 + 0x124) = iVar2 + 1;
    GXSetTexCoordGen2(iVar2,0,0,iVar3,0,0x7d);
    iVar2 = *(int *)(param_1 + 0x11c);
    *(int *)(param_1 + 0x11c) = iVar2 + 1;
    SetTexture__11CTextureManF11_GXTexMapIDP8CTexture
              (&TextureMan,iVar2,*(CTexture **)(iVar1 + 0x3c));
    if (param_5 != 0) {
      iVar2 = *(int *)(param_1 + 0x11c);
      *(int *)(param_1 + 0x11c) = iVar2 + 1;
      SetTexture__11CTextureManF11_GXTexMapIDP8CTexture
                (&TextureMan,iVar2,*(CTexture **)(iVar1 + 0x40));
      *(undefined *)(param_1 + *(int *)(param_1 + 0x58) + 0x209) = *(undefined *)(iVar1 + 0xa4);
      *(byte *)(param_1 + 0x208) =
           *(byte *)(param_1 + 0x208) | (byte)(1 << *(int *)(param_1 + 0x58));
      *(int *)(param_1 + 0x5c) = *(int *)(param_1 + 0x5c) + 1;
    }
    *(int *)(param_1 + 0x58) = *(int *)(param_1 + 0x58) + 1;
    *(int *)(param_1 + 0x5c) = *(int *)(param_1 + 0x5c) + 1;
  }
  return;
}

