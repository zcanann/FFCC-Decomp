// Function: SetWorldMapMatrix__10CCameraPcsFPA4_f
// Entry: 800b95b0
// Size: 76 bytes

void SetWorldMapMatrix__10CCameraPcsFPA4_f(int param_1,Mtx *param_2)

{
  PSMTXCopy(param_2,(Mtx *)(param_1 + 0x34));
  PSMTXInverse(param_2,(Mtx *)(param_1 + 100));
  return;
}

