// Function: Crc16__6JoyBusFiPUcPUs
// Entry: 800b26d8
// Size: 80 bytes

ushort Crc16__6JoyBusFiPUcPUs(JoyBus *joyBus,int len,byte *data,ushort *crc)

{
  byte bVar1;
  
  while( true ) {
    len = len + -1;
    if (len < 0) break;
    bVar1 = *data;
    data = data + 1;
    *crc = *crc << 8 ^ JoyBusCrcTable[(int)(uint)*crc >> 8 ^ (uint)bVar1];
  }
  return ~*crc;
}

