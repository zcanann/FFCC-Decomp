// Function: BlurChara_AfterDrawModelCallback__FPQ26CChara6CModelPvPv
// Entry: 800de29c
// Size: 1084 bytes

/* WARNING: Removing unreachable block (ram,0x800de6bc) */
/* WARNING: Removing unreachable block (ram,0x800de2ac) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void BlurChara_AfterDrawModelCallback__FPQ26CChara6CModelPvPv
               (CModel *model,undefined4 *param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  double dVar6;
  double dVar7;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  float local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  undefined auStack_74 [36];
  longlong local_50;
  longlong local_48;
  undefined4 local_40;
  uint uStack_3c;
  undefined4 local_38;
  uint uStack_34;
  
  uVar3 = GetCharaHandlePtr__FP8CGObjectl((CGObject *)param_2[1],0);
  GXGetTexBufferSize(0x140,0xe0,6,0,0);
  uVar1 = (uint)FLOAT_80331050;
  local_50 = (longlong)(int)uVar1;
  uVar2 = (uint)FLOAT_80331054;
  local_48 = (longlong)(int)uVar2;
  GetBackBufferRect2__8CGraphicFPvP9_GXTexObjiiiii12_GXTexFilter9_GXTexFmti
            (&Graphic,DAT_80238030,auStack_74,0,0,uVar1,uVar2,0,1,6,0);
  SetVtxFmt_POS_CLR__5CUtilFv(&DAT_8032ec70);
  uStack_3c = uVar1 ^ 0x80000000;
  uStack_34 = uVar2 ^ 0x80000000;
  local_40 = 0x43300000;
  local_8c = (float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80331058);
  local_38 = 0x43300000;
  local_88 = (float)((double)CONCAT44(0x43300000,uStack_34) - DOUBLE_80331058);
  local_c0 = 0xff;
  local_80 = FLOAT_80331030;
  local_7c = FLOAT_80331030;
  local_78 = FLOAT_80331030;
  local_84 = FLOAT_80331030;
  BeginQuadEnv__5CUtilFv(&DAT_8032ec70);
  _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,4);
  local_c4 = local_c0;
  local_a4 = local_8c;
  local_a0 = local_88;
  local_9c = local_84;
  local_98 = local_80;
  local_94 = local_7c;
  local_90 = local_78;
  RenderQuadNoTex__5CUtilF3Vec3Vec8_GXColor(&DAT_8032ec70,&local_98,&local_a4,&local_c4);
  EndQuadEnv__5CUtilFv(&DAT_8032ec70);
  dVar6 = (double)FLOAT_80331030;
  GXSetViewport(dVar6,dVar6,(double)FLOAT_80331050,(double)FLOAT_80331054,dVar6,
                (double)FLOAT_8033103c);
  uVar4 = __cvt_fp2unsigned((double)FLOAT_80331054);
  uVar5 = __cvt_fp2unsigned((double)FLOAT_80331050);
  GXSetScissor(0,0,uVar5,uVar4);
  model->m_beforeMeshCallback = BlurChara_SetBeforeMeshLockEnvCallback__FPQ26CChara6CModelPvPvi;
  model->m_afterDrawModelCallback = (void *)0x0;
  Draw__Q29CCharaPcs7CHandleFi(uVar3,0);
  model->m_beforeMeshCallback = (void *)0x0;
  model->m_afterDrawModelCallback = BlurChara_AfterDrawModelCallback__FPQ26CChara6CModelPvPv;
  SetViewport__8CGraphicFv(&Graphic);
  GXSetScissor(0,0,0x280,0x1c0);
  GetBackBufferRect2__8CGraphicFPvP9_GXTexObjiiiii12_GXTexFilter9_GXTexFmti
            (&Graphic,*param_2,param_2[2],0,0,uVar1,uVar2,0,1,1,0);
  if (*(char *)(param_3 + 4) == '\x01') {
    dVar6 = (double)*(float *)(param_3 + 0x14);
    dVar7 = (double)(float)((double)FLOAT_80331044 * dVar6);
    RenderTextureQuad__5CUtilFffffP9_GXTexObjP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
              (-dVar7,-dVar6,(double)(float)((double)FLOAT_80331050 + dVar7),
               (double)(float)((double)FLOAT_80331054 + dVar6),&DAT_8032ec70,param_2[2],0,0,0,4,5);
    BeginQuadEnv__5CUtilFv(&DAT_8032ec70);
    SetVtxFmt_POS_CLR_TEX__5CUtilFv(&DAT_8032ec70);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,4);
    _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,3);
    GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
    GXLoadTexObj(param_2[2],0);
    local_7c = *(float *)(param_3 + 0x14);
    local_8c = (float)((double)FLOAT_80331050 - dVar7);
    local_88 = FLOAT_80331054 - local_7c;
    local_c0 = 0xffffffff;
    local_80 = (float)dVar7;
    local_78 = FLOAT_80331030;
    local_84 = FLOAT_80331030;
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(3,1,1,7);
    local_c8 = local_c0;
    local_bc = local_8c;
    local_b8 = local_88;
    local_b4 = local_84;
    local_b0 = local_80;
    local_ac = local_7c;
    local_a8 = local_78;
    RenderQuad__5CUtilF3Vec3Vec8_GXColorP5Vec2dP5Vec2d
              (&DAT_8032ec70,&local_b0,&local_bc,&local_c8,0,0);
    EndQuadEnv__5CUtilFv(&DAT_8032ec70);
    GetBackBufferRect2__8CGraphicFPvP9_GXTexObjiiiii12_GXTexFilter9_GXTexFmti
              (&Graphic,*param_2,param_2[2],0,0,uVar1,uVar2,0,1,1,0);
  }
  RenderTextureQuad__5CUtilFffffP9_GXTexObjP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
            ((double)FLOAT_80331030,(double)FLOAT_80331030,(double)FLOAT_80331050,
             (double)FLOAT_80331054,&DAT_8032ec70,auStack_74,0,0,0,4,5);
  return;
}

