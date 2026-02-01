// Function: Init__9CGObjWorkFiP8CRomWorki
// Entry: 800a2ca8
// Size: 228 bytes

void Init__9CGObjWorkFiP8CRomWorki(CGObjWork *gObjWork,int32_t param_2,short *param_3,short param_4)

{
  gObjWork->m_baseDataIndex = param_2;
  gObjWork->m_id = *param_3 + param_4;
  gObjWork->m_param1 = param_3[1];
  gObjWork->m_param2 = param_3[2];
  gObjWork->m_maxHp = param_3[3];
  gObjWork->m_strength = param_3[4];
  gObjWork->m_magic = param_3[5];
  gObjWork->m_defense = param_3[6];
  gObjWork->m_romWorkPtr = (uint16_t *)(param_3 + 8);
  memcpy(gObjWork->m_elementResistances,gObjWork->m_romWorkPtr + 0x6f,0x16);
  memset(gObjWork->m_statusTimers + 3,0,0x4e);
  gObjWork->m_statusValues[0] = 0xffff;
  gObjWork->m_statusValues[1] = 0xffff;
  gObjWork->m_statusValues[2] = 0xffff;
  gObjWork->m_statusValues[3] = 0xffff;
  gObjWork->m_statusValues[4] = 0xffff;
  gObjWork->m_statusValues[5] = 0xffff;
  gObjWork->m_statusValues[6] = 0xffff;
  gObjWork->m_statusValues[7] = 0xffff;
  gObjWork->m_statusValues[8] = 0xffff;
  gObjWork->m_statusValues[9] = 0xffff;
  gObjWork->m_statusValues[10] = 0xffff;
  gObjWork->m_statusValues[0xb] = 0xffff;
  gObjWork->m_statusValues[0xc] = 0xffff;
  gObjWork->m_statusValues[0xd] = 0xffff;
  gObjWork->m_statusValues[0xe] = 0xffff;
  gObjWork->m_statusValues[0xf] = 0xffff;
  gObjWork->m_hp = gObjWork->m_maxHp;
  return;
}

