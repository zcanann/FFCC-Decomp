// Function: PADRead
// Entry: 8018e054
// Size: 940 bytes

uint PADRead(ushort *param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  undefined *puVar8;
  uint local_3c [3];
  
  uVar1 = OSDisableInterrupts();
  iVar6 = 0;
  puVar8 = &DAT_8030cca0;
  uVar5 = 0;
  do {
    uVar7 = 0x80000000 >> iVar6;
    if ((DAT_8032f150 & uVar7) == 0) {
      if ((DAT_8032f140 & uVar7) == 0) {
        if (DAT_8032eb1c != iVar6) {
          if ((DAT_8032f13c & uVar7) == 0) {
            *(undefined *)(param_1 + 5) = 0xff;
            memset(param_1,0,10);
          }
          else {
            iVar3 = SIIsChanBusy(iVar6);
            if (iVar3 == 0) {
              uVar4 = SIGetStatus(iVar6);
              if ((uVar4 & 8) == 0) {
                uVar4 = SIGetType(iVar6);
                if ((uVar4 & 0x20000000) == 0) {
                  uVar5 = uVar5 | uVar7;
                }
                iVar3 = SIGetResponse(iVar6,local_3c);
                if (iVar3 == 0) {
                  *(undefined *)(param_1 + 5) = 0xfd;
                  memset(param_1,0,10);
                }
                else if ((local_3c[0] & 0x80000000) == 0) {
                  (*DAT_8032eb2c)(iVar6,param_1,local_3c);
                  if ((*param_1 & 0x2000) == 0) {
                    *(undefined *)(param_1 + 5) = 0;
                    *param_1 = *param_1 & 0xff7f;
                  }
                  else {
                    *(undefined *)(param_1 + 5) = 0xfd;
                    memset(param_1,0,10);
                    SITransfer(iVar6,&DAT_8032eb30,1,puVar8,10,PADOriginUpdateCallback,0,0);
                  }
                }
                else {
                  *(undefined *)(param_1 + 5) = 0xfd;
                  memset(param_1,0,10);
                }
              }
              else {
                SIGetResponse(iVar6,local_3c);
                if ((DAT_8032f148 & uVar7) == 0) {
                  uVar2 = OSDisableInterrupts();
                  SIDisablePolling(uVar7);
                  uVar7 = ~uVar7;
                  DAT_8032f13c = DAT_8032f13c & uVar7;
                  DAT_8032f148 = DAT_8032f148 & uVar7;
                  DAT_8032f14c = DAT_8032f14c & uVar7;
                  DAT_8032f150 = DAT_8032f150 & uVar7;
                  OSSetWirelessID(iVar6,0);
                  OSRestoreInterrupts(uVar2);
                  *(undefined *)(param_1 + 5) = 0xff;
                  memset(param_1,0,10);
                }
                else {
                  *(undefined *)(param_1 + 5) = 0;
                  memset(param_1,0,10);
                  if ((DAT_8032f14c & uVar7) == 0) {
                    DAT_8032f14c = DAT_8032f14c | uVar7;
                    SIGetTypeAsync(iVar6,PADReceiveCheckCallback);
                  }
                }
              }
            }
            else {
              *(undefined *)(param_1 + 5) = 0xfd;
              memset(param_1,0,10);
            }
          }
          goto LAB_8018e3cc;
        }
      }
      *(undefined *)(param_1 + 5) = 0xfe;
      memset(param_1,0,10);
    }
    else {
      uVar2 = OSDisableInterrupts();
      uVar4 = DAT_8032f150 & ~(DAT_8032f148 | DAT_8032f14c);
      DAT_8032f140 = DAT_8032f140 | uVar4;
      DAT_8032f150 = 0;
      uVar7 = DAT_8032f140 & DAT_8032f13c;
      if (DAT_8032eb28 == 4) {
        DAT_8032f144 = DAT_8032f144 | uVar4;
      }
      DAT_8032f13c = DAT_8032f13c & ~uVar4;
      SIDisablePolling(uVar7);
      if (DAT_8032eb1c == 0x20) {
        DAT_8032eb1c = countLeadingZeros(DAT_8032f140);
        if (DAT_8032eb1c != 0x20) {
          DAT_8032f140 = DAT_8032f140 & ~(0x80000000U >> DAT_8032eb1c);
          memset(&DAT_8030cca0 + DAT_8032eb1c * 0xc,0,0xc);
          SIGetTypeAsync(DAT_8032eb1c,PADTypeAndStatusCallback);
        }
      }
      OSRestoreInterrupts(uVar2);
      *(undefined *)(param_1 + 5) = 0xfe;
      memset(param_1,0,10);
    }
LAB_8018e3cc:
    iVar6 = iVar6 + 1;
    puVar8 = puVar8 + 0xc;
    param_1 = param_1 + 6;
    if (3 < iVar6) {
      OSRestoreInterrupts(uVar1);
      return uVar5;
    }
  } while( true );
}

