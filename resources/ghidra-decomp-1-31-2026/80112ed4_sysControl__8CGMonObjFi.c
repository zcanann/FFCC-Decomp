// Function: sysControl__8CGMonObjFi
// Entry: 80112ed4
// Size: 256 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void sysControl__8CGMonObjFi(CGMonObj *gMonObj,undefined4 param_2)

{
  switch(param_2) {
  case 6:
    *(undefined2 *)&gMonObj->field_0x6d6 = 0;
    break;
  case 7:
    gMonObj->field_0x6be = 1;
    *(undefined4 *)&gMonObj->field_0x6d8 = 4;
    *(undefined4 *)&gMonObj->field_0x6dc = 0;
    gMonObj->field_0x6bb = 1;
    (gMonObj->gObject).m_bgColMask = (gMonObj->gObject).m_bgColMask & 0xfff7fffd;
    (gMonObj->gObject).m_displayFlags = (gMonObj->gObject).m_displayFlags & 0xfffffffe;
    break;
  case 8:
    gMonObj->field_0x6be = 0;
    break;
  case 0xc:
    gMonObj->field_0x6c1 = 1;
    break;
  case 0xd:
    gMonObj->field_0x6c1 = 0;
    break;
  case 0xf:
    setRepop__8CGMonObjFi(gMonObj,0);
    break;
  case 0x10:
    (gMonObj->gObject).m_displayFlags = (gMonObj->gObject).m_displayFlags | 0x400000;
    break;
  case 0x11:
    (gMonObj->gObject).m_displayFlags = (gMonObj->gObject).m_displayFlags & 0xffbfffff;
    break;
  case 0x15:
    *(byte *)&(gMonObj->gObject).m_weaponNodeFlags =
         *(byte *)&(gMonObj->gObject).m_weaponNodeFlags & 0xf7 | 8;
    break;
  case 0x16:
    *(byte *)&(gMonObj->gObject).m_weaponNodeFlags =
         *(byte *)&(gMonObj->gObject).m_weaponNodeFlags & 0xf7;
  }
  return;
}

