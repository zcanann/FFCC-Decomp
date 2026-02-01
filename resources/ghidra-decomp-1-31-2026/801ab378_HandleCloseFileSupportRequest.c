// Function: HandleCloseFileSupportRequest
// Entry: 801ab378
// Size: 232 bytes

int HandleCloseFileSupportRequest(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined local_58;
  undefined4 local_54;
  
  memset(&local_5c,0,0x40);
  local_58 = 0xd3;
  local_5c = 0x40;
  local_54 = param_1;
  iVar1 = TRKGetFreeBuffer(&local_64,&local_68);
  if (iVar1 == 0) {
    iVar1 = TRKAppendBuffer_ui8(local_68,&local_5c,0x40);
  }
  if (iVar1 == 0) {
    *param_2 = 0;
    iVar1 = TRKRequestSend(local_68,&local_60,3,3,0);
    if (iVar1 == 0) {
      iVar2 = TRKGetBuffer(local_60);
      *param_2 = *(undefined4 *)(iVar2 + 0x20);
    }
    TRKReleaseBuffer(local_60);
  }
  TRKReleaseBuffer(local_64);
  return iVar1;
}

