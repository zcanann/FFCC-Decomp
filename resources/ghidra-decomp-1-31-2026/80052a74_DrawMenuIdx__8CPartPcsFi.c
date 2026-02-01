// Function: DrawMenuIdx__8CPartPcsFi
// Entry: 80052a74
// Size: 156 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DrawMenuIdx__8CPartPcsFi(int param_1,undefined4 param_2)

{
  if (*(char *)(param_1 + 0x30) == '\0') {
    SetDrawDoneDebugDataPartControl__8CGraphicFi(&Graphic,0x7fff);
    SetFog__8CGraphicFii(&Graphic,1,0);
    pppInitDrawEnv__FUc(0);
    pppSetRendMatrix__8CPartMngFv(&PartMng);
    pppDrawIdx__8CPartMngFi(&PartMng,param_2);
    drawEnd__8CPartMngFv(&PartMng);
    pppClearDrawEnv__Fv();
    SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0x7f);
  }
  return;
}

