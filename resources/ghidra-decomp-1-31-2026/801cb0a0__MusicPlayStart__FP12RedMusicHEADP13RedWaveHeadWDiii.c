// Function: _MusicPlayStart__FP12RedMusicHEADP13RedWaveHeadWDiii
// Entry: 801cb0a0
// Size: 1360 bytes

undefined4 *
_MusicPlayStart__FP12RedMusicHEADP13RedWaveHeadWDiii
          (int param_1,undefined4 param_2,int param_3,int param_4,int param_5)

{
  undefined uVar1;
  undefined uVar2;
  undefined uVar3;
  undefined uVar4;
  uint uVar5;
  int iVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined4 uVar9;
  undefined *puVar10;
  char cVar11;
  undefined *puVar12;
  int *piVar13;
  
  iVar6 = SearchWaveBase__9CRedEntryFi(&DAT_8032e154,(int)*(short *)(param_1 + 6));
  if (iVar6 == 0) {
    puVar7 = (undefined4 *)0xffffffff;
  }
  else {
    piVar13 = DAT_8032f3f0;
    if (param_5 != 0) {
      piVar13 = DAT_8032f3f0 + 0x24a;
    }
    DAT_8032f410 = param_5;
    piVar13[0x11c] = param_3;
    piVar13[0x11b] = piVar13[0x11b] & 0xfffeffff;
    piVar13[0x122] = 0;
    if (DAT_8032f42c == 0) {
      piVar13[0x115] = 0x1ff000;
      piVar13[0x117] = 0;
    }
    else {
      piVar13[0x115] = 0;
      piVar13[0x116] = 0x1ff800;
      piVar13[0x116] = piVar13[0x116] / DAT_8032f42c;
      piVar13[0x117] = DAT_8032f42c;
      DAT_8032f42c = 0;
    }
    iVar6 = RedNew__Fi(*(char *)(param_1 + 8) * 0x154);
    if (iVar6 == 0) {
      if (DAT_8032f408 != 0) {
        OSReport(s__s_sMusic_Start___Couldn_t_Creat_801e7e86,&DAT_801e7e3e,&DAT_80333d75,
                 &DAT_80333d70);
        fflush(&DAT_8021d1a8);
        OSReport(s__s_s___music_3_3u_bgm___need_0x__801e7eb2,&DAT_801e7e3e,&DAT_80333d75,
                 (int)*(short *)(param_1 + 4),*(char *)(param_1 + 8) * 0x154,&DAT_80333d70);
        fflush(&DAT_8021d1a8);
      }
      DisplayMMemoryInfo__9CRedEntryFv(&DAT_8032e154);
      puVar7 = (undefined4 *)0xffffffff;
    }
    else {
      *piVar13 = iVar6;
      if (*(char *)(param_1 + 9) != '\0') {
        uVar5 = (int)*(char *)(param_1 + 9) - 1U & 7;
        SetReverb__FiiPi(0,*(undefined4 *)(&DAT_8021ec10 + uVar5 * 0x1c),uVar5 * 0x1c + -0x7fde13ec)
        ;
      }
      *DAT_8032f474 = (int)*(short *)(param_1 + 10);
      if (*DAT_8032f474 != 0) {
        *DAT_8032f474 = *DAT_8032f474 + 1;
        *DAT_8032f474 = *DAT_8032f474 << 8;
        *DAT_8032f474 = *DAT_8032f474 + -1;
        *DAT_8032f474 = *DAT_8032f474 << 0xc;
      }
      puVar12 = (undefined *)(param_1 + 0x20);
      DAT_8032f474[1] = 0;
      cVar11 = '\0';
      DAT_8032f474[2] = 0;
      piVar13[0x11f] = (int)*(short *)(param_1 + 6);
      puVar7 = (undefined4 *)*piVar13;
      iVar6 = (int)*(char *)(param_1 + 8);
      while( true ) {
        uVar1 = puVar12[3];
        uVar2 = puVar12[2];
        uVar3 = puVar12[1];
        uVar4 = *puVar12;
        *(char *)((int)puVar7 + 0x14e) = cVar11 + -1;
        puVar7[6] = param_2;
        *puVar7 = puVar12 + 4;
        puVar12 = puVar12 + 4 + CONCAT13(uVar1,CONCAT12(uVar2,CONCAT11(uVar3,uVar4)));
        iVar8 = DeltaTimeSumup__FPPUc(puVar7);
        puVar7[0x42] = iVar8 + 1;
        puVar7[0x3d] = 0;
        if (DAT_8032f414 == 0) {
          puVar10 = (undefined *)0x0;
        }
        else {
          puVar10 = &DAT_8021dcab;
        }
        puVar7[8] = puVar10;
        puVar7[0x13] = 0x7f000;
        puVar7[0x15] = 0;
        puVar7[10] = 0x7fff000;
        puVar7[0xd] = 0x7f000;
        puVar7[0x10] = 0x40000;
        puVar7[0x1a] = *DAT_8032f474;
        puVar7[0x1c] = 0;
        puVar7[0x12] = 0;
        puVar7[0xf] = 0;
        puVar7[0xc] = 0;
        puVar7[0x45] = 0;
        puVar7[0x44] = 0;
        puVar7[0x46] = 0;
        *(undefined2 *)(puVar7 + 0x4f) = 0;
        *(undefined2 *)((int)puVar7 + 0x142) = 0;
        *(undefined *)((int)puVar7 + 0x14b) = 2;
        *(undefined2 *)((int)puVar7 + 0x13e) = 0;
        *(undefined2 *)(puVar7 + 0x50) = 0;
        *(undefined *)(puVar7 + 0x52) = 0;
        puVar7[0x2d] = 0;
        puVar7[0x25] = 0;
        puVar7[0x1d] = 0;
        puVar7[0x33] = 0;
        *(undefined2 *)(puVar7 + 0x2c) = 0;
        *(undefined2 *)(puVar7 + 0x24) = 0;
        *(undefined2 *)((int)puVar7 + 0xb2) = 0;
        *(undefined2 *)((int)puVar7 + 0x92) = 0;
        puVar7[7] = 0;
        if ((*(uint *)(param_1 + 0x14) & 0x40000) == 0) {
          uVar9 = 0x200000;
        }
        else {
          uVar9 = 0;
        }
        puVar7[0x41] = uVar9;
        *(undefined2 *)((int)puVar7 + 0x13a) = 0;
        *(undefined2 *)(puVar7 + 0x4e) = 0;
        puVar7[0x3c] = 0;
        puVar7[0x3b] = 0;
        puVar7[0x3a] = 0;
        puVar7[0x39] = 0;
        puVar7[0x38] = 0;
        puVar7[0x48] = 0xffffffff;
        *(undefined *)((int)puVar7 + 0x26) = 0;
        puVar7[0x3f] = 0xc02;
        memset(puVar7 + 0x35,0xffffffff,0xc);
        iVar6 = iVar6 + -1;
        cVar11 = cVar11 + '\x01';
        if (iVar6 == 0) break;
        puVar7 = puVar7 + 0x55;
      }
      piVar13[0x11d] = 1;
      *(undefined *)(piVar13 + 0x124) = 0;
      piVar13[0x120] = 0;
      piVar13[2] = (int)&DAT_8021dcab;
      *(undefined *)((int)piVar13 + 0x491) = *(undefined *)(param_1 + 8);
      *(short *)((int)piVar13 + 0x48e) = (short)*(char *)(param_1 + 8);
      *(byte *)((int)piVar13 + 0x492) = (byte)*(undefined2 *)(param_1 + 0xc) & 0x7f;
      *(undefined2 *)(piVar13 + 0x123) = 1;
      piVar13[0x112] = 0x1000;
      piVar13[5] = 10000;
      piVar13[4] = -1;
      piVar13[3] = 1;
      piVar13[0x11e] = 0;
      if (param_4 != 0) {
        param_4 = ((param_4 + 1) * 4 + -1) * 0x1000;
      }
      piVar13[7] = param_4;
      piVar13[9] = 0;
      piVar13[0x122] = 0;
      piVar13[0x11b] = piVar13[0x11b] & 0x10;
      if ((*(uint *)(param_1 + 0x14) & 0x40000) != 0) {
        piVar13[0x11b] = piVar13[0x11b] | 0x40000;
      }
      WaveHistoryManager__9CRedEntryFii(&DAT_8032e154,1,piVar13[0x11f]);
      MusicHistoryManager__9CRedEntryFii(&DAT_8032e154,1,param_3);
      if (DAT_8032f410 != 0) {
        OSSignalSemaphore((OSSemaphore *)&DAT_8032e120);
      }
    }
  }
  return puVar7;
}

