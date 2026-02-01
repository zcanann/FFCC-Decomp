// Function: CheckName__8CTextureFPc
// Entry: 8003b030
// Size: 44 bytes

uint CheckName__8CTextureFPc(CTexture *texture)

{
  uint uVar1;
  undefined4 uVar2;
  
  uVar2 = strcmp(&texture->field_0x8);
  uVar1 = countLeadingZeros(uVar2);
  return uVar1 >> 5 & 0xff;
}

