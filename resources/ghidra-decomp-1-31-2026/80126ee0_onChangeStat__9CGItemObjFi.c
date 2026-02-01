// Function: onChangeStat__9CGItemObjFi
// Entry: 80126ee0
// Size: 40 bytes

void onChangeStat__9CGItemObjFi(int param_1,int param_2)

{
  if (0x27 < param_2) {
    return;
  }
  if (param_2 < 0x26) {
    return;
  }
  *(uint *)(param_1 + 0x1c0) = *(uint *)(param_1 + 0x1c0) & 0xfff7fffe;
  return;
}

