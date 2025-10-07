#include "../Utilities/util.h"
#include "../Utilities/settings.h"
#include "../Engine/sdk.h"
#pragma once
bool memory_event(Vector3 newpos)
{
    write<Vector3>(LocalPtrs::PlayerController + 0x2D48, newpos); //PlayerAimOffset
    return true;
}

void aim(uintptr_t targetmeshs, Vector2 target2d) {
    Vector2 target{};
    float speedPercent = settings::aimbot.smoothsize;
    float smoothness = 100.0f - (speedPercent - 1.0f);
    if (smoothness < 1.0f) smoothness = 1.0f;

    float screen_center_x = static_cast<float>(Width) / 2;
    float screen_center_y = static_cast<float>(Height) / 2;

    if (target2d.x > screen_center_x) {
        target.x = -(screen_center_x - target2d.x) / smoothness;
        if (target.x + screen_center_x > screen_center_x * 2)
            target.x = 0;
    }
    else if (target2d.x < screen_center_x) {
        target.x = (target2d.x - screen_center_x) / smoothness;
        if (target.x + screen_center_x < 0)
            target.x = 0;
    }

    if (target2d.y > screen_center_y) {
        target.y = -(screen_center_y - target2d.y) / smoothness;
        if (target.y + screen_center_y > screen_center_y * 2)
            target.y = 0;
    }
    else if (target2d.y < screen_center_y) {
        target.y = (target2d.y - screen_center_y) / smoothness;
        if (target.y + screen_center_y < 0)
            target.y = 0;
    }

    float scale = 5.0f;
    memory_event(Vector3(-target.y / 5, target.x / 5, 0));

}