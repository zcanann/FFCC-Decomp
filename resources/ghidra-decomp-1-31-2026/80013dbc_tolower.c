// Function: tolower
// Entry: 80013dbc
// Size: 88 bytes

void tolower(byte *string)

{
  byte bVar1;
  
  do {
    bVar1 = *string;
    if (bVar1 == 0) {
      return;
    }
    if (bVar1 < 0x41) {
LAB_80013d88:
      if ((0xbf < bVar1) && (bVar1 < 0xd7)) goto LAB_80013db0;
      if ((0xd7 < bVar1) && (bVar1 < 0xdd)) goto LAB_80013db0;
    }
    else {
      if (0x5a < bVar1) goto LAB_80013d88;
LAB_80013db0:
      bVar1 = bVar1 + 0x20;
    }
    *string = bVar1;
    string = string + 1;
  } while( true );
}

