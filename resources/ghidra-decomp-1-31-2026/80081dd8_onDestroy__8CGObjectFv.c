// Function: onDestroy__8CGObjectFv
// Entry: 80081dd8
// Size: 204 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onDestroy__8CGObjectFv(CGObject *gObject)

{
  if (gObject->m_charaModelHandle != (CCharaPcsCHandle *)0x0) {
    pppDeleteCHandle__8CPartMngFPQ29CCharaPcs7CHandle(&PartMng,gObject->m_charaModelHandle);
  }
  if (gObject->m_weaponModelHandle != (CCharaPcsCHandle *)0x0) {
    pppDeleteCHandle__8CPartMngFPQ29CCharaPcs7CHandle(&PartMng,gObject->m_weaponModelHandle);
  }
  if (gObject->m_shieldModelHandle != (CCharaPcsCHandle *)0x0) {
    pppDeleteCHandle__8CPartMngFPQ29CCharaPcs7CHandle(&PartMng,gObject->m_shieldModelHandle);
  }
  if (gObject->m_charaModelHandle != (CCharaPcsCHandle *)0x0) {
    __dt__Q29CCharaPcs7CHandleFv(gObject->m_charaModelHandle,1);
    gObject->m_charaModelHandle = (CCharaPcsCHandle *)0x0;
  }
  if (gObject->m_weaponModelHandle != (CCharaPcsCHandle *)0x0) {
    __dt__Q29CCharaPcs7CHandleFv(gObject->m_weaponModelHandle,1);
    gObject->m_weaponModelHandle = (CCharaPcsCHandle *)0x0;
  }
  if (gObject->m_shieldModelHandle != (CCharaPcsCHandle *)0x0) {
    __dt__Q29CCharaPcs7CHandleFv(gObject->m_shieldModelHandle,1);
    gObject->m_shieldModelHandle = (CCharaPcsCHandle *)0x0;
  }
  gObject->m_scriptHandle = (void **)0x0;
  return;
}

