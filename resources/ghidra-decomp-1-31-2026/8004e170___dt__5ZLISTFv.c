// Function: __dt__5ZLISTFv
// Entry: 8004e170
// Size: 136 bytes

ZLIST * __dt__5ZLISTFv(ZLIST *zlist,short param_2)

{
  _ZLISTITEM *p_Var1;
  
  if (zlist != (ZLIST *)0x0) {
    p_Var1 = (zlist->m_root).m_previous;
    if (p_Var1 != (_ZLISTITEM *)0x0) {
      while (p_Var1 = p_Var1->m_next, p_Var1 != (_ZLISTITEM *)0x0) {
        __dl__FPv();
      }
      (zlist->m_root).m_previous = (_ZLISTITEM *)0x0;
      (zlist->m_root).m_next = (_ZLISTITEM *)0x0;
      zlist->m_count = 0;
    }
    if (0 < param_2) {
      __dl__FPv(zlist);
    }
  }
  return zlist;
}

