// Function: Init__6CSoundFv
// Entry: 800c810c
// Size: 372 bytes

void Init__6CSoundFv(CSound *sound)

{
  uint uVar1;
  CStage *pCVar2;
  undefined4 uVar3;
  
  pCVar2 = CreateStage__7CMemoryFUlPci(&Memory,0xa4000,s_CSound_80330ce0,0);
  *(CStage **)&sound->field_0x4 = pCVar2;
  uVar3 = __nwa__FUlPQ27CMemory6CStagePci
                    (0x80000,*(undefined4 *)&sound->field_0x4,s_sound_cpp_801db2d4,0x2e);
  *(undefined4 *)&(sound->m_redSound).field_0x4 = uVar3;
  uVar3 = __nwa__FUlPQ27CMemory6CStagePci
                    (0x20000,*(undefined4 *)&sound->field_0x4,s_sound_cpp_801db2d4,0x2f);
  *(undefined4 *)&sound->field_0x228c = uVar3;
  *(undefined4 *)&sound->field_0x22b0 = 0x7f;
  *(undefined4 *)&sound->field_0x22b4 = 0x7f;
  *(undefined4 *)&sound->field_0x22bc = 0x7f;
  *(undefined4 *)&sound->field_0x22b8 = 0x7f;
  *(undefined4 *)&sound->field_0x22d4 = 0;
  ARInit(0,0);
  ARQInit();
  Init__9CRedSoundFPviii
            (&sound->m_redSound,*(undefined4 *)&(sound->m_redSound).field_0x4,0x80000,0x800000,
             0x800000);
  ReportPrint__9CRedSoundFi
            (&sound->m_redSound,
             (-*(uint *)&sound->field_0x22d4 | *(uint *)&sound->field_0x22d4) >> 0x1f);
  uVar3 = GetSoundMode__9CRedSoundFv(&sound->m_redSound);
  uVar1 = countLeadingZeros(uVar3);
  uVar1 = countLeadingZeros(uVar1 >> 5);
  SetSoundMode__9CRedSoundFi(&sound->m_redSound,uVar1 >> 5);
  MusicMasterVolume__9CRedSoundFi((int)&sound->m_redSound,*(int *)&sound->field_0x22b0);
  SeMasterVolume__9CRedSoundFi(&sound->m_redSound,*(int *)&sound->field_0x22b4);
  SetReverb__9CRedSoundFii(&sound->m_redSound,1,4);
  SetReverbDepth__9CRedSoundFiii(&sound->m_redSound,1,0x40,0xf);
  *(undefined4 *)&(sound->m_redSound).field_0x8 = 0;
  *(undefined4 *)&sound->field_0x2290 = 0;
  *(undefined4 *)&sound->field_0x22a0 = 0;
  memset(&sound->field_0x22c0,0xff,8);
  memset(&sound->field_0x22c8,0xff,8);
  *(undefined4 *)&sound->field_0x22d0 = 0;
  return;
}

