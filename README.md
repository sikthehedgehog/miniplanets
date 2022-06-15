# Miniplanets

This is the source code for Miniplanets, an unique platformer for Mega Drive where you jump'n'run on small 3D planets (the "miniplanets") in a quest to save Qisha's children and restore the Planelago System back to normal.

You can get a prebuilt ROM here:
https://sik.itch.io/miniplanets

This repo now hosts the REMIX Ver. version, which upgrades the graphics and improves the music. If you want to download the last non-REMIX version check [commit `104ce86dc5ebc57909019908b2002e872314941e`](https://github.com/sikthehedgehog/miniplanets/tree/104ce86dc5ebc57909019908b2002e872314941e).

## Tools you'll need

The shell script has been written for Linux, sorry Windows users!

Though in detail in `tools/README`, in short you can get nearly all the tools simply by getting the so-called [mdtools pack](https://github.com/sikthehedgehog/mdtools), and the Sona tools from [Sona's website](https://www.arkagis.com/sona) (included with the sound driver). Additionally, you're going to need `asm68k.exe` (for now, hopefully we can replace this with a free assembler soon). Either way, once you have everything just copy the executables into the `tools` directory.

## Sona sound driver

Since REMIX Ver., this game is powered by the Sona sound driver. For the sake of convenience the prebuilt binaries have been included here, but if you want to replace it with your own copy you can get the library here:

https://www.arkagis.com/sona

You'll need to replace the files in the `sona` folder with the ones from `api-asm` in Sona's source code.

## Echo sound driver

Prior to REMIX Ver. (i.e. up to REV03) this game used the Echo sound driver instead. Again, the prebuilt binary was included in those versions but you can replace it with your own copy you can get the library here:

https://github.com/sikthehedgehog/echo

You'll need to replace the following files:

* `data/sound/prog-z80.bin`
* `src-68k/echo.68k`
* `src-68k/esf.68k`

And also make sure to modify the filename in `echo.68k` to `"data/sound/prog-z80.bin"`.
