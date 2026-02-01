// Function: DrawArtiBase__8CMenuPcsFPQ28CMenuPcs5Sprt2f
// Entry: 8013351c
// Size: 616 bytes

/* WARNING: Removing unreachable block (ram,0x80133768) */
/* WARNING: Removing unreachable block (ram,0x80133760) */
/* WARNING: Removing unreachable block (ram,0x80133758) */
/* WARNING: Removing unreachable block (ram,0x80133750) */
/* WARNING: Removing unreachable block (ram,0x80133544) */
/* WARNING: Removing unreachable block (ram,0x8013353c) */
/* WARNING: Removing unreachable block (ram,0x80133534) */
/* WARNING: Removing unreachable block (ram,0x8013352c) */

void DrawArtiBase__8CMenuPcsFPQ28CMenuPcs5Sprt2f(double param_1,CMenuPcs *menuPcs,int param_3)

{
  float fVar1;
  undefined uVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  double local_80;
  undefined8 local_78;
  double local_70;
  longlong local_68;
  
  if (DOUBLE_80331e90 < param_1) {
    if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x1c) != 4) {
      local_80 = (double)(longlong)(int)((double)FLOAT_80331e98 * param_1);
      local_88 = CONCAT31(0xffffff,(char)(int)((double)FLOAT_80331e98 * param_1));
      local_8c = local_88;
      GXSetChanMatColor(4,&local_8c);
    }
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x1a);
    iVar5 = 0;
    local_80 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_3 + 4)) ^ 0x80000000);
    iVar3 = *DAT_8032eea8;
    dVar8 = (double)(float)(local_80 - DOUBLE_80331e88);
    local_78 = (double)CONCAT44(0x43300000,(int)*(short *)(param_3 + 6) ^ 0x80000000);
    dVar7 = (double)(float)(local_78 - DOUBLE_80331e88);
    piVar4 = DAT_8032eea8;
    if (0 < iVar3) {
      do {
        if ((int)*(short *)(*(int *)&menuPcs->field_0x82c + 0xe) == piVar4[0xd]) break;
        piVar4 = piVar4 + 0xb;
        iVar5 = iVar5 + 1;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
    iVar3 = 0;
    dVar10 = (double)FLOAT_80331eac;
    dVar9 = (double)(float)((double)FLOAT_80331e98 * param_1);
    iVar6 = 0;
    do {
      if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x1c) == 4) {
        fVar1 = FLOAT_80331eb0;
        if ((((int)(char)(*(byte *)(DAT_8032eea8 + 2) | *(byte *)((int)DAT_8032eea8 + 9)) |
             DAT_8032eea8[iVar5 * 0xb + 0xe]) & 1 << iVar3) != 0) {
          fVar1 = FLOAT_80331eb4;
        }
        local_68 = (longlong)(int)dVar9;
        local_80 = (double)(longlong)(int)(FLOAT_80331e98 * fVar1);
        uVar2 = (undefined)(int)(FLOAT_80331e98 * fVar1);
        local_90 = CONCAT31(CONCAT21(CONCAT11(uVar2,uVar2),uVar2),(char)(int)dVar9);
        local_88 = local_90;
        local_78 = local_80;
        local_70 = local_80;
        GXSetChanMatColor(4,&local_90);
      }
      DrawRect__8CMenuPcsFUlfffffffff
                ((double)*(float *)(DAT_8032eeb0 + iVar6 + 8),
                 (double)*(float *)(DAT_8032eeb0 + iVar6 + 0xc),dVar8,dVar7,dVar10,dVar10,
                 (double)FLOAT_80331eb0,(double)FLOAT_80331eb0,&MenuPcs,0);
      iVar3 = iVar3 + 1;
      iVar6 = iVar6 + 8;
    } while (iVar3 < 8);
  }
  return;
}

