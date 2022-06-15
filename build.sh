#!/bin/sh

GAMENAME=Miniplanets.bin
BGMDIR=bgm
SFXDIR=sfx
VOICEDIR=voices

asm() { wine tools/asm68k.exe /p $1, $2, , listing.txt ; }
gfx() { ./tools/mdtiler $1 ; }
slz() { ./tools/slz $1 $2 ; }
uftc() { ./tools/uftc $1 $2 ; }
eif() { ./tools/tfi2eif $1 $2 ; }
ewf() { ./tools/pcm2ewf $1 $2 ; }
esf() { ./tools/mml2esf $1 $2 ; }

gfx src-data/common/gfxbuild
slz src-data/common/font.4bpp data/common/font.slz
cat src-data/common/background.4bpp > src-data/common/universe.blob
cat src-data/common/background.blob >> src-data/common/universe.blob
slz src-data/common/universe.blob data/common/universe.slz
slz src-data/common/void.4bpp data/common/void.slz
slz src-data/common/game_over.4bpp data/common/game_over.slz

gfx src-data/qisha/gfxbuild
slz src-data/qisha/side.4bpp data/qisha/side.slz
slz src-data/qisha/back.4bpp data/qisha/back.slz
slz src-data/qisha/children.4bpp data/qisha/children.slz
slz src-data/qisha/stars.4bpp data/qisha/stars.slz

gfx src-data/player/gfxbuild
uftc src-data/player/player_h.4bpp data/player/player_h.uftc
uftc src-data/player/player_v.4bpp data/player/player_v.uftc
uftc src-data/player/player_d.4bpp data/player/player_d.uftc
uftc src-data/player/player_x.4bpp data/player/player_x.uftc
gfx src-data/ingame/gfxbuild
slz src-data/ingame/ingame.4bpp data/ingame/ingame.slz
gfx src-data/globe/gfxbuild
slz src-data/globe/globe.4bpp data/globe/globe.slz
#uftc src-data/globe/raft.4bpp data/globe/raft.uftc
#uftc src-data/globe/belt_h.4bpp data/globe/belt_h.uftc
#uftc src-data/globe/belt_v.4bpp data/globe/belt_v.uftc
#uftc data/globe/water.4bpp data/globe/water.uftc
#uftc data/globe/fire.4bpp data/globe/fire.uftc
slz data/globe/water.4bpp data/globe/water.slz
slz data/globe/fire.4bpp data/globe/fire.slz
#slz src-data/globe/belt_h.4bpp data/globe/belt_h.slz
#slz src-data/globe/belt_v.4bpp data/globe/belt_v.slz
cat src-data/globe/belt_h.4bpp src-data/globe/belt_v.4bpp > src-data/globe/belt.4bpp && \
slz src-data/globe/belt.4bpp data/globe/belt.slz

gfx src-data/title/gfxbuild
slz src-data/title/miniplanets.4bpp data/title/miniplanets.slz
slz src-data/title/menu.4bpp data/title/menu.slz
slz src-data/title/other.4bpp data/title/other.slz
gfx src-data/logo/gfxbuild
slz src-data/logo/logo.4bpp data/logo/logo.slz
gfx src-data/password/gfxbuild
slz src-data/password/led.4bpp data/password/led.slz

gfx src-data/credits/gfxbuild
cat src-data/credits/foreground.4bpp >> src-data/credits/foreground.blob
slz src-data/credits/foreground.blob data/credits/foreground.slz

for a in $BGMDIR/*.mml ; do ./tools/mml2sona $a ${a%.mml}.sona ; done
for a in $SFXDIR/*.mml ; do ./tools/mml2sona $a ${a%.mml}.sona ; done
for a in $VOICEDIR/*.tfi ; do ./tools/tfi2spat $a ${a%.tfi}.spat ; done
for a in $VOICEDIR/*.wav ; do ./tools/wav2swav $a ${a%.wav}.swav ; done

rm -f "$GAMENAME"
#asm buildme.68k tmp.bin && ./tools/romfix -d -z -4 tmp.bin && mv tmp.bin "$GAMENAME"
asm buildme.68k tmp.bin && ./tools/romfix -d -z tmp.bin && mv tmp.bin "$GAMENAME"
