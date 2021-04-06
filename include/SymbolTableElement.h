#pragma once

#include "type/Type.h"
#include "type/Void.h"
#include <string>

class SymbolTableElement{//todo this entire class should probably be seperated into multiple in the futur
    public:
        SymbolTableElement():type(&VOIDTYPE), isSet(false), isUsed(false), memoryOffset(0), isConst(false), constValue(""), isReg(false), regValue(""){}

        SymbolTableElement(VarType::Type* type, bool isSet, bool isUsed, int isFunction, int memoryoffset) 
		    : type(type), isSet(isSet), isUsed(isUsed), isFunction(isFunction), memoryOffset(memoryoffset), isConst(false),constValue(""), isReg(false), regValue(""){} 

        SymbolTableElement(VarType::Type* type, bool isSet, bool isUsed, int memoryoffset) 
		    : type(type), isSet(isSet), isUsed(isUsed), memoryOffset(memoryoffset), isConst(false),constValue(""), isReg(false), regValue(""){} 

	    SymbolTableElement(VarType::Type* _type, std::string _constValue)
		    : type(_type), isSet(false), isUsed(false), memoryOffset(false), isConst(true), constValue(_constValue), isReg(false), regValue(""){}

        SymbolTableElement(VarType::Type* _type, std::string _regValue, bool _isReg)
		    : type(_type), isSet(false), isUsed(false), memoryOffset(false), isConst(false), constValue(""), isReg(_isReg), regValue(_regValue){}

        std::string getAsm(){
            if(isConst){
                return "$" + constValue;
            }else if(isReg){
                return "%" + regValue;
            }else{
                return "-" + std::to_string(memoryOffset) + "(%rbp)";
            }
        }
        int getSize(){return type->getSize();}
    private:
        VarType::Type* type;
        bool isSet;
        bool isUsed;
        int memoryOffset;
        bool isFunction = false;
        
        bool isConst;
        std::string constValue;

        bool isReg;
        std::string regValue;
};