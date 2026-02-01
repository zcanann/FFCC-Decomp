// Function: DrawSphere__8CGraphicFPA4_fP3VecP3VecP8_GXColor
// Entry: 80018894
// Size: 192 bytes

void DrawSphere__8CGraphicFPA4_fP3VecP3VecP8_GXColor
               (CGraphic *graphic,Mtx *param_2,float *param_3,float *param_4,undefined4 *param_5)

{
  undefined4 local_48;
  Mtx MStack_44;
  
  PSMTXScale(*param_4,param_4[1],param_4[2],&MStack_44);
  MStack_44.value[0][3] = *param_3;
  MStack_44.value[1][3] = param_3[1];
  MStack_44.value[2][3] = param_3[2];
  PSMTXConcat(param_2,&MStack_44,&MStack_44);
  GXLoadPosMtxImm(&MStack_44,0);
  local_48 = *param_5;
  GXSetChanMatColor(4,&local_48);
  GXSetLineWidth(8,0);
  GXCallDisplayList(*(undefined4 *)&graphic->field_0x71fc,*(undefined4 *)&graphic->field_0x71f8);
  return;
}

