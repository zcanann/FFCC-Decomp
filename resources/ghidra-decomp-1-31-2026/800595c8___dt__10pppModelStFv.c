// Function: __dt__10pppModelStFv
// Entry: 800595c8
// Size: 84 bytes

pppModelSt * __dt__10pppModelStFv(pppModelSt *pppModelSt,short param_2)

{
  if ((pppModelSt != (pppModelSt *)0x0) &&
     (__dt__8CMapMeshFv(&pppModelSt->m_mapMesh,0), 0 < param_2)) {
    __dl__FPv(pppModelSt);
  }
  return pppModelSt;
}

