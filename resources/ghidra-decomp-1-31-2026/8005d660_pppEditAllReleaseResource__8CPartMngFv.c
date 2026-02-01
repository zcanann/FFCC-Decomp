// Function: pppEditAllReleaseResource__8CPartMngFv
// Entry: 8005d660
// Size: 628 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppEditAllReleaseResource__8CPartMngFv(CPartMng *partMng)

{
  CMaterialSet *pCVar1;
  CTextureSet *pCVar2;
  int iVar3;
  CMapMesh *mapMesh;
  int *piVar4;
  int iVar5;
  CPartMng *pCVar6;
  
  pCVar1 = partMng->m_materialSet;
  if (pCVar1 != (CMaterialSet *)0x0) {
    if (pCVar1 != (CMaterialSet *)0x0) {
      (**(code **)((int)pCVar1->vtable + 8))(pCVar1,1);
    }
    partMng->m_materialSet = (CMaterialSet *)0x0;
  }
  pCVar2 = partMng->m_textureSet;
  if (pCVar2 != (CTextureSet *)0x0) {
    if (pCVar2 != (CTextureSet *)0x0) {
      (**(code **)((int)pCVar2->vtable + 8))(pCVar2,1);
    }
    partMng->m_textureSet = (CTextureSet *)0x0;
  }
  iVar3 = 0;
  pCVar6 = partMng;
  do {
    if (pCVar6->m_unk0x1d4_0x3d3[0] != (void *)0x0) {
      __dl__FPv();
      pCVar6->m_unk0x1d4_0x3d3[0] = (void *)0x0;
    }
    iVar3 = iVar3 + 1;
    pCVar6 = (CPartMng *)&pCVar6->m_editCount;
  } while (iVar3 < 0x80);
  iVar3 = 0;
  pCVar6 = partMng;
  do {
    if (pCVar6->m_streamTextRaw[0] != (void *)0x0) {
      __dl__FPv();
      pCVar6->m_streamTextRaw[0] = (void *)0x0;
    }
    iVar3 = iVar3 + 1;
    pCVar6 = (CPartMng *)&pCVar6->m_editCount;
  } while (iVar3 < 0x80);
  iVar3 = 0;
  pCVar6 = partMng;
  do {
    if (pCVar6->m_pppProgOffsetReconstructionTable[0] != (long *)0x0) {
      __dl__FPv();
      pCVar6->m_pppProgOffsetReconstructionTable[0] = (long *)0x0;
    }
    iVar3 = iVar3 + 1;
    pCVar6 = (CPartMng *)&pCVar6->m_editCount;
  } while (iVar3 < 0x80);
  if (partMng->m_recvBuff != (void *)0x0) {
    __dla__FPv(partMng->m_recvBuff);
    partMng->m_recvBuff = (void *)0x0;
  }
  if (*(int *)(partMng->m_usbEdit + 4) != 0) {
    iVar5 = 0;
    iVar3 = 0;
    do {
      mapMesh = *(CMapMesh **)(*(int *)(partMng->m_usbEdit + 4) + iVar5);
      if (mapMesh != (CMapMesh *)0x0) {
        if (mapMesh != (CMapMesh *)0x0) {
          __dt__8CMapMeshFv(mapMesh,0);
          __dl__FPv(mapMesh);
        }
        *(undefined4 *)(*(int *)(partMng->m_usbEdit + 4) + iVar5) = 0;
      }
      iVar3 = iVar3 + 1;
      iVar5 = iVar5 + 4;
    } while (iVar3 < 0x88);
    if (*(int *)(partMng->m_usbEdit + 4) != 0) {
      __dl__FPv();
      partMng->m_usbEdit[4] = '\0';
      partMng->m_usbEdit[5] = '\0';
      partMng->m_usbEdit[6] = '\0';
      partMng->m_usbEdit[7] = '\0';
    }
  }
  if (*(int *)(partMng->m_usbEdit + 8) != 0) {
    iVar3 = 0;
    iVar5 = 0;
    do {
      piVar4 = *(int **)(*(int *)(partMng->m_usbEdit + 8) + iVar5);
      if (piVar4 != (int *)0x0) {
        if (piVar4 != (int *)0x0) {
          if (*piVar4 != 0) {
            __dl__FPv();
            *piVar4 = 0;
          }
          if (piVar4[1] != 0) {
            __dl__FPv();
            piVar4[1] = 0;
          }
          __dl__FPv(piVar4);
        }
        *(undefined4 *)(*(int *)(partMng->m_usbEdit + 8) + iVar5) = 0;
      }
      iVar3 = iVar3 + 1;
      iVar5 = iVar5 + 4;
    } while (iVar3 < 0x80);
    if (*(int *)(partMng->m_usbEdit + 8) != 0) {
      __dl__FPv();
      partMng->m_usbEdit[8] = '\0';
      partMng->m_usbEdit[9] = '\0';
      partMng->m_usbEdit[10] = '\0';
      partMng->m_usbEdit[0xb] = '\0';
    }
  }
  iVar3 = 0;
  pCVar6 = partMng;
  do {
    if (pCVar6->m_streamTextRaw[0] != (void *)0x0) {
      __dl__FPv();
      pCVar6->m_streamTextRaw[0] = (void *)0x0;
    }
    iVar3 = iVar3 + 1;
    pCVar6 = (CPartMng *)&pCVar6->m_editCount;
  } while (iVar3 < 0x80);
  if (*(int *)(partMng->m_usbEdit + 0xc) != 0) {
    __dl__FPv();
    partMng->m_usbEdit[0xc] = '\0';
    partMng->m_usbEdit[0xd] = '\0';
    partMng->m_usbEdit[0xe] = '\0';
    partMng->m_usbEdit[0xf] = '\0';
  }
  return;
}

