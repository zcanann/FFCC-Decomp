// Function: __dt__Q36CChara5CMesh8CRefDataFv
// Entry: 8006ebd4
// Size: 308 bytes

CMeshCRefData * __dt__Q36CChara5CMesh8CRefDataFv(CMeshCRefData *refData,short param_2)

{
  if (refData != (CMeshCRefData *)0x0) {
    if (refData->m_vertices != (S16Vec *)0x0) {
      __dla__FPv(refData->m_vertices);
      refData->m_vertices = (S16Vec *)0x0;
    }
    if (refData->m_normals != (S16Vec *)0x0) {
      __dla__FPv(refData->m_normals);
      refData->m_normals = (S16Vec *)0x0;
    }
    if (refData->m_colors != (uint8_t *)0x0) {
      __dla__FPv(refData->m_colors);
      refData->m_colors = (uint8_t *)0x0;
    }
    if (refData->m_uvs != (S16Vec *)0x0) {
      __dla__FPv(refData->m_uvs);
      refData->m_uvs = (S16Vec *)0x0;
    }
    if (refData->m_oneWeightData != (void *)0x0) {
      __dla__FPv(refData->m_oneWeightData);
      refData->m_oneWeightData = (void *)0x0;
    }
    if (refData->m_twoWeightData != (void *)0x0) {
      __dla__FPv(refData->m_twoWeightData);
      refData->m_twoWeightData = (void *)0x0;
    }
    if (refData->m_threeWeightData != (void *)0x0) {
      __dla__FPv(refData->m_threeWeightData);
      refData->m_threeWeightData = (void *)0x0;
    }
    if (refData->m_displayLists != (CDisplayList *)0x0) {
      __destroy_new_array(refData->m_displayLists,__dt__Q36CChara5CMesh12CDisplayListFv);
      refData->m_displayLists = (CDisplayList *)0x0;
    }
    if (refData->m_skins != (CSkin *)0x0) {
      __destroy_new_array(refData->m_skins,__dt__Q26CChara5CSkinFv);
      refData->m_skins = (CSkin *)0x0;
    }
    if (0 < param_2) {
      __dl__FPv(refData);
    }
  }
  return refData;
}

