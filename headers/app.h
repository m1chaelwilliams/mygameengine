#ifndef APP_H
#define APP_H

// external dependencies
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// internal dependencies
#include "scenemanager.h"
#include "eventhandler.h"
#include "contentmanager.h"

namespace myengine {
    struct GameWindowSettings {
        int width;
        int height;
        const char* title;
        int x;
        int y;
        Uint32 flags;
        const char* icon_filepath;

        GameWindowSettings(
            int width = 600,
            int height = 400,
            const char* title = "MyEngine Application",
            int x = SDL_WINDOWPOS_CENTERED,
            int y = SDL_WINDOWPOS_CENTERED,
            Uint32 flags = SDL_WINDOW_SHOWN,
            const char* icon_filepath = ""
        ) :
        width(width),
        height(height),
        title(title),
        x(x),
        y(y),
        flags(flags),
        icon_filepath(icon_filepath)
        {}
    };

    struct RendererSettings {
        int index;
        Uint32 flags;

        RendererSettings(
            int index = -1,
            Uint32 flags = 0
        ) :
        index(index),
        flags(flags)
        {}
    };

    class IApp {
        public:
            IApp(
                GameWindowSettings gwsettings,
                RendererSettings rsettings
            );
            ~IApp();

            bool init();
            bool create_display();
            bool create_renderer();
            int run();

            // utils
            bool load_icon();

            // getters
            SDL_Point get_size() const;
            SDL_Window* get_window_ptr() const;
            SDL_Renderer* get_renderer_ptr() const;
            ContentManager* get_content_manager();
            SceneManager* get_scene_manager();

        protected:
            virtual void on_update() = 0;
            virtual void on_draw() = 0;
            virtual void on_load() = 0;
            virtual void on_unload() = 0;

            bool is_running() const;
            void close();

            // managers (could be moved in the future)
            SceneManager m_scene_manager;
            EventHandler m_event_handler;
            ContentManager m_content_manager;

            IScene* m_active_scene;
        
        private:
            SDL_Window* m_window_ptr;
            SDL_Renderer* m_renderer_ptr;

            GameWindowSettings gwsettings;
            RendererSettings rsettings;

            SDL_Surface* icon;
    };
};

#endif