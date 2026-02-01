// Function: Mana2_BeforeDrawCallback__FPQ26CChara6CModelPvPvPA4_fi
// Entry: 80107744
// Size: 1796 bytes

/* WARNING: Removing unreachable block (ram,0x80107e2c) */
/* WARNING: Removing unreachable block (ram,0x80107e24) */
/* WARNING: Removing unreachable block (ram,0x8010775c) */
/* WARNING: Removing unreachable block (ram,0x80107754) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void Mana2_BeforeDrawCallback__FPQ26CChara6CModelPvPvPA4_fi
               (undefined4 param_1,undefined4 *param_2,int param_3)

{
  CCharaPcsCHandle *pCVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  CGObject *gObject;
  int iVar5;
  double dVar6;
  double dVar7;
  undefined4 local_1f8;
  undefined4 local_1f4;
  float local_1f0;
  float local_1ec;
  float local_1e8;
  float local_1e4;
  float local_1e0;
  float local_1dc;
  float local_1d8;
  float local_1d4;
  float local_1d0;
  float local_1cc;
  float local_1c8;
  float local_1c4;
  float local_1c0;
  float local_1bc;
  float local_1b8;
  Vec local_1b4;
  Vec local_1a8;
  undefined auStack_19c [32];
  undefined auStack_17c [32];
  Mtx MStack_15c;
  Mtx MStack_11c;
  Mtx MStack_ec;
  Mtx MStack_bc;
  Mat4x4 MStack_8c;
  
  iVar5 = param_2[8];
  if (*(char *)(param_3 + 0x1c) != '\0') {
    PSMTXIdentity(&MStack_ec);
    PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_bc);
    PSMTX44Copy(&CameraPcs.m_screenMatrix,&MStack_8c);
    GetBackBufferRect2__8CGraphicFPvP9_GXTexObjiiiii12_GXTexFilter9_GXTexFmti
              (&Graphic,DAT_80238030,auStack_17c,0,0,0x80,0x80,0,1,6,0);
    gObject = (CGObject *)*param_2;
    if (gObject != (CGObject *)0x0) {
      pCVar1 = (CCharaPcsCHandle *)GetCharaHandlePtr__FP8CGObjectl(gObject,0);
      iVar2 = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(pCVar1);
      *(undefined4 *)(iVar2 + 0xf0) = 0;
      *(undefined4 *)(iVar2 + 0xfc) = 0;
      if (Game.game.m_currentSceneId == 7) {
        local_1a8.z = FLOAT_80331898;
        local_1a8.y = FLOAT_80331898;
        local_1a8.x = FLOAT_80331898;
      }
      else {
        local_1a8.x = (gObject->m_worldPosition).x;
        local_1a8.y = (gObject->m_worldPosition).y;
        local_1a8.z = (gObject->m_worldPosition).z;
      }
      local_1a8.y = FLOAT_803318c4 + local_1a8.y;
      uVar3 = GXGetTexBufferSize(0x80,0x80,6,0,0);
      GXGetTexBufferSize(0x80,0x80,4,0,0);
      uVar4 = param_2[0x1d];
      if (*(char *)(param_3 + 0x38) != '\0') {
        GetBackBufferRect2__8CGraphicFPvP9_GXTexObjiiiii12_GXTexFilter9_GXTexFmti
                  (&Graphic,DAT_80238030,auStack_19c,0,0,0x80,0x80,uVar3,0,0x16,1);
        dVar6 = (double)FLOAT_80331898;
        GXSetViewport(dVar6,dVar6,(double)FLOAT_803318c8,(double)FLOAT_803318c8,dVar6,
                      (double)FLOAT_803318a0);
        C_MTXPerspective(FLOAT_803318cc,FLOAT_803318a0,FLOAT_803318a0,FLOAT_803318d0,&MStack_15c);
        GXSetProjection(&MStack_15c,0);
        dVar6 = (double)FLOAT_80331898;
        dVar7 = (double)FLOAT_803318a0;
        iVar2 = 0;
        do {
          local_1b4.x = local_1a8.x;
          local_1b4.y = local_1a8.y;
          local_1b4.z = local_1a8.z;
          local_1bc = (float)dVar7;
          local_1b8 = (float)dVar6;
          if (iVar2 == 3) {
            local_1b4.y = (float)((double)local_1a8.y - dVar7);
            local_1bc = (float)dVar6;
            local_1b8 = (float)dVar7;
          }
          else if (iVar2 < 3) {
            if (iVar2 == 1) {
              local_1b4.x = (float)((double)local_1a8.x - dVar7);
            }
            else if (iVar2 < 1) {
              if (-1 < iVar2) {
                local_1b4.x = (float)((double)local_1a8.x + dVar7);
              }
            }
            else {
              local_1b4.y = (float)((double)local_1a8.y + dVar7);
              local_1bc = (float)dVar6;
              local_1b8 = FLOAT_8033189c;
            }
          }
          else if (iVar2 == 5) {
            local_1b4.z = (float)((double)local_1a8.z - dVar7);
          }
          else if (iVar2 < 5) {
            local_1b4.z = (float)((double)local_1a8.z + dVar7);
          }
          local_1c0 = (float)dVar6;
          C_MTXLookAt(&MStack_11c,&local_1a8,&local_1c0,&local_1b4);
          SetViewport__8CGraphicFv(&Graphic);
          GXSetScissor(0,0,0x280,0x1c0);
          RenderTextureQuad__5CUtilFffffP9_GXTexObjP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
                    ((double)FLOAT_80331898,(double)FLOAT_80331898,(double)FLOAT_803318c8,
                     (double)FLOAT_803318c8,&DAT_8032ec70,iVar5,0,0,0,4,5);
          iVar2 = iVar2 + 1;
          iVar5 = iVar5 + 0x20;
        } while (iVar2 < 6);
        PSMTXCopy(&MStack_bc,&CameraPcs.m_cameraMatrix);
        SetViewport__8CGraphicFv(&Graphic);
        GXSetScissor(0,0,0x280,0x1c0);
        GXSetZTexture(2,0x16,0);
        GXSetColorUpdate(0);
        BeginQuadEnv__5CUtilFv(&DAT_8032ec70);
        GXSetZMode(1,7,1);
        GXSetZCompLoc(0);
        SetVtxFmt_POS_CLR_TEX__5CUtilFv(&DAT_8032ec70);
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,4);
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,0xff);
        _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                  (0,0xf,0xf,0xf,0xf);
        _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                  (0,0,0,0,1,0);
        _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                  (0,7,7,7,6);
        _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                  (0,0,0,0,1,0);
        GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
        GXLoadTexObj(auStack_19c,0);
        local_1cc = FLOAT_80331898;
        local_1c8 = FLOAT_80331898;
        local_1c4 = FLOAT_80331898;
        local_1d8 = FLOAT_803318c8;
        local_1d4 = FLOAT_803318c8;
        local_1d0 = FLOAT_80331898;
        local_1f4 = 0xffffff00;
        local_1f0 = FLOAT_803318c8;
        local_1f8 = 0xffffff00;
        local_1ec = FLOAT_803318c8;
        local_1e8 = FLOAT_80331898;
        local_1e4 = FLOAT_80331898;
        local_1e0 = FLOAT_80331898;
        local_1dc = FLOAT_80331898;
        RenderQuad__5CUtilF3Vec3Vec8_GXColorP5Vec2dP5Vec2d
                  (&DAT_8032ec70,&local_1e4,&local_1f0,&local_1f8,0,0);
        EndQuadEnv__5CUtilFv(&DAT_8032ec70);
        GXSetZTexture(0,0x11,0);
        GXSetColorUpdate(1);
        GXSetAlphaUpdate(1);
        GXSetZCompLoc(1);
        local_1cc = FLOAT_80331898;
        local_1c8 = FLOAT_80331898;
        local_1c4 = FLOAT_80331898;
        RenderTextureQuad__5CUtilFffffP9_GXTexObjP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
                  ((double)FLOAT_80331898,(double)FLOAT_80331898,(double)FLOAT_803318c8,
                   (double)FLOAT_803318c8,&DAT_8032ec70,auStack_17c,0,0,0,4,5);
        *(undefined *)(param_2 + 0x3b) = 1;
      }
      iVar5 = param_2[0x1e];
      if (*(char *)(param_3 + 0x38) == '\0') {
        if (*(char *)(param_2 + 0x3b) == '\0') {
          GXInitTexObj(param_2[10],param_2[0xc],0x80,0x80,4,1,1,0);
          GXInitTexObj(param_2[0xb],param_2[0xd],0x80,0x80,4,1,1,0);
          drawParaboloidMap__FP9_GXTexObjP9_GXTexObjPvUlP9_GXTexObjUc
                    (param_2[8],param_2[0xb],param_2[9],param_2[0x39],iVar5 + 0x28,1);
          drawParaboloidMap__FP9_GXTexObjP9_GXTexObjPvUlP9_GXTexObjUc
                    (param_2[8],param_2[10],param_2[9],param_2[0x39],iVar5 + 0x28,0);
          *(undefined *)(param_2 + 0x3b) = 1;
        }
      }
      else {
        GXInitTexObj(param_2[10],param_2[0xc],0x80,0x80,4,0,0,0);
        GXInitTexObj(param_2[0xb],param_2[0xd],0x80,0x80,4,0,0,0);
        drawParaboloidMap__FP9_GXTexObjP9_GXTexObjPvUlP9_GXTexObjUc
                  (uVar4,param_2[0xb],param_2[9],param_2[0x39],iVar5 + 0x28,1);
        drawParaboloidMap__FP9_GXTexObjP9_GXTexObjPvUlP9_GXTexObjUc
                  (uVar4,param_2[10],param_2[9],param_2[0x39],iVar5 + 0x28,0);
        SetViewport__8CGraphicFv(&Graphic);
        GXSetProjection(&MStack_8c,0);
        PSMTXCopy(&MStack_bc,&CameraPcs.m_cameraMatrix);
      }
      GXSetZMode(1,3,1);
      pCVar1 = (CCharaPcsCHandle *)GetCharaHandlePtr__FP8CGObjectl(gObject,0);
      iVar5 = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(pCVar1);
      *(code **)(iVar5 + 0xf0) = Mana2_BeforeDrawCallback__FPQ26CChara6CModelPvPvPA4_fi;
      *(code **)(iVar5 + 0xfc) = Mana2_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f;
    }
  }
  return;
}

