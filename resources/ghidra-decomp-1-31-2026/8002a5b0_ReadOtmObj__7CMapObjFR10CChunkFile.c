// Function: ReadOtmObj__7CMapObjFR10CChunkFile
// Entry: 8002a5b0
// Size: 6240 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4 ReadOtmObj__7CMapObjFR10CChunkFile(CMapObj *mapObj,CChunkFile *chunkFile)

{
  float fVar1;
  float fVar2;
  int iVar3;
  short sVar10;
  short sVar11;
  undefined4 *puVar4;
  undefined2 uVar12;
  undefined4 uVar5;
  undefined uVar13;
  uint uVar6;
  char cVar14;
  float *pfVar7;
  int iVar8;
  int iVar9;
  undefined4 *puVar15;
  double dVar16;
  undefined local_88 [32];
  uint32_t local_68;
  int32_t local_64;
  uchar *local_60;
  longlong local_58;
  
  Init__7CMapObjFv();
  PushChunk__10CChunkFileFv(chunkFile);
  iVar3 = (int)&mapObj[0x8861ba].field_0xe8 / 0xf0 + ((int)&mapObj[0x8861ba].field_0xe8 >> 0x1f);
  iVar3 = iVar3 - (iVar3 >> 0x1f);
  while (iVar9 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                           (chunkFile,(CChunkFile *)&local_68), iVar9 != 0) {
    if (local_68 == 0x4d494d45) {
      if (*(int *)&mapObj->field_0xec != 0) {
        Printf__7CSystemFPce(&System,&DAT_801d718c,iVar3);
      }
      puVar4 = (undefined4 *)
               __nw__FUlPQ27CMemory6CStagePci(0x3c,MapMng._0_4_,s_mapobj_cpp_801d70c0,0x33b);
      if (puVar4 != (undefined4 *)0x0) {
        *puVar4 = &PTR_PTR_s_CMapObjAtr_801e8950;
        *puVar4 = &PTR_PTR_s_CMapObjAtrMime_801e88fc;
        puVar4[0xb] = 0;
        puVar4[0xc] = 0;
        puVar4[0xd] = 0;
        puVar4[0xe] = 0;
        *(undefined *)((int)puVar4 + 0x17) = 1;
        *(undefined *)(puVar4 + 6) = 0;
        puVar4[1] = 2;
        puVar4[3] = 0;
      }
      PushChunk__10CChunkFileFv(chunkFile);
      while (iVar9 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                               (chunkFile,(CChunkFile *)(local_88 + 0x10)), iVar9 != 0) {
        uVar13 = (undefined)local_88._20_4_;
        if ((uint8_t *)local_88._16_4_ == (uint8_t *)0x4b455920) {
          ReadKey__12CMapKeyFrameFR10CChunkFilei((CMapKeyFrame *)(puVar4 + 5),chunkFile,uVar13);
        }
        else if ((int)local_88._16_4_ < 0x4b455920) {
          if ((uint8_t *)local_88._16_4_ == (uint8_t *)0x4a554e20) {
            ReadJun__12CMapKeyFrameFR10CChunkFilei((CMapKeyFrame *)(puVar4 + 5),chunkFile,uVar13);
          }
          else if (((int)local_88._16_4_ < 0x4a554e20) &&
                  ((uint8_t *)local_88._16_4_ == (uint8_t *)0x4652414d)) {
            ReadFrame__12CMapKeyFrameFR10CChunkFilei((CMapKeyFrame *)(puVar4 + 5),chunkFile);
          }
        }
        else if ((uint8_t *)local_88._16_4_ == (uint8_t *)0x5654584c) {
          *(undefined *)(puVar4 + 2) = uVar13;
          uVar5 = __nwa__FUlPQ27CMemory6CStagePci
                            ((uint)*(byte *)(puVar4 + 2) << 2,MapMng._0_4_,s_mapobj_cpp_801d70c0,
                             0x348);
          puVar4[3] = uVar5;
          PushChunk__10CChunkFileFv(chunkFile);
          iVar9 = 0;
          while (iVar8 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                   (chunkFile,(CChunkFile *)local_88), iVar8 != 0) {
            if (local_88._0_4_ == 0x56545820) {
              pfVar7 = (float *)__nwa__FUlPQ27CMemory6CStagePci
                                          (local_88._4_4_ * 0xc,MapMng._0_4_,s_mapobj_cpp_801d70c0,
                                           0x353);
              *(float **)(puVar4[3] + iVar9) = pfVar7;
              iVar9 = iVar9 + 4;
              puVar4[4] = local_88._4_4_;
              for (iVar8 = 0; iVar8 < (int)puVar4[4]; iVar8 = iVar8 + 1) {
                dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
                *pfVar7 = (float)dVar16;
                dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
                pfVar7[1] = (float)dVar16;
                dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
                pfVar7[2] = (float)dVar16;
                pfVar7 = pfVar7 + 3;
              }
            }
          }
          PopChunk__10CChunkFileFv(chunkFile);
        }
      }
      PopChunk__10CChunkFileFv(chunkFile);
      *(undefined4 **)&mapObj->field_0xec = puVar4;
    }
    else if ((int)local_68 < 0x4d494d45) {
      if (local_68 == 0x47424944) {
        uVar12 = Get2__10CChunkFileFv(chunkFile);
        *(undefined2 *)&mapObj->field_0x32 = uVar12;
      }
      else if ((int)local_68 < 0x47424944) {
        if (local_68 == 0x424f424a) {
          uVar12 = Get2__10CChunkFileFv(chunkFile);
          *(undefined2 *)&mapObj->field_0x16 = uVar12;
        }
        else if ((int)local_68 < 0x424f424a) {
          if (local_68 == 0x414e494d) {
            puVar4 = (undefined4 *)
                     __nw__FUlPQ27CMemory6CStagePci(0x14,MapMng._0_4_,s_mapobj_cpp_801d70c0,0x21e);
            if (puVar4 != (undefined4 *)0x0) {
              *puVar4 = 0xffffffff;
            }
            uVar12 = Get4__10CChunkFileFv(chunkFile);
            *(undefined2 *)((int)puVar4 + 0x12) = uVar12;
            uVar5 = Get4__10CChunkFileFv(chunkFile);
            puVar4[1] = uVar5;
            uVar5 = Get4__10CChunkFileFv(chunkFile);
            puVar4[2] = uVar5;
            uVar5 = Get4__10CChunkFileFv(chunkFile);
            puVar4[3] = uVar5;
            uVar13 = Get1__10CChunkFileFv(chunkFile);
            *(undefined *)(puVar4 + 4) = uVar13;
            if (local_60 == (uchar *)0x1) {
              uVar13 = Get1__10CChunkFileFv(chunkFile);
              *(undefined *)((int)puVar4 + 0x11) = uVar13;
            }
            else {
              *(undefined *)((int)puVar4 + 0x11) = 0;
            }
            Add__25CPtrArray<P11CMapAnimRun>FP11CMapAnimRun(0x80266b44,puVar4);
          }
          else if (((int)local_68 < 0x414e494d) && (local_68 == 0x414d4249)) {
            uVar13 = Get1__10CChunkFileFv(chunkFile);
            mapObj->field_0xe8 = uVar13;
            uVar13 = Get1__10CChunkFileFv(chunkFile);
            mapObj->field_0xe9 = uVar13;
            uVar13 = Get1__10CChunkFileFv(chunkFile);
            mapObj->field_0xea = uVar13;
            uVar13 = Get1__10CChunkFileFv(chunkFile);
            mapObj->field_0xeb = uVar13;
            mapObj->field_0x21 = 1;
          }
        }
        else if (local_68 == 0x46534457) {
          CameraPcs._1028_1_ = Get1__10CChunkFileFv(chunkFile);
        }
        else if (((int)local_68 < 0x46534457) && (local_68 == 0x45464944)) {
          uVar12 = Get2__10CChunkFileFv(chunkFile);
          *(undefined2 *)&mapObj->field_0x30 = uVar12;
        }
      }
      else if (local_68 == 0x4c534457) {
        puVar4 = (undefined4 *)
                 __nw__FUlPQ27CMemory6CStagePci(0xf4,MapMng._0_4_,s_mapobj_cpp_801d70c0,0x241);
        if (puVar4 != (undefined4 *)0x0) {
          __construct_array(puVar4 + 0x30,__ct__6CBoundFv,0,0x18,2);
          *puVar4 = 1;
          *(undefined2 *)(puVar4 + 1) = 0;
          puVar4[3] = 0;
          puVar4[4] = 0;
          puVar4[5] = 0;
        }
        *(undefined *)((int)puVar4 + 9) = 0;
        if (local_60 == (uchar *)0x4) {
          uVar12 = Get4__10CChunkFileFv(chunkFile);
          *(undefined2 *)(puVar4 + 1) = uVar12;
          uVar6 = Get2__10CChunkFileFv(chunkFile);
          puVar4[3] = (uVar6 & 0xffff) * 0xf0 + -0x7fdb9f48;
          uVar6 = Get2__10CChunkFileFv(chunkFile);
          puVar4[4] = (uVar6 & 0xffff) * 0xf0 + -0x7fdb9f48;
          uVar6 = Get2__10CChunkFileFv(chunkFile);
          puVar4[5] = (uVar6 & 0xffff) * 0xf0 + -0x7fdb9f48;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)((int)puVar4 + 6) = uVar13;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)(puVar4 + 2) = uVar13;
          uVar6 = Get1__10CChunkFileFv(chunkFile);
          uVar6 = countLeadingZeros(uVar6 & 0xff);
          *(char *)((int)puVar4 + 0xf1) = (char)(uVar6 >> 5);
          uVar6 = Get1__10CChunkFileFv(chunkFile);
          uVar6 = countLeadingZeros(uVar6 & 0xff);
          *(char *)(puVar4 + 0x3c) = (char)(uVar6 >> 5);
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)((int)puVar4 + 9) = uVar13;
          Get1__10CChunkFileFv(chunkFile);
          dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
          puVar4[0x2d] = (float)dVar16;
          dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
          puVar4[0x2a] = (float)dVar16;
          dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
          puVar4[0x2b] = (float)dVar16;
          dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
          puVar4[0x2c] = (float)dVar16;
          dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
          puVar4[0x2e] = (float)dVar16;
          dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
          puVar4[0x2f] = (float)dVar16;
          dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
          puVar4[0x30] = (float)dVar16;
          dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
          puVar4[0x31] = (float)dVar16;
          dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
          puVar4[0x32] = (float)dVar16;
          dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
          puVar4[0x33] = (float)dVar16;
          dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
          puVar4[0x34] = (float)dVar16;
          dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
          puVar4[0x35] = (float)dVar16;
        }
        else if (local_60 == (uchar *)0x3) {
          uVar12 = Get4__10CChunkFileFv(chunkFile);
          *(undefined2 *)(puVar4 + 1) = uVar12;
          uVar6 = Get2__10CChunkFileFv(chunkFile);
          puVar4[3] = (uVar6 & 0xffff) * 0xf0 + -0x7fdb9f48;
          uVar6 = Get2__10CChunkFileFv(chunkFile);
          puVar4[4] = (uVar6 & 0xffff) * 0xf0 + -0x7fdb9f48;
          uVar6 = Get2__10CChunkFileFv(chunkFile);
          puVar4[5] = (uVar6 & 0xffff) * 0xf0 + -0x7fdb9f48;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)((int)puVar4 + 6) = uVar13;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)(puVar4 + 2) = uVar13;
          Get1__10CChunkFileFv(chunkFile);
          Get1__10CChunkFileFv(chunkFile);
          Get1__10CChunkFileFv(chunkFile);
          Get1__10CChunkFileFv(chunkFile);
          dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
          puVar4[0x2a] = (float)dVar16;
          dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
          puVar4[0x2b] = (float)dVar16;
          dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
          puVar4[0x2c] = (float)dVar16;
          dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
          puVar4[0x2e] = (float)dVar16;
          dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
          puVar4[0x2f] = (float)dVar16;
          dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
          puVar4[0x30] = (float)dVar16;
          dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
          puVar4[0x31] = (float)dVar16;
          dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
          puVar4[0x32] = (float)dVar16;
          dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
          puVar4[0x33] = (float)dVar16;
          dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
          puVar4[0x34] = (float)dVar16;
          dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
          puVar4[0x35] = (float)dVar16;
          fVar1 = FLOAT_8032f940;
          *(undefined *)((int)puVar4 + 0xf1) = 1;
          *(undefined *)(puVar4 + 0x3c) = 1;
          puVar4[0x2d] = fVar1;
        }
        puVar4[0x36] = (float)puVar4[0x30] * (float)puVar4[0x2d];
        puVar4[0x37] = (float)puVar4[0x31] * (float)puVar4[0x2d];
        puVar4[0x38] = (float)puVar4[0x32] * (float)puVar4[0x2d];
        puVar4[0x39] = (float)puVar4[0x33] * (float)puVar4[0x2d];
        puVar4[0x3a] = (float)puVar4[0x34] * (float)puVar4[0x2d];
        puVar4[0x3b] = (float)puVar4[0x35] * (float)puVar4[0x2d];
        Add__24CPtrArray<P10CMapShadow>FP10CMapShadow(&MapMng.m_mapShadowArray,puVar4);
      }
      else if ((int)local_68 < 0x4c534457) {
        if (local_68 == 0x49442020) {
          uVar12 = Get2__10CChunkFileFv(chunkFile);
          *(undefined2 *)&mapObj->field_0x2e = uVar12;
        }
        else if (((int)local_68 < 0x49442020) && (local_68 == 0x47454f4d)) {
          dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
          *(float *)&mapObj->field_0x40 = (float)dVar16;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          mapObj->field_0x1a = uVar13;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          mapObj->field_0x27 = uVar13;
        }
      }
      else if (local_68 == 0x4c545354) {
        if (local_60 == (uchar *)0x1) {
          uVar5 = Get4__10CChunkFileFv(chunkFile);
          *(undefined4 *)&mapObj->field_0x38 = uVar5;
        }
        else {
          cVar14 = Get1__10CChunkFileFv(chunkFile);
          if (cVar14 == '\0') {
            *(undefined4 *)&mapObj->field_0x38 = 0;
          }
        }
      }
    }
    else if (local_68 == 0x53445354) {
      if (local_60 == (uchar *)0x2) {
        uVar13 = Get1__10CChunkFileFv(chunkFile);
        mapObj->field_0x22 = uVar13;
        Get1__10CChunkFileFv(chunkFile);
        Get1__10CChunkFileFv(chunkFile);
        Get1__10CChunkFileFv(chunkFile);
        uVar5 = Get4__10CChunkFileFv(chunkFile);
        *(undefined4 *)&mapObj->field_0x3c = uVar5;
      }
      else if (local_60 == (uchar *)0x1) {
        uVar13 = Get1__10CChunkFileFv(chunkFile);
        mapObj->field_0x22 = uVar13;
        cVar14 = Get1__10CChunkFileFv(chunkFile);
        if (cVar14 == '\0') {
          *(undefined4 *)&mapObj->field_0x3c = 0;
        }
        else {
          *(undefined4 *)&mapObj->field_0x3c = 0xffffffff;
        }
      }
      else {
        uVar13 = Get1__10CChunkFileFv(chunkFile);
        mapObj->field_0x22 = uVar13;
        *(undefined4 *)&mapObj->field_0x3c = 0xffffffff;
      }
    }
    else if ((int)local_68 < 0x53445354) {
      if (local_68 == 0x504c4954) {
        if (*(int *)&mapObj->field_0xec != 0) {
          Printf__7CSystemFPce(&System,&DAT_801d718c,iVar3);
        }
        puVar4 = (undefined4 *)
                 __nw__FUlPQ27CMemory6CStagePci(0xf4,MapMng._0_4_,s_mapobj_cpp_801d70c0,0xd4);
        if (puVar4 != (undefined4 *)0x0) {
          *puVar4 = &PTR_PTR_s_CMapObjAtr_801e8950;
          *puVar4 = &PTR_PTR_s_CMapObjAtrPointLight_801e892c;
          puVar4[0x2f] = 0;
          puVar4[0x30] = 0;
          puVar4[0x31] = 0;
          puVar4[0x32] = 0;
          *(undefined *)((int)puVar4 + 0xa7) = 1;
          *(undefined *)(puVar4 + 0x2a) = 0;
          puVar4[0x39] = 0;
          puVar4[0x3a] = 0;
          puVar4[0x3b] = 0;
          puVar4[0x3c] = 0;
          *(undefined *)((int)puVar4 + 0xcf) = 1;
          *(undefined *)(puVar4 + 0x34) = 0;
          puVar4[1] = 0;
          *(undefined *)(puVar4 + 7) = 0;
          *(undefined *)(puVar4 + 8) = 0;
        }
        if (local_60 == (uchar *)0x2) {
          PushChunk__10CChunkFileFv(chunkFile);
          while (iVar9 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                   (chunkFile,(CChunkFile *)&local_68), iVar9 != 0) {
            if (local_68 == 0x4c444154) {
              dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
              puVar4[4] = (float)dVar16;
              dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
              puVar4[5] = (float)dVar16;
              uVar13 = Get1__10CChunkFileFv(chunkFile);
              *(undefined *)(puVar4 + 7) = uVar13;
              uVar13 = Get1__10CChunkFileFv(chunkFile);
              *(undefined *)((int)puVar4 + 0x1f) = uVar13;
              uVar13 = Get1__10CChunkFileFv(chunkFile);
              *(undefined *)(puVar4 + 8) = uVar13;
              Get1__10CChunkFileFv(chunkFile);
              uVar13 = Get1__10CChunkFileFv(chunkFile);
              *(undefined *)((int)puVar4 + 0x1d) = uVar13;
              puVar15 = puVar4;
              for (iVar9 = 0; iVar9 < (int)(uint)*(byte *)((int)puVar4 + 0x1d); iVar9 = iVar9 + 1) {
                uVar13 = Get1__10CChunkFileFv(chunkFile);
                *(undefined *)(puVar15 + 9) = uVar13;
                uVar13 = Get1__10CChunkFileFv(chunkFile);
                *(undefined *)((int)puVar15 + 0x25) = uVar13;
                uVar13 = Get1__10CChunkFileFv(chunkFile);
                *(undefined *)((int)puVar15 + 0x26) = uVar13;
                uVar13 = Get1__10CChunkFileFv(chunkFile);
                *(undefined *)((int)puVar15 + 0x27) = uVar13;
                puVar15 = puVar15 + 1;
              }
              uVar13 = Get1__10CChunkFileFv(chunkFile);
              *(undefined *)((int)puVar4 + 0x1e) = uVar13;
              puVar15 = puVar4;
              for (iVar9 = 0; iVar9 < (int)(uint)*(byte *)((int)puVar4 + 0x1e); iVar9 = iVar9 + 1) {
                uVar13 = Get1__10CChunkFileFv(chunkFile);
                *(undefined *)(puVar15 + 0x19) = uVar13;
                uVar13 = Get1__10CChunkFileFv(chunkFile);
                *(undefined *)((int)puVar15 + 0x65) = uVar13;
                uVar13 = Get1__10CChunkFileFv(chunkFile);
                *(undefined *)((int)puVar15 + 0x66) = uVar13;
                uVar13 = Get1__10CChunkFileFv(chunkFile);
                *(undefined *)((int)puVar15 + 0x67) = uVar13;
                puVar15 = puVar15 + 1;
              }
              *(undefined *)(puVar4 + 2) = *(undefined *)(puVar4 + 9);
              *(undefined *)((int)puVar4 + 9) = *(undefined *)((int)puVar4 + 0x25);
              *(undefined *)((int)puVar4 + 10) = *(undefined *)((int)puVar4 + 0x26);
              *(undefined *)((int)puVar4 + 0xb) = *(undefined *)((int)puVar4 + 0x27);
              *(undefined *)(puVar4 + 3) = *(undefined *)(puVar4 + 0x19);
              *(undefined *)((int)puVar4 + 0xd) = *(undefined *)((int)puVar4 + 0x65);
              *(undefined *)((int)puVar4 + 0xe) = *(undefined *)((int)puVar4 + 0x66);
              *(undefined *)((int)puVar4 + 0xf) = *(undefined *)((int)puVar4 + 0x67);
            }
            else {
              uVar13 = (undefined)local_64;
              if ((int)local_68 < 0x4c444154) {
                if (local_68 == 0x434a554e) {
                  ReadJun__12CMapKeyFrameFR10CChunkFilei
                            ((CMapKeyFrame *)(puVar4 + 0x33),chunkFile,uVar13);
                }
                else if ((int)local_68 < 0x434a554e) {
                  if (local_68 == 0x4346524d) {
                    ReadFrame__12CMapKeyFrameFR10CChunkFilei
                              ((CMapKeyFrame *)(puVar4 + 0x33),chunkFile);
                  }
                }
                else if (local_68 == 0x434b4559) {
                  ReadKey__12CMapKeyFrameFR10CChunkFilei
                            ((CMapKeyFrame *)(puVar4 + 0x33),chunkFile,uVar13);
                }
              }
              else if (local_68 == 0x4d4a554e) {
                ReadJun__12CMapKeyFrameFR10CChunkFilei
                          ((CMapKeyFrame *)(puVar4 + 0x29),chunkFile,uVar13);
              }
              else if ((int)local_68 < 0x4d4a554e) {
                if (local_68 == 0x4d46524d) {
                  ReadFrame__12CMapKeyFrameFR10CChunkFilei
                            ((CMapKeyFrame *)(puVar4 + 0x29),chunkFile);
                }
              }
              else if (local_68 == 0x4d4b4559) {
                ReadKey__12CMapKeyFrameFR10CChunkFilei
                          ((CMapKeyFrame *)(puVar4 + 0x29),chunkFile,uVar13);
              }
            }
          }
          PopChunk__10CChunkFileFv(chunkFile);
        }
        else if (local_60 == (uchar *)0x1) {
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)(puVar4 + 2) = uVar13;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)((int)puVar4 + 9) = uVar13;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)((int)puVar4 + 10) = uVar13;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)((int)puVar4 + 0xb) = uVar13;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)(puVar4 + 3) = uVar13;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)((int)puVar4 + 0xd) = uVar13;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)((int)puVar4 + 0xe) = uVar13;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)((int)puVar4 + 0xf) = uVar13;
          dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
          puVar4[4] = (float)dVar16;
          dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
          puVar4[5] = (float)dVar16;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)(puVar4 + 7) = uVar13;
        }
        *(undefined4 **)&mapObj->field_0xec = puVar4;
      }
      else if ((int)local_68 < 0x504c4954) {
        if (local_68 == 0x50494458) {
          sVar10 = Get2__10CChunkFileFv(chunkFile);
          sVar11 = Get2__10CChunkFileFv(chunkFile);
          iVar9 = (int)sVar11;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          mapObj->field_0x1e = uVar13;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          mapObj->field_0x1d = uVar13;
          if (sVar10 == -1) {
            *(undefined4 *)mapObj = 0;
          }
          else {
            *(int *)mapObj = sVar10 * 0xf0 + -0x7fdb9f48;
          }
          if (iVar9 == -1) {
            mapObj->field12_0xc = (CMapHit *)0x0;
          }
          else {
            cVar14 = mapObj->field_0x1d;
            if (cVar14 == '\x01') {
              mapObj->field12_0xc = (CMapHit *)(MapMng.mapMeshArr + iVar9);
              mapObj->field_0x14 = 0;
              mapObj->field_0x15 = 0;
            }
            else if ((cVar14 == '\x02') || (cVar14 == '\x03')) {
              if (iVar9 == -2) {
                puVar4 = (undefined4 *)
                         __nw__FUlPQ27CMemory6CStagePci
                                   (0x28,MapMng._0_4_,s_mapobj_cpp_801d70c0,0x84);
                if (puVar4 != (undefined4 *)0x0) {
                  *puVar4 = &PTR_PTR_s_CMapObjAtr_801e8950;
                  *puVar4 = &PTR_PTR_s_CMapObjAtrMeshName_801e8944;
                  puVar4[1] = 3;
                }
                *(undefined4 **)&mapObj->field_0xec = puVar4;
                uVar5 = GetString__10CChunkFileFv(chunkFile);
                strncpy(puVar4 + 2,uVar5,0x20);
              }
              else {
                mapObj->field12_0xc = MapMng.mapHits + iVar9;
              }
            }
          }
          fVar2 = FLOAT_8032f944;
          fVar1 = FLOAT_8032f940;
          if ((((Game.game.m_currentSceneId == 4) || (Game.game.m_currentSceneId == 7)) &&
              ((char)mapObj->field_0x1e < '\n')) && ('\a' < (char)mapObj->field_0x1e)) {
            (mapObj->m_translationRate).x = FLOAT_8032f940;
            (mapObj->m_translationRate).y = fVar2;
            (mapObj->m_translationRate).z = fVar1;
          }
        }
        else if (((int)local_68 < 0x50494458) && (local_68 == 0x4d534944)) {
          uVar12 = Get4__10CChunkFileFv(chunkFile);
          *(undefined2 *)&mapObj->field_0x34 = uVar12;
        }
      }
      else if (local_68 == 0x50535441) {
        if (*(int *)&mapObj->field_0xec != 0) {
          Printf__7CSystemFPce(&System,&DAT_801d718c,iVar3);
        }
        puVar4 = (undefined4 *)
                 __nw__FUlPQ27CMemory6CStagePci(0xc,MapMng._0_4_,s_mapobj_cpp_801d70c0,0x39b);
        if (puVar4 != (undefined4 *)0x0) {
          *puVar4 = &PTR_PTR_s_CMapObjAtr_801e8950;
          *puVar4 = &PTR_PTR_s_CMapObjAtrPlaySta_801e88e4;
          puVar4[1] = 4;
        }
        uVar13 = Get1__10CChunkFileFv(chunkFile);
        *(undefined *)(puVar4 + 2) = uVar13;
        *(undefined4 **)&mapObj->field_0xec = puVar4;
      }
      else if (((int)local_68 < 0x50535441) && (local_68 == 0x5052494f)) {
        uVar13 = Get1__10CChunkFileFv(chunkFile);
        mapObj->field_0x15 = uVar13;
        mapObj->field_0x14 = uVar13;
      }
    }
    else if (local_68 == 0x5446524d) {
      dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
      mapObj->drawRange = (float)dVar16;
      dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
      *(float *)&mapObj->field_0x68 = (float)dVar16;
      dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
      *(float *)&mapObj->field_0x6c = (float)dVar16;
      dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
      *(float *)&mapObj->field_0x70 = (float)dVar16;
      dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
      *(float *)&mapObj->field_0x74 = (float)dVar16;
      dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
      *(float *)&mapObj->field_0x78 = (float)dVar16;
      dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
      *(float *)&mapObj->field_0x7c = (float)dVar16;
      dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
      *(float *)&mapObj->field_0x80 = (float)dVar16;
      dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
      *(float *)&mapObj->field_0x84 = (float)dVar16;
      if (((mapObj->field_0x1d == '\x02') || (mapObj->field_0x1d == '\x03')) &&
         ((FLOAT_8032f940 != *(float *)&mapObj->field_0x7c ||
          ((FLOAT_8032f940 != *(float *)&mapObj->field_0x80 ||
           (FLOAT_8032f940 != *(float *)&mapObj->field_0x84)))))) {
        if (*(int *)&mapObj->field_0xec == 0) {
          Printf__7CSystemFPce(&System,&DAT_801d70cc);
        }
        else {
          Printf__7CSystemFPce(&System,&DAT_801d7144,*(int *)&mapObj->field_0xec + 8);
        }
        fVar1 = FLOAT_8032f940;
        *(float *)&mapObj->field_0x7c = FLOAT_8032f940;
        *(float *)&mapObj->field_0x80 = fVar1;
        *(float *)&mapObj->field_0x84 = fVar1;
      }
      mapObj->field_0x1c = 1;
      mapObj->field_0x1b = 1;
    }
    else if ((int)local_68 < 0x5446524d) {
      if (local_68 == 0x534c4954) {
        if (*(int *)&mapObj->field_0xec != 0) {
          Printf__7CSystemFPce(&System,&DAT_801d718c,iVar3);
        }
        puVar4 = (undefined4 *)
                 __nw__FUlPQ27CMemory6CStagePci(0x110,MapMng._0_4_,s_mapobj_cpp_801d70c0,0x139);
        if (puVar4 != (undefined4 *)0x0) {
          *puVar4 = &PTR_PTR_s_CMapObjAtr_801e8950;
          fVar1 = FLOAT_8032f944;
          *puVar4 = &PTR_PTR_s_CMapObjAtrSpotLight_801e8914;
          puVar4[0x36] = 0;
          puVar4[0x37] = 0;
          puVar4[0x38] = 0;
          puVar4[0x39] = 0;
          *(undefined *)((int)puVar4 + 0xc3) = 1;
          *(undefined *)(puVar4 + 0x31) = 0;
          puVar4[0x40] = 0;
          puVar4[0x41] = 0;
          puVar4[0x42] = 0;
          puVar4[0x43] = 0;
          *(undefined *)((int)puVar4 + 0xeb) = 1;
          *(undefined *)(puVar4 + 0x3b) = 0;
          puVar4[1] = 1;
          puVar4[0xe] = 0;
          puVar4[9] = fVar1;
          puVar4[8] = fVar1;
          *(undefined *)(puVar4 + 0xb) = 0;
          *(undefined *)((int)puVar4 + 0x2d) = 0;
          *(undefined *)(puVar4 + 0xc) = 0;
        }
        if (local_60 == (uchar *)0x6) {
          PushChunk__10CChunkFileFv(chunkFile);
          while (iVar9 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                   (chunkFile,(CChunkFile *)&local_68), iVar9 != 0) {
            if (local_68 == 0x4c444154) {
              uVar13 = Get1__10CChunkFileFv(chunkFile);
              *(undefined *)(puVar4 + 0xd) = uVar13;
              uVar13 = Get1__10CChunkFileFv(chunkFile);
              *(undefined *)((int)puVar4 + 0x35) = uVar13;
              uVar13 = Get1__10CChunkFileFv(chunkFile);
              *(undefined *)((int)puVar4 + 0x36) = uVar13;
              uVar13 = Get1__10CChunkFileFv(chunkFile);
              *(undefined *)((int)puVar4 + 0x37) = uVar13;
              dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
              puVar4[5] = (float)dVar16;
              dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
              puVar4[6] = (float)dVar16;
              dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
              puVar4[7] = (float)dVar16;
              dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
              puVar4[8] = (float)dVar16;
              GetF4__10CChunkFileFv(chunkFile);
              dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
              puVar4[9] = (float)dVar16;
              uVar6 = Get2__10CChunkFileFv(chunkFile);
              puVar4[4] = (uVar6 & 0xffff) * 0xf0 + -0x7fdb9f48;
              uVar13 = Get1__10CChunkFileFv(chunkFile);
              *(undefined *)(puVar4 + 0xb) = uVar13;
              uVar13 = Get1__10CChunkFileFv(chunkFile);
              *(undefined *)((int)puVar4 + 0x2d) = uVar13;
              dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
              puVar4[10] = (float)dVar16;
              uVar13 = Get1__10CChunkFileFv(chunkFile);
              *(undefined *)((int)puVar4 + 0x2e) = uVar13;
              uVar13 = Get1__10CChunkFileFv(chunkFile);
              *(undefined *)((int)puVar4 + 0x2f) = uVar13;
              uVar13 = Get1__10CChunkFileFv(chunkFile);
              *(undefined *)(puVar4 + 0xc) = uVar13;
              Get1__10CChunkFileFv(chunkFile);
              Get4__10CChunkFileFv(chunkFile);
              Get4__10CChunkFileFv(chunkFile);
              Get4__10CChunkFileFv(chunkFile);
              Get4__10CChunkFileFv(chunkFile);
              uVar13 = Get1__10CChunkFileFv(chunkFile);
              *(undefined *)(puVar4 + 0xf) = uVar13;
              puVar15 = puVar4;
              for (iVar9 = 0; iVar9 < (int)(uint)*(byte *)(puVar4 + 0xf); iVar9 = iVar9 + 1) {
                uVar13 = Get1__10CChunkFileFv(chunkFile);
                *(undefined *)(puVar15 + 0x10) = uVar13;
                uVar13 = Get1__10CChunkFileFv(chunkFile);
                *(undefined *)((int)puVar15 + 0x41) = uVar13;
                uVar13 = Get1__10CChunkFileFv(chunkFile);
                *(undefined *)((int)puVar15 + 0x42) = uVar13;
                uVar13 = Get1__10CChunkFileFv(chunkFile);
                *(undefined *)((int)puVar15 + 0x43) = uVar13;
                puVar15 = puVar15 + 1;
              }
              uVar13 = Get1__10CChunkFileFv(chunkFile);
              *(undefined *)((int)puVar4 + 0x3d) = uVar13;
              puVar15 = puVar4;
              for (iVar9 = 0; iVar9 < (int)(uint)*(byte *)((int)puVar4 + 0x3d); iVar9 = iVar9 + 1) {
                uVar13 = Get1__10CChunkFileFv(chunkFile);
                *(undefined *)(puVar15 + 0x20) = uVar13;
                uVar13 = Get1__10CChunkFileFv(chunkFile);
                *(undefined *)((int)puVar15 + 0x81) = uVar13;
                uVar13 = Get1__10CChunkFileFv(chunkFile);
                *(undefined *)((int)puVar15 + 0x82) = uVar13;
                uVar13 = Get1__10CChunkFileFv(chunkFile);
                *(undefined *)((int)puVar15 + 0x83) = uVar13;
                puVar15 = puVar15 + 1;
              }
              *(undefined *)(puVar4 + 2) = *(undefined *)(puVar4 + 0x10);
              *(undefined *)((int)puVar4 + 9) = *(undefined *)((int)puVar4 + 0x41);
              *(undefined *)((int)puVar4 + 10) = *(undefined *)((int)puVar4 + 0x42);
              *(undefined *)((int)puVar4 + 0xb) = *(undefined *)((int)puVar4 + 0x43);
              *(undefined *)(puVar4 + 3) = *(undefined *)(puVar4 + 0x20);
              *(undefined *)((int)puVar4 + 0xd) = *(undefined *)((int)puVar4 + 0x81);
              *(undefined *)((int)puVar4 + 0xe) = *(undefined *)((int)puVar4 + 0x82);
              *(undefined *)((int)puVar4 + 0xf) = *(undefined *)((int)puVar4 + 0x83);
            }
            else {
              uVar13 = (undefined)local_64;
              if ((int)local_68 < 0x4c444154) {
                if (local_68 == 0x434a554e) {
                  ReadJun__12CMapKeyFrameFR10CChunkFilei
                            ((CMapKeyFrame *)(puVar4 + 0x3a),chunkFile,uVar13);
                }
                else if ((int)local_68 < 0x434a554e) {
                  if (local_68 == 0x4346524d) {
                    ReadFrame__12CMapKeyFrameFR10CChunkFilei
                              ((CMapKeyFrame *)(puVar4 + 0x3a),chunkFile);
                  }
                }
                else if (local_68 == 0x434b4559) {
                  ReadKey__12CMapKeyFrameFR10CChunkFilei
                            ((CMapKeyFrame *)(puVar4 + 0x3a),chunkFile,uVar13);
                }
              }
              else if (local_68 == 0x4d4a554e) {
                ReadJun__12CMapKeyFrameFR10CChunkFilei
                          ((CMapKeyFrame *)(puVar4 + 0x30),chunkFile,uVar13);
              }
              else if ((int)local_68 < 0x4d4a554e) {
                if (local_68 == 0x4d46524d) {
                  ReadFrame__12CMapKeyFrameFR10CChunkFilei
                            ((CMapKeyFrame *)(puVar4 + 0x30),chunkFile);
                }
              }
              else if (local_68 == 0x4d4b4559) {
                ReadKey__12CMapKeyFrameFR10CChunkFilei
                          ((CMapKeyFrame *)(puVar4 + 0x30),chunkFile,uVar13);
              }
            }
          }
          PopChunk__10CChunkFileFv(chunkFile);
        }
        else if (local_60 == (uchar *)0x5) {
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)(puVar4 + 2) = uVar13;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)((int)puVar4 + 9) = uVar13;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)((int)puVar4 + 10) = uVar13;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)((int)puVar4 + 0xb) = uVar13;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)(puVar4 + 3) = uVar13;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)((int)puVar4 + 0xd) = uVar13;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)((int)puVar4 + 0xe) = uVar13;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)((int)puVar4 + 0xf) = uVar13;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)(puVar4 + 0xd) = uVar13;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)((int)puVar4 + 0x35) = uVar13;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)((int)puVar4 + 0x36) = uVar13;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)((int)puVar4 + 0x37) = uVar13;
          dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
          puVar4[5] = (float)dVar16;
          dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
          puVar4[6] = (float)dVar16;
          dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
          puVar4[7] = (float)dVar16;
          dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
          puVar4[8] = (float)dVar16;
          GetF4__10CChunkFileFv(chunkFile);
          dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
          puVar4[9] = (float)dVar16;
          uVar6 = Get2__10CChunkFileFv(chunkFile);
          puVar4[4] = (uVar6 & 0xffff) * 0xf0 + -0x7fdb9f48;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)(puVar4 + 0xb) = uVar13;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)((int)puVar4 + 0x2d) = uVar13;
          dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
          puVar4[10] = (float)dVar16;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)((int)puVar4 + 0x2e) = uVar13;
        }
        else if (local_60 == (uchar *)0x4) {
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)(puVar4 + 2) = uVar13;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)((int)puVar4 + 9) = uVar13;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)((int)puVar4 + 10) = uVar13;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)((int)puVar4 + 0xb) = uVar13;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)(puVar4 + 3) = uVar13;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)((int)puVar4 + 0xd) = uVar13;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)((int)puVar4 + 0xe) = uVar13;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)((int)puVar4 + 0xf) = uVar13;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)(puVar4 + 0xd) = uVar13;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)((int)puVar4 + 0x35) = uVar13;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)((int)puVar4 + 0x36) = uVar13;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)((int)puVar4 + 0x37) = uVar13;
          dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
          puVar4[5] = (float)dVar16;
          dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
          puVar4[6] = (float)dVar16;
          dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
          puVar4[7] = (float)dVar16;
          dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
          puVar4[8] = (float)dVar16;
          GetF4__10CChunkFileFv(chunkFile);
          dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
          puVar4[9] = (float)dVar16;
          uVar6 = Get2__10CChunkFileFv(chunkFile);
          puVar4[4] = (uVar6 & 0xffff) * 0xf0 + -0x7fdb9f48;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)(puVar4 + 0xb) = uVar13;
          uVar13 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)((int)puVar4 + 0x2d) = uVar13;
          puVar4[10] = FLOAT_8032f954;
          *(undefined *)((int)puVar4 + 0x2e) = 0;
        }
        *(undefined4 **)&mapObj->field_0xec = puVar4;
      }
      else if ((((int)local_68 < 0x534c4954) && (local_68 == 0x53484b49)) &&
              ((short)MapMng._16_2_ < 4)) {
        iVar9 = (short)MapMng._16_2_ * 0x18;
        MapMng._16_2_ = MapMng._16_2_ + 1;
        uVar5 = Get4__10CChunkFileFv(chunkFile);
        *(undefined4 *)((int)(MapMng.mapLightHolderArr + 2) + iVar9) = uVar5;
        dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
        local_58 = (longlong)(int)dVar16;
        *(short *)((int)(MapMng.mapLightHolderArr + 2) + iVar9 + 4) = (short)(int)dVar16;
        uVar13 = Get1__10CChunkFileFv(chunkFile);
        *(undefined *)((int)(MapMng.mapLightHolderArr + 2) + iVar9 + 6) = uVar13;
        uVar13 = Get1__10CChunkFileFv(chunkFile);
        *(undefined *)((int)(MapMng.mapLightHolderArr + 2) + iVar9 + 7) = uVar13;
        uVar13 = Get1__10CChunkFileFv(chunkFile);
        *(undefined *)((int)(MapMng.mapLightHolderArr + 2) + iVar9 + 0x10) = uVar13;
        uVar13 = Get1__10CChunkFileFv(chunkFile);
        *(undefined *)((int)(MapMng.mapLightHolderArr + 2) + iVar9 + 0x11) = uVar13;
        uVar13 = Get1__10CChunkFileFv(chunkFile);
        *(undefined *)((int)(MapMng.mapLightHolderArr + 2) + iVar9 + 0x12) = uVar13;
        uVar13 = Get1__10CChunkFileFv(chunkFile);
        *(undefined *)((int)(MapMng.mapLightHolderArr + 2) + iVar9 + 0x13) = uVar13;
        uVar13 = Get1__10CChunkFileFv(chunkFile);
        *(undefined *)((int)(MapMng.mapLightHolderArr + 2) + iVar9 + 0x14) = uVar13;
        uVar13 = Get1__10CChunkFileFv(chunkFile);
        *(undefined *)((int)MapMng.mapIdGrpArr + iVar9 + -0x4b) = uVar13;
        uVar13 = Get1__10CChunkFileFv(chunkFile);
        *(undefined *)((int)MapMng.mapIdGrpArr + iVar9 + -0x4a) = uVar13;
        uVar13 = Get1__10CChunkFileFv(chunkFile);
        *(undefined *)((int)MapMng.mapIdGrpArr + iVar9 + -0x49) = uVar13;
      }
    }
    else if (local_68 == 0x54524e53) {
      dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
      (mapObj->m_translationRate).x = (float)dVar16;
      dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
      (mapObj->m_translationRate).y = (float)dVar16;
      dVar16 = (double)GetF4__10CChunkFileFv(chunkFile);
      (mapObj->m_translationRate).z = (float)dVar16;
    }
  }
  PopChunk__10CChunkFileFv(chunkFile);
  return 1;
}

