#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <map>

namespace myengine {
    // forward declare `IScene`
    class IScene;

    struct SceneNode {
        int scene_id;
        IScene* scene_ptr;
        SceneNode* next;
    };

    inline SceneNode* create_scene_node(int scene_id, IScene* scene_ptr) {
        return new SceneNode{scene_id, scene_ptr, nullptr};
    }

    class SceneManager {
        public:
            SceneManager();
            ~SceneManager();

            // modifying scene store
            void add_scene(int scene_id, IScene* scene_ptr);
            bool has_scene(int scene_id);
            void remove_scene(
                int scene_id, 
                int num_args, 
                const char* args[]);

            // modifying scene stack
            void push_scene_raw(int scene_id); // pushes scene without calling any scene methods, used for building a scene stack
            void swap_active_scene(
                int scene_id, 
                int num_exit_args = 0,
                const char* exit_args[] = nullptr,
                int num_enter_args = 0,
                const char* enter_args[] = nullptr);
            void push_scene(
                int scene_id, 
                int num_args = 0, 
                const char* args[] = nullptr); // adds scene to top of stack
            IScene* pop_scene(
                int num_exit_args = 0, 
                const char* exit_args[] = nullptr, 
                int num_args = 0, 
                const char* args[] = nullptr); // pops scene node from top of stack
            IScene* get_active_scene() const; // returns scene at top of stack
            bool scene_stack_is_empty() const;
            void clear_stack();

            IScene* get_scene_by_id(int scene_id);
        private:
            // stores all scenes in application.
            std::map<int, IScene*> m_scene_store;
            // head of the scene stack (aka the active scene)
            SceneNode* m_scene_head;
    };
};

#endif