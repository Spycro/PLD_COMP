#pragma once

#include <vector>
#include <memory>
#include <list>
#include "Scope.h"
using namespace std;

#define THROW { throw; }

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
    WHILEINSTR,
    PUTCHARINSTR,
    GETCHARINSTR,
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
    NOT,
    UNARYMINUS
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
    virtual bool isBlock() THROW
    virtual NodeType getType() { return type; }

    /***************BLOCK*****************/
    virtual inline shared_ptr<Scope> getScope() THROW
    virtual inline vector<shared_ptr<Node>>& getInstructions() THROW

    virtual void setScope(shared_ptr<Scope> s) THROW
    /**************************************/

    /*************CONTROLSTRUCT************/
    virtual inline shared_ptr<Node> getTest() THROW
    virtual inline void setTest(shared_ptr<Node> test) THROW
    virtual inline shared_ptr<Node> getCode() THROW //For function too
    virtual inline void setCode(shared_ptr<Node> code) THROW //For function too
    /**************************************/

    /*************FORINSTR*************/
    virtual inline shared_ptr<Node> getInitialisation() THROW
    virtual inline void setInitialisation(shared_ptr<Node>) THROW
    virtual inline shared_ptr<Node> getStep() THROW
    virtual inline void setStep(shared_ptr<Node>) THROW
    /**************************************/

    /**************FUNCTION************/
    virtual inline list<shared_ptr<Node>> getParameters() THROW
    /*********************************/

    /**************IFINSTR************/
    virtual inline shared_ptr<Node> getCodeElse() THROW
    /*********************************/

    /**************RETURN*************/
    virtual shared_ptr<Node> getValue() THROW //for affecation
    virtual inline void setValue(shared_ptr<Node>) THROW //for affecation
    /*********************************/
    
    
    /************AFFECTATION************/
    virtual inline string& getSymbol() THROW
    /*********************************/
    
    /************ARRAY************/
    virtual inline shared_ptr<Node> getPosition() THROW
    /*********************************/

    /***********BINARY**********************/ //and part Tenary too
    virtual inline shared_ptr<Node> getOperand1() THROW
    virtual inline shared_ptr<Node> getOperand2() THROW
    virtual inline BinaryOperator getOp() THROW
    virtual void setOperand1(shared_ptr<Node> op1) THROW
    virtual void setOperand2(shared_ptr<Node> op2) THROW
    virtual void setBinaryOperator(BinaryOperator bop) THROW
    /***************************************/

    /***********TERNARY*********************/
    virtual inline shared_ptr<Node> getOperand3() THROW
    /*****************************************/
    
    /************UNARY************************/
    virtual inline shared_ptr<Node> getOperand() THROW
    virtual inline UnaryOperator getUnaryOp() THROW
    virtual void setOperand(shared_ptr<Node> op) THROW
    virtual void setOp(UnaryOperator o) THROW
    /*****************************************/

    /****************VARIABLE***********/
    virtual void setSymbol(std::string) THROW
    /**************************************/

    /**************CONST**************/
    virtual inline int getConstValue() THROW
    virtual void setConstValue(int value) THROW
    /*********************************/



protected:
    vector<shared_ptr<Node>> children;
    shared_ptr<Node> parent;
    NodeType type;
    std::string placeholder = "";
};