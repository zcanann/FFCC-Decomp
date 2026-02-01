// Function: AddPrim__10pppDrawMngFfPQ29CCharaPcs7CHandle
// Entry: 8007bb90
// Size: 108 bytes

void AddPrim__10pppDrawMngFfPQ29CCharaPcs7CHandle
               (float depth,pppDrawMng *pppDrawMng,CCharaPcsCHandle *handle)

{
  pppDrawPrimitive *ppVar1;
  int iVar2;
  
  iVar2 = 0x100 - (int)(depth * pppDrawMng->m_depthScale);
  if (((-1 < iVar2) && (iVar2 < 0x400)) &&
     (ppVar1 = pppDrawMng->m_nextFree, ppVar1 < &pppDrawMng->m_nextFree)) {
    pppDrawMng->m_nextFree = ppVar1 + 1;
    ppVar1->m_type = '\x01';
    ppVar1->m_handle = handle;
    ppVar1->m_next = *(pppDrawPrimitive **)((int)pppDrawMng + iVar2 * 4);
    *(pppDrawPrimitive **)((int)pppDrawMng + iVar2 * 4) = ppVar1;
  }
  return;
}

