// Function: putParticle__8CGPrgObjFiiP3Vecfi
// Entry: 801275ac
// Size: 164 bytes

/* WARNING: Removing unreachable block (ram,0x80127630) */
/* WARNING: Removing unreachable block (ram,0x801275bc) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void putParticle__8CGPrgObjFiiP3Vecfi
               (undefined8 param_1,CGPrgObj *gPrgObj,undefined4 param_3,undefined4 param_4,
               Vec *param_5,int param_6)

{
  ResetParticleWork__13CFlatRuntime2Fii((CFlatRuntime2 *)&CFlat,param_3,param_4);
  SetParticleWorkScale__13CFlatRuntime2Ff(param_1,(CFlatRuntime2 *)&CFlat);
  SetParticleWorkPos__13CFlatRuntime2FR3Vecf((double)FLOAT_80331bd4,(CFlatRuntime2 *)&CFlat,param_5)
  ;
  if (param_6 != 0) {
    SetParticleWorkSe__13CFlatRuntime2Fiii((CFlatRuntime2 *)&CFlat,param_6,2,0);
  }
  PutParticleWork__13CFlatRuntime2Fv((CFlatRuntime2 *)&CFlat);
  return;
}

