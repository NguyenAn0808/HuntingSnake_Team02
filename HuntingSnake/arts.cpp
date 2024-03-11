#include "arts.h"

void drawMenuSnake(int pos_x, int pos_y, std::string pic)
{
    GotoXY(pos_x, pos_y);
    for (auto i : pic) {
        switch (i)
        {
        case '1': case '2':
            text_color(BG_COLOR, colorCode::LIGHT_YELLOW);
            break;
        case '3': case '4': case '6': case '7': case '5':
            text_color(BG_COLOR, colorCode::DARK_YELLOW);
            break;
        default:
            text_color(BG_COLOR, colorCode::BLACK);
            break;
        }
        if (i > 32) cout << (char)219;
        else cout << i;
    }
}

void drawHSnake(int pos_x, int pos_y)
{
    text_color(BG_COLOR, TXT_COLOR);
    for (auto i : HSnake) {
        GotoXY(pos_x, pos_y);
        if (i == '\n') {
            ++pos_y;
            cout << '\n';
        }
        else cout << i;
    }
}
