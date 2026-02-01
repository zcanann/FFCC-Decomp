// Function: DrawCharaShadowTypeMeshFlag_r__8COctTreeFP8COctNode
// Entry: 8002e994
// Size: 556 bytes

void DrawCharaShadowTypeMeshFlag_r__8COctTreeFP8COctNode(COctTree *octTree,COctNode *octNode)

{
  int iVar1;
  int iVar2;
  COctNode *pCVar3;
  COctNode *pCVar4;
  COctNode *pCVar5;
  COctNode *pCVar6;
  COctNode *pCVar7;
  COctNode *pCVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  
  if (((ushort)octNode->meshIndex != 0) && ((octNode->flags & 1) != 0)) {
    DrawMeshCharaShadow__8CMapMeshFUsUs
              (*(CMapMesh **)((int)octTree->field2_0x8 + 0xc),(uint)(ushort)octNode->_meshIndex2,
               (uint)(ushort)octNode->meshIndex);
  }
  iVar1 = 0;
  do {
    pCVar3 = octNode->children[0];
    if (pCVar3 == (COctNode *)0x0) {
      return;
    }
    if (((ushort)pCVar3->meshIndex != 0) && ((pCVar3->flags & 1) != 0)) {
      DrawMeshCharaShadow__8CMapMeshFUsUs
                (*(CMapMesh **)((int)octTree->field2_0x8 + 0xc),(uint)(ushort)pCVar3->_meshIndex2,
                 (uint)(ushort)pCVar3->meshIndex);
    }
    iVar2 = 0;
    do {
      pCVar8 = pCVar3->children[0];
      if (pCVar8 == (COctNode *)0x0) break;
      if (((ushort)pCVar8->meshIndex != 0) && ((pCVar8->flags & 1) != 0)) {
        DrawMeshCharaShadow__8CMapMeshFUsUs
                  (*(CMapMesh **)((int)octTree->field2_0x8 + 0xc),(uint)(ushort)pCVar8->_meshIndex2,
                   (uint)(ushort)pCVar8->meshIndex);
      }
      iVar13 = 0;
      do {
        pCVar7 = pCVar8->children[0];
        if (pCVar7 == (COctNode *)0x0) break;
        if (((ushort)pCVar7->meshIndex != 0) && ((pCVar7->flags & 1) != 0)) {
          DrawMeshCharaShadow__8CMapMeshFUsUs
                    (*(CMapMesh **)((int)octTree->field2_0x8 + 0xc),
                     (uint)(ushort)pCVar7->_meshIndex2,(uint)(ushort)pCVar7->meshIndex);
        }
        iVar12 = 0;
        do {
          pCVar6 = pCVar7->children[0];
          if (pCVar6 == (COctNode *)0x0) break;
          if (((ushort)pCVar6->meshIndex != 0) && ((pCVar6->flags & 1) != 0)) {
            DrawMeshCharaShadow__8CMapMeshFUsUs
                      (*(CMapMesh **)((int)octTree->field2_0x8 + 0xc),
                       (uint)(ushort)pCVar6->_meshIndex2,(uint)(ushort)pCVar6->meshIndex);
          }
          iVar11 = 0;
          do {
            pCVar5 = pCVar6->children[0];
            if (pCVar5 == (COctNode *)0x0) break;
            if (((ushort)pCVar5->meshIndex != 0) && ((pCVar5->flags & 1) != 0)) {
              DrawMeshCharaShadow__8CMapMeshFUsUs
                        (*(CMapMesh **)((int)octTree->field2_0x8 + 0xc),
                         (uint)(ushort)pCVar5->_meshIndex2,(uint)(ushort)pCVar5->meshIndex);
            }
            iVar10 = 0;
            do {
              pCVar4 = pCVar5->children[0];
              if (pCVar4 == (COctNode *)0x0) break;
              if (((ushort)pCVar4->meshIndex != 0) && ((pCVar4->flags & 1) != 0)) {
                DrawMeshCharaShadow__8CMapMeshFUsUs
                          (*(CMapMesh **)((int)octTree->field2_0x8 + 0xc),
                           (uint)(ushort)pCVar4->_meshIndex2,(uint)(ushort)pCVar4->meshIndex);
              }
              iVar9 = 0;
              do {
                if (pCVar4->children[0] == (COctNode *)0x0) break;
                DrawCharaShadowTypeMeshFlag_r__8COctTreeFP8COctNode(octTree,pCVar4->children[0]);
                iVar9 = iVar9 + 1;
                pCVar4 = (COctNode *)&(pCVar4->boundsMin).y;
              } while (iVar9 < 8);
              iVar10 = iVar10 + 1;
              pCVar5 = (COctNode *)&(pCVar5->boundsMin).y;
            } while (iVar10 < 8);
            iVar11 = iVar11 + 1;
            pCVar6 = (COctNode *)&(pCVar6->boundsMin).y;
          } while (iVar11 < 8);
          iVar12 = iVar12 + 1;
          pCVar7 = (COctNode *)&(pCVar7->boundsMin).y;
        } while (iVar12 < 8);
        iVar13 = iVar13 + 1;
        pCVar8 = (COctNode *)&(pCVar8->boundsMin).y;
      } while (iVar13 < 8);
      iVar2 = iVar2 + 1;
      pCVar3 = (COctNode *)&(pCVar3->boundsMin).y;
    } while (iVar2 < 8);
    iVar1 = iVar1 + 1;
    octNode = (COctNode *)&(octNode->boundsMin).y;
    if (7 < iVar1) {
      return;
    }
  } while( true );
}

