// Function: __fwrite
// Entry: 801b52c4
// Size: 780 bytes

uint __fwrite(void *buffer,uint size,int count,FILE *file)

{
  bool bVar1;
  bool bVar2;
  ushort uVar3;
  int iVar4;
  int iVar5;
  uchar *puVar6;
  ulong uVar7;
  ulong uVar8;
  uint local_28 [3];
  
  iVar4 = fwide(file,0);
  if (iVar4 == 0) {
    fwide(file,0xffffffff);
  }
  uVar7 = size * count;
  if (((uVar7 == 0) || (*(char *)((int)&file->file_state + 2) != '\0')) ||
     (uVar3 = *(ushort *)&file->file_mode >> 6 & 7, uVar3 == 0)) {
    return 0;
  }
  if (uVar3 == 2) {
    __stdio_atexit();
  }
  bVar2 = true;
  bVar1 = false;
  if (((*(byte *)((int)&file->file_mode + 1) >> 3 & 1) == 0) ||
     ((*(byte *)&file->file_mode >> 1 & 3) == 2)) {
    bVar1 = true;
  }
  if ((!bVar1) && ((*(byte *)&file->file_mode >> 1 & 3) != 1)) {
    bVar2 = false;
  }
  if ((*(byte *)&file->file_state >> 5 == 0) && ((*(byte *)&file->file_mode >> 3 & 2) != 0)) {
    if (((*(byte *)&file->file_mode >> 3 & 4) != 0) && (iVar4 = fseek(file,0,2), iVar4 != 0)) {
      return 0;
    }
    *(byte *)&file->file_state = *(byte *)&file->file_state & 0x1f | 0x20;
    __prep_buffer(file);
  }
  if (*(byte *)&file->file_state >> 5 != 1) {
    *(undefined *)((int)&file->file_state + 2) = 1;
    file->buffer_length = 0;
    return 0;
  }
  iVar4 = 0;
  if (uVar7 != 0) {
    if ((file->buffer_ptr != file->buffer) || (bVar2)) {
      file->buffer_length = file->buffer_size - ((int)file->buffer_ptr - (int)file->buffer);
      while( true ) {
        iVar5 = 0;
        local_28[0] = file->buffer_length;
        if (uVar7 < file->buffer_length) {
          local_28[0] = uVar7;
        }
        if ((((*(byte *)&file->file_mode >> 1 & 3) == 1) && (local_28[0] != 0)) &&
           (iVar5 = __memrchr(buffer,10), iVar5 != 0)) {
          local_28[0] = (iVar5 + 1) - (int)buffer;
        }
        if (local_28[0] != 0) {
          memcpy(file->buffer_ptr,buffer,local_28[0]);
          buffer = (void *)((int)buffer + local_28[0]);
          iVar4 = iVar4 + local_28[0];
          uVar7 = uVar7 - local_28[0];
          file->buffer_ptr = file->buffer_ptr + local_28[0];
          file->buffer_length = file->buffer_length - local_28[0];
        }
        if ((((file->buffer_length == 0) || (iVar5 != 0)) ||
            ((*(byte *)&file->file_mode >> 1 & 3) == 0)) &&
           (iVar5 = __flush_buffer(file,0), iVar5 != 0)) break;
        if ((uVar7 == 0) || (!bVar2)) goto LAB_801b552c;
      }
      *(undefined *)((int)&file->file_state + 2) = 1;
      uVar7 = 0;
      file->buffer_length = 0;
    }
  }
LAB_801b552c:
  if ((uVar7 != 0) && (!bVar2)) {
    puVar6 = file->buffer;
    uVar8 = file->buffer_size;
    file->buffer = (uchar *)buffer;
    file->buffer_size = uVar7;
    file->buffer_ptr = (uchar *)((int)buffer + uVar7);
    iVar5 = __flush_buffer(file,local_28);
    if (iVar5 != 0) {
      *(undefined *)((int)&file->file_state + 2) = 1;
      file->buffer_length = 0;
    }
    file->buffer = puVar6;
    iVar4 = iVar4 + local_28[0];
    file->buffer_size = uVar8;
    __prep_buffer(file);
    file->buffer_length = 0;
  }
  if ((*(byte *)&file->file_mode >> 1 & 3) != 2) {
    file->buffer_length = 0;
  }
  return (iVar4 + (size - 1)) / size;
}

