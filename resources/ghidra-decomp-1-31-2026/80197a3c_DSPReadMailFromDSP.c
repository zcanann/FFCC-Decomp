// Function: DSPReadMailFromDSP
// Entry: 80197a3c
// Size: 24 bytes

undefined4 DSPReadMailFromDSP(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  
  uVar1 = DAT_cc005004;
  uVar2 = DAT_cc005006;
  return CONCAT22(uVar1,uVar2);
}

