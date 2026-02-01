// Function: onCalc__8CMesMenuFv
// Entry: 8009d69c
// Size: 2292 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onCalc__8CMesMenuFv(int param_1)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  uint32_t uVar4;
  uint uVar5;
  int iVar6;
  bool bVar7;
  uint uVar8;
  double dVar9;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  uint uStack_24;
  undefined4 local_20;
  uint uStack_1c;
  
  if (((Game.game.m_gameWork.m_menuStageMode != '\0') && (0 < *(int *)(param_1 + 0x18))) &&
     (*(int *)(param_1 + 0x18) < 4)) {
    return;
  }
  if (*(int *)(param_1 + 0x18) < 4) {
    uVar2 = CFlat._4768_4_ & CFlat._4772_4_ & 1;
  }
  else {
    uVar2 = CFlat._4768_4_ & CFlat._4772_4_ & 2;
  }
  if (*(uint *)(param_1 + 0x3df8) != -uVar2 >> 0x1f) {
    Printf__7CSystemFPce(&System,&DAT_801d9e9c);
    uVar2 = countLeadingZeros(*(undefined4 *)(param_1 + 0x3df8));
    *(uint *)(param_1 + 0x3df8) = uVar2 >> 5 & 0xff;
    *(int *)(param_1 + 0x3df4) = 0x10 - *(int *)(param_1 + 0x3df4);
  }
  uVar2 = *(int *)(param_1 + 0x3df4) - 1;
  *(uint *)(param_1 + 0x3df4) = uVar2 & ~((int)uVar2 >> 0x1f);
  iVar6 = *(int *)(param_1 + 0x18);
  if ((3 < iVar6) && (*(int *)(param_1 + 8) == 0)) {
    return;
  }
  if ((iVar6 < 4) && (uVar4 = Game.game.m_scriptFoodBase[iVar6], uVar4 != 0)) {
    uVar2 = (uint)*(ushort *)(uVar4 + 0x1c);
    iVar6 = uVar2 * 6;
    if (*(int *)(param_1 + 0x3dac) < iVar6) {
      *(int *)(param_1 + 0x3dac) = iVar6;
    }
    else if (iVar6 < *(int *)(param_1 + 0x3dac)) {
      *(uint *)(param_1 + 0x3dac) = uVar2 * 6;
    }
    iVar6 = *(int *)(param_1 + 0x3da8);
    if (iVar6 < *(int *)(param_1 + 0x3dac)) {
      iVar6 = iVar6 / 0xc + (iVar6 >> 0x1f);
      iVar6 = param_1 + (iVar6 - (iVar6 >> 0x1f)) * 4;
      if (*(int *)(iVar6 + 0x3db0) == 0) {
        *(undefined4 *)(iVar6 + 0x3db0) = 0x10;
      }
      iVar3 = *(int *)(param_1 + 0x3da8) + 2;
      iVar6 = *(int *)(param_1 + 0x3dac);
      if (iVar3 < *(int *)(param_1 + 0x3dac)) {
        iVar6 = iVar3;
      }
      *(int *)(param_1 + 0x3da8) = iVar6;
    }
    else if (*(int *)(param_1 + 0x3dac) < iVar6) {
      *(uint *)(param_1 + 0x3da8) = iVar6 - 2U & ~((int)(iVar6 - 2U) >> 0x1f);
      iVar6 = *(int *)(param_1 + 0x3da8) / 0xc + (*(int *)(param_1 + 0x3da8) >> 0x1f);
      iVar6 = param_1 + (iVar6 - (iVar6 >> 0x1f)) * 4;
      if (*(int *)(iVar6 + 0x3dd0) == 0) {
        *(undefined4 *)(iVar6 + 0x3dd0) = 0x10;
      }
      if (*(int *)(param_1 + 0x3df0) == 0) {
        *(undefined4 *)(param_1 + 0x3df0) = 0x10;
      }
    }
    iVar3 = 2;
    iVar6 = param_1;
    do {
      uVar2 = *(int *)(iVar6 + 0x3db0) - 1;
      *(uint *)(iVar6 + 0x3db0) = uVar2 & ~((int)uVar2 >> 0x1f);
      uVar2 = *(int *)(iVar6 + 0x3dd0) - 1;
      *(uint *)(iVar6 + 0x3dd0) = uVar2 & ~((int)uVar2 >> 0x1f);
      uVar2 = *(int *)(iVar6 + 0x3db4) - 1;
      *(uint *)(iVar6 + 0x3db4) = uVar2 & ~((int)uVar2 >> 0x1f);
      uVar2 = *(int *)(iVar6 + 0x3dd4) - 1;
      *(uint *)(iVar6 + 0x3dd4) = uVar2 & ~((int)uVar2 >> 0x1f);
      uVar2 = *(int *)(iVar6 + 0x3db8) - 1;
      *(uint *)(iVar6 + 0x3db8) = uVar2 & ~((int)uVar2 >> 0x1f);
      uVar2 = *(int *)(iVar6 + 0x3dd8) - 1;
      *(uint *)(iVar6 + 0x3dd8) = uVar2 & ~((int)uVar2 >> 0x1f);
      uVar2 = *(int *)(iVar6 + 0x3dbc) - 1;
      *(uint *)(iVar6 + 0x3dbc) = uVar2 & ~((int)uVar2 >> 0x1f);
      uVar2 = *(int *)(iVar6 + 0x3ddc) - 1;
      *(uint *)(iVar6 + 0x3ddc) = uVar2 & ~((int)uVar2 >> 0x1f);
      iVar6 = iVar6 + 0x10;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    uVar2 = *(int *)(param_1 + 0x3df0) - 1;
    *(uint *)(param_1 + 0x3df0) = uVar2 & ~((int)uVar2 >> 0x1f);
  }
  if (*(int *)(param_1 + 8) == 0) {
    return;
  }
  iVar6 = *(int *)(param_1 + 0xc);
  if (iVar6 == 2) goto LAB_8009de74;
  if (1 < iVar6) {
    if (iVar6 < 4) {
      uStack_1c = *(uint *)(param_1 + 0x10) ^ 0x80000000;
      local_20 = 0x43300000;
      uStack_24 = *(uint *)(param_1 + 0x14) ^ 0x80000000;
      local_28 = 0x43300000;
      dVar9 = (double)sin((double)(FLOAT_80330910 *
                                   (FLOAT_80330914 -
                                   (float)((double)CONCAT44(0x43300000,uStack_1c) - DOUBLE_80330900)
                                   / (float)((double)CONCAT44(0x43300000,uStack_24) -
                                            DOUBLE_80330900)) + FLOAT_80330980));
      *(float *)(param_1 + 0x3d84) = FLOAT_803308ec * (FLOAT_80330914 + (float)dVar9);
    }
    goto LAB_8009de74;
  }
  if (iVar6 == 0) {
    uStack_24 = *(uint *)(param_1 + 0x10) ^ 0x80000000;
    local_28 = 0x43300000;
    uStack_1c = *(uint *)(param_1 + 0x14) ^ 0x80000000;
    local_20 = 0x43300000;
    sin((double)(FLOAT_80330980 +
                (FLOAT_80330910 * (float)((double)CONCAT44(0x43300000,uStack_24) - DOUBLE_80330900))
                / (float)((double)CONCAT44(0x43300000,uStack_1c) - DOUBLE_80330900)));
    goto LAB_8009de74;
  }
  if (iVar6 < 0) goto LAB_8009de74;
  *(float *)(param_1 + 0x3d84) = FLOAT_80330914;
  Calc__4CMesFv(param_1 + 0x1c);
  uVar8 = 0;
  uVar2 = 0;
  if (0 < *(int *)(param_1 + 0x10)) {
    iVar6 = 0;
    do {
      if ((*(uint *)(param_1 + 0x3d90) & 1 << iVar6) != 0) {
        uVar5 = GetButtonDown__8CMenuPcsFi(&MenuPcs,iVar6);
        uVar8 = uVar8 | uVar5 & 0xffff;
        uVar5 = GetButtonRepeat__8CMenuPcsFi(&MenuPcs,iVar6);
        uVar2 = uVar2 | uVar5 & 0xffff;
      }
      iVar6 = iVar6 + 1;
    } while (iVar6 < 4);
  }
  iVar6 = GetWait__4CMesFv(param_1 + 0x1c);
  if (iVar6 == 3) {
    iVar6 = *(int *)(param_1 + 0x3d34);
    iVar3 = *(int *)(param_1 + 0x3d38);
    if ((uVar2 & 8) == 0) {
      if ((uVar2 & 4) == 0) {
        if ((uVar8 & 0x200) != 0) {
          if (iVar3 < 0) {
            if ((*(uint *)(param_1 + 0x3d8c) & 0x4000) == 0) {
              PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
            }
          }
          else {
            iVar6 = iVar3;
            if ((*(uint *)(param_1 + 0x3d8c) & 0x4000) == 0) {
              PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
            }
          }
        }
      }
      else {
        iVar6 = iVar6 + 1;
        if (*(int *)(param_1 + 0x3d30) <= iVar6) {
          iVar6 = 0;
        }
        if ((*(uint *)(param_1 + 0x3d8c) & 0x4000) == 0) {
          PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
        }
      }
    }
    else {
      iVar6 = iVar6 + -1;
      if (iVar6 < 0) {
        iVar6 = *(int *)(param_1 + 0x3d30) + -1;
      }
      if ((*(uint *)(param_1 + 0x3d8c) & 0x4000) == 0) {
        PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
      }
    }
    *(int *)(param_1 + 0x3d34) = iVar6;
    if ((-1 < iVar3) && (iVar6 == iVar3)) {
      iVar6 = -1;
    }
    *(int *)(param_1 + 0x3cdc) = iVar6;
  }
  else {
    iVar6 = GetWait__4CMesFv(param_1 + 0x1c);
    if (((iVar6 == 1) || (iVar6 = GetWait__4CMesFv(param_1 + 0x1c), iVar6 == 5)) &&
       (*(int *)(param_1 + 0x3cc8) == 0)) {
      *(undefined4 *)(param_1 + 0x3cc8) = 1;
      *(undefined4 *)(param_1 + 0x3cd8) = 0;
    }
  }
  if ((uVar8 & 0x100) == 0) {
LAB_8009dcc8:
    bVar1 = *(int *)(param_1 + 0x3cc8) != 0;
    if (!bVar1) goto LAB_8009de74;
    bVar7 = false;
    if ((bVar1) && (*(int *)(param_1 + 0x3cd8) == *(int *)(param_1 + 0x3cd4))) {
      bVar7 = true;
    }
    if (!bVar7) goto LAB_8009de74;
  }
  else {
    iVar6 = GetWait__4CMesFv(param_1 + 0x1c);
    if (iVar6 == 0) {
      *(int *)(param_1 + 0x3c9c) = *(int *)(param_1 + 0x3c98) + 1000;
      useFlag__4CMesFii(param_1 + 0x1c,*(undefined4 *)(param_1 + 0x3c28),1);
      goto LAB_8009dcc8;
    }
    iVar6 = GetWait__4CMesFv(param_1 + 0x1c);
    if ((iVar6 == 3) && ((*(uint *)(param_1 + 0x3d8c) & 0x4000) == 0)) {
      PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
    }
    iVar6 = GetWait__4CMesFv(param_1 + 0x1c);
    if ((((iVar6 != 1) && (iVar6 = GetWait__4CMesFv(param_1 + 0x1c), iVar6 != 5)) &&
        (*(int *)(param_1 + 0x3c90) == 0)) && ((*(uint *)(param_1 + 0x3d8c) & 0x4000) == 0)) {
      PlaySe__6CSoundFiiii(&Sound,0xc,0x40,0x7f,0);
    }
    if (*(int *)(param_1 + 0x3cc8) == 0) {
      *(undefined4 *)(param_1 + 0x3cc8) = 1;
      *(undefined4 *)(param_1 + 0x3cd8) = 0;
      goto LAB_8009dcc8;
    }
  }
  if (*(int *)(param_1 + 0x3c90) == 0) {
    Next__4CMesFv(param_1 + 0x1c);
  }
  else {
    iVar6 = GetWait__4CMesFv(param_1 + 0x1c);
    if ((iVar6 != 4) && (*(undefined4 *)(param_1 + 0x3da4) = 0, *(int *)(param_1 + 0xc) < 2)) {
      if ((*(uint *)(param_1 + 0x3d8c) & 0x40) == 0) {
        *(undefined4 *)(param_1 + 0xc) = 2;
        *(undefined4 *)(param_1 + 0x10) = 0;
        *(undefined4 *)(param_1 + 0x14) = 4;
        if (((*(uint *)(param_1 + 0x3d8c) & 1) == 0) &&
           ((*(uint *)(param_1 + 0x3d8c) & 0x4000) == 0)) {
          PlaySe__6CSoundFiiii(&Sound,6,0x40,0x7f,0);
        }
      }
      else {
        Set__4CMesFPci(param_1 + 0x1c,0,0);
        local_38 = *(undefined4 *)(param_1 + 0x18);
        local_34 = *(undefined4 *)(param_1 + 0x3da4);
        SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
                  (&CFlat,0,1,3,2,&local_38,(CStack *)0x0);
        *(undefined4 *)(param_1 + 0xc) = 4;
        *(undefined4 *)(param_1 + 8) = 0;
        if (*(int *)(param_1 + 0x18) < 4) {
          SetFade__9CRingMenuFi
                    (*(undefined4 *)(&MenuPcs.field_0x13c + *(int *)(param_1 + 0x18) * 4),1);
        }
      }
    }
  }
LAB_8009de74:
  *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + 1;
  if (*(int *)(param_1 + 0x14) < *(int *)(param_1 + 0x10)) {
    iVar6 = *(int *)(param_1 + 0xc);
    if (iVar6 == 2) {
      *(undefined4 *)(param_1 + 0xc) = 3;
      *(undefined4 *)(param_1 + 0x10) = 0;
      *(undefined4 *)(param_1 + 0x14) = 8;
    }
    else if (iVar6 < 2) {
      if (iVar6 == 0) {
        *(undefined4 *)(param_1 + 0xc) = 1;
        *(undefined4 *)(param_1 + 0x10) = 0;
        *(undefined4 *)(param_1 + 0x14) = 0;
      }
    }
    else if (iVar6 < 4) {
      *(undefined4 *)(param_1 + 0xc) = 4;
      *(undefined4 *)(param_1 + 0x10) = 0;
      *(undefined4 *)(param_1 + 0x14) = 0;
      Set__4CMesFPci(param_1 + 0x1c,0,0);
      local_30 = *(undefined4 *)(param_1 + 0x18);
      local_2c = *(undefined4 *)(param_1 + 0x3da4);
      SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
                (&CFlat,0,1,3,2,&local_30,(CStack *)0x0);
      *(undefined4 *)(param_1 + 0xc) = 4;
      *(undefined4 *)(param_1 + 8) = 0;
      if (*(int *)(param_1 + 0x18) < 4) {
        SetFade__9CRingMenuFi
                  (*(undefined4 *)(&MenuPcs.field_0x13c + *(int *)(param_1 + 0x18) * 4),1);
      }
    }
  }
  return;
}

