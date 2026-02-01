// Function: GetAutoID__9CRedSoundFv
// Entry: 801cca80
// Size: 44 bytes

uint GetAutoID__9CRedSoundFv(void)

{
  do {
    DAT_8032f4c4 = DAT_8032f4c4 + 1 & 0x7fffffff;
  } while (DAT_8032f4c4 == 0);
  return DAT_8032f4c4;
}

