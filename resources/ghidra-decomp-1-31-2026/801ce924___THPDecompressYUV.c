// Function: __THPDecompressYUV
// Entry: 801ce924
// Size: 264 bytes

void __THPDecompressYUV(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  ushort uVar1;
  ushort uVar2;
  
  *(undefined4 *)(DAT_8032f5f0 + 0x6b0) = param_1;
  *(undefined4 *)(DAT_8032f5f0 + 0x6b4) = param_2;
  *(undefined4 *)(DAT_8032f5f0 + 0x6b8) = param_3;
  uVar2 = *(ushort *)(DAT_8032f5f0 + 0x698);
  uVar1 = *(ushort *)(DAT_8032f5f0 + 0x694);
  DAT_8032f5e4 = 0;
  DAT_8032f5e8 = 0;
  __THPPrepBitStream(0x3d043d04);
  if ((*(short *)(DAT_8032f5f0 + 0x692) == 0x200) && (uVar1 == 0x1c0)) {
    for (; uVar2 < 0x1c0; uVar2 = uVar2 + 0x10) {
      __THPDecompressiMCURow512x448();
    }
  }
  else if ((*(short *)(DAT_8032f5f0 + 0x692) == 0x280) && (uVar1 == 0x1e0)) {
    for (; uVar2 < 0x1e0; uVar2 = uVar2 + 0x10) {
      __THPDecompressiMCURow640x480();
    }
  }
  else {
    for (; uVar2 < uVar1; uVar2 = uVar2 + 0x10) {
      __THPDecompressiMCURowNxN();
    }
  }
  return;
}

