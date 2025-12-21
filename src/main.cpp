#include <bn_core.h>
#include <bn_sprite_ptr.h>

#include "bn_sprite_items_dot.h"

int main() {
    bn::core::init();

    bn::sprite_ptr dot = bn::sprite_items::dot.create_sprite(0, 0);

    while(1) {
        bn::core::update();
    }

    return 0;
}