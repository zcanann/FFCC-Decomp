// Function: bgCollision__8CGObjectFv
// Entry: 80080c68
// Size: 156 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void bgCollision__8CGObjectFv(CGObject *gObject)

{
  float fVar1;
  
  fVar1 = FLOAT_80330350;
  gObject->m_stateFlags0 = gObject->m_stateFlags0 & 0x7f;
  gObject->m_stateFlags0 = gObject->m_stateFlags0 & 0xbf;
  (gObject->m_radiusCtrl).x = 0.0;
  gObject->m_gravityY = fVar1;
  bgAttribCollision__8CGObjectFv(gObject);
  if ((gObject->m_bgColMask & 1) != 0) {
    DAT_8032ecb9 = 1;
    if (Game.game.m_currentMapId == 0x21) {
      bgWorldCollision__8CGObjectFv(gObject);
    }
    else {
      bgNormalCollision__8CGObjectFv(gObject);
    }
    DAT_8032ecb9 = 0;
  }
  return;
}

