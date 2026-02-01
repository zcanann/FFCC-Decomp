// Function: HitParticle__8CGObjectFiiiiP3VecP10PPPIFPARAM
// Entry: 8007cf24
// Size: 200 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void HitParticle__8CGObjectFiiiiP3VecP10PPPIFPARAM
               (CGObject *gObject,int effectIndex,int kind,int nodeIndex,int colliderIndex,Vec *vec,
               PPPIFPARAM *pppIFParam)

{
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  float local_38;
  float local_34;
  float local_30;
  int32_t local_2c;
  int local_28;
  
  local_38 = vec->x;
  local_34 = vec->y;
  local_30 = vec->z;
  local_2c = pppIFParam->m_particleIndex;
  local_28 = (int)pppIFParam->m_classId;
  local_48 = effectIndex;
  local_44 = kind;
  local_40 = nodeIndex;
  local_3c = colliderIndex;
  SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack
            (&CFlat,gObject,2,0xb,9,&local_48,(CStack *)0x0);
  (**(code **)((int)(gObject->base_object).object.m_vtable + 0x3c))
            (gObject,effectIndex,kind,nodeIndex,colliderIndex,vec,pppIFParam);
  return;
}

