#include "allegro5/display.h"
#include "allegro5/drawing.h"
#include "allegro5/events.h"
#include "allegro5/system.h"
#include "allegro5/allegro_image.h"

#include "app/animation_playback.h"

#include <chrono>

using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::seconds;

int main(int argc, char** argv) {
    al_init();
    al_init_image_addon();

    al_set_new_display_flags(ALLEGRO_FRAMELESS | ALLEGRO_FULLSCREEN_WINDOW);
	auto display = al_create_display(1280, 960);
    auto queue = al_create_event_queue();
	
	al_register_event_source(queue, al_get_display_event_source(display));

    volatile bool running = true;
    auto previous = std::chrono::high_resolution_clock::now(), current = previous;
    Animation& walk_right = AnimationPlayback::create(
        "res/chicken_walk.png",
        1.f,
        {{0.f, 96.f}, {32.f, 96.f}, {64.f, 96.f}, {96.f, 96.f}}
    ), walk_left = AnimationPlayback::create(
        "res/chicken_walk.png",
        2.f,
        {{0.f, 32.f}, {32.f, 32.f}, {64.f, 32.f}, {96.f, 32.f}}
    );

	while (running) {
        ALLEGRO_EVENT event;
		if (!al_is_event_queue_empty(queue)) {
			al_wait_for_event(queue, &event);
            switch(event.type) {
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                    running = false;
                    break;
            }
        }

        al_clear_to_color(al_map_rgb(0x63, 0x63, 0x63));

        current = high_resolution_clock::now();
        auto dt= duration<float>(current - previous);
        previous = current;

        AnimationPlayback::tick(dt.count());
        AnimationPlayback::draw();

		al_flip_display();
	}

    al_destroy_display(display);
    al_destroy_event_queue(queue);

    return 0;
}