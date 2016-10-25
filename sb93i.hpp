#ifndef __SB93I_HPP__
#define __SB93I_HPP__

#include <iostream>
#include <fstream>
#include <stack>
#include <cstdlib>
#include <cstring>

#define PROGRAM_LINES   25
#define PROGRAM_COLUMNS 80
#define POP(a, b)       a = pop(stack, true); b = pop(stack, true);
#define IN_BOUNDS(y, x) (y >= 0 && y < PROGRAM_LINES && x >= 0 && x < PROGRAM_COLUMNS)

class PC
{
    public:
        enum { LEFT, RIGHT, UP, DOWN };
        struct { int x; int y; } pos;
        struct { int x; int y; } dir;

        PC()
        {
            pos.x = 0;
            pos.y = 0;
            change_dir(RIGHT);
        }

        void move()
        {
            pos.x = (pos.x + dir.x) % PROGRAM_COLUMNS;  if (pos.x < 0) pos.x += PROGRAM_COLUMNS;
            pos.y = (pos.y + dir.y) % PROGRAM_LINES;    if (pos.y < 0) pos.y += PROGRAM_LINES;
        }

        void change_dir(int new_dir)
        {
            switch(new_dir)
            {
                case LEFT:  dir.x = -1; dir.y = 0;  break;
                case RIGHT: dir.x = 1;  dir.y = 0;  break;
                case UP:    dir.x = 0;  dir.y = -1; break;
                case DOWN:  dir.x = 0;  dir.y = 1;  break;
            }
        }
};

#endif
