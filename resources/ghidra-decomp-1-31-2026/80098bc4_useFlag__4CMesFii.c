// Function: useFlag__4CMesFii
// Entry: 80098bc4
// Size: 192 bytes

undefined4 useFlag__4CMesFii(int param_1,int param_2,int param_3)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  
  pbVar3 = (byte *)(param_1 + *(int *)(param_1 + 0x3c10) * 6 + 0x3c14);
  do {
    if (param_2 <= *(int *)(param_1 + 0x3c10)) {
      return 1;
    }
    bVar1 = *pbVar3;
    if (bVar1 != 3) {
      if (bVar1 < 3) {
        if (bVar1 == 1) {
          iVar2 = (uint)pbVar3[2] * 4 + 0x3cc0;
          *(int *)(param_1 + iVar2) = *(int *)(param_1 + iVar2) + 1;
        }
        else if (bVar1 != 0) {
          *(int *)(param_1 + (uint)pbVar3[2] * 4 + 0x3cc0) = (int)*(short *)(pbVar3 + 4);
        }
      }
      else if (((bVar1 < 5) && (*(int *)(param_1 + (uint)pbVar3[2] * 4 + 0x3cc0) == 0)) &&
              (param_3 == 0)) {
        return 0;
      }
    }
    pbVar3 = pbVar3 + 6;
    *(int *)(param_1 + 0x3c10) = *(int *)(param_1 + 0x3c10) + 1;
  } while( true );
}

