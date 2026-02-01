// Function: ClearShadow_r__FP8COctNode
// Entry: 8002da40
// Size: 408 bytes

void ClearShadow_r__FP8COctNode(COctNode *octNode)

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
  
  if (octNode->meshIndex != 0) {
    octNode->ptrB = (void *)0x0;
  }
  iVar1 = 0;
  do {
    pCVar8 = octNode->children[0];
    if (pCVar8 == (COctNode *)0x0) {
      return;
    }
    if (pCVar8->meshIndex != 0) {
      pCVar8->ptrB = (void *)0x0;
    }
    iVar2 = 0;
    do {
      pCVar7 = pCVar8->children[0];
      if (pCVar7 == (COctNode *)0x0) break;
      if (pCVar7->meshIndex != 0) {
        pCVar7->ptrB = (void *)0x0;
      }
      iVar13 = 0;
      do {
        pCVar6 = pCVar7->children[0];
        if (pCVar6 == (COctNode *)0x0) break;
        if (pCVar6->meshIndex != 0) {
          pCVar6->ptrB = (void *)0x0;
        }
        iVar12 = 0;
        do {
          pCVar5 = pCVar6->children[0];
          if (pCVar5 == (COctNode *)0x0) break;
          if (pCVar5->meshIndex != 0) {
            pCVar5->ptrB = (void *)0x0;
          }
          iVar11 = 0;
          do {
            pCVar4 = pCVar5->children[0];
            if (pCVar4 == (COctNode *)0x0) break;
            if (pCVar4->meshIndex != 0) {
              pCVar4->ptrB = (void *)0x0;
            }
            iVar10 = 0;
            do {
              pCVar3 = pCVar4->children[0];
              if (pCVar3 == (COctNode *)0x0) break;
              if (pCVar3->meshIndex != 0) {
                pCVar3->ptrB = (void *)0x0;
              }
              iVar9 = 0;
              do {
                if (pCVar3->children[0] == (COctNode *)0x0) break;
                ClearShadow_r__FP8COctNode(pCVar3->children[0]);
                iVar9 = iVar9 + 1;
                pCVar3 = (COctNode *)&(pCVar3->boundsMin).y;
              } while (iVar9 < 8);
              iVar10 = iVar10 + 1;
              pCVar4 = (COctNode *)&(pCVar4->boundsMin).y;
            } while (iVar10 < 8);
            iVar11 = iVar11 + 1;
            pCVar5 = (COctNode *)&(pCVar5->boundsMin).y;
          } while (iVar11 < 8);
          iVar12 = iVar12 + 1;
          pCVar6 = (COctNode *)&(pCVar6->boundsMin).y;
        } while (iVar12 < 8);
        iVar13 = iVar13 + 1;
        pCVar7 = (COctNode *)&(pCVar7->boundsMin).y;
      } while (iVar13 < 8);
      iVar2 = iVar2 + 1;
      pCVar8 = (COctNode *)&(pCVar8->boundsMin).y;
    } while (iVar2 < 8);
    iVar1 = iVar1 + 1;
    octNode = (COctNode *)&(octNode->boundsMin).y;
    if (7 < iVar1) {
      return;
    }
  } while( true );
}

