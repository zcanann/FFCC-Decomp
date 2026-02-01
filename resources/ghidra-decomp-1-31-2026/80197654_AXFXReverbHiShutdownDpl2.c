// Function: AXFXReverbHiShutdownDpl2
// Entry: 80197654
// Size: 532 bytes

undefined4 AXFXReverbHiShutdownDpl2(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = OSDisableInterrupts();
  (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(param_1 + 0xc));
  (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(param_1 + 0x20));
  (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(param_1 + 0x34));
  (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(param_1 + 0x48));
  (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(param_1 + 0x5c));
  (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(param_1 + 0x70));
  (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(param_1 + 0x84));
  (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(param_1 + 0x98));
  (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(param_1 + 0xac));
  (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(param_1 + 0xc0));
  (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(param_1 + 0xd4));
  (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(param_1 + 0xe8));
  (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(param_1 + 0xfc));
  (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(param_1 + 0x110));
  (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(param_1 + 0x124));
  (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(param_1 + 0x138));
  (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(param_1 + 0x14c));
  (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(param_1 + 0x160));
  (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(param_1 + 0x174));
  (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(param_1 + 0x188));
  (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(param_1 + 0x19c));
  (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(param_1 + 0x1b0));
  (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(param_1 + 0x1c4));
  (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(param_1 + 0x1d8));
  if (*(int *)(param_1 + 0x22c) != 0) {
    (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(param_1 + 0x234));
    (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(param_1 + 0x238));
    (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(param_1 + 0x23c));
    (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(param_1 + 0x240));
  }
  OSRestoreInterrupts(uVar1);
  return 1;
}

