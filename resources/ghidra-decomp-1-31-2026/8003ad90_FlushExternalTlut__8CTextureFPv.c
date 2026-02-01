// Function: FlushExternalTlut__8CTextureFPv
// Entry: 8003ad90
// Size: 80 bytes

void FlushExternalTlut__8CTextureFPv(CTexture *texture,undefined4 param_2)

{
  int iVar1;
  
  if (texture->field93_0x60 == 9) {
    iVar1 = 0x100;
  }
  else if (texture->field93_0x60 == 8) {
    iVar1 = 0x10;
  }
  else {
    iVar1 = 0;
  }
  DCFlushRange(param_2,iVar1 << 2);
  return;
}

