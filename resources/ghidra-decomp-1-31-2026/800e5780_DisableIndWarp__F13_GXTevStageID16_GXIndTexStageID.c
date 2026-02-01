// Function: DisableIndWarp__F13_GXTevStageID16_GXIndTexStageID
// Entry: 800e5780
// Size: 112 bytes

void DisableIndWarp__F13_GXTevStageID16_GXIndTexStageID(undefined4 param_1,undefined4 param_2)

{
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  
  GXSetTevDirect();
  GXSetNumIndStages(0);
  GXSetIndTexCoordScale(param_2,0,0);
  local_28 = FLOAT_80331180;
  local_24 = FLOAT_80331180;
  local_20 = FLOAT_80331180;
  local_1c = FLOAT_80331180;
  local_18 = FLOAT_80331180;
  local_14 = FLOAT_80331180;
  GXSetIndTexMtx(1,&local_28,1);
  return;
}

