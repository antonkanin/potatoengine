#pragma once

#include "../video_component.hpp"
#include "model.hpp"
#include <LinearMath/btIDebugDraw.h>

namespace pt
{

class debug_drawer : public btIDebugDraw
{
public:
    explicit debug_drawer(video_component* video_component)
        : video_component_(video_component)
    {
        vertex v;

        mesh m = { .vertices = { v, v, v },
                   .indices  = { 1, 2, 3 },
                   .textures = {} };

        model_ = std::make_shared<model>();
        model_->add_mesh(m);
    }

    void drawLine(const btVector3& from, const btVector3& to,
                  const btVector3& color) override
    {
        model_->get_meshes()[0].vertices[0].position = { from.x(), from.y(),
                                                         from.z() };
        model_->get_meshes()[0].vertices[0].color    = { color.x(), color.y(),
                                                      color.z() };

        model_->get_meshes()[0].vertices[1].position = { from.x(), from.y(),
                                                         from.z() };
        model_->get_meshes()[0].vertices[1].color    = { color.x(), color.y(),
                                                      color.z() };

        model_->get_meshes()[0].vertices[2].position = { to.x(), to.y(),
                                                         to.z() };
        model_->get_meshes()[0].vertices[2].color    = { color.x(), color.y(),
                                                      color.z() };
    }

    void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB,
                          btScalar distance, int lifeTime,
                          const btVector3& color) override
    {
    }

    void reportErrorWarning(const char* warningString) override {}

    void draw3dText(const btVector3& location, const char* textString) override
    {
    }

    void setDebugMode(int debugMode) override {}

    int getDebugMode() const override { return 0; }

private:
    video_component* video_component_; // we don't own the rendered so should not destroy it

    std::shared_ptr<model> model_;
};

} // namespace pt