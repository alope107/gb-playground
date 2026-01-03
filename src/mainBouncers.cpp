#include <bn_core.h>
#include <bn_sprite_ptr.h>
#include <bn_vector.h>
#include <bn_keypad.h>
#include <bn_random.h>
#include <bn_rect.h>

#include <bn_sprite_items_dot.h>
#include <bn_log.h>

#define HALF_SCREEN_WIDTH 120
#define HALF_SCREEN_HEIGHT 80 

#define MAX_COUNT 10
#define STARTING_COUNT 3

#define MAX_ABS_D_COMPONENT 3
#define BOUNCER_CREATE_DELAY 100

#define INITIAL_SPEED 2

class Bouncer {
    public:
        Bouncer(bn::fixed x, bn::fixed y, bn::fixed dx, bn::fixed dy) :
            _sprite(bn::sprite_items::dot.create_sprite(x, y, 2)),
            _dx(dx),
            _dy(dy){
        };

        Bouncer(bn::random& rng) :
            _sprite(bn::sprite_items::dot.create_sprite(rng.get_fixed(-HALF_SCREEN_WIDTH, HALF_SCREEN_WIDTH),
                                                        rng.get_fixed(-HALF_SCREEN_HEIGHT, HALF_SCREEN_HEIGHT),
                                                        1)),
            _dx(rng.get_fixed(-MAX_ABS_D_COMPONENT, MAX_ABS_D_COMPONENT)),
            _dy(rng.get_fixed(-MAX_ABS_D_COMPONENT, MAX_ABS_D_COMPONENT)){
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

        bn::rect bounding_box() {
            return bn::rect(_sprite.x().round_integer(), _sprite.y().round_integer(), size, size);
        }

    private:
        static constexpr int size = 8;
        bn::sprite_ptr _sprite;
        bn::fixed _dx;
        bn::fixed _dy;
};

class Player {
    public:
        Player() :
            _sprite(bn::sprite_items::dot.create_sprite(0, 0, 0)),
            speed(INITIAL_SPEED)
        {};

        void update() {
            if(bn::keypad::left_held()) {
                _sprite.set_x(_sprite.x() - speed);
            }
            if(bn::keypad::right_held()) {
                _sprite.set_x(_sprite.x() + speed);
            }
            if(bn::keypad::down_held()) {
                _sprite.set_y(_sprite.y() + speed);
            }
            if(bn::keypad::up_held()) {
                _sprite.set_y(_sprite.y() - speed);
            }
        }

        bool collides(Bouncer bouncer) {
            return bouncer.bounding_box().intersects(bounding_box());
        }

        bn::rect bounding_box() {
            return bn::rect(_sprite.x().round_integer(), _sprite.y().round_integer(), size, size);
        }
    private:
        static constexpr int size = 8;
        bn::sprite_ptr _sprite;
        bn::fixed speed;
};


int main() {
    bn::core::init();

    bn::random rng = bn::random();

    bn::vector<Bouncer, MAX_COUNT> bouncers = {};
    bn::vector<bn::fixed, MAX_COUNT> dxs {};
    bn::vector<bn::fixed, MAX_COUNT> dys {};

    Player player = Player();

    for (int i = 0; i < STARTING_COUNT; i++) {
        bouncers.push_back(Bouncer(rng));
    }

    int time = 0;

    while(true) {
        player.update();
        for(Bouncer& bouncer : bouncers){
            bouncer.update();

            if(player.collides(bouncer)) {
                BN_LOG("DIRECT HIT");
            }
        }
        

        time++;

        if(time == BOUNCER_CREATE_DELAY && bouncers.size() < MAX_COUNT) {
            bouncers.push_back(Bouncer(rng));
            time = 0;
        }

        bn::core::update();
    }
}