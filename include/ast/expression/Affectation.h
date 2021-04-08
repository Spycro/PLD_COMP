#pragma once

#include "Expression.h"
#include <string>

using namespace std;

class Affectation : public Expression
{

    public:
        Affectation()
            : lValue(nullptr), rValue(nullptr) {type=AFFECTATION;}
        
        Affectation(shared_ptr<Node> lValue)
            : lValue(lValue), rValue(nullptr) {type=AFFECTATION;} 

        Affectation(shared_ptr<Node> lValue, shared_ptr<Node> rValue)
            : lValue(lValue), rValue(rValue) {type=AFFECTATION;}
        
        inline shared_ptr<Node> getLValue() override { return lValue; }
        void setLValue(shared_ptr<Node> lValue) override { this->lValue = lValue; }

        inline shared_ptr<Node> getRValue() override { return rValue; }
        void setRValue(shared_ptr<Node> rValue) override { this->rValue = rValue; }

        virtual std::string toString() override;

    private:

        shared_ptr<Node> lValue;
        shared_ptr<Node> rValue;

};