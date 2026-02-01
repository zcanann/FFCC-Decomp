// Function: drawSingleMenu__8CMenuPcsFv
// Entry: 80149534
// Size: 2344 bytes

/* WARNING: Removing unreachable block (ram,0x80149e40) */
/* WARNING: Removing unreachable block (ram,0x80149e38) */
/* WARNING: Removing unreachable block (ram,0x8014954c) */
/* WARNING: Removing unreachable block (ram,0x80149544) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void drawSingleMenu__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  short sVar1;
  uint uVar2;
  uint uVar3;
  short *psVar4;
  int iVar5;
  double dVar6;
  double dVar7;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined8 local_60;
  undefined8 local_58;
  
  if ((Game.game.m_gameWork.m_menuStageMode != '\0') &&
     (Game.game.m_gameWork.m_singleShopOrSmithMenuActiveFlag != '\0')) {
    DrawInit__8CMenuPcsFv(menuPcs);
    DrawFilter__8CMenuPcsFUcUcUcUc(menuPcs,0,0,0,0xff);
    ClearZBufferRect__5CUtilFffff
              ((double)FLOAT_8033294c,(double)FLOAT_8033294c,(double)FLOAT_803329a4,
               (double)FLOAT_80332a20,&DAT_8032ec70);
    DrawInit__8CMenuPcsFv(menuPcs);
    if (*(char *)(Game.game.m_scriptFoodBase[0] + 0xbe0) == '\x01') {
      if (menuPcs->m_shopMenuPtr != (CShopMenu *)0x0) {
        Draw__9CShopMenuFv();
      }
    }
    else if ((*(char *)(Game.game.m_scriptFoodBase[0] + 0xbe0) == '\x02') &&
            (menuPcs->m_shopMenuPtr != (CShopMenu *)0x0)) {
      Draw__9CShopMenuFv();
    }
    if ((DAT_8032eec0 != 0) && (*(short *)(*(int *)&menuPcs->field_0x850 + 6) != 0)) {
      Game.game.m_gameWork.m_singleShopOrSmithMenuActiveFlag = '\0';
      _WaitDrawDone__8CGraphicFPci(&Graphic,s_singmenu_cpp_801de8d4,0x62b);
      menuPcs->field_0x85a = 0;
      if (DAT_8032eeb8 != (CFileCHandle *)0x0) {
        Close__5CFileFPQ25CFile7CHandle(&File,DAT_8032eeb8);
        DAT_8032eeb8 = (CFileCHandle *)0x0;
      }
      freeTexture__8CMenuPcsFiiii(menuPcs,5,2,0x2d,0x33);
      if (*(int *)&menuPcs->field_0x774 != 0) {
        __dt__Q29CCharaPcs7CHandleFv(*(int *)&menuPcs->field_0x774,1);
        *(undefined4 *)&menuPcs->field_0x774 = 0;
      }
      if (*(void **)&menuPcs->field_0x814 != (void *)0x0) {
        __dla__FPv(*(void **)&menuPcs->field_0x814);
        *(undefined4 *)&menuPcs->field_0x814 = 0;
      }
      if (*(void **)&menuPcs->field_0x82c != (void *)0x0) {
        __dla__FPv(*(void **)&menuPcs->field_0x82c);
        *(undefined4 *)&menuPcs->field_0x82c = 0;
      }
      if (*(int *)&menuPcs->field_0x850 != 0) {
        __dl__FPv();
        *(undefined4 *)&menuPcs->field_0x850 = 0;
      }
      if (*(int *)&menuPcs->field_0x848 != 0) {
        __dl__FPv();
        *(undefined4 *)&menuPcs->field_0x848 = 0;
      }
      heapWalker__Q27CMemory6CStageFiPvUl(*(CStage **)&menuPcs->field_0xf4,0xffffffff,0,0xffffffff);
      CreateTempBuffer__8CGraphicFv(&Graphic);
      *(undefined4 *)&menuPcs->field_0xf4 = 0;
      menuPcs->field_0x872 = 0;
      SetCtrlMode__6JoyBusFii(&Joybus,0,0);
    }
    if (DAT_8032eec0 == 0) {
      sVar1 = *(short *)&menuPcs->field_0x866;
      if (sVar1 == 1) {
        SingleDrawCtrl__8CMenuPcsFv(menuPcs);
      }
      else if (sVar1 < 1) {
        if (-1 < sVar1) {
          sVar1 = **(short **)&menuPcs->field_0x850;
          psVar4 = *(short **)&menuPcs->field_0x850 + 4;
          for (iVar5 = 0; iVar5 < sVar1; iVar5 = iVar5 + 1) {
            if ((iVar5 == 0) || (*(short *)&menuPcs->field_0x864 != 8)) {
              if (iVar5 == 0) {
                dVar6 = (double)*(float *)(psVar4 + 8);
                DrawInit__8CMenuPcsFv(menuPcs);
                _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp
                          (1,4,5,1);
                SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
                local_60 = (double)(longlong)(int)((double)FLOAT_80332940 * dVar6);
                local_68 = CONCAT31(0xffffff,(char)(int)((double)FLOAT_80332940 * dVar6));
                local_64 = local_68;
                GXSetChanMatColor(4,&local_64);
                SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x20);
                dVar6 = (double)FLOAT_8033294c;
                DrawRect__8CMenuPcsFUlfffffffff
                          (dVar6,dVar6,(double)FLOAT_803329a4,(double)FLOAT_80332928,dVar6,dVar6,
                           (double)FLOAT_80332934,(double)FLOAT_80332934,&MenuPcs,0);
                dVar6 = (double)FLOAT_8033294c;
                DrawRect__8CMenuPcsFUlfffffffff
                          (dVar6,(double)FLOAT_803329a8,(double)FLOAT_803329a4,
                           (double)FLOAT_80332928,dVar6,dVar6,(double)FLOAT_80332934,
                           (double)FLOAT_80332934,&MenuPcs,4);
                SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x28);
                dVar7 = (double)FLOAT_8033294c;
                uVar3 = 0x20;
                dVar6 = DOUBLE_80332938;
                for (uVar2 = 0x40; (int)uVar2 < 0x180; uVar2 = uVar2 + uVar3) {
                  if ((int)(0x180 - uVar2) < (int)uVar3) {
                    uVar3 = 0x180 - uVar2;
                  }
                  local_60 = (double)CONCAT44(0x43300000,uVar2 ^ 0x80000000);
                  local_58 = (double)CONCAT44(0x43300000,uVar3 ^ 0x80000000);
                  DrawRect__8CMenuPcsFUlfffffffff
                            (dVar7,(double)(float)(local_60 - dVar6),(double)FLOAT_803329a4,
                             (double)(float)(local_58 - dVar6),dVar7,dVar7,(double)FLOAT_80332934,
                             (double)FLOAT_80332934,&MenuPcs,0);
                }
              }
              else if (iVar5 == 1) {
                dVar6 = (double)*(float *)(psVar4 + 8);
                DrawInit__8CMenuPcsFv(menuPcs);
                _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp
                          (1,4,5,1);
                SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
                local_70 = 0xffffffff;
                local_6c = 0xffffffff;
                GXSetChanMatColor(4,&local_6c);
                SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x21);
                DrawRect__8CMenuPcsFUlfffffffff
                          (-(double)(float)((double)FLOAT_803329ac * dVar6 - (double)FLOAT_803329bc)
                           ,(double)FLOAT_80332948,(double)FLOAT_803329ac,(double)FLOAT_803329b0,
                           (double)FLOAT_8033294c,(double)FLOAT_8033294c,dVar6,
                           (double)FLOAT_80332934,&MenuPcs,0);
                DrawRect__8CMenuPcsFUlfffffffff
                          ((double)FLOAT_803329b4,(double)FLOAT_80332948,(double)FLOAT_803329ac,
                           (double)FLOAT_803329b0,(double)FLOAT_8033294c,(double)FLOAT_8033294c,
                           dVar6,(double)FLOAT_80332934,&MenuPcs,8);
              }
              else if (iVar5 == 2) {
                DrawSingleStat__8CMenuPcsFf((double)*(float *)(psVar4 + 8),menuPcs);
              }
              else {
                DrawSingleHelpWim__8CMenuPcsFf((double)*(float *)(psVar4 + 8),menuPcs);
              }
            }
            psVar4 = psVar4 + 0x20;
          }
        }
      }
      else if (sVar1 < 3) {
        sVar1 = **(short **)&menuPcs->field_0x850;
        psVar4 = *(short **)&menuPcs->field_0x850 + 4;
        for (iVar5 = 0; iVar5 < sVar1; iVar5 = iVar5 + 1) {
          if ((iVar5 == 0) || (*(short *)&menuPcs->field_0x864 != 8)) {
            if (iVar5 == 0) {
              dVar6 = (double)*(float *)(psVar4 + 8);
              DrawInit__8CMenuPcsFv(menuPcs);
              _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
              SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
              local_58 = (double)(longlong)(int)((double)FLOAT_80332940 * dVar6);
              local_78 = CONCAT31(0xffffff,(char)(int)((double)FLOAT_80332940 * dVar6));
              local_74 = local_78;
              GXSetChanMatColor(4,&local_74);
              SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x20);
              dVar6 = (double)FLOAT_8033294c;
              DrawRect__8CMenuPcsFUlfffffffff
                        (dVar6,dVar6,(double)FLOAT_803329a4,(double)FLOAT_80332928,dVar6,dVar6,
                         (double)FLOAT_80332934,(double)FLOAT_80332934,&MenuPcs,0);
              dVar6 = (double)FLOAT_8033294c;
              DrawRect__8CMenuPcsFUlfffffffff
                        (dVar6,(double)FLOAT_803329a8,(double)FLOAT_803329a4,(double)FLOAT_80332928,
                         dVar6,dVar6,(double)FLOAT_80332934,(double)FLOAT_80332934,&MenuPcs,4);
              SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x28);
              dVar7 = (double)FLOAT_8033294c;
              uVar3 = 0x20;
              dVar6 = DOUBLE_80332938;
              for (uVar2 = 0x40; (int)uVar2 < 0x180; uVar2 = uVar2 + uVar3) {
                if ((int)(0x180 - uVar2) < (int)uVar3) {
                  uVar3 = 0x180 - uVar2;
                }
                local_58 = (double)CONCAT44(0x43300000,uVar2 ^ 0x80000000);
                local_60 = (double)CONCAT44(0x43300000,uVar3 ^ 0x80000000);
                DrawRect__8CMenuPcsFUlfffffffff
                          (dVar7,(double)(float)(local_58 - dVar6),(double)FLOAT_803329a4,
                           (double)(float)(local_60 - dVar6),dVar7,dVar7,(double)FLOAT_80332934,
                           (double)FLOAT_80332934,&MenuPcs,0);
              }
            }
            else if (iVar5 == 1) {
              dVar6 = (double)*(float *)(psVar4 + 8);
              DrawInit__8CMenuPcsFv(menuPcs);
              _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
              SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
              local_7c = 0xffffffff;
              GXSetChanMatColor(4,&local_7c);
              SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x21);
              DrawRect__8CMenuPcsFUlfffffffff
                        (-(double)(float)((double)FLOAT_803329ac * dVar6 - (double)FLOAT_803329bc),
                         (double)FLOAT_80332948,(double)FLOAT_803329ac,(double)FLOAT_803329b0,
                         (double)FLOAT_8033294c,(double)FLOAT_8033294c,dVar6,(double)FLOAT_80332934,
                         &MenuPcs,0);
              DrawRect__8CMenuPcsFUlfffffffff
                        ((double)FLOAT_803329b4,(double)FLOAT_80332948,(double)FLOAT_803329ac,
                         (double)FLOAT_803329b0,(double)FLOAT_8033294c,(double)FLOAT_8033294c,dVar6,
                         (double)FLOAT_80332934,&MenuPcs,8);
            }
            else if (iVar5 == 2) {
              DrawSingleStat__8CMenuPcsFf((double)*(float *)(psVar4 + 8),menuPcs);
            }
            else {
              DrawSingleHelpWim__8CMenuPcsFf((double)*(float *)(psVar4 + 8),menuPcs);
            }
          }
          psVar4 = psVar4 + 0x20;
        }
        if (*(short *)(*(int *)&menuPcs->field_0x850 + 6) != 0) {
          Game.game.m_gameWork.m_singleShopOrSmithMenuActiveFlag = '\0';
          _WaitDrawDone__8CGraphicFPci(&Graphic,s_singmenu_cpp_801de8d4,0x62b);
          menuPcs->field_0x85a = 0;
          if (DAT_8032eeb8 != (CFileCHandle *)0x0) {
            Close__5CFileFPQ25CFile7CHandle(&File,DAT_8032eeb8);
            DAT_8032eeb8 = (CFileCHandle *)0x0;
          }
          freeTexture__8CMenuPcsFiiii(menuPcs,5,2,0x2d,0x33);
          if (*(int *)&menuPcs->field_0x774 != 0) {
            __dt__Q29CCharaPcs7CHandleFv(*(int *)&menuPcs->field_0x774,1);
            *(undefined4 *)&menuPcs->field_0x774 = 0;
          }
          if (*(void **)&menuPcs->field_0x814 != (void *)0x0) {
            __dla__FPv(*(void **)&menuPcs->field_0x814);
            *(undefined4 *)&menuPcs->field_0x814 = 0;
          }
          if (*(void **)&menuPcs->field_0x82c != (void *)0x0) {
            __dla__FPv(*(void **)&menuPcs->field_0x82c);
            *(undefined4 *)&menuPcs->field_0x82c = 0;
          }
          if (*(int *)&menuPcs->field_0x850 != 0) {
            __dl__FPv();
            *(undefined4 *)&menuPcs->field_0x850 = 0;
          }
          if (*(int *)&menuPcs->field_0x848 != 0) {
            __dl__FPv();
            *(undefined4 *)&menuPcs->field_0x848 = 0;
          }
          heapWalker__Q27CMemory6CStageFiPvUl
                    (*(CStage **)&menuPcs->field_0xf4,0xffffffff,0,0xffffffff);
          CreateTempBuffer__8CGraphicFv(&Graphic);
          *(undefined4 *)&menuPcs->field_0xf4 = 0;
          menuPcs->field_0x872 = 0;
          SetCtrlMode__6JoyBusFii(&Joybus,0,0);
        }
      }
    }
  }
  return;
}

