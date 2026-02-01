// Function: Add__9CGQuadObjFff
// Entry: 8010b2ac
// Size: 208 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void Add__9CGQuadObjFff(float x,float y,CGQuadObj *gQuadObj)

{
  float fVar1;
  float fVar2;
  
  gQuadObj->m_vertices[gQuadObj->m_vertexCount].x = x;
  gQuadObj->m_vertices[gQuadObj->m_vertexCount].z = y;
  fVar1 = gQuadObj->m_vertices[gQuadObj->m_vertexCount].x;
  if (gQuadObj->m_bboxMinX < fVar1) {
    fVar1 = gQuadObj->m_bboxMinX;
  }
  gQuadObj->m_bboxMinX = fVar1;
  fVar1 = gQuadObj->m_vertices[gQuadObj->m_vertexCount].z;
  if (gQuadObj->m_bboxMinZ < fVar1) {
    fVar1 = gQuadObj->m_bboxMinZ;
  }
  gQuadObj->m_bboxMinZ = fVar1;
  fVar1 = gQuadObj->m_bboxMaxX;
  fVar2 = gQuadObj->m_vertices[gQuadObj->m_vertexCount].x;
  if (fVar1 < fVar2) {
    fVar1 = fVar2;
  }
  gQuadObj->m_bboxMaxX = fVar1;
  fVar1 = gQuadObj->m_bboxMaxZ;
  fVar2 = gQuadObj->m_vertices[gQuadObj->m_vertexCount].z;
  if (fVar1 < fVar2) {
    fVar1 = fVar2;
  }
  gQuadObj->m_bboxMaxZ = fVar1;
  gQuadObj->m_vertexCount = gQuadObj->m_vertexCount + '\x01';
  return;
}

