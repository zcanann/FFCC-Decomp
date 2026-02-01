// Function: PPCHalt
// Entry: 8017b4d4
// Size: 20 bytes

void PPCHalt(void)

{
  sync(0);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

