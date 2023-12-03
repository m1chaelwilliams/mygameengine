#include "app.h"
#include "scenemanager.h"
#include "scene.h"
#include "debugutils.h"

enum class Scenes {
    START
};

class ColoredScene : public myengine::IScene {
    public:
        ColoredScene(myengine::IApp* app_ptr, SDL_Color clear_color) {
            m_app_ptr = app_ptr;
            m_scene_color = clear_color;
        }

        void on_load() override {
            test_texture = m_app_ptr->get_content_manager()->load_texture_from_file(m_app_ptr->get_renderer_ptr(), "assets/logo.png");
            m_font_ptr = m_app_ptr->get_content_manager()->load_font_from_file("assets/fira.ttf", 20);

            SDL_Surface* text_surf = TTF_RenderText_Solid(m_font_ptr, "Hello, World!", SDL_Color{255,255,255,255});
            text_texture = m_app_ptr->get_content_manager()->load_texture_from_surface(m_app_ptr->get_renderer_ptr(), text_surf);
        }
        void on_unload() override {}
        void on_update() override {}
        void on_draw() override {
            SDL_SetRenderDrawColor(
                m_app_ptr->get_renderer_ptr(),
                m_scene_color.r,
                m_scene_color.g,
                m_scene_color.b,
                m_scene_color.a
                );
            SDL_RenderClear(m_app_ptr->get_renderer_ptr());

            SDL_Rect drect = test_texture.get_rect(10, 10);
            SDL_RenderCopy(m_app_ptr->get_renderer_ptr(), test_texture.data, nullptr, &drect);
        
            SDL_Rect tdrect = text_texture.get_rect(100,100);
            SDL_RenderCopy(m_app_ptr->get_renderer_ptr(), text_texture.data, nullptr, &tdrect);
        }
        void on_scene_enter() override {}
        void on_scene_exit() override {}
    private:
        SDL_Color m_scene_color;
        myengine::IApp* m_app_ptr;
        myengine::Texture test_texture;
        myengine::Texture text_texture;
        TTF_Font* m_font_ptr;
        
};

class GameApp : public myengine::IApp {
    public:
        GameApp(
            myengine::GameWindowSettings gwsettings,
            myengine::RendererSettings rsettings
            ) :
            IApp(gwsettings,rsettings) {}
    protected:
        void on_load() override {
            m_scene_manager.add_scene(0, new ColoredScene(this, SDL_Color{255, 0, 0, 255}));
            m_scene_manager.add_scene(1, new ColoredScene(this, SDL_Color{0, 255, 0, 255}));
            m_scene_manager.add_scene(2, new ColoredScene(this, SDL_Color{0, 0, 255, 255}));
            m_scene_manager.add_scene(3, new ColoredScene(this, SDL_Color{255, 255, 0, 255}));
            m_scene_manager.add_scene(4, new ColoredScene(this, SDL_Color{0, 255, 255, 255}));
            m_scene_manager.push_scene(4);
            m_scene_manager.push_scene(3);
            m_scene_manager.push_scene(2);
            m_scene_manager.push_scene(1);
            m_scene_manager.push_scene(0);
        }
        void on_unload() override {}
        void on_update() override {
            m_event_handler.poll_events();
            if (m_event_handler.is_close_requested()) {
                close();
            }
            if (m_event_handler.is_key_pressed(SDLK_q)) {
                close();
            }
            if (m_event_handler.is_key_pressed(SDLK_SPACE)) {
                m_scene_manager.pop_scene();
            }

            m_active_scene->on_update();

            SDL_Delay(16);
        }
        void on_draw() override {

            m_active_scene->on_draw();

            SDL_RenderPresent(get_renderer_ptr());
        }
};

int main(int argc, char* argv[]) {
    myengine::GameWindowSettings gw;
    gw.title = "Game Engine Test App";
    gw.icon_filepath = "assets/logo.png";
    
    return GameApp(
        gw, 
        myengine::RendererSettings())
        .run();
}