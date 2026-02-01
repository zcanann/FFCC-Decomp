// Function: SetDrawFlag__7CMapObjFv
// Entry: 80028fd8
// Size: 188 bytes

void SetDrawFlag__7CMapObjFv(int param_1)

{
  int iVar1;
  Mtx MStack_38;
  
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfb;
  if ((*(char *)(param_1 + 0x1d) == '\x01') && (*(int *)(param_1 + 0xc) != 0)) {
    if ((*(char *)(param_1 + 0x1f) == -1) && ((*(byte *)(param_1 + 0x18) & 1) != 0)) {
      PSMTXConcat((Mtx *)&MapMng.field_0x22958,(Mtx *)(param_1 + 0xb8),&MStack_38);
      iVar1 = CheckFrustum__6CBoundFR3VecPA4_ff
                        ((double)MapMng.drawRangeMapObj,*(int *)(param_1 + 0xc) + 0xc,0x80268050,
                         &MStack_38);
      if (iVar1 != 0) {
        *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) | 4;
      }
    }
  }
  return;
}

