// Function: InsertLight_r__FP8COctNode
// Entry: 8002dca8
// Size: 860 bytes

void InsertLight_r__FP8COctNode(COctNode *octNode)

{
  float fVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  int iVar5;
  uint uVar6;
  COctNode *pCVar7;
  int iVar8;
  int iVar9;
  COctNode *pCVar10;
  
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
    if (octNode->meshIndex != 0) {
      uVar6 = DAT_8032eca0 >> 3 & 0x1ffffffc;
      *(uint *)((int)octNode->children + uVar6 + 0x28) =
           *(uint *)((int)octNode->children + uVar6 + 0x28) | 1 << (DAT_8032eca0 & 0x1f);
    }
    iVar9 = 0;
    do {
      pCVar10 = octNode->children[0];
      if (pCVar10 == (COctNode *)0x0) {
        return;
      }
      fVar1 = (pCVar10->boundsMin).x;
      bVar2 = false;
      bVar4 = false;
      if (s_bound[0].x <= fVar1) {
        if (fVar1 <= s_bound[0].x) {
          bVar3 = true;
        }
        else {
          bVar3 = fVar1 <= s_bound[1].x;
        }
      }
      else {
        bVar3 = s_bound[0].x <= (pCVar10->boundsMax).x;
      }
      if (bVar3) {
        fVar1 = (pCVar10->boundsMin).y;
        if (s_bound[0].y <= fVar1) {
          if (fVar1 <= s_bound[0].y) {
            bVar3 = true;
          }
          else {
            bVar3 = fVar1 <= s_bound[1].y;
          }
        }
        else {
          bVar3 = s_bound[0].y <= (pCVar10->boundsMax).y;
        }
        if (bVar3) {
          bVar4 = true;
        }
      }
      if (bVar4) {
        fVar1 = (pCVar10->boundsMin).z;
        if (s_bound[0].z <= fVar1) {
          if (fVar1 <= s_bound[0].z) {
            bVar4 = true;
          }
          else {
            bVar4 = fVar1 <= s_bound[1].z;
          }
        }
        else {
          bVar4 = s_bound[0].z <= (pCVar10->boundsMax).z;
        }
        if (bVar4) {
          bVar2 = true;
        }
      }
      if (bVar2) {
        if (pCVar10->meshIndex != 0) {
          uVar6 = DAT_8032eca0 >> 3 & 0x1ffffffc;
          *(uint *)((int)pCVar10->children + uVar6 + 0x28) =
               *(uint *)((int)pCVar10->children + uVar6 + 0x28) | 1 << (DAT_8032eca0 & 0x1f);
        }
        iVar8 = 0;
        do {
          pCVar7 = pCVar10->children[0];
          if (pCVar7 == (COctNode *)0x0) break;
          iVar5 = CheckCross__6CBoundFR6CBound(pCVar7,s_bound);
          if (iVar5 != 0) {
            if (pCVar7->meshIndex != 0) {
              setbit32__FPUlUl(&pCVar7->ptrA,DAT_8032eca0);
            }
            iVar5 = 0;
            do {
              if (pCVar7->children[0] == (COctNode *)0x0) break;
              InsertLight_r__FP8COctNode(pCVar7->children[0]);
              iVar5 = iVar5 + 1;
              pCVar7 = (COctNode *)&(pCVar7->boundsMin).y;
            } while (iVar5 < 8);
          }
          iVar8 = iVar8 + 1;
          pCVar10 = (COctNode *)&(pCVar10->boundsMin).y;
        } while (iVar8 < 8);
      }
      iVar9 = iVar9 + 1;
      octNode = (COctNode *)&(octNode->boundsMin).y;
    } while (iVar9 < 8);
  }
  return;
}

