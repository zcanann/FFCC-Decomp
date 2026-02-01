// Function: DrawSingleBase__8CMenuPcsFf
// Entry: 8014935c
// Size: 472 bytes

/* WARNING: Removing unreachable block (ram,0x8014950c) */
/* WARNING: Removing unreachable block (ram,0x80149504) */
/* WARNING: Removing unreachable block (ram,0x80149374) */
/* WARNING: Removing unreachable block (ram,0x8014936c) */

void DrawSingleBase__8CMenuPcsFf(double param_1,CMenuPcs *menuPcs)

{
  uint uVar1;
  uint uVar2;
  double dVar3;
  double dVar4;
  undefined4 local_50;
  undefined4 local_4c;
  undefined8 local_48;
  undefined4 local_40;
  uint uStack_3c;
  
  DrawInit__8CMenuPcsFv(menuPcs);
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  local_48 = (double)(longlong)(int)((double)FLOAT_80332940 * param_1);
  local_4c = CONCAT31(0xffffff,(char)(int)((double)FLOAT_80332940 * param_1));
  local_50 = local_4c;
  GXSetChanMatColor(4,&local_50);
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x20);
  dVar3 = (double)FLOAT_8033294c;
  DrawRect__8CMenuPcsFUlfffffffff
            (dVar3,dVar3,(double)FLOAT_803329a4,(double)FLOAT_80332928,dVar3,dVar3,
             (double)FLOAT_80332934,(double)FLOAT_80332934,&MenuPcs,0);
  dVar3 = (double)FLOAT_8033294c;
  DrawRect__8CMenuPcsFUlfffffffff
            (dVar3,(double)FLOAT_803329a8,(double)FLOAT_803329a4,(double)FLOAT_80332928,dVar3,dVar3,
             (double)FLOAT_80332934,(double)FLOAT_80332934,&MenuPcs,4);
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x28);
  dVar4 = (double)FLOAT_8033294c;
  uVar1 = 0x20;
  dVar3 = DOUBLE_80332938;
  for (uVar2 = 0x40; (int)uVar2 < 0x180; uVar2 = uVar2 + uVar1) {
    if ((int)(0x180 - uVar2) < (int)uVar1) {
      uVar1 = 0x180 - uVar2;
    }
    uStack_3c = uVar1 ^ 0x80000000;
    local_48 = (double)CONCAT44(0x43300000,uVar2 ^ 0x80000000);
    local_40 = 0x43300000;
    DrawRect__8CMenuPcsFUlfffffffff
              (dVar4,(double)(float)(local_48 - dVar3),(double)FLOAT_803329a4,
               (double)(float)((double)CONCAT44(0x43300000,uStack_3c) - dVar3),dVar4,dVar4,
               (double)FLOAT_80332934,(double)FLOAT_80332934,&MenuPcs,0);
  }
  return;
}

