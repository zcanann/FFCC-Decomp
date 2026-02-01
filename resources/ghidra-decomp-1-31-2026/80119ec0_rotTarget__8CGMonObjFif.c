// Function: rotTarget__8CGMonObjFif
// Entry: 80119ec0
// Size: 180 bytes

/* WARNING: Removing unreachable block (ram,0x80119f58) */
/* WARNING: Removing unreachable block (ram,0x80119ed0) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void rotTarget__8CGMonObjFif(double param_1,CGPrgObj *param_2,int param_3)

{
  double dVar1;
  double dVar2;
  
  if (-1 < param_3) {
    dVar1 = (double)getTargetRot__8CGPrgObjFP8CGPrgObj(param_2,Game.game.m_partyObjArr[param_3]);
    if (param_1 <= (double)FLOAT_80331a48) {
      dVar2 = (double)DstRot__5CMathFff(dVar1,(double)(float)(param_2->object).m_bgFlags,&Math);
      dVar1 = -param_1;
      if ((dVar1 <= dVar2) && (dVar1 = dVar2, param_1 < dVar2)) {
        dVar1 = param_1;
      }
      (param_2->object).m_rotTargetY = (float)((double)(float)(param_2->object).m_bgFlags + dVar1);
    }
    else {
      (param_2->object).m_rotTargetY = (float)dVar1;
    }
  }
  return;
}

