// Function: MakeLetterList__8GbaQueueFiPc
// Entry: 800cd850
// Size: 1436 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

int MakeLetterList__8GbaQueueFiPc(GbaQueue *gbaQueue,int param_2,void *param_3)

{
  byte bVar1;
  int iVar2;
  void *ptr;
  void *ptr_00;
  uint *ptr_01;
  undefined uVar3;
  uint32_t uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  byte bVar10;
  int iVar9;
  void *pvVar11;
  void *dstBuffer;
  uint *puVar12;
  uint32_t uVar13;
  uint uVar14;
  uint32_t uVar15;
  int iVar16;
  uint local_90;
  uint local_8c;
  uint local_84;
  uint local_80;
  uint local_7c;
  undefined4 local_78;
  undefined auStack_74 [48];
  undefined uVar4;
  
  uVar15 = Game.game.m_scriptFoodBase[param_2];
  if (uVar15 == 0) {
    bVar10 = (byte)(1 << param_2);
    gbaQueue->letterDatFlg = gbaQueue->letterDatFlg | bVar10;
    SetLetterSize__6JoyBusFii(&Joybus,param_2,0);
    iVar2 = 0;
    gbaQueue->field_0x2c89 = gbaQueue->field_0x2c89 & ~bVar10;
  }
  else {
    ptr = (void *)__nwa__FUlPQ27CMemory6CStagePci(0x800,uRam8032edac,s_gbaque_cpp_801db370,0x7a7);
    if (ptr == (void *)0x0) {
      if (System.m_execParam != 0) {
        Printf__7CSystemFPce
                  (&System,s__s__d___Error__memory_allocation_801db37c,s_gbaque_cpp_801db370,0x7a9);
      }
      iVar2 = -1;
    }
    else {
      memset(ptr,0,0x800);
      ptr_00 = (void *)__nwa__FUlPQ27CMemory6CStagePci
                                 (0x1800,uRam8032edac,s_gbaque_cpp_801db370,0x7b1);
      if (ptr_00 == (void *)0x0) {
        if (System.m_execParam != 0) {
          Printf__7CSystemFPce
                    (&System,s__s__d___Error__memory_allocation_801db37c,s_gbaque_cpp_801db370,0x7b3
                    );
        }
        iVar2 = -1;
      }
      else {
        memset(ptr_00,0,0x1800);
        ptr_01 = (uint *)__nwa__FUlPQ27CMemory6CStagePci
                                   (0x4000,uRam8032edac,s_gbaque_cpp_801db370,0x7bb);
        if (ptr_01 == (uint *)0x0) {
          if (System.m_execParam != 0) {
            Printf__7CSystemFPce
                      (&System,s__s__d___Error__memory_allocation_801db37c,s_gbaque_cpp_801db370,
                       0x7bd);
          }
          iVar2 = -1;
        }
        else {
          memset(ptr_01,0,0x800);
          uVar14 = *(uint *)(uVar15 + 1000);
          local_90 = 0;
          local_8c = 0;
          pvVar11 = ptr_00;
          dstBuffer = ptr;
          puVar12 = ptr_01;
          uVar13 = uVar15;
          for (iVar2 = 0; uVar3 = (undefined)local_90, uVar4 = (undefined)local_8c,
              iVar2 < (int)uVar14; iVar2 = iVar2 + 1) {
            iVar8 = -1;
            iVar9 = -1;
            iVar7 = 0;
            uVar5 = uVar15;
            iVar16 = iVar2;
            if (0 < iVar2) {
              do {
                if ((*(uint *)(uVar13 + 0x3ec) >> 9 & 0x1ff) ==
                    (*(uint *)(uVar5 + 0x3ec) >> 9 & 0x1ff)) {
                  iVar9 = iVar7;
                }
                if ((*(ushort *)(uVar13 + 0x3ec) >> 2 & 0x1ff) ==
                    (*(ushort *)(uVar5 + 0x3ec) >> 2 & 0x1ff)) {
                  iVar8 = iVar7;
                }
                if ((iVar9 != -1) && (iVar8 != -1)) break;
                uVar5 = uVar5 + 0xc;
                iVar7 = iVar7 + 1;
                iVar16 = iVar16 + -1;
              } while (iVar16 != 0);
            }
            if (iVar9 == -1) {
              if ((0x7f < (int)local_8c) && (System.m_execParam != 0)) {
                Printf__7CSystemFPce
                          (&System,s__s__d___Error__NPC_max_over___801db438,s_gbaque_cpp_801db370,
                           0x7dc);
              }
              memset(auStack_74,0,0x20);
              strcpy(auStack_74,
                     *(undefined4 *)
                      ((int)Game.game.m_cFlatDataArr[1].m_table[2].index +
                      (*(uint *)(uVar13 + 0x3ec) >> 7 & 0x7fc)));
              memcpy(dstBuffer,auStack_74,0x10);
              dstBuffer = (void *)((int)dstBuffer + 0x10);
              local_8c = local_8c + 1;
              *(undefined *)((int)puVar12 + 5) = uVar4;
            }
            else {
              *(undefined *)((int)puVar12 + 5) = *(undefined *)((int)ptr_01 + iVar9 * 8 + 5);
            }
            if (iVar8 == -1) {
              if (0xff < (int)local_90) {
                if (System.m_execParam != 0) {
                  Printf__7CSystemFPce
                            (&System,s__s__d___Error__Subject_max_over__801db458,
                             s_gbaque_cpp_801db370,0x7f0);
                }
              }
              memset(auStack_74,0,0x20);
              strcpy(auStack_74,
                     *(undefined4 *)
                      ((int)Game.game.m_cFlatDataArr[1].m_table[5].index +
                      (*(ushort *)(uVar13 + 0x3ec) & 0x7fc)));
              memcpy(pvVar11,auStack_74,0x18);
              pvVar11 = (void *)((int)pvVar11 + 0x18);
              local_90 = local_90 + 1;
              *(undefined *)(puVar12 + 1) = uVar3;
            }
            else {
              *(undefined *)(puVar12 + 1) = *(undefined *)(ptr_01 + iVar8 * 2 + 1);
            }
            bVar10 = 0;
            if (*(char *)(uVar13 + 0x3ec) < '\0') {
              bVar10 = (byte)DAT_80330d58;
            }
            if ((*(byte *)(uVar13 + 0x3ec) >> 6 & 1) != 0) {
              bVar10 = bVar10 | (byte)DAT_80330d5c;
            }
            if ((*(byte *)(uVar13 + 0x3ec) >> 5 & 1) != 0) {
              bVar10 = bVar10 | (byte)DAT_80330d60;
            }
            if ((*(byte *)(uVar13 + 0x3ec) >> 4 & 1) != 0) {
              bVar10 = bVar10 | (byte)DAT_80330d64;
            }
            bVar1 = *(byte *)(uVar13 + 0x3ec) >> 3 & 1;
            if (bVar1 == 0) {
              uVar6 = *(ushort *)(uVar13 + 0x3ee) & 0x1ff;
              if ((*(ushort *)(uVar13 + 0x3ee) & 0x1ff) == 0) goto LAB_800cdc88;
              if ((uVar6 < 0x100) || (0x124 < uVar6)) {
                bVar10 = bVar10 | (byte)DAT_80330d68;
                *puVar12 = uVar6 << 0x18 | (uVar6 >> 8) << 0x10;
              }
              else if (System.m_execParam != 0) {
                Printf__7CSystemFPce
                          (&System,s__s__d___Error__Letter_data_error_801db47c,s_gbaque_cpp_801db370
                           ,0x810,param_2,iVar2);
              }
            }
            else {
LAB_800cdc88:
              if (bVar1 != 0) {
                uVar6 = *(ushort *)(uVar13 + 0x3ee) & 0x1ff;
                if ((*(ushort *)(uVar13 + 0x3ee) & 0x1ff) != 0) {
                  bVar10 = bVar10 | (byte)DAT_80330d6c;
                  *puVar12 = uVar6 * 0x64000000 | (uVar6 * 100 >> 8) << 0x10;
                }
              }
            }
            *(byte *)((int)puVar12 + 6) = bVar10;
            uVar13 = uVar13 + 0xc;
            puVar12 = puVar12 + 2;
          }
          memset(&local_84,0,0x10);
          local_84 = uVar14 << 0x18 | (uVar14 >> 8 & 0xff) << 0x10 | (uVar14 >> 0x10 & 0xff) << 8 |
                     uVar14 >> 0x18;
          local_80 = local_90 << 0x18 | (local_90 >> 8 & 0xff) << 0x10 |
                     (local_90 >> 0x10 & 0xff) << 8 | local_90 >> 0x18;
          local_7c = local_8c << 0x18 | (local_8c >> 8 & 0xff) << 0x10 |
                     (local_8c >> 0x10 & 0xff) << 8 | local_8c >> 0x18;
          local_78 = CFlat._66568_4_;
          memcpy(param_3,&local_84,0x10);
          iVar2 = uVar14 * 8;
          memcpy((void *)((int)param_3 + 0x10),ptr_01,iVar2);
          pvVar11 = (void *)((int)param_3 + 0x10 + iVar2);
          iVar9 = local_90 * 0x18;
          memcpy(pvVar11,ptr_00,iVar9);
          memcpy((void *)((int)pvVar11 + iVar9),ptr,local_8c * 0x10);
          iVar2 = iVar2 + 0x10 + iVar9 + local_8c * 0x10;
          __dla__FPv(ptr_01);
          __dla__FPv(ptr_00);
          __dla__FPv(ptr);
          bVar10 = (byte)(1 << param_2);
          gbaQueue->letterDatFlg = gbaQueue->letterDatFlg | bVar10;
          SetLetterSize__6JoyBusFii(&Joybus,param_2,iVar2);
          gbaQueue->field_0x2c89 = gbaQueue->field_0x2c89 & ~bVar10;
        }
      }
    }
  }
  return iVar2;
}

