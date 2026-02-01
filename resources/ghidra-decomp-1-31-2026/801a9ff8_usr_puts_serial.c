// Function: usr_puts_serial
// Entry: 801a9ff8
// Size: 136 bytes

void usr_puts_serial(char *param_1)

{
  char cVar1;
  undefined4 uVar2;
  char local_18 [12];
  
  while( true ) {
    cVar1 = *param_1;
    param_1 = param_1 + 1;
    if (cVar1 == '\0') break;
    uVar2 = GetTRKConnected();
    local_18[1] = 0;
    local_18[0] = cVar1;
    SetTRKConnected(0);
    OSReport(local_18);
    SetTRKConnected(uVar2);
  }
  return;
}

