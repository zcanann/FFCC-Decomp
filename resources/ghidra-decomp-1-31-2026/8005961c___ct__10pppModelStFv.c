// Function: __ct__10pppModelStFv
// Entry: 8005961c
// Size: 60 bytes

pppModelSt * __ct__10pppModelStFv(pppModelSt *pppModelSt)

{
  __ct__8CMapMeshFv(&pppModelSt->m_mapMesh);
  pppModelSt->m_refCount = 0;
  pppModelSt->m_isUsed = '\0';
  return pppModelSt;
}

