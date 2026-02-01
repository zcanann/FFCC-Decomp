// Function: SetRefPosition__10CCameraPcsFP3Vec
// Entry: 800b9c44
// Size: 28 bytes

void SetRefPosition__10CCameraPcsFP3Vec(int param_1,undefined4 *param_2)

{
  *(undefined4 *)(param_1 + 0xd4) = *param_2;
  *(undefined4 *)(param_1 + 0xd8) = param_2[1];
  *(undefined4 *)(param_1 + 0xdc) = param_2[2];
  return;
}

