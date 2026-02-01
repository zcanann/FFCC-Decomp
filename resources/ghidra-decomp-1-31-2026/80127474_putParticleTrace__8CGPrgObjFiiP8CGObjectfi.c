// Function: putParticleTrace__8CGPrgObjFiiP8CGObjectfi
// Entry: 80127474
// Size: 156 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void putParticleTrace__8CGPrgObjFiiP8CGObjectfi
               (CFlatRuntime2 *cflatRuntime2,CGPrgObj *gPrgObj,int param_3,int param_4,
               CGObject *param_5,int param_6)

{
  undefined4 in_register_00004008;
  undefined8 uVar1;
  
  uVar1 = CONCAT44(in_register_00004008,cflatRuntime2);
  ResetParticleWork__13CFlatRuntime2Fii((CFlatRuntime2 *)&CFlat,param_3,param_4);
  SetParticleWorkScale__13CFlatRuntime2Ff(uVar1,(CFlatRuntime2 *)&CFlat);
  SetParticleWorkTrace__13CFlatRuntime2FPQ212CFlatRuntime7CObject((CFlatRuntime2 *)&CFlat,gPrgObj);
  PutParticleWork__13CFlatRuntime2Fv((CFlatRuntime2 *)&CFlat);
  if (param_6 != 0) {
    SetParticleWorkSe__13CFlatRuntime2Fiii((CFlatRuntime2 *)&CFlat,param_6,2,0);
  }
  return;
}

