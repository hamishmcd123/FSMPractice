#pragma once
#include "behaviour.hpp"

class RecoverBehaviour : public Behaviour {
public:
    void update(Agent *agent, float dtime) override;
    void exit(Agent *agent) override;
    void enter(Agent *agent) override;
    static float timer;
};
