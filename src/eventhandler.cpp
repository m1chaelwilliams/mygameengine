#include "eventhandler.h"

#include "debugutils.h"

using namespace myengine;

EventHandler::EventHandler() {
    mouse_wheel = 0;
}
EventHandler::~EventHandler() {
    LOG("Destructing EventHandler...");
}

void EventHandler::poll_events() {
    events.clear();
    keys_pressed.clear();
    mouse_pressed.clear();
    mouse_wheel = 0;

    std::vector<SDL_Keycode> keys_to_remove;
    std::vector<Uint8> mouse_buttons_to_remove;

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        events.push_back(e);

        if (e.type == SDL_KEYDOWN && !is_key_down(e.key.keysym.sym)) {
            keys_pressed.push_back(e.key.keysym.sym);
            keys_held.push_back(e.key.keysym.sym);
        }

        if (e.type == SDL_KEYUP && is_key_down(e.key.keysym.sym)) {
            keys_to_remove.push_back(e.key.keysym.sym);
        }

        if (e.type == SDL_MOUSEBUTTONDOWN && !is_mouse_clicked(e.button.button)) {
            mouse_pressed.push_back(e.button.button);
            mouse_held.push_back(e.button.button);
        }

        if (e.type == SDL_MOUSEBUTTONUP && is_mouse_down(e.button.button)) {
            mouse_buttons_to_remove.push_back(e.button.button);
        }

        if (e.type == SDL_MOUSEWHEEL) {
            if (e.wheel.y > 0) {
                mouse_wheel = 1;
            }
            if (e.wheel.y < 0) {
                mouse_wheel = -1;
            }
        }
    }

    for (const auto& key : keys_to_remove) {
        keys_held.erase(std::remove(keys_held.begin(), keys_held.end(), key), keys_held.end());
    }

    for (const auto& mouse_button : mouse_buttons_to_remove) {
        mouse_held.erase(std::remove(mouse_held.begin(), mouse_held.end(), mouse_button), mouse_held.end());
    }
}

bool EventHandler::is_key_down(SDL_Keycode key) const {
    for (auto& key_iter : keys_held) {
        if (key_iter == key) {
            return true;
        }
    }
    return false;
}

bool EventHandler::is_key_pressed(SDL_Keycode key) const {
    for (auto& key_iter : keys_pressed) {
        if (key_iter == key) {
            return true;
        }
    }
    return false;
}

bool EventHandler::is_close_requested() const {
    for (auto& event : events) {
        if (event.type == SDL_QUIT)
            return true;
    }
    return false;
}

bool EventHandler::is_mouse_clicked(Uint8 button) const {
    for (const auto& mouse_iter : mouse_pressed) {
        if (mouse_iter == button) {
            return true;
        }
    }
    return false;
}

bool EventHandler::is_mouse_down(Uint8 button) const {
    for (const auto& mouse_iter : mouse_held) {
        if (mouse_iter == button) {
            return true;
        }
    }
    return false;
}

bool EventHandler::is_scroll_wheel(int direction) const {
    return direction == mouse_wheel;
}

std::vector<SDL_Event>& EventHandler::get_events() {
    return events;
}