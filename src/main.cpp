#include <bn_core.h>
#include <bn_sprite_ptr.h>
#include <bn_log.h>
#include <bn_fixed.h>

#include <bn_vector.h>

#include "bn_sprite_items_dot.h"

int main() {
    bn::core::init();

    bn::vector<bn::sprite_ptr, 36> dots = {};

    for(int x = 0; x <= 100; x+=20) {
        for(int y = -40; y <= 60; y+= 20) {
            BN_LOG("x", x, "y", y);
            bn::sprite_ptr dot = bn::sprite_items::dot.create_sprite(x, y);
            // bn::fixed scale = 1 + (x/100.0);
            // BN_LOG("scale: ", scale);
            // dot.set_scale(scale);
            dots.push_back(dot);
        }
        
    }

    while(1) {
        bn::core::update();
    }

    return 0;
}