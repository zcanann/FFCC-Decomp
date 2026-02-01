// Function: Mana_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f
// Entry: 800d79f4
// Size: 1280 bytes

/* WARNING: Removing unreachable block (ram,0x800d7a58) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void Mana_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f
               (CModel *model,int *param_2,int param_3,int param_4,int param_5,Mtx *param_6)

{
  byte bVar1;
  bool bVar2;
  float fVar3;
  int iVar4;
  CDisplayList *pCVar5;
  int iVar6;
  CMeshCRefData *pCVar7;
  Mtx MStack_128;
  Mtx MStack_f8;
  Mtx MStack_c8;
  Mtx MStack_98;
  Mtx MStack_68;
  longlong local_38;
  
  bVar2 = false;
  bVar1 = *(byte *)(param_3 + 0x1c);
  iVar6 = *param_2;
  pCVar7 = model->m_meshes[param_4].m_data;
  pCVar5 = pCVar7->m_displayLists + param_5;
  if (bVar1 == 2) {
    iVar4 = strcmp(pCVar7,&DAT_80330ebc);
    if ((iVar4 == 0) || (iVar4 = strcmp(pCVar7,&DAT_80330e90), iVar4 == 0)) {
      bVar2 = true;
    }
  }
  else if (bVar1 < 2) {
    if (bVar1 == 0) {
      iVar4 = strcmp(pCVar7,&DAT_80330ebc);
      if (iVar4 == 0) {
        bVar2 = true;
      }
    }
    else {
      iVar4 = strcmp(pCVar7,&DAT_80330ebc);
      if ((iVar4 == 0) || (iVar4 = strcmp(pCVar7,&DAT_80330e88), iVar4 == 0)) {
        bVar2 = true;
      }
    }
  }
  else if ((bVar1 < 4) &&
          ((iVar4 = strcmp(pCVar7,&DAT_80330ebc), iVar4 == 0 ||
           (iVar4 = strcmp(pCVar7,&DAT_80330e98), iVar4 == 0)))) {
    bVar2 = true;
  }
  iVar4 = strcmp(pCVar7,&DAT_80330ea0);
  if (((iVar4 == 0) && (*(char *)(param_3 + 0x1c) == '\x01')) ||
     ((iVar4 = strcmp(pCVar7,&DAT_80330ea8), iVar4 == 0 && (*(char *)(param_3 + 0x1c) == '\x02'))))
  {
    PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_98);
    PSMTXCopy(param_6,(Mtx *)(param_2 + 0x22));
    GXSetZMode(1,3,0);
    GXSetCullMode(0);
    PSMTXRotRad(FLOAT_80330e48,&MStack_128,0x78);
    PSMTXRotRad(FLOAT_80330e48,&MStack_f8,0x7a);
    PSMTXIdentity(&MStack_68);
    MStack_68.value[1][3] = -*(float *)(param_3 + 0x30);
    PSMTXConcat(&MStack_f8,&MStack_68,&MStack_68);
    PSMTXConcat(&MStack_128,&MStack_68,&MStack_68);
    PSMTXConcat(param_6,&MStack_68,&MStack_68);
    PSMTXConcat(&MStack_98,&MStack_68,&MStack_c8);
    GXLoadPosMtxImm(&MStack_c8,0);
    RenderWaterMesh__FP7VYmMana(param_2);
  }
  if (bVar2) {
    if ((bVar2) && (iVar4 = strcmp(pCVar7,&DAT_80330ebc), iVar4 != 0)) {
      PSMTXCopy(param_6,(Mtx *)(param_2 + 0x2e));
      if (*(char *)(param_2 + 0x3d) != '\0') {
        *(uint8_t *)(param_2 + 0xe) = *pCVar7->m_colors;
        *(uint8_t *)((int)param_2 + 0x39) = pCVar7->m_colors[1];
        *(uint8_t *)((int)param_2 + 0x3a) = pCVar7->m_colors[2];
        *(undefined *)((int)param_2 + 0x3b) = 0x80;
        DCFlushRange(param_2 + 0xe,4);
        GXSetArray(0xb,param_2[0x1a],4);
        GXSetArray(0xd,param_2[0x1b],4);
        GXSetArray(0xe,param_2[0x1c],4);
        MaterialMan._8_4_ = param_2[0x19];
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
        MaterialMan._72_4_ = 0xaee0f;
        MaterialMan._296_4_ = 0;
        MaterialMan._300_4_ = 0x1e;
        MaterialMan._304_4_ = 0;
        MaterialMan._64_4_ = 0xaee0f;
        MaterialMan._208_4_ = param_2[10];
        MaterialMan._220_4_ = param_2[0xb];
        GXSetCullMode(1);
        GXSetZMode(1,3,0);
        SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale
                  (&MaterialMan,model->m_data->m_materialSet,(uint)pCVar5->m_material,0,0);
        SetEnvMap__FP7PYmManaP7VYmMana(param_3,param_2);
        GXCallDisplayList(*(undefined4 *)(param_2[0x18] + param_5 * 4),pCVar5->m_size);
        iVar6 = 0;
        do {
          GXSetTevKColorSel(iVar6,6);
          GXSetTevKAlphaSel(iVar6,0);
          iVar6 = iVar6 + 1;
        } while (iVar6 < 0x10);
      }
    }
    else {
      iVar4 = strcmp(pCVar7,&DAT_80330ebc);
      if (iVar4 == 0) {
        if (Game.game.m_currentMapId == 0x21) {
          fVar3 = FLOAT_80330ec0 * *(float *)(iVar6 + 0x4b0);
          *(undefined *)(param_2 + 0x40) = 0xff;
          *(undefined *)((int)param_2 + 0x101) = 0xff;
          iVar6 = (int)fVar3;
          local_38 = (longlong)iVar6;
          *(undefined *)((int)param_2 + 0x102) = 0xff;
          *(char *)((int)param_2 + 0x103) = (char)iVar6;
        }
        else {
          *(undefined *)(param_2 + 0x40) = *(undefined *)(param_3 + 0x3c);
          *(undefined *)((int)param_2 + 0x101) = *(undefined *)(param_3 + 0x3d);
          *(undefined *)((int)param_2 + 0x102) = *(undefined *)(param_3 + 0x3e);
          *(undefined *)((int)param_2 + 0x103) = 0xff;
          if (*(char *)(param_3 + 0x3c) == '\0') {
            *(undefined *)(param_2 + 0x40) = 0xff;
          }
          if (*(char *)(param_3 + 0x3d) == '\0') {
            *(undefined *)((int)param_2 + 0x101) = 0xff;
          }
          if (*(char *)(param_3 + 0x3e) == '\0') {
            *(undefined *)((int)param_2 + 0x102) = 0xff;
          }
        }
        GXSetZMode(1,3,1);
        DCFlushRange(param_2 + 0x40,4);
        GXSetArray(0xb,param_2 + 0x40,4);
        SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale
                  (&MaterialMan,model->m_data->m_materialSet,(uint)pCVar5->m_material,0,0);
        _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(0,4,1,0xf);
        GXCallDisplayList(pCVar5->m_data,pCVar5->m_size);
      }
    }
  }
  return;
}

