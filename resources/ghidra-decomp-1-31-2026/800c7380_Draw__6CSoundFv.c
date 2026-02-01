// Function: Draw__6CSoundFv
// Entry: 800c7380
// Size: 532 bytes

void Draw__6CSoundFv(CSound *sound)

{
  undefined4 uVar1;
  uint uVar2;
  char *pcVar3;
  undefined4 local_58;
  undefined auStack_54 [4];
  undefined auStack_50 [4];
  undefined4 local_4c;
  Mtx MStack_48;
  
  PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_48);
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  GXSetZCompLoc(0);
  _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6,1,0,7,0);
  GXSetZMode(1,3,1);
  GXSetCullMode(1);
  GXSetNumTevStages(1);
  _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,4);
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0xff,0xff,4);
  GXSetNumChans(1);
  GXSetChanCtrl(0,0,0,0,0,2,1);
  GXSetChanCtrl(2,0,0,0,0,2,2);
  GXClearVtxDesc();
  GXSetVtxDesc(9,1);
  GXSetVtxAttrFmt(0,9,1,4,0);
  pcVar3 = &sound->field_0x2c;
  uVar2 = 0;
  do {
    if (*pcVar3 < '\0') {
      uVar1 = __ct__6CColorFUcUcUcUc(auStack_50,0xc0,0xc0,0xc0,0x80);
      DrawSphere__8CGraphicFPA4_fP3VecfP8_GXColor
                ((double)*(float *)(pcVar3 + 0x10),&Graphic,&MStack_48,pcVar3 + 0x18,uVar1);
      uVar1 = __ct__6CColorFUcUcUcUc(auStack_54,0x80,0x80,0x80,0x80);
      DrawSphere__8CGraphicFPA4_fP3VecfP8_GXColor
                ((double)*(float *)(pcVar3 + 0x14),&Graphic,&MStack_48,pcVar3 + 0x18,uVar1);
    }
    uVar2 = uVar2 + 1;
    pcVar3 = pcVar3 + 0x28;
  } while (uVar2 < 0x80);
  local_4c = 0xff8000ff;
  local_58 = 0xff8000ff;
  GXSetChanMatColor(4,&local_58);
  GXLoadPosMtxImm(&MStack_48,0);
  uVar2 = 0;
  do {
    Draw__9CLine(&sound->field_0x142c);
    uVar2 = uVar2 + 1;
    sound = (CSound *)&sound->field_0x1cc;
  } while (uVar2 < 8);
  return;
}

