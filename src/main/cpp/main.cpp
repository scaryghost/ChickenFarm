#include "allegro5/allegro5.h"
#include "allegro5/allegro_image.h"

#include <iostream>
#include <chrono>

using std::cout;
using std::endl;
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
    float x = 0, y = 0;
    auto previous = std::chrono::high_resolution_clock::now(), current = previous;

    auto image = al_load_bitmap("res/chicken_walk.png");

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

        al_draw_scaled_bitmap(image, 0, 96, 32, 32, x, y, 256, 256, 0);

		al_flip_display();
	}
    return 0;
}