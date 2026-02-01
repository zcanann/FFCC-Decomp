// Function: SetShadowBit32__12CMaterialManFQ210CMapShadow6TARGETPUlPA4_f
// Entry: 8003e660
// Size: 188 bytes

void SetShadowBit32__12CMaterialManFQ210CMapShadow6TARGETPUlPA4_f
               (undefined4 param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  for (uVar3 = 0; uVar2 = GetSize__24CPtrArray<P10CMapShadow>Fv(&MapMng.m_mapShadowArray),
      uVar3 < uVar2; uVar3 = uVar3 + 1) {
    iVar1 = __vc__24CPtrArray<P10CMapShadow>FUl(0x80266b98,uVar3);
    if (*(char *)(param_2 + iVar1 + 0xf0) != '\0') {
      if ((*(char *)(iVar1 + 7) == '\x01') ||
         ((1 << (uVar3 & 0x1f) & *(uint *)(param_3 + (uVar3 >> 3 & 0x1ffffffc))) != 0)) {
        SetShadow__12CMaterialManFR10CMapShadowPA4_fiUl(param_1,iVar1,param_4,uVar3,0xffffffff);
      }
    }
  }
  return;
}

