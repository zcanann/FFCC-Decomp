// Function: SetObjMatrix__12CMaterialManFPA4_fPA4_f
// Entry: 8003eb24
// Size: 124 bytes

void SetObjMatrix__12CMaterialManFPA4_fPA4_f(int param_1,Mtx *param_2,Mtx *param_3)

{
  Mtx MStack_68;
  Mtx MStack_38;
  
  PSMTXConcat(param_2,param_3,&MStack_38);
  GXLoadPosMtxImm(&MStack_38,0);
  PSMTXCopy(&MStack_38,&MStack_68);
  MStack_68.value[0][3] = FLOAT_8032faf4;
  MStack_68.value[1][3] = FLOAT_8032faf4;
  MStack_68.value[2][3] = FLOAT_8032faf4;
  GXLoadNrmMtxImm(&MStack_68,0);
  PSMTXCopy(&MStack_68,(Mtx *)(param_1 + 0xe8));
  return;
}

