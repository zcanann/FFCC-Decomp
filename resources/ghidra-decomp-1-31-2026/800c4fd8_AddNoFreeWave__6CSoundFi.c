// Function: AddNoFreeWave__6CSoundFi
// Entry: 800c4fd8
// Size: 120 bytes

void AddNoFreeWave__6CSoundFi(CSound *sound,undefined2 param_2)

{
  CSound *pCVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  iVar3 = 4;
  pCVar1 = sound;
  do {
    if (*(short *)&pCVar1->field_0x22c8 == -1) {
      *(undefined2 *)(&sound->field_0x22c8 + iVar2 * 2) = param_2;
      return;
    }
    pCVar1 = (CSound *)&pCVar1->field_0x2;
    iVar2 = iVar2 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  if (System.m_execParam != 0) {
    Printf__7CSystemFPce(&System,&DAT_801db0bc);
  }
  return;
}

