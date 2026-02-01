// Function: Destroy__8CPartMngFv
// Entry: 8005ee7c
// Size: 640 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void Destroy__8CPartMngFv(CPartMng *partMng)

{
  short sVar3;
  CTextureSet *pCVar1;
  CMaterialSet *pCVar2;
  int iVar4;
  pppModelSt *ppVar5;
  int *piVar6;
  pppModelSt *mapMesh;
  int *piVar7;
  uint uVar8;
  
  iVar4 = 0;
  do {
    pppReleasePdt__8CPartMngFi(partMng,iVar4);
    iVar4 = iVar4 + 1;
  } while (iVar4 < 0x20);
  ppVar5 = partMng->m_pppModelStArr;
  if (ppVar5 != (pppModelSt *)0x0) {
    if (ppVar5 != (pppModelSt *)0x0) {
      uVar8 = 0;
      mapMesh = ppVar5;
      do {
        if (mapMesh->m_isUsed != '\0') {
          sVar3 = mapMesh->m_refCount + -1;
          mapMesh->m_refCount = sVar3;
          if (sVar3 < 1) {
            if (mapMesh->m_cacheId != -1) {
              DestroyCache__13CAmemCacheSetFi
                        ((CAmemCacheSet *)CAMemCacheSet,(int)mapMesh->m_cacheId);
              (mapMesh->m_mapMesh).field12_0x24 = 0;
              (mapMesh->m_mapMesh).field13_0x28 = 0;
            }
            Destroy__8CMapMeshFv(&mapMesh->m_mapMesh);
            mapMesh->m_refCount = 0;
            mapMesh->m_isUsed = '\0';
          }
        }
        uVar8 = uVar8 + 1;
        mapMesh = mapMesh + 1;
      } while (uVar8 < 0x100);
      __destroy_arr(ppVar5,__dt__10pppModelStFv,0x6c,0x100);
      __dl__FPv(ppVar5);
    }
    partMng->m_pppModelStArr = (pppModelSt *)0x0;
  }
  piVar6 = *(int **)partMng->m_usbEdit;
  if (piVar6 != (int *)0x0) {
    if (piVar6 != (int *)0x0) {
      uVar8 = 0;
      piVar7 = piVar6;
      do {
        if (*(char *)((int)piVar7 + 0x2a) != '\0') {
          sVar3 = *(short *)(piVar7 + 10);
          *(short *)(piVar7 + 10) = sVar3 + -1;
          if ((short)(sVar3 + -1) < 1) {
            if (*piVar7 != 0) {
              __dl__FPv();
              *piVar7 = 0;
            }
            if (piVar7[1] != 0) {
              __dl__FPv();
              piVar7[1] = 0;
            }
            *(undefined2 *)(piVar7 + 10) = 0;
            *(undefined *)((int)piVar7 + 0x2a) = 0;
          }
        }
        uVar8 = uVar8 + 1;
        piVar7 = piVar7 + 0xb;
      } while (uVar8 < 0x100);
      __destroy_arr(piVar6,__dt__10pppShapeStFv,0x2c,0x100);
      __dl__FPv(piVar6);
    }
    partMng->m_usbEdit[0] = '\0';
    partMng->m_usbEdit[1] = '\0';
    partMng->m_usbEdit[2] = '\0';
    partMng->m_usbEdit[3] = '\0';
  }
  pCVar1 = partMng->m_textureSet;
  if (pCVar1 != (CTextureSet *)0x0) {
    iVar4 = *(int *)&pCVar1->field_0x4 + -1;
    *(int *)&pCVar1->field_0x4 = iVar4;
    if ((iVar4 == 0) && (pCVar1 != (CTextureSet *)0x0)) {
      (**(code **)((int)pCVar1->vtable + 8))(pCVar1,1);
    }
    partMng->m_textureSet = (CTextureSet *)0x0;
  }
  pCVar2 = partMng->m_materialSet;
  if (pCVar2 != (CMaterialSet *)0x0) {
    iVar4 = *(int *)&pCVar2->field_0x4 + -1;
    *(int *)&pCVar2->field_0x4 = iVar4;
    if ((iVar4 == 0) && (pCVar2 != (CMaterialSet *)0x0)) {
      (**(code **)((int)pCVar2->vtable + 8))(pCVar2,1);
    }
    partMng->m_materialSet = (CMaterialSet *)0x0;
  }
  if (*(int *)(partMng->m_usbEdit + 0x1c) != 0) {
    iVar4 = *(int *)(*(int *)(partMng->m_usbEdit + 0x1c) + 0xf8);
    if (iVar4 != 0) {
      __dt__Q29CCharaPcs7CHandleFv(iVar4,1);
      *(undefined4 *)(*(int *)(partMng->m_usbEdit + 0x1c) + 0xf8) = 0;
    }
    if (*(int *)(partMng->m_usbEdit + 0x1c) != 0) {
      __dl__FPv();
      partMng->m_usbEdit[0x1c] = '\0';
      partMng->m_usbEdit[0x1d] = '\0';
      partMng->m_usbEdit[0x1e] = '\0';
      partMng->m_usbEdit[0x1f] = '\0';
    }
  }
  pppDestroyHeap__FP9_pppEnvSt(&partMng->m_pppEnvSt);
  return;
}

