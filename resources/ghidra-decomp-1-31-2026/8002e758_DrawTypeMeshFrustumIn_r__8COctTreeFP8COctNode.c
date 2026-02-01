// Function: DrawTypeMeshFrustumIn_r__8COctTreeFP8COctNode
// Entry: 8002e758
// Size: 572 bytes

void DrawTypeMeshFrustumIn_r__8COctTreeFP8COctNode(COctTree *octTree,COctNode *octNode)

{
  COctNode *pCVar1;
  COctNode *pCVar2;
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
  int iVar14;
  int iVar15;
  int iVar16;
  int local_58;
  
  if (octNode->meshIndex != 0) {
    octNode->flags = octNode->flags | 1;
  }
  local_58 = 0;
  do {
    pCVar8 = octNode->children[0];
    if (pCVar8 == (COctNode *)0x0) {
      return;
    }
    if (pCVar8->meshIndex != 0) {
      pCVar8->flags = pCVar8->flags | 1;
    }
    iVar16 = 0;
    do {
      pCVar7 = pCVar8->children[0];
      if (pCVar7 == (COctNode *)0x0) break;
      if (pCVar7->meshIndex != 0) {
        pCVar7->flags = pCVar7->flags | 1;
      }
      iVar15 = 0;
      do {
        pCVar6 = pCVar7->children[0];
        if (pCVar6 == (COctNode *)0x0) break;
        if (pCVar6->meshIndex != 0) {
          pCVar6->flags = pCVar6->flags | 1;
        }
        iVar14 = 0;
        do {
          pCVar5 = pCVar6->children[0];
          if (pCVar5 == (COctNode *)0x0) break;
          if (pCVar5->meshIndex != 0) {
            pCVar5->flags = pCVar5->flags | 1;
          }
          iVar13 = 0;
          do {
            pCVar4 = pCVar5->children[0];
            if (pCVar4 == (COctNode *)0x0) break;
            if (pCVar4->meshIndex != 0) {
              pCVar4->flags = pCVar4->flags | 1;
            }
            iVar12 = 0;
            do {
              pCVar3 = pCVar4->children[0];
              if (pCVar3 == (COctNode *)0x0) break;
              if (pCVar3->meshIndex != 0) {
                pCVar3->flags = pCVar3->flags | 1;
              }
              iVar11 = 0;
              do {
                pCVar2 = pCVar3->children[0];
                if (pCVar2 == (COctNode *)0x0) break;
                if (pCVar2->meshIndex != 0) {
                  pCVar2->flags = pCVar2->flags | 1;
                }
                iVar10 = 0;
                do {
                  pCVar1 = pCVar2->children[0];
                  if (pCVar1 == (COctNode *)0x0) break;
                  if (pCVar1->meshIndex != 0) {
                    pCVar1->flags = pCVar1->flags | 1;
                  }
                  iVar9 = 0;
                  do {
                    if (pCVar1->children[0] == (COctNode *)0x0) break;
                    DrawTypeMeshFrustumIn_r__8COctTreeFP8COctNode(octTree,pCVar1->children[0]);
                    iVar9 = iVar9 + 1;
                    pCVar1 = (COctNode *)&(pCVar1->boundsMin).y;
                  } while (iVar9 < 8);
                  iVar10 = iVar10 + 1;
                  pCVar2 = (COctNode *)&(pCVar2->boundsMin).y;
                } while (iVar10 < 8);
                iVar11 = iVar11 + 1;
                pCVar3 = (COctNode *)&(pCVar3->boundsMin).y;
              } while (iVar11 < 8);
              iVar12 = iVar12 + 1;
              pCVar4 = (COctNode *)&(pCVar4->boundsMin).y;
            } while (iVar12 < 8);
            iVar13 = iVar13 + 1;
            pCVar5 = (COctNode *)&(pCVar5->boundsMin).y;
          } while (iVar13 < 8);
          iVar14 = iVar14 + 1;
          pCVar6 = (COctNode *)&(pCVar6->boundsMin).y;
        } while (iVar14 < 8);
        iVar15 = iVar15 + 1;
        pCVar7 = (COctNode *)&(pCVar7->boundsMin).y;
      } while (iVar15 < 8);
      iVar16 = iVar16 + 1;
      pCVar8 = (COctNode *)&(pCVar8->boundsMin).y;
    } while (iVar16 < 8);
    octNode = (COctNode *)&(octNode->boundsMin).y;
    local_58 = local_58 + 1;
    if (7 < local_58) {
      return;
    }
  } while( true );
}

