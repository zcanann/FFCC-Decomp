// Function: __dt__Q26CChara5CMeshFv
// Entry: 8006fb50
// Size: 96 bytes

CMesh * __dt__Q26CChara5CMeshFv(CMesh *mesh,short param_2)

{
  if (mesh != (CMesh *)0x0) {
    (mesh->ref).vtable = &PTR_PTR_s_CChara_CMesh_801fccdc;
    __dt__4CRefFv(&mesh->ref,0);
    if (0 < param_2) {
      __dl__FPv(mesh);
    }
  }
  return mesh;
}

