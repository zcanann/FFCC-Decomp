// Function: Draw__7CMapObjFUc
// Entry: 80029094
// Size: 820 bytes

void Draw__7CMapObjFUc(int param_1,char param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  undefined4 local_28;
  uint local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  if ((*(char *)(param_1 + 0x15) == param_2) && ((*(byte *)(param_1 + 0x18) & 4) != 0)) {
    local_1c = *(undefined4 *)(param_1 + 0xc4);
    local_18 = *(undefined4 *)(param_1 + 0xd4);
    local_14 = *(undefined4 *)(param_1 + 0xe4);
    SetPosition__9CLightPcsFQ29CLightPcs6TARGETP3VecUl
              (&LightPcs,1,&local_1c,*(undefined4 *)(param_1 + 0x38));
    MaterialMan._72_4_ = 0xace0f;
    MaterialMan._68_4_ = 0xffffffff;
    MaterialMan._76_1_ = 0xff;
    MaterialMan._296_4_ = 0;
    MaterialMan._284_4_ = 0;
    MaterialMan._300_4_ = 0x1e;
    MaterialMan._288_4_ = 0x1e;
    MaterialMan._304_4_ = 0;
    MaterialMan._292_4_ = 0;
    MaterialMan._517_1_ = 0xff;
    MaterialMan._518_1_ = 0xff;
    MaterialMan._88_4_ = 0;
    MaterialMan._92_4_ = 0;
    MaterialMan._520_1_ = 0;
    if (*(char *)(param_1 + 0x22) != '\0') {
      SetFullScreenShadow__10CCameraPcsFPA4_fl(&CameraPcs,param_1 + 0xb8,0);
    }
    if (*(int *)(param_1 + 0x3c) != 0) {
      SetShadowBound__12CMaterialManFQ210CMapShadow6TARGETP6CBoundPA4_f
                (&MaterialMan,1,*(int *)(param_1 + 0xc) + 0xc,param_1 + 0xb8);
    }
    MaterialMan._296_4_ = MaterialMan._284_4_;
    MaterialMan._300_4_ = MaterialMan._288_4_;
    MaterialMan._304_4_ = MaterialMan._292_4_;
    MaterialMan._64_4_ = MaterialMan._72_4_;
    DAT_8032e498 = CONCAT31(DAT_8032e498._0_3_,*(undefined *)(param_1 + 0x23));
    if (*(char *)(param_1 + 0x21) == '\0') {
      local_28 = CONCAT31(CONCAT21(CONCAT11(MapMng._141708_1_,MapMng._141709_1_),MapMng._141710_1_),
                          MapMng._141711_1_);
    }
    else {
      local_28 = *(uint *)(param_1 + 0xe8);
    }
    if (MapMng._141705_1_ != '\0') {
      local_28 = CONCAT31(CONCAT21(CONCAT11((char)((local_28 >> 0x18) *
                                                   (uint)(byte)MapMng._141712_1_ >> 8),
                                            (char)((local_28 >> 0x10 & 0xff) *
                                                   (uint)(byte)MapMng._141713_1_ >> 8)),
                                   (char)((local_28 >> 8 & 0xff) * (uint)(byte)MapMng._141714_1_ >>
                                         8)),
                          (char)((local_28 & 0xff) * (uint)(byte)MapMng._141715_1_ >> 8));
    }
    uVar4 = (uint)*(byte *)(param_1 + 0x24);
    if (uVar4 != 0xff) {
      uVar1 = local_28 >> 0x18;
      uVar2 = local_28 >> 0x10;
      uVar3 = local_28 >> 8;
      local_28 = CONCAT22(CONCAT11((char)(uVar1 * uVar4 >> 8),(char)((uVar2 & 0xff) * uVar4 >> 8)),
                          CONCAT11((char)((uVar3 & 0xff) * uVar4 >> 8),(undefined)local_28));
    }
    local_20 = DAT_8032e498;
    local_24 = local_28;
    SetMapColorAlpha__9CLightPcsFPA4_f8_GXColor8_GXColorUcfffUc
              ((double)*(float *)(param_1 + 0x44),(double)*(float *)(param_1 + 0x48),
               (double)*(float *)(param_1 + 0x54),&LightPcs,param_1 + 0xb8,&local_24,&local_20,
               *(undefined *)(param_1 + 0x26),*(short *)(param_1 + 0x28) >> 7 & 0xff);
    SetBumpTexMatirx__9CLightPcsFPA4_fPQ29CLightPcs10CBumpLightP3VecUc
              (&LightPcs,param_1 + 0xb8,*(undefined4 *)(param_1 + 0x10),param_1 + 0x58,
               *(undefined *)(param_1 + 0x1a));
    if (FLOAT_8032f944 != *(float *)(param_1 + 0x40)) {
      SetOffsetZBuff__10CCameraPcsFf(&CameraPcs);
    }
    if (*(char *)(param_1 + 0x27) != '\0') {
      GXSetZMode(1,3,0);
    }
    SetRenderArray__8CMapMeshFv(*(CMapMesh **)(param_1 + 0xc));
    Draw__8CMapMeshFP12CMaterialSet(*(CMapMesh **)(param_1 + 0xc),0);
    if (*(char *)(param_1 + 0x27) != '\0') {
      GXSetZMode(1,3,1);
    }
    if (FLOAT_8032f944 != *(float *)(param_1 + 0x40)) {
      SetOffsetZBuff__10CCameraPcsFf(&CameraPcs);
    }
  }
  return;
}

