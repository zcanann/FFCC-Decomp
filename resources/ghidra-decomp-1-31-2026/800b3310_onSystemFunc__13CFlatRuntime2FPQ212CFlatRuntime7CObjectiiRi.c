// Function: onSystemFunc__13CFlatRuntime2FPQ212CFlatRuntime7CObjectiiRi
// Entry: 800b3310
// Size: 23664 bytes

/* WARNING: Removing unreachable block (ram,0x800b8f64) */
/* WARNING: Removing unreachable block (ram,0x800b8f5c) */
/* WARNING: Removing unreachable block (ram,0x800b8f54) */
/* WARNING: Removing unreachable block (ram,0x800b8f4c) */
/* WARNING: Removing unreachable block (ram,0x800b3338) */
/* WARNING: Removing unreachable block (ram,0x800b3330) */
/* WARNING: Removing unreachable block (ram,0x800b3328) */
/* WARNING: Removing unreachable block (ram,0x800b3320) */
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4
onSystemFunc__13CFlatRuntime2FPQ212CFlatRuntime7CObjectiiRi
          (CFlatRuntime2 *flatRuntime2,CObject *object,undefined4 param_3,int param_4,
          undefined4 *param_5)

{
  int *piVar1;
  float fVar2;
  char cVar3;
  float fVar4;
  float fVar5;
  float b;
  float radius;
  uint uVar6;
  undefined4 uVar7;
  int iVar8;
  ushort uVar22;
  uint uVar9;
  CVector *pCVar10;
  CVector *pCVar11;
  Vec *pVVar12;
  undefined *puVar13;
  undefined *puVar14;
  undefined *puVar15;
  undefined4 uVar16;
  CObject *object_00;
  CMes *mes;
  CFileCHandle *fileHandle;
  void *pvVar17;
  Vec *p;
  short sVar23;
  CRomLetterWork *pCVar18;
  undefined4 *puVar19;
  int *piVar20;
  CFont *pCVar21;
  uint32_t *puVar24;
  int iVar25;
  uint extraout_r4;
  int iVar26;
  int iVar27;
  float *pfVar28;
  uint *puVar29;
  char *pcVar30;
  uint uVar31;
  char *pcVar32;
  uint32_t uVar33;
  int iVar34;
  int iVar35;
  int iVar36;
  int iVar37;
  int iVar38;
  int iVar39;
  uint32_t *puVar40;
  uint32_t uVar41;
  uint unaff_r24;
  char *pcVar42;
  uint32_t uVar43;
  uint32_t uVar44;
  char *pcVar45;
  uint32_t uVar46;
  uint32_t uVar47;
  uint32_t uVar48;
  double dVar49;
  double dVar50;
  double dVar51;
  double in_f28;
  double dVar52;
  double dVar53;
  double in_f30;
  undefined auStack_d88 [4];
  undefined4 local_d84;
  undefined auStack_d80 [4];
  undefined auStack_d7c [4];
  undefined4 local_d78;
  undefined auStack_d74 [4];
  undefined4 local_d70;
  undefined auStack_d6c [4];
  undefined4 local_d68;
  undefined auStack_d64 [4];
  undefined4 local_d60;
  undefined4 local_d5c;
  undefined4 local_d58;
  undefined4 local_d54;
  undefined auStack_d50 [4];
  undefined auStack_d4c [4];
  undefined local_d48;
  undefined local_d47;
  undefined local_d46;
  undefined local_d45;
  float local_d44;
  uint32_t local_d40;
  undefined4 local_d3c;
  undefined4 local_d38;
  undefined4 local_d34;
  undefined4 local_d30;
  float local_d2c;
  int local_d28;
  float local_d24;
  float local_d20;
  int local_d1c;
  float local_d18;
  float local_d14;
  float local_d10;
  float local_d0c;
  float local_d08;
  float local_d04;
  float local_d00;
  CVector CStack_cfc;
  CVector CStack_cf0;
  CVector CStack_ce4;
  CVector CStack_cd8;
  undefined4 local_ccc;
  undefined4 local_cc8;
  undefined4 local_cc4;
  CVector CStack_cc0;
  CVector CStack_cb4;
  CVector CStack_ca8;
  CVector CStack_c9c;
  CVector CStack_c90;
  CVector CStack_c84;
  CVector CStack_c78;
  CVector CStack_c6c;
  CVector CStack_c60;
  CVector CStack_c54;
  CVector CStack_c48;
  CVector CStack_c3c;
  CVector CStack_c30;
  CVector CStack_c24;
  CVector CStack_c18;
  CVector CStack_c0c;
  CVector CStack_c00;
  CVector CStack_bf4;
  CVector CStack_be8;
  CVector CStack_bdc;
  CVector CStack_bd0;
  CVector CStack_bc4;
  CVector CStack_bb8;
  uint32_t local_bac;
  uint32_t local_ba8;
  uint32_t local_ba4;
  int local_ba0 [4];
  CVector local_b90;
  Quat local_b84;
  Quat local_b74;
  Quat local_b64;
  Quat local_b54;
  Quat local_b44;
  float local_b34;
  float local_b30;
  float local_b2c;
  uint32_t local_b28;
  uint32_t local_b24;
  uint32_t local_b20;
  uint32_t local_b1c;
  uint32_t local_b18;
  uint32_t local_b14;
  float local_b10;
  float local_b0c;
  float local_b08;
  undefined4 local_b04;
  undefined4 local_b00;
  undefined4 local_afc;
  uint32_t local_af8;
  uint32_t local_af4;
  uint32_t local_af0;
  undefined4 local_aec;
  undefined4 local_ae8;
  undefined4 local_ae4;
  Vec VStack_ae0;
  Vec VStack_ad4;
  Vec VStack_ac8;
  Vec local_abc;
  CVector CStack_ab0;
  CVector CStack_aa4;
  CVector CStack_a98;
  CVector CStack_a8c;
  CVector CStack_a80;
  Vec local_a74;
  Vec local_a68;
  uint32_t local_a5c;
  uint32_t local_a58;
  uint32_t local_a54;
  undefined auStack_a50 [32];
  CRomLetterWork local_a30 [8];
  Mtx MStack_a10;
  Mtx MStack_9e0;
  Mtx MStack_9b0;
  Mtx MStack_980;
  Mtx MStack_950;
  Mtx MStack_920;
  PPPCREATEPARAM PStack_8f0;
  CNextScript CStack_884;
  char acStack_684 [256];
  undefined auStack_584 [256];
  CNextScript CStack_484;
  char local_284 [256];
  char local_184 [260];
  undefined8 local_80;
  undefined8 local_78;
  
  fVar2 = FLOAT_80330b30;
  switch(param_4) {
  case -0xfd:
    dVar49 = (double)GetLeftStickX__4CPadFl(&Pad,*object->m_localBase);
    dVar50 = (double)GetLeftStickY__4CPadFl(&Pad,*object->m_localBase);
    *(float *)object->m_localBase[1] = (float)dVar49;
    *(float *)object->m_localBase[2] = (float)dVar50;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xfc:
    DbgMenuPcs._10844_4_ = *object->m_localBase;
    DbgMenuPcs._10848_4_ = object->m_localBase[1];
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xfb:
    SetNextScriptNewGame__5CGameFv(&Game.game);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xfa:
    ItemJump__9CGItemObjFif((double)(float)object->m_localBase[1],*object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xf9:
    SetFullScreenShadowCamLen__10CCameraPcsFf((double)(float)*object->m_localBase,&CameraPcs);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xf8:
    uVar9 = GetNumMes__9CFlatDataFv((CFlatData *)&System);
    if (2 < uVar9) {
      Printf__7CSystemFPce(&System,&DAT_801da6ec,*object->m_localBase);
    }
    AddNoFreeSeGroup__6CSoundFi(&Sound,(short)*object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xf7:
    puVar24 = object->m_localBase;
    __ct__6CColorFUcUcUcUc
              (auStack_d88,puVar24[2] & 0xff,puVar24[3] & 0xff,puVar24[4] & 0xff,puVar24[5] & 0xff);
    local_d84 = __op8_GXColor__6CColorFv();
    puVar24 = object->m_localBase;
    pCVar21 = (CFont *)GetFont22__8CMenuPcsFv(&MenuPcs);
    SetTlutColor__5CFontFii8_GXColor(pCVar21,*puVar24 + 0xb);
    pCVar21 = (CFont *)GetFont22__8CMenuPcsFv(&MenuPcs);
    FlushTlutColor__5CFontFv(pCVar21);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xf6:
    Game.game.m_caravanWorkArr[*object->m_localBase].m_gil = object->m_localBase[1];
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xf4:
    pppSetDebugHide__8CPartPcsFUc(&PartPcs,(char)*object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
  case -0xf5:
    SeMaxVolume__6CSoundFi(&Sound,*object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xf3:
    uVar7 = GetSysControl__13CFlatRuntime2Fi(flatRuntime2,*object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,uVar7);
    *param_5 = 0;
    break;
  case -0xf2:
    puVar24 = object->m_localBase;
    SetMapAnimID__7CMapMngFiiii(&MapMng,(char)*puVar24,puVar24[1],puVar24[2],(char)puVar24[3]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xf1:
    resetSpawnBit__13CFlatRuntime2Fi(flatRuntime2,*object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xf0:
    puVar24 = object->m_localBase;
    __shl2i(0,1,puVar24[1]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti
              (flatRuntime2,object,
               *(uint *)(&flatRuntime2->field_0x12f4 + *puVar24 * 8) & extraout_r4);
    *param_5 = 0;
    break;
  case -0xef:
    calcAStar__6CAStarFv((CAStar *)&DbgMenuPcs.field_0x2a5c);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xee:
    pfVar28 = (float *)object->m_localBase;
    addAstar__6CAStarFfffii
              (*pfVar28,pfVar28[1],pfVar28[2],(CAStar *)&DbgMenuPcs.field_0x2a5c,pfVar28[3],
               pfVar28[4]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xed:
    __ct__7CVectorFv(&local_bac);
    puVar24 = object->m_localBase;
    local_bac = *puVar24;
    local_ba8 = puVar24[1];
    local_ba4 = puVar24[2];
    __ct__7CVectorFfff(FLOAT_80330b30,FLOAT_80330b90,FLOAT_80330b30,&CStack_cfc);
    uVar7 = __opP3Vec__7CVectorFv();
    uVar16 = __opP3Vec__7CVectorFv(&local_bac);
    iVar8 = CheckHitCylinderNear__7CMapPcsFP3VecP3VecfUl
                      ((double)FLOAT_80330b30,&MapPcs,uVar16,uVar7,object->m_localBase[3]);
    if (iVar8 == 0) {
      push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
      *param_5 = 0;
    }
    else {
      uVar7 = __opP3Vec__7CVectorFv(&local_bac);
      CalcHitPosition__7CMapPcsFP3Vec(&MapPcs,uVar7);
      *(uint32_t *)object->m_localBase[4] = local_ba8;
      push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,1);
      *param_5 = 0;
    }
    break;
  case -0xec:
    iVar8 = GetPadType__6JoyBusFi(&Joybus,*object->m_localBase);
    uVar9 = countLeadingZeros(0x40000 - iVar8);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,uVar9 >> 5 & 0xff);
    *param_5 = 0;
    break;
  case -0xeb:
    puVar24 = object->m_localBase;
    SetBonusCondition__10CGPartyObjFiiiii(*puVar24,puVar24[1],puVar24[2],puVar24[3],puVar24[4]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xea:
    SetSpecularAlpha__9CCharaPcsFi(&CharaPcs,*object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xe9:
    if (*object->m_localBase == 0) {
      uVar7 = GetTmpFrameBuffer__8CGraphicFv(&Graphic);
      GXInitTexObj(auStack_a50,uVar7,0x280,0x1c0,4,0,0,0);
      dVar49 = (double)FLOAT_80330b30;
      GXInitTexObjLOD(dVar49,dVar49,dVar49,auStack_a50,0,0,0,0,0);
      __ct__6CColorFUcUcUcUc(auStack_d80,0xff,0xff,0xff,object->m_localBase[1] & 0xff);
      uVar7 = __opP8_GXColor__6CColorFv();
      RenderTextureQuad__5CUtilFffffP9_GXTexObjP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
                ((double)FLOAT_80330b30,(double)FLOAT_80330b30,(double)FLOAT_80330b88,
                 (double)FLOAT_80330b8c,&DAT_8032ec70,auStack_a50,0,0,uVar7,4,5);
    }
    else {
      uVar7 = GetTmpFrameBuffer__8CGraphicFv(&Graphic);
      GetBackBufferRect2__8CGraphicFPvP9_GXTexObjiiiii12_GXTexFilter9_GXTexFmti
                (&Graphic,uVar7,0,0,0,0x280,0x1c0,0,0,4,0);
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xe8:
    puVar24 = object->m_localBase;
    __ct__6CColorFUcUcUcUc(auStack_d7c,puVar24[1] & 0xff,puVar24[2] & 0xff,puVar24[3] & 0xff,0xff);
    local_d78 = __op8_GXColor__6CColorFv();
    SetExtraFontTlut__8CMenuPcsFi8_GXColor(&MenuPcs,*object->m_localBase,&local_d78);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xe7:
    CharaPcs._68_4_ = *object->m_localBase;
    CharaPcs._72_4_ = (undefined4)(float)object->m_localBase[1];
    local_78 = (double)(longlong)(int)CharaPcs._72_4_;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xe6:
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti
              (flatRuntime2,object,
               (uint)(ushort)Game.game.m_caravanWorkArr[*object->m_localBase].m_inventoryItemCount);
    *param_5 = 0;
    break;
  case -0xe5:
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti
              (flatRuntime2,object,Game.game.m_caravanWorkArr[*object->m_localBase].m_gil);
    *param_5 = 0;
    break;
  case -0xe4:
    puVar24 = object->m_localBase;
    if (puVar24[1] == 1) {
      DeleteItem__12CCaravanWorkFii(Game.game.m_caravanWorkArr + *puVar24,puVar24[2],1);
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xe3:
    puVar24 = object->m_localBase;
    uVar9 = 0;
    if ((puVar24[1] & 2) != 0) {
      iVar8 = FindItem__12CCaravanWorkFi(Game.game.m_caravanWorkArr + *puVar24,puVar24[2]);
      uVar9 = 0xffffffffU - (iVar8 >> 0x1f) & 2;
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,uVar9);
    *param_5 = 0;
    break;
  case -0xe2:
    SetMiniGameParam__12CMiniGamePcsFii(0x80300268,*object->m_localBase,object->m_localBase[1]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xe1:
    uVar7 = GetMiniGameParam__12CMiniGamePcsFi(0x80300268,*object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,uVar7);
    *param_5 = 0;
    break;
  case -0xe0:
    SetMapObjPrioID__7CMapMngFiUc(&MapMng,*object->m_localBase,(char)object->m_localBase[1]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xdf:
    puVar24 = object->m_localBase;
    uVar46 = *puVar24;
    if (uVar46 == 1) {
      if (puVar24[1] == 0) {
        EndMiruraEvent__8CPartPcsFv(&PartPcs);
      }
      else {
        StartMiruraEvent__8CPartPcsFv(&PartPcs);
      }
    }
    else if (((int)uVar46 < 1) && (-1 < (int)uVar46)) {
      if (puVar24[1] == 0) {
        EndLocationTitle__8CPartPcsFv(&PartPcs);
      }
      else {
        StartLocationTitle__8CPartPcsFv(&PartPcs);
      }
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xde:
    SysControl__13CFlatRuntime2Fii(flatRuntime2,*object->m_localBase,object->m_localBase[1]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xdd:
    FadeOutSe__6CSoundFii(&Sound,*object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xdc:
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti
              (flatRuntime2,object,
               (uint)*(ushort *)
                      (Game.game.unkCFlatData0[3] +
                      *object->m_localBase * 0x3e + object->m_localBase[1] * 2));
    *param_5 = 0;
    break;
  case -0xdb:
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xda:
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xd9:
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,1);
    *param_5 = 0;
    break;
  case -0xd8:
    uVar7 = isLoadLayerASyncCompleted__13CFlatRuntime2Fi(flatRuntime2,*object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,uVar7);
    *param_5 = 0;
    break;
  case -0xd7:
    loadLayerASync__13CFlatRuntime2FiPc
              (flatRuntime2,*object->m_localBase,
               (flatRuntime2->flatRuntimeBase).m_strBlob +
               (flatRuntime2->flatRuntimeBase).m_strOffs[object->m_localBase[1]]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xd6:
    puVar24 = object->m_localBase;
    local_78 = (double)(longlong)(int)(FLOAT_80330b74 * (float)puVar24[10]);
    local_80 = (double)(longlong)(int)(FLOAT_80330b74 * (float)puVar24[0xb]);
    local_d48 = (undefined)(int)(FLOAT_80330b74 * (float)puVar24[10]);
    local_d45 = (undefined)(int)(FLOAT_80330b74 * (float)puVar24[0xb]);
    local_d47 = local_d48;
    local_d46 = local_d48;
    drawLayer__13CFlatRuntime2FiPciiiiiiffP8_GXColori
              ((double)(float)puVar24[8],(double)(float)puVar24[9],flatRuntime2,*object->m_localBase
               ,(flatRuntime2->flatRuntimeBase).m_strBlob +
                (flatRuntime2->flatRuntimeBase).m_strOffs[puVar24[1]],puVar24[2],puVar24[3],
               puVar24[4],puVar24[5],(short)puVar24[6],(short)puVar24[7],&local_d48,puVar24[0xc]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xd5:
    loadLayer__13CFlatRuntime2FiPc
              (flatRuntime2,*object->m_localBase,
               (flatRuntime2->flatRuntimeBase).m_strBlob +
               (flatRuntime2->flatRuntimeBase).m_strOffs[object->m_localBase[1]]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xd4:
    puVar24 = object->m_localBase;
    if (*puVar24 == 0) {
      SetDrawRangeMapObj__7CMapMngFf((float)puVar24[1],&MapMng);
    }
    else {
      SetDrawRangeOctTree__7CMapMngFf((float)puVar24[1],&MapMng);
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xd3:
    puVar24 = object->m_localBase;
    if (puVar24[1] == 0) {
      SetMeshCameraSemiTransAlpha__7CMapMngFUsii(&MapMng,(short)*puVar24,0,0x3c);
    }
    else {
      SetMeshCameraSemiTransAlpha__7CMapMngFUsii(&MapMng,(short)*puVar24,0x80,0x3c);
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xd2:
    if (*object->m_localBase == 0) {
      strcpy(&CStack_884,&flatRuntime2->field_0x15cc);
      SetNextScript__5CGameFPQ25CGame11CNextScript(&Game.game,&CStack_884);
    }
    else {
      memcpy(&flatRuntime2->field_0x15cc,0x8022b6b4,0x100);
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xd1:
    uVar9 = GetNumMes__9CFlatDataFv((CFlatData *)&System);
    if (2 < uVar9) {
      Printf__7CSystemFPce(&System,&DAT_801da6b8,*object->m_localBase);
    }
    CrossPlayBgm__6CSoundFii(&Sound,*object->m_localBase,object->m_localBase[1]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xd0:
    puVar24 = object->m_localBase;
    __ct__7CVectorFfff((float)puVar24[2],(float)puVar24[3],(float)puVar24[4],&CStack_cf0);
    uVar7 = __opP3Vec__7CVectorFv();
    iVar8 = CcClass2D__13CFlatRuntime2FiiP3VecffiPP8CGObject
                      ((double)(float)puVar24[5],(double)(float)puVar24[6],flatRuntime2,*puVar24,
                       puVar24[1],uVar7,puVar24[7],local_ba0);
    iVar26 = 0;
    if (0 < iVar8) {
      if (8 < iVar8) {
        piVar20 = local_ba0;
        uVar9 = iVar8 - 1U >> 3;
        iVar25 = 0;
        if (0 < iVar8 + -8) {
          do {
            iVar39 = iVar25 + 4;
            iVar38 = iVar25 + 8;
            iVar37 = iVar25 + 0xc;
            iVar35 = iVar25 + 0x10;
            iVar36 = iVar25 + 0x14;
            iVar34 = iVar25 + 0x18;
            *(int *)(object->m_localBase[8] + iVar25) = (int)*(short *)(*piVar20 + 0x30);
            iVar27 = iVar25 + 0x1c;
            iVar25 = iVar25 + 0x20;
            iVar26 = iVar26 + 8;
            *(int *)(object->m_localBase[8] + iVar39) = (int)*(short *)(piVar20[1] + 0x30);
            *(int *)(object->m_localBase[8] + iVar38) = (int)*(short *)(piVar20[2] + 0x30);
            *(int *)(object->m_localBase[8] + iVar37) = (int)*(short *)(piVar20[3] + 0x30);
            *(int *)(object->m_localBase[8] + iVar35) = (int)*(short *)(piVar20[4] + 0x30);
            *(int *)(object->m_localBase[8] + iVar36) = (int)*(short *)(piVar20[5] + 0x30);
            *(int *)(object->m_localBase[8] + iVar34) = (int)*(short *)(piVar20[6] + 0x30);
            piVar1 = piVar20 + 7;
            piVar20 = piVar20 + 8;
            *(int *)(object->m_localBase[8] + iVar27) = (int)*(short *)(*piVar1 + 0x30);
            uVar9 = uVar9 - 1;
          } while (uVar9 != 0);
        }
      }
      iVar25 = iVar26 * 4;
      iVar27 = iVar8 - iVar26;
      piVar20 = local_ba0 + iVar26;
      if (iVar26 < iVar8) {
        do {
          iVar26 = *piVar20;
          piVar20 = piVar20 + 1;
          *(int *)(object->m_localBase[8] + iVar25) = (int)*(short *)(iVar26 + 0x30);
          iVar25 = iVar25 + 4;
          iVar27 = iVar27 + -1;
        } while (iVar27 != 0);
      }
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,iVar8);
    *param_5 = 0;
    break;
  case -0xcf:
    ClearEvtWork__12CCaravanWorkFv(Game.game.m_caravanWorkArr + *object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xce:
    ClearEvtWork__Q25CGame9CGameWorkFv((CGame *)&Game.game.m_gameWork);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xcd:
    ClearParmanent__12CFlatRuntimeFv((CFlatRuntime2 *)&CFlat);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xcc:
    LoadExtraFont__8CMenuPcsFiPc
              (&MenuPcs,*object->m_localBase,
               (flatRuntime2->flatRuntimeBase).m_strBlob +
               (flatRuntime2->flatRuntimeBase).m_strOffs[object->m_localBase[1]]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xcb:
    SetShadowAuto__10CCameraPcsFi(&CameraPcs,*object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xca:
    puVar24 = object->m_localBase;
    __ct__7CVectorFfff((float)puVar24[1],(float)puVar24[2],(float)puVar24[3],&CStack_ce4);
    uVar7 = __opP3Vec__7CVectorFv();
    uVar7 = PlaySe3D__6CSoundFiP3Vecffi
                      ((double)(float)puVar24[4],(double)(float)puVar24[5],&Sound,
                       *object->m_localBase,uVar7,puVar24[6]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,uVar7);
    *param_5 = 0;
    break;
  case -0xc9:
    uVar7 = GetMapObjIdx__7CMapMngFUs(&MapMng,(short)*object->m_localBase);
    puVar24 = object->m_localBase;
    SetMapObjTransRate__7CMapMngFifff
              ((float)puVar24[1],(float)puVar24[2],(float)puVar24[3],&MapMng,uVar7);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -200:
    uVar9 = GetNumMes__9CFlatDataFv((CFlatData *)&System);
    if (2 < uVar9) {
      Printf__7CSystemFPce(&System,&DAT_801da688);
    }
    CancelLoadWaveASync__6CSoundFv(&Sound);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -199:
    puVar24 = object->m_localBase;
    MenuPcs._76_4_ = *puVar24;
    MenuPcs._80_4_ = puVar24[1];
    MenuPcs._84_4_ = puVar24[2];
    if ((int)puVar24[3] < (int)MenuPcs._104_4_) {
      MenuPcs._92_4_ = 0x10;
    }
    MenuPcs._104_4_ = puVar24[3];
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xc6:
    puVar24 = object->m_localBase;
    MenuPcs._72_4_ = *puVar24;
    MenuPcs._88_4_ = 0x40;
    MenuPcs._96_4_ = puVar24[1];
    MenuPcs._100_4_ = puVar24[2];
    MenuPcs._104_4_ = MenuPcs._100_4_;
    MenuPcs._108_4_ = MenuPcs._100_4_;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xc5:
    puVar24 = object->m_localBase;
    __ct__7CVectorFfff((float)puVar24[4],(float)puVar24[5],(float)puVar24[6],&CStack_cd8);
    puVar19 = (undefined4 *)__opR3Vec__7CVectorFv();
    local_ccc = *puVar19;
    local_cc8 = puVar19[1];
    local_cc4 = puVar19[2];
    puVar24 = object->m_localBase;
    __ct__6CColorFUcUcUcUc(auStack_d74,puVar24[1] & 0xff,puVar24[2] & 0xff,puVar24[3] & 0xff,0xff);
    local_d70 = __op8_GXColor__6CColorFv();
    SetMapObjWorldMapLightID__7CMapMngFi8_GXColor3Vec
              (&MapMng,(short)*object->m_localBase,&local_d70,&local_ccc);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xc4:
    GXSetDispCopyGamma(*object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xc3:
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti
              (flatRuntime2,object,
               (uint)Game.game.m_caravanWorkArr[*object->m_localBase].m_progressValue);
    *param_5 = 0;
    break;
  case -0xc2:
    Game.game.m_caravanWorkArr[*object->m_localBase].m_progressValue =
         (uint16_t)object->m_localBase[1];
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xc1:
    uVar7 = GetFoodRank__12CCaravanWorkFi
                      (Game.game.m_caravanWorkArr + *object->m_localBase,object->m_localBase[1]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,uVar7);
    *param_5 = 0;
    break;
  case -0xc0:
    pfVar28 = (float *)object->m_localBase;
    __ct__7CVectorFfff(*pfVar28,pfVar28[1],pfVar28[2],&CStack_cc0);
    pVVar12 = (Vec *)__opP3Vec__7CVectorFv();
    SetTexShadowPos__9CCharaPcsFP3Vec(&CharaPcs,pVVar12);
    puVar24 = object->m_localBase;
    __ct__6CColorFUcUcUcUc
              (auStack_d6c,puVar24[3] & 0xff,puVar24[4] & 0xff,puVar24[5] & 0xff,puVar24[6] & 0xff);
    local_d68 = __op8_GXColor__6CColorFv();
    SetTexShadowColor__9CCharaPcsF8_GXColor(&CharaPcs,&local_d68);
    SetTexShadowRadius__9CCharaPcsFf((float)object->m_localBase[7],&CharaPcs);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xbf:
    puVar24 = object->m_localBase;
    if (puVar24[2] == 0) {
      ShowMapObjID__7CMapMngFii(&MapMng,*puVar24,puVar24[1]);
    }
    else {
      ShowMapObjChildID__7CMapMngFii(&MapMng,*puVar24,puVar24[1]);
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xbe:
    SearchRomLetterWork__12CCaravanWorkFPP14CRomLetterWorki
              (Game.game.m_caravanWorkArr + *object->m_localBase,local_a30,8);
    pCVar18 = local_a30;
    iVar26 = 0;
    iVar8 = 0;
    do {
      iVar25 = 0;
      iVar27 = 0;
      iVar34 = 3;
      do {
        if (*pCVar18 == (CRomLetterWork)0x0) {
          *(undefined4 *)(iVar8 + *(int *)((int)object->m_localBase + iVar27 + 4)) = 0xffffffff;
        }
        else {
          *(uint *)(iVar8 + *(int *)((int)object->m_localBase + iVar27 + 4)) =
               (uint)*(ushort *)((int)*pCVar18 + iVar25);
        }
        if (*pCVar18 == (CRomLetterWork)0x0) {
          *(undefined4 *)(iVar8 + *(int *)((int)object->m_localBase + iVar27 + 8)) = 0xffffffff;
        }
        else {
          *(uint *)(iVar8 + *(int *)((int)object->m_localBase + iVar27 + 8)) =
               (uint)*(ushort *)((int)*pCVar18 + iVar25 + 2);
        }
        if (*pCVar18 == (CRomLetterWork)0x0) {
          *(undefined4 *)(iVar8 + *(int *)((int)object->m_localBase + iVar27 + 0xc)) = 0xffffffff;
        }
        else {
          *(uint *)(iVar8 + *(int *)((int)object->m_localBase + iVar27 + 0xc)) =
               (uint)*(ushort *)((int)*pCVar18 + iVar25 + 4);
        }
        if (*pCVar18 == (CRomLetterWork)0x0) {
          *(undefined4 *)(iVar8 + *(int *)((int)object->m_localBase + iVar27 + 0x10)) = 0xffffffff;
        }
        else {
          *(uint *)(iVar8 + *(int *)((int)object->m_localBase + iVar27 + 0x10)) =
               (uint)*(ushort *)((int)*pCVar18 + iVar25 + 6);
        }
        iVar25 = iVar25 + 8;
        iVar27 = iVar27 + 0x10;
        iVar34 = iVar34 + -1;
      } while (iVar34 != 0);
      if (*pCVar18 == (CRomLetterWork)0x0) {
        *(undefined4 *)(object->m_localBase[0xd] + iVar8) = 0xffffffff;
      }
      else {
        iVar25 = (int)*pCVar18 - Game.game.unkCFlatData0[3];
        iVar25 = iVar25 / 0x3e + (iVar25 >> 0x1f);
        *(int *)(object->m_localBase[0xd] + iVar8) = iVar25 - (iVar25 >> 0x1f);
      }
      iVar26 = iVar26 + 1;
      iVar8 = iVar8 + 4;
      pCVar18 = pCVar18 + 1;
    } while (iVar26 < 8);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xbd:
    pppFieldEndFpNo__8CPartMngFs(&PartMng,(short)*object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xbc:
    pppFieldEndFpNo__8CPartMngFs(&PartMng,(short)*object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xbb:
    __ct__14PPPCREATEPARAMFv(&PStack_8f0);
    pppCreate__8CPartMngFiiP14PPPCREATEPARAMi(&PartMng,0,*object->m_localBase,&PStack_8f0,1);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xba:
    flatRuntime2->field61766_0x10414 = *object->m_localBase;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xb9:
    CharaPcs._36_4_ = *object->m_localBase;
    CharaPcs._40_4_ = object->m_localBase[1];
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xb8:
    puVar24 = object->m_localBase;
    __ct__7CVectorFfff((float)puVar24[1],(float)puVar24[2],(float)puVar24[3],&CStack_cb4);
    pVVar12 = (Vec *)__opP3Vec__7CVectorFv();
    ChangeSe3DPos__6CSoundFiP3Vec(&Sound,*object->m_localBase,pVVar12);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xb7:
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti
              (flatRuntime2,object,Game.game.m_caravanWorkArr[*object->m_localBase].unk_0x3ac);
    *param_5 = 0;
    break;
  case -0xb6:
    Game.game.m_caravanWorkArr[*object->m_localBase].unk_0x3ac = object->m_localBase[1];
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xb5:
    iVar8 = (int)(FLOAT_80330b60 * (float)object->m_localBase[1]);
    local_78 = (double)(longlong)iVar8;
    pppSetDeltaIdx__8CPartMngFsl(&PartMng,(short)*object->m_localBase,iVar8);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xb4:
    iVar8 = (int)(FLOAT_80330b60 * (float)object->m_localBase[1]);
    local_78 = (double)(longlong)iVar8;
    pppSetDeltaSlot__8CPartMngFil(&PartMng,*object->m_localBase,iVar8);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xb3:
    uVar7 = DeleteOld__9CGItemObjFiiPQ212CFlatRuntime7CObjectPQ212CFlatRuntime7CObject
                      (*object->m_localBase,object->m_localBase[1],object,object->m_engineObject);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,uVar7);
    *param_5 = 0;
    break;
  case -0xb2:
    GraphicsPcs._64_4_ = 0;
    GraphicsPcs._48_4_ = 1;
    GraphicsPcs._52_4_ = 1;
    puVar24 = object->m_localBase;
    GraphicsPcs._68_4_ = *puVar24;
    GraphicsPcs._56_1_ = (undefined)puVar24[1];
    GraphicsPcs._57_1_ = (undefined)puVar24[2];
    GraphicsPcs._58_1_ = (undefined)puVar24[3];
    GraphicsPcs._59_1_ = (undefined)puVar24[4];
    GraphicsPcs._60_1_ = (undefined)puVar24[5];
    GraphicsPcs._61_1_ = (undefined)puVar24[6];
    GraphicsPcs._62_1_ = (undefined)puVar24[7];
    GraphicsPcs._63_1_ = (undefined)puVar24[8];
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xb1:
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti
              (flatRuntime2,object,(int)Game.game.m_gameWork.m_townName[*object->m_localBase]);
    *param_5 = 0;
    break;
  case -0xb0:
    strcpy(0x8021ff68,
           (flatRuntime2->flatRuntimeBase).m_strBlob +
           (flatRuntime2->flatRuntimeBase).m_strOffs[*object->m_localBase]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xaf:
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti
              (flatRuntime2,object,
               (int)(char)Game.game.m_caravanWorkArr[*object->m_localBase].unk_0x3ca_0x3dd
                          [object->m_localBase[1]]);
    *param_5 = 0;
    break;
  case -0xae:
    strcpy(*object->m_localBase * 0xc30 + -0x7fddf986,
           (flatRuntime2->flatRuntimeBase).m_strBlob +
           (flatRuntime2->flatRuntimeBase).m_strOffs[object->m_localBase[1]]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xad:
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti
              (flatRuntime2,object,Game.game.m_caravanWorkArr[*object->m_localBase].unk_0x3a8);
    *param_5 = 0;
    break;
  case -0xac:
    Game.game.m_caravanWorkArr[*object->m_localBase].unk_0x3a8 = object->m_localBase[1];
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xab:
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti
              (flatRuntime2,object,
               (uint)Game.game.m_caravanWorkArr[*object->m_localBase].m_letterMeta
                     [object->m_localBase[1]]);
    *param_5 = 0;
    break;
  case -0xaa:
    puVar24 = object->m_localBase;
    Game.game.m_caravanWorkArr[*puVar24].m_letterMeta[puVar24[1]] = (uint16_t)puVar24[2];
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xa9:
    SetWorldParam__8CMenuPcsFii(&MenuPcs,*object->m_localBase,object->m_localBase[1]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xa8:
    uVar7 = GetWorldParam__8CMenuPcsFi(&MenuPcs,*object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,uVar7);
    *param_5 = 0;
    break;
  case -0xa7:
    puVar24 = object->m_localBase;
    SetEvtWord__12CCaravanWorkFis
              (Game.game.m_caravanWorkArr + *puVar24,puVar24[1],(short)puVar24[2]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xa6:
    sVar23 = GetEvtWord__12CCaravanWorkFi
                       (Game.game.m_caravanWorkArr + *object->m_localBase,object->m_localBase[1]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,(int)sVar23);
    *param_5 = 0;
    break;
  case -0xa5:
    puVar24 = object->m_localBase;
    SetEvtFlag__12CCaravanWorkFii(Game.game.m_caravanWorkArr + *puVar24,puVar24[1],puVar24[2]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xa4:
    uVar7 = GetEvtFlag__12CCaravanWorkFi
                      (Game.game.m_caravanWorkArr + *object->m_localBase,object->m_localBase[1]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,uVar7);
    *param_5 = 0;
    break;
  case -0xa3:
    SetFirstZone__7CGbaPcsFv(&GbaPcs);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xa2:
    uVar9 = OSGetTick();
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti
              (flatRuntime2,object,uVar9 / (DAT_800000f8 / 4000));
    *param_5 = 0;
    break;
  case -0xa1:
    DispAllFieldItem__9CGItemObjFi(*object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0xa0:
    uVar9 = GetNumMes__9CFlatDataFv((CFlatData *)&System);
    if (2 < uVar9) {
      Printf__7CSystemFPce(&System,&DAT_801da5b0);
    }
    SetStreamVolume__6CSoundFii(&Sound,*object->m_localBase,object->m_localBase[1]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x9f:
    puVar24 = object->m_localBase;
    uVar46 = puVar24[1];
    if ((int)uVar46 < 0) {
      Game.game.m_caravanWorkArr[*puVar24].m_shopState = 0;
    }
    else {
      Init__12CCaravanWorkFiP8CRomWorki
                (*puVar24 * 0xc30 + -0x7fddfd50,uVar46,Game.game.unkCFlatData0[0] + uVar46 * 0x1d0,
                 puVar24[2]);
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x9e:
    uVar7 = DummySave__14CMemoryCardManFv(&MemoryCardMan);
    uVar9 = countLeadingZeros(uVar7);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,uVar9 >> 5 & 0xff);
    *param_5 = 0;
    break;
  case -0x9d:
    uVar7 = DummyLoad__14CMemoryCardManFv(&MemoryCardMan);
    uVar9 = countLeadingZeros(uVar7);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,uVar9 >> 5 & 0xff);
    *param_5 = 0;
    break;
  case -0x9c:
    uVar46 = object->m_localBase[1];
    iVar8 = *object->m_localBase * 4;
    piVar20 = (int *)(&CharaPcs.field_0x14 + iVar8);
    if (((*piVar20 == 0) || ((int)uVar46 < 0)) ||
       (*(int *)(&CharaPcs.field_0x4 + iVar8) <= (int)uVar46)) {
      push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
      *param_5 = 0;
    }
    fVar2 = FLOAT_80330b54;
    iVar8 = uVar46 * 0x20;
    *(undefined4 *)object->m_localBase[2] = *(undefined4 *)(*piVar20 + iVar8);
    fVar4 = FLOAT_80330b64;
    *(float *)object->m_localBase[3] = -*(float *)(*piVar20 + iVar8 + 4);
    *(float *)object->m_localBase[4] = -*(float *)(*piVar20 + iVar8 + 8);
    *(undefined4 *)object->m_localBase[5] = *(undefined4 *)(*piVar20 + iVar8 + 0xc);
    *(float *)object->m_localBase[6] = -*(float *)(*piVar20 + iVar8 + 0x10);
    *(float *)object->m_localBase[7] = -*(float *)(*piVar20 + iVar8 + 0x14);
    *(undefined4 *)object->m_localBase[8] = *(undefined4 *)(*piVar20 + iVar8 + 0x18);
    *(float *)object->m_localBase[9] = -((fVar2 * *(float *)(*piVar20 + iVar8 + 0x1c)) / fVar4);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,1);
    *param_5 = 0;
    break;
  case -0x9b:
    LoadCam__9CCharaPcsFiPc
              (&CharaPcs,*object->m_localBase,
               (flatRuntime2->flatRuntimeBase).m_strBlob +
               (flatRuntime2->flatRuntimeBase).m_strOffs[object->m_localBase[1]]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x9a:
    uVar7 = GetMapObjIdx__7CMapMngFUs(&MapMng,(short)*object->m_localBase);
    puVar24 = object->m_localBase;
    SetMapObjMime__7CMapMngFiiii(&MapMng,uVar7,puVar24[1],puVar24[2],puVar24[3]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x99:
    uVar7 = GetMapObjIdx__7CMapMngFUs(&MapMng,(short)*object->m_localBase);
    puVar24 = object->m_localBase;
    SetMapObjAnim__7CMapMngFiiii(&MapMng,uVar7,puVar24[1],puVar24[2],(char)puVar24[3]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x98:
    (&flatRuntime2->field_0x134d)[*object->m_localBase * 0x14] = (char)object->m_localBase[1];
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x97:
    uVar46 = *object->m_localBase;
    (&flatRuntime2->field_0x134c)[uVar46 * 0x14] = (char)object->m_localBase[1];
    *(uint32_t *)(&flatRuntime2->field_0x1350 + uVar46 * 0x14) = object->m_localBase[2];
    *(uint32_t *)(&flatRuntime2->field_0x1354 + uVar46 * 0x14) = object->m_localBase[3];
    *(uint32_t *)(&flatRuntime2->field_0x1358 + uVar46 * 0x14) = object->m_localBase[4];
    *(uint32_t *)(&flatRuntime2->field_0x135c + uVar46 * 0x14) = object->m_localBase[5];
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x96:
    *(uint32_t *)&flatRuntime2->field_0x12ac = *object->m_localBase;
    *(uint32_t *)&flatRuntime2->field_0x12b0 = object->m_localBase[1];
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x95:
    puVar24 = object->m_localBase;
    uVar9 = 1;
    switch(*puVar24) {
    case 0:
      Realloc__6CSoundFi(&Sound,1);
      break;
    case 1:
      ChangeMap__5CGameFiiii(&Game.game,puVar24[1],puVar24[2],1,0);
      break;
    case 2:
      pppDestroyAll__8CPartMngFv(&PartMng);
      ChangeMap__5CGameFiiii(&Game.game,object->m_localBase[1],object->m_localBase[2],1,1);
      break;
    case 3:
      Realloc__6CSoundFi(&Sound,0);
      break;
    case 4:
      ChangeMap__5CGameFiiii(&Game.game,puVar24[1],puVar24[2],2,0);
      break;
    case 5:
      pppDestroyAll__8CPartMngFv(&PartMng);
      ChangeMap__5CGameFiiii(&Game.game,object->m_localBase[1],object->m_localBase[2],2,1);
      break;
    case 6:
      uVar9 = IsLoadMapCompleted__7CMapPcsFv(&MapPcs);
      uVar31 = IsLoadPartCompleted__8CPartPcsFv(&PartPcs);
      uVar9 = uVar9 & uVar31;
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,uVar9);
    *param_5 = 0;
    break;
  case -0x94:
    pfVar28 = (float *)object->m_localBase;
    PartMng.m_pppEnvSt.m_boxMinX = *pfVar28;
    PartMng.m_pppEnvSt.m_boxMaxX = pfVar28[1];
    PartMng.m_pppEnvSt.m_boxMinY = pfVar28[2];
    PartMng.m_pppEnvSt.m_boxMaxY = pfVar28[3];
    PartMng.m_pppEnvSt.m_boxMinZ = pfVar28[4];
    PartMng.m_pppEnvSt.m_boxMaxZ = pfVar28[5];
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x93:
    uVar9 = GetNumMes__9CFlatDataFv((CFlatData *)&System);
    if (2 < uVar9) {
      Printf__7CSystemFPce(&System,&DAT_801da71c,*object->m_localBase);
    }
    AddNoFreeWave__6CSoundFi(&Sound,(short)*object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x92:
    SetMapTexAnim__7CMapMngFiiii(&MapMng);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x91:
    uVar7 = pppGetNumFreePppMngSt__8CPartMngFv(&PartMng);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,uVar7);
    *param_5 = 0;
    break;
  case -0x90:
    uVar9 = GetNumMes__9CFlatDataFv((CFlatData *)&System);
    if (2 < uVar9) {
      Printf__7CSystemFPce(&System,&DAT_801da654,*object->m_localBase);
    }
    PlayNextBgm__6CSoundFi(&Sound,*object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x8f:
    FadeOutSe3D__6CSoundFii(&Sound,*object->m_localBase,object->m_localBase[1]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x8e:
    uVar9 = GetNumMes__9CFlatDataFv((CFlatData *)&System);
    if (2 < uVar9) {
      Printf__7CSystemFPce(&System,&DAT_801da62c);
    }
    FadeOutBgm__6CSoundFi(&Sound,*object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x8d:
    uVar9 = GetNumMes__9CFlatDataFv((CFlatData *)&System);
    if (2 < uVar9) {
      Printf__7CSystemFPce(&System,&DAT_801da604);
    }
    StopBgm__6CSoundFv(&Sound);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x8c:
    uVar9 = GetNumMes__9CFlatDataFv((CFlatData *)&System);
    if (2 < uVar9) {
      Printf__7CSystemFPce(&System,&DAT_801da5dc,*object->m_localBase);
    }
    FreeWave__6CSoundFi(&Sound,*object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x8b:
    StopStream__6CSoundFv(&Sound);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x8a:
    uVar9 = GetNumMes__9CFlatDataFv((CFlatData *)&System);
    if (2 < uVar9) {
      Printf__7CSystemFPce(&System,&DAT_801da588);
    }
    PlayStreamASync__6CSoundFv(&Sound);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x89:
    uVar9 = GetNumMes__9CFlatDataFv((CFlatData *)&System);
    if (2 < uVar9) {
      Printf__7CSystemFPce(&System,&DAT_801da55c,*object->m_localBase);
    }
    LoadStream__6CSoundFi(&Sound,*object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x88:
    ChangePower__5CWindFif((double)(float)object->m_localBase[1],&Wind,*object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x87:
    pfVar28 = (float *)object->m_localBase;
    __ct__7CVectorFfff(*pfVar28,pfVar28[1],pfVar28[2],&CStack_ca8);
    uVar7 = __opP3Vec__7CVectorFv();
    uVar7 = AddSphere__5CWindFPC3Vecffi
                      ((double)pfVar28[3],(double)pfVar28[4],&Wind,uVar7,pfVar28[5]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,uVar7);
    *param_5 = 0;
    break;
  case -0x86:
    pfVar28 = (float *)object->m_localBase;
    __ct__7CVectorFfff(*pfVar28,pfVar28[1],pfVar28[2],&CStack_c9c);
    uVar7 = __opP3Vec__7CVectorFv();
    uVar7 = AddDiffuse__5CWindFPC3Vecfff
                      ((double)pfVar28[3],(double)pfVar28[4],(double)pfVar28[5],&Wind,uVar7);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,uVar7);
    *param_5 = 0;
    break;
  case -0x85:
    uVar7 = AddAmbient__5CWindFff
                      ((double)(float)*object->m_localBase,(double)(float)object->m_localBase[1],
                       &Wind);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,uVar7);
    *param_5 = 0;
    break;
  case -0x84:
    ChangeProgressive__8CGraphicFi(&Graphic,*object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x83:
    uVar7 = GetProgressive__8CGraphicFv(&Graphic);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,uVar7);
    *param_5 = 0;
    break;
  case -0x82:
    *(uint32_t *)&flatRuntime2->field_0x10408 = *object->m_localBase;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x81:
    dVar49 = (double)cosf__3stdFf((double)(float)object->m_localBase[2]);
    dVar50 = (double)sinf__3stdFf((double)(float)object->m_localBase[2]);
    __ct__7CVectorFfff((float)dVar50,FLOAT_80330b30,(float)dVar49,&local_b90);
    pVVar12 = (Vec *)__opP3Vec__7CVectorFv(&local_b90);
    __ct__7CVectorFfff((float)*object->m_localBase,FLOAT_80330b30,(float)object->m_localBase[1],
                       &CStack_c90);
    p = (Vec *)__opP3Vec__7CVectorFv();
    PSMTXReflect((Mtx *)&flatRuntime2->field_0x12b4,p,pVVar12);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x80:
    puVar24 = object->m_localBase;
    SetParticleWorkSe__13CFlatRuntime2Fiii(flatRuntime2,*puVar24,(char)puVar24[1],puVar24[2]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x7f:
    SetReverb__6CSoundFii(&Sound,*object->m_localBase,object->m_localBase[1]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x7e:
    pppDeleteSlot__8CPartMngFii(&PartMng,*object->m_localBase,0);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x7d:
    pppDeletePart__8CPartMngFi(&PartMng,*object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x7c:
    StopSe3D__6CSoundFi(&Sound,*object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x7b:
    puVar24 = object->m_localBase;
    uVar7 = PlaySe3DLine__6CSoundFiiffi
                      ((double)(float)puVar24[2],(double)(float)puVar24[3],&Sound,*puVar24,
                       (char)puVar24[1],0);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,uVar7);
    *param_5 = 0;
    break;
  case -0x7a:
    puVar24 = object->m_localBase;
    __ct__7CVectorFfff((float)puVar24[1],(float)puVar24[2],(float)puVar24[3],&CStack_c84);
    uVar7 = __opP3Vec__7CVectorFv();
    uVar7 = PlaySe3D__6CSoundFiP3Vecffi
                      ((double)(float)puVar24[4],(double)(float)puVar24[5],&Sound,
                       *object->m_localBase,uVar7,0);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,uVar7);
    *param_5 = 0;
    break;
  case -0x79:
    puVar24 = object->m_localBase;
    __ct__7CVectorFfff((float)puVar24[1],(float)puVar24[2],(float)puVar24[3],&CStack_c78);
    pVVar12 = (Vec *)__opP3Vec__7CVectorFv();
    Add3DLine__6CSoundFiP3Vec(&Sound,*object->m_localBase,pVVar12);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x78:
    Clear3DLine__6CSoundFi(&Sound,*object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x77:
    uVar9 = GetNumMes__9CFlatDataFv((CFlatData *)&System);
    if (2 < uVar9) {
      Printf__7CSystemFPce(&System,&DAT_801da534,*object->m_localBase);
    }
    LoadWave__6CSoundFi(&Sound,*object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x76:
    (flatRuntime2->flatRuntimeBase).m_unk0x1298 = *object->m_localBase;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x75:
    SetTempValue__4CMesFii(*object->m_localBase,object->m_localBase[1]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x74:
    uVar22 = GetGbaButtonDown__4CPadFl(&Pad,*object->m_localBase);
    uVar9 = GetDbgFlag__11CDbgMenuPcsFv(0x80306708);
    if ((uVar9 & 0x100) != 0) {
      uVar22 = uVar22 & 0xf3ff;
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,(int)(short)uVar22);
    *param_5 = 0;
    break;
  case -0x73:
    Game.game.m_gameWork.m_unkStageTable[*object->m_localBase] = object->m_localBase[1];
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x72:
    Game.game.m_gameWork.m_bossArtifactStageTable[*object->m_localBase] = object->m_localBase[1];
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x71:
    Game.game.m_gameWork.m_scriptGlobalTime = *object->m_localBase;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x70:
    Game.game.m_gameWork.m_timerA = *object->m_localBase;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x6f:
    Game.game.m_gameWork._8_4_ = *object->m_localBase;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x6e:
    puVar24 = object->m_localBase;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti
              (flatRuntime2,object,
               (uint)Game.game.m_gameWork.m_linkTable[*puVar24][puVar24[1]][puVar24[2]][puVar24[3]])
    ;
    *param_5 = 0;
    break;
  case -0x6d:
    puVar24 = object->m_localBase;
    uVar41 = puVar24[2];
    uVar43 = puVar24[3];
    uVar48 = *puVar24;
    uVar33 = puVar24[1];
    uVar46 = puVar24[4];
    Game.game.m_gameWork.m_linkTable[uVar41][uVar43][uVar48][uVar33] = (uint8_t)uVar46;
    Game.game.m_gameWork.m_linkTable[uVar48][uVar33][uVar41][uVar43] = (uint8_t)uVar46;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x6c:
    uVar7 = PlaySe__6CSoundFiiii(&Sound,*object->m_localBase,0x40,0x7f,0);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,uVar7);
    *param_5 = 0;
    break;
  case -0x6b:
    LoadSe__6CSoundFi(&Sound,*object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x6a:
    uVar9 = GetNumMes__9CFlatDataFv((CFlatData *)&System);
    if (2 < uVar9) {
      Printf__7CSystemFPce(&System,&DAT_801da504,*object->m_localBase);
    }
    PlayBgm__6CSoundFi(&Sound,*object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x69:
    uVar9 = GetNumMes__9CFlatDataFv((CFlatData *)&System);
    if (2 < uVar9) {
      Printf__7CSystemFPce(&System,&DAT_801da4dc,*object->m_localBase);
    }
    LoadBgm__6CSoundFi(&Sound,*object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x68:
    iVar8 = IsLoadWaveASyncCompleted__6CSoundFv(&Sound);
    uVar9 = GetNumMes__9CFlatDataFv((CFlatData *)&System);
    if (2 < uVar9) {
      puVar13 = &DAT_80330b80;
      if (iVar8 != 0) {
        puVar13 = &DAT_80330b78;
      }
      Printf__7CSystemFPce(&System,&DAT_801da498,puVar13);
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,iVar8);
    *param_5 = 0;
    break;
  case -0x67:
    uVar9 = GetNumMes__9CFlatDataFv((CFlatData *)&System);
    if (2 < uVar9) {
      Printf__7CSystemFPce(&System,&DAT_801da468,*object->m_localBase);
    }
    LoadWaveASync__6CSoundFiii(&Sound,*object->m_localBase,0xffffffff,0);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x66:
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,2);
    *param_5 = 0;
    break;
  case -0x65:
    puVar24 = object->m_localBase;
    uVar7 = __ct__6CColorFUcUcUcUc
                      (auStack_d64,puVar24[1] & 0xff,puVar24[2] & 0xff,puVar24[3] & 0xff,0xff);
    SetMapShadeColor__9CCharaPcsFi6CColor(&CharaPcs,*object->m_localBase,uVar7);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -100:
    initAllFinished__13CFlatRuntime2Fv();
    flatRuntime2->field61759_0x10404 = 1;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -99:
    uVar7 = (**(code **)((int)(flatRuntime2->flatRuntimeBase).vtable + 0x3c))
                      (flatRuntime2,*object->m_localBase);
    SetParticleWorkTrace__13CFlatRuntime2FPQ212CFlatRuntime7CObject(flatRuntime2,uVar7);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x62:
    SetNoFreeMergeMask__9CCharaPcsFi(&CharaPcs,*object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x61:
    uVar46 = object->m_localBase[1];
    SetDefaultGroup__7CMemoryFi(&Memory,(int)~(uVar46 - 1 | 1 - uVar46) >> 0x1f & 3);
    LoadMergeFile__9CCharaPcsFiii(&CharaPcs,*object->m_localBase,uVar46,0);
    ResetDefaultGroup__7CMemoryFv(&Memory);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x60:
    puVar24 = object->m_localBase;
    uVar9 = countLeadingZeros(puVar24[4]);
    uVar31 = countLeadingZeros(puVar24[5]);
    local_78 = (double)(longlong)(int)(FLOAT_80330b74 * (float)puVar24[3]);
    SetBlurParameter__11CGraphicPcsFiUcUcUcUcUcs
              (&GraphicsPcs,*puVar24,puVar24[1] & 0xff,puVar24[2] & 0xff,
               (int)(FLOAT_80330b74 * (float)puVar24[3]) & 0xff,uVar9 >> 5 & 0xff,uVar31 >> 5 & 0xff
               ,(int)(short)puVar24[6]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x5f:
    dVar49 = (double)DstRot__5CMathFff((double)(float)*object->m_localBase,
                                       (double)(float)object->m_localBase[1],&Math);
    local_d44 = (float)dVar49;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,local_d44);
    *param_5 = 0;
    break;
  case -0x5e:
    iVar8 = GetNumMes__9CFlatDataFv((CFlatData *)&System);
    if (iVar8 != 0) {
      Printf__7CSystemFPce(&System,&DAT_801da434);
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x5d:
    uVar7 = IsGdev__7CSystemFv(&System);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,uVar7);
    *param_5 = 0;
    break;
  case -0x5c:
    object_00 = (CObject *)
                (**(code **)((int)(flatRuntime2->flatRuntimeBase).vtable + 0x3c))
                          (flatRuntime2,object->m_localBase[1]);
    IgnoreParticle__13CFlatRuntime2FiPQ212CFlatRuntime7CObject
              (flatRuntime2,(short)*object->m_localBase,object_00);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x5b:
    uVar7 = (**(code **)((int)(flatRuntime2->flatRuntimeBase).vtable + 0x3c))
                      (flatRuntime2,object->m_localBase[1]);
    SetParticleWorkParam__13CFlatRuntime2FiPQ212CFlatRuntime7CObject
              (flatRuntime2,*object->m_localBase,uVar7);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x5a:
    *(undefined4 *)&flatRuntime2->field_0x10400 = 0;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x59:
    sprintf(CStack_884.m_name + 0xfc,s_cflat_d_80330b6c,*object->m_localBase);
    DebugReadWrite__14CMemoryCardManFiPcPvi
              (&MemoryCardMan,0,CStack_884.m_name + 0xfc,&flatRuntime2->field_0xe400,0x2000);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x58:
    sprintf(acStack_684,s_cflat_d_80330b6c,*object->m_localBase);
    DebugReadWrite__14CMemoryCardManFiPcPvi
              (&MemoryCardMan,1,acStack_684,&flatRuntime2->field_0xe400,0x2000);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x57:
    iVar8 = *(int *)&flatRuntime2->field_0x10400;
    local_d40 = *object->m_localBase;
    *(int *)&flatRuntime2->field_0x10400 = iVar8 + 1;
    *(uint32_t *)(&flatRuntime2->field_0xe400 + iVar8 * 4) = local_d40;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x56:
    iVar8 = *(int *)&flatRuntime2->field_0x10400;
    uVar46 = *object->m_localBase;
    *(int *)&flatRuntime2->field_0x10400 = iVar8 + 1;
    *(uint32_t *)(&flatRuntime2->field_0xe400 + iVar8 * 4) = uVar46;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x55:
    iVar8 = *(int *)&flatRuntime2->field_0x10400;
    *(int *)&flatRuntime2->field_0x10400 = iVar8 + 1;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti
              (flatRuntime2,object,*(undefined4 *)(&flatRuntime2->field_0xe400 + iVar8 * 4));
    *param_5 = 0;
    break;
  case -0x54:
    iVar8 = *(int *)&flatRuntime2->field_0x10400;
    *(int *)&flatRuntime2->field_0x10400 = iVar8 + 1;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti
              (flatRuntime2,object,*(undefined4 *)(&flatRuntime2->field_0xe400 + iVar8 * 4));
    *param_5 = 0;
    break;
  case -0x53:
    SetCharaAllocStage__9CCharaPcsFi(&CharaPcs,*object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x52:
    uVar9 = *object->m_localBase;
    SetUseDOF__11CGraphicPcsFi(&GraphicsPcs,(-uVar9 | uVar9) >> 0x1f);
    puVar24 = object->m_localBase;
    SetDOFParameter__11CGraphicPcsFScScfffffi
              ((double)(float)puVar24[2],(double)(float)puVar24[3],(double)(float)puVar24[4],
               (double)(float)puVar24[5],(double)(float)puVar24[6],&GraphicsPcs,
               (int)(char)((char)uVar9 + -1),(int)(char)puVar24[1],puVar24[7]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x51:
    pcVar42 = GetLangString__5CGameFv(&Game.game);
    sprintf(auStack_584,s_dvd__scft__s_cfd_801da420,pcVar42,
            (flatRuntime2->flatRuntimeBase).m_strBlob +
            (flatRuntime2->flatRuntimeBase).m_strOffs[*object->m_localBase]);
    fileHandle = (CFileCHandle *)Open__5CFileFPcUlQ25CFile3PRI(&File,auStack_584,0,0);
    if (fileHandle != (CFileCHandle *)0x0) {
      Read__Q25CFile7CHandleFv(fileHandle);
      SyncCompleted__Q25CFile7CHandleFv(fileHandle);
      pvVar17 = GetBuffer__5CFileFv(&File);
      Create__9CFlatDataFPv((CFlatData *)&flatRuntime2->field_0xcf20,pvVar17);
      Close__Q25CFile7CHandleFv(fileHandle);
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x50:
    GraphicsPcs._24_4_ = 2;
    GraphicsPcs._12_1_ = 0xff;
    GraphicsPcs._13_1_ = 0xff;
    GraphicsPcs._14_1_ = 0xff;
    GraphicsPcs._15_1_ = 0xff;
    GraphicsPcs._20_4_ = 0;
    puVar24 = object->m_localBase;
    GraphicsPcs._4_4_ = *puVar24;
    GraphicsPcs._44_4_ = puVar24[1];
    GraphicsPcs._36_4_ = puVar24[2];
    GraphicsPcs._40_4_ = puVar24[3];
    GraphicsPcs._8_4_ = GraphicsPcs._4_4_;
    ReqScreenCapture__11CGraphicPcsFv();
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x4f:
    puVar24 = object->m_localBase;
    SetMeshCameraSemiTransRange__7CMapMngFUsfffff
              ((double)(float)puVar24[1],(double)(float)puVar24[2],(double)(float)puVar24[3],
               (double)(float)puVar24[4],
               (double)((FLOAT_80330b64 * FLOAT_80330b68 * (float)puVar24[5]) / FLOAT_80330b54),
               &MapMng,(short)*puVar24);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x4e:
    uVar7 = (**(code **)((int)(flatRuntime2->flatRuntimeBase).vtable + 0x3c))
                      (flatRuntime2,*object->m_localBase);
    SetParticleWorkBind__13CFlatRuntime2FPQ212CFlatRuntime7CObject(flatRuntime2,uVar7);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x4d:
    uVar46 = *object->m_localBase;
    iVar8 = _GetMesMenu__8CMenuPcsFi(&MenuPcs,uVar46);
    if (iVar8 == 0) {
      iVar8 = GetNumMes__9CFlatDataFv((CFlatData *)&System);
      if (iVar8 != 0) {
        Printf__7CSystemFPce(&System,&DAT_801da3fc,uVar46);
      }
      push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
      *param_5 = 0;
    }
    else {
      _GetMesMenu__8CMenuPcsFi(&MenuPcs,uVar46);
      iVar8 = IsUse__8CMesMenuFv();
      if (iVar8 == 0) {
        push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
        *param_5 = 0;
      }
    }
    break;
  case -0x4c:
    puVar24 = object->m_localBase;
    local_d3c = CONCAT13((char)puVar24[2],CONCAT12((char)puVar24[3],0x80));
    local_d3c._2_2_ = CONCAT11((char)puVar24[4],0x80);
    local_d60 = local_d3c;
    SetIdGrpColor__7CMapMngFii8_GXColor
              (&MapMng,*object->m_localBase,object->m_localBase[1],&local_d60);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x4b:
    pppFieldShowFpNo__8CPartMngFsUc
              (&PartMng,(short)*object->m_localBase,(char)object->m_localBase[1]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x4a:
    *(uint32_t *)&flatRuntime2->field_0x12a0 = *object->m_localBase;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x49:
    SetParticleWorkSpeed__13CFlatRuntime2Ff((double)(float)*object->m_localBase,flatRuntime2);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x48:
    uVar46 = *object->m_localBase;
    uVar48 = object->m_localBase[1];
    iVar8 = _GetMesMenu__8CMenuPcsFi(&MenuPcs,uVar46);
    if (iVar8 == 0) {
      iVar8 = GetNumMes__9CFlatDataFv((CFlatData *)&System);
      if (iVar8 != 0) {
        Printf__7CSystemFPce(&System,&DAT_801da3fc,uVar46);
      }
      push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
      *param_5 = 0;
    }
    else {
      uVar7 = _GetMesMenu__8CMenuPcsFi(&MenuPcs,uVar46);
      uVar7 = FUN_800b94dc(uVar7,uVar48);
      push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,uVar7);
      *param_5 = 0;
    }
    break;
  case -0x47:
    puVar24 = object->m_localBase;
    uVar46 = *puVar24;
    uVar48 = puVar24[1];
    uVar33 = puVar24[2];
    iVar8 = _GetMesMenu__8CMenuPcsFi(&MenuPcs,uVar46);
    if (iVar8 == 0) {
      iVar8 = GetNumMes__9CFlatDataFv((CFlatData *)&System);
      if (iVar8 != 0) {
        Printf__7CSystemFPce(&System,&DAT_801da3fc,uVar46);
      }
    }
    else {
      mes = (CMes *)_GetMesMenu__8CMenuPcsFi(&MenuPcs,uVar46);
      GetMes__9CFlatDataFi(mes,uVar48,uVar33);
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x46:
    uVar46 = *object->m_localBase;
    iVar8 = _GetMesMenu__8CMenuPcsFi(&MenuPcs,uVar46);
    if (iVar8 == 0) {
      iVar8 = GetNumMes__9CFlatDataFv((CFlatData *)&System);
      if (iVar8 != 0) {
        Printf__7CSystemFPce(&System,&DAT_801da3fc,uVar46);
      }
    }
    else {
      uVar7 = _GetMesMenu__8CMenuPcsFi(&MenuPcs,uVar46);
      CloseRequest__8CMesMenuFi(uVar7,1);
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x45:
    puVar24 = object->m_localBase;
    uVar41 = *puVar24;
    uVar43 = puVar24[1];
    uVar44 = puVar24[2];
    uVar9 = puVar24[3];
    uVar47 = puVar24[4];
    uVar33 = puVar24[5];
    uVar48 = puVar24[6];
    uVar46 = puVar24[7];
    iVar8 = _GetMesMenu__8CMenuPcsFi(&MenuPcs,uVar41);
    if (iVar8 == 0) {
      iVar8 = GetNumMes__9CFlatDataFv((CFlatData *)&System);
      if (iVar8 != 0) {
        Printf__7CSystemFPce(&System,&DAT_801da3fc,uVar41);
      }
    }
    else {
      if ((uVar9 & 0x80) == 0) {
        GetSysMes__5CGameFi((CGame *)&flatRuntime2->field_0xcf20,uVar46);
        uVar7 = GetSysMes__5CGameFi((CGame *)&flatRuntime2->field_0xcf20,uVar46);
      }
      else {
        GetNumSysMes__5CGameFv(&Game.game,uVar46);
        uVar7 = GetNumSysMes__5CGameFv(&Game.game,uVar46);
      }
      uVar16 = _GetMesMenu__8CMenuPcsFi(&MenuPcs,uVar41);
      Open__8CMesMenuFPciiiiii(uVar16,uVar7,uVar43,uVar44,uVar9,uVar47,uVar33,uVar48);
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x44:
    pppShowSlot__8CPartMngFiUc(&PartMng,*object->m_localBase,(char)object->m_localBase[1]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x43:
    pppShowIdx__8CPartMngFsUc(&PartMng,(short)*object->m_localBase,(char)object->m_localBase[1]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x42:
    iVar8 = GetPadType__6JoyBusFi(&Joybus,*object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti
              (flatRuntime2,object,(0x40U - iVar8 | iVar8 - 0x40U) >> 0x1f);
    *param_5 = 0;
    break;
  case -0x41:
    puVar29 = object->m_localBase;
    uVar9 = *puVar29 & 3;
    local_b64.x = (float)puVar29[3];
    local_78 = (double)(CONCAT44(0x43300000,puVar29[1]) ^ 0x80000000);
    local_b64.y = (float)puVar29[4];
    local_80 = (double)CONCAT44(0x43300000,puVar29[2] ^ 0x80000000);
    local_b64.z = (float)puVar29[5];
    local_b64.w = (float)puVar29[6];
    dVar49 = (double)((float)(local_78 - DOUBLE_80330b98) / (float)(local_80 - DOUBLE_80330b98));
    local_b74.x = (float)puVar29[7];
    local_b74.y = (float)puVar29[8];
    local_b74.z = (float)puVar29[9];
    local_b74.w = (float)puVar29[10];
    if (uVar9 == 3) {
      dVar49 = (double)sinf__3stdFf((double)(float)((double)FLOAT_80330b54 * dVar49 +
                                                   (double)FLOAT_80330b50));
      dVar49 = -(double)(float)((double)FLOAT_80330b3c *
                                (double)(float)((double)FLOAT_80330b34 + dVar49) -
                               (double)FLOAT_80330b34);
    }
    else if (uVar9 == 1) {
      dVar49 = (double)sinf__3stdFf((double)(float)((double)FLOAT_80330b50 * dVar49 +
                                                   (double)FLOAT_80330b58));
      dVar49 = (double)(float)((double)FLOAT_80330b34 + dVar49);
    }
    else if (uVar9 == 2) {
      dVar49 = (double)sinf__3stdFf((double)(float)((double)FLOAT_80330b50 * dVar49));
    }
    C_QUATSlerp(dVar49,&local_b64,&local_b74,&local_b84);
    *(float *)object->m_localBase[0xb] = local_b84.x;
    *(float *)object->m_localBase[0xc] = local_b84.y;
    *(float *)object->m_localBase[0xd] = local_b84.z;
    *(float *)object->m_localBase[0xe] = local_b84.w;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x40:
    pfVar28 = (float *)object->m_localBase;
    local_b54.x = *pfVar28;
    local_b54.y = pfVar28[1];
    local_b54.z = pfVar28[2];
    local_b54.w = pfVar28[3];
    PSMTXQuat(&MStack_a10,&local_b54);
    SetWorldMapMatrix__10CCameraPcsFPA4_f(&CameraPcs,&MStack_a10);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x3f:
    GetWorldMapMatrix__10CCameraPcsFPA4_f(&CameraPcs,&MStack_9e0);
    C_QUATMtx(&local_b44,&MStack_9e0);
    *(float *)*object->m_localBase = local_b44.x;
    *(float *)object->m_localBase[1] = local_b44.y;
    *(float *)object->m_localBase[2] = local_b44.z;
    *(float *)object->m_localBase[3] = local_b44.w;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x3e:
    pppEndPart__8CPartMngFi(&PartMng,*object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x3d:
    PutParticleWork__13CFlatRuntime2Fv(flatRuntime2);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x3c:
    puVar24 = object->m_localBase;
    local_78 = (double)(CONCAT44(0x43300000,puVar24[2]) ^ 0x80000000);
    SetParticleWorkCol__13CFlatRuntime2Fiif
              ((double)(float)(local_78 - DOUBLE_80330b98),flatRuntime2,*puVar24,puVar24[1]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x3b:
    SetParticleWorkScale__13CFlatRuntime2Ff((double)(float)*object->m_localBase,flatRuntime2);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x3a:
    SetParticleWorkVector__13CFlatRuntime2Fff
              ((double)(float)*object->m_localBase,(double)(float)object->m_localBase[1],
               flatRuntime2);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x39:
    pfVar28 = (float *)object->m_localBase;
    __ct__7CVectorFfff(*pfVar28,pfVar28[1],pfVar28[2],&CStack_c6c);
    pVVar12 = (Vec *)__opR3Vec__7CVectorFv();
    SetParticleWorkTarget__13CFlatRuntime2FR3Vec(flatRuntime2,pVVar12);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x38:
    pfVar28 = (float *)object->m_localBase;
    __ct__7CVectorFfff(*pfVar28,pfVar28[1],pfVar28[2],&CStack_c60);
    pVVar12 = (Vec *)__opR3Vec__7CVectorFv();
    SetParticleWorkPos__13CFlatRuntime2FR3Vecf((double)pfVar28[3],flatRuntime2,pVVar12);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x37:
    puVar24 = object->m_localBase;
    ResetParticleWork__13CFlatRuntime2Fii(flatRuntime2,*puVar24 << 8 | puVar24[2],puVar24[1]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x36:
    EndParticleSlot__13CFlatRuntime2Fii(flatRuntime2,*object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x35:
    uVar7 = GetFreeParticleSlot__13CFlatRuntime2Fv();
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,uVar7);
    *param_5 = 0;
    break;
  case -0x34:
    dVar50 = (double)(float)object->m_localBase[1];
    dVar51 = (double)(float)object->m_localBase[2];
    dVar49 = (double)cosf__3stdFf(dVar50);
    local_b34 = (float)dVar49;
    local_b30 = FLOAT_80330b30;
    dVar49 = (double)sinf__3stdFf(dVar50);
    local_b2c = (float)dVar49;
    GetWorldMapMatrix__10CCameraPcsFPA4_f(&CameraPcs,&MStack_980);
    if (*object->m_localBase != 0) {
      PSMTXIdentity(&MStack_980);
    }
    PSMTXRotAxisRad((float)dVar51,&MStack_9b0,&local_b34);
    PSMTXConcat(&MStack_9b0,&MStack_980,&MStack_980);
    local_b34 = FLOAT_80330b30;
    local_b30 = FLOAT_80330b34;
    local_b2c = FLOAT_80330b30;
    PSMTXRotAxisRad((float)object->m_localBase[3],&MStack_9b0,&local_b34);
    PSMTXConcat(&MStack_9b0,&MStack_980,&MStack_980);
    SetWorldMapMatrix__10CCameraPcsFPA4_f(&CameraPcs,&MStack_980);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x33:
    puVar24 = object->m_localBase;
    GraphicsPcs._108_4_ = *puVar24;
    GraphicsPcs._112_4_ = 0;
    GraphicsPcs._100_1_ = (undefined)puVar24[1];
    GraphicsPcs._101_1_ = (undefined)puVar24[2];
    GraphicsPcs._102_1_ = (undefined)puVar24[3];
    GraphicsPcs._103_1_ = 0xff;
    GraphicsPcs._92_4_ = puVar24[4];
    GraphicsPcs._96_4_ = GraphicsPcs._92_4_;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x32:
    GraphicsPcs._152_4_ = *object->m_localBase;
    GraphicsPcs._136_4_ = object->m_localBase[1];
    GraphicsPcs._140_4_ = GraphicsPcs._136_4_;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x31:
    DeleteAllFieldItem__9CGItemObjFv();
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x30:
    uVar7 = GetScreenFadeExecutingBit__11CGraphicPcsFv(&GraphicsPcs);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,uVar7);
    *param_5 = 0;
    break;
  case -0x2f:
    SetIdGrpMask__7CMapMngFiUl(&MapMng,*object->m_localBase,object->m_localBase[1]);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x2e:
    IsHitDrawMode__7CMapPcsFc(&MapPcs,(int)(char)*object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x2d:
    SetFullScreenShadowRot__10CCameraPcsFff
              ((double)(float)*object->m_localBase,(double)(float)object->m_localBase[1],&CameraPcs)
    ;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x2c:
    puVar24 = object->m_localBase;
    local_b28 = *puVar24;
    local_b24 = puVar24[1];
    local_b20 = puVar24[2];
    SetFullScreenShadowPos__10CCameraPcsFP3Vecf((double)(float)puVar24[3],&CameraPcs,&local_b28);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x2b:
    SetFullScreenShadowEnable__10CCameraPcsFUc(&CameraPcs,*object->m_localBase & 0xff);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x2a:
    puVar24 = object->m_localBase;
    local_d38 = CONCAT13((char)*puVar24,CONCAT12((char)puVar24[1],0xff));
    local_d38._2_2_ = CONCAT11((char)puVar24[2],0xff);
    local_d5c = local_d38;
    SetFogColor__8CGraphicF8_GXColor(&Graphic,&local_d5c);
    SetFogParam__8CGraphicFff((float)object->m_localBase[3],(float)object->m_localBase[4],&Graphic);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x29:
    puVar24 = object->m_localBase;
    local_d34 = CONCAT31(CONCAT21(CONCAT11((char)*puVar24,(char)puVar24[1]),(char)puVar24[2]),0xff);
    local_d58 = local_d34;
    SetCopyClear__8CGraphicF8_GXColori(&Graphic,&local_d58);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x28:
    *(uint32_t *)(&flatRuntime2->field_0x1c08 + *object->m_localBase * 0xb14) = *object->m_localBase
    ;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x27:
    if ((*(uint *)&flatRuntime2->field_0x129c & 0x100000) != 0) {
      GetViewMatrix__10CCameraPcsFPA4_f(&CameraPcs,&MStack_950);
      _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
      GXSetZCompLoc(0);
      _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6,1,0,7,0);
      GXSetZMode(1,3,1);
      GXSetCullMode(1);
      GXSetNumTevStages(1);
      _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,4);
      _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0xff,0xff,4);
      GXSetNumChans(1);
      GXSetChanCtrl(0,0,0,0,0,2,1);
      GXSetChanCtrl(2,0,0,0,0,2,2);
      GXClearVtxDesc();
      GXSetVtxDesc(9,1);
      GXSetVtxAttrFmt(0,9,1,4,0);
      fVar2 = (float)object->m_localBase[3];
      PSMTXScale(fVar2,fVar2,fVar2,&MStack_920);
      pfVar28 = (float *)object->m_localBase;
      MStack_920.value[1][3] = pfVar28[1];
      MStack_920.value[2][3] = pfVar28[2];
      MStack_920.value[0][3] = *pfVar28;
      PSMTXConcat(&MStack_950,&MStack_920,&MStack_920);
      GXLoadPosMtxImm(&MStack_920,0);
      puVar24 = object->m_localBase;
      local_d30 = CONCAT13((char)puVar24[4],CONCAT12((char)puVar24[5],0xff));
      local_d30._2_2_ = CONCAT11((char)puVar24[6],0xff);
      local_d54 = local_d30;
      GXSetChanMatColor(4,&local_d54);
      DrawSphere__8CGraphicFv(&Graphic);
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x26:
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti
              (flatRuntime2,object,
               *(undefined4 *)(&flatRuntime2->field_0x26ec + *object->m_localBase * 0xb14));
    *param_5 = 0;
    break;
  case -0x25:
    puVar24 = object->m_localBase;
    local_b1c = puVar24[1];
    local_b18 = puVar24[2];
    puVar13 = &flatRuntime2->field_0x1bdc + *puVar24 * 0xb14;
    local_b14 = puVar24[3];
    iVar8 = Calc__9CLine<64>FP3VecPfPUlPfP3Vecf
                      ((double)FLOAT_80330b30,puVar13,0,0,&local_d28,&local_d2c,&local_b1c);
    if (iVar8 != 0) {
      in_f28 = (double)(*(float *)(puVar13 + local_d28 * 0x20 + 0x348) * local_d2c +
                       *(float *)(puVar13 + local_d28 * 0x20 + 0x34c));
    }
    *(float *)object->m_localBase[4] = (float)in_f28;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x24:
    fVar2 = (float)object->m_localBase[1];
    puVar13 = &flatRuntime2->field_0x1bdc + *object->m_localBase * 0xb14;
    if (FLOAT_80330b30 <= fVar2) {
      if (fVar2 < *(float *)(puVar13 + 0xb10)) {
        iVar26 = *(int *)(puVar13 + 0x18);
        iVar8 = 0;
        puVar14 = puVar13;
        while (iVar26 = iVar26 + -1, iVar26 != 0) {
          if ((*(float *)(puVar14 + 0x34c) <= fVar2) &&
             (fVar2 < *(float *)(puVar14 + 0x34c) + *(float *)(puVar14 + 0x348))) {
            __as__3VecFRC3Vec(&local_b10,puVar13 + iVar8 * 0x20 + 0x33c);
            break;
          }
          puVar14 = puVar14 + 0x20;
          iVar8 = iVar8 + 1;
        }
      }
      else {
        __as__3VecFRC3Vec(&local_b10,puVar13 + (*(int *)(puVar13 + 0x18) + -1) * 0x20 + 0x33c);
      }
    }
    else {
      __as__3VecFRC3Vec(&local_b10,puVar13 + 0x33c);
    }
    if (object->m_localBase[2] == 0) {
      local_b10 = -local_b10;
      local_b0c = -local_b0c;
      local_b08 = -local_b08;
    }
    *(float *)object->m_localBase[3] = local_b10;
    *(float *)object->m_localBase[4] = local_b0c;
    *(float *)object->m_localBase[5] = local_b08;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x23:
    fVar2 = (float)object->m_localBase[1];
    puVar13 = &flatRuntime2->field_0x1bdc + *object->m_localBase * 0xb14;
    if (FLOAT_80330b30 <= fVar2) {
      if (fVar2 < *(float *)(puVar13 + 0xb10)) {
        iVar26 = *(int *)(puVar13 + 0x18);
        iVar8 = 0;
        puVar14 = puVar13;
        while (iVar26 = iVar26 + -1, iVar26 != 0) {
          if ((*(float *)(puVar14 + 0x34c) <= fVar2) &&
             (fVar2 < *(float *)(puVar14 + 0x34c) + *(float *)(puVar14 + 0x348))) {
            VECLerp__FP3VecP3VecP3Vecf
                      ((double)((fVar2 - *(float *)(puVar13 + iVar8 * 0x20 + 0x34c)) /
                               *(float *)(puVar13 + iVar8 * 0x20 + 0x348)),
                       puVar13 + iVar8 * 0xc + 0x30,puVar13 + (iVar8 + 1) * 0xc + 0x30,&local_b04);
            break;
          }
          puVar14 = puVar14 + 0x20;
          iVar8 = iVar8 + 1;
        }
      }
      else {
        __as__3VecFRC3Vec(&local_b04,puVar13 + (*(int *)(puVar13 + 0x18) + -1) * 0xc + 0x30);
      }
    }
    else {
      __as__3VecFRC3Vec(&local_b04,puVar13 + 0x30);
    }
    *(undefined4 *)object->m_localBase[2] = local_b04;
    *(undefined4 *)object->m_localBase[3] = local_b00;
    *(undefined4 *)object->m_localBase[4] = local_afc;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x22:
    puVar24 = object->m_localBase;
    puVar13 = &flatRuntime2->field_0x1bdc;
    dVar49 = (double)FLOAT_80330b5c;
    iVar8 = 0;
    uVar9 = *puVar24;
    uVar31 = 0;
    local_af8 = puVar24[1];
    local_af4 = puVar24[2];
    local_af0 = puVar24[3];
    dVar50 = (double)(float)puVar24[4];
    do {
      if ((((*(int *)(puVar13 + 0x18) != 0) && ((*(uint *)(puVar13 + 0x2c) & uVar9) != 0)) &&
          (iVar26 = IsInner__9CLine<64>FP3Vecf(dVar50,puVar13,&local_af8), iVar26 != 0)) &&
         ((iVar26 = Calc__9CLine<64>FP3VecPfPUlPfP3Vecf
                              (dVar50,puVar13,0,&local_d24,&local_d1c,&local_d20,&local_af8),
          iVar26 != 0 && ((double)local_d24 < dVar49)))) {
        iVar8 = 1;
        in_f30 = (double)(*(float *)(puVar13 + local_d1c * 0x20 + 0x348) * local_d20 +
                         *(float *)(puVar13 + local_d1c * 0x20 + 0x34c));
        unaff_r24 = uVar31;
        dVar49 = (double)local_d24;
      }
      uVar31 = uVar31 + 1;
      puVar13 = puVar13 + 0xb14;
    } while (uVar31 < 0x10);
    if (iVar8 != 0) {
      *(uint *)object->m_localBase[5] = unaff_r24;
      *(float *)object->m_localBase[6] = (float)in_f30;
      *(undefined4 *)object->m_localBase[7] =
           *(undefined4 *)(&flatRuntime2->field_0x26ec + unaff_r24 * 0xb14);
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,iVar8);
    *param_5 = 0;
    break;
  case -0x21:
    dVar50 = (double)(float)object->m_localBase[5];
    dVar53 = (double)(float)object->m_localBase[6];
    dVar49 = (double)sinf__3stdFf(dVar50);
    dVar50 = (double)cosf__3stdFf(dVar50);
    dVar51 = (double)cosf__3stdFf(dVar53);
    dVar52 = (double)(float)(dVar49 * dVar51);
    dVar49 = (double)sinf__3stdFf(dVar53);
    dVar51 = (double)cosf__3stdFf(dVar53);
    puVar40 = object->m_localBase;
    __ct__7CVectorFfff((float)-dVar52,(float)-dVar49,-(float)(dVar50 * dVar51),&CStack_c48);
    uVar7 = __opP3Vec__7CVectorFv();
    puVar24 = object->m_localBase;
    __ct__6CColorFUcUcUcUc(auStack_d50,puVar24[2] & 0xff,puVar24[3] & 0xff,puVar24[4] & 0xff,0xff);
    uVar16 = __opP8_GXColor__6CColorFv();
    SetDiffuse__9CCharaPcsFiUlP8_GXColorP3Vec(&CharaPcs,*puVar40,puVar40[1],uVar16,uVar7);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x20:
    puVar24 = object->m_localBase;
    __ct__6CColorFUcUcUcUc(auStack_d4c,puVar24[1] & 0xff,puVar24[2] & 0xff,puVar24[3] & 0xff,0xff);
    uVar7 = __opP8_GXColor__6CColorFv();
    SetAmbient__9CCharaPcsFiP8_GXColor(&CharaPcs,*object->m_localBase,uVar7);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x1f:
    if (*object->m_localBase < 0x10) {
      iVar8 = *object->m_localBase * 0xb14;
      uVar9 = *(uint *)(&flatRuntime2->field_0x1bf4 + iVar8);
      if (uVar9 < 0x40) {
        *(uint *)(&flatRuntime2->field_0x1bf4 + iVar8) = uVar9 + 1;
        iVar26 = uVar9 * 0xc + iVar8;
        *(uint32_t *)(&flatRuntime2->field_0x1c0c + iVar26) = object->m_localBase[1];
        *(uint32_t *)(&flatRuntime2->field_0x1c10 + iVar26) = object->m_localBase[2];
        *(uint32_t *)(&flatRuntime2->field_0x1c14 + iVar26) = object->m_localBase[3];
        CalcBound__9CLine(&flatRuntime2->field_0x1bdc + iVar8);
      }
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x1e:
    uVar9 = *object->m_localBase;
    if (uVar9 < 0x10) {
      uVar31 = object->m_localBase[1];
      *(undefined4 *)(&flatRuntime2->field_0x1bf4 + uVar9 * 0xb14) = 0;
      *(uint *)(&flatRuntime2->field_0x1c08 + uVar9 * 0xb14) = uVar31;
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x1d:
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x1c:
    *(uint32_t *)&flatRuntime2->field_0x129c = *object->m_localBase;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x1b:
    puVar24 = object->m_localBase;
    __ct__7CVectorFfff((float)puVar24[2],(float)puVar24[3],(float)puVar24[4],&CStack_c54);
    uVar7 = __opR3Vec__7CVectorFv();
    PutParticle__13CFlatRuntime2FiR3Vecf
              ((double)(float)puVar24[5],flatRuntime2,
               *object->m_localBase << 8 | object->m_localBase[1],uVar7);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x1a:
    puVar24 = object->m_localBase;
    local_80 = (double)(CONCAT44(0x43300000,puVar24[1]) ^ 0x80000000);
    uVar31 = *puVar24;
    uVar9 = uVar31 & 3;
    local_78 = (double)CONCAT44(0x43300000,puVar24[2] ^ 0x80000000);
    dVar49 = (double)((float)(local_80 - DOUBLE_80330b98) / (float)(local_78 - DOUBLE_80330b98));
    if ((uVar31 & 4) == 0) {
      if (uVar9 == 3) {
        dVar49 = (double)sinf__3stdFf((double)(float)((double)FLOAT_80330b54 * dVar49 +
                                                     (double)FLOAT_80330b50));
        dVar49 = -(double)(float)((double)FLOAT_80330b3c *
                                  (double)(float)((double)FLOAT_80330b34 + dVar49) -
                                 (double)FLOAT_80330b34);
      }
      else if (uVar9 == 1) {
        dVar49 = (double)sinf__3stdFf((double)(float)((double)FLOAT_80330b50 * dVar49 +
                                                     (double)FLOAT_80330b58));
        dVar49 = (double)(float)((double)FLOAT_80330b34 + dVar49);
      }
      else if (uVar9 == 2) {
        dVar49 = (double)sinf__3stdFf((double)(float)((double)FLOAT_80330b50 * dVar49));
      }
      pfVar28 = (float *)&flatRuntime2->field_0x17dc;
      iVar25 = 0;
      iVar8 = *(int *)&flatRuntime2->field_0x17d4 + -1;
      fVar2 = (float)((double)*(float *)&flatRuntime2->field_0x17d8 * dVar49);
      iVar26 = iVar8;
      if (0 < iVar8) {
        do {
          if ((*pfVar28 <= fVar2) && (fVar2 <= pfVar28[4])) {
            iVar26 = iVar8;
            if (iVar25 + 1 < iVar8) {
              iVar26 = iVar25 + 1;
            }
            if (iVar25 + 2 < iVar8) {
              iVar8 = iVar25 + 2;
            }
            fVar4 = *(float *)(&flatRuntime2->field_0x17dc + iVar26 * 0x10);
            fVar5 = *(float *)(&flatRuntime2->field_0x17dc + iVar25 * 0x10);
            b = fVar4 - fVar5;
            radius = FLOAT_80330b30;
            if (FLOAT_80330b30 != b) {
              radius = (fVar2 - fVar5) / b;
            }
            CrossCheckEllipseCapsule__5CMathFP3VecPfP3VecP3VecfP3Vecff
                      (fVar5 - *(float *)(&flatRuntime2->field_0x17dc +
                                         (iVar25 - 1U & ~((int)(iVar25 - 1U) >> 0x1f)) * 0x10),b,
                       *(float *)(&flatRuntime2->field_0x17dc + iVar8 * 0x10) - fVar4,radius,
                       FLOAT_80330b34,(Mat4x4 *)&Math,&local_aec,
                       (float *)((int)(&flatRuntime2->field_0x17dc +
                                      (iVar25 - 1U & ~((int)(iVar25 - 1U) >> 0x1f)) * 0x10) + 4),
                       (float *)((int)(&flatRuntime2->field_0x17dc + iVar25 * 0x10) + 4),
                       (float *)((int)(&flatRuntime2->field_0x17dc + iVar26 * 0x10) + 4),
                       (float *)((int)(&flatRuntime2->field_0x17dc + iVar8 * 0x10) + 4));
            *(undefined4 *)object->m_localBase[3] = local_aec;
            *(undefined4 *)object->m_localBase[4] = local_ae8;
            *(undefined4 *)object->m_localBase[5] = local_ae4;
            break;
          }
          iVar25 = iVar25 + 1;
          pfVar28 = pfVar28 + 4;
          iVar26 = iVar26 + -1;
        } while (iVar26 != 0);
      }
    }
    else {
      uVar6 = uVar31 & 1;
      local_78 = (double)(CONCAT44(0x43300000,
                                   (*(int *)&flatRuntime2->field_0x17d4 + 1) -
                                   (uVar6 + (uVar9 >> 1))) ^ 0x80000000);
      dVar49 = dVar49 * (double)(float)(local_78 - DOUBLE_80330b98);
      iVar8 = (int)dVar49;
      local_80 = (double)(longlong)iVar8;
      iVar8 = iVar8 - ((int)-uVar6 >> 0x1f);
      dVar49 = (double)fmodf__3stdFff((double)(float)dVar49,(double)FLOAT_80330b34);
      pCVar10 = (CVector *)__ct__7CVectorFRC3Vec(&CStack_bd0,(Vec *)&flatRuntime2->field_0x17e0);
      pCVar11 = (CVector *)__ct__7CVectorFRC3Vec(&CStack_bc4,(Vec *)&flatRuntime2->field_0x17f0);
      __mi__7CVectorCFRC7CVector(&CStack_bb8,pCVar11,pCVar10);
      __ct__7CVectorFRC7CVector(&CStack_a80,&CStack_bb8);
      pCVar10 = (CVector *)__ct__7CVectorFRC3Vec(&CStack_be8,(Vec *)&flatRuntime2->field_0x17e0);
      __mi__7CVectorCFRC7CVector(&CStack_bdc,pCVar10,&CStack_a80);
      __ct__7CVectorFRC7CVector(&CStack_a8c,&CStack_bdc);
      __mi__7CVectorCFRC7CVector(&CStack_bf4,&CStack_a8c,&CStack_a80);
      __ct__7CVectorFRC7CVector(&CStack_a98,&CStack_bf4);
      pCVar10 = (CVector *)
                __ct__7CVectorFRC3Vec
                          (&CStack_c18,
                           (Vec *)(&flatRuntime2->field_0x17c0 +
                                  *(int *)&flatRuntime2->field_0x17d4 * 0x10));
      pCVar11 = (CVector *)
                __ct__7CVectorFRC3Vec
                          (&CStack_c0c,
                           (Vec *)(&flatRuntime2->field_0x17d0 +
                                  *(int *)&flatRuntime2->field_0x17d4 * 0x10));
      __mi__7CVectorCFRC7CVector(&CStack_c00,pCVar11,pCVar10);
      __as__7CVectorFRC7CVector(&CStack_a80,&CStack_c00);
      pCVar10 = (CVector *)
                __ct__7CVectorFRC3Vec
                          (&CStack_c30,
                           (Vec *)(&flatRuntime2->field_0x17d0 +
                                  *(int *)&flatRuntime2->field_0x17d4 * 0x10));
      __pl__7CVectorCFRC7CVector(&CStack_c24,pCVar10,&CStack_a80);
      __ct__7CVectorFRC7CVector(&CStack_aa4,&CStack_c24);
      __pl__7CVectorCFRC7CVector(&CStack_c3c,&CStack_aa4,&CStack_a80);
      __ct__7CVectorFRC7CVector(&CStack_ab0,&CStack_c3c);
      if (uVar6 == 0) {
        if (iVar8 + -2 < 0) {
          iVar26 = 0;
        }
        else {
          iVar25 = *(int *)&flatRuntime2->field_0x17d4 + -1;
          iVar26 = iVar8 + -2;
          if (iVar25 < iVar8 + -2) {
            iVar26 = iVar25;
          }
        }
        pVVar12 = (Vec *)(&flatRuntime2->field_0x17e0 + iVar26 * 0x10);
        if (iVar8 + -1 < 0) {
          iVar26 = 0;
        }
        else {
          iVar25 = *(int *)&flatRuntime2->field_0x17d4 + -1;
          iVar26 = iVar8 + -1;
          if (iVar25 < iVar8 + -1) {
            iVar26 = iVar25;
          }
        }
        puVar13 = &flatRuntime2->field_0x17e0 + iVar26 * 0x10;
      }
      else {
        if (iVar8 == 0) {
          pVVar12 = (Vec *)__opP3Vec__7CVectorFv(&CStack_a98);
        }
        else if (iVar8 == 1) {
          pVVar12 = (Vec *)__opP3Vec__7CVectorFv(&CStack_a8c);
        }
        else {
          if (iVar8 + -2 < 0) {
            iVar26 = 0;
          }
          else {
            iVar25 = *(int *)&flatRuntime2->field_0x17d4 + -1;
            iVar26 = iVar8 + -2;
            if (iVar25 < iVar8 + -2) {
              iVar26 = iVar25;
            }
          }
          pVVar12 = (Vec *)(&flatRuntime2->field_0x17e0 + iVar26 * 0x10);
        }
        if (iVar8 == 0) {
          puVar13 = (undefined *)__opP3Vec__7CVectorFv(&CStack_a8c);
        }
        else {
          if (iVar8 + -1 < 0) {
            iVar26 = 0;
          }
          else {
            iVar25 = *(int *)&flatRuntime2->field_0x17d4 + -1;
            iVar26 = iVar8 + -1;
            if (iVar25 < iVar8 + -1) {
              iVar26 = iVar25;
            }
          }
          puVar13 = &flatRuntime2->field_0x17e0 + iVar26 * 0x10;
        }
      }
      if ((uVar31 & 2) == 0) {
        if (iVar8 < 0) {
          iVar26 = 0;
        }
        else {
          iVar25 = *(int *)&flatRuntime2->field_0x17d4 + -1;
          iVar26 = iVar8;
          if (iVar25 < iVar8) {
            iVar26 = iVar25;
          }
        }
        puVar14 = &flatRuntime2->field_0x17e0 + iVar26 * 0x10;
        if (iVar8 + 1 < 0) {
          iVar26 = 0;
        }
        else {
          iVar25 = *(int *)&flatRuntime2->field_0x17d4 + -1;
          iVar26 = iVar8 + 1;
          if (iVar25 < iVar8 + 1) {
            iVar26 = iVar25;
          }
        }
        puVar15 = &flatRuntime2->field_0x17e0 + iVar26 * 0x10;
      }
      else {
        if (iVar8 == *(int *)&flatRuntime2->field_0x17d4) {
          puVar14 = (undefined *)__opP3Vec__7CVectorFv(&CStack_aa4);
        }
        else {
          if (iVar8 < 0) {
            iVar26 = 0;
          }
          else {
            iVar25 = *(int *)&flatRuntime2->field_0x17d4 + -1;
            iVar26 = iVar8;
            if (iVar25 < iVar8) {
              iVar26 = iVar25;
            }
          }
          puVar14 = &flatRuntime2->field_0x17e0 + iVar26 * 0x10;
        }
        iVar26 = *(int *)&flatRuntime2->field_0x17d4 + -1;
        if (iVar8 == iVar26) {
          puVar15 = (undefined *)__opP3Vec__7CVectorFv(&CStack_aa4);
        }
        else if (iVar8 == *(int *)&flatRuntime2->field_0x17d4) {
          puVar15 = (undefined *)__opP3Vec__7CVectorFv(&CStack_ab0);
        }
        else {
          if (iVar8 + 1 < 0) {
            iVar25 = 0;
          }
          else {
            iVar25 = iVar8 + 1;
            if (iVar26 < iVar8 + 1) {
              iVar25 = iVar26;
            }
          }
          puVar15 = &flatRuntime2->field_0x17e0 + iVar25 * 0x10;
        }
      }
      PSVECScale(FLOAT_80330b38,pVVar12,&local_abc);
      VECMultAdd__FP3VecP3VecP3Vecf((double)FLOAT_80330b3c,&local_abc,puVar13,&local_abc);
      VECMultAdd__FP3VecP3VecP3Vecf((double)FLOAT_80330b40,&local_abc,puVar14,&local_abc);
      VECMultAdd__FP3VecP3VecP3Vecf((double)FLOAT_80330b44,&local_abc,puVar15,&local_abc);
      PSVECScale(FLOAT_80330b3c,pVVar12,&VStack_ac8);
      VECMultAdd__FP3VecP3VecP3Vecf((double)FLOAT_80330b48,&VStack_ac8,puVar13,&VStack_ac8);
      VECMultAdd__FP3VecP3VecP3Vecf((double)FLOAT_80330b3c,&VStack_ac8,puVar14,&VStack_ac8);
      PSVECScale(FLOAT_80330b40,pVVar12,&VStack_ad4);
      VECMultAdd__FP3VecP3VecP3Vecf((double)FLOAT_80330b3c,&VStack_ad4,puVar14,&VStack_ad4);
      PSVECScale(FLOAT_80330b44,pVVar12,&VStack_ae0);
      VECMultAdd__FP3VecP3VecP3Vecf((double)FLOAT_80330b4c,&VStack_ae0,puVar13,&VStack_ae0);
      VECMultAdd__FP3VecP3VecP3Vecf((double)FLOAT_80330b44,&VStack_ae0,puVar14,&VStack_ae0);
      PSVECScale((float)dVar49,&local_abc,&local_abc);
      PSVECAdd(&local_abc,&VStack_ac8,&local_abc);
      PSVECScale((float)dVar49,&local_abc,&local_abc);
      PSVECAdd(&local_abc,&VStack_ad4,&local_abc);
      PSVECScale((float)dVar49,&local_abc,&local_abc);
      PSVECAdd(&local_abc,&VStack_ae0,&local_abc);
      *(float *)object->m_localBase[3] = local_abc.x;
      *(float *)object->m_localBase[4] = local_abc.y;
      *(float *)object->m_localBase[5] = local_abc.z;
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x19:
    if (*(uint *)&flatRuntime2->field_0x17d4 < 0x40) {
      if (*object->m_localBase != 0) {
        *(undefined4 *)&flatRuntime2->field_0x17d4 = 0;
        *(float *)&flatRuntime2->field_0x17d8 = fVar2;
      }
      *(uint32_t *)(&flatRuntime2->field_0x17e0 + *(int *)&flatRuntime2->field_0x17d4 * 0x10) =
           object->m_localBase[1];
      *(uint32_t *)(&flatRuntime2->field_0x17e4 + *(int *)&flatRuntime2->field_0x17d4 * 0x10) =
           object->m_localBase[2];
      *(uint32_t *)(&flatRuntime2->field_0x17e8 + *(int *)&flatRuntime2->field_0x17d4 * 0x10) =
           object->m_localBase[3];
      iVar8 = *(int *)&flatRuntime2->field_0x17d4;
      if (iVar8 != 0) {
        dVar49 = (double)PSVECDistance((Vec *)(&flatRuntime2->field_0x17e0 + iVar8 * 0x10),
                                       (Vec *)(&flatRuntime2->field_0x17d0 + iVar8 * 0x10));
        *(float *)&flatRuntime2->field_0x17d8 =
             (float)((double)*(float *)&flatRuntime2->field_0x17d8 + dVar49);
      }
      *(undefined4 *)(&flatRuntime2->field_0x17dc + *(int *)&flatRuntime2->field_0x17d4 * 0x10) =
           *(undefined4 *)&flatRuntime2->field_0x17d8;
      *(int *)&flatRuntime2->field_0x17d4 = *(int *)&flatRuntime2->field_0x17d4 + 1;
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x18:
    SetFov__10CCameraPcsFf((double)(float)*object->m_localBase,&CameraPcs);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x17:
    SetZRotate__10CCameraPcsFf((double)(float)*object->m_localBase,&CameraPcs);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x16:
    strcpy(&CStack_484,
           (flatRuntime2->flatRuntimeBase).m_strBlob +
           (flatRuntime2->flatRuntimeBase).m_strOffs[*object->m_localBase]);
    SetNextScript__5CGameFPQ25CGame11CNextScript(&Game.game,&CStack_484);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x15:
    local_d18 = ABS((float)*object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,local_d18);
    *param_5 = 0;
    break;
  case -0x14:
    uVar9 = (int)*object->m_localBase >> 0x1f;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti
              (flatRuntime2,object,(uVar9 ^ *object->m_localBase) - uVar9);
    *param_5 = 0;
    break;
  case -0x13:
    uVar9 = GetDbgFlag__11CDbgMenuPcsFv(0x80306708);
    fVar2 = FLOAT_80330b30;
    if ((uVar9 & 0x100) == 0) {
      dVar49 = (double)GetRightStickX__4CPadFl(&Pad,*object->m_localBase);
      dVar50 = (double)GetRightStickY__4CPadFl(&Pad,*object->m_localBase);
      *(float *)object->m_localBase[1] = (float)dVar49;
      *(float *)object->m_localBase[2] = (float)dVar50;
    }
    else {
      *(float *)object->m_localBase[1] = FLOAT_80330b30;
      *(float *)object->m_localBase[2] = fVar2;
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x12:
    uVar9 = GetDbgFlag__11CDbgMenuPcsFv(0x80306708);
    fVar2 = FLOAT_80330b30;
    if ((uVar9 & 0x100) == 0) {
      dVar49 = (double)GetLeftStickX__4CPadFl(&Pad,*object->m_localBase);
      dVar50 = (double)GetLeftStickY__4CPadFl(&Pad,*object->m_localBase);
      *(float *)object->m_localBase[1] = (float)dVar49;
      *(float *)object->m_localBase[2] = (float)dVar50;
    }
    else {
      *(float *)object->m_localBase[1] = FLOAT_80330b30;
      *(float *)object->m_localBase[2] = fVar2;
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -0x11:
    dVar49 = (double)RandFPM__5CMathFf((double)(float)*object->m_localBase,&Math);
    local_d14 = (float)dVar49;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,local_d14);
    *param_5 = 0;
    break;
  case -0x10:
    uVar7 = RandPM__5CMathFUl(&Math,*object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,uVar7);
    *param_5 = 0;
    break;
  case -0xf:
    dVar49 = (double)RandF__5CMathFf((double)(float)*object->m_localBase,&Math);
    local_d10 = (float)dVar49;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,local_d10);
    *param_5 = 0;
    break;
  case -0xe:
    uVar7 = Rand__5CMathFUl(&Math,*object->m_localBase);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,uVar7);
    *param_5 = 0;
    break;
  case -0xd:
    pfVar28 = (float *)object->m_localBase;
    local_a68.x = *pfVar28;
    local_a68.y = pfVar28[1];
    local_a68.z = pfVar28[2];
    local_a74.x = pfVar28[3];
    local_a74.y = pfVar28[4];
    local_a74.z = pfVar28[5];
    dVar49 = (double)PSVECDistance(&local_a68,&local_a74);
    local_d0c = (float)dVar49;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,local_d0c);
    *param_5 = 0;
    break;
  case -0xc:
    if ((1 << *object->m_localBase & *(uint *)&flatRuntime2->field_0x12a8) == 0) {
      uVar22 = GetButtonRepeat__4CPadFl(&Pad);
    }
    else {
      uVar22 = 0;
    }
    uVar9 = GetDbgFlag__11CDbgMenuPcsFv(0x80306708);
    if ((uVar9 & 0x100) != 0) {
      uVar22 = uVar22 & 0xf3ff;
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,(int)(short)uVar22);
    *param_5 = 0;
    break;
  case -0xb:
    if ((1 << *object->m_localBase & *(uint *)&flatRuntime2->field_0x12a8) == 0) {
      uVar22 = GetButtonDown__4CPadFl(&Pad);
    }
    else {
      uVar22 = 0;
    }
    uVar9 = GetDbgFlag__11CDbgMenuPcsFv(0x80306708);
    if ((uVar9 & 0x100) != 0) {
      uVar22 = uVar22 & 0xf3ff;
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,(int)(short)uVar22);
    *param_5 = 0;
    break;
  case -10:
    dVar49 = (double)atan2__3stdFff((double)(float)*object->m_localBase,
                                    (double)(float)object->m_localBase[1]);
    local_d08 = (float)dVar49;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,local_d08);
    *param_5 = 0;
    break;
  case -9:
    ChangeMap__5CGameFiiii(&Game.game,*object->m_localBase,object->m_localBase[1],0,1);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -8:
    puVar24 = object->m_localBase;
    uVar46 = *puVar24;
    uVar48 = puVar24[1];
    pcVar42 = (flatRuntime2->flatRuntimeBase).m_strBlob +
              (flatRuntime2->flatRuntimeBase).m_strOffs[puVar24[2]];
    if (object->m_argCount == 3) {
      Printf__8CGraphicFUlUlPce(&Graphic,uVar46,uVar48,pcVar42);
    }
    else {
      pcVar45 = local_284 + 1;
      local_184[0] = '\0';
      for (iVar8 = 0; iVar8 < object->m_argCount + -3; iVar8 = iVar8 + 1) {
        while( true ) {
          pcVar30 = local_284;
          iVar26 = 0;
          for (; (cVar3 = *pcVar42, cVar3 != '\0' &&
                 ((iVar26 == 0 || ((iVar26 != 0 && (cVar3 != '%')))))); pcVar42 = pcVar42 + 1) {
            *pcVar30 = cVar3;
            iVar26 = iVar26 + 1;
            pcVar30 = pcVar30 + 1;
          }
          local_284[iVar26] = '\0';
          if (local_284[0] == '%') break;
          strcat(local_184,local_284);
        }
        iVar26 = iVar8 + 3;
        puVar24 = object->m_localBase;
        pcVar30 = pcVar45;
        if (local_284[0] == '%') {
          iVar27 = 1;
          iVar25 = 0;
          uVar9 = countLeadingZeros(0x30 - local_284[1]);
          uVar9 = uVar9 >> 5 & 0xff;
          for (pcVar32 = pcVar45; (cVar3 = *pcVar32, '/' < cVar3 && (cVar3 < ':'));
              pcVar32 = pcVar32 + 1) {
            iVar27 = iVar27 + 1;
            iVar25 = (int)cVar3 + iVar25 * 10 + -0x30;
          }
          if (local_284[iVar27] != 'b') goto LAB_800b3794;
          pcVar30 = CStack_484.m_name + 0xfc;
          uVar33 = puVar24[iVar26];
          iVar34 = 0;
          iVar36 = 0;
          iVar26 = iVar25;
          if (0 < iVar25) {
            do {
              uVar31 = (int)uVar33 >> ((iVar25 - iVar36) - 1U & 0x3f) & 1;
              if ((uVar9 == 0) && (uVar31 != 0)) {
                uVar9 = 1;
              }
              if (uVar9 != 0) {
                iVar34 = iVar34 + 1;
                *pcVar30 = (char)uVar31 + '0';
                pcVar30 = pcVar30 + 1;
              }
              iVar36 = iVar36 + 1;
              iVar26 = iVar26 + -1;
            } while (iVar26 != 0);
          }
          (CStack_484.m_name + 0xfc)[iVar34] = '\0';
          strcat(CStack_484.m_name + 0xfc,local_284 + iVar27 + 1);
        }
        else {
LAB_800b3794:
          while (*pcVar30 != '\0') {
            switch(*pcVar30) {
            case 'd':
            case 'x':
              sprintf(CStack_484.m_name + 0xfc,local_284,puVar24[iVar26]);
              goto LAB_800b37a0;
            default:
              pcVar30 = pcVar30 + 1;
              break;
            case 'f':
              sprintf((double)(float)puVar24[iVar26],CStack_484.m_name + 0xfc,local_284);
              goto LAB_800b37a0;
            case 's':
              sprintf(CStack_484.m_name + 0xfc,local_284,
                      (flatRuntime2->flatRuntimeBase).m_strBlob +
                      (flatRuntime2->flatRuntimeBase).m_strOffs[puVar24[iVar26]]);
              goto LAB_800b37a0;
            }
          }
        }
LAB_800b37a0:
        strcat(local_184,CStack_484.m_name + 0xfc);
      }
      Printf__8CGraphicFUlUlPce(&Graphic,uVar46,uVar48,local_184);
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -7:
    dVar49 = (double)cosf__3stdFf((double)(float)*object->m_localBase);
    local_d04 = (float)dVar49;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,local_d04);
    *param_5 = 0;
    break;
  case -6:
    dVar49 = (double)sinf__3stdFf((double)(float)*object->m_localBase);
    local_d00 = (float)dVar49;
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,local_d00);
    *param_5 = 0;
    break;
  case -5:
    if ((1 << *object->m_localBase & *(uint *)&flatRuntime2->field_0x12a8) == 0) {
      uVar22 = GetButton__4CPadFl(&Pad);
    }
    else {
      uVar22 = 0;
    }
    uVar9 = GetDbgFlag__11CDbgMenuPcsFv(0x80306708);
    if ((uVar9 & 0x100) != 0) {
      uVar22 = uVar22 & 0xf3ff;
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,(int)(short)uVar22);
    *param_5 = 0;
    break;
  case -4:
    iVar8 = IsAbsolute__10CCameraPcsFv(&CameraPcs);
    if (iVar8 != 0) {
      puVar24 = object->m_localBase;
      local_a5c = *puVar24;
      local_a58 = puVar24[1];
      local_a54 = puVar24[2];
      if (flatRuntime2->field61766_0x10414 == 0) {
        SetRefPosition__10CCameraPcsFP3Vec(&CameraPcs,&local_a5c);
      }
      else {
        __as__3VecFRC3Vec(0x802e999c,&local_a5c);
      }
      puVar24 = object->m_localBase;
      local_a5c = puVar24[3];
      local_a58 = puVar24[4];
      local_a54 = puVar24[5];
      if (flatRuntime2->field61766_0x10414 == 0) {
        SetPosition__10CCameraPcsFP3Vec(&CameraPcs,&local_a5c);
      }
      else {
        __as__3VecFRC3Vec(0x802e9990,&local_a5c);
      }
      SetFromScript__10CCameraPcsFv(&CameraPcs);
    }
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,0);
    *param_5 = 0;
    break;
  case -3:
    uVar7 = getNumFreeObject__13CFlatRuntime2Fi(flatRuntime2,5);
    push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti(flatRuntime2,object,uVar7);
    *param_5 = 0;
    break;
  default:
    return 0;
  }
  return 1;
}

