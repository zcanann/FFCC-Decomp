// Function: VECLerp__FP3VecP3VecP3Vecf
// Entry: 800b9680
// Size: 120 bytes

/* WARNING: Removing unreachable block (ram,0x800b96d8) */
/* WARNING: Removing unreachable block (ram,0x800b9690) */

void VECLerp__FP3VecP3VecP3Vecf(double param_1,Vec *param_2,Vec *param_3,Vec *param_4)

{
  Vec VStack_38;
  Vec VStack_2c;
  
  PSVECScale((float)((double)FLOAT_80330b34 - param_1),param_2,&VStack_2c);
  PSVECScale((float)param_1,param_3,&VStack_38);
  PSVECAdd(&VStack_2c,&VStack_38,param_4);
  return;
}

