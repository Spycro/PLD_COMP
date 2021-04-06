#pragma once

#include <vector>
#include <memory>
#include <list>
#include "Scope.h"
using namespace std;

typedef enum {
    BLOCK,
    BREAK,
    CONTINUE,
    CONTROLSTRUCTURE,
    DOWHILEINSTR,
    FORINSTR,
    FUNCTION,
    INFINSTR,
    NULLINSTR,
    RETURN,
    AFFECTATION,
    ARRAY,
    BINARY,
    CONST,
    FUNCTIONCALL,
    TERNARY,
    UNARY,
    VARIABLE,
    WHILEINSTR
} NodeType;

typedef enum
{
    PLUS,
    MINUS,
    MULT,
    DIV,
    MOD,
    EQUAL,
    NE,
    GTE,
    LTE,
    GT,
    LT,
    BINAND,
    LOGAND,
    BINOR,
    LOGOR,
    BINXOR,
    LOGXOR
} BinaryOperator;

typedef enum
{
    PREINCR,
    POSTINCR,
    PREDECR,
    POSTDECR,
    PARENTHESIS,
    TILD,
    NOT
} UnaryOperator;

class Node
{

public:

    Node() {}

    Node(shared_ptr<Node> parent) 
        : parent(parent) {}

    inline vector<shared_ptr<Node>>& getChildren() { return children; }
    inline shared_ptr<Node>& getParent() { return parent; }
    void setParent(std::shared_ptr<Node> node) { 
        parent.reset();
        parent = node;
    }
    
    virtual std::string toString();
    virtual bool isBlock() { return false; }
    virtual NodeType getType() { return type;}

    /***************BLOCK*****************/
    virtual inline shared_ptr<Scope> getScope() {return nullptr;};
    virtual inline vector<shared_ptr<Node>> getInstructions() {return vector<shared_ptr<Node>>();}

    virtual void setScope(shared_ptr<Scope> s) {}
    /**************************************/

    /*************CONTROLSTRUCT************/
    virtual inline shared_ptr<Node> getTest() {return nullptr;}
    virtual inline void setTest(shared_ptr<Node> test) {}
    virtual inline shared_ptr<Node> getCode() {return nullptr;} //For function too
    virtual inline void setCode(shared_ptr<Node> code) {} //For function too
    /**************************************/

    /*************FORINSTR*************/
    virtual inline shared_ptr<Node> getInitialisation() {return nullptr;}
    virtual inline void setInitialisation(shared_ptr<Node>) {}
    virtual inline shared_ptr<Node> getStep() {return nullptr;}
    virtual inline void setStep(shared_ptr<Node>) {}
    /**************************************/

    /**************FUNCTION************/
    virtual inline list<shared_ptr<Node>> getParameters() {return list<shared_ptr<Node>>();}
    /*********************************/

    /**************IFINSTR************/
    virtual inline shared_ptr<Node> getCodeElse() { return nullptr; }
    /*********************************/

    /**************RETURN*************/
    virtual shared_ptr<Node> getValue() { return nullptr; } //for affecation
    virtual inline void setValue(shared_ptr<Node>) { } //for affecation
    /*********************************/
    
    
    /************AFFECTATION************/
    virtual inline string& getSymbol() { return placeholder; }
    /*********************************/
    
    /************ARRAY************/
    virtual inline shared_ptr<Node> getPosition() { return nullptr; }
    /*********************************/

    /***********BINARY**********************/ //and part Tenary too
    virtual inline shared_ptr<Node> getOperand1() { return nullptr; }
    virtual inline shared_ptr<Node> getOperand2() { return nullptr; }
    virtual inline BinaryOperator getOp() { return PLUS; }
    virtual void setOperand1(shared_ptr<Node> op1) {}
    virtual void setOperand2(shared_ptr<Node> op2) {}
    virtual void setBinaryOperator(BinaryOperator bop) {}
    /***************************************/

    /***********TERNARY*********************/
    virtual inline shared_ptr<Node> getOperand3() { return nullptr; }
    /*****************************************/
    
    /*UNARY*/
    virtual inline shared_ptr<Node> getOperand() { return nullptr; }
    virtual inline UnaryOperator getUnaryOp() { return POSTDECR; }
    virtual void setOperand(shared_ptr<Node> op) {}
    virtual void setOp(UnaryOperator o) {}
    /*****************************************/

    /****************VARIABLE***********/
    virtual void setSymbol(std::string) { }
    /**************************************/

    /**************CONST**************/
    virtual inline int getConstValue() { return 0; }
    virtual void setConstValue(int value) { }
    /*********************************/



protected:
    vector<shared_ptr<Node>> children;
    shared_ptr<Node> parent;
    NodeType type;
    std::string placeholder = "";
};