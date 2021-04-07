#pragma once

#include "FunctionCall.h"

using namespace std;

class getCharInstr : public FunctionCall {

    public:
        getCharInstr() {type=GETCHARINSTR;}

        virtual std::string toString() override;

    private:
       

};