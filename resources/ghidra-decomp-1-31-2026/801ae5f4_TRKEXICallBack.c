// Function: TRKEXICallBack
// Entry: 801ae5f4
// Size: 56 bytes

void TRKEXICallBack(undefined4 param_1,undefined4 param_2)

{
  OSEnableScheduler();
  TRKLoadContext(param_2,0x500);
  return;
}

