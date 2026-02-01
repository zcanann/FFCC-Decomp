// Function: DoMount
// Entry: 8019c5b4
// Size: 1040 bytes

int DoMount(int param_1)

{
  char cVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  char cVar5;
  char cVar6;
  char cVar7;
  short sVar8;
  byte bVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  undefined *puVar13;
  int iVar14;
  char *pcVar15;
  uint8_t *puVar16;
  uint8_t *puVar17;
  byte local_1c [4];
  uint local_18 [2];
  
  iVar12 = param_1 * 0x110;
  if (*(int *)(&DAT_80327564 + iVar12) == 0) {
    iVar10 = EXIGetID(param_1,0,local_18);
    if (iVar10 == 0) {
      iVar10 = -3;
    }
    else {
      iVar10 = IsCard(local_18[0]);
      if (iVar10 == 0) {
        iVar10 = -2;
      }
      else {
        iVar10 = 0;
      }
    }
    if (-1 < iVar10) {
      *(uint *)(&DAT_80327648 + iVar12) = local_18[0];
      *(ushort *)(&DAT_80327548 + iVar12) = (ushort)local_18[0] & 0xfc;
      *(undefined4 *)(&DAT_8032754c + iVar12) =
           *(undefined4 *)(&DAT_8021c340 + (local_18[0] >> 9 & 0x1c));
      *(short *)(&DAT_80327550 + iVar12) =
           (short)(((int)((uint)*(ushort *)(&DAT_80327548 + iVar12) << 0x14) >> 3) /
                  *(int *)(&DAT_8032754c + iVar12));
      *(undefined4 *)(&DAT_80327554 + iVar12) =
           *(undefined4 *)(&DAT_8021c360 + (local_18[0] >> 6 & 0x1c));
      iVar10 = __CARDClearStatus(param_1);
      if ((-1 < iVar10) && (iVar10 = __CARDReadStatus(param_1,(char *)local_1c), -1 < iVar10)) {
        iVar10 = EXIProbe(param_1);
        if (iVar10 == 0) {
          iVar10 = -3;
        }
        else if ((local_1c[0] & 0x40) == 0) {
          iVar10 = __CARDUnlock(param_1,&DAT_80327558 + iVar12);
          if (-1 < iVar10) {
            iVar11 = __OSLockSramEx();
            puVar13 = (undefined *)(iVar11 + param_1 * 0xc);
            *puVar13 = (&DAT_80327558)[iVar12];
            cVar1 = (&DAT_80327558)[iVar12];
            puVar13[1] = (&DAT_80327559)[iVar12];
            iVar14 = 8;
            cVar2 = (&DAT_80327559)[iVar12];
            puVar13[2] = (&DAT_8032755a)[iVar12];
            cVar3 = (&DAT_8032755a)[iVar12];
            puVar13[3] = (&DAT_8032755b)[iVar12];
            cVar4 = (&DAT_8032755b)[iVar12];
            puVar13[4] = (&DAT_8032755c)[iVar12];
            cVar5 = (&DAT_8032755c)[iVar12];
            puVar13[5] = (&DAT_8032755d)[iVar12];
            cVar6 = (&DAT_8032755d)[iVar12];
            puVar13[6] = (&DAT_8032755e)[iVar12];
            cVar7 = (&DAT_8032755e)[iVar12];
            puVar13[7] = (&DAT_8032755f)[iVar12];
            bVar9 = cVar1 + cVar2 + cVar3 + cVar4 + cVar5 + cVar6 + cVar7 + (&DAT_8032755f)[iVar12];
            puVar16 = puVar13 + 8;
            iVar12 = 4;
            do {
              puVar17 = ((CARDControl *)(&DAT_80327540 + param_1 * 0x44))->id + iVar14;
              iVar14 = iVar14 + 1;
              *puVar16 = *puVar17;
              puVar16 = puVar16 + 1;
              bVar9 = bVar9 + *puVar17;
              iVar12 = iVar12 + -1;
            } while (iVar12 != 0);
            *(byte *)(iVar11 + param_1 + 0x26) = ~bVar9;
            __OSUnlockSramEx(1);
            return iVar10;
          }
        }
        else {
          *(undefined4 *)(&DAT_80327564 + iVar12) = 1;
          iVar11 = __OSLockSramEx();
          pcVar15 = (char *)(iVar11 + param_1 * 0xc);
          bVar9 = *pcVar15 + pcVar15[1] + pcVar15[2] + pcVar15[3] + pcVar15[4] + pcVar15[5] +
                  pcVar15[6] + pcVar15[7];
          pcVar15 = pcVar15 + 8;
          iVar10 = 4;
          do {
            cVar1 = *pcVar15;
            pcVar15 = pcVar15 + 1;
            bVar9 = bVar9 + cVar1;
            iVar10 = iVar10 + -1;
          } while (iVar10 != 0);
          __OSUnlockSramEx(0);
          if (*(byte *)(iVar11 + param_1 + 0x26) == (byte)~bVar9) goto LAB_8019c89c;
          iVar10 = -5;
        }
      }
    }
LAB_8019c978:
    EXIUnlock(param_1);
    DoUnmount(param_1,iVar10);
  }
  else {
LAB_8019c89c:
    if (*(int *)(&DAT_80327564 + iVar12) == 1) {
      if (*(int *)(&DAT_80327648 + iVar12) == -0x7ffffffc) {
        iVar10 = __OSLockSramEx();
        sVar8 = *(short *)(iVar10 + param_1 * 0xc);
        __OSUnlockSramEx(0);
        if ((DAT_8032eb80 == -1) || (sVar8 != DAT_8032eb80)) {
          iVar10 = -2;
          goto LAB_8019c978;
        }
      }
      *(undefined4 *)(&DAT_80327564 + iVar12) = 2;
      iVar10 = __CARDEnableInterrupt(param_1,1);
      if (iVar10 < 0) goto LAB_8019c978;
      EXISetExiCallback(param_1,__CARDExiHandler);
      EXIUnlock(param_1);
      DCInvalidateRange((&DAT_803275c0)[param_1 * 0x44],0xa000);
    }
    iVar10 = __CARDRead(param_1,*(int *)(&DAT_8032754c + iVar12) *
                                (*(int *)(&DAT_80327564 + iVar12) + -2),0x2000,
                        (void *)((&DAT_803275c0)[param_1 * 0x44] +
                                (*(int *)(&DAT_80327564 + iVar12) + -2) * 0x2000),
                        __CARDMountCallback);
    if (iVar10 < 0) {
      __CARDPutControlBlock((CARDControl *)(&DAT_80327540 + param_1 * 0x44),iVar10);
    }
  }
  return iVar10;
}

