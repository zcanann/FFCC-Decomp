// Function: DrawDebugStringDirect__8CGraphicFUlUlPcUl
// Entry: 80018a50
// Size: 416 bytes

CGraphic *
DrawDebugStringDirect__8CGraphicFUlUlPcUl
          (CGraphic *graphic,short param_2,short param_3,CGraphic *param_4,short param_5)

{
  char cVar1;
  short sVar2;
  short sVar3;
  CGraphic *pCVar4;
  uint uVar5;
  short sVar6;
  short sVar7;
  uint uVar8;
  
  if (param_4 != (CGraphic *)0x0) {
    GXClearVtxDesc();
    GXSetVtxDesc(9,1);
    GXSetVtxDesc(0xd,1);
    GXSetVtxAttrFmt(0,9,1,3,0);
    graphic = (CGraphic *)GXSetVtxAttrFmt(0,0xd,1,3,1);
    uVar8 = 0;
    pCVar4 = param_4;
    while( true ) {
      while( true ) {
        cVar1 = *(char *)param_4;
        param_4 = (CGraphic *)&param_4->field_0x1;
        if ((cVar1 < ' ') || ('\x7f' < cVar1)) break;
        uVar8 = uVar8 + 1;
      }
      if (0 < (int)uVar8) {
        GXBegin(0x80,0,(uVar8 & 0x3fff) << 2);
        sVar7 = 0;
        if (0 < (int)uVar8) {
          do {
            sVar6 = sVar7 * param_5;
            sVar7 = sVar7 + 1;
            uVar5 = (int)*(char *)pCVar4 - 0x20;
            sVar6 = param_2 + sVar6;
            DAT_cc008000._0_2_ = sVar6;
            DAT_cc008000._0_2_ = param_3;
            sVar2 = (short)((int)uVar5 >> 0x1f);
            sVar3 = ((short)((int)uVar5 >> 3) + (ushort)((int)uVar5 < 0 && (uVar5 & 7) != 0)) * 0x10
            ;
            DAT_cc008000._0_2_ = 0;
            sVar2 = ((sVar2 * 8 |
                     (ushort)((uint)(*(char *)pCVar4 * 0x20000000 + ((int)uVar5 >> 0x1f)) >> 0x1d))
                    - sVar2) * 0x10;
            DAT_cc008000._0_2_ = sVar2;
            pCVar4 = (CGraphic *)&pCVar4->field_0x1;
            DAT_cc008000._0_2_ = sVar3;
            DAT_cc008000._0_2_ = param_5 + sVar6;
            DAT_cc008000._0_2_ = param_3;
            DAT_cc008000._0_2_ = 0;
            DAT_cc008000._0_2_ = sVar2 + 0x10;
            DAT_cc008000._0_2_ = sVar3;
            DAT_cc008000._0_2_ = param_5 + sVar6;
            DAT_cc008000._0_2_ = param_3 + param_5;
            DAT_cc008000._0_2_ = 0;
            DAT_cc008000._0_2_ = sVar2 + 0x10;
            DAT_cc008000._0_2_ = sVar3 + 0x10;
            DAT_cc008000._0_2_ = sVar6;
            DAT_cc008000._0_2_ = param_3 + param_5;
            DAT_cc008000._0_2_ = 0;
            DAT_cc008000._0_2_ = sVar2;
            DAT_cc008000._0_2_ = sVar3 + 0x10;
            uVar8 = uVar8 - 1;
          } while (uVar8 != 0);
        }
        uVar8 = 0;
        graphic = pCVar4;
      }
      if (cVar1 != '\n') break;
      param_3 = param_3 + param_5;
      pCVar4 = param_4;
    }
  }
  return graphic;
}

