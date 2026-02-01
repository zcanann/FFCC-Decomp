// Function: SetProjection__8CMenuPcsFi
// Entry: 800f67e0
// Size: 456 bytes

void SetProjection__8CMenuPcsFi(CMenuPcs *menuPcs,int param_2)

{
  Vec *targetPosition;
  undefined4 cameraUp;
  undefined4 *puVar1;
  int iVar2;
  undefined auStack_c8 [4];
  undefined4 local_c4;
  CVector CStack_c0;
  CVector CStack_b4;
  Mtx MStack_a8;
  Mat4x4 MStack_78;
  undefined4 local_38;
  uint uStack_34;
  undefined4 local_30;
  uint uStack_2c;
  undefined4 local_28;
  uint uStack_24;
  undefined4 local_20;
  uint uStack_1c;
  
  iVar2 = *(int *)&menuPcs->field_0x814 + param_2 * 0x50;
  C_MTXPerspective(FLOAT_80331470,FLOAT_80331474,FLOAT_80331478,FLOAT_8033147c,(Mtx *)&MStack_78);
  GXSetProjection(&MStack_78,0);
  PSMTX44Copy(&MStack_78,&CameraPcs.m_screenMatrix);
  targetPosition =
       (Vec *)__ct__7CVectorFfff(FLOAT_803313dc,FLOAT_803313dc,FLOAT_803313dc,&CStack_c0);
  cameraUp = __ct__7CVectorFfff(FLOAT_803313dc,FLOAT_803313e8,FLOAT_803313dc,&CStack_b4);
  C_MTXLookAt(&MStack_a8,(Vec *)(iVar2 + 0x10),cameraUp,targetPosition);
  PSMTXCopy(&CameraPcs.m_cameraMatrix,&menuPcs->m_cameraMatrix);
  PSMTXCopy(&MStack_a8,&CameraPcs.m_cameraMatrix);
  InitEnv__9CCharaPcsFi(&CharaPcs,5);
  GXSetColorUpdate(0);
  GXSetAlphaUpdate(0);
  puVar1 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_c8,0,0,0,0);
  local_c4 = *puVar1;
  GXSetCopyClear(&local_c4,0xffffff);
  GXSetColorUpdate(1);
  GXSetAlphaUpdate(1);
  uStack_34 = (int)*(short *)(iVar2 + 8) ^ 0x80000000;
  uStack_2c = (int)*(short *)(iVar2 + 10) ^ 0x80000000;
  uStack_24 = (int)*(short *)(iVar2 + 0xc) ^ 0x80000000;
  uStack_1c = (int)*(short *)(iVar2 + 0xe) ^ 0x80000000;
  local_38 = 0x43300000;
  local_30 = 0x43300000;
  local_28 = 0x43300000;
  local_20 = 0x43300000;
  GXSetViewport((double)(float)((double)CONCAT44(0x43300000,uStack_34) - DOUBLE_80331408),
                (double)(float)((double)CONCAT44(0x43300000,uStack_2c) - DOUBLE_80331408),
                (double)(float)((double)CONCAT44(0x43300000,uStack_24) - DOUBLE_80331408),
                (double)(float)((double)CONCAT44(0x43300000,uStack_1c) - DOUBLE_80331408),
                (double)FLOAT_803313dc,(double)FLOAT_803313e8);
  GXSetScissor(*(undefined4 *)(iVar2 + 0x40),*(undefined4 *)(iVar2 + 0x44),
               *(undefined4 *)(iVar2 + 0x48),*(undefined4 *)(iVar2 + 0x4c));
  return;
}

