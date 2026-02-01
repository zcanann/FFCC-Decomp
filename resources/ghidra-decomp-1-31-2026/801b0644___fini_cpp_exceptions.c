// Function: __fini_cpp_exceptions
// Entry: 801b0644
// Size: 52 bytes

void __fini_cpp_exceptions(void)

{
  if (DAT_8032ebf0 != -2) {
    __unregister_fragment();
    DAT_8032ebf0 = -2;
  }
  return;
}

