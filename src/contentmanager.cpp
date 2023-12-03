#include "contentmanager.h"
#include "debugutils.h"

using namespace myengine;

ContentManager::ContentManager() {}
ContentManager::~ContentManager() {
    LOG("DEALLOCATING CONTENT MANAGER...");
}

void ContentManager::dealloc_all() {
    LOG("FREEING TEXTURES...");
    for (auto& texture : m_texture_data_store) {
        LOG("Deallocating texture");
        SDL_DestroyTexture(texture);
    }
    m_texture_data_store.clear();

    LOG("FREEING FONTS...");
    for (auto& font : m_font_data_store) {
        LOG("Deallocating font");
        TTF_CloseFont(font);
    }
    m_font_data_store.clear();

    LOG("FREEING MUSIC...");
    for (auto& music : m_music_data_store) {
        LOG("Deallocating music");
        Mix_FreeMusic(music);
    }
    m_music_data_store.clear();

    LOG("FREEING MUSIC CHUNK...");
    for (auto& chunk : m_music_chunk_data_store) {
        LOG("Deallocating music chunk");
        Mix_FreeChunk(chunk);
    }
    m_music_chunk_data_store.clear();
}

Texture ContentManager::load_texture_from_file(SDL_Renderer* renderer_ptr, const char* filename) {
    Texture texture;

    SDL_Surface* surf_ptr = IMG_Load(filename);

    if (!surf_ptr) {
        LOG("FAILED TO LOAD SURFACE FROM: " << filename)
        return texture;
    }

    SDL_Texture* texture_ptr = SDL_CreateTextureFromSurface(renderer_ptr, surf_ptr);

    SDL_FreeSurface(surf_ptr);

    if (!texture_ptr) {
        LOG("FAILED TO LOAD TEXTURE FROM: " << filename);
        return texture;
    }

    SDL_QueryTexture(
        texture_ptr,
        &texture.format,
        &texture.access,
        &texture.w,
        &texture.h
    );

    texture.data = texture_ptr;

    m_texture_data_store.push_back(texture.data);

    return texture;
}

Texture ContentManager::load_texture_from_surface(SDL_Renderer* renderer_ptr, SDL_Surface* surface_ptr) {
    Texture texture;

    SDL_Texture* texture_ptr = SDL_CreateTextureFromSurface(renderer_ptr, surface_ptr);

    SDL_FreeSurface(surface_ptr);

    if (!texture_ptr) {
        return texture;
    }

    SDL_QueryTexture(
        texture_ptr,
        &texture.format,
        &texture.access,
        &texture.w,
        &texture.h
    );

    texture.data = texture_ptr;

    m_texture_data_store.push_back(texture.data);

    return texture;
}

TTF_Font* ContentManager::load_font_from_file(const char* filename, int font_size) {
    TTF_Font* font_ptr = TTF_OpenFont(filename, font_size);

    if (!font_ptr) {
        LOG("FAILED TO LOAD FONT FROM FILE: " << filename);
        return nullptr;
    }

    m_font_data_store.push_back(font_ptr);

    return font_ptr;
}

Mix_Music* ContentManager::load_music_from_file(const char* filename) {
    Mix_Music* music_ptr = Mix_LoadMUS(filename);

    if (!music_ptr) {
        LOG("FAILED TO LOAD MUSIC FILE: " << filename);
        return nullptr;
    }

    m_music_data_store.push_back(music_ptr);

    return music_ptr;
}

Mix_Chunk* ContentManager::load_music_chunk_from_file(const char* filename) {
    Mix_Chunk* chunk_ptr = Mix_LoadWAV(filename);

    if (!chunk_ptr) {
        LOG("FAILED TO LOAD MUSIC CHUNK FILE: " << filename);
        return nullptr;
    }

    m_music_chunk_data_store.push_back(chunk_ptr);

    return chunk_ptr;
}