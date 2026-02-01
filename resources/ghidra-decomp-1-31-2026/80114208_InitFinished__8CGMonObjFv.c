// Function: InitFinished__8CGMonObjFv
// Entry: 80114208
// Size: 456 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void InitFinished__8CGMonObjFv(CGMonObj *gMonObj)

{
  *(float *)&gMonObj->field_0x6f8 = (gMonObj->gObject).unk_0x168;
  *(float *)&gMonObj->field_0x6fc = (gMonObj->gObject).unk_0x16C;
  *(float *)&gMonObj->field_0x700 = (gMonObj->gObject).unk_0x170;
  switch((gMonObj->gObject).m_scriptHandle[4]) {
  case (void *)0x5b:
    *(undefined4 **)&gMonObj->field_0x708 = &DAT_80212b30;
    break;
  default:
    *(undefined4 **)&gMonObj->field_0x708 = &DAT_80212a1c;
    break;
  case (void *)0x5f:
    *(undefined4 **)&gMonObj->field_0x708 = &DAT_80213064;
    break;
  case (void *)0x63:
    *(undefined4 **)&gMonObj->field_0x708 = &DAT_80212c38;
    break;
  case (void *)0x67:
    *(undefined4 **)&gMonObj->field_0x708 = &DAT_80212f5c;
    break;
  case (void *)0x6b:
    *(undefined4 **)&gMonObj->field_0x708 = &DAT_80212e54;
    break;
  case (void *)0x6f:
    *(undefined4 **)&gMonObj->field_0x708 = &DAT_80213394;
    break;
  case (void *)0x70:
    *(undefined4 **)&gMonObj->field_0x708 = &DAT_802134a8;
    break;
  case (void *)0x71:
    *(undefined4 **)&gMonObj->field_0x708 = &DAT_80212d4c;
    break;
  case (void *)0x73:
    *(undefined4 **)&gMonObj->field_0x708 = &DAT_8021316c;
    break;
  case (void *)0x74:
  case (void *)0x75:
    *(undefined4 **)&gMonObj->field_0x708 = &DAT_80214054;
    break;
  case (void *)0x77:
    *(undefined4 **)&gMonObj->field_0x708 = &DAT_80213274;
    break;
  case (void *)0x79:
    *(undefined4 **)&gMonObj->field_0x708 = &DAT_80213b08;
    break;
  case (void *)0x7b:
    *(undefined4 **)&gMonObj->field_0x708 = &DAT_80213a00;
    break;
  case (void *)0x7f:
    *(undefined4 **)&gMonObj->field_0x708 = &DAT_80213c10;
    break;
  case (void *)0x83:
    *(undefined4 **)&gMonObj->field_0x708 = &DAT_802138f8;
    break;
  case (void *)0x85:
  case (void *)0x86:
  case (void *)0x87:
    *(undefined4 **)&gMonObj->field_0x708 = &DAT_802135bc;
    break;
  case (void *)0x88:
    *(undefined4 **)&gMonObj->field_0x708 = &DAT_802136dc;
    break;
  case (void *)0x8e:
  case (void *)0x8f:
  case (void *)0x90:
  case (void *)0x91:
  case (void *)0x92:
  case (void *)0x93:
  case (void *)0x94:
  case (void *)0x95:
  case (void *)0x96:
  case (void *)0x97:
  case (void *)0x98:
  case (void *)0x99:
    *(undefined4 **)&gMonObj->field_0x708 = &DAT_802137f0;
    break;
  case (void *)0x9a:
    *(undefined4 **)&gMonObj->field_0x708 = &DAT_80213f40;
    break;
  case (void *)0x9b:
    *(undefined4 **)&gMonObj->field_0x708 = &DAT_80213e2c;
    break;
  case (void *)0x9e:
    *(undefined4 **)&gMonObj->field_0x708 = &DAT_80213d24;
  }
  __ptmf_scall();
  return;
}

