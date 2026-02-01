// Function: __ct__8CProfileFPc
// Entry: 800212f8
// Size: 112 bytes

OSStopwatch * __ct__8CProfileFPc(OSStopwatch *param_1,undefined4 param_2)

{
  float fVar1;
  OSStopwatch OStack_38;
  
  OSInitStopwatch(param_1,s_no_name_8032f860);
  OSResetStopwatch(param_1);
  OSInitStopwatch(&OStack_38,param_2);
  OSResetStopwatch(&OStack_38);
  fVar1 = FLOAT_8032f854;
  *(float *)((int)&param_1[2].total + 4) = FLOAT_8032f854;
  *(float *)&param_1[2].total = fVar1;
  *(undefined4 *)&param_1[2].min = 0;
  return param_1;
}

