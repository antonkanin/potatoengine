#pragma once

#include "../video_component.hpp"
#include "log_utils.hpp"
#include "model.hpp"
#include <LinearMath/btIDebugDraw.h>

namespace pt
{

class debug_drawer : public btIDebugDraw
{
public:
    explicit debug_drawer(video_component* video_component,
                          movable_object*  camera);

    ~debug_drawer();

    void drawLine(const btVector3& from, const btVector3& to,
                  const btVector3& color) override
    {
        video_component_->render_line(
            /*from*/ { from.x(), from.y(), from.z() },
            /*to*/ { to.x(), to.y(), to.z() },
            /*color*/ { color.x(), color.y(), color.z() },
            /*camera*/ *camera_);
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

    void setDebugMode(int debugMode) override { debug_mode_ = debugMode; }

    int getDebugMode() const override { return debug_mode_; }

private:
    video_component* video_component_;
    movable_object*  camera_;
    int              debug_mode_;
};

} // namespace pt