// Function: Draw__13CFlatRuntime2Fv
// Entry: 8006b7b8
// Size: 2124 bytes

/* WARNING: Removing unreachable block (ram,0x8006bfe8) */
/* WARNING: Removing unreachable block (ram,0x8006bfe0) */
/* WARNING: Removing unreachable block (ram,0x8006bfd8) */
/* WARNING: Removing unreachable block (ram,0x8006bfd0) */
/* WARNING: Removing unreachable block (ram,0x8006bfc8) */
/* WARNING: Removing unreachable block (ram,0x8006b7e8) */
/* WARNING: Removing unreachable block (ram,0x8006b7e0) */
/* WARNING: Removing unreachable block (ram,0x8006b7d8) */
/* WARNING: Removing unreachable block (ram,0x8006b7d0) */
/* WARNING: Removing unreachable block (ram,0x8006b7c8) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void Draw__13CFlatRuntime2Fv(CFlatRuntime2 *flatRuntime2)

{
  float *pfVar1;
  float *pfVar2;
  byte bVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  uint uVar7;
  float *pfVar8;
  CFlatRuntime2 *pCVar9;
  CGObject *gObject;
  CObject *gItemObj;
  int iVar10;
  byte *pbVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  undefined4 local_1f8;
  undefined4 local_1f4;
  undefined auStack_1f0 [4];
  undefined4 local_1ec;
  undefined local_1e8;
  undefined uStack_1e7;
  undefined uStack_1e6;
  undefined uStack_1e5;
  undefined local_1e4;
  undefined local_1e3;
  undefined local_1e2;
  undefined local_1e1;
  undefined local_1e0;
  undefined local_1df;
  undefined local_1de;
  undefined local_1dd;
  undefined4 local_1dc;
  Vec VStack_1d8;
  Vec local_1cc;
  Mtx MStack_1c0;
  Mtx MStack_190;
  Mat4x4 MStack_160;
  Mat4x4 MStack_120;
  float local_e0 [24];
  undefined4 local_80;
  uint uStack_7c;
  
  uVar5 = MenuPcs._248_4_;
  SetScale__5CFontFf(FLOAT_80330180,(CFont *)MenuPcs._248_4_);
  SetShadow__5CFontFi((CFont *)uVar5,1);
  SetMargin__5CFontFf(FLOAT_80330140,(CFont *)uVar5);
  SetZMode__5CFontFii((CFont *)uVar5,0,0);
  DrawInit__5CFontFv((CFont *)uVar5);
  SetTlut__5CFontFi((CFont *)uVar5,7);
  puVar6 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_1f0,0xff,0xff,0xff,0xff);
  local_1ec = *puVar6;
  SetColor__5CFontF8_GXColor((CFont *)uVar5,&local_1ec);
  for (gObject = (CGObject *)((flatRuntime2->flatRuntimeBase).m_objRoot.m_next)->m_next;
      gObject != (CGObject *)&(flatRuntime2->flatRuntimeBase).m_objRoot;
      gObject = (CGObject *)(gObject->base_object).object.m_next) {
    if (-1 < (gObject->base_object).object.m_classIndex) {
      bVar3 = (gObject->base_object).object.m_flags;
      if (((-1 < (int)((uint)bVar3 << 0x18)) &&
          (-1 < (int)((uint)bVar3 << 0x19 | (uint)(bVar3 >> 7)))) &&
         (uVar7 = (**(code **)((int)(gObject->base_object).object.m_vtable + 0xc))(gObject),
         (uVar7 & 5) == 5)) goto LAB_8006b8ec;
    }
  }
  gObject = (CGObject *)0x0;
LAB_8006b8ec:
LAB_8006b978:
  if (gObject != (CGObject *)0x0) {
    DrawDebug__8CGObjectFP5CFont(gObject,(CFont *)uVar5);
    for (gObject = (CGObject *)(gObject->base_object).object.m_next;
        gObject != (CGObject *)&(flatRuntime2->flatRuntimeBase).m_objRoot;
        gObject = (CGObject *)(gObject->base_object).object.m_next) {
      if (-1 < (gObject->base_object).object.m_classIndex) {
        bVar3 = (gObject->base_object).object.m_flags;
        if (((-1 < (int)((uint)bVar3 << 0x18)) &&
            (-1 < (int)((uint)bVar3 << 0x19 | (uint)(bVar3 >> 7)))) &&
           (uVar7 = (**(code **)((int)(gObject->base_object).object.m_vtable + 0xc))(gObject),
           (uVar7 & 5) == 5)) goto LAB_8006b978;
      }
    }
    gObject = (CGObject *)0x0;
    goto LAB_8006b978;
  }
  SetZMode__5CFontFii((CFont *)uVar5,0,0);
  SetPosZ__5CFontFf(FLOAT_80330144,(CFont *)uVar5);
  PSMTX44Copy(&CameraPcs.m_screenMatrix,&MStack_120);
  GXSetProjection(&MStack_120,0);
  uVar5 = MenuPcs._248_4_;
  SetScale__5CFontFf(FLOAT_80330184,(CFont *)MenuPcs._248_4_);
  SetShadow__5CFontFi((CFont *)uVar5,1);
  SetMargin__5CFontFf(FLOAT_80330140,(CFont *)uVar5);
  SetZMode__5CFontFii((CFont *)uVar5,1,1);
  DrawInit__5CFontFv((CFont *)uVar5);
  for (gItemObj = ((flatRuntime2->flatRuntimeBase).m_objRoot.m_next)->m_next;
      gItemObj != &(flatRuntime2->flatRuntimeBase).m_objRoot; gItemObj = gItemObj->m_next) {
    if (-1 < gItemObj->m_classIndex) {
      bVar3 = gItemObj->m_flags;
      if (((-1 < (int)((uint)bVar3 << 0x18)) &&
          (-1 < (int)((uint)bVar3 << 0x19 | (uint)(bVar3 >> 7)))) &&
         (uVar7 = (**(code **)((int)gItemObj->m_vtable + 0xc))(gItemObj), (uVar7 & 0x1d) == 0x1d))
      goto LAB_8006ba78;
    }
  }
  gItemObj = (CObject *)0x0;
LAB_8006ba78:
LAB_8006bb04:
  do {
    if (gItemObj == (CObject *)0x0) {
      SetZMode__5CFontFii((CFont *)uVar5,0,0);
      SetPosZ__5CFontFf(FLOAT_80330144,(CFont *)uVar5);
      PSMTX44Copy(&CameraPcs.m_screenMatrix,&MStack_160);
      GXSetProjection(&MStack_160,0);
      PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_190);
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
      if ((*(uint *)&flatRuntime2->field_0x129c & 0x20000) != 0) {
        local_1dc = 0xff8080ff;
        local_1f4 = 0xff8080ff;
        GXSetChanMatColor(4,&local_1f4);
        GXLoadPosMtxImm(&MStack_190,0);
        uVar7 = 0;
        pCVar9 = flatRuntime2;
        do {
          Draw__9CLine<64>Fv(&pCVar9->field_0x1bdc);
          uVar7 = uVar7 + 1;
          pCVar9 = (CFlatRuntime2 *)((pCVar9->flatRuntimeBase).m_freeNodes + 0x17c);
        } while (uVar7 < 0x10);
      }
      if ((((*(uint *)&flatRuntime2->field_0x129c & 0x200000) != 0) ||
          ((MiniGamePcs._25732_4_ & 0x80) != 0)) && (*(int *)&flatRuntime2->field_0xcd1c != 0)) {
        local_1e0 = 0x80;
        pbVar11 = &flatRuntime2->field_0xcd20;
        dVar15 = (double)FLOAT_80330190;
        local_1df = 0xff;
        local_1de = 0x80;
        dVar17 = (double)FLOAT_80330188;
        local_1dd = 0xff;
        local_1e4 = 0x80;
        local_1e3 = 0x80;
        local_1e2 = 0xff;
        local_1e1 = 0xff;
        local_1e8 = 0xff;
        uStack_1e7 = 0;
        uStack_1e6 = 0;
        uStack_1e5 = 0xff;
        dVar16 = DOUBLE_80330160;
        for (iVar10 = 0; iVar10 < *(int *)&flatRuntime2->field_0xcd1c; iVar10 = iVar10 + 1) {
          bVar3 = *pbVar11;
          if ((int)((uint)bVar3 << 0x19 | (uint)(bVar3 >> 7)) < 0) {
            puVar6 = (undefined4 *)&local_1e8;
          }
          else {
            puVar6 = (undefined4 *)&local_1e0;
            if ((int)((uint)bVar3 << 0x18) < 0) {
              puVar6 = (undefined4 *)&local_1e4;
            }
          }
          local_1f8 = *puVar6;
          GXSetChanMatColor(4,&local_1f8);
          dVar12 = (double)PSVECMag((Vec *)(pbVar11 + 0x10));
          PSMTXIdentity(&MStack_1c0);
          local_1cc.x = DAT_801d8f5c;
          local_1cc.y = DAT_801d8f60;
          local_1cc.z = DAT_801d8f64;
          PSVECNormalize((Vec *)(pbVar11 + 0x10),(Vec *)(pbVar11 + 0x10));
          dVar13 = (double)PSVECDotProduct(&local_1cc,(Vec *)(pbVar11 + 0x10));
          if (dVar13 < dVar17) {
            if ((double)FLOAT_8033018c <= dVar13) {
              dVar13 = (double)acos();
              dVar13 = (double)(float)dVar13;
              PSVECCrossProduct((Vec *)(pbVar11 + 0x10),&local_1cc,&VStack_1d8);
              PSMTXRotAxisRad((float)-dVar13,&MStack_1c0,&VStack_1d8);
            }
            else {
              dVar12 = -dVar12;
            }
          }
          MStack_1c0.value[0][3] = *(float *)(pbVar11 + 4);
          MStack_1c0.value[1][3] = *(float *)(pbVar11 + 8);
          MStack_1c0.value[2][3] = *(float *)(pbVar11 + 0xc);
          PSMTXConcat(&MStack_190,&MStack_1c0,&MStack_1c0);
          GXLoadPosMtxImm(&MStack_1c0,0);
          GXBegin(0xa8,0,0x20);
          uVar7 = 0;
          pfVar8 = local_e0;
          do {
            uStack_7c = uVar7 ^ 0x80000000;
            local_80 = 0x43300000;
            dVar14 = (double)(float)(dVar15 * (double)(float)((double)CONCAT44(0x43300000,uStack_7c)
                                                             - dVar16));
            dVar13 = (double)sin(dVar14);
            *pfVar8 = *(float *)(pbVar11 + 0x1c) * (float)dVar13;
            dVar13 = (double)cos(dVar14);
            bVar3 = *pbVar11;
            pfVar8[1] = *(float *)(pbVar11 + 0x1c) * (float)dVar13;
            pfVar8[2] = (float)dVar12;
            if ((int)((uint)bVar3 << 0x18) < 0) {
              DAT_cc008000 = *pfVar8;
              DAT_cc008000 = pfVar8[1];
              DAT_cc008000 = FLOAT_80330144;
            }
            else {
              DAT_cc008000 = FLOAT_80330144;
              DAT_cc008000 = FLOAT_80330144;
              DAT_cc008000 = FLOAT_80330144;
            }
            uVar7 = uVar7 + 1;
            pfVar1 = pfVar8 + 1;
            DAT_cc008000 = *pfVar8;
            pfVar2 = pfVar8 + 2;
            pfVar8 = pfVar8 + 3;
            DAT_cc008000 = *pfVar1;
            DAT_cc008000 = *pfVar2;
          } while ((int)uVar7 < 8);
          uVar7 = 0;
          pfVar8 = local_e0;
          do {
            uStack_7c = uVar7 ^ 0x80000000;
            local_80 = 0x43300000;
            dVar14 = (double)(float)(dVar15 * (double)(float)((double)CONCAT44(0x43300000,uStack_7c)
                                                             - dVar16));
            dVar13 = (double)sin(dVar14);
            *pfVar8 = *(float *)(pbVar11 + 0x1c) * (float)dVar13;
            dVar13 = (double)cos(dVar14);
            uVar4 = uVar7 + 1 & 7;
            uVar7 = uVar7 + 1;
            pfVar8[1] = *(float *)(pbVar11 + 0x1c) * (float)dVar13;
            pfVar8[2] = (float)dVar12;
            pfVar1 = pfVar8 + 1;
            DAT_cc008000 = *pfVar8;
            pfVar2 = pfVar8 + 2;
            pfVar8 = pfVar8 + 3;
            DAT_cc008000 = *pfVar1;
            DAT_cc008000 = *pfVar2;
            DAT_cc008000 = local_e0[uVar4 * 3];
            DAT_cc008000 = local_e0[uVar4 * 3 + 1];
            DAT_cc008000 = local_e0[uVar4 * 3 + 2];
          } while ((int)uVar7 < 8);
          pbVar11 = pbVar11 + 0x20;
        }
      }
      return;
    }
    DrawOmoideName__9CGItemObjFP5CFont((CGItemObj *)gItemObj,uVar5);
    for (gItemObj = gItemObj->m_next; gItemObj != &(flatRuntime2->flatRuntimeBase).m_objRoot;
        gItemObj = gItemObj->m_next) {
      if (-1 < gItemObj->m_classIndex) {
        bVar3 = gItemObj->m_flags;
        if (((-1 < (int)((uint)bVar3 << 0x18)) &&
            (-1 < (int)((uint)bVar3 << 0x19 | (uint)(bVar3 >> 7)))) &&
           (uVar7 = (**(code **)((int)gItemObj->m_vtable + 0xc))(gItemObj), (uVar7 & 0x1d) == 0x1d))
        goto LAB_8006bb04;
      }
    }
    gItemObj = (CObject *)0x0;
  } while( true );
}

