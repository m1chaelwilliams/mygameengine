#include "scenemanager.h"
#include "scene.h"
#include "debugutils.h"

using namespace myengine;

SceneManager::SceneManager() :
    m_scene_head(nullptr)
{}

SceneManager::~SceneManager() {
    LOG("DEALLOCATING SCENE MANAGER...");
    for (auto& scene : m_scene_store) {
        LOG("DELETING SCENE: " << scene.first);
        scene.second->on_unload();
        delete scene.second;
    }
    m_scene_store.clear();

    while (m_scene_head) {
        SceneNode* target = m_scene_head;
        m_scene_head = m_scene_head->next;
        delete target;
    }
    m_scene_head = nullptr;
}

void SceneManager::add_scene(int scene_id, IScene* scene_ptr) {
    auto* scene = get_scene_by_id(scene_id);
    if (scene) {
        delete scene;
    }

    m_scene_store[scene_id] = scene_ptr;

    scene_ptr->on_load();
}

void SceneManager::remove_scene(int scene_id) {
    auto* scene = get_scene_by_id(scene_id);
    if (scene) {

        if (m_scene_head->scene_ptr == scene) {
            scene->on_scene_exit();
        }
        scene->on_unload();

        delete scene;
        m_scene_store.erase(scene_id);
    }
}

IScene* SceneManager::get_scene_by_id(int scene_id) {
    auto it = m_scene_store.find(scene_id);
    return (it != m_scene_store.end()) ? it->second : nullptr;
}

IScene* SceneManager::get_active_scene() const {
    return m_scene_head->scene_ptr;
}

bool SceneManager::has_scene(int scene_id) {
    return get_scene_by_id(scene_id);
}

void SceneManager::push_scene(int scene_id) {
    auto* scene = get_scene_by_id(scene_id);

    if (!scene) {
        return;
    }

    scene->on_scene_enter();

    SceneNode* newNode = create_scene_node(scene_id, scene);
    newNode->next = m_scene_head;
    m_scene_head = newNode;

    LOG("Added new scene: " << scene_id);
}

IScene* SceneManager::pop_scene() {
    if (scene_stack_is_empty()) {
        return nullptr;
    }

    m_scene_head->scene_ptr->on_scene_exit();

    SceneNode* target_node = m_scene_head;
    m_scene_head = m_scene_head->next;

    LOG("Removed scene: " << target_node->scene_id);

    IScene* target_scene = target_node->scene_ptr;
    delete target_node;

    return target_scene;
}

bool SceneManager::scene_stack_is_empty() const {
    return m_scene_head == nullptr;
}

void SceneManager::clear_stack() {
    while (m_scene_head) {
        SceneNode* target = m_scene_head;
        m_scene_head = m_scene_head->next;
        delete target;
    }
    m_scene_head = nullptr;
}