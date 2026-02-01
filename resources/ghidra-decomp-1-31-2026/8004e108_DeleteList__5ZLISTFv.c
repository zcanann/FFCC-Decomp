// Function: DeleteList__5ZLISTFv
// Entry: 8004e108
// Size: 104 bytes

void DeleteList__5ZLISTFv(ZLIST *zlist)

{
  _ZLISTITEM *p_Var1;
  
  p_Var1 = (zlist->m_root).m_previous;
  if (p_Var1 != (_ZLISTITEM *)0x0) {
    while (p_Var1 = p_Var1->m_next, p_Var1 != (_ZLISTITEM *)0x0) {
      __dl__FPv();
    }
    (zlist->m_root).m_previous = (_ZLISTITEM *)0x0;
    (zlist->m_root).m_next = (_ZLISTITEM *)0x0;
    zlist->m_count = 0;
  }
  return;
}

