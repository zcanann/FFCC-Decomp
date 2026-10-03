/* Objdiff comparison view only. The final image links the original objects,
   allowing COMMON definitions to coalesce across translation units. */
SECTIONS
{
    .common (NOLOAD) : { *(COMMON) }
}
INSERT AFTER .bss;
