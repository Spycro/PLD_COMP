#pragma once

#include "FunctionCall.h"

using namespace std;

class putCharInstr : public FunctionCall {

    public:
        putCharInstr() {type=PUTCHARINSTR;}

        virtual std::string toString() override;

    private:
       

};