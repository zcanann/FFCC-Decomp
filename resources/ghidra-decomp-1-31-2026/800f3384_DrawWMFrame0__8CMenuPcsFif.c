// Function: DrawWMFrame0__8CMenuPcsFif
// Entry: 800f3384
// Size: 380 bytes

/* WARNING: Removing unreachable block (ram,0x800f34d8) */
/* WARNING: Removing unreachable block (ram,0x800f3394) */

void DrawWMFrame0__8CMenuPcsFif(double param_1,int param_2,uint param_3)

{
  short *psVar1;
  int iVar2;
  int iVar3;
  undefined4 local_50;
  undefined4 local_4c;
  double local_48;
  undefined4 local_40;
  uint uStack_3c;
  undefined4 local_38;
  uint uStack_34;
  undefined4 local_30;
  uint uStack_2c;
  
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  local_48 = (double)(longlong)(int)(DOUBLE_80331508 * param_1);
  local_4c = CONCAT31(0xffffff,(char)(int)(DOUBLE_80331508 * param_1));
  local_50 = local_4c;
  GXSetChanMatColor(4,&local_50);
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x1e);
  iVar2 = 0;
  iVar3 = 0;
  do {
    if ((param_3 & 1 << iVar2) != 0) {
      psVar1 = (short *)(*(int *)(param_2 + 0x820) + iVar3 + 4);
      uStack_3c = (int)psVar1[1] ^ 0x80000000;
      local_48 = (double)(CONCAT44(0x43300000,(int)*psVar1) ^ 0x80000000);
      uStack_34 = (int)psVar1[2] ^ 0x80000000;
      uStack_2c = (int)psVar1[3] ^ 0x80000000;
      local_40 = 0x43300000;
      local_38 = 0x43300000;
      local_30 = 0x43300000;
      DrawRect__8CMenuPcsFUlfffffffff
                ((double)(float)(local_48 - DOUBLE_80331408),
                 (double)(float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80331408),
                 (double)(float)((double)CONCAT44(0x43300000,uStack_34) - DOUBLE_80331408),
                 (double)(float)((double)CONCAT44(0x43300000,uStack_2c) - DOUBLE_80331408),
                 (double)*(float *)(psVar1 + 4),(double)*(float *)(psVar1 + 6),
                 (double)FLOAT_803313e8,(double)FLOAT_803313e8,&MenuPcs,
                 *(undefined4 *)(psVar1 + 0xc));
    }
    iVar2 = iVar2 + 1;
    iVar3 = iVar3 + 0x1c;
  } while (iVar2 < 2);
  return;
}

