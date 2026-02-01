// Function: AddTail__5ZLISTFPv
// Entry: 8004e04c
// Size: 188 bytes

undefined4 AddTail__5ZLISTFPv(ZLIST *zlist,void *tail)

{
  _ZLISTITEM *p_Var1;
  _ZLISTITEM *p_Var2;
  undefined4 uVar3;
  
  p_Var2 = (_ZLISTITEM *)
           __nw__FUlPQ27CMemory6CStagePci(0xc,MaterialEditorPcs._4_4_,s_zlist_cpp_801d7dc0,0x107);
  if (p_Var2 == (_ZLISTITEM *)0x0) {
    p_Var2 = (_ZLISTITEM *)0x0;
  }
  else {
    p_Var2->m_previous = (_ZLISTITEM *)0x0;
    p_Var2->m_next = (_ZLISTITEM *)0x0;
  }
  if (p_Var2 == (_ZLISTITEM *)0x0) {
    uVar3 = 0;
  }
  else {
    p_Var1 = (zlist->m_root).m_next;
    if (p_Var1 == (_ZLISTITEM *)0x0) {
      (zlist->m_root).m_previous = p_Var2;
      (zlist->m_root).m_next = p_Var2;
    }
    else {
      p_Var2->m_previous = p_Var1;
      ((zlist->m_root).m_next)->m_next = p_Var2;
      (zlist->m_root).m_next = p_Var2;
    }
    p_Var2->m_data = tail;
    uVar3 = 1;
    zlist->m_count = zlist->m_count + 1;
  }
  return uVar3;
}

