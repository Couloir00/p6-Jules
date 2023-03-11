#include <cstddef>
#include <cstdlib>
#include <iterator>
#include <vector>
#include "boids.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"

using vec   = glm::vec2;
using color = p6::Color;

float Deg2Rad(int deg)
{
    return static_cast<float>(deg) * (p6::PI / static_cast<float>(180));
}

vec newPosFromAngle(vec center, int angle, float velocity)
{
    vec newPos = vec((velocity * cos(Deg2Rad(angle))) / 2.f + center.x, (velocity * sin(Deg2Rad(angle))) / 2.f + center.y);
    return newPos;
}

int main(int argc, char* argv[])
{
    { // Run the tests
        if (doctest::Context{}.run() != 0)
            return EXIT_FAILURE;
        // The CI does not have a GPU so it cannot run the rest of the code.
        const bool no_gpu_available = argc >= 2 && strcmp(argv[1], "-nogpu") == 0; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        if (no_gpu_available)
            return EXIT_SUCCESS;
    }

    // Actual app
    auto ctx = p6::Context{{.title = "Simple-p6-Setup"}};
    ctx.maximize_window();

    float windowWidth = ctx.aspect_ratio();

    // create vector of boids
    std::vector<Boids> boids;

    for (int i = 0; i < 2; i++)
    {
        vec RandCoord = p6::random::point();
        boids.emplace_back(vec(RandCoord.x * windowWidth, RandCoord.y), p6::random::number(1, 360), 0.017, color(1.f, 0.f, 1.f));
    }
    bool isNear = false;

    // Declare your infinite update loop.
    ctx.update = [&]() {
        ctx.use_stroke = false;
        ctx.fill       = {0.f};
        ctx.rectangle(p6::FullScreen{});
        const float treshold = 0.35f;
        for (Boids& i : boids)
        {
            ctx.fill = {0.f, 1.f, 0.f};
            ctx.circle(p6::Center{i.getCenter()}, p6::Radius{treshold});

            i.draw(ctx);

            // create direction
            int direction = p6::random::number(1, 100);

            if (direction <= 20)
            {
                i.setAngle(i.getAngle() + 10);
            }
            else if (direction >= 80)
            {
                i.setAngle(i.getAngle() - 10);
            }

            // New position (make them move in the loop)
            glm::vec2 newPos =
                newPosFromAngle(i.getCenter(), i.getAngle(), i.getVelocity());
            if (newPos.x > windowWidth)
                newPos.x = -1.f * windowWidth;
            if (newPos.y > 1)
                newPos.y = -1.f;
            if (newPos.x < -windowWidth)
                newPos.x = 1.f * windowWidth;
            if (newPos.y < -1)
                newPos.y = 1.f;
            i.setPos(newPos);
        }
        for (size_t j = 0; j < boids.size(); j++)
        {
            if (glm::distance(boids[j].getCenter(), boids[j + 1].getCenter()) < treshold)
            {
                isNear = true;
            }
            else
            {
                isNear = false;
            }
        }
        std::cout << isNear << std::endl;
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}