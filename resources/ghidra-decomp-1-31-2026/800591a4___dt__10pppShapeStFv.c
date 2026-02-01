// Function: __dt__10pppShapeStFv
// Entry: 800591a4
// Size: 124 bytes

pppShapeSt * __dt__10pppShapeStFv(pppShapeSt *pppShapeSt,short param_2)

{
  if (pppShapeSt != (pppShapeSt *)0x0) {
    if (pppShapeSt->m_animData != (void *)0x0) {
      __dl__FPv();
      pppShapeSt->m_animData = (void *)0x0;
    }
    if (pppShapeSt->m_displayListData != (void *)0x0) {
      __dl__FPv();
      pppShapeSt->m_displayListData = (void *)0x0;
    }
    if (0 < param_2) {
      __dl__FPv(pppShapeSt);
    }
  }
  return pppShapeSt;
}

