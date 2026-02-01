// Function: SetClassWork__8CGObjectFii
// Entry: 8007ce64
// Size: 192 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void SetClassWork__8CGObjectFii(CGObject *gObject,int param_2,void *param_3)

{
  gObject->m_ownerType = (int8_t)param_2;
  gObject->m_classWorkIndex = (uint8_t)param_3;
  if (param_2 == 1) {
    gObject->m_scriptHandle = (void **)(Game.game.m_monWorkArr + (int)param_3);
    gObject->m_scriptHandle[3] = gObject;
    gObject->m_scriptHandle[2] = param_3;
    Game.game.m_scriptWork[0][0][(int)param_3] = (uint32_t)gObject;
    Game.game.m_scriptWork[2][0][(int)param_3] = (uint32_t)gObject->m_scriptHandle;
    return;
  }
  if ((param_2 < 1) && (-1 < param_2)) {
    gObject->m_scriptHandle =
         (void **)(Game.game.m_caravanWorkArr + Game.game.m_gameWork.m_wmBackupParams[(int)param_3])
    ;
    gObject->m_scriptHandle[2] = (void *)Game.game.m_gameWork.m_wmBackupParams[(int)param_3];
    gObject->m_scriptHandle[3] = gObject;
    Game.game.m_scriptFoodBase[(int)param_3] = (uint32_t)gObject->m_scriptHandle;
    return;
  }
  gObject->m_scriptHandle = (void **)0x0;
  return;
}

