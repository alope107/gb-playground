#include <bn_core.h>
#include <bn_sprite_ptr.h>
// #include <bn_vector.h>

#include <bn_sprite_items_dot.h>

#define HALF_SCREEN_WIDTH 120
#define HALF_SCREEN_HEIGHT 80 

#define BOUNCER_COUNT 5

int main() {
    bn::core::init();

    // bn::vector<bn::sprite_ptr> bouncers

    bn::sprite_ptr bouncer = bn::sprite_items::dot.create_sprite(0, 0, 1);
    bn::sprite_ptr bouncer2 = bn::sprite_items::dot.create_sprite(40, 50, 1);

    bn::fixed dx = 1;
    bn::fixed dy = 1;

    bn::fixed dx2 = -1;
    bn::fixed dy2 = 1;

    while(true) {
        bouncer.set_x(bouncer.x() + dx);
        bouncer.set_y(bouncer.y() + dy);

        bouncer2.set_x(bouncer2.x() + dx2);
        bouncer2.set_y(bouncer2.y() + dy2);

        if (bouncer.x() >= HALF_SCREEN_WIDTH || bouncer.x() <= -HALF_SCREEN_WIDTH) {
            dx *= -1;
        }

        if (bouncer.y() >= HALF_SCREEN_HEIGHT || bouncer.y() <= -HALF_SCREEN_HEIGHT) {
            dy *= -1;
        }


        if (bouncer2.x() >= HALF_SCREEN_WIDTH || bouncer2.x() <= -HALF_SCREEN_WIDTH) {
            dx2 *= -1;
        }

        if (bouncer2.y() >= HALF_SCREEN_HEIGHT || bouncer2.y() <= -HALF_SCREEN_HEIGHT) {
            dy2 *= -1;
        }

        bn::core::update();
    }
}