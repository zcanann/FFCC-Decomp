// Function: Create__12CMaterialSetFR10CChunkFileP11CTextureSetQ212CMaterialMan7TEV_BITPQ29CLightPcs10CBumpLight
// Entry: 8003cdbc
// Size: 2748 bytes

void Create__12CMaterialSetFR10CChunkFileP11CTextureSetQ212CMaterialMan7TEV_BITPQ29CLightPcs10CBumpLight
               (CMaterialSet *materialSet,CChunkFile *chunkFile,CTextureSet *textureSet,int param_4,
               void *param_5)

{
  ushort uVar1;
  float fVar2;
  uint uVar3;
  undefined uVar8;
  char cVar9;
  undefined2 uVar6;
  short sVar7;
  undefined4 uVar4;
  int iVar5;
  CRef *pCVar10;
  CMapKeyFrame *mapKeyFrame;
  CMapKeyFrame *mapKeyFrame_00;
  CRef *ref;
  uint unaff_r28;
  double dVar11;
  undefined local_68;
  undefined uStack_67;
  undefined uStack_66;
  undefined uStack_65;
  undefined local_64;
  undefined uStack_63;
  undefined uStack_62;
  undefined uStack_61;
  undefined local_60;
  undefined uStack_5f;
  undefined uStack_5e;
  undefined uStack_5d;
  uint32_t local_5c;
  int32_t local_58;
  int local_54;
  
  ref = (CRef *)0x0;
  PushChunk__10CChunkFileFv(chunkFile);
  do {
    do {
      iVar5 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk(chunkFile,(CChunkFile *)&local_5c);
      if (iVar5 == 0) {
        PopChunk__10CChunkFileFv(chunkFile);
        SetTextureSet__12CMaterialSetFP11CTextureSet(materialSet,textureSet);
        return;
      }
    } while (local_5c != 0x4d41544c);
    PushChunk__10CChunkFileFv(chunkFile);
    while (iVar5 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                             (chunkFile,(CChunkFile *)&local_5c), iVar5 != 0) {
      if (local_5c == 0x4e414d45) {
        ref = (CRef *)__vc__22CPtrArray<P9CMaterial>FUl(&materialSet->materials,unaff_r28);
        uVar4 = GetString__10CChunkFileFv(chunkFile);
        strncpy(ref + 1,uVar4,0x10);
      }
      else if ((int)local_5c < 0x4e414d45) {
        if (local_5c == 0x46555220) {
          ref = (CRef *)__vc__22CPtrArray<P9CMaterial>FUl(&materialSet->materials,unaff_r28);
          uVar1 = *(ushort *)&ref[3].vtable;
          *(ushort *)&ref[3].vtable = uVar1 + 1;
          uVar6 = Get2__10CChunkFileFv(chunkFile);
          *(undefined2 *)((int)&ref[3].vtable + (uint)uVar1 * 2 + 2) = uVar6;
          *(undefined *)((int)&ref[0x14].refCount + 3) = 1;
        }
        else if ((int)local_5c < 0x46555220) {
          if (local_5c == 0x42554d50) {
            if (local_54 == 1) {
              cVar9 = Get1__10CChunkFileFv(chunkFile);
              uVar8 = Get1__10CChunkFileFv(chunkFile);
              *(undefined *)((int)&ref[0x14].refCount + 1) = uVar8;
              Get2__10CChunkFileFv(chunkFile);
            }
            else {
              cVar9 = '\0';
            }
            ref = (CRef *)__vc__22CPtrArray<P9CMaterial>FUl(&materialSet->materials,unaff_r28);
            uVar1 = *(ushort *)&ref[3].vtable;
            *(ushort *)&ref[3].vtable = uVar1 + 1;
            uVar6 = Get2__10CChunkFileFv(chunkFile);
            *(undefined2 *)((int)&ref[3].vtable + (uint)uVar1 * 2 + 2) = uVar6;
            uVar1 = *(ushort *)&ref[3].vtable;
            *(ushort *)&ref[3].vtable = uVar1 + 1;
            uVar6 = Get2__10CChunkFileFv(chunkFile);
            *(undefined2 *)((int)&ref[3].vtable + (uint)uVar1 * 2 + 2) = uVar6;
            sVar7 = Get2__10CChunkFileFv(chunkFile);
            uVar1 = *(ushort *)&ref[3].vtable;
            *(ushort *)&ref[3].vtable = uVar1 + 1;
            uVar6 = Get2__10CChunkFileFv(chunkFile);
            *(undefined2 *)((int)&ref[3].vtable + (uint)uVar1 * 2 + 2) = uVar6;
            dVar11 = (double)GetF4__10CChunkFileFv(chunkFile);
            ref[5].refCount = (int)(float)((double)FLOAT_8032faf0 / dVar11);
            dVar11 = (double)GetF4__10CChunkFileFv(chunkFile);
            ref[6].vtable = (void *)(float)((double)FLOAT_8032faf0 / dVar11);
            uVar8 = Get4__10CChunkFileFv(chunkFile);
            *(undefined *)((int)&ref[6].refCount + 2) = uVar8;
            uVar4 = Get4__10CChunkFileFv(chunkFile);
            local_60 = (undefined)((uint)uVar4 >> 0x18);
            uStack_5f = (undefined)((uint)uVar4 >> 0x10);
            *(undefined *)&ref[7].vtable = local_60;
            uStack_5e = (undefined)((uint)uVar4 >> 8);
            *(undefined *)((int)&ref[7].vtable + 1) = uStack_5f;
            uStack_5d = (undefined)uVar4;
            *(undefined *)((int)&ref[7].vtable + 2) = uStack_5e;
            *(undefined *)((int)&ref[7].vtable + 3) = uStack_5d;
            *(undefined *)((int)&ref[0x14].vtable + 2) = 1;
            if (param_5 == (void *)0x0) {
              ref[5].vtable = (void *)(sVar7 * 0x138 + -0x7fd94a7c);
              if (cVar9 == '\0') {
                *(undefined *)((int)&ref[0x14].vtable + 3) = 0;
              }
              else {
                *(undefined *)((int)&ref[0x14].vtable + 3) = 1;
              }
            }
            else {
              ref[5].vtable = param_5;
              *(undefined *)((int)&ref[0x14].vtable + 3) = 1;
            }
            *(undefined *)((int)ref[5].vtable + 0xb1) = *(undefined *)((int)&ref[0x14].vtable + 2);
            ref[4].refCount = ref[4].refCount | 4;
          }
          else if (((int)local_5c < 0x42554d50) && (local_5c == 0x41545242)) {
            ref = (CRef *)__vc__22CPtrArray<P9CMaterial>FUl(&materialSet->materials,unaff_r28);
            uVar3 = Get4__10CChunkFileFv(chunkFile);
            if ((uVar3 & 1) != 0) {
              ref[4].refCount = ref[4].refCount | 0x80;
            }
            if ((uVar3 & 2) != 0) {
              ref[4].refCount = ref[4].refCount | 0x10;
            }
            if ((uVar3 & 4) != 0) {
              ref[4].refCount = ref[4].refCount | 4;
            }
            if ((uVar3 & 8) != 0) {
              ref[4].refCount = ref[4].refCount | 0x100000;
            }
            uVar8 = Get1__10CChunkFileFv(chunkFile);
            *(undefined *)&ref[0x14].vtable = uVar8;
            uVar8 = Get1__10CChunkFileFv(chunkFile);
            *(undefined *)((int)&ref[0x14].vtable + 1) = uVar8;
            Get1__10CChunkFileFv(chunkFile);
            Get1__10CChunkFileFv(chunkFile);
            uVar8 = Get2__10CChunkFileFv(chunkFile);
            *(undefined *)((int)&ref[0x14].refCount + 2) = uVar8;
            Get2__10CChunkFileFv(chunkFile);
            GetF4__10CChunkFileFv(chunkFile);
          }
        }
        else if (local_5c == 0x4a494d45) {
          ref = (CRef *)__vc__22CPtrArray<P9CMaterial>FUl(&materialSet->materials,unaff_r28);
          uVar1 = *(ushort *)&ref[3].vtable;
          *(ushort *)&ref[3].vtable = uVar1 + 1;
          uVar6 = Get2__10CChunkFileFv(chunkFile);
          *(undefined2 *)((int)&ref[3].vtable + (uint)uVar1 * 2 + 2) = uVar6;
          uVar1 = *(ushort *)&ref[3].vtable;
          *(ushort *)&ref[3].vtable = uVar1 + 1;
          uVar6 = Get2__10CChunkFileFv(chunkFile);
          *(undefined2 *)((int)&ref[3].vtable + (uint)uVar1 * 2 + 2) = uVar6;
          sVar7 = Get2__10CChunkFileFv(chunkFile);
          uVar8 = Get1__10CChunkFileFv(chunkFile);
          *(undefined *)((int)&ref[0x14].refCount + 1) = uVar8;
          cVar9 = Get1__10CChunkFileFv(chunkFile);
          if (cVar9 != '\0') {
            ref[4].refCount = ref[4].refCount | 0x20000;
          }
          dVar11 = (double)GetF4__10CChunkFileFv(chunkFile);
          ref[5].refCount = (int)(float)((double)FLOAT_8032faf0 / dVar11);
          dVar11 = (double)GetF4__10CChunkFileFv(chunkFile);
          ref[6].vtable = (void *)(float)((double)FLOAT_8032faf0 / dVar11);
          *(undefined *)((int)&ref[0x14].vtable + 2) = 3;
          ref[5].vtable = (void *)(sVar7 * 0x138 + -0x7fd94a7c);
          *(undefined *)((int)ref[5].vtable + 0xb1) = *(undefined *)((int)&ref[0x14].vtable + 2);
          ref[4].refCount = ref[4].refCount | 0x4000;
          Get4__10CChunkFileFv(chunkFile);
          uVar4 = Get4__10CChunkFileFv(chunkFile);
          local_68 = (undefined)((uint)uVar4 >> 0x18);
          uStack_67 = (undefined)((uint)uVar4 >> 0x10);
          *(undefined *)&ref[7].vtable = local_68;
          uStack_66 = (undefined)((uint)uVar4 >> 8);
          *(undefined *)((int)&ref[7].vtable + 1) = uStack_67;
          uStack_65 = (undefined)uVar4;
          *(undefined *)((int)&ref[7].vtable + 2) = uStack_66;
          *(undefined *)((int)&ref[7].vtable + 3) = uStack_65;
          *(undefined *)((int)&ref[0x14].vtable + 3) = 1;
        }
      }
      else if (local_5c == 0x5453434c) {
        if (local_54 == 1) {
          mapKeyFrame_00 = (CMapKeyFrame *)0x0;
          mapKeyFrame = (CMapKeyFrame *)0x0;
          PushChunk__10CChunkFileFv(chunkFile);
          while (iVar5 = GetNextChunk__10CChunkFileFRQ210CChunkFile6CChunk
                                   (chunkFile,(CChunkFile *)&local_5c), iVar5 != 0) {
            if (local_5c == 0x554b4559) {
              ReadKey__12CMapKeyFrameFR10CChunkFilei(mapKeyFrame_00,chunkFile,(char)local_58);
            }
            else if ((int)local_5c < 0x554b4559) {
              if (local_5c == 0x5546524d) {
                mapKeyFrame_00 =
                     (CMapKeyFrame *)
                     __nw__FUlPQ27CMemory6CStagePci
                               (0x28,MaterialMan._536_4_,s_materialman_cpp_801d7a38,0xdd3);
                if (mapKeyFrame_00 != (CMapKeyFrame *)0x0) {
                  *(undefined4 *)&mapKeyFrame_00->field_0x18 = 0;
                  mapKeyFrame_00->field16_0x1c = 0;
                  mapKeyFrame_00->field17_0x20 = 0;
                  *(undefined4 *)(mapKeyFrame_00 + 1) = 0;
                  mapKeyFrame_00->field_0x3 = 1;
                  *(undefined *)&mapKeyFrame_00->isRun = 0;
                }
                ReadFrame__12CMapKeyFrameFR10CChunkFilei(mapKeyFrame_00,chunkFile);
              }
              else if (((int)local_5c < 0x5546524d) && (local_5c == 0x54534454)) {
                uVar3 = Get2__10CChunkFileFv(chunkFile);
                uVar3 = uVar3 & 0xffff;
                Get2__10CChunkFileFv(chunkFile);
                if (mapKeyFrame_00 == (CMapKeyFrame *)0x0) {
                  dVar11 = (double)GetF4__10CChunkFileFv(chunkFile);
                  fVar2 = FLOAT_8032faf4;
                  *(float *)((int)ref + uVar3 * 0x14 + 0x58) = (float)dVar11;
                  if (fVar2 == *(float *)((int)ref + uVar3 * 0x14 + 0x58)) {
                    *(undefined *)((int)ref + uVar3 * 0x14 + 0x4c) = 0;
                  }
                  else {
                    *(undefined *)((int)ref + uVar3 * 0x14 + 0x4c) = 1;
                  }
                }
                else {
                  GetF4__10CChunkFileFv(chunkFile);
                  *(CMapKeyFrame **)((int)ref + uVar3 * 0x14 + 0x58) = mapKeyFrame_00;
                  *(undefined *)((int)ref + uVar3 * 0x14 + 0x4c) = 2;
                }
                if (mapKeyFrame == (CMapKeyFrame *)0x0) {
                  dVar11 = (double)GetF4__10CChunkFileFv(chunkFile);
                  fVar2 = FLOAT_8032faf4;
                  *(float *)((int)ref + uVar3 * 0x14 + 0x5c) = (float)dVar11;
                  if (fVar2 == *(float *)((int)ref + uVar3 * 0x14 + 0x5c)) {
                    *(undefined *)((int)ref + uVar3 * 0x14 + 0x4d) = 0;
                  }
                  else {
                    *(undefined *)((int)ref + uVar3 * 0x14 + 0x4d) = 1;
                  }
                }
                else {
                  GetF4__10CChunkFileFv(chunkFile);
                  *(CMapKeyFrame **)((int)ref + uVar3 * 0x14 + 0x5c) = mapKeyFrame;
                  *(undefined *)((int)ref + uVar3 * 0x14 + 0x4d) = 2;
                }
              }
            }
            else if (local_5c == 0x564b4559) {
              ReadKey__12CMapKeyFrameFR10CChunkFilei(mapKeyFrame,chunkFile,(char)local_58);
            }
            else if (((int)local_5c < 0x564b4559) && (local_5c == 0x5646524d)) {
              mapKeyFrame = (CMapKeyFrame *)
                            __nw__FUlPQ27CMemory6CStagePci
                                      (0x28,MaterialMan._536_4_,s_materialman_cpp_801d7a38,0xddd);
              if (mapKeyFrame != (CMapKeyFrame *)0x0) {
                *(undefined4 *)&mapKeyFrame->field_0x18 = 0;
                mapKeyFrame->field16_0x1c = 0;
                mapKeyFrame->field17_0x20 = 0;
                *(undefined4 *)(mapKeyFrame + 1) = 0;
                mapKeyFrame->field_0x3 = 1;
                *(undefined *)&mapKeyFrame->isRun = 0;
              }
              ReadFrame__12CMapKeyFrameFR10CChunkFilei(mapKeyFrame,chunkFile);
            }
          }
          PopChunk__10CChunkFileFv(chunkFile);
        }
        else {
          uVar3 = Get2__10CChunkFileFv(chunkFile);
          uVar3 = uVar3 & 0xffff;
          Get2__10CChunkFileFv(chunkFile);
          dVar11 = (double)GetF4__10CChunkFileFv(chunkFile);
          *(float *)((int)ref + uVar3 * 0x14 + 0x58) = (float)dVar11;
          dVar11 = (double)GetF4__10CChunkFileFv(chunkFile);
          *(float *)((int)ref + uVar3 * 0x14 + 0x5c) = (float)dVar11;
          if (FLOAT_8032faf4 != *(float *)((int)ref + uVar3 * 0x14 + 0x58)) {
            *(undefined *)((int)ref + uVar3 * 0x14 + 0x4c) = 1;
          }
          if (FLOAT_8032faf4 != *(float *)((int)ref + uVar3 * 0x14 + 0x5c)) {
            *(undefined *)((int)ref + uVar3 * 0x14 + 0x4d) = 1;
          }
        }
      }
      else if ((int)local_5c < 0x5453434c) {
        if (local_5c == 0x54494458) {
          for (unaff_r28 = 0; uVar3 = _UnkMaterialSetGetter((CMaterial *)&materialSet->materials),
              unaff_r28 < uVar3; unaff_r28 = unaff_r28 + 1) {
            iVar5 = __vc__22CPtrArray<P9CMaterial>FUl(&materialSet->materials,unaff_r28);
            if (iVar5 == 0) goto LAB_8003cf0c;
          }
          unaff_r28 = _UnkMaterialSetGetter((CMaterial *)&materialSet->materials);
LAB_8003cf0c:
          ref = (CRef *)_Alloc__7CMemoryFUlPQ27CMemory6CStagePcii
                                  (&Memory,0xa8,MaterialMan._536_4_,s_materialman_cpp_801d7a38,0xcff
                                   ,0);
          if (ref != (CRef *)0x0) {
            __ct__4CRefFv(ref);
            ref->vtable = &PTR_PTR_s_CMaterial_801e9bd4;
            __construct_array(&ref[9].refCount,__ct__10CTexScrollFv,__dt__10CTexScrollFv,0x14,4);
            memset(ref + 1,0,0x10);
            ref[0x13].refCount = -1;
            *(undefined *)&ref[0x14].vtable = 4;
            *(undefined *)((int)&ref[0x14].vtable + 1) = 1;
            *(undefined *)((int)&ref[0x14].vtable + 2) = 0;
            *(undefined *)&ref[0x14].refCount = 0;
            ref[7].refCount = 0;
            ref[8].vtable = (void *)0x0;
            ref[8].refCount = 0;
            ref[9].vtable = (void *)0x0;
            *(undefined *)&ref[6].refCount = 0;
            *(undefined *)((int)&ref[6].refCount + 1) = 0;
            *(undefined *)((int)&ref[6].refCount + 2) = 0;
            *(undefined *)((int)&ref[0x14].refCount + 1) = 0;
          }
          fVar2 = FLOAT_8032faf0;
          ref[4].refCount = param_4;
          ref[5].vtable = (void *)0x0;
          *(undefined2 *)&ref[3].vtable = 0;
          ref[6].vtable = (void *)fVar2;
          ref[5].refCount = (int)fVar2;
          *(undefined *)((int)&ref[0x14].refCount + 3) = 0;
          *(short *)&ref[3].vtable = (short)local_58;
          if (*(short *)&ref[3].vtable == 0) {
            ref[4].refCount = ref[4].refCount | 1;
          }
          else {
            pCVar10 = ref;
            for (iVar5 = 0; iVar5 < (int)(uint)*(ushort *)&ref[3].vtable; iVar5 = iVar5 + 1) {
              uVar6 = Get4__10CChunkFileFv(chunkFile);
              *(undefined2 *)((int)&pCVar10[3].vtable + 2) = uVar6;
              pCVar10 = (CRef *)((int)&pCVar10->vtable + 2);
            }
            if (*(ushort *)&ref[3].vtable == 2) {
              ref[4].refCount = ref[4].refCount | 2;
            }
          }
          uVar3 = _UnkMaterialSetGetter((CMaterial *)&materialSet->materials);
          if (unaff_r28 < uVar3) {
            SetAt__22CPtrArray<P9CMaterial>FUlP9CMaterial(&materialSet->materials,unaff_r28,ref);
          }
          else {
            Add__22CPtrArray<P9CMaterial>FP9CMaterial(&materialSet->materials,ref);
          }
        }
      }
      else if (local_5c == 0x57415452) {
        ref = (CRef *)__vc__22CPtrArray<P9CMaterial>FUl(&materialSet->materials,unaff_r28);
        uVar1 = *(ushort *)&ref[3].vtable;
        *(ushort *)&ref[3].vtable = uVar1 + 1;
        uVar6 = Get2__10CChunkFileFv(chunkFile);
        *(undefined2 *)((int)&ref[3].vtable + (uint)uVar1 * 2 + 2) = uVar6;
        uVar1 = *(ushort *)&ref[3].vtable;
        *(ushort *)&ref[3].vtable = uVar1 + 1;
        uVar6 = Get2__10CChunkFileFv(chunkFile);
        *(undefined2 *)((int)&ref[3].vtable + (uint)uVar1 * 2 + 2) = uVar6;
        sVar7 = Get2__10CChunkFileFv(chunkFile);
        cVar9 = Get1__10CChunkFileFv(chunkFile);
        uVar8 = Get1__10CChunkFileFv(chunkFile);
        *(undefined *)((int)&ref[0x14].refCount + 1) = uVar8;
        dVar11 = (double)GetF4__10CChunkFileFv(chunkFile);
        ref[5].refCount = (int)(float)((double)FLOAT_8032faf0 / dVar11);
        dVar11 = (double)GetF4__10CChunkFileFv(chunkFile);
        ref[6].vtable = (void *)(float)((double)FLOAT_8032faf0 / dVar11);
        *(undefined *)((int)&ref[0x14].vtable + 2) = 2;
        ref[5].vtable = (void *)(sVar7 * 0x138 + -0x7fd94a7c);
        *(undefined *)((int)ref[5].vtable + 0xb1) = *(undefined *)((int)&ref[0x14].vtable + 2);
        *(undefined *)&ref[0x14].vtable = 4;
        Get4__10CChunkFileFv(chunkFile);
        uVar4 = Get4__10CChunkFileFv(chunkFile);
        local_64 = (undefined)((uint)uVar4 >> 0x18);
        uStack_63 = (undefined)((uint)uVar4 >> 0x10);
        *(undefined *)&ref[7].vtable = local_64;
        uStack_62 = (undefined)((uint)uVar4 >> 8);
        *(undefined *)((int)&ref[7].vtable + 1) = uStack_63;
        uStack_61 = (undefined)uVar4;
        *(undefined *)((int)&ref[7].vtable + 2) = uStack_62;
        *(undefined *)((int)&ref[7].vtable + 3) = uStack_61;
        if ((cVar9 == '\0') && (*(char *)((int)&ref[0x14].refCount + 1) == '\0')) {
          ref[4].refCount = ref[4].refCount | 8;
        }
        else {
          ref[4].refCount = ref[4].refCount | 0x80000;
        }
      }
    }
    PopChunk__10CChunkFileFv(chunkFile);
  } while( true );
}

