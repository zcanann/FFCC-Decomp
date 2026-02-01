// Function: Printf__7CSystemFPce
// Entry: 80021efc
// Size: 184 bytes

void Printf__7CSystemFPce
               (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
               undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  byte in_cr1;
  undefined4 local_278;
  undefined4 local_274;
  undefined4 local_270;
  undefined4 local_26c;
  undefined4 local_268;
  undefined4 local_264;
  undefined4 local_260;
  undefined4 local_25c;
  undefined8 local_258;
  undefined8 local_250;
  undefined8 local_248;
  undefined8 local_240;
  undefined8 local_238;
  undefined8 local_230;
  undefined8 local_228;
  undefined8 local_220;
  undefined4 local_218;
  undefined *local_214;
  undefined4 *local_210;
  undefined auStack_20c [524];
  
  if ((bool)(in_cr1 >> 1 & 1)) {
    local_258 = param_1;
    local_250 = param_2;
    local_248 = param_3;
    local_240 = param_4;
    local_238 = param_5;
    local_230 = param_6;
    local_228 = param_7;
    local_220 = param_8;
  }
  if ((MiniGamePcs._25732_4_ & 0x1000) != 0) {
    local_214 = &stack0x00000008;
    local_210 = &local_278;
    local_218 = 0x2000000;
    local_278 = param_9;
    local_274 = param_10;
    local_270 = param_11;
    local_26c = param_12;
    local_268 = param_13;
    local_264 = param_14;
    local_260 = param_15;
    local_25c = param_16;
    vsprintf(auStack_20c,param_10,&local_218);
    OSReport(auStack_20c);
    Printf__4CUSBFPce(&USB,auStack_20c);
  }
  return;
}

