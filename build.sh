#!/bin/sh

GAMENAME=Miniplanets.bin

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
uftc src-data/globe/raft.4bpp data/globe/raft.uftc
uftc src-data/globe/belt.4bpp data/globe/belt.uftc

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

eif src-data/sound/bell.tfi data/sound/bell.eif
eif src-data/sound/sawtooth.tfi data/sound/sawtooth.eif
eif src-data/sound/distortion.tfi data/sound/distortion.eif
eif src-data/sound/sax.tfi data/sound/sax.eif
eif src-data/sound/guitar.tfi data/sound/guitar.eif
eif src-data/sound/bass.tfi data/sound/bass.eif
eif src-data/sound/synbass.tfi data/sound/synbass.eif
eif src-data/sound/stage1lead.tfi data/sound/stage1lead.eif
eif src-data/sound/bell2.tfi data/sound/bell2.eif
eif src-data/sound/church.tfi data/sound/church.eif
eif src-data/sound/trumpet.tfi data/sound/trumpet.eif
eif src-data/sound/impact.tfi data/sound/impact.eif
ewf src-data/sound/explosion.pcm data/sound/explosion.ewf
ewf src-data/sound/tick.pcm data/sound/tick.ewf
ewf src-data/sound/tock.pcm data/sound/tock.ewf

esf src-data/music/stage_1.mml data/sound/stage_1.esf
esf src-data/music/stage_2.mml data/sound/stage_2.esf
esf src-data/music/stage_3.mml data/sound/stage_3.esf
esf src-data/music/stage_4.mml data/sound/stage_4.esf
esf src-data/music/stage_5.mml data/sound/stage_5.esf
esf src-data/music/boss.mml data/sound/boss.esf
esf src-data/music/title.mml data/sound/title.esf
esf src-data/music/ending.mml data/sound/ending.esf
esf src-data/music/tally.mml data/sound/tally.esf
esf src-data/music/game_over.mml data/sound/game_over.esf

rm -f "$GAMENAME"
asm buildme.68k tmp.bin
mv tmp.bin "$GAMENAME"
