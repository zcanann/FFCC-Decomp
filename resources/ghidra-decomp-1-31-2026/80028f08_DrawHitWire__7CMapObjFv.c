// Function: DrawHitWire__7CMapObjFv
// Entry: 80028f08
// Size: 104 bytes

void DrawHitWire__7CMapObjFv(int param_1)

{
  if ((*(char *)(param_1 + 0x1d) == '\x02') && (*(int *)(param_1 + 0xc) != 0)) {
    SetObjMatrix__12CMaterialManFPA4_fPA4_f(&MaterialMan,0x8026805c,param_1 + 0xb8);
    DrawWire__7CMapHitFv(*(CMapHit **)(param_1 + 0xc));
  }
  return;
}

