// Function: SetFullScreenShadow__10CCameraPcsFPA4_fl
// Entry: 80036c38
// Size: 68 bytes

void SetFullScreenShadow__10CCameraPcsFPA4_fl(int param_1,undefined4 param_2,undefined4 param_3)

{
  if (*(char *)(param_1 + 0x404) != '\0') {
    SetFullScreenShadow__12CMaterialManFR17CFullScreenShadowPA4_fl
              (&MaterialMan,param_1 + 0x31c,param_2,param_3);
  }
  return;
}

