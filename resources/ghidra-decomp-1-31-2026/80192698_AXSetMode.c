// Function: AXSetMode
// Entry: 80192698
// Size: 20 bytes

void AXSetMode(int param_1)

{
  if (DAT_8032f238 == param_1) {
    return;
  }
  DAT_8032f238 = param_1;
  return;
}

