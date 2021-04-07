#include "ir/ASMx86Utils.h"
#include "ir/ASMConstants.h"

#include <sstream>

char ASMx86Utils::symbolSizeChar(int s) {

    switch(s) {
        case 1:
            return 'b'; // 8 bits
        case 2:
            return 'w'; // 16 bits
        case 4:
            return 'l'; // 32 bits
        case 8:
            return 'q'; // 64 bits
        default:
            throw "Unsupported size.";
    }
}

std::string ASMx86Utils::moveTo64Reg(SymbolTableElement& s, SymbolTableElement& reg64) {

    std::stringstream ss;

    int size = s.getSize();

    if(size == 8) {
        ss << "\tmovq " << s.getAsm() << ", " << reg64.getAsm();
    } else if(size < 8) {
        ss << "\tmovs" << symbolSizeChar(size) << symbolSizeChar(8) << " " << s.getAsm() << ", " << reg64.getAsm();
    } else {
        throw "Unsupported size";
    }

    return ss.str();
}

SymbolTableElement& ASMx86Utils::getSubReg(SymbolTableElement& reg64, int s) {

    if(s == 8) {
        return reg64;
    }

    if(&reg64 == &RAX_REGISTER) {
        
        if(s == 1)
            return AL_REGISTER;
        else if(s == 2)
            return AX_REGISTER;
        else if(s == 4)
            return EAX_REGISTER;

    } else if(&reg64 == &RBX_REGISTER) {

        if(s == 1)
            return BL_REGISTER;
        else if(s == 2)
            return BX_REGISTER;
        else if(s == 4)
            return EBX_REGISTER;

    } else if(&reg64 == &RCX_REGISTER) {

        if(s == 1)
            return CL_REGISTER;
        else if(s == 2)
            return CX_REGISTER;
        else if(s == 4)
            return ECX_REGISTER;

    } else if(&reg64 == &RDX_REGISTER) {
        
        if(s == 1)
            return DL_REGISTER;
        else if(s == 2)
            return DX_REGISTER;
        else if(s == 4)
            return EDX_REGISTER;

    }

    throw "Can't find a valid sub-register.";
}