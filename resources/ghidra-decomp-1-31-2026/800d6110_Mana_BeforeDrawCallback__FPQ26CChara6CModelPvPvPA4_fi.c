// Function: Mana_BeforeDrawCallback__FPQ26CChara6CModelPvPvPA4_fi
// Entry: 800d6110
// Size: 2040 bytes

/* WARNING: Removing unreachable block (ram,0x800d68ec) */
/* WARNING: Removing unreachable block (ram,0x800d68e4) */
/* WARNING: Removing unreachable block (ram,0x800d6128) */
/* WARNING: Removing unreachable block (ram,0x800d6120) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void Mana_BeforeDrawCallback__FPQ26CChara6CModelPvPvPA4_fi
               (undefined4 param_1,undefined4 *param_2,void *param_3,undefined4 param_4,int param_5)

{
  CCharaPcsCHandle *pCVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  CModel *pCVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  CGObject *gObject;
  int iVar11;
  int iVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  float local_1e8;
  float local_1e4;
  float local_1e0;
  Vec local_1dc;
  Vec local_1d0;
  float local_1c4;
  float local_1c0;
  float local_1bc;
  float local_1b8;
  float local_1b4;
  float local_1b0;
  undefined auStack_1a8 [32];
  Mtx MStack_188;
  Mtx MStack_148;
  Mtx MStack_118;
  Mtx MStack_e8;
  Mat4x4 MStack_b8;
  longlong local_78;
  
  if ((param_5 == 0) && (iVar7 = param_2[8], *(char *)((int)param_3 + 0x1c) != '\0')) {
    if (Game.game.m_currentMapId == 0x21) {
      GXGetViewportv(&local_1c4);
    }
    SetViewport__8CGraphicFv(&Graphic);
    PSMTXIdentity(&MStack_118);
    PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_e8);
    PSMTX44Copy(&CameraPcs.m_screenMatrix,&MStack_b8);
    iVar9 = (int)FLOAT_80330e4c;
    local_78 = (longlong)iVar9;
    GetBackBufferRect2__8CGraphicFPvP9_GXTexObjiiiii12_GXTexFilter9_GXTexFmti
              (&Graphic,DAT_80238030,auStack_1a8,iVar9,iVar9,0x80,0x80,0,0,6,0);
    gObject = (CGObject *)*param_2;
    if (gObject != (CGObject *)0x0) {
      pCVar1 = (CCharaPcsCHandle *)GetCharaHandlePtr__FP8CGObjectl(gObject,0);
      GetCharaModelPtr__FPQ29CCharaPcs7CHandle(pCVar1);
      if (Game.game.m_currentSceneId == 7) {
        local_1d0.z = FLOAT_80330e4c;
        local_1d0.y = FLOAT_80330e4c;
        local_1d0.x = FLOAT_80330e4c;
      }
      else {
        local_1d0.x = (gObject->m_worldPosition).x;
        local_1d0.y = (gObject->m_worldPosition).y;
        local_1d0.z = (gObject->m_worldPosition).z;
      }
      local_1d0.y = local_1d0.y + FLOAT_80330e78;
      iVar2 = GXGetTexBufferSize(0x80,0x80,6,0,0);
      iVar3 = GXGetTexBufferSize(0x80,0x80,4,0,0);
      iVar8 = param_2[0x1e];
      if (*(char *)((int)param_3 + 0x38) != '\0') {
        C_MTXPerspective(FLOAT_80330e7c,FLOAT_80330e58,FLOAT_80330e58,FLOAT_80330e80,&MStack_188);
        GXSetProjection(&MStack_188,0);
        iVar10 = 0;
        uVar4 = __cvt_fp2unsigned((double)FLOAT_80330e4c);
        dVar14 = (double)FLOAT_80330e4c;
        dVar15 = (double)FLOAT_80330e58;
        iVar11 = iVar8;
        iVar12 = iVar7;
        do {
          local_1dc.x = local_1d0.x;
          local_1dc.y = local_1d0.y;
          local_1dc.z = local_1d0.z;
          local_1e8 = (float)dVar14;
          local_1e4 = (float)dVar15;
          local_1e0 = (float)dVar14;
          iVar5 = strcmp(&DAT_80330e50,0x8022b6b4);
          if (iVar5 == 0) {
            if (iVar10 == 0) {
              local_1dc.z = local_1dc.z - FLOAT_80330e58;
            }
            else if (iVar10 == 1) {
              local_1dc.x = local_1dc.x + FLOAT_80330e58;
            }
            else if (iVar10 == 2) {
              local_1dc.z = local_1dc.z + FLOAT_80330e58;
            }
            else if (iVar10 == 3) {
              local_1dc.x = local_1dc.x - FLOAT_80330e58;
            }
            if ((iVar10 == 4) || (iVar10 == 5)) goto LAB_800d63cc;
          }
          else {
LAB_800d63cc:
            if (iVar10 == 3) {
              local_1dc.z = local_1dc.z - FLOAT_80330e58;
            }
            else if (iVar10 < 3) {
              if (iVar10 == 1) {
                local_1dc.z = local_1dc.z + FLOAT_80330e58;
              }
              else if (iVar10 < 1) {
                if (-1 < iVar10) {
                  local_1dc.x = local_1dc.x + FLOAT_80330e58;
                }
              }
              else {
                local_1dc.x = local_1dc.x - FLOAT_80330e58;
              }
            }
            else if (iVar10 == 5) {
              local_1dc.y = local_1dc.y - FLOAT_80330e58;
              local_1e0 = FLOAT_80330e58;
              local_1e8 = FLOAT_80330e4c;
              local_1e4 = FLOAT_80330e4c;
            }
            else if (iVar10 < 5) {
              local_1dc.y = local_1dc.y + FLOAT_80330e58;
              local_1e8 = FLOAT_80330e4c;
              local_1e4 = FLOAT_80330e4c;
              local_1e0 = FLOAT_80330e68;
            }
          }
          C_MTXLookAt(&MStack_148,&local_1d0,&local_1e8,&local_1dc);
          SetViewport__8CGraphicFv(&Graphic);
          GXSetScissor(uVar4,uVar4,0x80,0x80);
          RenderTextureQuad__5CUtilFffffP9_GXTexObjP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
                    ((double)FLOAT_80330e4c,(double)FLOAT_80330e4c,(double)FLOAT_80330e84,
                     (double)FLOAT_80330e84,&DAT_8032ec70,iVar12,0,0,0,4,5);
          dVar13 = (double)FLOAT_80330e4c;
          GXSetViewport(dVar13,dVar13,(double)FLOAT_80330e84,(double)FLOAT_80330e84,dVar13,
                        (double)FLOAT_80330e58);
          GXSetScissor(uVar4,uVar4,0x80,0x80);
          PSMTXCopy(&MStack_148,&CameraPcs.m_cameraMatrix);
          GXSetProjection(&MStack_188,0);
          if ((((*(byte *)&gObject->m_weaponNodeFlags & 1) != 0) ||
              (gObject->m_attachOwner != (CGObject *)0x0)) &&
             (pCVar1 = gObject->m_attachOwner->m_charaModelHandle, pCVar1 != (CCharaPcsCHandle *)0x0
             )) {
            pCVar6 = pCVar1->m_model;
            pCVar6->m_cbUser0 = param_2;
            pCVar6->m_cbUser1 = param_3;
            pCVar1->m_model->m_customMeshDrawCallback =
                 Mana_BeforeDrawShadowLockEnvCallback__FPQ26CChara6CModelPvPvi;
            pCVar1->m_model->m_unknownCallback0x100 =
                 Chara_DrawShadowMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f;
            Draw__Q29CCharaPcs7CHandleFi(pCVar1,1);
            pCVar6 = pCVar1->m_model;
            pCVar6->m_cbUser0 = (void *)0x0;
            pCVar6->m_cbUser1 = (void *)0x0;
            pCVar1->m_model->m_customMeshDrawCallback = (void *)0x0;
            pCVar1->m_model->m_unknownCallback0x100 = (void *)0x0;
          }
          GetBackBufferRect2__8CGraphicFPvP9_GXTexObjiiiii12_GXTexFilter9_GXTexFmti
                    (&Graphic,DAT_80238030,iVar11,iVar9,iVar9,0x80,0x80,iVar2,1,4,0);
          iVar10 = iVar10 + 1;
          iVar2 = iVar2 + iVar3;
          iVar12 = iVar12 + 0x20;
          iVar11 = iVar11 + 0x20;
        } while (iVar10 < 6);
        PSMTXCopy(&MStack_e8,&CameraPcs.m_cameraMatrix);
        SetViewport__8CGraphicFv(&Graphic);
        GXSetScissor(0,0,0x280,0x1c0);
        iVar9 = 0;
        do {
          GXSetTevKColorSel(iVar9,6);
          GXSetTevKAlphaSel(iVar9,0);
          _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(iVar9,0,0);
          iVar9 = iVar9 + 1;
        } while (iVar9 < 0x10);
        *(undefined *)(param_2 + 0x3d) = 1;
      }
      iVar9 = param_2[0x1f];
      if (*(char *)((int)param_3 + 0x38) == '\0') {
        if (*(char *)(param_2 + 0x3d) == '\0') {
          GXInitTexObj(param_2[10],param_2[0xc],0x80,0x80,4,0,0,0);
          GXInitTexObj(param_2[0xb],param_2[0xd],0x80,0x80,4,0,0,0);
          drawParaboloidMap__FP9_GXTexObjP9_GXTexObjPvUlP9_GXTexObjUc
                    (iVar7,param_2[0xb],param_2[9],param_2[0x3b],iVar9 + 0x28,1);
          drawParaboloidMap__FP9_GXTexObjP9_GXTexObjPvUlP9_GXTexObjUc
                    (iVar7,param_2[10],param_2[9],param_2[0x3b],iVar9 + 0x28,0);
          RenderTextureQuad__5CUtilFffffP9_GXTexObjP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
                    ((double)FLOAT_80330e4c,(double)FLOAT_80330e4c,(double)FLOAT_80330e84,
                     (double)FLOAT_80330e84,&DAT_8032ec70,auStack_1a8,0,0,0,4,5);
          *(undefined *)(param_2 + 0x3d) = 1;
        }
      }
      else {
        GXInitTexObj(param_2[10],param_2[0xc],0x80,0x80,4,0,0,0);
        dVar14 = (double)FLOAT_80330e4c;
        GXInitTexObjLOD(dVar14,dVar14,dVar14,param_2[10],1,1,0,0,0);
        GXInitTexObj(param_2[0xb],param_2[0xd],0x80,0x80,4,0,0,0);
        dVar14 = (double)FLOAT_80330e4c;
        GXInitTexObjLOD(dVar14,dVar14,dVar14,param_2[0xb],1,1,0,0,0);
        drawParaboloidMap__FP9_GXTexObjP9_GXTexObjPvUlP9_GXTexObjUc
                  (iVar8,param_2[0xb],param_2[9],param_2[0x3b],iVar9 + 0x28,1);
        drawParaboloidMap__FP9_GXTexObjP9_GXTexObjPvUlP9_GXTexObjUc
                  (iVar8,param_2[10],param_2[9],param_2[0x3b],iVar9 + 0x28,0);
        SetViewport__8CGraphicFv(&Graphic);
        GXSetProjection(&MStack_b8,0);
        PSMTXCopy(&MStack_e8,&CameraPcs.m_cameraMatrix);
        RenderTextureQuad__5CUtilFffffP9_GXTexObjP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
                  ((double)FLOAT_80330e4c,(double)FLOAT_80330e4c,(double)FLOAT_80330e84,
                   (double)FLOAT_80330e84,&DAT_8032ec70,auStack_1a8,0,0,0,4,5);
      }
      GXSetZMode(1,3,1);
      pCVar1 = (CCharaPcsCHandle *)GetCharaHandlePtr__FP8CGObjectl(gObject,0);
      iVar7 = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(pCVar1);
      *(code **)(iVar7 + 0xf0) = Mana_BeforeDrawCallback__FPQ26CChara6CModelPvPvPA4_fi;
      *(code **)(iVar7 + 0xfc) = Mana_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f;
      if (Game.game.m_currentMapId == 0x21) {
        GXSetViewport((double)local_1c4,(double)local_1c0,(double)local_1bc,(double)local_1b8,
                      (double)local_1b4,(double)local_1b0);
      }
    }
  }
  return;
}

