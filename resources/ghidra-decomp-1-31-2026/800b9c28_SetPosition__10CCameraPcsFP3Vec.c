// Function: SetPosition__10CCameraPcsFP3Vec
// Entry: 800b9c28
// Size: 28 bytes

void SetPosition__10CCameraPcsFP3Vec(int param_1,undefined4 *param_2)

{
  *(undefined4 *)(param_1 + 0xe0) = *param_2;
  *(undefined4 *)(param_1 + 0xe4) = param_2[1];
  *(undefined4 *)(param_1 + 0xe8) = param_2[2];
  return;
}

