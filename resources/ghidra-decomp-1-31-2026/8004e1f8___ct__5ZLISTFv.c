// Function: __ct__5ZLISTFv
// Entry: 8004e1f8
// Size: 24 bytes

void __ct__5ZLISTFv(ZLIST *zlist)

{
  (zlist->m_root).m_previous = (_ZLISTITEM *)0x0;
  (zlist->m_root).m_next = (_ZLISTITEM *)0x0;
  (zlist->m_root).m_data = (void *)0x0;
  zlist->m_count = 0;
  return;
}

