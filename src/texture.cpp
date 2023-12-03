#include "texture.h"

using namespace myengine;

Texture::Texture() :
data(0),
w(0),
h(0),
format(0),
access(0)
{}

SDL_Rect Texture::get_rect(int x, int y) const {
    return SDL_Rect{x, y, w, h};
}