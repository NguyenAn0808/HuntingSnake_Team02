#include "graphics.h"

void draw_rec(int x0, int x1, int y0, int y1, unsigned int color)
{
	for (int ix = x0; ix < x1; ++ix) {
		GotoXY(ix, y0);
		std::cout << char(196);
	}
}
