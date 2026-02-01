// Function: cbForReadAsync
// Entry: 80188a40
// Size: 48 bytes

void cbForReadAsync(undefined4 param_1,int param_2)

{
  if (*(code **)(param_2 + 0x38) != (code *)0x0) {
    (**(code **)(param_2 + 0x38))();
  }
  return;
}

