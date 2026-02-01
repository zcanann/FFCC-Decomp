// Function: isLoadLayerASyncCompleted__13CFlatRuntime2Fi
// Entry: 8006b050
// Size: 24 bytes

uint isLoadLayerASyncCompleted__13CFlatRuntime2Fi(CFlatRuntime2 *flatRuntime2,int param_2)

{
  uint uVar1;
  
  uVar1 = countLeadingZeros(*(undefined4 *)(&flatRuntime2->field_0x1778 + param_2 * 0xc));
  return uVar1 >> 5;
}

