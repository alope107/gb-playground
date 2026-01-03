#include <bn_core.h>
#include <bn_sprite_ptr.h>
#include <bn_vector.h>

#include <bn_sprite_items_dot.h>

#define HALF_SCREEN_WIDTH 120
#define HALF_SCREEN_HEIGHT 80 

#define BOUNCER_COUNT 3

int main() {
    bn::core::init();

    bn::array<bn::sprite_ptr, BOUNCER_COUNT> bouncers = {
        bn::sprite_items::dot.create_sprite(0, 0, 1),
        bn::sprite_items::dot.create_sprite(0, 0, 1),
        bn::sprite_items::dot.create_sprite(0, 0, 1)
    };

    bn::array<bn::fixed, BOUNCER_COUNT> dxs = {
       1,
       1.5,
       -1
    };

    bn::array<bn::fixed, BOUNCER_COUNT> dys = {
        2,
        -1.1,
        1
    };

    while(true) {
        for(int i = 0; i < BOUNCER_COUNT; i++){
            bouncers[i].set_x(bouncers[i].x() + dxs[i]);
            bouncers[i].set_y(bouncers[i].y() + dys[i]);

            if(bouncers[i].x() >= HALF_SCREEN_WIDTH || bouncers[i].x() <= -HALF_SCREEN_WIDTH) {
                dxs[i] *= -1;
            }

            if(bouncers[i].y() >= HALF_SCREEN_HEIGHT || bouncers[i].y() <= -HALF_SCREEN_HEIGHT) {
                dys[i] *= -1;
            }
        }
        // bouncer.set_x(bouncer.x() + dx);
        // bouncer.set_y(bouncer.y() + dy);

        // bouncer2.set_x(bouncer2.x() + dx2);
        // bouncer2.set_y(bouncer2.y() + dy2);

        // if (bouncer.x() >= HALF_SCREEN_WIDTH || bouncer.x() <= -HALF_SCREEN_WIDTH) {
        //     dx *= -1;
        // }

        // if (bouncer.y() >= HALF_SCREEN_HEIGHT || bouncer.y() <= -HALF_SCREEN_HEIGHT) {
        //     dy *= -1;
        // }


        // if (bouncer2.x() >= HALF_SCREEN_WIDTH || bouncer2.x() <= -HALF_SCREEN_WIDTH) {
        //     dx2 *= -1;
        // }

        // if (bouncer2.y() >= HALF_SCREEN_HEIGHT || bouncer2.y() <= -HALF_SCREEN_HEIGHT) {
        //     dy2 *= -1;
        // }

        bn::core::update();
    }
}