#pragma once

#include "ControlStructure.h"
#include <memory>

using namespace std;

class ForInstr : public ControlStructure
{
    public:
        ForInstr(shared_ptr<Expression> initialisation, shared_ptr<Expression> step) 
            : initialisation(initialisation), step(step) {}

        inline shared_ptr<Expression> getInitialisation() { return initialisation; }
        inline shared_ptr<Expression> getStep() { return step; }
        virtual std::string toString() override;
    private:
        shared_ptr<Expression> initialisation;
        shared_ptr<Expression> step;
};