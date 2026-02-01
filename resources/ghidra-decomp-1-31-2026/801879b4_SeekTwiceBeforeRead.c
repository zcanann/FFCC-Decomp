// Function: SeekTwiceBeforeRead
// Entry: 801879b4
// Size: 128 bytes

void SeekTwiceBeforeRead(undefined4 param_1,undefined4 param_2,uint param_3,undefined4 param_4)

{
  if ((param_3 & 0xffff8000) == 0) {
    DAT_8030c95c = 0;
  }
  else {
    DAT_8030c95c = (param_3 & 0xffff8000) + DAT_8032f040;
  }
  DAT_8030c950 = 2;
  DAT_8030c964 = 1;
  DAT_8030c978 = 0xffffffff;
  DAT_8032f05c = 0;
  DAT_8030c960 = param_4;
  DAT_8030c968 = param_1;
  DAT_8030c96c = param_2;
  DAT_8030c970 = param_3;
  DAT_8030c974 = param_4;
  DVDLowSeek(DAT_8030c95c,param_4);
  return;
}

