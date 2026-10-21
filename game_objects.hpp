#ifndef __HPP_GAME_OBJECTS__
#define __HPP_GAME_OBJECTS__

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <algorithm>
#include <glm/vec4.hpp>
#include <memory>
#include <vector>

#include "utility_functions.hpp"
#include "components.hpp"

// Everything is a game object.  Game objects hold components
// that encapsulate behaviors.  PLEASE NOTICE THAT THIS CLASS
// USES TEMPLATES FOR GENERIC METHODS.  You will need to have the
// code in the header file so it can compile.
class GameObject {
public:
  // Components to be added are of different types, but still
  // are components.  This generic function allows for that.
  template <typename T, typename... Args> T *addComponent(Args &&...args) {
    static_assert(std::is_base_of<Component, T>::value,
                  "T must derive from Component");

    // Making the component a unique pointer makes sure that it is
    // only owned by one GameObject, and that we can't accidentally
    // mess that up.  It also makes sure the object is deleted if
    // it goes out of scope.
    auto component = std::make_unique<T>(std::forward<Args>(args)...);
    component->setOwner(this);

    T *ptr = component.get();
    components.push_back(std::move(component));
    return ptr;
  }

  // Since the getter returns a variety of types (all derived from Component),
  // we need another generic method.
  template <typename T> T *getComponent() {
    for (auto &c : components) {
      if (auto casted = dynamic_cast<T *>(c.get()))
        return casted;
    }
    return nullptr;
  }

  // Virtual so deleting through unique_ptr<GameObject> destroys the derived class.
  virtual ~GameObject() = default;
  virtual void update(float deltaTime);

private:
  std::vector<std::unique_ptr<Component>> components;
};

// A Scene owns its game objects. You may also want to keep other
// information in a scene, like background color, etc.
class Scene {
public:
  void addObject(std::unique_ptr<GameObject> go) { game_objects.push_back(std::move(go)); }
  // Removal only queues the object; it is destroyed at the end of updateScene,
  // so pointers to it stay valid for the rest of the frame.
  void markRemoval(GameObject *go) { remove_queue.push_back(go); }
  // Objects created during an update are queued so we don't modify the
  // vector while iterating over it.
  void markAdd(std::unique_ptr<GameObject> go) { add_queue.push_back(std::move(go)); }

  // Updates all objects, then applies queued additions and removals.
  void updateScene(float deltaTime) {
    for (auto &o : game_objects) {
      o->update(deltaTime);
    }

    // Add game objects that were created during object updates
    for (auto &o : add_queue) {
      game_objects.push_back(std::move(o));
    }
    add_queue.clear();

    // Remove (and destroy) game objects that were marked for removal during object updates
    for (GameObject *go : remove_queue) {
      game_objects.erase(
          std::remove_if(game_objects.begin(), game_objects.end(),
                         [go](const std::unique_ptr<GameObject> &p) { return p.get() == go; }),
          game_objects.end());
    }
    remove_queue.clear();
  }

  // Destroys every object in the scene.
  void clear() {
    game_objects.clear();
    add_queue.clear();
    remove_queue.clear();
  }

  // returns object that given rectangle collides with, if any
  GameObject* collision(SDL_FRect* rect, GameObject* ignore) {
    for (const auto &o : game_objects) {
      if (o.get() == ignore) continue;
      auto *sprite = o->getComponent<SpriteComponent>();
      // Objects without a sprite have no rect to collide with
      if (sprite && UtilityFunctions::AABB_Collision(*rect, *(sprite->getRect()))) {
        return o.get();
      }
    }
    return nullptr;
  }

private:
  std::vector<std::unique_ptr<GameObject>> game_objects;
  std::vector<GameObject *> remove_queue;
  std::vector<std::unique_ptr<GameObject>> add_queue;
};

#endif
