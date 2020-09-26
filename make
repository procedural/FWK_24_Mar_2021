#!/bin/bash

sudo apt-get install xorg-dev libglfw3-dev libassimp-dev

clang   3rd/3rd_tools/ass2iqe.c   -I. -Wno-everything -lm -lpthread -ldl -g -lassimp -o 3rd/3rd_tools/ass2iqe
clang   3rd/3rd_tools/mid2wav.c   -I. -Wno-everything -lm -lpthread -ldl -g          -o 3rd/3rd_tools/mid2wav
clang++ 3rd/3rd_tools/iqe2iqm.cpp -I. -Wno-everything -lm -lpthread -ldl -g          -o 3rd/3rd_tools/iqe2iqm

clang test.c         -Wno-everything -lm -lpthread -ldl -g -o test
clang test_cubemap.c -Wno-everything -lm -lpthread -ldl -g -o test_cubemap
clang test_collide.c -Wno-everything -lm -lpthread -ldl -g -o test_collide
clang test_sprite.c  -Wno-everything -lm -lpthread -ldl -g -o test_sprite
clang test_video.c   -Wno-everything -lm -lpthread -ldl -g -o test_video
clang test_script.c  -Wno-everything -lm -lpthread -ldl -g -o test_script
