#pragma once
#include <Kinex/init.hpp>

namespace knx{
    namespace irl{
        class PhysicsMaterial{
            public:
            float DynamicFriction = 1;
            float StaticFriction = 1;
            float Bounciness = 1;
        };

        class PhysicsEnviroment{
            public:
            vec3f Gravity;
            float AirResistance;
        };
    };
};