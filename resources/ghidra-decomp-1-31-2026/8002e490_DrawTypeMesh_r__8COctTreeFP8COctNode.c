// Function: DrawTypeMesh_r__8COctTreeFP8COctNode
// Entry: 8002e490
// Size: 712 bytes

/* WARNING: Removing unreachable block (ram,0x8002e73c) */
/* WARNING: Removing unreachable block (ram,0x8002e734) */
/* WARNING: Removing unreachable block (ram,0x8002e4a8) */
/* WARNING: Removing unreachable block (ram,0x8002e4a0) */

void DrawTypeMesh_r__8COctTreeFP8COctNode(COctTree *octTree,COctNode *octNode)

{
  float fVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  Vec local_58;
  Vec local_4c;
  
  fVar1 = (octTree->field51_0x3c).x;
  if (((((octNode->boundsMax).x < fVar1) ||
       (fVar2 = (octTree->field51_0x3c).y, (octNode->boundsMax).y < fVar2)) ||
      (fVar3 = (octTree->field51_0x3c).z, (octNode->boundsMax).z < fVar3)) ||
     (((fVar1 < (octNode->boundsMin).x || (fVar2 < (octNode->boundsMin).y)) ||
      (fVar3 < (octNode->boundsMin).z)))) {
    dVar12 = (double)FLOAT_8032f968;
    uVar10 = 0xf;
    dVar13 = (double)FLOAT_8032f964;
    uVar9 = 0;
    iVar8 = 0;
    iVar6 = 0;
    do {
      if (iVar6 == 0) {
        local_4c.x = (octNode->boundsMin).x;
      }
      else {
        local_4c.x = (octNode->boundsMax).x;
      }
      iVar7 = 0;
      do {
        if (iVar7 == 0) {
          local_4c.y = (octNode->boundsMin).y;
        }
        else {
          local_4c.y = (octNode->boundsMax).y;
        }
        iVar5 = 0;
        do {
          if (iVar5 == 0) {
            local_4c.z = (octNode->boundsMin).z;
          }
          else {
            local_4c.z = (octNode->boundsMax).z;
          }
          PSMTXMultVec((Mtx *)&octTree->field_0xc,&local_4c,&local_58);
          dVar11 = (double)local_58.z;
          if (dVar12 < dVar11) {
            dVar12 = dVar11;
          }
          if (dVar11 <= dVar13) {
            if ((double)local_58.x <= -dVar11) {
              if (dVar11 <= (double)local_58.x) {
                uVar4 = 0;
              }
              else {
                uVar4 = 2;
              }
            }
            else {
              uVar4 = 1;
            }
            if ((double)local_58.y <= -dVar11) {
              if ((double)local_58.y < dVar11) {
                uVar4 = uVar4 | 8;
              }
            }
            else {
              uVar4 = uVar4 | 4;
            }
          }
          else {
            iVar8 = iVar8 + 1;
            if ((double)local_58.x <= -dVar11) {
              if (dVar11 <= (double)local_58.x) {
                uVar4 = 0x10;
              }
              else {
                uVar4 = 0x12;
              }
            }
            else {
              uVar4 = 0x11;
            }
            if ((double)local_58.y <= -dVar11) {
              if ((double)local_58.y < dVar11) {
                uVar4 = uVar4 | 0x18;
              }
            }
            else {
              uVar4 = uVar4 | 0x14;
            }
          }
          iVar5 = iVar5 + 1;
          uVar10 = uVar10 & uVar4;
          uVar9 = uVar9 | uVar4;
        } while (iVar5 < 2);
        iVar7 = iVar7 + 1;
      } while (iVar7 < 2);
      iVar6 = iVar6 + 1;
    } while (iVar6 < 2);
    if (7 < iVar8) {
      return;
    }
    if (dVar12 < (double)MapMng.drawRangeOctTree) {
      return;
    }
    if (uVar10 != 0) {
      return;
    }
  }
  else {
    uVar9 = 0xf;
  }
  if (octNode->meshIndex != 0) {
    octNode->flags = octNode->flags | 1;
  }
  if (uVar9 == 0) {
    iVar6 = 0;
    do {
      if (octNode->children[0] == (COctNode *)0x0) {
        return;
      }
      DrawTypeMeshFrustumIn_r__8COctTreeFP8COctNode(octTree,octNode->children[0]);
      iVar6 = iVar6 + 1;
      octNode = (COctNode *)&(octNode->boundsMin).y;
    } while (iVar6 < 8);
  }
  else {
    iVar6 = 0;
    do {
      if (octNode->children[0] == (COctNode *)0x0) {
        return;
      }
      DrawTypeMesh_r__8COctTreeFP8COctNode(octTree,octNode->children[0]);
      iVar6 = iVar6 + 1;
      octNode = (COctNode *)&(octNode->boundsMin).y;
    } while (iVar6 < 8);
  }
  return;
}

