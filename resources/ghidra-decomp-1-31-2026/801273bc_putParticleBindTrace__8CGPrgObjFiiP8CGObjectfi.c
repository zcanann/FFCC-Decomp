// Function: putParticleBindTrace__8CGPrgObjFiiP8CGObjectfi
// Entry: 801273bc
// Size: 184 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void putParticleBindTrace__8CGPrgObjFiiP8CGObjectfi
               (undefined8 param_1,CGPrgObj *gPrgObj,int param_3,int param_4,CGObject *param_5,
               int param_6)

{
  ResetParticleWork__13CFlatRuntime2Fii((CFlatRuntime2 *)&CFlat,param_3,param_4);
  SetParticleWorkScale__13CFlatRuntime2Ff(param_1,(CFlatRuntime2 *)&CFlat);
  SetParticleWorkBind__13CFlatRuntime2FPQ212CFlatRuntime7CObject((CFlatRuntime2 *)&CFlat,gPrgObj);
  SetParticleWorkTrace__13CFlatRuntime2FPQ212CFlatRuntime7CObject((CFlatRuntime2 *)&CFlat,param_5);
  PutParticleWork__13CFlatRuntime2Fv((CFlatRuntime2 *)&CFlat);
  if (param_6 != 0) {
    SetParticleWorkSe__13CFlatRuntime2Fiii((CFlatRuntime2 *)&CFlat,param_6,2,0);
  }
  return;
}

