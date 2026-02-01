// Function: __dt__6CSoundFv
// Entry: 800c8a1c
// Size: 100 bytes

CSound * __dt__6CSoundFv(CSound *sound,short param_2)

{
  if (sound != (CSound *)0x0) {
    *(undefined ***)sound = &PTR_PTR_s_CSound_8021056c;
    __dt__9CRedSoundFv(&sound->m_redSound,0xffff);
    if (0 < param_2) {
      __dl__FPv(sound);
    }
  }
  return sound;
}

