// Function: DrawDiaryMenu__8CMenuPcsFv
// Entry: 800fb440
// Size: 1232 bytes

/* WARNING: Removing unreachable block (ram,0x800fb8e8) */
/* WARNING: Removing unreachable block (ram,0x800fb8e0) */
/* WARNING: Removing unreachable block (ram,0x800fb8d8) */
/* WARNING: Removing unreachable block (ram,0x800fb460) */
/* WARNING: Removing unreachable block (ram,0x800fb458) */
/* WARNING: Removing unreachable block (ram,0x800fb450) */

void DrawDiaryMenu__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  short sVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  Vec *targetPosition;
  undefined4 cameraUp;
  undefined4 *puVar5;
  uint uVar6;
  int iVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  undefined4 local_140;
  undefined4 local_13c;
  undefined4 local_138;
  undefined4 local_134;
  undefined auStack_130 [4];
  CVector CStack_12c;
  CVector CStack_120;
  Mat4x4 MStack_114;
  Mat4x4 MStack_d4;
  Mtx MStack_94;
  undefined4 local_60;
  uint uStack_5c;
  undefined8 local_58;
  undefined4 local_50;
  uint uStack_4c;
  undefined4 local_48;
  uint uStack_44;
  
  fVar3 = FLOAT_80331474;
  fVar2 = FLOAT_80331470;
  *(float *)(*(int *)(*(int *)&menuPcs->field_0x778 + 0x168) + 0x9c) = FLOAT_803313e8;
  iVar7 = *(int *)&menuPcs->field_0x814;
  C_MTXPerspective(fVar2,fVar3,FLOAT_80331478,FLOAT_8033147c,(Mtx *)&MStack_d4);
  GXSetProjection(&MStack_d4,0);
  PSMTX44Copy(&MStack_d4,&CameraPcs.m_screenMatrix);
  targetPosition =
       (Vec *)__ct__7CVectorFfff(FLOAT_803313dc,FLOAT_803313dc,FLOAT_803313dc,&CStack_120);
  cameraUp = __ct__7CVectorFfff(FLOAT_803313dc,FLOAT_803313e8,FLOAT_803313dc,&CStack_12c);
  C_MTXLookAt(&MStack_94,(Vec *)(iVar7 + 0x60),cameraUp,targetPosition);
  PSMTXCopy(&CameraPcs.m_cameraMatrix,&menuPcs->m_cameraMatrix);
  PSMTXCopy(&MStack_94,&CameraPcs.m_cameraMatrix);
  InitEnv__9CCharaPcsFi(&CharaPcs,5);
  GXSetColorUpdate(0);
  GXSetAlphaUpdate(0);
  puVar5 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_130,0,0,0,0);
  local_134 = *puVar5;
  GXSetCopyClear(&local_134,0xffffff);
  GXSetColorUpdate(1);
  GXSetAlphaUpdate(1);
  uStack_5c = (int)*(short *)(iVar7 + 0x58) ^ 0x80000000;
  uStack_4c = (int)*(short *)(iVar7 + 0x5c) ^ 0x80000000;
  uStack_44 = (int)*(short *)(iVar7 + 0x5e) ^ 0x80000000;
  local_60 = 0x43300000;
  local_58 = (double)CONCAT44(0x43300000,(int)*(short *)(iVar7 + 0x5a) ^ 0x80000000);
  local_50 = 0x43300000;
  local_48 = 0x43300000;
  GXSetViewport((double)(float)((double)CONCAT44(0x43300000,uStack_5c) - DOUBLE_80331408),
                (double)(float)(local_58 - DOUBLE_80331408),
                (double)(float)((double)CONCAT44(0x43300000,uStack_4c) - DOUBLE_80331408),
                (double)(float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_80331408),
                (double)FLOAT_803313dc,(double)FLOAT_803313e8);
  GXSetScissor(*(undefined4 *)(iVar7 + 0x90),*(undefined4 *)(iVar7 + 0x94),
               *(undefined4 *)(iVar7 + 0x98),*(undefined4 *)(iVar7 + 0x9c));
  Draw__Q29CCharaPcs7CHandleFi(*(undefined4 *)&menuPcs->field_0x778,5);
  PSMTXCopy(&menuPcs->m_cameraMatrix,&CameraPcs.m_cameraMatrix);
  local_138 = DAT_802381a7;
  GXSetCopyClear(&local_138,0xffffff);
  PSMTX44Copy(&CameraPcs.m_screenMatrix,&MStack_114);
  GXSetProjection(&MStack_114,0);
  SetViewport__8CGraphicFv(&Graphic);
  GXSetScissor(0,0,0x280,0x1c0);
  DrawInit__8CMenuPcsFv(menuPcs);
  iVar7 = *(int *)&menuPcs->field_0x82c;
  sVar1 = *(short *)(iVar7 + 0x10);
  if ((0 < sVar1) && (sVar1 < 4)) {
    if (sVar1 == 1) {
      local_48 = 0x43300000;
      uStack_44 = (int)*(short *)(iVar7 + 0x22) ^ 0x80000000;
      dVar8 = (double)(float)(DOUBLE_803314e8 *
                             ((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_80331408));
    }
    else if (sVar1 == 2) {
      dVar8 = (double)FLOAT_803313e8;
    }
    else {
      local_48 = 0x43300000;
      uStack_44 = (int)*(short *)(iVar7 + 0x22) ^ 0x80000000;
      dVar8 = (double)(float)-(DOUBLE_803314e8 *
                               ((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_80331408) -
                              DOUBLE_80331420);
    }
    DrawDiaryBase__8CMenuPcsFif(dVar8,menuPcs,0);
  }
  DrawInit__8CMenuPcsFv(menuPcs);
  local_48 = 0x43300000;
  iVar7 = (int)System.m_frameCounter / 0x14 + ((int)System.m_frameCounter >> 0x1f);
  dVar8 = (double)(float)(DOUBLE_80331438 - (double)FLOAT_80331440);
  dVar9 = (double)FLOAT_80331444;
  uVar6 = (System.m_frameCounter + (iVar7 - (iVar7 >> 0x1f)) * -0x14) - 10;
  uVar4 = (int)uVar6 >> 0x1f;
  uVar4 = (uVar4 ^ uVar6) - uVar4;
  uStack_44 = uVar4 ^ 0x80000000;
  dVar10 = (double)(float)(DOUBLE_80331450 *
                           ((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_80331408) +
                          DOUBLE_80331448);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  uStack_4c = uVar4 ^ 0x80000000;
  local_50 = 0x43300000;
  iVar7 = (int)(FLOAT_80331458 *
               (float)(DOUBLE_80331460 * ((double)CONCAT44(0x43300000,uStack_4c) - DOUBLE_80331408)
                      + DOUBLE_803313f8));
  local_58 = (double)(longlong)iVar7;
  local_140 = CONCAT31(0xffffff,(char)iVar7);
  local_13c = local_140;
  GXSetChanMatColor(4,&local_13c);
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x2b);
  dVar8 = (double)(float)(-(double)(float)((double)FLOAT_80331468 * dVar10 - (double)FLOAT_80331468)
                          * DOUBLE_803313f8 + dVar8);
  dVar9 = (double)(float)(-(double)(float)((double)FLOAT_80331440 * dVar10 - (double)FLOAT_80331440)
                          * DOUBLE_803313f8 + dVar9);
  if ((menuPcs->field_0xf & 2) != 0) {
    DrawRect__8CMenuPcsFUlfffffffff(dVar8,dVar9,&MenuPcs,8);
  }
  if ((menuPcs->field_0xf & 1) != 0) {
    DrawRect__8CMenuPcsFUlfffffffff
              ((double)(float)(dVar8 + (double)FLOAT_8033146c),dVar9,(double)FLOAT_80331468,
               (double)FLOAT_80331440,(double)FLOAT_803313dc,(double)FLOAT_803313dc,dVar10,dVar10,
               &MenuPcs,0);
  }
  return;
}

