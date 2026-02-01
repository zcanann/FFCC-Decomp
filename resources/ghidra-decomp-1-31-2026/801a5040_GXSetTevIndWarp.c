// Function: GXSetTevIndWarp
// Entry: 801a5040
// Size: 100 bytes

void GXSetTevIndWarp(undefined4 param_1,undefined4 param_2,char param_3,char param_4,
                    undefined4 param_5)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  if (param_4 == '\0') {
    uVar1 = 0;
  }
  else {
    uVar1 = 6;
  }
  if (param_3 == '\0') {
    uVar2 = 0;
  }
  else {
    uVar2 = 7;
  }
  GXSetTevIndirect(param_1,param_2,0,uVar2,param_5,uVar1,uVar1,0,0,0);
  return;
}

