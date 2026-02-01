// Function: calc__11CDbgMenuPcsFv
// Entry: 8012cd88
// Size: 1144 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void calc__11CDbgMenuPcsFv(CMenuPcs *menuPcs)

{
  ushort uVar2;
  uint uVar1;
  int iVar3;
  int iVar4;
  undefined4 local_18;
  int local_14;
  undefined4 local_10;
  
  if (*(int *)&menuPcs->field_0x58 != 0) {
    if (Pad._452_4_ == 0) {
      uVar2 = *(ushort *)
               (&Pad.field_0x8 + (~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) * 0x54)
      ;
    }
    else {
      uVar2 = 0;
    }
    if ((uVar2 & 0x100) != 0) {
      switch(*(undefined4 *)(*(int *)&menuPcs[4].field_0x7e4 + 0x38)) {
      case 100:
        CFlat._4772_4_ = ~CFlat._4772_4_;
        break;
      case 0x65:
        local_18 = 0;
        local_10 = 0;
        uVar1 = countLeadingZeros((int)((char)CFlat._4836_1_ >> 7));
        uVar1 = ((int)(char)(uVar1 >> 5) & 1U) << 7 | (byte)CFlat._4836_1_ & 0xffffff7f;
        CFlat._4836_1_ = (undefined)uVar1;
        local_14 = (int)(uVar1 << 0x18) >> 0x1f;
        SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
                  (&CFlat,0,1,9,3,&local_18,(CStack *)0x0);
        break;
      case 0x66:
        uVar1 = countLeadingZeros((int)(char)((int)((uint)(byte)CFlat._4836_1_ << 0x1d) >> 0x1f));
        CFlat._4836_1_ = (byte)((int)(char)(uVar1 >> 5) << 2) & 4 | CFlat._4836_1_ & 0xfb;
        break;
      case 0x67:
        *(uint *)&menuPcs->field_0x4 = *(uint *)&menuPcs->field_0x4 ^ 1;
        break;
      case 0x68:
        *(uint *)&menuPcs->field_0x4 = *(uint *)&menuPcs->field_0x4 ^ 2;
        break;
      case 0x69:
        *(uint *)&menuPcs->field_0x4 = *(uint *)&menuPcs->field_0x4 ^ 4;
        break;
      case 0x6a:
        *(uint *)&menuPcs->field_0x4 = *(uint *)&menuPcs->field_0x4 ^ 8;
        break;
      case 0x6b:
        *(uint *)&menuPcs->field_0x4 = *(uint *)&menuPcs->field_0x4 ^ 0x10;
        break;
      case 0x6c:
        *(uint *)&menuPcs->field_0x4 = *(uint *)&menuPcs->field_0x4 ^ 0x20;
        break;
      case 0x6d:
        *(uint *)&menuPcs->field_0x4 = *(uint *)&menuPcs->field_0x4 ^ 0x40;
        break;
      case 0x6e:
        *(uint *)&menuPcs->field_0x4 = *(uint *)&menuPcs->field_0x4 ^ 0x80;
        break;
      case 0x6f:
        *(uint *)&menuPcs->field_0x4 = *(uint *)&menuPcs->field_0x4 ^ 0x100;
        break;
      case 0x70:
        *(uint *)&menuPcs->field_0x4 = *(uint *)&menuPcs->field_0x4 ^ 0x200;
        break;
      case 0x71:
        *(uint *)&menuPcs->field_0x4 = *(uint *)&menuPcs->field_0x4 ^ 0x400;
        break;
      case 0x72:
        *(uint *)&menuPcs->field_0x4 = *(uint *)&menuPcs->field_0x4 ^ 0x800;
        uVar1 = countLeadingZeros(*(uint *)&menuPcs->field_0x4 & 0x800);
        PartPcs.m_usbStreamData.m_disableShokiDraw = (uint8_t)(uVar1 >> 5);
        break;
      case 0x73:
        *(uint *)&menuPcs->field_0x4 = *(uint *)&menuPcs->field_0x4 ^ 0x1000;
        break;
      case 0x74:
        CheckDriver__6CSoundFi(&Sound,1);
        break;
      case 0x75:
        DAT_8032ecd8 = '\x01' - DAT_8032ecd8;
        break;
      case 0x76:
        DAT_8032e698 = '\x01' - DAT_8032e698;
        pppDumpMngSt__8CPartMngFv(&PartMng);
        break;
      case 0x77:
        DumpLoad__9CCharaPcsFv(&CharaPcs);
        break;
      case 0x78:
        *(uint *)&menuPcs->field_0x4 = *(uint *)&menuPcs->field_0x4 ^ 0x2000;
        break;
      case 0x79:
        *(uint *)&menuPcs->field_0x4 = *(uint *)&menuPcs->field_0x4 ^ 0x4000;
        break;
      case 0x7a:
        *(uint *)&menuPcs->field_0x4 = *(uint *)&menuPcs->field_0x4 ^ 0x8000;
      }
    }
    if (Pad._452_4_ == 0) {
      uVar2 = *(ushort *)
               (&Pad.field_0x8 + (~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) * 0x54)
      ;
    }
    else {
      uVar2 = 0;
    }
    if ((uVar2 & 4) != 0) {
      iVar3 = *(int *)&menuPcs[4].field_0x7e4;
      *(byte *)(iVar3 + 0x34) = *(byte *)(iVar3 + 0x34) & 0xbf;
      do {
        *(undefined4 *)&menuPcs[4].field_0x7e4 =
             *(undefined4 *)(*(int *)&menuPcs[4].field_0x7e4 + 0x48);
        iVar4 = *(int *)&menuPcs[4].field_0x7e4;
        if ((*(uint *)(iVar4 + 4) & 1) != 0) break;
      } while (iVar3 != iVar4);
      *(byte *)(iVar4 + 0x34) = *(byte *)(iVar4 + 0x34) & 0xbf | 0x40;
    }
    if (Pad._452_4_ == 0) {
      uVar2 = *(ushort *)
               (&Pad.field_0x8 + (~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) * 0x54)
      ;
    }
    else {
      uVar2 = 0;
    }
    if ((uVar2 & 8) != 0) {
      iVar3 = *(int *)&menuPcs[4].field_0x7e4;
      *(byte *)(iVar3 + 0x34) = *(byte *)(iVar3 + 0x34) & 0xbf;
      do {
        *(undefined4 *)&menuPcs[4].field_0x7e4 =
             *(undefined4 *)(*(int *)&menuPcs[4].field_0x7e4 + 0x44);
        iVar4 = *(int *)&menuPcs[4].field_0x7e4;
        if ((*(uint *)(iVar4 + 4) & 1) != 0) break;
      } while (iVar3 != iVar4);
      *(byte *)(iVar4 + 0x34) = *(byte *)(iVar4 + 0x34) & 0xbf | 0x40;
    }
    if (*(int *)&menuPcs->field_0x58 != 0) {
      calcMenu__11CDbgMenuPcsFPQ211CDbgMenuPcs3CDM(menuPcs,*(int *)&menuPcs->field_0x58);
    }
    if (Pad._452_4_ == 0) {
      uVar2 = *(ushort *)
               (&Pad.field_0x8 + (~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) * 0x54)
      ;
    }
    else {
      uVar2 = 0;
    }
    if ((uVar2 & 0x200) != 0) {
      memset(&menuPcs->field_0x5c,0,0x2a00);
      *(undefined4 *)&menuPcs->field_0x58 = 0;
      *(undefined4 *)&menuPcs[4].field_0x7e0 = 0;
      *(undefined4 *)&menuPcs[4].field_0x7e4 = 0;
    }
    Pad._452_4_ = 1;
  }
  return;
}

