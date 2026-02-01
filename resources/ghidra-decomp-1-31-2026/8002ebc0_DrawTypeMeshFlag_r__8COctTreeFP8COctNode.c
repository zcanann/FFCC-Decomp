// Function: DrawTypeMeshFlag_r__8COctTreeFP8COctNode
// Entry: 8002ebc0
// Size: 868 bytes

void DrawTypeMeshFlag_r__8COctTreeFP8COctNode(COctTree *octTree,COctNode *octNode)

{
  int iVar1;
  int iVar2;
  COctNode *pCVar3;
  COctNode *pCVar4;
  int iVar5;
  
  if ((octNode->meshIndex != 0) && ((octNode->flags & 1) != 0)) {
    MaterialMan._72_4_ = 0xace0f;
    MaterialMan._68_4_ = 0xffffffff;
    MaterialMan._76_1_ = 0xff;
    MaterialMan._296_4_ = 0;
    MaterialMan._284_4_ = 0;
    MaterialMan._300_4_ = 0x1e;
    MaterialMan._288_4_ = 0x1e;
    MaterialMan._304_4_ = 0;
    MaterialMan._292_4_ = 0;
    MaterialMan._517_1_ = 0xff;
    MaterialMan._518_1_ = 0xff;
    MaterialMan._88_4_ = 0;
    MaterialMan._92_4_ = 0;
    MaterialMan._520_1_ = 0;
    if (*(char *)((int)octTree->field2_0x8 + 0x22) != '\0') {
      SetFullScreenShadow__10CCameraPcsFPA4_fl(&CameraPcs,(int)octTree->field2_0x8 + 0xb8,0);
    }
    if (*(int *)((int)octTree->field2_0x8 + 0x3c) != 0) {
      SetShadowBit32__12CMaterialManFQ210CMapShadow6TARGETPUlPA4_f
                (&MaterialMan,1,&octNode->ptrB,(int)octTree->field2_0x8 + 0xb8);
    }
    MaterialMan._296_4_ = MaterialMan._284_4_;
    MaterialMan._300_4_ = MaterialMan._288_4_;
    MaterialMan._304_4_ = MaterialMan._292_4_;
    MaterialMan._64_4_ = MaterialMan._72_4_;
    SetBit32__9CLightPcsFQ29CLightPcs6TARGETPUl(&LightPcs,1,&octNode->ptrA);
    SetDrawEnv__7CMapObjFv(octTree->field2_0x8);
    DrawMesh__8CMapMeshFUsUs
              (*(CMapMesh **)((int)octTree->field2_0x8 + 0xc),(uint)(ushort)octNode->_meshIndex2,
               (uint)(ushort)octNode->meshIndex);
  }
  iVar2 = 0;
  do {
    pCVar4 = octNode->children[0];
    if (pCVar4 == (COctNode *)0x0) {
      return;
    }
    if ((pCVar4->meshIndex != 0) && ((pCVar4->flags & 1) != 0)) {
      MaterialMan._72_4_ = 0xace0f;
      MaterialMan._68_4_ = 0xffffffff;
      MaterialMan._76_1_ = 0xff;
      MaterialMan._296_4_ = 0;
      MaterialMan._284_4_ = 0;
      MaterialMan._300_4_ = 0x1e;
      MaterialMan._288_4_ = 0x1e;
      MaterialMan._304_4_ = 0;
      MaterialMan._292_4_ = 0;
      MaterialMan._517_1_ = 0xff;
      MaterialMan._518_1_ = 0xff;
      MaterialMan._88_4_ = 0;
      MaterialMan._92_4_ = 0;
      MaterialMan._520_1_ = 0;
      if (*(char *)((int)octTree->field2_0x8 + 0x22) != '\0') {
        SetFullScreenShadow__10CCameraPcsFPA4_fl(&CameraPcs,(int)octTree->field2_0x8 + 0xb8,0);
      }
      if (*(int *)((int)octTree->field2_0x8 + 0x3c) != 0) {
        SetShadowBit32__12CMaterialManFQ210CMapShadow6TARGETPUlPA4_f
                  (&MaterialMan,1,&pCVar4->ptrB,(int)octTree->field2_0x8 + 0xb8);
      }
      MaterialMan._296_4_ = MaterialMan._284_4_;
      MaterialMan._300_4_ = MaterialMan._288_4_;
      MaterialMan._304_4_ = MaterialMan._292_4_;
      MaterialMan._64_4_ = MaterialMan._72_4_;
      SetBit32__9CLightPcsFQ29CLightPcs6TARGETPUl(&LightPcs,1,&pCVar4->ptrA);
      SetDrawEnv__7CMapObjFv(octTree->field2_0x8);
      DrawMesh__8CMapMeshFUsUs
                (*(CMapMesh **)((int)octTree->field2_0x8 + 0xc),(uint)(ushort)pCVar4->_meshIndex2,
                 (uint)(ushort)pCVar4->meshIndex);
    }
    iVar5 = 0;
    do {
      pCVar3 = pCVar4->children[0];
      if (pCVar3 == (COctNode *)0x0) break;
      if ((pCVar3->meshIndex != 0) && ((pCVar3->flags & 1) != 0)) {
        InitEnv__12CMaterialManFv(&MaterialMan);
        if (*(char *)((int)octTree->field2_0x8 + 0x22) != '\0') {
          SetFullScreenShadow__10CCameraPcsFPA4_fl(&CameraPcs,(int)octTree->field2_0x8 + 0xb8,0);
        }
        if (*(int *)((int)octTree->field2_0x8 + 0x3c) != 0) {
          SetShadowBit32__12CMaterialManFQ210CMapShadow6TARGETPUlPA4_f
                    (&MaterialMan,1,&pCVar3->ptrB,(int)octTree->field2_0x8 + 0xb8);
        }
        LockEnv__12CMaterialManFv(&MaterialMan);
        SetBit32__9CLightPcsFQ29CLightPcs6TARGETPUl(&LightPcs,1,&pCVar3->ptrA);
        SetDrawEnv__7CMapObjFv(octTree->field2_0x8);
        DrawMesh__8CMapMeshFUsUs
                  (*(CMapMesh **)((int)octTree->field2_0x8 + 0xc),(uint)(ushort)pCVar3->_meshIndex2,
                   (uint)(ushort)pCVar3->meshIndex);
      }
      iVar1 = 0;
      do {
        if (pCVar3->children[0] == (COctNode *)0x0) break;
        DrawTypeMeshFlag_r__8COctTreeFP8COctNode(octTree,pCVar3->children[0]);
        iVar1 = iVar1 + 1;
        pCVar3 = (COctNode *)&(pCVar3->boundsMin).y;
      } while (iVar1 < 8);
      iVar5 = iVar5 + 1;
      pCVar4 = (COctNode *)&(pCVar4->boundsMin).y;
    } while (iVar5 < 8);
    iVar2 = iVar2 + 1;
    octNode = (COctNode *)&(octNode->boundsMin).y;
    if (7 < iVar2) {
      return;
    }
  } while( true );
}

