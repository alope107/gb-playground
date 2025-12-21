#include <bn_core.h>
#include <bn_sprite_ptr.h>
#include <bn_log.h>
#include <bn_fixed.h>
#include <bn_keypad.h>

#include <bn_vector.h>

#include "bn_sprite_items_dot.h"

int main() {
    bn::core::init();

    bn::vector<bn::sprite_ptr, 256> dots = {};

    int count = 0;

    for(int x = -120; x <= 120; x+=20) {
        for(int y = -80; y <= 80; y+=20) {
            BN_LOG("x", x, "y", y);
            count++;
            BN_LOG("count ", count);
            bn::sprite_ptr dot = bn::sprite_items::dot.create_sprite(x, y);
            // if(x > 0) {
            //     bn::fixed scale = 1 + (x/100.0) + (y/100.0);
            //     BN_LOG("scale: ", scale);
            //     dot.set_scale(scale);
            // }
            dots.push_back(dot);
        }
        
    }

    int selected = 1;

    dots[selected].set_item(bn::sprite_items::dot, 1);

    while(1) {
        if (bn::keypad::left_held()) {
            selected++;
            if(selected >= dots.size()) {
                selected = 0;
            }
            dots[selected].set_item(bn::sprite_items::dot, 1);
        }
        bn::core::update();
    }

    return 0;
}