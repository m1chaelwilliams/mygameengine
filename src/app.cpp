#include "app.h"
#include "debugutils.h"

using namespace myengine;

IApp::IApp(
    GameWindowSettings gwsettings,
    RendererSettings rsettings
) :
gwsettings(gwsettings),
rsettings(rsettings),
m_window_ptr(nullptr),
m_renderer_ptr(nullptr),
m_active_scene(nullptr)
{

}

IApp::~IApp() {
    if (icon) {
        SDL_FreeSurface(icon);
    }

    SDL_DestroyRenderer(m_renderer_ptr);
    SDL_DestroyWindow(m_window_ptr);
    SDL_Quit();
}

bool IApp::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return false;
    }
    return true;
}
bool IApp::create_display() {
    m_window_ptr = SDL_CreateWindow(
        gwsettings.title,
        gwsettings.x,
        gwsettings.y,
        gwsettings.width,
        gwsettings.height,
        gwsettings.flags
    );

    if (!m_window_ptr) {
        return false;
    }
    return true;
}

bool IApp::create_renderer() {
    m_renderer_ptr = SDL_CreateRenderer(
        m_window_ptr,
        rsettings.index,
        rsettings.flags
    );

    if (!m_renderer_ptr) {
        return false;
    }
    return true;
}

int IApp::run() {
    // initialization
    if (!(init() && create_display() && create_renderer())) {
        return -1;
    }

    // loading icons
    if (load_icon()) {
        SDL_SetWindowIcon(m_window_ptr, icon);
    }

    on_load();
    // game loop
    while (!m_scene_manager.scene_stack_is_empty()) {
        m_active_scene = m_scene_manager.get_active_scene();

        if (m_active_scene) {
            on_update();
            on_draw();
        }
    }
    // unload
    on_unload();

    // destructor is called after leaving this scope
    return 0;
}

bool IApp::is_running() const {
    return !m_scene_manager.scene_stack_is_empty();
}

void IApp::close() {
    m_scene_manager.clear_stack();   
}

bool IApp::load_icon() {
    if (gwsettings.icon_filepath) {
        icon = IMG_Load(gwsettings.icon_filepath);

        if (!icon) {
            return false;
        }
        return true;
    }
    return false;
}

// getters

SDL_Point IApp::get_size() const {
    int w, h;
    SDL_GetWindowSize(m_window_ptr, &w, &h);
    return SDL_Point{w,h};
}

SDL_Window* IApp::get_window_ptr() const {
    return m_window_ptr;
}

SDL_Renderer* IApp::get_renderer_ptr() const {
    return m_renderer_ptr;
}