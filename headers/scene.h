#ifndef SCENE_H
#define SCENE_H

namespace myengine {
    class IScene {
        public:
            IScene() {}
            virtual ~IScene() {}

            virtual void on_load() = 0;
            virtual void on_unload() = 0;
            virtual void on_update() = 0;
            virtual void on_draw() = 0;
            virtual void on_scene_enter() = 0;
            virtual void on_scene_exit() = 0;
    };
};

#endif