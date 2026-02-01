// Function: Init__11CTextureManFv
// Entry: 8003bdf4
// Size: 72 bytes

void Init__11CTextureManFv(CTextureMan *textureMan)

{
  CStage *pCVar1;
  
  pCVar1 = CreateStage__7CMemoryFUlPci(&Memory,0x40000,s_CTexture_texture_801d79a0,0);
  textureMan->memoryStage = pCVar1;
  return;
}

