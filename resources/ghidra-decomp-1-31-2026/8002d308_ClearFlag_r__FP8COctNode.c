// Function: ClearFlag_r__FP8COctNode
// Entry: 8002d308
// Size: 584 bytes

void ClearFlag_r__FP8COctNode(COctNode *octNode)

{
  int iVar1;
  int iVar2;
  COctNode *pCVar3;
  int iVar4;
  COctNode *pCVar5;
  int iVar6;
  int iVar7;
  COctNode *pCVar8;
  COctNode *pCVar9;
  COctNode *pCVar10;
  COctNode *pCVar11;
  COctNode *pCVar12;
  COctNode *pCVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  
  if (octNode->meshIndex != 0) {
    octNode->flags = octNode->flags & DAT_8032ecac;
  }
  iVar1 = 0;
  do {
    pCVar3 = octNode->children[0];
    if (pCVar3 == (COctNode *)0x0) {
      return;
    }
    if (pCVar3->meshIndex != 0) {
      pCVar3->flags = pCVar3->flags & DAT_8032ecac;
    }
    iVar2 = 0;
    do {
      pCVar5 = pCVar3->children[0];
      if (pCVar5 == (COctNode *)0x0) break;
      if (pCVar5->meshIndex != 0) {
        pCVar5->flags = pCVar5->flags & DAT_8032ecac;
      }
      iVar4 = 0;
      do {
        pCVar13 = pCVar5->children[0];
        if (pCVar13 == (COctNode *)0x0) break;
        if (pCVar13->meshIndex != 0) {
          pCVar13->flags = pCVar13->flags & DAT_8032ecac;
        }
        iVar6 = 0;
        do {
          pCVar12 = pCVar13->children[0];
          if (pCVar12 == (COctNode *)0x0) break;
          if (pCVar12->meshIndex != 0) {
            pCVar12->flags = pCVar12->flags & DAT_8032ecac;
          }
          iVar7 = 0;
          do {
            pCVar11 = pCVar12->children[0];
            if (pCVar11 == (COctNode *)0x0) break;
            if (pCVar11->meshIndex != 0) {
              pCVar11->flags = pCVar11->flags & DAT_8032ecac;
            }
            iVar17 = 0;
            do {
              pCVar10 = pCVar11->children[0];
              if (pCVar10 == (COctNode *)0x0) break;
              if (pCVar10->meshIndex != 0) {
                pCVar10->flags = pCVar10->flags & DAT_8032ecac;
              }
              iVar16 = 0;
              do {
                pCVar9 = pCVar10->children[0];
                if (pCVar9 == (COctNode *)0x0) break;
                if (pCVar9->meshIndex != 0) {
                  pCVar9->flags = pCVar9->flags & DAT_8032ecac;
                }
                iVar15 = 0;
                do {
                  pCVar8 = pCVar9->children[0];
                  if (pCVar8 == (COctNode *)0x0) break;
                  if (pCVar8->meshIndex != 0) {
                    pCVar8->flags = pCVar8->flags & DAT_8032ecac;
                  }
                  iVar14 = 0;
                  do {
                    if (pCVar8->children[0] == (COctNode *)0x0) break;
                    ClearFlag_r__FP8COctNode(pCVar8->children[0]);
                    iVar14 = iVar14 + 1;
                    pCVar8 = (COctNode *)&(pCVar8->boundsMin).y;
                  } while (iVar14 < 8);
                  iVar15 = iVar15 + 1;
                  pCVar9 = (COctNode *)&(pCVar9->boundsMin).y;
                } while (iVar15 < 8);
                iVar16 = iVar16 + 1;
                pCVar10 = (COctNode *)&(pCVar10->boundsMin).y;
              } while (iVar16 < 8);
              iVar17 = iVar17 + 1;
              pCVar11 = (COctNode *)&(pCVar11->boundsMin).y;
            } while (iVar17 < 8);
            iVar7 = iVar7 + 1;
            pCVar12 = (COctNode *)&(pCVar12->boundsMin).y;
          } while (iVar7 < 8);
          iVar6 = iVar6 + 1;
          pCVar13 = (COctNode *)&(pCVar13->boundsMin).y;
        } while (iVar6 < 8);
        iVar4 = iVar4 + 1;
        pCVar5 = (COctNode *)&(pCVar5->boundsMin).y;
      } while (iVar4 < 8);
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

