// Function: VECMultAdd__FP3VecP3VecP3Vecf
// Entry: 800b9784
// Size: 84 bytes

void VECMultAdd__FP3VecP3VecP3Vecf(double param_1,Vec *param_2,Vec *param_3,Vec *param_4)

{
  Vec VStack_18;
  
  PSVECScale((float)param_1,param_3,&VStack_18);
  PSVECAdd(param_2,&VStack_18,param_4);
  return;
}

