// Function: __ptmf_scall
// Entry: 801aff1c
// Size: 40 bytes

void __ptmf_scall(int param_1)

{
  int *in_r12;
  code *UNRECOVERED_JUMPTABLE;
  
  UNRECOVERED_JUMPTABLE = (code *)in_r12[2];
  if (-1 < in_r12[1]) {
    UNRECOVERED_JUMPTABLE =
         *(code **)(*(int *)(UNRECOVERED_JUMPTABLE + param_1 + *in_r12) + in_r12[1]);
  }
                    /* WARNING: Could not recover jumptable at 0x801aff40. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)();
  return;
}

