// Function: DrawBonusFrame__8CMenuPcsFfffff
// Entry: 80133784
// Size: 852 bytes

/* WARNING: Removing unreachable block (ram,0x80133ab8) */
/* WARNING: Removing unreachable block (ram,0x80133ab0) */
/* WARNING: Removing unreachable block (ram,0x80133aa8) */
/* WARNING: Removing unreachable block (ram,0x80133aa0) */
/* WARNING: Removing unreachable block (ram,0x80133a98) */
/* WARNING: Removing unreachable block (ram,0x80133a90) */
/* WARNING: Removing unreachable block (ram,0x80133a88) */
/* WARNING: Removing unreachable block (ram,0x80133a80) */
/* WARNING: Removing unreachable block (ram,0x801337cc) */
/* WARNING: Removing unreachable block (ram,0x801337c4) */
/* WARNING: Removing unreachable block (ram,0x801337bc) */
/* WARNING: Removing unreachable block (ram,0x801337b4) */
/* WARNING: Removing unreachable block (ram,0x801337ac) */
/* WARNING: Removing unreachable block (ram,0x801337a4) */
/* WARNING: Removing unreachable block (ram,0x8013379c) */
/* WARNING: Removing unreachable block (ram,0x80133794) */

void DrawBonusFrame__8CMenuPcsFfffff
               (double param_1,double param_2,double param_3,double param_4,double param_5)

{
  int iVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  undefined4 local_a0;
  undefined4 local_9c;
  longlong local_98;
  
  if (DOUBLE_80331e90 < param_5) {
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
    local_98 = (longlong)(int)((double)FLOAT_80331e98 * param_5);
    local_9c = CONCAT31(0xffffff,(char)(int)((double)FLOAT_80331e98 * param_5));
    local_a0 = local_9c;
    GXSetChanMatColor(4,&local_a0);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x1b);
    dVar7 = (double)((float)(param_1 + param_3) - FLOAT_80331eb8);
    iVar1 = 0;
    dVar5 = (double)((float)(param_2 + param_4) - FLOAT_80331eb8);
    do {
      dVar4 = param_1;
      dVar6 = param_2;
      if (iVar1 == 0) {
        dVar2 = (double)FLOAT_80331eac;
        dVar3 = dVar2;
      }
      else if (iVar1 == 1) {
        dVar2 = (double)FLOAT_80331eb8;
        dVar4 = dVar7;
        dVar3 = (double)FLOAT_80331eac;
      }
      else {
        dVar6 = dVar5;
        if (iVar1 == 2) {
          dVar2 = (double)FLOAT_80331eac;
          dVar3 = (double)FLOAT_80331eb8;
        }
        else {
          dVar2 = (double)FLOAT_80331eb8;
          dVar4 = dVar7;
          dVar3 = dVar2;
        }
      }
      DrawRect__8CMenuPcsFUlfffffffff
                (dVar4,dVar6,(double)FLOAT_80331eb8,(double)FLOAT_80331eb8,dVar2,dVar3,
                 (double)FLOAT_80331eb0,(double)FLOAT_80331eb0,&MenuPcs,0);
      iVar1 = iVar1 + 1;
    } while (iVar1 < 4);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x1c);
    param_3 = param_3 - DOUBLE_80331ec0;
    dVar6 = (double)(float)((double)FLOAT_80331eb8 + param_1);
    dVar4 = (double)(float)param_3;
    DrawRect__8CMenuPcsFUlfffffffff
              (dVar6,param_2,dVar4,(double)FLOAT_80331eb8,(double)FLOAT_80331eac,
               (double)FLOAT_80331eac,(double)FLOAT_80331eb0,(double)FLOAT_80331eb0,&MenuPcs,0);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x22);
    DrawRect__8CMenuPcsFUlfffffffff
              (dVar6,dVar5,dVar4,(double)FLOAT_80331eb8,(double)FLOAT_80331eac,
               (double)FLOAT_80331eac,(double)FLOAT_80331eb0,(double)FLOAT_80331eb0,&MenuPcs,0);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x1d);
    dVar4 = (double)(float)((double)FLOAT_80331eb8 + param_2);
    dVar5 = (double)(float)(param_4 - DOUBLE_80331ec0);
    DrawRect__8CMenuPcsFUlfffffffff
              (param_1,dVar4,(double)FLOAT_80331eb8,dVar5,(double)FLOAT_80331eac,
               (double)FLOAT_80331eac,(double)FLOAT_80331eb0,(double)FLOAT_80331eb0,&MenuPcs,0);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x21);
    DrawRect__8CMenuPcsFUlfffffffff
              (dVar7,dVar4,(double)FLOAT_80331eb8,dVar5,(double)FLOAT_80331eac,
               (double)FLOAT_80331eac,(double)FLOAT_80331eb0,(double)FLOAT_80331eb0,&MenuPcs,0);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x1e);
    DrawRect__8CMenuPcsFUlfffffffff
              (dVar6,dVar4,(double)(float)param_3,dVar5,(double)FLOAT_80331eac,
               (double)FLOAT_80331eac,(double)FLOAT_80331eb0,(double)FLOAT_80331eb0,&MenuPcs,0);
  }
  return;
}

