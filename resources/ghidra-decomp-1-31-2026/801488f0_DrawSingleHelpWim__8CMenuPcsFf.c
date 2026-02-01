// Function: DrawSingleHelpWim__8CMenuPcsFf
// Entry: 801488f0
// Size: 680 bytes

/* WARNING: Removing unreachable block (ram,0x80148b80) */
/* WARNING: Removing unreachable block (ram,0x80148900) */

void DrawSingleHelpWim__8CMenuPcsFf(double param_1,CMenuPcs *menuPcs)

{
  double dVar1;
  double in_f31;
  double in_ps31_1;
  undefined4 local_20;
  undefined4 local_1c;
  longlong local_18;
  float local_8;
  float fStack_4;
  
  local_8 = (float)in_f31;
  fStack_4 = (float)in_ps31_1;
  DrawInit__8CMenuPcsFv(menuPcs);
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  local_18 = (longlong)(int)((double)FLOAT_80332940 * param_1);
  local_1c = CONCAT31(0xffffff,(char)(int)((double)FLOAT_80332940 * param_1));
  local_20 = local_1c;
  GXSetChanMatColor(4,&local_20);
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x23);
  dVar1 = (double)FLOAT_8033292c;
  DrawRect__8CMenuPcsFUlfffffffff
            (dVar1,(double)FLOAT_803329c0,dVar1,dVar1,(double)FLOAT_8033294c,(double)FLOAT_8033294c,
             (double)FLOAT_80332934,(double)FLOAT_80332934,&MenuPcs,0);
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)FLOAT_803329c4,(double)FLOAT_803329c0,(double)FLOAT_8033292c,
             (double)FLOAT_8033292c,(double)FLOAT_8033294c,(double)FLOAT_8033294c,
             (double)FLOAT_80332934,(double)FLOAT_80332934,&MenuPcs,8);
  dVar1 = (double)FLOAT_8033292c;
  DrawRect__8CMenuPcsFUlfffffffff
            (dVar1,(double)FLOAT_803329a8,dVar1,dVar1,(double)FLOAT_8033294c,(double)FLOAT_8033294c,
             (double)FLOAT_80332934,(double)FLOAT_80332934,&MenuPcs,4);
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)FLOAT_803329c4,(double)FLOAT_803329a8,(double)FLOAT_8033292c,
             (double)FLOAT_8033292c,(double)FLOAT_8033294c,(double)FLOAT_8033294c,
             (double)FLOAT_80332934,(double)FLOAT_80332934,&MenuPcs,0xc);
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x27);
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)FLOAT_80332928,(double)FLOAT_803329c0,(double)FLOAT_803329c8,
             (double)FLOAT_8033292c,(double)FLOAT_8033294c,(double)FLOAT_8033294c,
             (double)FLOAT_80332934,(double)FLOAT_80332934,&MenuPcs,0);
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)FLOAT_80332928,(double)FLOAT_803329a8,(double)FLOAT_803329c8,
             (double)FLOAT_8033292c,(double)FLOAT_8033294c,(double)FLOAT_8033294c,
             (double)FLOAT_80332934,(double)FLOAT_80332934,&MenuPcs,4);
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x24);
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)FLOAT_8033292c,(double)FLOAT_803329cc,(double)FLOAT_8033292c,
             (double)FLOAT_803329d0,(double)FLOAT_8033294c,(double)FLOAT_8033294c,
             (double)FLOAT_80332934,(double)FLOAT_80332934,&MenuPcs,0);
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)FLOAT_803329c4,(double)FLOAT_803329cc,(double)FLOAT_8033292c,
             (double)FLOAT_803329d0,(double)FLOAT_8033294c,(double)FLOAT_8033294c,
             (double)FLOAT_80332934,(double)FLOAT_80332934,&MenuPcs,8);
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x2b);
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)FLOAT_80332928,(double)FLOAT_803329cc,(double)FLOAT_803329c8,
             (double)FLOAT_803329d0,(double)FLOAT_8033294c,(double)FLOAT_8033294c,
             (double)FLOAT_80332934,(double)FLOAT_80332934,&MenuPcs,8);
  return;
}

