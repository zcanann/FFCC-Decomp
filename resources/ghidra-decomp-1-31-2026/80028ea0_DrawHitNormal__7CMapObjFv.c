// Function: DrawHitNormal__7CMapObjFv
// Entry: 80028ea0
// Size: 104 bytes

void DrawHitNormal__7CMapObjFv(int param_1)

{
  if ((*(char *)(param_1 + 0x1d) == '\x02') && (*(int *)(param_1 + 0xc) != 0)) {
    SetObjMatrix__12CMaterialManFPA4_fPA4_f(&MaterialMan,0x8026805c,param_1 + 0xb8);
    DrawNormal__7CMapHitFv(*(undefined4 *)(param_1 + 0xc));
  }
  return;
}

