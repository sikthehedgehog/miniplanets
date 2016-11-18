# Miniplanets

This is the source code for Miniplanets, an unique platformer for Mega Drive where you jump'n'run on small 3D planets (the "miniplanets") in a quest to save Qisha's children and restore the Planelago System back to normal.

You can get a prebuilt ROM (and optionally pay if you wish) here:
https://sik.itch.io/miniplanets

## Echo sound engine

This game is powered by the Echo sound engine. For the sake of convenience the prebuilt binaries have been included here, but if you want to replace it with your own copy you can get the library here:

https://github.com/sikthehedgehog/echo

You'll need to replace the following files:

* `data/sound/prog-z80.bin`
* `src-68k/echo.68k`
* `src-68k/esf.68k`

And also make sure to modify the filename in `echo.68k` to `"data/sound/prog-z80.bin"`.
