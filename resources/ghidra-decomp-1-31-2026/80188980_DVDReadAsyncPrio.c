// Function: DVDReadAsyncPrio
// Entry: 80188980
// Size: 192 bytes

undefined4
DVDReadAsyncPrio(int param_1,undefined4 param_2,int param_3,uint param_4,undefined4 param_5,
                undefined4 param_6)

{
  if (-1 < (int)param_4) {
    if (param_4 < *(uint *)(param_1 + 0x34)) goto LAB_801889d0;
  }
  OSPanic(&DAT_8032ead8,0x2e6,s_DVDReadAsync____specified_area_i_80217570);
LAB_801889d0:
  if (((int)(param_4 + param_3) < 0) || (*(int *)(param_1 + 0x34) + 0x20U <= param_4 + param_3)) {
    OSPanic(&DAT_8032ead8,0x2ec,s_DVDReadAsync____specified_area_i_80217570);
  }
  *(undefined4 *)(param_1 + 0x38) = param_5;
  DVDReadAbsAsyncPrio(param_1,param_2,param_3,*(int *)(param_1 + 0x30) + param_4,cbForReadAsync,
                      param_6);
  return 1;
}

