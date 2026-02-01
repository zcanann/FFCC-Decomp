// Function: ChangeMogMode__6CCharaFi
// Entry: 800e10c0
// Size: 136 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void ChangeMogMode__6CCharaFi(CChara *chara,int mogMode)

{
  if (mogMode == 0) {
    if (m_mogWork._36_4_ != 0) {
      StopSe__6CSoundFi(&Sound,m_mogWork._36_4_);
      m_mogWork._36_4_ = 0;
    }
  }
  else {
    memset(&m_mogWork,0,0x2c);
    *(undefined4 *)&chara->field_0x200c = 0x140;
    *(undefined4 *)&chara->field_0x2010 = 0xe0;
    *(undefined4 *)&chara->field_0x2004 = 0;
  }
  return;
}

