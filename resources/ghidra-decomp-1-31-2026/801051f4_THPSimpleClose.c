// Function: THPSimpleClose
// Entry: 801051f4
// Size: 144 bytes

undefined4 THPSimpleClose(void)

{
  if ((SimpleControl._160_4_ != 0) && (SimpleControl._164_1_ == '\0')) {
    if (SimpleControl._167_1_ == '\0') {
      SimpleControl._165_1_ = 0;
    }
    else if (SimpleControl._165_1_ == '\x01') {
      return 0;
    }
    if (SimpleControl._176_4_ == 0) {
      SimpleControl._160_4_ = 0;
      DVDClose((DVDFileInfo *)&SimpleControl);
      return 1;
    }
  }
  return 0;
}

