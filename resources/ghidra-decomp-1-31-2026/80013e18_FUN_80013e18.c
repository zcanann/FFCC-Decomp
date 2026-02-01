// Function: FUN_80013e18
// Entry: 80013e18
// Size: 88 bytes

void FUN_80013e18(byte *param_1)

{
  byte bVar1;
  
  do {
    bVar1 = *param_1;
    if (bVar1 == 0) {
      return;
    }
    if (bVar1 < 0x61) {
LAB_80013de4:
      if ((0xdf < bVar1) && (bVar1 < 0xf7)) goto LAB_80013e0c;
      if ((0xf7 < bVar1) && (bVar1 < 0xfd)) goto LAB_80013e0c;
    }
    else {
      if (0x7a < bVar1) goto LAB_80013de4;
LAB_80013e0c:
      bVar1 = bVar1 - 0x20;
    }
    *param_1 = bVar1;
    param_1 = param_1 + 1;
  } while( true );
}

