// Function: CheckHitCylinder_r__8COctTreeFP8COctNode
// Entry: 8002cef0
// Size: 1004 bytes

undefined4 CheckHitCylinder_r__8COctTreeFP8COctNode(COctTree *octTree,COctNode *octNode)

{
  float fVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  COctNode *pCVar9;
  COctNode *pCVar10;
  
  bVar2 = false;
  bVar4 = false;
  fVar1 = (octNode->boundsMin).x;
  if (s_cyl.m_top.z <= fVar1) {
    if (fVar1 <= s_cyl.m_top.z) {
      bVar3 = true;
    }
    else {
      bVar3 = fVar1 <= s_cyl.m_direction2.z;
    }
  }
  else {
    bVar3 = s_cyl.m_top.z <= (octNode->boundsMax).x;
  }
  if (bVar3) {
    fVar1 = (octNode->boundsMin).y;
    if (s_cyl.m_direction2.x <= fVar1) {
      if (fVar1 <= s_cyl.m_direction2.x) {
        bVar3 = true;
      }
      else {
        bVar3 = fVar1 <= s_cyl.m_radius2;
      }
    }
    else {
      bVar3 = s_cyl.m_direction2.x <= (octNode->boundsMax).y;
    }
    if (bVar3) {
      bVar4 = true;
    }
  }
  if (bVar4) {
    fVar1 = (octNode->boundsMin).z;
    if (s_cyl.m_direction2.y <= fVar1) {
      if (fVar1 <= s_cyl.m_direction2.y) {
        bVar4 = true;
      }
      else {
        bVar4 = fVar1 <= s_cyl.m_height2;
      }
    }
    else {
      bVar4 = s_cyl.m_direction2.y <= (octNode->boundsMax).z;
    }
    if (bVar4) {
      bVar2 = true;
    }
  }
  if (bVar2) {
    if (((ushort)octNode->meshIndex != 0) &&
       (iVar5 = CheckHitCylinder__7CMapHitFP12CMapCylinderP3VecUsUsUl
                          (*(CMapHit **)((int)octTree->field2_0x8 + 0xc),&s_cyl,&s_mvec,
                           (uint)(ushort)octNode->_meshIndex2,(uint)(ushort)octNode->meshIndex,
                           DAT_8032ecb0), iVar5 != 0)) {
      return 1;
    }
    iVar5 = 0;
    do {
      pCVar10 = octNode->children[0];
      if (pCVar10 == (COctNode *)0x0) {
        return 0;
      }
      fVar1 = (pCVar10->boundsMin).x;
      bVar2 = false;
      bVar4 = false;
      if (s_cyl.m_top.z <= fVar1) {
        if (fVar1 <= s_cyl.m_top.z) {
          bVar3 = true;
        }
        else {
          bVar3 = fVar1 <= s_cyl.m_direction2.z;
        }
      }
      else {
        bVar3 = s_cyl.m_top.z <= (pCVar10->boundsMax).x;
      }
      if (bVar3) {
        fVar1 = (pCVar10->boundsMin).y;
        if (s_cyl.m_direction2.x <= fVar1) {
          if (fVar1 <= s_cyl.m_direction2.x) {
            bVar3 = true;
          }
          else {
            bVar3 = fVar1 <= s_cyl.m_radius2;
          }
        }
        else {
          bVar3 = s_cyl.m_direction2.x <= (pCVar10->boundsMax).y;
        }
        if (bVar3) {
          bVar4 = true;
        }
      }
      if (bVar4) {
        fVar1 = (pCVar10->boundsMin).z;
        if (s_cyl.m_direction2.y <= fVar1) {
          if (fVar1 <= s_cyl.m_direction2.y) {
            bVar4 = true;
          }
          else {
            bVar4 = fVar1 <= s_cyl.m_height2;
          }
        }
        else {
          bVar4 = s_cyl.m_direction2.y <= (pCVar10->boundsMax).z;
        }
        if (bVar4) {
          bVar2 = true;
        }
      }
      if (bVar2) {
        if (((ushort)pCVar10->meshIndex == 0) ||
           (iVar6 = CheckHitCylinder__7CMapHitFP12CMapCylinderP3VecUsUsUl
                              (*(CMapHit **)((int)octTree->field2_0x8 + 0xc),&s_cyl,&s_mvec,
                               (uint)(ushort)pCVar10->_meshIndex2,(uint)(ushort)pCVar10->meshIndex,
                               DAT_8032ecb0), iVar6 == 0)) {
          iVar6 = 0;
          do {
            pCVar9 = pCVar10->children[0];
            if (pCVar9 == (COctNode *)0x0) break;
            iVar7 = CheckCross__6CBoundFR6CBound(pCVar9,0x80245730);
            if (iVar7 == 0) {
LAB_8002d27c:
              bVar4 = false;
            }
            else {
              if (((ushort)pCVar9->meshIndex == 0) ||
                 (iVar7 = CheckHitCylinder__7CMapHitFP12CMapCylinderP3VecUsUsUl
                                    (*(CMapHit **)((int)octTree->field2_0x8 + 0xc),&s_cyl,&s_mvec,
                                     (uint)(ushort)pCVar9->_meshIndex2,
                                     (uint)(ushort)pCVar9->meshIndex,DAT_8032ecb0), iVar7 == 0)) {
                iVar7 = 0;
                do {
                  if (pCVar9->children[0] == (COctNode *)0x0) break;
                  iVar8 = CheckHitCylinder_r__8COctTreeFP8COctNode(octTree,pCVar9->children[0]);
                  if (iVar8 != 0) {
                    bVar4 = true;
                    goto LAB_8002d280;
                  }
                  iVar7 = iVar7 + 1;
                  pCVar9 = (COctNode *)&(pCVar9->boundsMin).y;
                } while (iVar7 < 8);
                goto LAB_8002d27c;
              }
              bVar4 = true;
            }
LAB_8002d280:
            if (bVar4) {
              bVar4 = true;
              goto LAB_8002d2a4;
            }
            iVar6 = iVar6 + 1;
            pCVar10 = (COctNode *)&(pCVar10->boundsMin).y;
          } while (iVar6 < 8);
          goto LAB_8002d2a0;
        }
        bVar4 = true;
      }
      else {
LAB_8002d2a0:
        bVar4 = false;
      }
LAB_8002d2a4:
      if (bVar4) {
        return 1;
      }
      iVar5 = iVar5 + 1;
      octNode = (COctNode *)&(octNode->boundsMin).y;
    } while (iVar5 < 8);
  }
  return 0;
}

