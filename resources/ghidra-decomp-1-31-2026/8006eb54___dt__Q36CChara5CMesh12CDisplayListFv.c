// Function: __dt__Q36CChara5CMesh12CDisplayListFv
// Entry: 8006eb54
// Size: 100 bytes

CDisplayList * __dt__Q36CChara5CMesh12CDisplayListFv(CDisplayList *displayList,short param_2)

{
  if (displayList != (CDisplayList *)0x0) {
    if (displayList->m_data != (void *)0x0) {
      __dla__FPv(displayList->m_data);
      displayList->m_data = (void *)0x0;
    }
    if (0 < param_2) {
      __dl__FPv(displayList);
    }
  }
  return displayList;
}

