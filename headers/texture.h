#ifndef MYENGINE_TEXTURE_H
#define MYENGINE_TEXTURE_H

#include <SDL2/SDL.h>

namespace myengine {

    class Texture {
        public:
            SDL_Texture* data;
            int w;
            int h;
            Uint32 format;
            int access;

            Texture();
            SDL_Rect get_rect(int x = 0, int y = 0) const;
    };
    
};

#endif