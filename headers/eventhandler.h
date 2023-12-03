// in need of optimization ... ( wip )

#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <SDL2/SDL.h>
#include <vector>
#include <algorithm>

namespace myengine {
    class EventHandler {
        public:
            EventHandler();
            ~EventHandler();
            void poll_events();
            bool is_key_down(SDL_Keycode key) const;
            bool is_key_pressed(SDL_Keycode key) const;
            bool is_mouse_clicked(Uint8 button) const;
            bool is_mouse_down(Uint8 button) const;
            bool is_scroll_wheel(int direction) const;
            bool is_close_requested() const;
            std::vector<SDL_Event>& get_events();
        private:
            std::vector<SDL_Keycode> keys_pressed;
            std::vector<SDL_Keycode> keys_held;
            std::vector<Uint8> mouse_pressed;
            std::vector<Uint8> mouse_held;
            std::vector<SDL_Event> events;
            int mouse_wheel;
    };

}

#endif