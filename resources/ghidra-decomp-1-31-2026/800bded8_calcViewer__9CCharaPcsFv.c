// Function: calcViewer__9CCharaPcsFv
// Entry: 800bded8
// Size: 3960 bytes

/* WARNING: Removing unreachable block (ram,0x800bee34) */
/* WARNING: Removing unreachable block (ram,0x800bee2c) */
/* WARNING: Removing unreachable block (ram,0x800bee24) */
/* WARNING: Removing unreachable block (ram,0x800bdef8) */
/* WARNING: Removing unreachable block (ram,0x800bdef0) */
/* WARNING: Removing unreachable block (ram,0x800bdee8) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void calcViewer__9CCharaPcsFv(int param_1)

{
  float fVar1;
  float fVar2;
  bool bVar3;
  ushort uVar5;
  uint uVar4;
  int *piVar6;
  CFileCHandle *pCVar7;
  CModel *model;
  undefined4 uVar8;
  ushort uVar9;
  CTexAnimSet *texAnimSet;
  int iVar10;
  int iVar11;
  undefined *puVar12;
  undefined *puVar13;
  uint uVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  double dVar18;
  undefined auStack_1b8 [48];
  undefined auStack_188 [48];
  undefined auStack_158 [256];
  COrder *local_58;
  CProcess *pCStack_54;
  
  if (*(int *)(param_1 + 0x6fc) != 0) {
    piVar6 = *(int **)(param_1 + 0x1a0);
    if (piVar6 != (int *)0x0) {
      iVar10 = piVar6[1];
      piVar6[1] = iVar10 + -1;
      if ((iVar10 + -1 == 0) && (piVar6 != (int *)0x0)) {
        (**(code **)(*piVar6 + 8))(piVar6,1);
      }
      *(undefined4 *)(param_1 + 0x1a0) = 0;
    }
    *(undefined4 *)(param_1 + 0x1a0) = *(undefined4 *)(param_1 + 0x198);
    iVar10 = *(int *)(param_1 + 0x1a0);
    if (iVar10 != 0) {
      *(int *)(iVar10 + 4) = *(int *)(iVar10 + 4) + 1;
    }
    *(undefined4 *)(param_1 + 0x6fc) = 0;
  }
  if ((((*(int *)(param_1 + 700) != 0) || (*(int *)(param_1 + 0x3c0) != 0)) ||
      (*(int *)(param_1 + 0x4c4) != 0)) || (*(int *)(param_1 + 0x710) != 0)) {
    if (*(int *)(param_1 + 700) != 0) {
      Printf__7CSystemFPce(&System,s_CCharaPcs_calcViewer___s_801da830,param_1 + 0x2c0);
      pCVar7 = (CFileCHandle *)Open__5CFileFPcUlQ25CFile3PRI(&File,param_1 + 0x2c0,0,0);
      if (pCVar7 != (CFileCHandle *)0x0) {
        piVar6 = *(int **)(param_1 + 0x194);
        if (piVar6 != (int *)0x0) {
          iVar10 = piVar6[1];
          piVar6[1] = iVar10 + -1;
          if ((iVar10 + -1 == 0) && (piVar6 != (int *)0x0)) {
            (**(code **)(*piVar6 + 8))(piVar6,1);
          }
          *(undefined4 *)(param_1 + 0x194) = 0;
        }
        piVar6 = *(int **)(param_1 + 0x19c);
        if (piVar6 != (int *)0x0) {
          iVar10 = piVar6[1];
          piVar6[1] = iVar10 + -1;
          if ((iVar10 + -1 == 0) && (piVar6 != (int *)0x0)) {
            (**(code **)(*piVar6 + 8))(piVar6,1);
          }
          *(undefined4 *)(param_1 + 0x19c) = 0;
        }
        piVar6 = *(int **)(param_1 + 0x2b4);
        if (piVar6 != (int *)0x0) {
          iVar10 = piVar6[1];
          piVar6[1] = iVar10 + -1;
          if ((iVar10 + -1 == 0) && (piVar6 != (int *)0x0)) {
            (**(code **)(*piVar6 + 8))(piVar6,1);
          }
          *(undefined4 *)(param_1 + 0x2b4) = 0;
        }
        *(undefined4 *)(param_1 + 0x194) = *(undefined4 *)(param_1 + 400);
        *(undefined4 *)(param_1 + 0x19c) = *(undefined4 *)(param_1 + 0x198);
        *(undefined4 *)(param_1 + 0x2b4) = *(undefined4 *)(param_1 + 0x2b0);
        *(undefined4 *)(param_1 + 400) = 0;
        *(undefined4 *)(param_1 + 0x198) = 0;
        *(undefined4 *)(param_1 + 0x2b0) = 0;
        Read__5CFileFPQ25CFile7CHandle(&File,pCVar7);
        SyncCompleted__5CFileFPQ25CFile7CHandle(&File,pCVar7);
        model = (CModel *)
                __nw__FUlPQ27CMemory6CStagePci
                          (0x124,CharaPcs._192_4_,s_p_chara_viewer_cpp_801da7f8,0xea);
        if (model != (CModel *)0x0) {
          model = (CModel *)__ct__Q26CChara6CModelFv(model);
        }
        *(CModel **)(param_1 + 400) = model;
        Create__Q26CChara6CModelFPvPQ27CMemory6CStage
                  (*(CModel **)(param_1 + 400),File.m_readBuffer,*(CStage **)(param_1 + 0xcc));
        *(byte *)(*(int *)(param_1 + 400) + 0x10c) =
             *(byte *)(*(int *)(param_1 + 400) + 0x10c) & 0xbf | 0x40;
        Close__5CFileFPQ25CFile7CHandle(&File,pCVar7);
      }
      *(undefined4 *)(param_1 + 700) = 0;
    }
    if ((*(int *)(param_1 + 0x5f0) != 0) && (*(int *)(param_1 + 400) != 0)) {
      Printf__7CSystemFPce(&System,s_CCharaPcs_calcViewer___s_801da830,param_1 + 0x5f4);
      pCVar7 = (CFileCHandle *)Open__5CFileFPcUlQ25CFile3PRI(&File,param_1 + 0x5f4,0,0);
      if (pCVar7 != (CFileCHandle *)0x0) {
        Read__5CFileFPQ25CFile7CHandle(&File,pCVar7);
        SyncCompleted__5CFileFPQ25CFile7CHandle(&File,pCVar7);
        CreateDynamics__Q26CChara6CModelFPvPQ27CMemory6CStage
                  (*(CModel **)(param_1 + 400),File.m_readBuffer,*(undefined4 *)(param_1 + 0xcc));
        Close__5CFileFPQ25CFile7CHandle(&File,pCVar7);
      }
      *(undefined4 *)(param_1 + 0x5f0) = 0;
    }
    if ((*(int *)(param_1 + 0x3c0) != 0) || (*(int *)(param_1 + 0x710) != 0)) {
      piVar6 = *(int **)(param_1 + 0x198);
      if (piVar6 != (int *)0x0) {
        iVar10 = piVar6[1];
        piVar6[1] = iVar10 + -1;
        if ((iVar10 + -1 == 0) && (piVar6 != (int *)0x0)) {
          (**(code **)(*piVar6 + 8))(piVar6,1);
        }
        *(undefined4 *)(param_1 + 0x198) = 0;
      }
      uVar14 = 0;
      iVar10 = param_1;
      do {
        piVar6 = *(int **)(iVar10 + 0x1b0);
        if (piVar6 != (int *)0x0) {
          iVar11 = piVar6[1];
          piVar6[1] = iVar11 + -1;
          if ((iVar11 + -1 == 0) && (piVar6 != (int *)0x0)) {
            (**(code **)(*piVar6 + 8))(piVar6,1);
          }
          *(undefined4 *)(iVar10 + 0x1b0) = 0;
        }
        uVar14 = uVar14 + 1;
        iVar10 = iVar10 + 4;
      } while (uVar14 < 0x40);
      *(undefined4 *)(param_1 + 0x1ac) = 0;
      *(undefined4 *)(param_1 + 0x1a4) = 0;
      if (*(int *)(param_1 + 0x3c0) == 0) {
        for (iVar10 = 0; iVar10 < *(int *)(param_1 + 0x1a8); iVar10 = iVar10 + 1) {
          sprintf(auStack_158,s__splot_d_cha_801da84c,param_1 + 0x3c4,
                  *(undefined4 *)(param_1 + 0x1a4));
          Printf__7CSystemFPce(&System,s_CCharaPcs_calcViewer___s_801da830,auStack_158);
          pCVar7 = (CFileCHandle *)Open__5CFileFPcUlQ25CFile3PRI(&File,auStack_158,0,0);
          if (pCVar7 != (CFileCHandle *)0x0) {
            piVar6 = *(int **)(param_1 + *(int *)(param_1 + 0x1a4) * 4 + 0x1b0);
            if (piVar6 != (int *)0x0) {
              iVar11 = piVar6[1];
              piVar6[1] = iVar11 + -1;
              if ((iVar11 + -1 == 0) && (piVar6 != (int *)0x0)) {
                (**(code **)(*piVar6 + 8))(piVar6,1);
              }
              *(undefined4 *)(param_1 + *(int *)(param_1 + 0x1a4) * 4 + 0x1b0) = 0;
            }
            Read__5CFileFPQ25CFile7CHandle(&File,pCVar7);
            SyncCompleted__5CFileFPQ25CFile7CHandle(&File,pCVar7);
            iVar11 = __nw__FUlPQ27CMemory6CStagePci
                               (0x30,CharaPcs._192_4_,s_p_chara_viewer_cpp_801da7f8,0x124);
            if (iVar11 != 0) {
              iVar11 = __ct__Q26CChara5CAnimFv();
            }
            *(int *)(param_1 + *(int *)(param_1 + 0x1a4) * 4 + 0x1b0) = iVar11;
            Create__Q26CChara5CAnimFPvPQ27CMemory6CStage
                      (*(undefined4 *)(param_1 + *(int *)(param_1 + 0x1a4) * 4 + 0x1b0),
                       File.m_readBuffer,*(CStage **)(param_1 + 0xd4));
            Close__5CFileFPQ25CFile7CHandle(&File,pCVar7);
            if (*(int *)(param_1 + 0x1a4) == 0) {
              *(undefined4 *)(param_1 + 0x198) = *(undefined4 *)(param_1 + 0x1b0);
              *(int *)(*(int *)(param_1 + 0x198) + 4) = *(int *)(*(int *)(param_1 + 0x198) + 4) + 1;
            }
            *(int *)(param_1 + 0x1a4) = *(int *)(param_1 + 0x1a4) + 1;
          }
        }
        *(undefined4 *)(param_1 + 0x710) = 0;
      }
      else {
        Printf__7CSystemFPce(&System,s_CCharaPcs_calcViewer___s_801da830,param_1 + 0x3c4);
        pCVar7 = (CFileCHandle *)Open__5CFileFPcUlQ25CFile3PRI(&File,param_1 + 0x3c4,0,0);
        if (pCVar7 != (CFileCHandle *)0x0) {
          Read__5CFileFPQ25CFile7CHandle(&File,pCVar7);
          SyncCompleted__5CFileFPQ25CFile7CHandle(&File,pCVar7);
          iVar10 = __nw__FUlPQ27CMemory6CStagePci
                             (0x30,CharaPcs._192_4_,s_p_chara_viewer_cpp_801da7f8,0x111);
          if (iVar10 != 0) {
            iVar10 = __ct__Q26CChara5CAnimFv();
          }
          *(int *)(param_1 + 0x198) = iVar10;
          Create__Q26CChara5CAnimFPvPQ27CMemory6CStage
                    (*(undefined4 *)(param_1 + 0x198),File.m_readBuffer,*(CStage **)(param_1 + 0xd4)
                    );
          Close__5CFileFPQ25CFile7CHandle(&File,pCVar7);
        }
        *(undefined4 *)(param_1 + 0x3c0) = 0;
      }
    }
    if (*(int *)(param_1 + 0x4c4) != 0) {
      Printf__7CSystemFPce(&System,s_CCharaPcs_calcViewer___s_801da830,param_1 + 0x4c8);
      pCVar7 = (CFileCHandle *)Open__5CFileFPcUlQ25CFile3PRI(&File,param_1 + 0x4c8,0,0);
      if (pCVar7 != (CFileCHandle *)0x0) {
        piVar6 = *(int **)(param_1 + 0x2b0);
        if (piVar6 != (int *)0x0) {
          iVar10 = piVar6[1];
          piVar6[1] = iVar10 + -1;
          if ((iVar10 + -1 == 0) && (piVar6 != (int *)0x0)) {
            (**(code **)(*piVar6 + 8))(piVar6,1);
          }
          *(undefined4 *)(param_1 + 0x2b0) = 0;
        }
        Read__5CFileFPQ25CFile7CHandle(&File,pCVar7);
        SyncCompleted__5CFileFPQ25CFile7CHandle(&File,pCVar7);
        uVar8 = createTextureSet__9CCharaPcsFPvi(param_1,File.m_readBuffer,0);
        *(undefined4 *)(param_1 + 0x2b0) = uVar8;
        Close__5CFileFPQ25CFile7CHandle(&File,pCVar7);
      }
      *(undefined4 *)(param_1 + 0x4c4) = 0;
    }
    if (*(CModel **)(param_1 + 400) != (CModel *)0x0) {
      AttachAnim__Q26CChara6CModelFPQ26CChara5CAnimiii
                (*(CModel **)(param_1 + 400),*(CChara **)(param_1 + 0x198),0xffffffff,0xffffffff,
                 0xffffffff);
      AttachTextureSet__Q26CChara6CModelFP11CTextureSet
                (*(CModel **)(param_1 + 400),*(CTexture **)(param_1 + 0x2b0));
    }
  }
  if (DAT_8032edc8 == '\0') {
    DAT_8032edc4 = &DAT_80330c18;
    DAT_8032edc8 = '\x01';
  }
  if (DAT_8032edd0 == '\0') {
    DAT_8032edcc = 0;
    DAT_8032edd0 = '\x01';
  }
  DAT_8032edcc = DAT_8032edcc + 1;
  iVar10 = DAT_8032edcc >> 0x1f;
  Printf__8CGraphicFPce
            (&Graphic,&DAT_80330c20,
             (int)(char)DAT_8032edc4
                        [(iVar10 * 4 | (uint)((DAT_8032edcc >> 4) * 0x40000000 + iVar10) >> 0x1e) -
                         iVar10],0x8024402c);
  bVar3 = false;
  if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
    bVar3 = true;
  }
  if (bVar3) {
    uVar5 = 0;
  }
  else {
    countLeadingZeros(Pad._448_4_);
    uVar5 = Pad._4_2_;
  }
  bVar3 = false;
  if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
    bVar3 = true;
  }
  if (bVar3) {
    uVar9 = 0;
  }
  else {
    countLeadingZeros(Pad._448_4_);
    uVar9 = Pad._8_2_;
  }
  if ((*(int *)(param_1 + 400) != 0) && (*(int *)(param_1 + 0x70c) != 0)) {
    if (*(int *)(param_1 + 0x708) == 0) {
      *(undefined4 *)(param_1 + 0x704) = 0;
      AttachAnim__Q26CChara6CModelFPQ26CChara5CAnimiii
                (*(CModel **)(param_1 + 400),*(CChara **)(param_1 + 0x198),0xffffffff,0xffffffff,0);
    }
    else {
      *(undefined4 *)(param_1 + 0x704) = 0;
      pCStack_54 = (CProcess *)(uint)*(ushort *)(*(int *)(param_1 + 0x198) + 0x10);
      local_58 = (COrder *)0x43300000;
      dVar18 = (double)fmod((double)*(float *)(*(int *)(param_1 + 400) + 0xb4),
                            (double)(float)((double)CONCAT44(0x43300000,pCStack_54) -
                                           DOUBLE_80330c10));
      *(float *)(param_1 + 0x700) = (float)dVar18;
      AttachAnim__Q26CChara6CModelFPQ26CChara5CAnimiii
                (*(CModel **)(param_1 + 400),*(CChara **)(param_1 + 0x198),0xffffffff,0xffffffff,0);
    }
    *(undefined4 *)(param_1 + 0x70c) = 0;
  }
  if ((((uVar9 & 0x1000) != 0) && (*(int *)(param_1 + 0x1a0) == 0)) &&
     (*(CModel **)(param_1 + 400) != (CModel *)0x0)) {
    AttachAnim__Q26CChara6CModelFPQ26CChara5CAnimiii
              (*(CModel **)(param_1 + 400),*(CChara **)(param_1 + 0x198),0xffffffff,0xffffffff,
               0xffffffff);
  }
  if ((uVar9 & 0x800) != 0) {
    uVar14 = countLeadingZeros(*(undefined4 *)(param_1 + 0x6f8));
    *(uint *)(param_1 + 0x6f8) = uVar14 >> 5 & 0xff;
  }
  if ((uVar9 & 0x400) != 0) {
    uVar14 = countLeadingZeros(*(undefined4 *)(param_1 + 0x6f4));
    *(uint *)(param_1 + 0x6f4) = uVar14 >> 5 & 0xff;
  }
  if (*(int *)(param_1 + 0x6f4) == 0) {
    fVar2 = FLOAT_80330bf8;
    if ((uVar5 & 0x200) != 0) {
      fVar2 = FLOAT_80330c28;
    }
    fVar1 = FLOAT_80330bf8;
    if ((uVar5 & 0x100) != 0) {
      fVar1 = FLOAT_80330c2c;
    }
    fVar2 = fVar2 * fVar1;
  }
  else {
    fVar1 = FLOAT_80330be8;
    if ((uVar9 & 0x100) != 0) {
      fVar1 = FLOAT_80330bf8;
    }
    fVar2 = FLOAT_80330be8;
    if ((uVar9 & 0x200) != 0) {
      fVar2 = FLOAT_80330c28;
    }
    fVar2 = FLOAT_80330be8 + fVar1 + fVar2;
  }
  dVar18 = (double)fVar2;
  uVar14 = 0;
  iVar10 = param_1;
  do {
    if (*(int *)(iVar10 + 400) != 0) {
      dVar17 = (double)FLOAT_80330be8;
      if ((uVar14 != 0) && (*(int *)(iVar10 + 0x18c) != 0)) {
        local_58 = (COrder *)0x43300000;
        uVar4 = 1 << 0xf - *(int *)(*(int *)(*(int *)(iVar10 + 0x18c) + 0xa4) + 0x34);
        pCStack_54 = (CProcess *)
                     (((int)uVar4 >> 3) + (uint)((int)uVar4 < 0 && (uVar4 & 7) != 0) ^ 0x80000000);
        dVar17 = (double)(float)((double)CONCAT44(0x43300000,pCStack_54) - DOUBLE_80330be0);
      }
      if ((uVar14 == 0) && (*(int *)(param_1 + 0x5c8) != 0)) {
        *(undefined4 *)(param_1 + 0x5c8) = 0;
        texAnimSet = *(CTexAnimSet **)(*(int *)(iVar10 + 400) + 0xd4);
        if (texAnimSet != (CTexAnimSet *)0x0) {
          uVar4 = *(uint *)(param_1 + 0x5ec);
          uVar8 = 0xfffffffe;
          if (-1 < (int)uVar4) {
            uVar8 = 0xfffffffd;
          }
          local_58 = (COrder *)0x43300000;
          pCStack_54 = (CProcess *)(uVar4 & 0xffffffffU - ((int)uVar4 >> 0x1f) ^ 0x80000000);
          Change__11CTexAnimSetFPcfQ211CTexAnimSet9ANIM_TYPE
                    ((double)(float)((double)CONCAT44(0x43300000,pCStack_54) - DOUBLE_80330be0),
                     texAnimSet,param_1 + 0x5cc,uVar8);
        }
      }
      if (*(int *)(iVar10 + 0x198) != 0) {
        if ((uVar14 == 0) && (*(int *)(param_1 + 0x1a4) != 0)) {
          SetFrame__Q26CChara6CModelFf
                    ((float)(dVar18 + (double)(*(CModel **)(iVar10 + 400))->m_time),
                     *(CModel **)(iVar10 + 400));
          pCStack_54 = (CProcess *)(uint)*(ushort *)(*(int *)(param_1 + 0x198) + 0x10);
          local_58 = (COrder *)0x43300000;
          if ((float)((double)CONCAT44(0x43300000,pCStack_54) - DOUBLE_80330c10) <=
              *(float *)(*(int *)(param_1 + 400) + 0xb4)) {
            iVar11 = *(int *)(param_1 + 0x1ac) + 1;
            *(int *)(param_1 + 0x1ac) =
                 iVar11 - (iVar11 / *(int *)(param_1 + 0x1a4)) * *(int *)(param_1 + 0x1a4);
            AttachAnim__Q26CChara6CModelFPQ26CChara5CAnimiii
                      (*(CModel **)(param_1 + 400),
                       *(CChara **)(param_1 + *(int *)(param_1 + 0x1ac) * 4 + 0x1b0),0xffffffff,
                       0xffffffff,0);
            piVar6 = *(int **)(param_1 + 0x198);
            if (piVar6 != (int *)0x0) {
              iVar11 = piVar6[1];
              piVar6[1] = iVar11 + -1;
              if ((iVar11 + -1 == 0) && (piVar6 != (int *)0x0)) {
                (**(code **)(*piVar6 + 8))(piVar6,1);
              }
              *(undefined4 *)(param_1 + 0x198) = 0;
            }
            *(undefined4 *)(param_1 + 0x198) =
                 *(undefined4 *)(param_1 + *(int *)(param_1 + 0x1ac) * 4 + 0x1b0);
            *(int *)(*(int *)(param_1 + 0x198) + 4) = *(int *)(*(int *)(param_1 + 0x198) + 4) + 1;
          }
        }
        else if ((uVar14 == 0) && (*(int *)(param_1 + 0x708) != 0)) {
          if (*(int *)(param_1 + 0x704) == 0) {
            pCStack_54 = (CProcess *)(uint)*(ushort *)(*(int *)(param_1 + 0x198) + 0x10);
            local_58 = (COrder *)0x43300000;
            if (*(float *)(param_1 + 0x700) +
                (float)((double)CONCAT44(0x43300000,pCStack_54) - DOUBLE_80330c10) <=
                *(float *)(*(int *)(iVar10 + 400) + 0xb4)) {
              *(undefined4 *)(param_1 + 0x704) = 1;
              AttachAnim__Q26CChara6CModelFPQ26CChara5CAnimiii
                        (*(CModel **)(iVar10 + 400),*(CChara **)(param_1 + 0x1a0),0xffffffff,
                         0xffffffff,0xffffffff);
            }
          }
          else {
            pCStack_54 = (CProcess *)(uint)*(ushort *)(*(int *)(param_1 + 0x198) + 0x10);
            local_58 = (COrder *)0x43300000;
            if ((float)((double)CONCAT44(0x43300000,pCStack_54) - DOUBLE_80330c10) <=
                *(float *)(*(int *)(iVar10 + 400) + 0xb4)) {
              *(undefined4 *)(param_1 + 0x704) = 0;
              AttachAnim__Q26CChara6CModelFPQ26CChara5CAnimiii
                        (*(CModel **)(iVar10 + 400),*(CChara **)(param_1 + 0x198),0xffffffff,
                         0xffffffff,0);
            }
          }
          SetFrame__Q26CChara6CModelFf
                    ((float)(dVar18 + (double)(*(CModel **)(iVar10 + 400))->m_time),
                     *(CModel **)(iVar10 + 400));
        }
        else {
          SetFrame__Q26CChara6CModelFf
                    ((float)(dVar18 + (double)(*(CModel **)(iVar10 + 400))->m_time),
                     *(CModel **)(iVar10 + 400));
        }
      }
      if (DAT_8032edd8 == '\0') {
        DAT_8032edd4 = 1;
        DAT_8032edd8 = '\x01';
      }
      if (DAT_8032edd4 != 0) {
        srt_821._8_4_ = FLOAT_80330be8;
        srt_821._4_4_ = FLOAT_80330be8;
        srt_821._20_4_ = FLOAT_80330be8;
        srt_821._16_4_ = FLOAT_80330be8;
        srt_821._12_4_ = FLOAT_80330be8;
        srt_821._32_4_ = FLOAT_80330bf8;
        srt_821._28_4_ = FLOAT_80330bf8;
        srt_821._24_4_ = FLOAT_80330bf8;
        DAT_8032edd4 = 0;
      }
      fVar2 = FLOAT_80330be8;
      if (Pad._452_4_ == 0) {
        fVar2 = *(float *)(&Pad.field_0x2c +
                          (~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) * 0x54);
      }
      srt_821._16_4_ = (float)srt_821._16_4_ + fVar2;
      srt_821._0_4_ = (undefined4)dVar17;
      SRTToMatrix__5CMathFPA4_fP3SRT(&Math,auStack_188);
      SetMatrix__Q26CChara6CModelFPA4_f(*(CModel **)(iVar10 + 400),auStack_188);
      DumpMapFile__7CSystemFPv((CSystem *)auStack_1b8);
      Reset__10CStopWatchFv(auStack_1b8);
      Start__10CStopWatchFv(auStack_1b8);
      CalcMatrix__Q26CChara6CModelFv(*(undefined4 *)(iVar10 + 400));
      Stop__10CStopWatchFv(auStack_1b8);
      dVar17 = (double)Get__10CStopWatchFv(auStack_1b8);
      Reset__10CStopWatchFv(auStack_1b8);
      Start__10CStopWatchFv(auStack_1b8);
      CalcSkin__Q26CChara6CModelFv(*(undefined4 *)(iVar10 + 400));
      Stop__10CStopWatchFv(auStack_1b8);
      dVar15 = (double)Get__10CStopWatchFv(auStack_1b8);
      if (uVar14 == 0) {
        iVar11 = *(int *)(*(int *)(iVar10 + 400) + 0xd0);
        if (iVar11 != 0) {
          pCStack_54 = (CProcess *)(uint)*(ushort *)(iVar11 + 0x10);
          local_58 = (COrder *)0x43300000;
          dVar16 = (double)fmod((double)*(float *)(*(int *)(iVar10 + 400) + 0xb4),
                                (double)(float)(dVar18 + (double)(float)((double)CONCAT44(0x43300000
                                                                                          ,
                                                  pCStack_54) - DOUBLE_80330c10)));
          Printf__8CGraphicFPce
                    ((double)(float)dVar16,dVar18,&Graphic,s_FRAME_____2f_SPEED___2f_801da85c);
        }
        if (*(int *)(param_1 + 0x1a0) != 0) {
          puVar13 = &DAT_80330c34;
          if (*(int *)(param_1 + 0x704) == 0) {
            puVar13 = &DAT_80330c30;
          }
          puVar12 = &DAT_80330c40;
          if (*(int *)(param_1 + 0x708) != 0) {
            puVar12 = &DAT_80330c3c;
          }
          Printf__8CGraphicFPce
                    ((double)*(float *)(param_1 + 0x700),&Graphic,s_I____s_IFRAME_____2f__s_801da874
                     ,puVar12,puVar13);
        }
        if (*(int *)(param_1 + 0x1a4) != 0) {
          Printf__8CGraphicFPce(&Graphic,s_CONT____d_801da88c,*(undefined4 *)(param_1 + 0x1ac));
        }
        Printf__8CGraphicFPce
                  ((double)(float)(dVar17 + dVar15),dVar17,dVar15,&Graphic,
                   s_CPU_____5f___M_____5f___S_____5f_801da898,
                   *(undefined4 *)(*(int *)(*(int *)(iVar10 + 400) + 0xa4) + 8));
      }
      __ct__10CStopWatchFPc(auStack_1b8,0xffffffff);
    }
    uVar14 = uVar14 + 1;
    iVar10 = iVar10 + 4;
  } while (uVar14 < 2);
  return;
}

