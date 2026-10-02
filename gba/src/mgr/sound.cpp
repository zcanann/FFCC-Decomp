extern "C" {
#include "global.h"
#include "obj.h"
#include "link.h"
#include "sound.h"

struct Sound gSound;

void Sound_Init(struct Sound *sound)
{
}

void Sound_UpdateListener(struct Sound *sound)
{
    struct Actor *actor = &gGame.actors[gPlayerNo];

    sound->listener = actor->pos;
}

void PlaySong(struct Sound *sound, u16 song, void *source)
{
    m4aSongNumStart(song);
}
}
