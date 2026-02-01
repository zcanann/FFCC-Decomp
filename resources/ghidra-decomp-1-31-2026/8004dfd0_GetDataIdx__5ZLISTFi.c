// Function: GetDataIdx__5ZLISTFi
// Entry: 8004dfd0
// Size: 72 bytes

void * GetDataIdx__5ZLISTFi(ZLIST *zlist,int index)

{
  _ZLISTITEM *p_Var1;
  
  p_Var1 = (zlist->m_root).m_previous;
  if (p_Var1 == (_ZLISTITEM *)0x0) {
    p_Var1 = (_ZLISTITEM *)0x0;
  }
  else if (0 < index) {
    do {
      p_Var1 = p_Var1->m_next;
      if (p_Var1 == (_ZLISTITEM *)0x0) break;
      index = index + -1;
    } while (index != 0);
  }
  if (p_Var1 == (_ZLISTITEM *)0x0) {
    return (void *)0x0;
  }
  return p_Var1->m_data;
}

