// Function: onDestroy__9CGItemObjFv
// Entry: 80126f3c
// Size: 88 bytes

void onDestroy__9CGItemObjFv(int param_1)

{
  if (*(int *)(param_1 + 0x564) != 0) {
    __dt__Q29CCharaPcs7CHandleFv(*(int *)(param_1 + 0x564),1);
  }
  DeleteParticleSlot__13CFlatRuntime2Fii((CFlatRuntime2 *)&CFlat,*(undefined4 *)(param_1 + 0x55c));
  onDestroy__8CGPrgObjFv(param_1);
  return;
}

