#pragma once

struct Animation {

    int index;
    int frames;
    int speed;

    Animation() {}

    Animation(int ind, int fram, int sped) {
        index = ind;
        frames = fram;
        speed = sped;
    }
};