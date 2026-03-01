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

  virtual void update(float deltaTime);

private:
  std::vector<std::unique_ptr<Component>> components;
};

// A Scene is a simple collection for game objects. You may also
// want to keep other information in a scene, like background color, etc.
class Scene {
public:
  void addObject(GameObject *go) { game_objects.push_back(go); }
  void markRemoval(GameObject *go) { remove_queue.push_back(go); }
  void markAdd(GameObject *go) { add_queue.push_back(go); }
  // BUG MIGHT BE that when player gets updated, if you shoot it adds projectile object to scene, in effect fucking with the
  // vector while iterating over it. So maybe try fixing with a markAdd() similar to markRemoval()? idk i'm way too tired
  void updateScene(float deltaTime) {
    for (auto it = game_objects.begin(); it != game_objects.end(); ++it) {
      (*it)->update(deltaTime);
    }

    // Add game objects that were created during object updates
    for (auto it = add_queue.begin(); it != add_queue.end(); ++it) {
      addObject(*it);
    }
    add_queue.clear();

    // Remove game objects that were marked for removal during object updates
    for (auto it = remove_queue.begin(); it != remove_queue.end(); ++it) {
      game_objects.erase(std::remove(game_objects.begin(), game_objects.end(), *it), game_objects.end());
    }
    remove_queue.clear();
  }
  
  // returns object that given rectangle collides with, if any
  GameObject* collision(GameObject* obj) {
    SDL_FRect rect = *(obj->getComponent<SpriteComponent>()->getRect());
    for (const auto &o : game_objects) {
      if (obj != o && UtilityFunctions::AABB_Collision(rect, *(o->getComponent<SpriteComponent>()->getRect()))) {
        return o;
      }
    }
    return nullptr;
  }

private:
  std::vector<GameObject *> game_objects;
  std::vector<GameObject *> remove_queue;
  std::vector<GameObject *> add_queue;
};

#endif
