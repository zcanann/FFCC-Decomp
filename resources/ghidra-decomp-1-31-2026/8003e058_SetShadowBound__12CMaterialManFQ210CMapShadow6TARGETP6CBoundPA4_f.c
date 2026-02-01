// Function: SetShadowBound__12CMaterialManFQ210CMapShadow6TARGETP6CBoundPA4_f
// Entry: 8003e058
// Size: 244 bytes

void SetShadowBound__12CMaterialManFQ210CMapShadow6TARGETP6CBoundPA4_f
               (undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  Mtx MStack_5c;
  
  for (uVar4 = 0; uVar2 = GetSize__24CPtrArray<P10CMapShadow>Fv(&MapMng.m_mapShadowArray),
      uVar4 < uVar2; uVar4 = uVar4 + 1) {
    iVar1 = __vc__24CPtrArray<P10CMapShadow>FUl(0x80266b98,uVar4);
    if (*(char *)(param_2 + iVar1 + 0xf0) != '\0') {
      iVar3 = *(int *)(iVar1 + 0xc);
      local_68 = *(undefined4 *)(iVar3 + 0xc4);
      local_64 = *(undefined4 *)(iVar3 + 0xd4);
      local_60 = *(undefined4 *)(iVar3 + 0xe4);
      PSMTXScaleApply(FLOAT_8032faf8,FLOAT_8032faf8,FLOAT_8032faf0,(Mtx *)(iVar1 + 0x78),&MStack_5c)
      ;
      if ((*(char *)(iVar1 + 7) == '\x01') ||
         (iVar3 = CheckFrustum__6CBoundFR3VecPA4_ff
                            ((double)FLOAT_8032fafc,param_3,&local_68,&MStack_5c), iVar3 != 0)) {
        SetShadow__12CMaterialManFR10CMapShadowPA4_fiUl(param_1,iVar1,param_4,uVar4,0xffffffff);
      }
    }
  }
  return;
}

