// Function: __construct_array
// Entry: 801af970
// Size: 252 bytes

void __construct_array(void *baseAddress,code *constructor,code *destructor,int objectSize,
                      uint count)

{
  void *pvVar1;
  undefined4 local_18;
  
  pvVar1 = baseAddress;
  for (local_18 = 0; local_18 < count; local_18 = local_18 + 1) {
    (*constructor)(pvVar1,1);
    pvVar1 = (void *)((int)pvVar1 + objectSize);
  }
  if ((local_18 < count) && (destructor != (code *)0x0)) {
    pvVar1 = (void *)((int)baseAddress + objectSize * local_18);
    for (; local_18 != 0; local_18 = local_18 - 1) {
      pvVar1 = (void *)((int)pvVar1 - objectSize);
      (*destructor)(pvVar1,0xffffffff);
    }
  }
  return;
}

