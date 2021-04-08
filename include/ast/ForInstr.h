#pragma once

#include "ControlStructure.h"
#include <memory>

using namespace std;

class ForInstr : public ControlStructure
{
    public:
        ForInstr()
            : initialisation(nullptr), step(nullptr) {type=FORINSTR;}

        ForInstr(shared_ptr<Node> initialisation, shared_ptr<Node> step) 
            : initialisation(move(initialisation)), step(step) {type=FORINSTR;}

        inline shared_ptr<Node> getInitialisation() override { return initialisation; }
        inline void setInitialisation(shared_ptr<Node> initialisation) override { this->initialisation = initialisation; }
        inline shared_ptr<Node> getStep() override { return step; }
        inline void setStep(shared_ptr<Node> step) override { this->step = step; }
        virtual std::string toString() override;
    private:
        shared_ptr<Node> initialisation;
        shared_ptr<Node> step;
};