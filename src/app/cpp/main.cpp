#include "allegro5/display.h"
#include "allegro5/drawing.h"
#include "allegro5/events.h"
#include "allegro5/system.h"
#include "allegro5/allegro_image.h"
#include "allegro5/timer.h"

#include "app/actor.h"
#include "app/animation_playback.h"
#include "app/random_controller.h"

#include <algorithm>
#include <chrono>
#include <vector>

using namespace std;

using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::seconds;

const float FPS = 60;

int main(int argc, char** argv) {
    al_init();
    al_init_image_addon();

    al_set_new_display_flags(ALLEGRO_FRAMELESS | ALLEGRO_FULLSCREEN_WINDOW);
	auto display = al_create_display(1280, 960);
    auto queue = al_create_event_queue();
    auto timer = al_create_timer(1.0 / FPS);
	
	al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    volatile bool running = true, redraw = true;
    auto previous = std::chrono::high_resolution_clock::now(), current = previous;

    vector<Actor> chickens = {
        {{512.f, 512.f}, {0.f, 0.f}, 0.f}, 
        {{1024.f, 512.f}, {0.f, 0.f}, 0.f}
    };
    for_each(chickens.begin(), chickens.end(), [i = static_cast<size_t>(0)](auto& c) mutable {
        AnimationPlayback::create(
            &c,
            "res/chicken_walk.png",
            0.5f,
            {{0.f, 0.f}, {32.f, 0.f}, {64.f, 0.f}, {96.f, 0.f}}
        );
        AnimationPlayback::create(
            &c,
            "res/chicken_walk.png",
            0.5f,
            {{0.f, 64.f}, {32.f, 64.f}, {64.f, 64.f}, {96.f, 64.f}}
        );
        AnimationPlayback::create(
            &c,
            "res/chicken_walk.png",
            0.5f,
            {{0.f, 96.f}, {32.f, 96.f}, {64.f, 96.f}, {96.f, 96.f}}
        );
        AnimationPlayback::create(
            &c,
            "res/chicken_walk.png",
            0.5f,
            {{0.f, 32.f}, {32.f, 32.f}, {64.f, 32.f}, {96.f, 32.f}}
        );

        c.animations = {i, i + 1, i + 2, i + 3};
        c.current_animation = no_animation;
        i += 4;

        RandomController::actors.insert(&c);
    });

    al_start_timer(timer);
	while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);
        switch(event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                running = false;
                break;
            case ALLEGRO_EVENT_TIMER:
                redraw = true;
                break;
        }

        if(redraw && al_is_event_queue_empty(queue)) {
            redraw = false;

            current = high_resolution_clock::now();
            auto dt= duration<float>(current - previous);
            previous = current;

            RandomController::tick(dt.count());
            AnimationPlayback::tick(dt.count());

            al_clear_to_color(al_map_rgb(0x63, 0x63, 0x63));
            AnimationPlayback::draw();

            al_flip_display();
        }
	}

    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}