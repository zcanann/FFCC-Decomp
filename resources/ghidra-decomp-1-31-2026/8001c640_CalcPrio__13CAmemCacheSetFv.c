// Function: CalcPrio__13CAmemCacheSetFv
// Entry: 8001c640
// Size: 100 bytes

void CalcPrio__13CAmemCacheSetFv(CAmemCacheSet *amemCacheSet)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar1 = 0;
  for (iVar3 = 0; iVar3 < *(int *)&amemCacheSet->field_0x3c; iVar3 = iVar3 + 1) {
    piVar2 = (int *)(*(int *)&amemCacheSet->field_0x58 + iVar1);
    if ((((*(char *)((int)piVar2 + 0xe) != '\0') && (*(short *)(piVar2 + 3) == 0)) && (*piVar2 != 0)
        ) && (piVar2[4] != 0)) {
      piVar2[4] = piVar2[4] + -1;
    }
    iVar1 = iVar1 + 0x1c;
  }
  return;
}

