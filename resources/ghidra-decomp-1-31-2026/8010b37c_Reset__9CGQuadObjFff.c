// Function: Reset__9CGQuadObjFff
// Entry: 8010b37c
// Size: 44 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void Reset__9CGQuadObjFff(float base,float height,CGQuadObj *gQuadObj)

{
  float fVar1;
  float fVar2;
  
  fVar1 = FLOAT_80331950;
  gQuadObj->m_vertexCount = '\0';
  fVar2 = FLOAT_80331954;
  gQuadObj->m_yBase = base;
  gQuadObj->m_yHeight = height;
  gQuadObj->m_bboxMinZ = fVar1;
  gQuadObj->m_bboxMinX = fVar1;
  gQuadObj->m_bboxMaxZ = fVar2;
  gQuadObj->m_bboxMaxX = fVar2;
  return;
}

