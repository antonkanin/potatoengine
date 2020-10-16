#pragma once

#include "mesh.hpp"
#include "model.hpp"
#include "ptm/vec3.hpp"
#include "transformation.hpp"
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <engine.hpp>
#include <memory>

namespace pt
{

class component;

class game_object
{
public:
    explicit game_object(std::string name);

    virtual ~game_object();

    /** called once for each game object before the main loop */
    virtual void start(){};

    /** called every frame */
    virtual void update(){};

    /** add custom GUI */
    virtual void on_gui(){};

    [[nodiscard]] virtual bool is_serializable() const { return false; }

    void set_transform(const transformation& transform);

    [[nodiscard]] const transformation& get_transformation() const;

    game_object*            set_position(const ptm::vec3& position);
    [[nodiscard]] ptm::vec3 get_position() const;

    game_object*            set_scale(const ptm::vec3& scale);
    [[nodiscard]] ptm::vec3 get_scale() const;

    game_object* set_rotation(const ptm::vec3& rotation_vector, float angle);

    [[nodiscard]] const model& get_model() const;
    void                       set_model(std::unique_ptr<model>&);

    game_object* load_model(const std::string& path);

    game_object* add_body(bool is_dynamic);

    // physics
    btRigidBody*   body_         = nullptr;
    btMotionState* motion_state_ = nullptr;

    [[nodiscard]] std::string get_name() const;

    void self_destroy();

    engine& get_engine();

    void add_component(std::unique_ptr<component> component);

private:
    void set_position_forced(const ptm::vec3& position);
    void set_rotation_forced(const ptm::vec3& rotation_vector, float angle);

    void set_name(const std::string& name);

    void destroy_forced();

    friend engine;
    friend engine_impl;

    friend game_objects_list;

    engine* engine_ = nullptr;

    bool has_model_ = false;

    std::unique_ptr<model> model_;

    transformation transformation_ = { .position        = ptm::vec3::zero(),
                                       .rotation_vector = ptm::vec3::up(),
                                       .rotation_angle  = 0.0f,
                                       .scale           = { 1.f, 1.f, 1.f } };

    std::string name_ = "NoName";

    bool to_be_destroyed_ = false;

    std::vector<std::unique_ptr<component>> components_;
};

template <typename T>
game_object* make_object(engine& e, std::string_view object_name)
{
    return e.add_object<T>(object_name);
}

} // namespace pt