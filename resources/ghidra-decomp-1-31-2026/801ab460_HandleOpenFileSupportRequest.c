// Function: HandleOpenFileSupportRequest
// Entry: 801ab460
// Size: 284 bytes

int HandleOpenFileSupportRequest
              (undefined4 param_1,undefined param_2,undefined4 *param_3,undefined4 *param_4)

{
  int iVar1;
  int unaff_r30;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  int local_5c;
  undefined local_58;
  undefined local_54;
  short local_50;
  
  memset(&local_5c,0,0x40);
  *param_3 = 0;
  local_58 = 0xd2;
  local_5c = strlen(param_1);
  local_5c = local_5c + 0x41;
  local_54 = param_2;
  local_50 = strlen(param_1);
  local_50 = local_50 + 1;
  TRKGetFreeBuffer(&local_64,&local_68);
  iVar1 = TRKAppendBuffer_ui8(local_68,&local_5c,0x40);
  if (iVar1 == 0) {
    iVar1 = strlen(param_1);
    iVar1 = TRKAppendBuffer_ui8(local_68,param_1,iVar1 + 1);
  }
  if (iVar1 == 0) {
    *param_4 = 0;
    iVar1 = TRKRequestSend(local_68,&local_60,7,3,0);
    if (iVar1 == 0) {
      unaff_r30 = TRKGetBuffer(local_60);
    }
    *param_4 = *(undefined4 *)(unaff_r30 + 0x20);
    *param_3 = *(undefined4 *)(unaff_r30 + 0x18);
    TRKReleaseBuffer(local_60);
  }
  TRKReleaseBuffer(local_64);
  return iVar1;
}

