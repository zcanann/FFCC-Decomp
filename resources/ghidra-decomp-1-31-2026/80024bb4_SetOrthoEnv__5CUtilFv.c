// Function: SetOrthoEnv__5CUtilFv
// Entry: 80024bb4
// Size: 100 bytes

void SetOrthoEnv__5CUtilFv(void)

{
  Mtx MStack_78;
  Mtx MStack_38;
  
  PSMTXIdentity(&MStack_38);
  GXLoadPosMtxImm(&MStack_38,0);
  GXSetCurrentMtx(0);
  C_MTXOrtho(FLOAT_8032f888,FLOAT_8032f8a0,FLOAT_8032f888,FLOAT_8032f8a4,FLOAT_8032f888,
             FLOAT_8032f88c,&MStack_78);
  GXSetProjection(&MStack_78,1);
  return;
}

