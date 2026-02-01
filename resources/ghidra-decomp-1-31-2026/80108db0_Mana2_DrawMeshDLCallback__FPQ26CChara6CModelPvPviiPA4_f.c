// Function: Mana2_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f
// Entry: 80108db0
// Size: 1060 bytes

/* WARNING: Removing unreachable block (ram,0x801091b8) */
/* WARNING: Removing unreachable block (ram,0x801091b0) */
/* WARNING: Removing unreachable block (ram,0x801091a8) */
/* WARNING: Removing unreachable block (ram,0x80108e28) */
/* WARNING: Removing unreachable block (ram,0x80108dd0) */
/* WARNING: Removing unreachable block (ram,0x80108dc8) */
/* WARNING: Removing unreachable block (ram,0x80108dc0) */

void Mana2_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f
               (int param_1,int param_2,int param_3,int param_4,int param_5,Mtx *param_6)

{
  byte bVar1;
  bool bVar2;
  float fVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  Vec local_f8;
  Mtx MStack_ec;
  Mtx MStack_bc;
  Mtx MStack_8c;
  
  bVar1 = *(byte *)(param_3 + 0x1c);
  iVar6 = *(int *)(*(int *)(param_1 + 0xac) + param_4 * 0x14 + 8);
  bVar2 = false;
  puVar5 = (undefined4 *)(*(int *)(iVar6 + 0x50) + param_5 * 0xc);
  if (bVar1 == 2) {
    iVar4 = strcmp(iVar6,&DAT_80331900);
    if ((iVar4 == 0) || (iVar4 = strcmp(iVar6,&DAT_803318dc), iVar4 == 0)) {
      bVar2 = true;
    }
  }
  else if (bVar1 < 2) {
    if (bVar1 == 0) {
      iVar4 = strcmp(iVar6,&DAT_80331900);
      if (iVar4 == 0) {
        bVar2 = true;
      }
    }
    else {
      iVar4 = strcmp(iVar6,&DAT_80331900);
      if ((iVar4 == 0) || (iVar4 = strcmp(iVar6,&DAT_803318d4), iVar4 == 0)) {
        bVar2 = true;
      }
    }
  }
  else if ((bVar1 < 4) &&
          ((iVar4 = strcmp(iVar6,&DAT_80331900), iVar4 == 0 ||
           (iVar4 = strcmp(iVar6,&DAT_803318e4), iVar4 == 0)))) {
    bVar2 = true;
  }
  iVar4 = strcmp(iVar6,&DAT_803318ec);
  if (((iVar4 == 0) && (*(char *)(param_3 + 0x1c) == '\x01')) ||
     ((iVar4 = strcmp(iVar6,&DAT_803318f4), iVar4 == 0 && (*(char *)(param_3 + 0x1c) == '\x02')))) {
    PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_8c);
    PSMTXRotRad(FLOAT_80331904,&MStack_ec,0x7a);
    fVar3 = FLOAT_80331898;
    dVar9 = (double)param_6->value[0][3];
    dVar8 = (double)param_6->value[1][3];
    dVar7 = (double)param_6->value[2][3];
    param_6->value[0][3] = FLOAT_80331898;
    param_6->value[1][3] = fVar3;
    param_6->value[2][3] = fVar3;
    PSMTXConcat(param_6,&MStack_ec,param_6);
    local_f8.z = FLOAT_80331898;
    local_f8.x = FLOAT_80331898;
    local_f8.y = *(float *)(param_3 + 0x30);
    PSMTXMultVec(param_6,&local_f8,&local_f8);
    param_6->value[0][3] = (float)dVar9;
    param_6->value[1][3] = (float)(dVar8 - (double)local_f8.y);
    param_6->value[2][3] = (float)dVar7;
    PSMTXConcat(&MStack_8c,param_6,&MStack_bc);
    GXLoadPosMtxImm(&MStack_bc,0);
    PSMTXCopy(param_6,(Mtx *)(param_2 + 0x80));
    GXSetZMode(1,3,0);
    RenderWaterMesh__FP6VMana2(param_2);
    GXSetCullMode(1);
  }
  if (bVar2) {
    if ((bVar2) && (iVar4 = strcmp(iVar6,&DAT_80331900), iVar4 != 0)) {
      PSMTXCopy(param_6,(Mtx *)(param_2 + 0xb0));
      if (*(char *)(param_2 + 0xec) != '\0') {
        *(undefined *)(param_2 + 0x38) = **(undefined **)(iVar6 + 0x28);
        *(undefined *)(param_2 + 0x39) = *(undefined *)(*(int *)(iVar6 + 0x28) + 1);
        *(undefined *)(param_2 + 0x3a) = *(undefined *)(*(int *)(iVar6 + 0x28) + 2);
        *(undefined *)(param_2 + 0x3b) = 0x80;
        DCFlushRange(param_2 + 0x38,4);
        GXSetArray(0xb,*(undefined4 *)(param_2 + 0x68),4);
        GXSetArray(0xd,*(undefined4 *)(param_2 + 0x6c),4);
        MaterialMan._8_4_ = *(undefined4 *)(param_2 + 100);
        MaterialMan._68_4_ = 0xffffffff;
        MaterialMan._76_1_ = 0xff;
        MaterialMan._284_4_ = 0;
        MaterialMan._288_4_ = 0x1e;
        MaterialMan._292_4_ = 0;
        MaterialMan._517_1_ = 0xff;
        MaterialMan._518_1_ = 0xff;
        MaterialMan._88_4_ = 0;
        MaterialMan._92_4_ = 0;
        MaterialMan._520_1_ = 0;
        MaterialMan._72_4_ = 0x2ace0f;
        MaterialMan._296_4_ = 0;
        MaterialMan._300_4_ = 0x1e;
        MaterialMan._304_4_ = 0;
        MaterialMan._64_4_ = 0x2ace0f;
        MaterialMan._208_4_ = *(undefined4 *)(param_2 + 0x20);
        GXSetCullMode(1);
        GXSetZMode(1,3,0);
        SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale
                  (&MaterialMan,*(CMaterialSet **)(*(int *)(param_1 + 0xa4) + 0x24),
                   (uint)*(ushort *)(puVar5 + 2),0,0);
        GXCallDisplayList(*(undefined4 *)(*(int *)(param_2 + 0x60) + param_5 * 4),*puVar5);
      }
    }
    else {
      iVar6 = strcmp(iVar6,&DAT_80331900);
      if (iVar6 == 0) {
        GXSetZMode(1,3,1);
        SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale
                  (&MaterialMan,*(CMaterialSet **)(*(int *)(param_1 + 0xa4) + 0x24),
                   (uint)*(ushort *)(puVar5 + 2),0,0);
        GXCallDisplayList(puVar5[1],*puVar5);
      }
    }
  }
  return;
}

