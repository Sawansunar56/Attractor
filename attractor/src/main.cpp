#include "imgui.h"
#include "rlimgui.h"
#include <raylib.h>
#include <vector>

struct Entity
{
    Vector2 Position;
    Vector2 Velocity;

    Entity(Vector2 Position, Vector2 Velocity)
        : Position(Position), Velocity(Velocity)
    {
    }
};

struct Ball : public Entity
{
    float radius;
    float attractFactor;

    Ball(Vector2 Position, Vector2 Velocity, float radius, float attractFactor)
        : radius(radius), attractFactor(attractFactor),
          Entity(Position, Velocity)
    {
    }

    bool AttractChecker(Ball v1, Ball v2)
    {
        if (v1.attractFactor > v2.attractFactor)
            return true;
        return false;
    }

    void Update(Ball v1, float dt)
    {
        Vector2 directionVector;

        if (v1.attractFactor > attractFactor)
        {
            directionVector.x = v1.Position.x - Position.x;
            directionVector.y = v1.Position.y - Position.y;
        } else
        {
            directionVector.x = Position.x - v1.Position.x;
            directionVector.y = Position.y - v1.Position.y;
        }

        Position.x += directionVector.x * dt * attractFactor;
        Position.y += directionVector.y * dt * attractFactor;
    }

    void Update(Vector2 destination, float dt)
    {
        Vector2 directionVector;

        directionVector.x = destination.x - Position.x;
        directionVector.y = destination.y - Position.y;

        Position.x += directionVector.x * dt * attractFactor;
        Position.y += directionVector.y * dt * attractFactor;
    }
    void Render() { DrawCircle(Position.x, Position.y, radius, BLACK); }
};

int main()
{
    constexpr int SCREEN_HEIGHT = 720;
    constexpr int SCREEN_WIDTH  = 1280;

    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Particle");
    rlImGuiSetup(true);

    Ball attractee({100, 100}, {0, 0}, 10, .03);
    Ball attractor({300, 400}, {0, 0}, 20, .02);
    std::vector<Ball> ballList;
    ballList.push_back(attractee);
    ballList.push_back(attractor);
    ballList.push_back(Ball({600, 200}, {0, 0}, 50, 0.2f));
    ballList.push_back(Ball({400, 700}, {0, 0}, 50, 0.09f));
    ballList.push_back(Ball({100, 500}, {0, 0}, 50, 0.8f));

    bool toggle  = true;
    int movement = 10;

    while (!WindowShouldClose())
    {
        // raylib drawing
        BeginDrawing();
        ClearBackground(WHITE);

        float dt = GetFrameTime();
        // rlimgui setup
        rlImGuiBegin();
        ImGui::Begin("Settings One");
        ImGui::Checkbox("toggle", &toggle);
        for (int i = 0; i < ballList.size(); i++)
        {
            ImGui::Text("ball[%d]: Position: %f %f", i, ballList[i].Position.x,
                        ballList[i].Position.y);
        }
        ImGui::End();

        // if(AttractChecker(attractor, attractee)) {
        //     attractee.Update(attractor, dt);
        // } else {
        //     attractor.Update(attractee, dt);
        // }

        if (IsKeyPressed(KEY_LEFT))
        {
            attractor.Position.x -= movement;
        }
        if (IsKeyPressed(KEY_RIGHT))
        {
            attractor.Position.x += movement;
        }
        if (IsKeyPressed(KEY_UP))
        {
            attractor.Position.y -= movement;
        }
        if (IsKeyPressed(KEY_DOWN))
        {
            attractor.Position.y += movement;
        }

        Vector2 destination{(float)GetMouseX(), (float)GetMouseY()};
        for (int i = 0; i < ballList.size() - 1; ++i)
        {
            for (int j = i + 1; j < ballList.size(); ++j)
            {
                ballList[i].Update(destination, dt);
                ballList[j].Update(destination, dt);
            }
        }

        for (auto Ball : ballList)
        {
            Ball.Render();
        }

        // end drawing
        rlImGuiEnd();
        EndDrawing();
    }

    // closing window
    rlImGuiShutdown();
    CloseWindow();

    return 0;
}
