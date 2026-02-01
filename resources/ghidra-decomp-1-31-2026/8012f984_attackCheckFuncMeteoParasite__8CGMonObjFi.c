// Function: attackCheckFuncMeteoParasite__8CGMonObjFi
// Entry: 8012f984
// Size: 156 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4 attackCheckFuncMeteoParasite__8CGMonObjFi(CGMonObj *gMonObj)

{
  void *pvVar1;
  
  pvVar1 = (gMonObj->gObject).m_scriptHandle[4];
  if (pvVar1 == (void *)0x86) {
    if ((m_boss__8CGMonObj._88_4_ == 1) && (gMonObj->_bossBranchRelated == 1)) {
      return 0xffffffff;
    }
    return 0xfffffffe;
  }
  if ((int)pvVar1 < 0x86) {
    if (0x84 < (int)pvVar1) {
      return 0xfffffffe;
    }
  }
  else if ((int)pvVar1 < 0x88) {
    if ((m_boss__8CGMonObj._88_4_ == 2) && (gMonObj->_bossBranchRelated < 2)) {
      return 0xffffffff;
    }
    return 0xfffffffe;
  }
  return 0xffffffff;
}

