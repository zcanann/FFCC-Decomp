// Function: SePlay__10CRedDriverFiiiiii
// Entry: 801bf540
// Size: 196 bytes

int SePlay__10CRedDriverFiiiiii
              (CRedDriver *redDriver,int param_2,int param_3,int param_4,int param_5,int param_6,
              int param_7)

{
  if (param_2 == -1) {
    if (-1 < param_3) {
      _EntryExecCommand__FPFPi_viiiiiii
                (_SeSepPlaySequence__FPi,param_4,param_3,param_5,param_6,param_7,0,0);
    }
  }
  else if ((((-1 < param_2) && (param_2 < 4)) && (-1 < param_3)) && (param_3 < 0x200)) {
    _EntryExecCommand__FPFPi_viiiiiii
              (_SeBlockPlay__FPi,param_4,param_2,param_3,param_5,param_6,param_7,0);
  }
  return param_4;
}

