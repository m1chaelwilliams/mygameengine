#ifndef CONTENTMANAGER_H
#define CONTENTMANAGER_H

// external dependencies
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <vector>
#include <string>

// internal dependencies
#include "texture.h"

namespace myengine {
    class ContentManager {
        public:
            ContentManager();
            ~ContentManager();

            Texture load_texture_from_file(SDL_Renderer* renderer_ptr, const char* filename);
            Texture load_texture_from_surface(SDL_Renderer* renderer_ptr, SDL_Surface* surface_ptr);
            TTF_Font* load_font_from_file(const char* filename, int font_size);

        private:
            std::vector<SDL_Texture*> m_texture_data_store;
            std::vector<TTF_Font*> m_font_data_store;
    };
};

#endif