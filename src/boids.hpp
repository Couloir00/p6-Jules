#ifndef __BOIDS_HPP__
#define __BOIDS_HPP__
#include <stdlib.h>
#include <vector>
#include "glm/fwd.hpp"
#include "p6/p6.h"

using vec   = glm::vec2;
using color = p6::Color;

class Boids {
private:
    vec   m_center;
    int   m_angle;
    float m_velocity;
    color m_color;

public:
    // constructors
    Boids();
    Boids(Boids& b);
    Boids(vec center, int angle, float velocity, color color);

    // getters & setters
    inline void setPos(vec center) { m_center = center; }
    inline void setAngle(int angle) { m_angle = angle; }

    inline vec   getCenter() const { return m_center; }
    inline int   getAngle() const { return m_angle; }
    inline float getVelocity() const { return m_velocity; }
    inline color getColor() const { return m_color; }

    // functions
    void draw(p6::Context& ctx);
};

#endif