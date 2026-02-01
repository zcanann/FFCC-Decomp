// Function: resetSpawnBit__13CFlatRuntime2Fi
// Entry: 80069d20
// Size: 92 bytes

void resetSpawnBit__13CFlatRuntime2Fi(CFlatRuntime2 *flatRuntime2,int param_2)

{
  if (param_2 == -1) {
    memset(&flatRuntime2->field_0x12f0,0,0x48);
  }
  else if ((-1 < param_2) && (param_2 < 9)) {
    *(undefined4 *)(&flatRuntime2->field_0x12f4 + param_2 * 8) = 0;
    *(undefined4 *)(&flatRuntime2->field_0x12f0 + param_2 * 8) = 0;
  }
  return;
}

