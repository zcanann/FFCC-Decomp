// Function: StreamControl__Fv
// Entry: 801cc788
// Size: 684 bytes

void StreamControl__Fv(void)

{
  bool bVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  char cVar5;
  int iVar6;
  uint uVar7;
  
  uVar7 = DAT_8032f438;
  do {
    if (*(int *)(uVar7 + 0x110) == 1) {
      iVar6 = *(int *)(uVar7 + 4);
      if (*(int *)(iVar6 + 0x14) != 0) {
        if (*(int *)(*(int *)(iVar6 + 0x14) + 0xc) == 0) {
          _StreamStop__FP13RedStreamDATA(uVar7);
        }
        else {
          iVar2 = (*(int *)(uVar7 + 300) + *(int *)(uVar7 + 0x128)) * 2;
          iVar4 = CONCAT22(*(undefined2 *)(*(int *)(iVar6 + 0x14) + 0x1b2),
                           *(undefined2 *)(*(int *)(iVar6 + 0x14) + 0x1b4));
          if ((iVar2 <= iVar4) && (iVar4 < iVar2 + 0x2000)) {
            bVar1 = false;
            if ((*(int *)(uVar7 + 0x20) < 0) &&
               (*(int *)(uVar7 + 0x1c) = *(int *)(uVar7 + 0x1c) + -0x200, *(int *)(uVar7 + 0x1c) < 1
               )) {
              _StreamStop__FP13RedStreamDATA(uVar7);
              bVar1 = true;
            }
            *(int *)(uVar7 + 0x11c) = *(int *)(uVar7 + 0x11c) + *(short *)(uVar7 + 0x2a) * 0x1000;
            if (*(int *)(uVar7 + 0x118) <= *(int *)(uVar7 + 0x11c)) {
              *(int *)(uVar7 + 0x11c) = *(int *)(uVar7 + 0x11c) - *(int *)(uVar7 + 0x118);
            }
            if (!bVar1) {
              bVar1 = *(int *)(uVar7 + 0x128) == 0;
              if (bVar1) {
                *(undefined4 *)(uVar7 + 0x128) = 0x1000;
              }
              else {
                *(undefined4 *)(uVar7 + 0x128) = 0;
              }
              if (*(int *)(uVar7 + 0x20) < 0) {
                uVar3 = _ArrangeStreamDataNoLoop__FP13RedStreamDATAii(uVar7,bVar1,0x1000);
              }
              else {
                uVar3 = _ArrangeStreamDataLoop__FP13RedStreamDATAii(uVar7,bVar1,0x1000);
              }
              *(undefined4 *)(uVar7 + 0x114) = uVar3;
            }
          }
          cVar5 = *(int *)(uVar7 + 0x108) != 0;
          if ((bool)cVar5) {
            *(int *)(uVar7 + 0x108) = *(int *)(uVar7 + 0x108) + -1;
            *(int *)(uVar7 + 0x100) = *(int *)(uVar7 + 0x100) + *(int *)(uVar7 + 0x104);
          }
          if (*(int *)(uVar7 + 0xf8) != 0) {
            cVar5 = cVar5 + '\x01';
            *(int *)(uVar7 + 0xf8) = *(int *)(uVar7 + 0xf8) + -1;
            *(int *)(uVar7 + 0xf0) = *(int *)(uVar7 + 0xf0) + *(int *)(uVar7 + 0xf4);
          }
          if (cVar5 != '\0') {
            if (*(short *)(uVar7 + 0x2a) == 2) {
              SetVoiceVolumeMix__FP12RedVoiceDATAii(iVar6,0,*(int *)(uVar7 + 0xf0) >> 0xc);
              SetVoiceVolumeMix__FP12RedVoiceDATAii(iVar6 + 0xc0,0x7f,*(int *)(uVar7 + 0xf0) >> 0xc)
              ;
            }
            else {
              SetVoiceVolumeMix__FP12RedVoiceDATAii
                        (iVar6,*(int *)(uVar7 + 0x100) >> 0xc,*(int *)(uVar7 + 0xf0) >> 0xc);
            }
          }
        }
      }
    }
    else if ((*(int *)(uVar7 + 0x110) == 3) &&
            (iVar6 = RedDmaSearchID__Fi(*(undefined4 *)(uVar7 + 0x114)), iVar6 == 0)) {
      iVar6 = *(int *)(uVar7 + 4);
      *(undefined4 *)(uVar7 + 0x110) = 1;
      *(uint *)(iVar6 + 0x90) = *(uint *)(iVar6 + 0x90) | 0x19;
      *(uint *)(iVar6 + 4) = uVar7 + 0x30;
      *(undefined4 *)(iVar6 + 0x8c) = 1;
      if (*(short *)(uVar7 + 0x2a) == 2) {
        *(uint *)(iVar6 + 0x150) = *(uint *)(iVar6 + 0x150) | 0x19;
        *(uint *)(iVar6 + 0xc4) = uVar7 + 0x90;
        *(undefined4 *)(iVar6 + 0x14c) = 1;
      }
    }
    uVar7 = uVar7 + 0x130;
  } while (uVar7 < DAT_8032f438 + 0x4c0);
  return;
}

