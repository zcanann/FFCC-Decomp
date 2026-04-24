/*
 * --INFO--
 * PAL Address: 0x80013D70
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void tolower_name_conflict(char* str)
{
    unsigned char c;

    goto test;

loop:
    if (((c >= 'A') && (c <= 'Z')) || ((c >= 0xC0) && (c <= 0xD6)) || ((c >= 0xD8) && (c <= 0xDC))) {
        c += 0x20;
    }

    *str = c;
    str++;

test:
    c = *str;
    if (c != '\0') {
        goto loop;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80013DCC
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void toupper(char* str)
{
    unsigned char c;

    goto test;

loop:
    if (((c >= 'a') && (c <= 'z')) || ((c >= 0xE0) && (c <= 0xF6)) || ((c >= 0xF8) && (c <= 0xFC))) {
        c -= 0x20;
    }

    *str = c;
    str++;

test:
    c = *str;
    if (c != '\0') {
        goto loop;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80013E28
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int toupperLatin1(unsigned char character)
{
    if (((character >= 0x61) && (character <= 0x7A)) || ((character >= 0xE0) && (character <= 0xF6)) ||
        ((character >= 0xF8) && (character <= 0xFC))) {
        character -= 0x20;
    }

    return character;
}
