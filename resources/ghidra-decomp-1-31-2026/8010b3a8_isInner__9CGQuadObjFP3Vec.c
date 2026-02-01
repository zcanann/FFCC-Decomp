// Function: isInner__9CGQuadObjFP3Vec
// Entry: 8010b3a8
// Size: 256 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4 isInner__9CGQuadObjFP3Vec(CGQuadObj *gQuadObj,Vec *vec)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  CGQuadObj *pCVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  
  uVar7 = (uint)gQuadObj->m_vertexCount;
  if ((((uVar7 != 0) && (fVar1 = vec->x, gQuadObj->m_bboxMinX <= fVar1)) &&
      (fVar2 = vec->z, gQuadObj->m_bboxMinZ <= fVar2)) &&
     ((fVar1 <= gQuadObj->m_bboxMaxX && (fVar2 <= gQuadObj->m_bboxMaxZ)))) {
    if ((gQuadObj->m_yBase <= vec->y) && (vec->y <= gQuadObj->m_yBase + gQuadObj->m_yHeight)) {
      uVar8 = 0;
      uVar9 = uVar7;
      pCVar6 = gQuadObj;
      while ((uVar9 != 0 &&
             (fVar3 = pCVar6->m_vertices[0].z, fVar4 = pCVar6->m_vertices[0].x,
             iVar5 = (uVar8 + 1) - ((int)(uVar8 + 1) / (int)uVar7) * uVar7,
             FLOAT_80331958 <=
             (*(float *)((int)gQuadObj + iVar5 * 8 + 0x54) - fVar4) * (fVar2 - fVar3) -
             (*(float *)((int)gQuadObj + iVar5 * 8 + 0x58) - fVar3) * (fVar1 - fVar4)))) {
        pCVar6 = (CGQuadObj *)&(pCVar6->field0_0x0).object.m_stackPointer;
        uVar8 = uVar8 + 1;
        uVar9 = uVar9 - 1;
      }
      if (uVar8 == uVar7) {
        return 1;
      }
    }
  }
  return 0;
}

