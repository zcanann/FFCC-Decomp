// Function: HitParticleBG__5CGameFiiiP3VecP10PPPIFPARAM
// Entry: 800147f8
// Size: 116 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void HitParticleBG__5CGameFiiiP3VecP10PPPIFPARAM
               (CGame *game,int effectIndex,int kind,int nodeIndex,Vec *vec,PPPIFPARAM *pppIFParam)

{
  int local_28;
  int local_24;
  int local_20;
  float local_1c;
  float local_18;
  float local_14;
  int32_t local_10;
  int local_c;
  
  local_1c = vec->x;
  local_18 = vec->y;
  local_14 = vec->z;
  local_10 = pppIFParam->m_particleIndex;
  local_c = (int)pppIFParam->m_classId;
  local_28 = effectIndex;
  local_24 = kind;
  local_20 = nodeIndex;
  SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
            (&CFlat,0,1,1,8,&local_28,(CStack *)0x0);
  return;
}

