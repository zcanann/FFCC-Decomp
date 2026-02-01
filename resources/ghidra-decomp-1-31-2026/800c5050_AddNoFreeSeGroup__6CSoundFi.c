// Function: AddNoFreeSeGroup__6CSoundFi
// Entry: 800c5050
// Size: 120 bytes

void AddNoFreeSeGroup__6CSoundFi(CSound *sound,undefined2 param_2)

{
  CSound *pCVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  iVar3 = 4;
  pCVar1 = sound;
  do {
    if (*(short *)&pCVar1->field_0x22c0 == -1) {
      *(undefined2 *)(&sound->field_0x22c0 + iVar2 * 2) = param_2;
      return;
    }
    pCVar1 = (CSound *)&pCVar1->field_0x2;
    iVar2 = iVar2 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  if (System.m_execParam != 0) {
    Printf__7CSystemFPce(&System,&DAT_801db0e4);
  }
  return;
}

