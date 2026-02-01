// Function: OSSetCurrentHeap
// Entry: 8017cb0c
// Size: 16 bytes

undefined4 OSSetCurrentHeap(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_8032ea90;
  DAT_8032ea90 = param_1;
  return uVar1;
}

