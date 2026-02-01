// Function: onDraw__9CGQuadObjFv
// Entry: 8010b4a8
// Size: 424 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onDraw__9CGQuadObjFv(CGQuadObj *gQuadObj)

{
  QuadVertex *pQVar1;
  QuadVertex *pQVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  CGQuadObj *pCVar6;
  int iVar7;
  undefined auStack_18 [4];
  undefined4 local_14 [4];
  
  if ((gQuadObj->m_vertexCount != '\0') && ((CFlat._4764_4_ & 0x10000) != 0)) {
    puVar4 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_18,0xff,0xff,0xff,0xff);
    local_14[0] = *puVar4;
    GXSetChanMatColor(4,local_14);
    GXLoadPosMtxImm(0x802687ac,0);
    GXBegin(0xa8,0,(uint)gQuadObj->m_vertexCount * 6);
    iVar7 = 0;
    pCVar6 = gQuadObj;
    while (iVar7 < (int)(uint)gQuadObj->m_vertexCount) {
      iVar5 = iVar7 + 1;
      iVar7 = iVar7 + 1;
      DAT_cc008000 = pCVar6->m_vertices[0].x;
      DAT_cc008000 = gQuadObj->m_yBase;
      DAT_cc008000 = pCVar6->m_vertices[0].z;
      iVar3 = iVar5 - (iVar5 / (int)(uint)gQuadObj->m_vertexCount) * (uint)gQuadObj->m_vertexCount;
      DAT_cc008000 = *(undefined4 *)((int)gQuadObj + iVar3 * 8 + 0x54);
      DAT_cc008000 = gQuadObj->m_yBase;
      DAT_cc008000 = *(undefined4 *)((int)gQuadObj + iVar3 * 8 + 0x58);
      DAT_cc008000 = pCVar6->m_vertices[0].x;
      DAT_cc008000 = gQuadObj->m_yBase + gQuadObj->m_yHeight;
      DAT_cc008000 = pCVar6->m_vertices[0].z;
      iVar5 = iVar5 - (iVar5 / (int)(uint)gQuadObj->m_vertexCount) * (uint)gQuadObj->m_vertexCount;
      DAT_cc008000 = *(undefined4 *)((int)gQuadObj + iVar5 * 8 + 0x54);
      DAT_cc008000 = gQuadObj->m_yBase + gQuadObj->m_yHeight;
      DAT_cc008000 = *(undefined4 *)((int)gQuadObj + iVar5 * 8 + 0x58);
      DAT_cc008000 = pCVar6->m_vertices[0].x;
      DAT_cc008000 = gQuadObj->m_yBase;
      DAT_cc008000 = pCVar6->m_vertices[0].z;
      pQVar2 = pCVar6->m_vertices;
      pQVar1 = pCVar6->m_vertices;
      pCVar6 = (CGQuadObj *)&(pCVar6->field0_0x0).object.m_stackPointer;
      DAT_cc008000 = pQVar1->x;
      DAT_cc008000 = gQuadObj->m_yBase + gQuadObj->m_yHeight;
      DAT_cc008000 = pQVar2->z;
    }
  }
  return;
}

