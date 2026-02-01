// Function: DrawSingleIcon__8CMenuPcsFiiifif
// Entry: 80147728
// Size: 420 bytes

/* WARNING: Removing unreachable block (ram,0x801478a4) */
/* WARNING: Removing unreachable block (ram,0x8014789c) */
/* WARNING: Removing unreachable block (ram,0x80147740) */
/* WARNING: Removing unreachable block (ram,0x80147738) */

void DrawSingleIcon__8CMenuPcsFiiifif
               (double param_1,undefined8 param_2,undefined4 param_3,uint param_4,uint param_5,
               uint param_6,int param_7)

{
  int iVar1;
  undefined4 local_60;
  undefined4 local_5c;
  longlong local_58;
  undefined4 local_50;
  uint uStack_4c;
  undefined4 local_48;
  uint uStack_44;
  undefined4 local_40;
  uint uStack_3c;
  undefined4 local_38;
  uint uStack_34;
  
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  local_58 = (longlong)(int)((double)FLOAT_80332940 * param_1);
  local_5c = CONCAT31(0xffffff,(char)(int)((double)FLOAT_80332940 * param_1));
  local_60 = local_5c;
  GXSetChanMatColor(4,&local_60);
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x25);
  if (param_7 == 0) {
    param_4 = (uint)(byte)(&DAT_801de6ac)[param_4];
  }
  iVar1 = (int)param_4 >> 0x1f;
  uStack_44 = param_6 ^ 0x80000000;
  uStack_4c = param_5 ^ 0x80000000;
  local_48 = 0x43300000;
  uStack_34 = (((int)param_4 >> 3) + (uint)((int)param_4 < 0 && (param_4 & 7) != 0)) * 0x20 ^
              0x80000000;
  uStack_3c = ((iVar1 * 8 | param_4 * 0x20000000 + iVar1 >> 0x1d) - iVar1) * 0x20 ^ 0x80000000;
  local_50 = 0x43300000;
  local_40 = 0x43300000;
  local_38 = 0x43300000;
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)(float)((double)CONCAT44(0x43300000,uStack_4c) - DOUBLE_80332938),
             (double)(float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_80332938),
             (double)FLOAT_8033292c,(double)FLOAT_8033292c,
             (double)(float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80332938),
             (double)(float)((double)CONCAT44(0x43300000,uStack_34) - DOUBLE_80332938),param_2,
             param_2,&MenuPcs,0);
  return;
}

