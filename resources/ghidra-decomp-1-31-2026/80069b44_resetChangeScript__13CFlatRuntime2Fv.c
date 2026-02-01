// Function: resetChangeScript__13CFlatRuntime2Fv
// Entry: 80069b44
// Size: 476 bytes

void resetChangeScript__13CFlatRuntime2Fv(CFlatRuntime2 *flatRuntime2)

{
  CFlatRuntime2 *pCVar1;
  int iVar2;
  
  flatRuntime2->field61759_0x10404 = 0;
  *(undefined4 *)&flatRuntime2->field_0x12a8 = 0;
  *(undefined4 *)&flatRuntime2->field_0x12ac = 0;
  *(undefined4 *)&flatRuntime2->field_0x1bf4 = 0;
  *(undefined4 *)&flatRuntime2->field_0x2708 = 0;
  flatRuntime2->field8065_0x321c = 0;
  flatRuntime2->field10898_0x3d30 = 0;
  flatRuntime2->field13731_0x4844 = 0;
  flatRuntime2->field16564_0x5358 = 0;
  flatRuntime2->field19397_0x5e6c = 0;
  flatRuntime2->field22230_0x6980 = 0;
  flatRuntime2->field25063_0x7494 = 0;
  flatRuntime2->field27896_0x7fa8 = 0;
  flatRuntime2->field30729_0x8abc = 0;
  flatRuntime2->field33562_0x95d0 = 0;
  flatRuntime2->field36395_0xa0e4 = 0;
  flatRuntime2->field39228_0xabf8 = 0;
  flatRuntime2->field42061_0xb70c = 0;
  flatRuntime2->field44894_0xc220 = 0;
  iVar2 = 2;
  pCVar1 = flatRuntime2;
  do {
    pCVar1->field_0x134d = 0;
    pCVar1->field_0x134c = 0xff;
    pCVar1->field_0x1361 = 0;
    pCVar1->field_0x1360 = 0xff;
    pCVar1->field_0x1375 = 0;
    pCVar1->field_0x1374 = 0xff;
    pCVar1->field_0x1389 = 0;
    pCVar1->field_0x1388 = 0xff;
    pCVar1->field_0x139d = 0;
    pCVar1->field_0x139c = 0xff;
    pCVar1->field_0x13b1 = 0;
    pCVar1->field_0x13b0 = 0xff;
    pCVar1->field_0x13c5 = 0;
    pCVar1->field_0x13c4 = 0xff;
    pCVar1->field_0x13d9 = 0;
    pCVar1->field_0x13d8 = 0xff;
    pCVar1->field_0x13ed = 0;
    pCVar1->field_0x13ec = 0xff;
    pCVar1->field_0x1401 = 0;
    pCVar1->field_0x1400 = 0xff;
    pCVar1->field_0x1415 = 0;
    pCVar1->field_0x1414 = 0xff;
    pCVar1->field_0x1429 = 0;
    pCVar1->field_0x1428 = 0xff;
    pCVar1->field_0x143d = 0;
    pCVar1->field_0x143c = 0xff;
    pCVar1->field_0x1451 = 0;
    pCVar1->field_0x1450 = 0xff;
    pCVar1->field_0x1465 = 0;
    pCVar1->field_0x1464 = 0xff;
    pCVar1->field_0x1479 = 0;
    pCVar1->field_0x1478 = 0xff;
    pCVar1 = (CFlatRuntime2 *)((pCVar1->flatRuntimeBase).m_workArea + 0xf8);
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  flatRuntime2->field61764_0x1040c = 0;
  flatRuntime2->field61765_0x10410 = 0;
  flatRuntime2->field61766_0x10414 = 0;
  flatRuntime2->field_0x12e4 = flatRuntime2->field_0x12e4 & 0x7f | 0x80;
  flatRuntime2->field_0x12e4 = flatRuntime2->field_0x12e4 & 0xdf;
  flatRuntime2->field_0x12e4 = flatRuntime2->field_0x12e4 & 0xef;
  *(undefined4 *)&flatRuntime2->field_0x12e8 = 0;
  *(undefined4 *)&flatRuntime2->field_0x12ec = 0;
  memset(&flatRuntime2->field_0x1041c,0,0x14);
  memset(0x8030014c,0,0x8c);
  flatRuntime2->field_0x12e4 = flatRuntime2->field_0x12e4 & 0xfd;
  flatRuntime2->field_0x12e4 = flatRuntime2->field_0x12e4 & 0xf7;
  flatRuntime2->field_0x12e4 = flatRuntime2->field_0x12e4 & 0xfe;
  Pad._456_4_ = 1;
  GraphicsPcs._68_4_ = 0;
  CameraPcs._1076_4_ = 1;
  reset__6CAStarFv((CAStar *)&DbgMenuPcs.field_0x2a5c);
  return;
}

