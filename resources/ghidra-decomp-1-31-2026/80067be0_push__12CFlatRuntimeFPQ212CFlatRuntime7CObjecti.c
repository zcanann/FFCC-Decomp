// Function: push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti
// Entry: 80067be0
// Size: 24 bytes

void push__12CFlatRuntimeFPQ212CFlatRuntime7CObjecti
               (undefined4 param_1,CObject *object,uint32_t param_3)

{
  *object->m_stackPointer = param_3;
  object->m_stackPointer = object->m_stackPointer + 1;
  return;
}

