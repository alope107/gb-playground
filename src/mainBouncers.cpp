#include <bn_core.h>
#include <bn_sprite_ptr.h>

#include <bn_sprite_items_dot.h>

int main() {
    bn::core::init();

    bn::sprite_ptr bouncer = bn::sprite_items::dot.create_sprite(0, 0, 1);

    while(true) {
        bn::fixed current_x = bouncer.x();
        bouncer.set_x(current_x + 1);
        bn::core::update();
    }
}