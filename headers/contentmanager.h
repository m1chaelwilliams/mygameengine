#ifndef CONTENTMANAGER_H
#define CONTENTMANAGER_H

// external dependencies
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

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
            Mix_Music* load_music_from_file(const char* filename);
            Mix_Chunk* load_music_chunk_from_file(const char* filename);

            void dealloc_all();

        private:
            std::vector<SDL_Texture*> m_texture_data_store;
            std::vector<TTF_Font*> m_font_data_store;
            std::vector<Mix_Music*> m_music_data_store;
            std::vector<Mix_Chunk*> m_music_chunk_data_store;
    };
};

#endif