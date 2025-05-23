// MIT License
// Copyright (c) 2025 Arseniy Panyukov
//
// See the LICENSE file in the root directory for full license information.


#ifndef ANIMATION_H
#define ANIMATION_H
#include <dto/poses/dynamic/keyframe/Keyframe.h>


class Animation
{
public:
    Animation() = default;

    Animation(std::vector<Keyframe> keyframes, bool cyclic = false) : keyframes(keyframes), cyclic(cyclic) {}

    Animation(std::vector<Keyframe>&& keyframes, bool cyclic = false) : keyframes(std::move(keyframes)), cyclic(cyclic) {}

    const std::vector<Keyframe>& getKeyframes() const { return keyframes; }

    bool isCyclic() const { return cyclic; }


private:
    std::vector<Keyframe> keyframes;
    bool cyclic = false;
};



#endif //ANIMATION_H
