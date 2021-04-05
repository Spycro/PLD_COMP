#pragma once

#include "ControlStructure.h"
#include <memory>

using namespace std;

class ForInstr : public ControlStructure
{
    public:
        ForInstr()
            : initialisation(nullptr), step(nullptr) {}

        ForInstr(shared_ptr<Expression> initialisation, shared_ptr<Expression> step) 
            : initialisation(move(initialisation)), step(step) {}

        inline shared_ptr<Expression> getInitialisation() { return initialisation; }
        inline void setInitialisation(shared_ptr<Expression> initialisation) { this->initialisation = initialisation; }
        inline shared_ptr<Expression> getStep() { return step; }
        inline void setStep(shared_ptr<Expression> step) { this->step = step; }
        virtual std::string toString() override;
    private:
        shared_ptr<Expression> initialisation;
        shared_ptr<Expression> step;
};