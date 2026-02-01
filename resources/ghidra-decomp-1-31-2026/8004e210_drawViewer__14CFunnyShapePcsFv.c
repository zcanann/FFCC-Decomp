// Function: drawViewer__14CFunnyShapePcsFv
// Entry: 8004e210
// Size: 528 bytes

void drawViewer__14CFunnyShapePcsFv(CFunnyShapePcs *funnyShapePcs)

{
  int iVar1;
  double dVar2;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  Vec local_ac;
  Vec local_a0;
  Mtx MStack_94;
  Mtx MStack_54;
  
  local_a0.x = DAT_801d7de8;
  local_a0.y = DAT_801d7dec;
  local_a0.z = DAT_801d7df0;
  local_ac.x = DAT_801d7df4;
  local_ac.y = DAT_801d7df8;
  local_ac.z = DAT_801d7dfc;
  local_b8 = DAT_801d7e00;
  local_b4 = DAT_801d7e04;
  local_b0 = DAT_801d7e08;
  C_MTXOrtho(FLOAT_8032fd10,FLOAT_8032fd14,FLOAT_8032fd14,FLOAT_8032fd10,FLOAT_8032fd10,
             FLOAT_8032fd18,&MStack_54);
  GXSetProjection(&MStack_54,1);
  C_MTXLookAt(&MStack_94,&local_a0,&local_b8,&local_ac);
  GXLoadPosMtxImm(&MStack_94,0);
  GXClearVtxDesc();
  GXSetNumChans(1);
  GXSetVtxAttrFmt(0,9,1,4,0);
  GXSetVtxAttrFmt(0,0xb,1,5,0);
  GXSetVtxAttrFmt(0,0xd,1,4,0);
  if ((*(uint *)&funnyShapePcs->field_0x6178 & 1) != 0) {
    RenderTexture__11CFunnyShapeFv((CFunnyShape *)&(funnyShapePcs->m_usbStreamData).m_stageDefault);
  }
  if ((*(uint *)&funnyShapePcs->field_0x6178 & 4) != 0) {
    RenderShape__11CFunnyShapeFv(&(funnyShapePcs->m_usbStreamData).m_stageDefault);
  }
  if ((*(uint *)&funnyShapePcs->field_0x6178 & 8) != 0) {
    Render__11CFunnyShapeFv(&(funnyShapePcs->m_usbStreamData).m_stageDefault);
  }
  if (DAT_8032ed2c == '\0') {
    DAT_8032ed28 = &DAT_8032fd1c;
    DAT_8032ed2c = '\x01';
  }
  if (DAT_8032ed34 == '\0') {
    DAT_8032ed30 = 0;
    DAT_8032ed34 = '\x01';
  }
  DAT_8032ed30 = DAT_8032ed30 + 1;
  if (100000 < DAT_8032ed30) {
    DAT_8032ed30 = 0;
  }
  dVar2 = (double)FLOAT_8032fd24;
  GXSetViewport(dVar2,dVar2,(double)FLOAT_8032fd28,(double)FLOAT_8032fd2c,dVar2,
                (double)FLOAT_8032fd10);
  iVar1 = DAT_8032ed30 >> 0x1f;
  Printf__8CGraphicFPce
            (&Graphic,s_FunnyShape___c__801d7e34,
             (int)(char)DAT_8032ed28
                        [(iVar1 * 4 | (uint)((DAT_8032ed30 >> 4) * 0x40000000 + iVar1) >> 0x1e) -
                         iVar1]);
  return;
}

