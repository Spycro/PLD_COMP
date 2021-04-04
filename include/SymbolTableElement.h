#include "type/Type.h"
#include <string>
class SymbolTableElement{
    public:
        SymbolTableElement(Type* type, bool isSet, bool isUsed, int memoryoffset) 
		    : type(type), isSet(isSet), isUsed(isUsed), memoryOffset(memoryoffset) {isConst = false; constValue = "";} 
	    SymbolTableElement(Type* _type, std::string _constValue)
		    : type(_type), isSet(false), isUsed(false), memoryOffset(false), isConst(true), constValue(_constValue){}

        std::string getAsm(){
            if(isConst){
                return "$" + constValue;
            }else{
                return "-" + std::to_string(memoryOffset) + "(%rbp)";
            }
        }
    private:
        Type* type;
        bool isSet;
        bool isUsed;
        int memoryOffset;
        
        bool isConst;
        std::string constValue;


};