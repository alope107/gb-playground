#include <bn_core.h>
#include <bn_sprite_ptr.h>
#include <bn_log.h>
#include <bn_fixed.h>
#include <bn_keypad.h>

#include <bn_vector.h>

#include "bn_sprite_items_dot.h"

int main() {
    bn::core::init();

    bn::vector<bn::vector<bn::sprite_ptr, 13>, 13> dots = {};

    int count = 0;

    for(int y = -80; y <= 80; y+=20) {
        bn::vector<bn::sprite_ptr, 13> new_line = {};
        for(int x = -120; x <= 120; x+=20) {
            BN_LOG("x", x, "y", y);
            count++;
            BN_LOG("count ", count);
            bn::sprite_ptr dot = bn::sprite_items::dot.create_sprite(x, y);
            // if(x > 0) {
            //     bn::fixed scale = 1 + (x/100.0) + (y/100.0);
            //     BN_LOG("scale: ", scale);
            //     dot.set_scale(scale);
            // }
            new_line.push_back(dot);
        }
        dots.push_back(new_line);
        
    }

    int sel_row = 1;
    int sel_col = 3;

    dots[sel_row][sel_col].set_item(bn::sprite_items::dot, 1);

    while(1) {
        if (bn::keypad::left_pressed()) {
            dots[sel_row][sel_col].set_item(bn::sprite_items::dot, 0);
            sel_col--; 
            if(sel_col < 0) {
                sel_col = dots[0].size() - 1;
            }
            dots[sel_row][sel_col].set_item(bn::sprite_items::dot, 1);
        }
        if (bn::keypad::right_pressed()) {
            dots[sel_row][sel_col].set_item(bn::sprite_items::dot, 0);
            sel_col++; 
            if(sel_col >= dots[0].size()) {
                sel_col = 0;
            }
            dots[sel_row][sel_col].set_item(bn::sprite_items::dot, 1);
        }
        if (bn::keypad::up_pressed()) {
            dots[sel_row][sel_col].set_item(bn::sprite_items::dot, 0);
            sel_row--; 
            if(sel_row < 0) {
                sel_row = dots.size() -1;
            }
            dots[sel_row][sel_col].set_item(bn::sprite_items::dot, 1);
        }
        if (bn::keypad::down_pressed()) {
            dots[sel_row][sel_col].set_item(bn::sprite_items::dot, 0);
            sel_row++; 
            if(sel_row >= dots.size()) {
                sel_row = 0;
            }
            dots[sel_row][sel_col].set_item(bn::sprite_items::dot, 1);
        }
        bn::core::update();
    }

    return 0;
}