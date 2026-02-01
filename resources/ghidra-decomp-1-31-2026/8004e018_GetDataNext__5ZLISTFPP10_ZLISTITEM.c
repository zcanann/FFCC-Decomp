// Function: GetDataNext__5ZLISTFPP10_ZLISTITEM
// Entry: 8004e018
// Size: 52 bytes

void * GetDataNext__5ZLISTFPP10_ZLISTITEM(ZLIST *zlist,_ZLISTITEM **zlistItem)

{
  _ZLISTITEM *p_Var1;
  
  if (zlistItem == (_ZLISTITEM **)0x0) {
    return (void *)0x0;
  }
  p_Var1 = *zlistItem;
  if (p_Var1 == (_ZLISTITEM *)0x0) {
    return (void *)0x0;
  }
  *zlistItem = p_Var1->m_next;
  return p_Var1->m_data;
}

