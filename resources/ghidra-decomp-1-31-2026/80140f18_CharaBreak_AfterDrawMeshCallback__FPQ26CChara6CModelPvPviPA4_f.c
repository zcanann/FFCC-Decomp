// Function: CharaBreak_AfterDrawMeshCallback__FPQ26CChara6CModelPvPviPA4_f
// Entry: 80140f18
// Size: 708 bytes

void CharaBreak_AfterDrawMeshCallback__FPQ26CChara6CModelPvPviPA4_f
               (int param_1,int param_2,undefined4 param_3,int param_4,Mtx *param_5)

{
  undefined2 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  Mtx MStack_98;
  Mtx MStack_68;
  
  if (*(int *)(param_2 + 0x44) != 0) {
    iVar7 = *(int *)(param_1 + 0xac) + param_4 * 0x14;
    iVar3 = *(int *)(iVar7 + 8);
    iVar6 = *(int *)(iVar3 + 0x50);
    PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_68);
    iVar5 = *(int *)(iVar3 + 0x4c) + -1;
    iVar3 = iVar5 * 4;
    for (; -1 < iVar5; iVar5 = iVar5 + -1) {
      iVar8 = *(int *)(param_4 * 4 + *(int *)(param_2 + 0x1c));
      iVar4 = *(int *)(*(int *)(iVar8 + iVar3) + 0xc);
      SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale
                (&MaterialMan,*(CMaterialSet **)(*(int *)(param_1 + 0xa4) + 0x24),
                 (uint)*(ushort *)(iVar6 + 8),0,0);
      GXSetZMode(1,3,1);
      GXSetCullMode(0);
      GXClearVtxDesc();
      GXSetVtxDesc(9,1);
      GXSetVtxDesc(10,3);
      GXSetVtxDesc(0xb,3);
      GXSetVtxDesc(0xd,3);
      GXSetVtxDesc(0xe,3);
      GXSetVtxAttrFmt(7,9,1,3,*(uint *)(*(int *)(param_1 + 0xa4) + 0x34) & 0xff);
      GXSetVtxAttrFmt(7,10,0,3,*(uint *)(*(int *)(param_1 + 0xa4) + 0x38) & 0xff);
      GXSetVtxAttrFmt(7,0xb,1,5,0);
      GXSetVtxAttrFmt(7,0xd,1,3,0xc);
      GXSetVtxAttrFmt(7,0xe,1,3,0xc);
      if (*(int *)(*(int *)(iVar7 + 8) + 0x54) == 0) {
        GXLoadPosMtxImm(&MStack_68,0);
      }
      else {
        PSMTXConcat(&MStack_68,param_5,&MStack_98);
        GXLoadPosMtxImm(&MStack_98,0);
      }
      GXBegin(0x90,7,*(short *)(*(int *)(iVar8 + iVar3) + 8) * 3);
      iVar2 = 0;
      while (iVar2 < (int)(uint)*(ushort *)(*(int *)(iVar8 + iVar3) + 8)) {
        iVar2 = iVar2 + 1;
        DAT_cc008000._0_2_ = *(undefined2 *)(iVar4 + 0x10);
        DAT_cc008000._0_2_ = *(undefined2 *)(iVar4 + 0x12);
        DAT_cc008000._0_2_ = *(undefined2 *)(iVar4 + 0x14);
        DAT_cc008000._0_2_ = *(undefined2 *)(iVar4 + 0x28);
        DAT_cc008000._0_2_ = 0;
        DAT_cc008000._0_2_ = *(undefined2 *)(iVar4 + 0x2e);
        DAT_cc008000._0_2_ = *(undefined2 *)(iVar4 + 0x2e);
        DAT_cc008000._0_2_ = *(undefined2 *)(iVar4 + 0x16);
        DAT_cc008000._0_2_ = *(undefined2 *)(iVar4 + 0x18);
        DAT_cc008000._0_2_ = *(undefined2 *)(iVar4 + 0x1a);
        DAT_cc008000._0_2_ = *(undefined2 *)(iVar4 + 0x2a);
        DAT_cc008000._0_2_ = 0;
        DAT_cc008000._0_2_ = *(undefined2 *)(iVar4 + 0x30);
        DAT_cc008000._0_2_ = *(undefined2 *)(iVar4 + 0x30);
        DAT_cc008000._0_2_ = *(undefined2 *)(iVar4 + 0x1c);
        DAT_cc008000._0_2_ = *(undefined2 *)(iVar4 + 0x1e);
        DAT_cc008000._0_2_ = *(undefined2 *)(iVar4 + 0x20);
        DAT_cc008000._0_2_ = *(undefined2 *)(iVar4 + 0x2c);
        DAT_cc008000._0_2_ = 0;
        DAT_cc008000._0_2_ = *(undefined2 *)(iVar4 + 0x32);
        puVar1 = (undefined2 *)(iVar4 + 0x32);
        iVar4 = iVar4 + 0x34;
        DAT_cc008000._0_2_ = *puVar1;
      }
      iVar3 = iVar3 + -4;
      iVar6 = iVar6 + 0xc;
    }
  }
  return;
}

