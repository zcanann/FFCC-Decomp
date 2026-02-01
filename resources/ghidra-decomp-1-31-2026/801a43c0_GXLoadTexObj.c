// Function: GXLoadTexObj
// Entry: 801a43c0
// Size: 84 bytes

void GXLoadTexObj(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = (**(code **)(DAT_80333828 + 0x410))();
  GXLoadTexObjPreLoaded(param_1,uVar1,param_2);
  return;
}

