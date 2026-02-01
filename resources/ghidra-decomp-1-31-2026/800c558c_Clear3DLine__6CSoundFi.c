// Function: Clear3DLine__6CSoundFi
// Entry: 800c558c
// Size: 100 bytes

void Clear3DLine__6CSoundFi(CSound *sound,int param_2)

{
  if (7 < (uint)param_2) {
    Printf__7CSystemFPce(&System,s_CSound__C_B_801db170);
  }
  *(undefined4 *)(&sound->field_0x1444 + param_2 * 0x1cc) = 0;
  return;
}

