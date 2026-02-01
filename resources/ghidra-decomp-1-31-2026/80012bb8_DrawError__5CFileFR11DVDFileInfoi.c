// Function: DrawError__5CFileFR11DVDFileInfoi
// Entry: 80012bb8
// Size: 1696 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DrawError__5CFileFR11DVDFileInfoi(CFile *file,DVDFileInfo *dvdFileInfo,int param_3)

{
  bool bVar1;
  bool bVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  undefined **ppuVar7;
  CFont *font;
  undefined auStack_b8 [4];
  undefined4 local_b4;
  undefined auStack_b0 [4];
  undefined4 local_ac;
  undefined auStack_a8 [4];
  undefined4 local_a4;
  undefined auStack_a0 [4];
  undefined4 local_9c;
  undefined auStack_98 [32];
  undefined4 local_78;
  uint uStack_74;
  undefined4 local_70;
  uint uStack_6c;
  undefined4 local_68;
  uint uStack_64;
  char *local_60;
  CSound *local_5c;
  CGraphic *local_58;
  char *local_54;
  
  local_60 = s_file_cpp_801d5dc0;
  local_58 = &Graphic;
  local_54 = s_file_cpp_801d5dc0;
  file->isDiskError = 1;
  local_5c = &Sound;
  do {
    if (System.m_execParam != 0) {
      Printf__7CSystemFPce(&System,s_CFile__drawError___d_801d5da8,param_3);
    }
    bVar1 = MenuPcs._248_4_ == 0;
    font = (CFont *)MenuPcs._248_4_;
    if (bVar1) {
      font = (CFont *)FontMan._8_4_;
    }
    if (font == (CFont *)0x0) {
      file->isDiskError = 0;
      return;
    }
    _WaitDrawDone__8CGraphicFPci(&Graphic,s_file_cpp_801d5dc0,0x2cc);
    bVar2 = false;
    if (((int)(-DAT_80238030 | DAT_80238030) < 0) && (!bVar1)) {
      bVar2 = true;
    }
    if (bVar2) {
      GetBackBufferRect2__8CGraphicFPvP9_GXTexObjiiiii12_GXTexFilter9_GXTexFmti
                (&Graphic,DAT_80238030,auStack_98,0,0,0x280,0x70,0,0,6,0);
      puVar3 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_a0,0,0,0,0xff);
      local_9c = *puVar3;
      RenderColorQuad__5CUtilFffff8_GXColor
                ((double)FLOAT_8032f60c,(double)FLOAT_8032f60c,(double)FLOAT_8032f610,
                 (double)FLOAT_8032f614,&DAT_8032ec70,&local_9c);
      memcpy((void *)(DAT_80238030 + 0x46000),DAT_8023802c + 0x34800,0x29400);
      DCFlushRange(DAT_80238030 + 0x46000,0x29400);
    }
    else {
      puVar3 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_a8,0,0,0,0xff);
      local_a4 = *puVar3;
      RenderColorQuad__5CUtilFffff8_GXColor
                ((double)FLOAT_8032f60c,(double)FLOAT_8032f60c,(double)FLOAT_8032f610,
                 (double)FLOAT_8032f618,&DAT_8032ec70,&local_a4);
    }
    SetScale__5CFontFf(FLOAT_8032f61c,font);
    SetShadow__5CFontFi(font,1);
    SetMargin__5CFontFf(FLOAT_8032f60c,font);
    SetZMode__5CFontFii(font,0,0);
    puVar3 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_b0,0xff,0xff,0xff,0xff);
    local_ac = *puVar3;
    SetColor__5CFontF8_GXColor(font,&local_ac);
    uVar4 = 7;
    if (bVar1) {
      uVar4 = 0xffffffff;
    }
    SetTlut__5CFontFi(font,uVar4);
    DrawInit__5CFontFv(font);
    uVar6 = 200;
    if (bVar2) {
      uVar6 = 0x20;
    }
    iVar5 = 0;
    switch(param_3) {
    case 4:
    case 6:
      iVar5 = 2;
      break;
    case 5:
      iVar5 = 1;
      break;
    case 0xb:
      iVar5 = 0;
      break;
    case -1:
      iVar5 = 3;
      file->fatal_diskErrorFlag = 1;
    }
    ppuVar7 = l_tError + iVar5 * 0x12 + (uint)Game.game.m_gameWork.m_languageId * 3;
    iVar5 = strlen(ppuVar7[2]);
    if (iVar5 == 0) {
      SetPosX__5CFontFf(FLOAT_8032f620,font);
      uStack_74 = uVar6 ^ 0x80000000;
      local_78 = 0x43300000;
      SetPosY__5CFontFf((float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_8032f628),font);
      SetPosZ__5CFontFf(FLOAT_8032f60c,font);
      Draw__5CFontFPc(font,*ppuVar7);
      SetPosX__5CFontFf(FLOAT_8032f620,font);
      uStack_6c = uVar6 + 0x1c ^ 0x80000000;
      local_70 = 0x43300000;
      SetPosY__5CFontFf((float)((double)CONCAT44(0x43300000,uStack_6c) - DOUBLE_8032f628),font);
      SetPosZ__5CFontFf(FLOAT_8032f60c,font);
      Draw__5CFontFPc(font,ppuVar7[1]);
    }
    else {
      SetPosX__5CFontFf(FLOAT_8032f620,font);
      uStack_6c = uVar6 - 0xe ^ 0x80000000;
      local_70 = 0x43300000;
      SetPosY__5CFontFf((float)((double)CONCAT44(0x43300000,uStack_6c) - DOUBLE_8032f628),font);
      SetPosZ__5CFontFf(FLOAT_8032f60c,font);
      Draw__5CFontFPc(font,*ppuVar7);
      SetPosX__5CFontFf(FLOAT_8032f620,font);
      uStack_74 = uVar6 + 0xe ^ 0x80000000;
      local_78 = 0x43300000;
      SetPosY__5CFontFf((float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_8032f628),font);
      SetPosZ__5CFontFf(FLOAT_8032f60c,font);
      Draw__5CFontFPc(font,ppuVar7[1]);
      SetPosX__5CFontFf(FLOAT_8032f620,font);
      uStack_64 = uVar6 + 0x2a ^ 0x80000000;
      local_68 = 0x43300000;
      SetPosY__5CFontFf((float)((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_8032f628),font);
      SetPosZ__5CFontFf(FLOAT_8032f60c,font);
      Draw__5CFontFPc(font,ppuVar7[2]);
    }
    DrawQuit__5CFontFv(font);
    if (bVar2) {
      GXSetDispCopySrc(0,0,0x280,0x70);
      GXSetDispCopyDst(0x280,0x70);
      GXCopyDisp(DAT_8023802c + 0x34800,0);
    }
    else {
      GXSetDispCopySrc(0,0,0x280,0x1c0);
      GXSetDispCopyDst(0x280,0x1c0);
      GXCopyDisp(DAT_8023802c,0);
    }
    _WaitDrawDone__8CGraphicFPci(&Graphic,s_file_cpp_801d5dc0,0x329);
    SetStdDispCopySrc__8CGraphicFv(&Graphic);
    SetStdDispCopyDst__8CGraphicFv(&Graphic);
    _WaitDrawDone__8CGraphicFPci(&Graphic,local_60,0x32d);
    VIWaitForRetrace();
    PauseDiscError__6CSoundFi(local_5c,1);
    VISetBlack(0);
    VIFlush();
    while (iVar5 = DVDGetCommandBlockStatus(dvdFileInfo), iVar5 == param_3) {
      VIWaitForRetrace();
    }
    if (bVar2) {
      RenderTextureQuad__5CUtilFffffP9_GXTexObjP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
                ((double)FLOAT_8032f60c,(double)FLOAT_8032f60c,(double)FLOAT_8032f610,
                 (double)FLOAT_8032f614,&DAT_8032ec70,auStack_98,0,0,0,4,5);
      memcpy((void *)(DAT_8023802c + 0x34800),DAT_80238030 + 0x46000,0x29400);
      DCFlushRange(DAT_8023802c + 0x34800,0x29400);
    }
    else {
      puVar3 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_b8,0,0,0,0xff);
      local_b4 = *puVar3;
      RenderColorQuad__5CUtilFffff8_GXColor
                ((double)FLOAT_8032f60c,(double)FLOAT_8032f60c,(double)FLOAT_8032f610,
                 (double)FLOAT_8032f618,&DAT_8032ec70,&local_b4);
      GXCopyDisp(DAT_8023802c,0);
    }
    _WaitDrawDone__8CGraphicFPci(local_58,local_54,0x35b);
    file->fatal_diskErrorFlag = 0;
    while (iVar5 == 1) {
      VIWaitForRetrace();
      iVar5 = DVDGetCommandBlockStatus(dvdFileInfo);
    }
    param_3 = iVar5;
  } while (((iVar5 == 0xb) || (iVar5 - 4U < 3)) || (iVar5 == -1));
  PauseDiscError__6CSoundFi(&Sound,0);
  file->isDiskError = 0;
  return;
}

