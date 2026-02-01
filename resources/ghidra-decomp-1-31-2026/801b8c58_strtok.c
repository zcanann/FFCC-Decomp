// Function: strtok
// Entry: 801b8c58
// Size: 316 bytes

byte * strtok(int param_1,int param_2)

{
  byte *pbVar1;
  byte bVar2;
  byte *pbVar3;
  byte *pbVar4;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  local_28 = DAT_801e70e0;
  local_24 = DAT_801e70e4;
  local_20 = DAT_801e70e8;
  local_1c = DAT_801e70ec;
  local_18 = DAT_801e70f0;
  local_14 = DAT_801e70f4;
  local_10 = DAT_801e70f8;
  local_c = DAT_801e70fc;
  if (param_1 != 0) {
    DAT_8032ec1c = (byte *)param_1;
  }
  pbVar3 = (byte *)(param_2 + -1);
  while( true ) {
    pbVar3 = pbVar3 + 1;
    bVar2 = *pbVar3;
    if (bVar2 == 0) break;
    *(byte *)((int)&local_28 + (uint)(bVar2 >> 3)) =
         *(byte *)((int)&local_28 + (uint)(bVar2 >> 3)) | (byte)(1 << (bVar2 & 7));
  }
  pbVar3 = (byte *)((int)DAT_8032ec1c + -1);
  do {
    pbVar3 = pbVar3 + 1;
    bVar2 = *pbVar3;
    if (bVar2 == 0) break;
  } while (((uint)*(byte *)((int)&local_28 + (uint)(bVar2 >> 3)) & 1 << (bVar2 & 7)) != 0);
  pbVar1 = pbVar3;
  if (bVar2 == 0) {
    pbVar3 = (byte *)0x0;
    DAT_8032ec1c = DAT_8032ec18;
  }
  else {
    do {
      pbVar4 = pbVar1;
      pbVar1 = pbVar4 + 1;
      bVar2 = *pbVar1;
      if (bVar2 == 0) break;
    } while (((uint)*(byte *)((int)&local_28 + (uint)(bVar2 >> 3)) & 1 << (bVar2 & 7)) == 0);
    if (bVar2 == 0) {
      DAT_8032ec1c = DAT_8032ec18;
    }
    else {
      DAT_8032ec1c = pbVar4 + 2;
      *pbVar1 = 0;
    }
  }
  return pbVar3;
}

