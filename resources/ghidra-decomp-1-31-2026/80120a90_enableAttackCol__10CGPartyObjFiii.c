// Function: enableAttackCol__10CGPartyObjFiii
// Entry: 80120a90
// Size: 228 bytes

void enableAttackCol__10CGPartyObjFiii(int param_1,int param_2,int param_3,uint param_4)

{
  int iVar1;
  int iVar2;
  
  if (param_2 == 0) {
    *(undefined4 *)(param_1 + 0x20c) = 0;
    *(undefined4 *)(param_1 + 0x23c) = 0;
    *(undefined4 *)(param_1 + 0x26c) = 0;
  }
  else {
    resetIgnoreHit__10CGCharaObjFv();
    iVar1 = 0;
    if ((param_3 == 0) || ((param_4 & 1) != 0)) {
      iVar1 = 1;
    }
    iVar2 = 0;
    *(uint *)(param_1 + 0x20c) = (uint)-iVar1 >> 0x1f;
    if ((param_3 != 0) && ((param_4 & 2) != 0)) {
      iVar2 = 1;
    }
    iVar1 = 0;
    *(uint *)(param_1 + 0x23c) = (uint)-iVar2 >> 0x1f;
    if ((param_3 != 0) && ((param_4 & 4) != 0)) {
      iVar1 = 1;
    }
    *(uint *)(param_1 + 0x26c) = (uint)-iVar1 >> 0x1f;
  }
  return;
}

