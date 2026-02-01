// Function: command__10CGPartyObjFv
// Entry: 80121f40
// Size: 4252 bytes

/* WARNING: Removing unreachable block (ram,0x80122994) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void command__10CGPartyObjFv(CGPrgObj *param_1)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  uint uVar4;
  float fVar5;
  uint32_t *puVar6;
  int iVar7;
  undefined2 uVar8;
  ushort uVar10;
  float fVar9;
  void **ppvVar11;
  undefined4 uVar12;
  CCaravanWork *pCVar13;
  uint uVar14;
  int iVar15;
  int iVar16;
  undefined4 local_58;
  undefined4 local_54;
  uint32_t *local_50;
  undefined auStack_4c [4];
  uint32_t *local_48;
  int local_44;
  int local_40;
  float local_3c;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  
  if (MenuPcs._1856_4_ != 0) {
    return;
  }
  bVar1 = false;
  iVar15 = -1;
  bVar2 = false;
  iVar16 = -1;
  uVar14 = 0xffffffff;
  uVar12 = 0xffffffff;
  if (-1 < (int)((uint)*(byte *)&param_1[1].object.unk_0x168 << 0x18)) {
    if (((*(short *)((param_1->object).m_scriptHandle + 7) != 0) &&
        ((*(ushort *)&param_1[1].object.m_rotBaseX & 1) != 0)) &&
       (iVar7 = GetCtrlMode__6JoyBusFi(&Joybus,(int)(char)(param_1->object).m_animStateMisc),
       iVar7 != 1)) {
      iVar7 = 0;
      uVar4 = (uint)(char)(param_1->object).m_animStateMisc;
      bVar3 = false;
      if ((Pad._452_4_ != 0) || ((uVar4 == 0 && (Pad._448_4_ != -1)))) {
        bVar3 = true;
      }
      if (bVar3) {
        uVar10 = 0;
      }
      else {
        uVar10 = *(ushort *)
                  (&Pad.field_0x4 +
                  (uVar4 & ~((int)~(Pad._448_4_ - uVar4 | uVar4 - Pad._448_4_) >> 0x1f)) * 0x54);
      }
      if ((uVar10 & 0x60) == 0x60) {
        _IsUseCmdList__12CCaravanWorkFi((CCaravanWork *)(param_1->object).m_scriptHandle,0);
      }
      else {
        bVar3 = false;
        if ((Pad._452_4_ != 0) || ((uVar4 == 0 && (Pad._448_4_ != -1)))) {
          bVar3 = true;
        }
        if (bVar3) {
          uVar10 = 0;
        }
        else {
          uVar10 = *(ushort *)
                    (&Pad.field_0x8 +
                    (uVar4 & ~((int)~(Pad._448_4_ - uVar4 | uVar4 - Pad._448_4_) >> 0x1f)) * 0x54);
        }
        if ((uVar10 & 0x20) == 0) {
          bVar3 = false;
          if ((Pad._452_4_ != 0) || ((uVar4 == 0 && (Pad._448_4_ != -1)))) {
            bVar3 = true;
          }
          if (bVar3) {
            uVar10 = 0;
          }
          else {
            uVar10 = *(ushort *)
                      (&Pad.field_0x8 +
                      (uVar4 & ~((int)~(Pad._448_4_ - uVar4 | uVar4 - Pad._448_4_) >> 0x1f)) * 0x54)
            ;
          }
          if ((uVar10 & 0x40) != 0) {
            iVar7 = -1;
          }
        }
        else {
          iVar7 = 1;
        }
      }
      if (iVar7 != 0) {
        PlaySe__6CSoundFiiii(&Sound,0xc,0x40,0x7f,0);
        pCVar13 = (CCaravanWork *)(param_1->object).m_scriptHandle;
        uVar12 = _GetIdxCmdList__12CCaravanWorkFv(pCVar13);
        uVar8 = GetNextCmdListIdx__12CCaravanWorkFii(pCVar13,uVar12,iVar7);
        _IsUseCmdList__12CCaravanWorkFi(pCVar13,uVar8);
      }
      iVar7 = _GetIdxCmdList__12CCaravanWorkFv((CCaravanWork *)(param_1->object).m_scriptHandle);
      if (iVar7 == 0) {
        uVar14 = 1;
      }
      else {
        iVar7 = _GetIdxCmdList__12CCaravanWorkFv((CCaravanWork *)(param_1->object).m_scriptHandle);
        if (iVar7 == 1) {
          uVar14 = 9;
        }
        else {
          pCVar13 = (CCaravanWork *)(param_1->object).m_scriptHandle;
          uVar12 = _GetIdxCmdList__12CCaravanWorkFv(pCVar13);
          uVar4 = _DelCmdListAndItem__12CCaravanWorkFii(pCVar13,uVar12);
          uVar10 = *(ushort *)(Game.game.unkCFlatData0[2] + uVar4 * 0x48);
          if (uVar10 != 0x125) {
            if (uVar10 < 0x125) {
              if (uVar10 != 0xdf) {
                if (uVar10 < 0xdf) {
                  if (uVar10 == 1) goto LAB_80122254;
                }
                else if (uVar10 == 0x100) goto LAB_80122254;
                goto LAB_80122258;
              }
            }
            else if (uVar10 != 0x186) {
              if (uVar10 < 0x186) {
                if (uVar10 == 0x17d) goto LAB_80122254;
              }
              else if (uVar10 == 0x1f5) goto LAB_80122254;
              goto LAB_80122258;
            }
          }
LAB_80122254:
          uVar14 = uVar4 | 0x8000;
        }
      }
LAB_80122258:
      uVar12 = _GetIdxCmdList__12CCaravanWorkFv((CCaravanWork *)(param_1->object).m_scriptHandle);
    }
    if (((((int)((uint)*(byte *)&(param_1->object).m_weaponNodeFlags << 0x18) < 0) &&
         ((int)((uint)*(byte *)&param_1[1].object.m_shieldAttachNodeIndex << 0x18) < 0)) &&
        ((int)((uint)*(byte *)((int)&(param_1->object).m_weaponNodeFlags + 1) << 0x18) < 0)) &&
       (iVar7 = GetCtrlMode__6JoyBusFi(&Joybus,(int)(char)(param_1->object).m_animStateMisc),
       iVar7 != 1)) {
      pCVar13 = (CCaravanWork *)(param_1->object).m_scriptHandle;
      if ((pCVar13->gObjWork).m_hp == 0) {
        bVar1 = true;
        iVar15 = 0x1b;
      }
      else {
        bVar1 = param_1[1].object.m_attachLocal.y != 0.0;
        if (bVar1) {
          iVar15 = 0xc;
        }
        fVar9 = param_1[1].object.m_attachLocal.x;
        if (fVar9 != 0.0) {
          iVar7 = *(int *)((int)fVar9 + 0x500);
          if (iVar7 == 0x24) goto LAB_80122388;
          if (iVar7 < 0x24) {
            if (iVar7 < 0x12) {
              if ((iVar7 != 0xb) &&
                 (((10 < iVar7 || (9 < iVar7)) && (*(int *)((int)fVar9 + 0x550) == 0)))) {
                bVar2 = true;
                iVar16 = 4;
              }
            }
            else if (iVar7 < 0x1c) {
              if (iVar7 < 0x19) {
LAB_80122388:
                if (*(int *)((int)fVar9 + 0x550) == 0) {
                  bVar2 = true;
                  if ((((iVar7 == 0x24) &&
                       (iVar16 = CanAddTmpArtifact__12CCaravanWorkFi(pCVar13,1), iVar16 != 0)) ||
                      ((fVar9 = param_1[1].object.m_attachLocal.x,
                       *(int *)((int)fVar9 + 0x500) == 0x20 &&
                       (iVar16 = CanAddGil__12CCaravanWorkFi
                                           ((CCaravanWork *)(param_1->object).m_scriptHandle,
                                            *(undefined4 *)((int)fVar9 + 0x558)), iVar16 != 0)))) ||
                     (((iVar16 = *(int *)((int)param_1[1].object.m_attachLocal.x + 0x500),
                       iVar16 != 0x24 && (iVar16 != 0x20)) &&
                      (*(ushort *)((param_1->object).m_scriptHandle + 0x2d) + 1 < 0x41)))) {
                    iVar16 = 0x17;
                  }
                  else {
                    iVar16 = 4;
                  }
                }
              }
            }
            else if (iVar7 < 0x22) goto LAB_80122388;
          }
          else if (iVar7 == 0xca) {
            if (CFlat._4780_4_ == 0) {
              bVar2 = true;
              iVar16 = 0x1c;
            }
            else {
              bVar1 = true;
              iVar15 = 0x1c;
            }
          }
          else if (iVar7 < 0xca) {
            if (iVar7 == 200) {
              if (CFlat._4780_4_ == 0) {
                bVar2 = true;
                iVar16 = 0xb;
              }
              else {
                bVar1 = true;
                iVar15 = 0xb;
              }
            }
            else if (199 < iVar7) {
              if (CFlat._4780_4_ == 0) {
                bVar2 = true;
                iVar16 = 10;
              }
              else {
                bVar1 = true;
                iVar15 = 10;
              }
            }
          }
          else if (iVar7 == 0xcc) {
            bVar2 = true;
            iVar16 = 6;
          }
        }
        fVar9 = param_1[1].object.m_moveBaseSpeed;
        if (fVar9 != 0.0) {
          iVar15 = *(int *)((int)fVar9 + 0x500);
          bVar2 = true;
          if (iVar15 == 0xd) {
            iVar16 = 7;
          }
          else if (iVar15 == 0xe) {
            iVar16 = 8;
          }
          else {
            iVar16 = 5;
          }
          bVar1 = true;
          iVar15 = -1;
        }
      }
    }
    iVar7 = GetCtrlMode__6JoyBusFi(&Joybus,(int)(char)(param_1->object).m_animStateMisc);
    if (iVar7 != 1) {
      uVar10 = *(ushort *)&param_1[1].object.m_rotBaseX;
      if ((uVar10 & 2) != 0) {
        bVar2 = false;
        bVar1 = true;
        iVar15 = 0x1a;
      }
      if ((uVar10 & 4) != 0) {
        bVar2 = false;
        bVar1 = true;
        iVar15 = 0x1d;
      }
      if ((uVar10 & 8) != 0) {
        bVar2 = true;
        uVar14 = (uint)(char)(param_1->object).m_animStateMisc;
        iVar16 = 0x1a;
        bVar1 = false;
        iVar7 = 0;
        bVar3 = false;
        if ((Pad._452_4_ != 0) || ((uVar14 == 0 && (Pad._448_4_ != -1)))) {
          bVar3 = true;
        }
        if (bVar3) {
          uVar10 = 0;
        }
        else {
          uVar10 = *(ushort *)
                    (&Pad.field_0x8 +
                    (uVar14 & ~((int)~(Pad._448_4_ - uVar14 | uVar14 - Pad._448_4_) >> 0x1f)) * 0x54
                    );
        }
        if ((uVar10 & 0x20) == 0) {
          bVar3 = false;
          if ((Pad._452_4_ != 0) || ((uVar14 == 0 && (Pad._448_4_ != -1)))) {
            bVar3 = true;
          }
          if (bVar3) {
            uVar10 = 0;
          }
          else {
            uVar10 = *(ushort *)
                      (&Pad.field_0x8 +
                      (uVar14 & ~((int)~(Pad._448_4_ - uVar14 | uVar14 - Pad._448_4_) >> 0x1f)) *
                      0x54);
          }
          if ((uVar10 & 0x40) != 0) {
            iVar7 = -1;
          }
        }
        else {
          iVar7 = 1;
        }
        if (iVar7 != 0) {
          PlaySe__6CSoundFiiii(&Sound,0xc,0x40,0x7f,0);
          Chara._8196_4_ = Chara._8196_4_ + iVar7;
          if ((int)Chara._8196_4_ < 0) {
            Chara._8196_4_ = Chara._8196_4_ + 5;
          }
          else if (4 < (int)Chara._8196_4_) {
            Chara._8196_4_ = Chara._8196_4_ + -5;
          }
        }
        uVar14 = Chara._8196_4_ + 0x1e;
        uVar12 = Chara._8196_4_;
      }
    }
    SetBattleCommand__9CRingMenuFiii
              (*(CRingMenu **)
                (&MenuPcs.field_0x13c + (int)(param_1->object).m_scriptHandle[0xed] * 4),0,iVar15,
               0xffffffff);
    SetBattleCommand__9CRingMenuFiii
              (*(CRingMenu **)
                (&MenuPcs.field_0x13c + (int)(param_1->object).m_scriptHandle[0xed] * 4),1,iVar16,
               0xffffffff);
    SetBattleCommand__9CRingMenuFiii
              (*(CRingMenu **)
                (&MenuPcs.field_0x13c + (int)(param_1->object).m_scriptHandle[0xed] * 4),2,uVar14,
               uVar12);
  }
  if ((Game.game.m_gameWork.m_menuStageMode != '\0') &&
     (Game.game.m_gameWork.m_singleShopOrSmithMenuActiveFlag != '\0')) {
    return;
  }
  bVar3 = false;
  uVar4 = (uint)(char)(param_1->object).m_animStateMisc;
  if ((Pad._452_4_ != 0) || ((uVar4 == 0 && (Pad._448_4_ != -1)))) {
    bVar3 = true;
  }
  if (bVar3) {
    uVar10 = 0;
  }
  else {
    uVar10 = *(ushort *)
              (&Pad.field_0x8 +
              (uVar4 & ~((int)~(Pad._448_4_ - uVar4 | uVar4 - Pad._448_4_) >> 0x1f)) * 0x54);
  }
  if ((uVar10 & 0x100) != 0) {
    if (bVar1) {
      if (iVar15 == 0x1b) {
        changeStat__8CGPrgObjFiii(param_1,0x20,0,0);
      }
      fVar9 = param_1[1].object.m_attachLocal.y;
      if (fVar9 == 0.0) {
        fVar9 = param_1[1].object.m_attachLocal.x;
      }
      *(byte *)&param_1[1].object.unk_0x168 = *(byte *)&param_1[1].object.unk_0x168 & 0x7f | 0x80;
      if (fVar9 == 0.0) {
        local_2c = 0;
      }
      else {
        local_2c = (int)*(short *)((int)fVar9 + 0x30);
      }
      local_30 = iVar15;
      SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
                (&CFlat,param_1,2,0x14,2,&local_30,(CStack *)0x0);
      return;
    }
    if (-1 < (int)((uint)*(byte *)((int)&(param_1->object).m_weaponNodeFlags + 1) << 0x18)) {
      return;
    }
    if (-1 < (int)((uint)*(byte *)&param_1[1].object.m_shieldAttachNodeIndex << 0x18)) {
      return;
    }
    pCVar13 = (CCaravanWork *)(param_1->object).m_scriptHandle;
    if ((pCVar13->gObjWork).m_hp == 0) {
      return;
    }
    if (uVar14 == 0xffffffff) {
      return;
    }
    if ((*(ushort *)&param_1[1].object.m_rotBaseX & 8) != 0) {
      return;
    }
    fVar9 = (float)_GetIdxCmdList__12CCaravanWorkFv(pCVar13);
    param_1[1].object.unk_0x16C = fVar9;
    fVar9 = param_1[1].object.unk_0x16C;
    if (fVar9 == 0.0) {
      _GetCurrentWeaponItem__12CCaravanWorkFRiRi
                ((CCaravanWork *)(param_1->object).m_scriptHandle,&local_3c,&local_40);
      fVar9 = param_1[1].object.unk_0x16C;
      if (local_3c == fVar9) {
        ppvVar11 = (param_1->object).m_scriptHandle;
        if (*(short *)(ppvVar11 + 0x2b) < 0) {
          iVar15 = 0;
        }
        else {
          iVar15 = (int)*(short *)((int)ppvVar11 + *(short *)(ppvVar11 + 0x2b) * 2 + 0xb6);
        }
        if (local_40 == iVar15) {
          if (*(short *)(ppvVar11 + 0x2b) < 0) {
            puVar6 = (uint32_t *)0x0;
          }
          else {
            puVar6 = (uint32_t *)
                     (int)*(short *)((int)ppvVar11 + *(short *)(ppvVar11 + 0x2b) * 2 + 0xb6);
          }
          param_1[1].object.base_object.object.m_thisBase = puVar6;
          changeStat__8CGPrgObjFiii(param_1,7,0,0);
          return;
        }
      }
      ppvVar11 = (param_1->object).m_scriptHandle;
      iVar15 = (int)*(short *)(ppvVar11 + 0x2b);
      if (iVar15 < 0) {
        fVar5 = 0.0;
      }
      else {
        fVar5 = (float)(int)*(short *)((int)ppvVar11 + iVar15 * 2 + 0xb6);
      }
      param_1[1].object.unk_0x184 = fVar9;
      param_1[1].object.unk_0x188 = fVar5;
      *(byte *)&param_1[1].object.m_rotationX =
           *(byte *)&param_1[1].object.m_rotationX & 0xdf | 0x20;
      changeStat__8CGPrgObjFiii(param_1,0xf,0,0);
      return;
    }
    if (fVar9 == 1.4013e-45) {
      uVar10 = *(ushort *)((param_1->object).m_scriptHandle + 0xf8);
      if (uVar10 == 2) {
        changeStat__8CGPrgObjFiii(param_1,0x14,0,0);
        return;
      }
      if (uVar10 < 2) {
        changeStat__8CGPrgObjFiii(param_1,8,0,0);
        return;
      }
      if (3 < uVar10) {
        return;
      }
      changeStat__8CGPrgObjFiii(param_1,0x15,0,0);
      return;
    }
    puVar6 = (uint32_t *)_DelCmdListAndItem__12CCaravanWorkFii((param_1->object).m_scriptHandle);
    iVar15 = (int)puVar6 * 0x48;
    uVar10 = *(ushort *)(Game.game.unkCFlatData0[2] + iVar15);
    if (uVar10 == 0x125) {
      param_1[1].object.base_object.object.m_thisBase = (uint32_t *)0x220;
      changeStat__8CGPrgObjFiii(param_1,2,0,2);
      return;
    }
    if (0x124 < uVar10) {
      if (uVar10 != 0x186) {
        if (0x185 < uVar10) {
          if (uVar10 != 0x1f5) {
            return;
          }
          param_1[1].object.base_object.object.m_thisBase = puVar6;
          changeStat__8CGPrgObjFiii(param_1,2,0,0);
          return;
        }
        if (uVar10 != 0x17d) {
          return;
        }
      }
      iVar15 = useItem__10CGPartyObjFi((CGPartyObj *)param_1,puVar6);
      if (iVar15 == 0) {
        return;
      }
      _GetNumCombi__12CCaravanWorkFi
                ((CCaravanWork *)(param_1->object).m_scriptHandle,param_1[1].object.unk_0x16C,1);
      return;
    }
    if (uVar10 == 0xdf) {
      param_1[1].object.base_object.object.m_thisBase =
           (uint32_t *)(uint)*(ushort *)(Game.game.unkCFlatData0[2] + iVar15 + 10);
      changeStat__8CGPrgObjFiii(param_1,2,0,0);
      return;
    }
    if (uVar10 < 0xdf) {
      if (uVar10 != 1) {
        return;
      }
      _GetCurrentWeaponItem__12CCaravanWorkFRiRi
                ((CCaravanWork *)(param_1->object).m_scriptHandle,&local_44,&local_48);
      iVar15 = _GetIdxCmdList__12CCaravanWorkFv((CCaravanWork *)(param_1->object).m_scriptHandle);
      if ((local_44 == iVar15) && (local_48 == puVar6)) {
        param_1[1].object.base_object.object.m_thisBase = puVar6;
        changeStat__8CGPrgObjFiii(param_1,7,0,0);
        return;
      }
      fVar9 = (float)_GetIdxCmdList__12CCaravanWorkFv
                               ((CCaravanWork *)(param_1->object).m_scriptHandle);
      param_1[1].object.unk_0x184 = fVar9;
      param_1[1].object.unk_0x188 = (float)puVar6;
      *(byte *)&param_1[1].object.m_rotationX =
           *(byte *)&param_1[1].object.m_rotationX & 0xdf | 0x20;
      changeStat__8CGPrgObjFiii(param_1,0xf,0,0);
      return;
    }
    if (uVar10 != 0x100) {
      return;
    }
    if (puVar6 == (uint32_t *)0x103) {
      iVar15 = Rand__5CMathFUl(&Math,3);
      if (iVar15 == 0) {
        ClearAllSta__10CGCharaObjFv(param_1);
        setSta__10CGCharaObjFii(param_1,0x1b,900);
        _GetNumCombi__12CCaravanWorkFi
                  ((CCaravanWork *)(param_1->object).m_scriptHandle,param_1[1].object.unk_0x16C,1);
        return;
      }
      param_1[1].object.base_object.object.m_thisBase = (uint32_t *)0x103;
      changeStat__8CGPrgObjFiii(param_1,2,0,2);
      return;
    }
    param_1[1].object.base_object.object.m_thisBase =
         (uint32_t *)(uint)*(ushort *)(Game.game.unkCFlatData0[2] + iVar15 + 10);
    changeStat__8CGPrgObjFiii(param_1,2,0,0);
    return;
  }
  bVar1 = false;
  if ((Pad._452_4_ != 0) || ((uVar4 == 0 && (Pad._448_4_ != -1)))) {
    bVar1 = true;
  }
  if (bVar1) {
    uVar10 = 0;
  }
  else {
    uVar10 = *(ushort *)
              (&Pad.field_0x8 +
              (uVar4 & ~((int)~(Pad._448_4_ - uVar4 | uVar4 - Pad._448_4_) >> 0x1f)) * 0x54);
  }
  if ((uVar10 & 0x200) == 0) {
    return;
  }
  if (!bVar2) {
    return;
  }
  if (((((int)((uint)*(byte *)((int)&(param_1->object).m_weaponNodeFlags + 1) << 0x18) < 0) &&
       ((int)((uint)*(byte *)&param_1[1].object.m_shieldAttachNodeIndex << 0x18) < 0)) &&
      (pCVar13 = (CCaravanWork *)(param_1->object).m_scriptHandle, (pCVar13->gObjWork).m_hp != 0))
     && ((uVar14 != 0xffffffff && (iVar16 == 6)))) {
    _GetCurrentWeaponItem__12CCaravanWorkFRiRi(pCVar13,auStack_4c,&local_50);
    param_1[1].object.base_object.object.m_thisBase = local_50;
    changeStat__8CGPrgObjFiii(param_1,1,0,0);
    goto LAB_80122f30;
  }
  if (iVar16 == 4) {
    carry__10CGPartyObjFiP8CGObjecti
              ((CGPartyObj *)param_1,0,(CGObject *)param_1[1].object.m_attachLocal.x,0);
    goto LAB_80122f30;
  }
  if ((1 < iVar16 - 2U) && (iVar16 != 0x17)) goto LAB_80122f30;
  rotTarget__8CGPrgObjFP8CGPrgObj(param_1,(CGPrgObj *)param_1[1].object.m_attachLocal.x);
  changeStat__8CGPrgObjFiii(param_1,0xe,0,0);
  *(CGPrgObj **)((int)param_1[1].object.m_attachLocal.x + 0x550) = param_1;
  changeStat__8CGPrgObjFiii((CGPrgObj *)param_1[1].object.m_attachLocal.x,0xe,0,0);
  iVar15 = *(int *)((int)param_1[1].object.m_attachLocal.x + 0x504);
  uVar10 = *(ushort *)(Game.game.unkCFlatData0[2] + iVar15 * 0x48);
  if (uVar10 == 0x125) {
LAB_80122da8:
    iVar7 = 0;
  }
  else {
    if (uVar10 < 0x125) {
      if ((uVar10 == 0x100) || ((uVar10 < 0x100 && (uVar10 == 1)))) goto LAB_80122da8;
    }
    else if (uVar10 == 400) {
      iVar7 = 1;
      goto LAB_80122dbc;
    }
    iVar7 = 2;
  }
LAB_80122dbc:
  if ((iVar7 == 0) || (iVar7 == 2)) {
    if ((iVar15 < 0x9f) || (0xff < iVar15)) {
      AddItem__12CCaravanWorkFiPi
                ((CCaravanWork *)(param_1->object).m_scriptHandle,(short)iVar15,&local_54);
      Printf__7CSystemFPce
                (&System,&DAT_801dcd28,
                 *(undefined4 *)((int)param_1[1].object.m_attachLocal.x + 0x504));
    }
    else {
      AddTmpArtifact__12CCaravanWorkFiPi
                ((CCaravanWork *)(param_1->object).m_scriptHandle,iVar15,&local_54);
      Printf__7CSystemFPce
                (&System,&DAT_801dcd08,
                 *(undefined4 *)((int)param_1[1].object.m_attachLocal.x + 0x504));
    }
    if ((iVar7 == 0) &&
       (iVar15 = CanAddComList__12CCaravanWorkFi((CCaravanWork *)(param_1->object).m_scriptHandle,1)
       , iVar15 != 0)) {
      AddComList__12CCaravanWorkFiPi
                ((CCaravanWork *)(param_1->object).m_scriptHandle,(short)local_54,&local_58);
      Printf__7CSystemFPce(&System,&DAT_801dcd40,local_54,local_58);
    }
    fVar9 = param_1[1].object.m_attachLocal.x;
    if (*(short *)((int)fVar9 + 0x560) != 1) {
      (**(code **)((int)(param_1->object).base_object.object.m_vtable + 0x4c))
                (param_1,4,*(undefined4 *)((int)fVar9 + 0x504),0);
    }
  }
  else if (iVar15 == 400) {
    (**(code **)((int)(param_1->object).base_object.object.m_vtable + 0x4c))(param_1,5,400,0);
    Printf__7CSystemFPce
              (&System,&DAT_801dcd6c,*(undefined4 *)((int)param_1[1].object.m_attachLocal.x + 0x558)
              );
    AddGil__12CCaravanWorkFi
              ((CCaravanWork *)(param_1->object).m_scriptHandle,
               *(undefined4 *)((int)param_1[1].object.m_attachLocal.x + 0x558));
    fVar9 = param_1[1].object.m_attachLocal.x;
    if (*(short *)((int)fVar9 + 0x560) != 1) {
      (**(code **)((int)(param_1->object).base_object.object.m_vtable + 0x4c))
                (param_1,4,*(undefined4 *)((int)fVar9 + 0x504),0);
    }
  }
LAB_80122f30:
  fVar9 = param_1[1].object.m_attachLocal.x;
  *(byte *)&param_1[1].object.unk_0x168 = *(byte *)&param_1[1].object.unk_0x168 & 0x7f | 0x80;
  if (fVar9 == 0.0) {
    local_34 = 0;
  }
  else {
    local_34 = (int)*(short *)((int)fVar9 + 0x30);
  }
  local_38 = iVar16;
  SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
            (&CFlat,param_1,2,0x14,2,&local_38,(CStack *)0x0);
  if (iVar16 == 5) {
    carry__10CGPartyObjFiP8CGObjecti((CGPartyObj *)param_1,1,(CGObject *)0x0,0);
  }
  else if ((iVar16 == 7) || (iVar16 == 8)) {
    carry__10CGPartyObjFiP8CGObjecti((CGPartyObj *)param_1,2,(CGObject *)0x0,0);
  }
  return;
}

