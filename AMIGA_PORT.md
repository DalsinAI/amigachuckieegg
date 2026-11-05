# Chuckie Egg for AmigaOS 3.x

- Upstream source: `https://github.com/pbrook/Chuckie-Egg`
- Imported commit: `e180046` ("Really fix build")
- Licence: GPL 3 (`COPYING`)

## Target

AmigaOS 3.x / AmiCradle, Motorola 68040 + FPU, on acsdl12 (our SDL 1.2 on
ACGame and AHI). This is upstream's plain SDL game, `chuckie`; the OpenGL
ones (`glchuckie`, `3dchuckie`) and the curses one are not built.

## Build

    make -f amiga/Makefile.amigaos \
        STOVE=/path/to/openamigagcc-16.2.0-open4-x86_64-linux \
        NDK=/path/to/gfopensdk/OpenNDK/Include_H \
        ACSDL=/path/to/amicradle-guest/gameports/acsdl12

acsdl12 is built with its own `Makefile.amigaos`. This gives
`build/amigaos/ChuckieEgg/` with `chuckie`, this ReadMe, `COPYING` and their
icons, and `ChuckieEgg.info` beside the drawer. The sprites and the eight
levels are compiled into the program, so it needs no data files and runs
from anywhere. The icons are made from upstream's `chuckie.png` with
AmiCradle's `port_icons.py` from `amiga/icons/icons.json`.

## Playing

320x240 in 16 colours, RTG or AGA (`chuckie 2` doubles it to 640x480).
Keys: cursor keys or `A` `Z` `,` `.` to move, Space to jump, `Q` or Esc
to quit; a joystick on ACGame's first pad works too. Sound is the game's
two beeper channels through AHI.

## Changes for the Amiga

All under `#ifdef __amigaos__`:

- `sdl.c`: scale 1 (320x240) by default instead of 2; `SDL_Quit` at exit;
  no `SDL_AddTimer` (acsdl12 has no timers).
- `sdl-input.c`: in place of waiting for the timer's event, `PollKeys`
  takes the waiting events and then sleeps with `SDL_Delay` until the next
  30 ms frame is due. Frame skipping when late works as before.
- `amiga/config.h` in place of configure's; `amiga/stack.c` sets a 64 KB
  stack.

Byte order: nothing to change. The game reads no files; its sprites and
levels are byte arrays, and its sound is 16-bit samples in the machine's
order (`AUDIO_S16SYS`), which acsdl12 takes as they are.

State: builds and links. Not yet run in a lab or on a real 68040.
