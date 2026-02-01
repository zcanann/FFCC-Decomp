// Function: InquiryCallback
// Entry: 8017b90c
// Size: 60 bytes

void InquiryCallback(undefined4 param_1,int param_2)

{
  if (*(int *)(param_2 + 0xc) == 0) {
    DAT_800030e6 = DriveInfo.deviceCode | 0x8000;
  }
  else {
    DAT_800030e6 = 1;
  }
  return;
}

