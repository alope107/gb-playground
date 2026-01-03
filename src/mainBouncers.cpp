#include <bn_core.h>
#include <bn_sprite_ptr.h>
#include <bn_vector.h>

#include <bn_random.h>

#include <bn_sprite_items_dot.h>

#define HALF_SCREEN_WIDTH 120
#define HALF_SCREEN_HEIGHT 80 

#define MAX_COUNT 5
#define STARTING_COUNT 3


int main() {
    bn::core::init();

    bn::random rng = bn::random();

    bn::vector<bn::sprite_ptr, MAX_COUNT> bouncers = {};
    bn::vector<bn::fixed, MAX_COUNT> dxs {};
    bn::vector<bn::fixed, MAX_COUNT> dys {};

    for (int i = 0; i < STARTING_COUNT; i++) {
        bn::fixed x = rng.get_fixed(-HALF_SCREEN_WIDTH, HALF_SCREEN_WIDTH);
        bn::fixed y = rng.get_fixed(-HALF_SCREEN_HEIGHT, HALF_SCREEN_HEIGHT);
        bouncers.push_back(bn::sprite_items::dot.create_sprite(x, y, 1));

        bn::fixed dx = rng.get_fixed(-3, 3);
        bn::fixed dy = rng.get_fixed(-3, 3);

        dxs.push_back(dx);
        dys.push_back(dy);
    }

    int time = 0;

    while(true) {
        for(int i = 0; i < bouncers.size(); i++){
            bouncers[i].set_x(bouncers[i].x() + dxs[i]);
            bouncers[i].set_y(bouncers[i].y() + dys[i]);

            if(bouncers[i].x() >= HALF_SCREEN_WIDTH || bouncers[i].x() <= -HALF_SCREEN_WIDTH) {
                dxs[i] *= -1;
            }

            if(bouncers[i].y() >= HALF_SCREEN_HEIGHT || bouncers[i].y() <= -HALF_SCREEN_HEIGHT) {
                dys[i] *= -1;
            }
        }

        time++;

        if(time == 100) {
            bn::fixed x = rng.get_fixed(-HALF_SCREEN_WIDTH, HALF_SCREEN_WIDTH);
            bn::fixed y = rng.get_fixed(-HALF_SCREEN_HEIGHT, HALF_SCREEN_HEIGHT);
            bouncers.push_back(bn::sprite_items::dot.create_sprite(x, y, 1));

            bn::fixed dx = rng.get_fixed(-3, 3);
            bn::fixed dy = rng.get_fixed(-3, 3);

            dxs.push_back(dx);
            dys.push_back(dy);

            time = 0;
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