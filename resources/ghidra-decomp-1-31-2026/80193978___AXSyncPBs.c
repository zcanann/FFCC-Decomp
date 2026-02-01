// Function: __AXSyncPBs
// Entry: 80193978
// Size: 616 bytes

void __AXSyncPBs(int param_1)

{
  ushort uVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  uint uVar5;
  
  DAT_8032f298 = 0;
  DCInvalidateRange(&DAT_80314940,0x3b00);
  DCInvalidateRange(&DAT_80318440,0x1000);
  iVar2 = __AXGetCommandListCycles();
  iVar4 = 0x1f;
  uVar5 = iVar2 + param_1 + 0xaa10;
  do {
    puVar3 = (undefined4 *)__AXGetStackHead(iVar4);
    while( true ) {
      if (puVar3 == (undefined4 *)0x0) break;
      if (puVar3[8] != 0) {
        __AXDepopVoice(&DAT_80314940 + puVar3[6] * 0x76);
      }
      if ((*(short *)((int)puVar3 + 0x146) == 1) || (puVar3[10] != 0)) {
        if (*(short *)(puVar3 + 0x50) != 2) {
          uVar5 = uVar5 + *(int *)(&DAT_80217d28 + (uint)*(ushort *)((int)puVar3 + 0x1de) * 4);
        }
        uVar1 = *(ushort *)(puVar3 + 0x51);
        uVar5 = *(int *)(&DAT_80217d3c + (uVar1 & 0xf) * 4) +
                *(int *)(&DAT_80217d7c + (uVar1 >> 2 & 0x7c)) +
                *(int *)(&DAT_80217d7c + (uVar1 >> 7 & 0x7c)) + 0x8c + uVar5;
        if (uVar5 < DAT_8032f290) {
          __AXServiceVPB(puVar3);
        }
        else {
          iVar2 = puVar3[6] * 0xec;
          if (*(short *)((int)&DAT_8031494c + iVar2 + 2) == 1) {
            __AXDepopVoice(&DAT_80314940 + puVar3[6] * 0x76);
          }
          *(undefined2 *)(&DAT_8031498c + iVar2) = 0;
          *(undefined2 *)(&DAT_8031498a + iVar2) = 0;
          *(undefined2 *)(&DAT_80314988 + iVar2) = 0;
          *(undefined2 *)(&DAT_80314986 + iVar2) = 0;
          *(undefined2 *)(&DAT_80314984 + iVar2) = 0;
          *(undefined2 *)((int)&DAT_8031494c + iVar2 + 2) = 0;
          *(undefined2 *)((int)puVar3 + 0x146) = 0;
          __AXPushCallbackStack(puVar3);
        }
      }
      else {
        __AXServiceVPB(puVar3);
      }
      puVar3[7] = 0;
      puVar3[8] = 0;
      puVar3[10] = 0;
      puVar3[9] = 0;
      puVar3[0xc] = puVar3 + 0xd;
      puVar3 = (undefined4 *)*puVar3;
    }
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  DAT_8032f294 = uVar5;
  for (puVar3 = (undefined4 *)__AXGetStackHead(0); puVar3 != (undefined4 *)0x0;
      puVar3 = (undefined4 *)*puVar3) {
    if (puVar3[8] != 0) {
      __AXDepopVoice(&DAT_80314940 + puVar3[6] * 0x76);
    }
    puVar3[8] = 0;
    *(undefined2 *)(&DAT_8031498c + puVar3[6] * 0xec) = 0;
    *(undefined2 *)(&DAT_8031498a + puVar3[6] * 0xec) = 0;
    *(undefined2 *)(&DAT_80314988 + puVar3[6] * 0xec) = 0;
    *(undefined2 *)(&DAT_80314986 + puVar3[6] * 0xec) = 0;
    *(undefined2 *)(&DAT_80314984 + puVar3[6] * 0xec) = 0;
    *(undefined2 *)((int)&DAT_8031494c + puVar3[6] * 0xec + 2) = 0;
  }
  DCFlushRange(&DAT_80314940,0x3b00);
  DCFlushRange(&DAT_80318440,0x1000);
  DCFlushRange(&DAT_80319440,0x4000);
  return;
}

