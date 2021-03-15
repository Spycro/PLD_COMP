#pragma once

#include "ControlStructure.h"

using namespace std;

class ForInstr : public ControlStructure {

    public:

    private:
        shared_ptr<Expression> initialisation;
        shared_ptr<Expression> step;

};