// Function: Create__Q26CChara5CAnimFPvPQ27CMemory6CStage
// Entry: 800bf984
// Size: 960 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void Create__Q26CChara5CAnimFPvPQ27CMemory6CStage(int param_1,void *param_2,CStage *stage)

{
  ushort uVar1;
  undefined4 uVar2;
  undefined uVar7;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar8;
  int iVar9;
  undefined local_128 [24];
  uint local_110;
  uint32_t local_10c;
  CChunkFile aCStack_108 [4];
  undefined4 local_48;
  undefined4 uStack_44;
  longlong local_40;
  
  __ct__10CChunkFileFPv(aCStack_108,param_2);
  *(CStage **)(param_1 + 0x2c) = stage;
  while( true ) {
    do {
      iVar6 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                        (aCStack_108,(CChunkFile *)(local_128 + 0x10));
      if (iVar6 == 0) {
        return;
      }
    } while ((uint8_t *)local_128._16_4_ != (uint8_t *)0x43484120);
    if (local_110 < 2) break;
    PushChunk__10CChunkFileFv(aCStack_108);
    while (iVar6 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                             (aCStack_108,(CChunkFile *)(local_128 + 0x10)), iVar6 != 0) {
      if ((uint8_t *)local_128._16_4_ == (uint8_t *)0x414e494d) {
        *(short *)(param_1 + 0xe) = (short)local_128._20_4_;
        uVar1 = *(ushort *)(param_1 + 0xe);
        uVar2 = __nwa__FUlPQ27CMemory6CStagePci
                          ((uint)uVar1 * 0x18 + 0x10,stage,s_chara_anim_cpp_801da980,0x5f);
        uVar2 = __construct_new_array
                          (uVar2,__ct__Q26CChara9CAnimNodeFv,__dt__Q26CChara9CAnimNodeFv,0x18,
                           (uint)uVar1);
        *(undefined4 *)(param_1 + 0x14) = uVar2;
        iVar6 = 0;
        PushChunk__10CChunkFileFv(aCStack_108);
        while (iVar5 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                 (aCStack_108,(CChunkFile *)(local_128 + 0x10)), iVar5 != 0) {
          if ((uint8_t *)local_128._16_4_ == (uint8_t *)0x494e464f) {
            uVar7 = Get4__10CChunkFileFv(aCStack_108);
            *(undefined *)(param_1 + 10) = uVar7;
            uVar7 = Get4__10CChunkFileFv(aCStack_108);
            *(undefined *)(param_1 + 0xb) = uVar7;
            uVar7 = Get4__10CChunkFileFv(aCStack_108);
            *(undefined *)(param_1 + 0xc) = uVar7;
          }
          else if ((int)local_128._16_4_ < 0x494e464f) {
            if ((uint8_t *)local_128._16_4_ == (uint8_t *)0x4652414d) {
              uStack_44 = Get4__10CChunkFileFv(aCStack_108);
              local_48 = 0x43300000;
              iVar5 = (int)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_80330c78);
              local_40 = (longlong)iVar5;
              *(short *)(param_1 + 0x10) = (short)iVar5;
            }
            else if (((int)local_128._16_4_ < 0x4652414d) &&
                    ((uint8_t *)local_128._16_4_ == (uint8_t *)0x42414e4b)) {
              *(uint32_t *)(param_1 + 0x1c) = local_10c + 0x1f & 0xffffffe0;
              uVar2 = __nwa__FUlPQ27CMemory6CStagePci
                                (local_10c,stage,s_chara_anim_cpp_801da980,0x7c);
              *(undefined4 *)(param_1 + 0x20) = uVar2;
              Get__10CChunkFileFPvl(aCStack_108,*(undefined4 *)(param_1 + 0x20),local_10c);
              CopyToAMemorySync__7CMemoryFPvPvUl
                        (&Memory,*(undefined4 *)(param_1 + 0x20),
                         Chara._8308_4_ + *(int *)(Chara._8284_4_ + 8),
                         *(undefined4 *)(param_1 + 0x1c));
              *(undefined4 *)(param_1 + 0x28) = Chara._8308_4_;
              Chara._8308_4_ = Chara._8308_4_ + *(int *)(param_1 + 0x1c);
              if (*(int *)(param_1 + 0x20) != 0) {
                __dl__FPv();
                *(undefined4 *)(param_1 + 0x20) = 0;
              }
            }
          }
          else if ((uint8_t *)local_128._16_4_ == (uint8_t *)0x4e4f4445) {
            iVar5 = *(int *)(param_1 + 0x14) + iVar6;
            iVar6 = iVar6 + 0x18;
            PushChunk__10CChunkFileFv(aCStack_108);
            while (iVar4 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                     (aCStack_108,(CChunkFile *)local_128), iVar4 != 0) {
              if (local_128._0_4_ == 0x4e414d45) {
                uVar2 = GetString__10CChunkFileFv(aCStack_108);
                strcpy(iVar5,uVar2);
              }
              else if (((int)local_128._0_4_ < 0x4e414d45) && (local_128._0_4_ == 0x44415441)) {
                iVar8 = 0;
                iVar4 = 0;
                do {
                  iVar3 = Get4__10CChunkFileFv(aCStack_108);
                  if (iVar3 == 0) {
                    iVar9 = 0;
                  }
                  else if (iVar3 == 1) {
                    iVar9 = 1;
                  }
                  else {
                    iVar9 = 2;
                  }
                  uVar2 = Get4__10CChunkFileFv(aCStack_108);
                  if (iVar8 == 0) {
                    *(undefined4 *)(iVar5 + 0x10) = uVar2;
                  }
                  *(uint *)(iVar5 + 0x14) =
                       (*(uint *)(iVar5 + 0x14) >> 0xd & 0x3ffff | iVar9 << iVar4 & 0x3ffffU) << 0xd
                       | *(uint *)(iVar5 + 0x14) & 0x80001fff;
                  if ((5 < iVar8) && (iVar3 != 0)) {
                    *(byte *)(iVar5 + 0x14) = *(byte *)(iVar5 + 0x14) & 0x7f | 0x80;
                  }
                  iVar8 = iVar8 + 1;
                  iVar4 = iVar4 + 2;
                } while (iVar8 < 9);
              }
            }
            PopChunk__10CChunkFileFv(aCStack_108);
          }
          else if (((int)local_128._16_4_ < 0x4e4f4445) &&
                  ((uint8_t *)local_128._16_4_ == (uint8_t *)0x494e5450)) {
            *(char *)(param_1 + 9) = (char)local_128._20_4_;
            uVar2 = Get4__10CChunkFileFv(aCStack_108);
            *(undefined4 *)(param_1 + 0x18) = uVar2;
          }
        }
        PopChunk__10CChunkFileFv(aCStack_108);
      }
    }
    PopChunk__10CChunkFileFv(aCStack_108);
  }
  if ((uint)System.m_execParam < 2) {
    return;
  }
  Printf__7CSystemFPce(&System,&DAT_801da990);
  return;
}

