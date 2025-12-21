#include <bn_core.h>
#include <bn_sprite_ptr.h>
#include <bn_log.h>
#include <bn_fixed.h>
#include <bn_keypad.h>
#include <bn_backdrop.h>

#include <bn_vector.h>

#include "bn_sprite_items_dot.h"
#include "bn_sound_items.h"

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

    for(int y = -80; y <= 80; y+=20) {
        bn::vector<bn::sprite_ptr, 13> new_line = {};
        for(int x = -120; x <= 120; x+=20) {
            bn::sprite_ptr dot = bn::sprite_items::dot.create_sprite(x, y);
            new_line.push_back(dot);

        }
        dots.push_back(new_line);
        
    }

    bool popped[13][13]= {};

    int sel_row = 1;
    int sel_col = 3;

    // TODO: Investigate whether to use set_tiles or set_item
    dots[sel_row][sel_col].set_item(bn::sprite_items::dot, 1);

    while(1) {
        if(popped[sel_row][sel_col]) {
            dots[sel_row][sel_col].set_item(bn::sprite_items::dot, 2);
        } else {
            dots[sel_row][sel_col].set_item(bn::sprite_items::dot, 0);
        }
        
        sel_col = wrap(sel_col+tribool(bn::keypad::left_pressed(), bn::keypad::right_pressed()), dots[0].size() - 1);
        sel_row = wrap(sel_row+tribool(bn::keypad::up_pressed(), bn::keypad::down_pressed()), dots.size() - 1);
        if(bn::keypad::a_pressed() && !popped[sel_row][sel_col]) {
            popped[sel_row][sel_col] = true;
            bn::sound_items::pop.play();
        }

        if(popped[sel_row][sel_col]) {
            dots[sel_row][sel_col].set_item(bn::sprite_items::dot, 3);
        } else {
            dots[sel_row][sel_col].set_item(bn::sprite_items::dot, 1);
        }

        if(bn::keypad::start_pressed()) {
            for(int row = 0; row < 9; row++) {
                for(int col = 0; col < 13; col++) {
                    dots[row][col].set_item(bn::sprite_items::dot, 0);
                    popped[row][col] = false;
                }
            }
        }

        bn::core::update();
    }

    return 0;
}