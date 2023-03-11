#include "boids.hpp"
#include "glm/fwd.hpp"

using vec   = glm::vec2;
using color = p6::Color;

Boids::Boids()
    : m_center(0.f), m_angle(0), m_velocity(0), m_color(1.)
{}

Boids::Boids(Boids& b)
    : m_center(b.m_center), m_angle(b.m_angle), m_velocity(b.m_velocity), m_color(b.m_color)
{}

Boids::Boids(vec center, int angle, float velocity, color color)
    : m_center(center), m_angle(angle), m_velocity(velocity), m_color(color)
{}

void Boids::draw(p6::Context& ctx)
{
    ctx.fill = getColor();
    ctx.equilateral_triangle(p6::Center{getCenter()}, p6::Radius{0.09f}, p6::Rotation{p6::Angle(p6::Radians(45))});
}