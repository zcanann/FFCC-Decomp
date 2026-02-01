// Function: drawEnd__11CGraphicPcsFv
// Entry: 80047248
// Size: 736 bytes

void drawEnd__11CGraphicPcsFv(undefined4 param_1)

{
  bool bVar1;
  undefined uVar2;
  ushort uVar3;
  undefined uVar4;
  undefined uVar5;
  undefined uVar6;
  undefined uVar7;
  undefined uVar8;
  undefined uVar9;
  undefined uVar10;
  undefined uVar11;
  undefined uVar12;
  uint uVar13;
  short sVar14;
  undefined auStack_218 [256];
  undefined auStack_118 [256];
  
  if ((MiniGamePcs._25732_4_ & 0x10) != 0) {
    DrawDebugString__8CGraphicFv(&Graphic);
  }
  if ((MiniGamePcs._25732_4_ & 1) != 0) {
    drawBar__11CGraphicPcsFv(param_1);
  }
  if ((MiniGamePcs._25732_4_ & 0x10) != 0) {
    InitDebugString__8CGraphicFv(&Graphic);
    if (System.m_scenegraphStepMode != 0) {
      DrawDebugStringDirect__8CGraphicFUlUlPcUl
                (&Graphic,0x10,0x10,(&PTR_DAT_801e9e64)[System.m_scenegraphStepMode],0xc);
    }
    if (Pad._448_4_ != -1) {
      sprintf(auStack_118,&DAT_8032fbf4,Pad._448_4_ + 1);
      DrawDebugStringDirect__8CGraphicFUlUlPcUl(&Graphic,0x10,0x11,auStack_118,0xc);
    }
    uVar13 = 0;
    sVar14 = 0x10;
    do {
      bVar1 = false;
      if (Pad._452_4_ == 0) {
        if (uVar13 == 0) {
          if (Pad._448_4_ != -1) goto LAB_8004736c;
        }
      }
      else {
LAB_8004736c:
        bVar1 = true;
      }
      if (bVar1) {
        uVar3 = 0;
      }
      else {
        uVar3 = *(ushort *)
                 (&Pad.field_0x4 +
                 (uVar13 & ~((int)~(Pad._448_4_ - uVar13 | uVar13 - Pad._448_4_) >> 0x1f)) * 0x54);
      }
      uVar12 = 0x20;
      if ((uVar3 & 0x20) != 0) {
        uVar12 = 0x72;
      }
      uVar7 = 0x20;
      if ((uVar3 & 0x40) != 0) {
        uVar7 = 0x6c;
      }
      uVar5 = 0x20;
      if ((uVar3 & 0x10) != 0) {
        uVar5 = 0x73;
      }
      uVar4 = 0x20;
      if ((uVar3 & 0x1000) != 0) {
        uVar4 = 0x53;
      }
      uVar2 = 0x20;
      if ((uVar3 & 0x100) != 0) {
        uVar2 = 0x41;
      }
      uVar11 = 0x20;
      if ((uVar3 & 0x200) != 0) {
        uVar11 = 0x42;
      }
      uVar10 = 0x20;
      if ((uVar3 & 2) != 0) {
        uVar10 = 0x52;
      }
      uVar9 = 0x20;
      if ((uVar3 & 1) != 0) {
        uVar9 = 0x4c;
      }
      uVar8 = 0x20;
      if ((uVar3 & 4) != 0) {
        uVar8 = 0x44;
      }
      uVar6 = 0x20;
      if ((uVar3 & 8) != 0) {
        uVar6 = 0x55;
      }
      sprintf(auStack_218,s__c_c_c_c_c_c_c_c_c_c_801d7bf8,uVar6,uVar8,uVar9,uVar10,uVar11,uVar2,
              uVar4,uVar5,uVar7,uVar12);
      DrawDebugStringDirect__8CGraphicFUlUlPcUl(&Graphic,sVar14,0x1a8,auStack_218,8);
      uVar13 = uVar13 + 1;
      sVar14 = sVar14 + 0x60;
    } while ((int)uVar13 < 4);
    sprintf(auStack_218,&DAT_8032fbf8,System.m_frameCounter);
    DrawDebugStringDirect__8CGraphicFUlUlPcUl
              (&Graphic,(short)uVar13 * 0x60 + 0x10,0x1a8,auStack_218,8);
  }
  Draw__7CMemoryFv(&Memory);
  EndFrame__8CGraphicFv(&Graphic);
  return;
}

