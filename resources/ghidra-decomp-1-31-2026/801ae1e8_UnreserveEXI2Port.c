// Function: UnreserveEXI2Port
// Entry: 801ae1e8
// Size: 48 bytes

void UnreserveEXI2Port(void)

{
  (*DAT_8021d058)();
  return;
}

