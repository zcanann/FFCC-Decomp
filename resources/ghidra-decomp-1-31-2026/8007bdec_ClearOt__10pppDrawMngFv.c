// Function: ClearOt__10pppDrawMngFv
// Entry: 8007bdec
// Size: 84 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void ClearOt__10pppDrawMngFv(pppDrawMng *pppDrawMng)

{
  int iVar1;
  pppDrawMng *ppVar2;
  
  iVar1 = 0x400;
  ppVar2 = pppDrawMng;
  if (Game.game.m_currentMapId == 0x21) {
    pppDrawMng->m_depthScale = FLOAT_80330330;
  }
  else {
    pppDrawMng->m_depthScale = FLOAT_80330334;
  }
  do {
    iVar1 = iVar1 + -1;
    ppVar2->m_primitiveRefs[0] = (pppDrawPrimitive *)0x0;
    ppVar2 = (pppDrawMng *)(ppVar2->m_primitiveRefs + 1);
  } while (iVar1 != 0);
  pppDrawMng->m_nextFree = pppDrawMng->m_primitivePool;
  return;
}

