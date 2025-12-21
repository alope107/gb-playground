#include <bn_core.h>
#include <bn_sprite_ptr.h>
#include <bn_log.h>
#include <bn_fixed.h>
#include <bn_keypad.h>
#include <bn_backdrop.h>

#include <bn_vector.h>

#include "bn_sprite_items_dot.h"

int tribool(bool minus, bool plus) {
    int val = 0;
    if(minus) val--;
    if(plus) val++;
    return val;
}

int wrap(int value, int max) {
    if(value < 0) {
        value = max;
    }
    if (value > max) {
        value = 0;
    }
    return value;
}

int main() {
    bn::core::init();

    bn::backdrop::set_color(bn::color(20, 20, 31));

    bn::vector<bn::vector<bn::sprite_ptr, 13>, 13> dots = {};

    int count = 0;

    for(int y = -80; y <= 80; y+=20) {
        bn::vector<bn::sprite_ptr, 13> new_line = {};
        for(int x = -120; x <= 120; x+=20) {
            count++;
            bn::sprite_ptr dot = bn::sprite_items::dot.create_sprite(x, y);
            new_line.push_back(dot);
        }
        dots.push_back(new_line);
        
    }

    int sel_row = 1;
    int sel_col = 3;

    dots[sel_row][sel_col].set_item(bn::sprite_items::dot, 1);

    while(1) {
        dots[sel_row][sel_col].set_item(bn::sprite_items::dot, 0);
        sel_col = wrap(sel_col+tribool(bn::keypad::left_pressed(), bn::keypad::right_pressed()), dots[0].size() - 1);
        sel_row = wrap(sel_row+tribool(bn::keypad::up_pressed(), bn::keypad::down_pressed()), dots.size() - 1);
        dots[sel_row][sel_col].set_item(bn::sprite_items::dot, 1);
        bn::core::update();
    }

    return 0;
}