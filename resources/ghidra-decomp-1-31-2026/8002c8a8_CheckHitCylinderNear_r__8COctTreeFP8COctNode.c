// Function: CheckHitCylinderNear_r__8COctTreeFP8COctNode
// Entry: 8002c8a8
// Size: 896 bytes

void CheckHitCylinderNear_r__8COctTreeFP8COctNode(COctTree *octTree,COctNode *octNode)

{
  float fVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  int iVar5;
  COctNode *pCVar6;
  int iVar7;
  int iVar8;
  COctNode *pCVar9;
  
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
    if ((ushort)octNode->meshIndex != 0) {
      CheckHitCylinderNear__7CMapHitFP12CMapCylinderP3VecUsUsUl
                (*(undefined4 *)((int)octTree->field2_0x8 + 0xc),&s_cyl,&s_mvec,
                 (uint)(ushort)octNode->_meshIndex2,(uint)(ushort)octNode->meshIndex,DAT_8032ecb0);
    }
    iVar8 = 0;
    do {
      pCVar9 = octNode->children[0];
      if (pCVar9 == (COctNode *)0x0) {
        return;
      }
      fVar1 = (pCVar9->boundsMin).x;
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
        bVar3 = s_cyl.m_top.z <= (pCVar9->boundsMax).x;
      }
      if (bVar3) {
        fVar1 = (pCVar9->boundsMin).y;
        if (s_cyl.m_direction2.x <= fVar1) {
          if (fVar1 <= s_cyl.m_direction2.x) {
            bVar3 = true;
          }
          else {
            bVar3 = fVar1 <= s_cyl.m_radius2;
          }
        }
        else {
          bVar3 = s_cyl.m_direction2.x <= (pCVar9->boundsMax).y;
        }
        if (bVar3) {
          bVar4 = true;
        }
      }
      if (bVar4) {
        fVar1 = (pCVar9->boundsMin).z;
        if (s_cyl.m_direction2.y <= fVar1) {
          if (fVar1 <= s_cyl.m_direction2.y) {
            bVar4 = true;
          }
          else {
            bVar4 = fVar1 <= s_cyl.m_height2;
          }
        }
        else {
          bVar4 = s_cyl.m_direction2.y <= (pCVar9->boundsMax).z;
        }
        if (bVar4) {
          bVar2 = true;
        }
      }
      if (bVar2) {
        if ((ushort)pCVar9->meshIndex != 0) {
          CheckHitCylinderNear__7CMapHitFP12CMapCylinderP3VecUsUsUl
                    (*(undefined4 *)((int)octTree->field2_0x8 + 0xc),&s_cyl,&s_mvec,
                     (uint)(ushort)pCVar9->_meshIndex2,(uint)(ushort)pCVar9->meshIndex,DAT_8032ecb0)
          ;
        }
        iVar7 = 0;
        do {
          pCVar6 = pCVar9->children[0];
          if (pCVar6 == (COctNode *)0x0) break;
          iVar5 = CheckCross__6CBoundFR6CBound(pCVar6,0x80245730);
          if (iVar5 != 0) {
            if ((ushort)pCVar6->meshIndex != 0) {
              CheckHitCylinderNear__7CMapHitFP12CMapCylinderP3VecUsUsUl
                        (*(undefined4 *)((int)octTree->field2_0x8 + 0xc),&s_cyl,&s_mvec,
                         (uint)(ushort)pCVar6->_meshIndex2,(uint)(ushort)pCVar6->meshIndex,
                         DAT_8032ecb0);
            }
            iVar5 = 0;
            do {
              if (pCVar6->children[0] == (COctNode *)0x0) break;
              CheckHitCylinderNear_r__8COctTreeFP8COctNode(octTree,pCVar6->children[0]);
              iVar5 = iVar5 + 1;
              pCVar6 = (COctNode *)&(pCVar6->boundsMin).y;
            } while (iVar5 < 8);
          }
          iVar7 = iVar7 + 1;
          pCVar9 = (COctNode *)&(pCVar9->boundsMin).y;
        } while (iVar7 < 8);
      }
      iVar8 = iVar8 + 1;
      octNode = (COctNode *)&(octNode->boundsMin).y;
    } while (iVar8 < 8);
  }
  return;
}

