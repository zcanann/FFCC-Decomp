// Function: onScriptChanging__8CMesMenuFPc
// Entry: 8009b8e8
// Size: 112 bytes

void onScriptChanging__8CMesMenuFPc(int param_1)

{
  Set__4CMesFPci(param_1 + 0x1c,0,0);
  *(undefined4 *)(param_1 + 0xc) = 4;
  *(undefined4 *)(param_1 + 8) = 0;
  if (*(int *)(param_1 + 0x18) < 4) {
    SetFade__9CRingMenuFi(*(undefined4 *)(&MenuPcs.field_0x13c + *(int *)(param_1 + 0x18) * 4),1);
  }
  return;
}

