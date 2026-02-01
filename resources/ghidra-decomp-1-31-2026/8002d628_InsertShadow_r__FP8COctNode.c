// Function: InsertShadow_r__FP8COctNode
// Entry: 8002d628
// Size: 980 bytes

void InsertShadow_r__FP8COctNode(COctNode *octNode)

{
  float fVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  int iVar5;
  uint uVar6;
  COctNode *pCVar7;
  int iVar8;
  COctNode *pCVar9;
  int iVar10;
  
  bVar2 = false;
  bVar4 = false;
  fVar1 = (octNode->boundsMin).x;
  if (s_bound[0].x <= fVar1) {
    if (fVar1 <= s_bound[0].x) {
      bVar3 = true;
    }
    else {
      bVar3 = fVar1 <= s_bound[1].x;
    }
  }
  else {
    bVar3 = s_bound[0].x <= (octNode->boundsMax).x;
  }
  if (bVar3) {
    fVar1 = (octNode->boundsMin).y;
    if (s_bound[0].y <= fVar1) {
      if (fVar1 <= s_bound[0].y) {
        bVar3 = true;
      }
      else {
        bVar3 = fVar1 <= s_bound[1].y;
      }
    }
    else {
      bVar3 = s_bound[0].y <= (octNode->boundsMax).y;
    }
    if (bVar3) {
      bVar4 = true;
    }
  }
  if (bVar4) {
    fVar1 = (octNode->boundsMin).z;
    if (s_bound[0].z <= fVar1) {
      if (fVar1 <= s_bound[0].z) {
        bVar4 = true;
      }
      else {
        bVar4 = fVar1 <= s_bound[1].z;
      }
    }
    else {
      bVar4 = s_bound[0].z <= (octNode->boundsMax).z;
    }
    if (bVar4) {
      bVar2 = true;
    }
  }
  if (bVar2) {
    if ((2 < DAT_8032eca8) && (octNode->meshIndex != 0)) {
      uVar6 = DAT_8032eca4 >> 3 & 0x1ffffffc;
      *(uint *)((int)octNode->children + uVar6 + 0x2c) =
           *(uint *)((int)octNode->children + uVar6 + 0x2c) | 1 << (DAT_8032eca4 & 0x1f);
    }
    iVar8 = 0;
    do {
      if (octNode->children[0] == (COctNode *)0x0) {
        return;
      }
      bVar2 = false;
      bVar4 = false;
      DAT_8032eca8 = DAT_8032eca8 + 1;
      pCVar9 = octNode->children[0];
      fVar1 = (pCVar9->boundsMin).x;
      if (s_bound[0].x <= fVar1) {
        if (fVar1 <= s_bound[0].x) {
          bVar3 = true;
        }
        else {
          bVar3 = fVar1 <= s_bound[1].x;
        }
      }
      else {
        bVar3 = s_bound[0].x <= (pCVar9->boundsMax).x;
      }
      if (bVar3) {
        fVar1 = (pCVar9->boundsMin).y;
        if (s_bound[0].y <= fVar1) {
          if (fVar1 <= s_bound[0].y) {
            bVar3 = true;
          }
          else {
            bVar3 = fVar1 <= s_bound[1].y;
          }
        }
        else {
          bVar3 = s_bound[0].y <= (pCVar9->boundsMax).y;
        }
        if (bVar3) {
          bVar4 = true;
        }
      }
      if (bVar4) {
        fVar1 = (pCVar9->boundsMin).z;
        if (s_bound[0].z <= fVar1) {
          if (fVar1 <= s_bound[0].z) {
            bVar4 = true;
          }
          else {
            bVar4 = fVar1 <= s_bound[1].z;
          }
        }
        else {
          bVar4 = s_bound[0].z <= (pCVar9->boundsMax).z;
        }
        if (bVar4) {
          bVar2 = true;
        }
      }
      if (bVar2) {
        if ((2 < DAT_8032eca8) && (pCVar9->meshIndex != 0)) {
          uVar6 = DAT_8032eca4 >> 3 & 0x1ffffffc;
          *(uint *)((int)pCVar9->children + uVar6 + 0x2c) =
               *(uint *)((int)pCVar9->children + uVar6 + 0x2c) | 1 << (DAT_8032eca4 & 0x1f);
        }
        iVar10 = 0;
        do {
          if (pCVar9->children[0] == (COctNode *)0x0) break;
          DAT_8032eca8 = DAT_8032eca8 + 1;
          pCVar7 = pCVar9->children[0];
          iVar5 = CheckCross__6CBoundFR6CBound(pCVar7,s_bound);
          if (iVar5 != 0) {
            if ((2 < DAT_8032eca8) && (pCVar7->meshIndex != 0)) {
              setbit32__FPUlUl(&pCVar7->ptrB,DAT_8032eca4);
            }
            iVar5 = 0;
            do {
              if (pCVar7->children[0] == (COctNode *)0x0) break;
              DAT_8032eca8 = DAT_8032eca8 + 1;
              InsertShadow_r__FP8COctNode(pCVar7->children[0]);
              iVar5 = iVar5 + 1;
              pCVar7 = (COctNode *)&(pCVar7->boundsMin).y;
              DAT_8032eca8 = DAT_8032eca8 + -1;
            } while (iVar5 < 8);
          }
          iVar10 = iVar10 + 1;
          pCVar9 = (COctNode *)&(pCVar9->boundsMin).y;
          DAT_8032eca8 = DAT_8032eca8 + -1;
        } while (iVar10 < 8);
      }
      iVar8 = iVar8 + 1;
      octNode = (COctNode *)&(octNode->boundsMin).y;
      DAT_8032eca8 = DAT_8032eca8 + -1;
    } while (iVar8 < 8);
  }
  return;
}

