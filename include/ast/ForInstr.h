#pragma once

#include "ControlStructure.h"
#include <memory>

using namespace std;

class ForInstr : public ControlStructure {

    public:
        inline shared_ptr<Expression> getInitialisation() { return initialisation; }
        inline shared_ptr<Expression> getStep() { return step; }
        void toString(int n);
    private:
        shared_ptr<Expression> initialisation;
        shared_ptr<Expression> step;

};