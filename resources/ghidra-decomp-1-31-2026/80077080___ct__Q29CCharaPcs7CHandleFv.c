// Function: __ct__Q29CCharaPcs7CHandleFv
// Entry: 80077080
// Size: 252 bytes

void __ct__Q29CCharaPcs7CHandleFv(CCharaPcsCHandle *handle)

{
  float fVar1;
  float fVar2;
  CCharaPcsCHandle *pCVar3;
  int iVar4;
  
  handle->m_previous = (CCharaPcsCHandle *)0x0;
  handle->m_next = (CCharaPcsCHandle *)0x0;
  handle->m_model = (CModel *)0x0;
  handle->m_textureSet = (CTextureSet *)0x0;
  handle->m_modelLoadRef = (CRef *)0x0;
  handle->m_texLoadRef = (CRef *)0x0;
  iVar4 = 2;
  pCVar3 = handle;
  do {
    pCVar3->m_animSlot[0] = (CRef *)0x0;
    pCVar3->m_animSlot[1] = (CRef *)0x0;
    pCVar3->m_animSlot[2] = (CRef *)0x0;
    pCVar3->m_animSlot[3] = (CRef *)0x0;
    pCVar3->m_animSlot[4] = (CRef *)0x0;
    pCVar3->m_animSlot[5] = (CRef *)0x0;
    pCVar3->m_animSlot[6] = (CRef *)0x0;
    pCVar3->m_animSlot[7] = (CRef *)0x0;
    pCVar3->m_animSlot[8] = (CRef *)0x0;
    pCVar3->m_animSlot[9] = (CRef *)0x0;
    pCVar3->m_animSlot[10] = (CRef *)0x0;
    pCVar3->m_animSlot[0xb] = (CRef *)0x0;
    pCVar3->m_animSlot[0xc] = (CRef *)0x0;
    pCVar3->m_animSlot[0xd] = (CRef *)0x0;
    pCVar3->m_animSlot[0xe] = (CRef *)0x0;
    pCVar3->m_animSlot[0xf] = (CRef *)0x0;
    pCVar3->m_animSlot[0x10] = (CRef *)0x0;
    pCVar3->m_animSlot[0x11] = (CRef *)0x0;
    pCVar3->m_animSlot[0x12] = (CRef *)0x0;
    pCVar3->m_animSlot[0x13] = (CRef *)0x0;
    pCVar3->m_animSlot[0x14] = (CRef *)0x0;
    pCVar3->m_animSlot[0x15] = (CRef *)0x0;
    pCVar3->m_animSlot[0x16] = (CRef *)0x0;
    pCVar3->m_animSlot[0x17] = (CRef *)0x0;
    pCVar3->m_animSlot[0x18] = (CRef *)0x0;
    pCVar3->m_animSlot[0x19] = (CRef *)0x0;
    pCVar3->m_animSlot[0x1a] = (CRef *)0x0;
    pCVar3->m_animSlot[0x1b] = (CRef *)0x0;
    pCVar3->m_animSlot[0x1c] = (CRef *)0x0;
    pCVar3->m_animSlot[0x1d] = (CRef *)0x0;
    pCVar3->m_animSlot[0x1e] = (CRef *)0x0;
    pCVar3->m_animSlot[0x1f] = (CRef *)0x0;
    pCVar3 = (CCharaPcsCHandle *)(pCVar3->m_animSlot + 0x1c);
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  handle->m_pdtLoadRef = (CRef *)0x0;
  fVar2 = FLOAT_8033028c;
  handle->m_currentAnimIndex = -1;
  fVar1 = FLOAT_80330288;
  handle->m_flags = 0;
  handle->m_colorPhase = fVar2;
  handle->m_sortZ = fVar1;
  handle->m_shadowTexturePtr = (void *)0x0;
  handle->m_asyncState = 0;
  handle->m_asyncFileHandle = (CFileCHandle *)0x0;
  handle->m_fogBlend = fVar1;
  handle->m_unk0x158 = 0;
  handle->m_drawListFlags = handle->m_drawListFlags & 0x7f | 0x80;
  return;
}

