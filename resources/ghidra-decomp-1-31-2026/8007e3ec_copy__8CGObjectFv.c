// Function: copy__8CGObjectFv
// Entry: 8007e3ec
// Size: 684 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void copy__8CGObjectFv(CGObject *gObject)

{
  bool bVar1;
  CCharaPcsCHandle *pCVar2;
  
  pCVar2 = gObject->m_charaModelHandle;
  bVar1 = false;
  if ((pCVar2 != (CCharaPcsCHandle *)0x0) && (pCVar2->m_model != (CModel *)0x0)) {
    bVar1 = true;
  }
  if (!bVar1) {
    return;
  }
  bVar1 = false;
  pCVar2->m_flags = gObject->m_displayFlags;
  gObject->m_charaModelHandle->m_colorPhase = gObject->m_animBlend;
  gObject->m_charaModelHandle->m_sortZ = gObject->m_screenDepth;
  gObject->m_charaModelHandle->m_fogBlend = gObject->m_worldParam;
  pCVar2 = gObject->m_weaponModelHandle;
  if ((pCVar2 != (CCharaPcsCHandle *)0x0) && (pCVar2->m_model != (CModel *)0x0)) {
    bVar1 = true;
  }
  if (bVar1) {
    pCVar2->m_flags = gObject->m_displayFlags;
    gObject->m_weaponModelHandle->m_colorPhase = gObject->m_animBlend;
    gObject->m_weaponModelHandle->m_sortZ = gObject->m_screenDepth;
    gObject->m_weaponModelHandle->m_fogBlend = gObject->m_worldParam;
  }
  pCVar2 = gObject->m_shieldModelHandle;
  bVar1 = false;
  if ((pCVar2 != (CCharaPcsCHandle *)0x0) && (pCVar2->m_model != (CModel *)0x0)) {
    bVar1 = true;
  }
  if (bVar1) {
    pCVar2->m_flags = gObject->m_displayFlags;
    gObject->m_shieldModelHandle->m_colorPhase = gObject->m_animBlend;
    gObject->m_shieldModelHandle->m_sortZ = gObject->m_screenDepth;
    gObject->m_shieldModelHandle->m_fogBlend = gObject->m_worldParam;
  }
  if (-1 < (int)((uint)*(byte *)&gObject->m_weaponNodeFlags << 0x1a |
                (uint)(*(byte *)&gObject->m_weaponNodeFlags >> 6))) {
    bVar1 = false;
    gObject->m_charaModelHandle->m_flags = gObject->m_charaModelHandle->m_flags & 0xfffffffe;
    pCVar2 = gObject->m_weaponModelHandle;
    if ((pCVar2 != (CCharaPcsCHandle *)0x0) && (pCVar2->m_model != (CModel *)0x0)) {
      bVar1 = true;
    }
    if (bVar1) {
      pCVar2->m_flags = pCVar2->m_flags & 0xfffffffe;
    }
    pCVar2 = gObject->m_shieldModelHandle;
    bVar1 = false;
    if ((pCVar2 != (CCharaPcsCHandle *)0x0) && (pCVar2->m_model != (CModel *)0x0)) {
      bVar1 = true;
    }
    if (bVar1) {
      pCVar2->m_flags = pCVar2->m_flags & 0xfffffffe;
    }
  }
  if (-1 < (int)((uint)*(byte *)&gObject->m_shieldNodeFlags << 0x1a |
                (uint)(*(byte *)&gObject->m_shieldNodeFlags >> 6))) {
    bVar1 = false;
    gObject->m_charaModelHandle->m_flags = gObject->m_charaModelHandle->m_flags & 0xfffffffb;
    pCVar2 = gObject->m_weaponModelHandle;
    if ((pCVar2 != (CCharaPcsCHandle *)0x0) && (pCVar2->m_model != (CModel *)0x0)) {
      bVar1 = true;
    }
    if (bVar1) {
      pCVar2->m_flags = pCVar2->m_flags & 0xfffffffb;
    }
    pCVar2 = gObject->m_shieldModelHandle;
    bVar1 = false;
    if ((pCVar2 != (CCharaPcsCHandle *)0x0) && (pCVar2->m_model != (CModel *)0x0)) {
      bVar1 = true;
    }
    if (!bVar1) {
      return;
    }
    pCVar2->m_flags = pCVar2->m_flags & 0xfffffffb;
    return;
  }
  bVar1 = false;
  gObject->m_charaModelHandle->m_bgCharmPlaneY = gObject->m_bgCharmFactor;
  gObject->m_charaModelHandle->m_worldPosY = (gObject->m_worldPosition).y;
  pCVar2 = gObject->m_weaponModelHandle;
  if ((pCVar2 != (CCharaPcsCHandle *)0x0) && (pCVar2->m_model != (CModel *)0x0)) {
    bVar1 = true;
  }
  if (bVar1) {
    pCVar2->m_bgCharmPlaneY = gObject->m_bgCharmFactor;
    gObject->m_weaponModelHandle->m_worldPosY = (gObject->m_worldPosition).y;
  }
  pCVar2 = gObject->m_shieldModelHandle;
  bVar1 = false;
  if ((pCVar2 != (CCharaPcsCHandle *)0x0) && (pCVar2->m_model != (CModel *)0x0)) {
    bVar1 = true;
  }
  if (!bVar1) {
    return;
  }
  pCVar2->m_bgCharmPlaneY = gObject->m_bgCharmFactor;
  gObject->m_shieldModelHandle->m_worldPosY = (gObject->m_worldPosition).y;
  return;
}

