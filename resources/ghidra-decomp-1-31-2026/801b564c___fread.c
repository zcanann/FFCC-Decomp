// Function: __fread
// Entry: 801b564c
// Size: 848 bytes

uint __fread(void *buffer,uint size,int count,FILE *file)

{
  bool bVar1;
  int iVar2;
  ulong uVar3;
  uint uVar4;
  uint uVar5;
  uchar *puVar6;
  uint local_28 [3];
  
  iVar2 = fwide(file,0);
  if (iVar2 == 0) {
    fwide(file,0xffffffff);
  }
  uVar5 = size * count;
  if (((uVar5 == 0) || (*(char *)((int)&file->file_state + 2) != '\0')) ||
     ((*(ushort *)&file->file_mode >> 6 & 7) == 0)) {
    return 0;
  }
  bVar1 = true;
  if (((*(byte *)((int)&file->file_mode + 1) >> 3 & 1) != 0) &&
     ((*(byte *)&file->file_mode >> 1 & 3) != 2)) {
    bVar1 = false;
  }
  if ((*(byte *)&file->file_state >> 5 == 0) && ((*(byte *)&file->file_mode >> 3 & 1) != 0)) {
    *(byte *)&file->file_state = *(byte *)&file->file_state & 0x1f | 0x40;
    file->buffer_length = 0;
  }
  if (*(byte *)&file->file_state >> 5 < 2) {
    *(undefined *)((int)&file->file_state + 2) = 1;
    file->buffer_length = 0;
    return 0;
  }
  if (((*(byte *)&file->file_mode >> 1 & 1) != 0) &&
     (iVar2 = __flush_line_buffered_output_files(), iVar2 != 0)) {
    *(undefined *)((int)&file->file_state + 2) = 1;
    file->buffer_length = 0;
    return 0;
  }
  uVar4 = 0;
  if ((uVar5 != 0) && (2 < *(byte *)&file->file_state >> 5)) {
    do {
      iVar2 = fwide(file,0);
      if (iVar2 == 1) {
        uVar4 = uVar4 + 2;
        uVar5 = uVar5 - 2;
        *(undefined2 *)buffer =
             *(undefined2 *)(file->ungetc_buffer_2_ + ((*(byte *)&file->file_state >> 4 & 0xe) - 3))
        ;
        buffer = (void *)((int)buffer + 2);
      }
      else {
        uVar4 = uVar4 + 1;
        uVar5 = uVar5 - 1;
        *(char *)buffer = file->ungetc_buffer_2_[(*(byte *)&file->file_state >> 5) - 3];
        buffer = (void *)((int)buffer + 1);
      }
      *(byte *)&file->file_state =
           ((*(byte *)&file->file_state >> 5) - 1) * ' ' | *(byte *)&file->file_state & 0x1f;
    } while ((uVar5 != 0) && (2 < *(byte *)&file->file_state >> 5));
    if (*(byte *)&file->file_state >> 5 == 2) {
      file->buffer_length = file->save_buffer_length;
    }
  }
  if ((uVar5 != 0) && ((file->buffer_length != 0 || (bVar1)))) {
    while ((file->buffer_length != 0 || (iVar2 = __load_buffer(file,0,0), iVar2 == 0))) {
      local_28[0] = file->buffer_length;
      if (uVar5 < file->buffer_length) {
        local_28[0] = uVar5;
      }
      memcpy(buffer,file->buffer_ptr,local_28[0]);
      uVar5 = uVar5 - local_28[0];
      buffer = (void *)((int)buffer + local_28[0]);
      uVar4 = uVar4 + local_28[0];
      file->buffer_ptr = file->buffer_ptr + local_28[0];
      file->buffer_length = file->buffer_length - local_28[0];
      if ((uVar5 == 0) || (!bVar1)) goto LAB_801b58f4;
    }
    if (iVar2 == 1) {
      *(undefined *)((int)&file->file_state + 2) = 1;
      file->buffer_length = 0;
    }
    else {
      *(byte *)&file->file_state = *(byte *)&file->file_state & 0x1f;
      *(undefined *)((int)&file->file_state + 1) = 1;
      file->buffer_length = 0;
    }
    uVar5 = 0;
  }
LAB_801b58f4:
  if ((uVar5 != 0) && (!bVar1)) {
    puVar6 = file->buffer;
    uVar3 = file->buffer_size;
    file->buffer = (uchar *)buffer;
    file->buffer_size = uVar5;
    iVar2 = __load_buffer(file,local_28,1);
    if (iVar2 != 0) {
      if (iVar2 == 1) {
        *(undefined *)((int)&file->file_state + 2) = 1;
        file->buffer_length = 0;
      }
      else {
        *(byte *)&file->file_state = *(byte *)&file->file_state & 0x1f;
        *(undefined *)((int)&file->file_state + 1) = 1;
        file->buffer_length = 0;
      }
    }
    file->buffer = puVar6;
    uVar4 = uVar4 + local_28[0];
    file->buffer_size = uVar3;
    __prep_buffer(file);
    file->buffer_length = 0;
  }
  return uVar4 / size;
}

