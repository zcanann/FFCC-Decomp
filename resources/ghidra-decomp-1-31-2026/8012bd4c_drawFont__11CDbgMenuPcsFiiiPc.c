// Function: drawFont__11CDbgMenuPcsFiiiPc
// Entry: 8012bd4c
// Size: 1320 bytes

/* WARNING: Removing unreachable block (ram,0x8012c028) */
/* WARNING: Removing unreachable block (ram,0x8012be28) */
/* WARNING: Removing unreachable block (ram,0x8012bf28) */
/* WARNING: Removing unreachable block (ram,0x8012c128) */

void drawFont__11CDbgMenuPcsFiiiPc
               (int param_1,uint param_2,short param_3,short param_4,undefined4 param_5)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  short sVar5;
  short sVar6;
  undefined4 local_58;
  uint local_54;
  undefined4 local_50;
  uint local_4c;
  undefined4 local_48;
  uint local_44;
  undefined4 local_40;
  uint local_3c;
  uint local_38;
  undefined4 local_34;
  
  if (*(int *)(param_1 + 0x2a68) != 0) {
    GXSetChanCtrl(4,0,0,0,0,2,1);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,4);
    _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,0);
    *(undefined4 *)(param_1 + 0x2a68) = 0;
  }
  local_34 = DAT_80331c8c;
  if ((param_2 & 2) != 0) {
    local_34 = (uint)((ushort)DAT_80331c8c & 0xff);
  }
  if ((param_2 & 4) != 0) {
    sVar6 = param_3 + -1;
    changeVtxFmt__11CDbgMenuPcsFi(param_1,0);
    local_40 = (uint)((ushort)DAT_80331c8c & 0xff);
    local_3c = local_40;
    GXSetChanMatColor(4,&local_3c);
    uVar1 = param_2 & 1;
    iVar4 = 10;
    if (uVar1 != 0) {
      iVar4 = 8;
    }
    uVar2 = param_2 & 8;
    sVar5 = param_4;
    if (uVar2 != 0) {
      iVar3 = strlen(param_5);
      sVar6 = sVar6 - (short)((uint)(iVar4 * iVar3) >> 1);
      sVar5 = param_4 - (short)(iVar4 >> 1);
    }
    DrawDebugStringDirect__8CGraphicFUlUlPcUl(&Graphic,sVar6,sVar5,param_5,(short)iVar4);
    sVar6 = param_4 + 1;
    changeVtxFmt__11CDbgMenuPcsFi(param_1,0);
    local_48 = (uint)((ushort)DAT_80331c8c & 0xff);
    local_44 = local_48;
    GXSetChanMatColor(4,&local_44);
    iVar4 = 10;
    if (uVar1 != 0) {
      iVar4 = 8;
    }
    sVar5 = param_3;
    if (uVar2 != 0) {
      iVar3 = strlen(param_5);
      sVar5 = param_3 - (short)((uint)(iVar4 * iVar3) >> 1);
      sVar6 = sVar6 - (short)(iVar4 >> 1);
    }
    DrawDebugStringDirect__8CGraphicFUlUlPcUl(&Graphic,sVar5,sVar6,param_5,(short)iVar4);
    sVar6 = param_3 + 1;
    changeVtxFmt__11CDbgMenuPcsFi(param_1,0);
    local_50 = (uint)((ushort)DAT_80331c8c & 0xff);
    local_4c = local_50;
    GXSetChanMatColor(4,&local_4c);
    iVar4 = 10;
    if (uVar1 != 0) {
      iVar4 = 8;
    }
    sVar5 = param_4;
    if (uVar2 != 0) {
      iVar3 = strlen(param_5);
      sVar6 = sVar6 - (short)((uint)(iVar4 * iVar3) >> 1);
      sVar5 = param_4 - (short)(iVar4 >> 1);
    }
    DrawDebugStringDirect__8CGraphicFUlUlPcUl(&Graphic,sVar6,sVar5,param_5,(short)iVar4);
    sVar6 = param_4 + -1;
    changeVtxFmt__11CDbgMenuPcsFi(param_1,0);
    local_58 = (uint)((ushort)DAT_80331c8c & 0xff);
    local_54 = local_58;
    GXSetChanMatColor(4,&local_54);
    iVar4 = 10;
    if (uVar1 != 0) {
      iVar4 = 8;
    }
    sVar5 = param_3;
    if (uVar2 != 0) {
      iVar3 = strlen(param_5);
      sVar5 = param_3 - (short)((uint)(iVar4 * iVar3) >> 1);
      sVar6 = sVar6 - (short)(iVar4 >> 1);
    }
    DrawDebugStringDirect__8CGraphicFUlUlPcUl(&Graphic,sVar5,sVar6,param_5,(short)iVar4);
  }
  local_38 = local_34;
  GXSetChanMatColor(4,&local_38);
  iVar4 = 10;
  if ((param_2 & 1) != 0) {
    iVar4 = 8;
  }
  if ((param_2 & 8) != 0) {
    iVar3 = strlen(param_5);
    param_3 = param_3 - (short)((uint)(iVar4 * iVar3) >> 1);
    param_4 = param_4 - (short)(iVar4 >> 1);
  }
  DrawDebugStringDirect__8CGraphicFUlUlPcUl(&Graphic,param_3,param_4,param_5,(short)iVar4);
  return;
}

