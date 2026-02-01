// Function: __AXPrintStudio
// Entry: 80192dac
// Size: 1016 bytes

void __AXPrintStudio(void)

{
  int iVar1;
  
  iVar1 = DAT_8032f268 / 0xa0 + (DAT_8032f268 >> 0x1f);
  iVar1 = iVar1 - (iVar1 >> 0x1f);
  if (iVar1 == 0) {
    DAT_8032f268 = 0;
    DAT_80314900 = 0;
    DAT_80314904 = 0;
  }
  else {
    if (0x14 < iVar1) {
      iVar1 = 0x14;
    }
    if (iVar1 < -0x14) {
      iVar1 = -0x14;
    }
    DAT_80314900 = DAT_8032f268;
    DAT_80314904 = -(short)iVar1;
    DAT_8032f268 = DAT_8032f268 + iVar1 * -0xa0;
  }
  iVar1 = DAT_8032f26c / 0xa0 + (DAT_8032f26c >> 0x1f);
  iVar1 = iVar1 - (iVar1 >> 0x1f);
  if (iVar1 == 0) {
    DAT_8032f26c = 0;
    DAT_80314906 = 0;
    DAT_8031490a = 0;
  }
  else {
    if (0x14 < iVar1) {
      iVar1 = 0x14;
    }
    if (iVar1 < -0x14) {
      iVar1 = -0x14;
    }
    DAT_80314906 = DAT_8032f26c;
    DAT_8031490a = -(short)iVar1;
    DAT_8032f26c = DAT_8032f26c + iVar1 * -0xa0;
  }
  iVar1 = DAT_8032f270 / 0xa0 + (DAT_8032f270 >> 0x1f);
  iVar1 = iVar1 - (iVar1 >> 0x1f);
  if (iVar1 == 0) {
    DAT_8032f270 = 0;
    DAT_8031490c = 0;
    DAT_80314910 = 0;
  }
  else {
    if (0x14 < iVar1) {
      iVar1 = 0x14;
    }
    if (iVar1 < -0x14) {
      iVar1 = -0x14;
    }
    DAT_8031490c = DAT_8032f270;
    DAT_80314910 = -(short)iVar1;
    DAT_8032f270 = DAT_8032f270 + iVar1 * -0xa0;
  }
  iVar1 = DAT_8032f274 / 0xa0 + (DAT_8032f274 >> 0x1f);
  iVar1 = iVar1 - (iVar1 >> 0x1f);
  if (iVar1 == 0) {
    DAT_8032f274 = 0;
    DAT_80314912 = 0;
    DAT_80314916 = 0;
  }
  else {
    if (0x14 < iVar1) {
      iVar1 = 0x14;
    }
    if (iVar1 < -0x14) {
      iVar1 = -0x14;
    }
    DAT_80314912 = DAT_8032f274;
    DAT_80314916 = -(short)iVar1;
    DAT_8032f274 = DAT_8032f274 + iVar1 * -0xa0;
  }
  iVar1 = DAT_8032f278 / 0xa0 + (DAT_8032f278 >> 0x1f);
  iVar1 = iVar1 - (iVar1 >> 0x1f);
  if (iVar1 == 0) {
    DAT_8032f278 = 0;
    DAT_80314918 = 0;
    DAT_8031491c = 0;
  }
  else {
    if (0x14 < iVar1) {
      iVar1 = 0x14;
    }
    if (iVar1 < -0x14) {
      iVar1 = -0x14;
    }
    DAT_80314918 = DAT_8032f278;
    DAT_8031491c = -(short)iVar1;
    DAT_8032f278 = DAT_8032f278 + iVar1 * -0xa0;
  }
  iVar1 = DAT_8032f27c / 0xa0 + (DAT_8032f27c >> 0x1f);
  iVar1 = iVar1 - (iVar1 >> 0x1f);
  if (iVar1 == 0) {
    DAT_8032f27c = 0;
    DAT_8031491e = 0;
    DAT_80314922 = 0;
  }
  else {
    if (0x14 < iVar1) {
      iVar1 = 0x14;
    }
    if (iVar1 < -0x14) {
      iVar1 = -0x14;
    }
    DAT_8031491e = DAT_8032f27c;
    DAT_80314922 = -(short)iVar1;
    DAT_8032f27c = DAT_8032f27c + iVar1 * -0xa0;
  }
  iVar1 = DAT_8032f280 / 0xa0 + (DAT_8032f280 >> 0x1f);
  iVar1 = iVar1 - (iVar1 >> 0x1f);
  if (iVar1 == 0) {
    DAT_8032f280 = 0;
    DAT_80314924 = 0;
    DAT_80314928 = 0;
  }
  else {
    if (0x14 < iVar1) {
      iVar1 = 0x14;
    }
    if (iVar1 < -0x14) {
      iVar1 = -0x14;
    }
    DAT_80314924 = DAT_8032f280;
    DAT_80314928 = -(short)iVar1;
    DAT_8032f280 = DAT_8032f280 + iVar1 * -0xa0;
  }
  iVar1 = DAT_8032f284 / 0xa0 + (DAT_8032f284 >> 0x1f);
  iVar1 = iVar1 - (iVar1 >> 0x1f);
  if (iVar1 == 0) {
    DAT_8032f284 = 0;
    DAT_8031492a = 0;
    DAT_8031492e = 0;
  }
  else {
    if (0x14 < iVar1) {
      iVar1 = 0x14;
    }
    if (iVar1 < -0x14) {
      iVar1 = -0x14;
    }
    DAT_8031492a = DAT_8032f284;
    DAT_8031492e = -(short)iVar1;
    DAT_8032f284 = DAT_8032f284 + iVar1 * -0xa0;
  }
  iVar1 = DAT_8032f288 / 0xa0 + (DAT_8032f288 >> 0x1f);
  iVar1 = iVar1 - (iVar1 >> 0x1f);
  if (iVar1 == 0) {
    DAT_8032f288 = 0;
    DAT_80314930 = 0;
    DAT_80314934 = 0;
  }
  else {
    if (0x14 < iVar1) {
      iVar1 = 0x14;
    }
    if (iVar1 < -0x14) {
      iVar1 = -0x14;
    }
    DAT_80314930 = DAT_8032f288;
    DAT_80314934 = -(short)iVar1;
    DAT_8032f288 = DAT_8032f288 + iVar1 * -0xa0;
  }
  DCFlushRange(&DAT_80314900,0x36);
  return;
}

