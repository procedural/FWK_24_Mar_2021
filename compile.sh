clang test.c         -Wno-everything -lm -ldl -pthread -o test
clang test_collide.c -Wno-everything -lm -ldl -pthread -o test_collide
clang test_cubemap.c -Wno-everything -lm -ldl -pthread -o test_cubemap
clang test_script.c  -Wno-everything -lm -ldl -pthread -o test_script
clang test_sprite.c  -Wno-everything -lm -ldl -pthread -o test_sprite
clang test_video.c   -Wno-everything -lm -ldl -pthread -o test_video