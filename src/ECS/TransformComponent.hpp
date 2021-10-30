#pragma once
#include "Components.hpp"
#include "../Vector2D.hpp"

class TransformComponent : public Component {

public:

    Vector2D position;
    Vector2D velocity;

    int width = 32;
    int height = 32;
    int scale = 1;

    int speed = 3;

    TransformComponent() {
        position.x = 0.0;
        position.y = 0.0;
    }

    TransformComponent(int sc) {
        position.x = 0.0;
        position.y = 0.0;
        scale = sc;
    }

    TransformComponent(double x, double y) {
        position.x = x;
        position.y = y;
    }

    TransformComponent(double x, double y, int h, int w, int sc) {
        position.x = x;
        position.y = y;
        height = h;
        width = w;
        scale = sc;
    }

    void init() override {
        velocity.x = 0;
        velocity.y = 0;
    }

    void update() override {
        velocity.Normalize();
        position.x += double (velocity.x * speed);
        position.y += double (velocity.y * speed);
    }
};