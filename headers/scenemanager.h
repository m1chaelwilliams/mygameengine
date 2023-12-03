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
            void remove_scene(int scene_id);

            // modifying scene stack
            void push_scene(int scene_id); // adds scene to top of stack
            IScene* pop_scene(); // pops scene node from top of stack
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