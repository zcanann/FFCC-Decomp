// Function: getReplaceStat__10CGPartyObjFi
// Entry: 8012098c
// Size: 72 bytes

int getReplaceStat__10CGPartyObjFi(undefined4 param_1,int param_2)

{
  if (param_2 != 7) {
    if ((param_2 < 7) && (param_2 == -0x14)) {
      param_2 = -1;
    }
    else {
      param_2 = getReplaceStat__10CGCharaObjFi();
    }
  }
  return param_2;
}

