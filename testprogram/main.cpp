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

        void on_load() override {}
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
        }
        void on_scene_enter() override {}
        void on_scene_exit() override {}
    private:
        SDL_Color m_scene_color;
        myengine::IApp* m_app_ptr;
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