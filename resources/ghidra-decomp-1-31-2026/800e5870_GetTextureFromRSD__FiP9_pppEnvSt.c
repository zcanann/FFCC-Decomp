// Function: GetTextureFromRSD__FiP9_pppEnvSt
// Entry: 800e5870
// Size: 80 bytes

undefined4 GetTextureFromRSD__FiP9_pppEnvSt(int mapMeshIndex,_pppEnvSt *pppEnvSt)

{
  undefined4 uVar1;
  undefined4 local_8 [2];
  
  if (mapMeshIndex == 0xffff) {
    uVar1 = 0;
  }
  else {
    local_8[0] = 0;
    uVar1 = GetTexture__8CMapMeshFP12CMaterialSetRi
                      (pppEnvSt->m_mapMeshPtr[mapMeshIndex],pppEnvSt->m_materialSetPtr,local_8);
  }
  return uVar1;
}

