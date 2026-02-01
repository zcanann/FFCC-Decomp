// Function: __ct__Q26CChara5CMeshFv
// Entry: 8006fbb0
// Size: 76 bytes

CMesh * __ct__Q26CChara5CMeshFv(CMesh *mesh)

{
  __ct__4CRefFv(&mesh->ref);
  (mesh->ref).vtable = &PTR_PTR_s_CChara_CMesh_801fccdc;
  mesh->m_data = (CMeshCRefData *)0x0;
  mesh->m_workPositions = (S16Vec *)0x0;
  mesh->m_workNormals = (S16Vec *)0x0;
  return mesh;
}

