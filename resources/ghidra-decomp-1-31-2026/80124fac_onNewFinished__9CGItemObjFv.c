// Function: onNewFinished__9CGItemObjFv
// Entry: 80124fac
// Size: 52 bytes

void onNewFinished__9CGItemObjFv(int param_1)

{
  *(undefined4 *)(param_1 + 0x568) = *(undefined4 *)(param_1 + 0x144);
  *(ushort *)(param_1 + 0x560) = (ushort)(DAT_8032ee90 >> 3) & 1;
  loadModel__9CGItemObjFv();
  return;
}

