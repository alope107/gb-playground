#include <bn_core.h>
#include <bn_sprite_ptr.h>
#include <bn_vector.h>

#include <bn_random.h>

#include <bn_sprite_items_dot.h>

#define HALF_SCREEN_WIDTH 120
#define HALF_SCREEN_HEIGHT 80 

#define MAX_COUNT 10
#define STARTING_COUNT 3

class Bouncer {
    public:
        Bouncer(bn::fixed x, bn::fixed y, bn::fixed dx, bn::fixed dy) :
            _sprite(bn::sprite_items::dot.create_sprite(x, y, 1)),
            _dx(dx),
            _dy(dy){
        };

        Bouncer(bn::random& rng) :
            _sprite(bn::sprite_items::dot.create_sprite(rng.get_fixed(-HALF_SCREEN_WIDTH, HALF_SCREEN_WIDTH), rng.get_fixed(-HALF_SCREEN_HEIGHT, HALF_SCREEN_HEIGHT), 1)),
            _dx(rng.get_fixed(-3, 3)),
            _dy(rng.get_fixed(-3, 3)){
        };

        void update() {
            _sprite.set_x(_sprite.x() + _dx);
            _sprite.set_y(_sprite.y() + _dy);

            if (_sprite.x() >= HALF_SCREEN_WIDTH || _sprite.x() <= -HALF_SCREEN_WIDTH) {
                _dx *= -1;
            }
            if (_sprite.y() >= HALF_SCREEN_HEIGHT || _sprite.y() <= -HALF_SCREEN_HEIGHT) {
                _dy *= -1;
            }
        }

    private:
        bn::sprite_ptr _sprite;
        bn::fixed _dx;
        bn::fixed _dy;
};


int main() {
    bn::core::init();

    bn::random rng = bn::random();

    bn::vector<Bouncer, MAX_COUNT> bouncers = {};
    bn::vector<bn::fixed, MAX_COUNT> dxs {};
    bn::vector<bn::fixed, MAX_COUNT> dys {};

    for (int i = 0; i < STARTING_COUNT; i++) {
        bouncers.push_back(Bouncer(rng));
    }

    int time = 0;

    while(true) {
        for(int i = 0; i < bouncers.size(); i++){
            bouncers[i].update();
        }

        time++;

        if(time == 100 && bouncers.size() < MAX_COUNT) {
            bouncers.push_back(Bouncer(rng));
            time = 0;
        }

        bn::core::update();
    }
}