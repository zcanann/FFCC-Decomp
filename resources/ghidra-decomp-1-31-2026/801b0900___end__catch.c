// Function: __end__catch
// Entry: 801b0900
// Size: 68 bytes

void __end__catch(int *param_1)

{
  if ((*param_1 != 0) && ((code *)param_1[2] != (code *)0x0)) {
    (*(code *)param_1[2])(*param_1,0xffffffff);
  }
  return;
}

