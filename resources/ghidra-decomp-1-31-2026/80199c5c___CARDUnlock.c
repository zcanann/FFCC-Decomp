// Function: __CARDUnlock
// Entry: 80199c5c
// Size: 2904 bytes

undefined4 __CARDUnlock(int chan,uint *flashId)

{
  uint *puVar1;
  uint *puVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint local_7c;
  uint local_78;
  uint local_74;
  uint local_70;
  uint local_6c;
  
  iVar9 = chan * 0x110;
  puVar2 = (uint *)(&DAT_803275c0)[chan * 0x44];
  puVar1 = (uint *)((int)puVar2 + 0x2fU & 0xffffffe0);
  iVar3 = OSGetTick();
  DAT_8032eb78 = iVar3 * 0x41c64e6d + 0x3039;
  uVar11 = DAT_8032eb78 >> 0x10 & 0x7000 | 0x7fec8000;
  uVar4 = DummyLen();
  iVar3 = ReadArrayUnlock(chan,uVar11,&local_7c,uVar4,0);
  if (iVar3 < 0) {
    uVar5 = 0xfffffffd;
  }
  else {
    uVar8 = uVar4 * 8 + 1;
    uVar6 = 0;
    if (uVar8 != 0) {
      if ((8 < uVar8) && (uVar12 = uVar4 & 0x1fffffff, uVar4 * 8 != 7)) {
        do {
          uVar11 = uVar11 >> 1 |
                   (~(uVar11 >> 0x17 ^ uVar11 >> 0xf ^ uVar11 ^ uVar11 >> 7) & 1) << 0x1e;
          uVar11 = uVar11 >> 1 |
                   (~(uVar11 >> 0x17 ^ uVar11 >> 0xf ^ uVar11 ^ uVar11 >> 7) & 1) << 0x1e;
          uVar11 = uVar11 >> 1 |
                   (~(uVar11 >> 0x17 ^ uVar11 >> 0xf ^ uVar11 ^ uVar11 >> 7) & 1) << 0x1e;
          uVar11 = uVar11 >> 1 |
                   (~(uVar11 >> 0x17 ^ uVar11 >> 0xf ^ uVar11 ^ uVar11 >> 7) & 1) << 0x1e;
          uVar11 = uVar11 >> 1 |
                   (~(uVar11 >> 0x17 ^ uVar11 >> 0xf ^ uVar11 ^ uVar11 >> 7) & 1) << 0x1e;
          uVar11 = uVar11 >> 1 |
                   (~(uVar11 >> 0x17 ^ uVar11 >> 0xf ^ uVar11 ^ uVar11 >> 7) & 1) << 0x1e;
          uVar11 = uVar11 >> 1 |
                   (~(uVar11 >> 0x17 ^ uVar11 >> 0xf ^ uVar11 ^ uVar11 >> 7) & 1) << 0x1e;
          uVar11 = uVar11 >> 1 |
                   (~(uVar11 >> 0x17 ^ uVar11 >> 0xf ^ uVar11 ^ uVar11 >> 7) & 1) << 0x1e;
          uVar6 = uVar6 + 8;
          uVar12 = uVar12 - 1;
        } while (uVar12 != 0);
      }
      iVar3 = uVar8 - uVar6;
      if (uVar6 < uVar8) {
        do {
          uVar11 = uVar11 >> 1 |
                   (~(uVar11 >> 0x17 ^ uVar11 >> 0xf ^ uVar11 ^ uVar11 >> 7) & 1) << 0x1e;
          iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
      }
    }
    *(uint *)(&DAT_8032756c + iVar9) =
         uVar11 | ~(uVar11 >> 0x17 ^ uVar11 >> 0xf ^ uVar11 ^ uVar11 >> 7) << 0x1f;
    uVar5 = bitrev(*(undefined4 *)(&DAT_8032756c + iVar9));
    *(undefined4 *)(&DAT_8032756c + iVar9) = uVar5;
    iVar3 = DummyLen();
    iVar7 = ReadArrayUnlock(chan,0,&local_7c,iVar3 + 0x14,1);
    if (iVar7 < 0) {
      uVar5 = 0xfffffffd;
    }
    else {
      uVar11 = *(uint *)(&DAT_8032756c + iVar9);
      iVar7 = 4;
      uVar4 = local_7c ^ uVar11;
      do {
        uVar11 = uVar11 << 1 | ~(uVar11 << 0x17 ^ uVar11 << 0xf ^ uVar11 ^ uVar11 << 7) >> 0x1e & 2;
        uVar11 = uVar11 << 1 | ~(uVar11 << 0x17 ^ uVar11 << 0xf ^ uVar11 ^ uVar11 << 7) >> 0x1e & 2;
        uVar11 = uVar11 << 1 | ~(uVar11 << 0x17 ^ uVar11 << 0xf ^ uVar11 ^ uVar11 << 7) >> 0x1e & 2;
        uVar11 = uVar11 << 1 | ~(uVar11 << 0x17 ^ uVar11 << 0xf ^ uVar11 ^ uVar11 << 7) >> 0x1e & 2;
        uVar11 = uVar11 << 1 | ~(uVar11 << 0x17 ^ uVar11 << 0xf ^ uVar11 ^ uVar11 << 7) >> 0x1e & 2;
        uVar11 = uVar11 << 1 | ~(uVar11 << 0x17 ^ uVar11 << 0xf ^ uVar11 ^ uVar11 << 7) >> 0x1e & 2;
        uVar11 = uVar11 << 1 | ~(uVar11 << 0x17 ^ uVar11 << 0xf ^ uVar11 ^ uVar11 << 7) >> 0x1e & 2;
        uVar11 = uVar11 << 1 | ~(uVar11 << 0x17 ^ uVar11 << 0xf ^ uVar11 ^ uVar11 << 7) >> 0x1e & 2;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
      *(uint *)(&DAT_8032756c + iVar9) =
           uVar11 | ~(uVar11 << 0x17 ^ uVar11 << 0xf ^ uVar11 ^ uVar11 << 7) >> 0x1f;
      iVar7 = 4;
      uVar11 = *(uint *)(&DAT_8032756c + iVar9);
      uVar6 = local_78 ^ uVar11;
      do {
        uVar11 = uVar11 << 1 | ~(uVar11 << 0x17 ^ uVar11 << 0xf ^ uVar11 ^ uVar11 << 7) >> 0x1e & 2;
        uVar11 = uVar11 << 1 | ~(uVar11 << 0x17 ^ uVar11 << 0xf ^ uVar11 ^ uVar11 << 7) >> 0x1e & 2;
        uVar11 = uVar11 << 1 | ~(uVar11 << 0x17 ^ uVar11 << 0xf ^ uVar11 ^ uVar11 << 7) >> 0x1e & 2;
        uVar11 = uVar11 << 1 | ~(uVar11 << 0x17 ^ uVar11 << 0xf ^ uVar11 ^ uVar11 << 7) >> 0x1e & 2;
        uVar11 = uVar11 << 1 | ~(uVar11 << 0x17 ^ uVar11 << 0xf ^ uVar11 ^ uVar11 << 7) >> 0x1e & 2;
        uVar11 = uVar11 << 1 | ~(uVar11 << 0x17 ^ uVar11 << 0xf ^ uVar11 ^ uVar11 << 7) >> 0x1e & 2;
        uVar11 = uVar11 << 1 | ~(uVar11 << 0x17 ^ uVar11 << 0xf ^ uVar11 ^ uVar11 << 7) >> 0x1e & 2;
        uVar11 = uVar11 << 1 | ~(uVar11 << 0x17 ^ uVar11 << 0xf ^ uVar11 ^ uVar11 << 7) >> 0x1e & 2;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
      *(uint *)(&DAT_8032756c + iVar9) =
           uVar11 | ~(uVar11 << 0x17 ^ uVar11 << 0xf ^ uVar11 ^ uVar11 << 7) >> 0x1f;
      iVar7 = 4;
      uVar11 = *(uint *)(&DAT_8032756c + iVar9);
      uVar8 = local_74 ^ uVar11;
      do {
        uVar11 = uVar11 << 1 | ~(uVar11 << 0x17 ^ uVar11 << 0xf ^ uVar11 ^ uVar11 << 7) >> 0x1e & 2;
        uVar11 = uVar11 << 1 | ~(uVar11 << 0x17 ^ uVar11 << 0xf ^ uVar11 ^ uVar11 << 7) >> 0x1e & 2;
        uVar11 = uVar11 << 1 | ~(uVar11 << 0x17 ^ uVar11 << 0xf ^ uVar11 ^ uVar11 << 7) >> 0x1e & 2;
        uVar11 = uVar11 << 1 | ~(uVar11 << 0x17 ^ uVar11 << 0xf ^ uVar11 ^ uVar11 << 7) >> 0x1e & 2;
        uVar11 = uVar11 << 1 | ~(uVar11 << 0x17 ^ uVar11 << 0xf ^ uVar11 ^ uVar11 << 7) >> 0x1e & 2;
        uVar11 = uVar11 << 1 | ~(uVar11 << 0x17 ^ uVar11 << 0xf ^ uVar11 ^ uVar11 << 7) >> 0x1e & 2;
        uVar11 = uVar11 << 1 | ~(uVar11 << 0x17 ^ uVar11 << 0xf ^ uVar11 ^ uVar11 << 7) >> 0x1e & 2;
        uVar11 = uVar11 << 1 | ~(uVar11 << 0x17 ^ uVar11 << 0xf ^ uVar11 ^ uVar11 << 7) >> 0x1e & 2;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
      *(uint *)(&DAT_8032756c + iVar9) =
           uVar11 | ~(uVar11 << 0x17 ^ uVar11 << 0xf ^ uVar11 ^ uVar11 << 7) >> 0x1f;
      iVar7 = 4;
      uVar11 = *(uint *)(&DAT_8032756c + iVar9);
      local_70 = local_70 ^ uVar11;
      do {
        uVar11 = uVar11 << 1 | ~(uVar11 << 0x17 ^ uVar11 << 0xf ^ uVar11 ^ uVar11 << 7) >> 0x1e & 2;
        uVar11 = uVar11 << 1 | ~(uVar11 << 0x17 ^ uVar11 << 0xf ^ uVar11 ^ uVar11 << 7) >> 0x1e & 2;
        uVar11 = uVar11 << 1 | ~(uVar11 << 0x17 ^ uVar11 << 0xf ^ uVar11 ^ uVar11 << 7) >> 0x1e & 2;
        uVar11 = uVar11 << 1 | ~(uVar11 << 0x17 ^ uVar11 << 0xf ^ uVar11 ^ uVar11 << 7) >> 0x1e & 2;
        uVar11 = uVar11 << 1 | ~(uVar11 << 0x17 ^ uVar11 << 0xf ^ uVar11 ^ uVar11 << 7) >> 0x1e & 2;
        uVar11 = uVar11 << 1 | ~(uVar11 << 0x17 ^ uVar11 << 0xf ^ uVar11 ^ uVar11 << 7) >> 0x1e & 2;
        uVar11 = uVar11 << 1 | ~(uVar11 << 0x17 ^ uVar11 << 0xf ^ uVar11 ^ uVar11 << 7) >> 0x1e & 2;
        uVar11 = uVar11 << 1 | ~(uVar11 << 0x17 ^ uVar11 << 0xf ^ uVar11 ^ uVar11 << 7) >> 0x1e & 2;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
      *(uint *)(&DAT_8032756c + iVar9) =
           uVar11 | ~(uVar11 << 0x17 ^ uVar11 << 0xf ^ uVar11 ^ uVar11 << 7) >> 0x1f;
      uVar11 = iVar3 * 8;
      uVar10 = *(uint *)(&DAT_8032756c + iVar9);
      uVar12 = 0;
      local_6c = local_6c ^ uVar10;
      if (uVar11 != 0) {
        if ((8 < uVar11) && (uVar13 = uVar11 - 1 >> 3, uVar11 != 8)) {
          do {
            uVar10 = uVar10 << 1 |
                     ~(uVar10 << 0x17 ^ uVar10 << 0xf ^ uVar10 ^ uVar10 << 7) >> 0x1e & 2;
            uVar10 = uVar10 << 1 |
                     ~(uVar10 << 0x17 ^ uVar10 << 0xf ^ uVar10 ^ uVar10 << 7) >> 0x1e & 2;
            uVar10 = uVar10 << 1 |
                     ~(uVar10 << 0x17 ^ uVar10 << 0xf ^ uVar10 ^ uVar10 << 7) >> 0x1e & 2;
            uVar10 = uVar10 << 1 |
                     ~(uVar10 << 0x17 ^ uVar10 << 0xf ^ uVar10 ^ uVar10 << 7) >> 0x1e & 2;
            uVar10 = uVar10 << 1 |
                     ~(uVar10 << 0x17 ^ uVar10 << 0xf ^ uVar10 ^ uVar10 << 7) >> 0x1e & 2;
            uVar10 = uVar10 << 1 |
                     ~(uVar10 << 0x17 ^ uVar10 << 0xf ^ uVar10 ^ uVar10 << 7) >> 0x1e & 2;
            uVar10 = uVar10 << 1 |
                     ~(uVar10 << 0x17 ^ uVar10 << 0xf ^ uVar10 ^ uVar10 << 7) >> 0x1e & 2;
            uVar10 = uVar10 << 1 |
                     ~(uVar10 << 0x17 ^ uVar10 << 0xf ^ uVar10 ^ uVar10 << 7) >> 0x1e & 2;
            uVar12 = uVar12 + 8;
            uVar13 = uVar13 - 1;
          } while (uVar13 != 0);
        }
        iVar3 = uVar11 - uVar12;
        if (uVar12 < uVar11) {
          do {
            uVar10 = uVar10 << 1 |
                     ~(uVar10 << 0x17 ^ uVar10 << 0xf ^ uVar10 ^ uVar10 << 7) >> 0x1e & 2;
            iVar3 = iVar3 + -1;
          } while (iVar3 != 0);
        }
      }
      *(uint *)(&DAT_8032756c + iVar9) =
           uVar10 | ~(uVar10 << 0x17 ^ uVar10 << 0xf ^ uVar10 ^ uVar10 << 7) >> 0x1f;
      iVar3 = 4;
      uVar11 = 0;
      uVar12 = *(uint *)(&DAT_8032756c + iVar9);
      do {
        uVar12 = uVar12 << 1 | ~(uVar12 << 0x17 ^ uVar12 << 0xf ^ uVar12 ^ uVar12 << 7) >> 0x1e & 2;
        uVar12 = uVar12 << 1 | ~(uVar12 << 0x17 ^ uVar12 << 0xf ^ uVar12 ^ uVar12 << 7) >> 0x1e & 2;
        uVar12 = uVar12 << 1 | ~(uVar12 << 0x17 ^ uVar12 << 0xf ^ uVar12 ^ uVar12 << 7) >> 0x1e & 2;
        uVar12 = uVar12 << 1 | ~(uVar12 << 0x17 ^ uVar12 << 0xf ^ uVar12 ^ uVar12 << 7) >> 0x1e & 2;
        uVar12 = uVar12 << 1 | ~(uVar12 << 0x17 ^ uVar12 << 0xf ^ uVar12 ^ uVar12 << 7) >> 0x1e & 2;
        uVar12 = uVar12 << 1 | ~(uVar12 << 0x17 ^ uVar12 << 0xf ^ uVar12 ^ uVar12 << 7) >> 0x1e & 2;
        uVar12 = uVar12 << 1 | ~(uVar12 << 0x17 ^ uVar12 << 0xf ^ uVar12 ^ uVar12 << 7) >> 0x1e & 2;
        uVar12 = uVar12 << 1 | ~(uVar12 << 0x17 ^ uVar12 << 0xf ^ uVar12 ^ uVar12 << 7) >> 0x1e & 2;
        uVar11 = uVar11 + 8;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
      iVar3 = 0x21 - uVar11;
      if (uVar11 < 0x21) {
        do {
          uVar12 = uVar12 << 1 |
                   ~(uVar12 << 0x17 ^ uVar12 << 0xf ^ uVar12 ^ uVar12 << 7) >> 0x1e & 2;
          iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
      }
      *(uint *)(&DAT_8032756c + iVar9) =
           uVar12 | ~(uVar12 << 0x17 ^ uVar12 << 0xf ^ uVar12 ^ uVar12 << 7) >> 0x1f;
      *puVar1 = local_70;
      puVar1[1] = local_6c;
      *puVar2 = (uint)puVar1;
      puVar2[1] = 8;
      puVar2[3] = (uint)(puVar1 + 8);
      puVar2[2] = 0;
      DCFlushRange(puVar1,8);
      DCInvalidateRange(puVar1 + 8,4);
      DCFlushRange(puVar2,0x10);
      *(undefined4 *)(&DAT_80327574 + iVar9) = 0xff;
      *(undefined4 *)(&DAT_8032757c + iVar9) = 0x21c1e0;
      *(undefined4 *)(&DAT_80327580 + iVar9) = 0x160;
      *(undefined4 *)(&DAT_80327584 + iVar9) = 0;
      *(undefined2 *)(&DAT_80327594 + iVar9) = 0x10;
      *(code **)(&DAT_80327598 + iVar9) = InitCallback;
      *(undefined4 *)(&DAT_8032759c + iVar9) = 0;
      *(code **)(&DAT_803275a0 + iVar9) = DoneCallback;
      *(undefined4 *)(&DAT_803275a4 + iVar9) = 0;
      DSPAddTask(iVar9 + -0x7fcd8a90);
      *flashId = uVar4;
      uVar5 = 0;
      flashId[1] = uVar6;
      flashId[2] = uVar8;
    }
  }
  return uVar5;
}

