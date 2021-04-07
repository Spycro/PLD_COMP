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

std::string ASMx86Utils::moveTo(SymbolTableElement& src, SymbolTableElement& dst) {

    std::stringstream ss;

    if(src.getSize() == dst.getSize()) { // src size match dst size

        ss << "\tmov" << symbolSizeChar(src.getSize()) << " " << src.getAsm() << ", " << dst.getAsm();

    } else if(dst.getSize() > src.getSize()) {

        SymbolTableElement& srcReg = getSubReg(RAX_REGISTER, src.getSize());
        SymbolTableElement& dstReg = getSubReg(RAX_REGISTER, dst.getSize());

        //TODO: optimise the number of instructions in specific cases

        // Move src to a registry where it fits and only if needed (eg: to not to movb %al, %al)
        if(src.getAsm() != srcReg.getAsm()) {
            ss << "\tmov" << symbolSizeChar(src.getSize()) << " " << src.getAsm() << ", " << srcReg.getAsm() << std::endl;
        }

        // Sign-extend the value in registry to the size of dst (movsxq, with x either b, q or l depending on the symbol's size)
        ss << "\tmovs" << symbolSizeChar(src.getSize()) << symbolSizeChar(dst.getSize()) << " " << srcReg.getAsm() << ", " << dstReg.getAsm() << std::endl;
        // Finally move the value from the registry to the dst
        ss << "\tmov" << symbolSizeChar(dst.getSize()) << " " << dstReg.getAsm() << ", " << dst.getAsm();

    } else { // dst.getSize() < src.getSize()

        SymbolTableElement& srcReg = getSubReg(RAX_REGISTER, src.getSize());
        SymbolTableElement& dstReg = getSubReg(RAX_REGISTER, dst.getSize());

        // Move src to a registry where it fits
        ss << "\tmov" << symbolSizeChar(src.getSize()) << " " << src.getAsm() << ", " << srcReg.getAsm() << std::endl;
        // Truncate and only move the part that interests us
        ss << "\tmov" << symbolSizeChar(dst.getSize()) << " " << dstReg.getAsm() << ", " << dst.getAsm();

    }

    return ss.str();
}


//TODO: remove this and use moveTo above instead
std::string ASMx86Utils::moveTo64Reg(SymbolTableElement& s, SymbolTableElement& reg64) {

    std::stringstream ss;

    if(s.getSize() == 8) {
        ss << "\tmovq " << s.getAsm() << ", " << reg64.getAsm();
    } else if(s.getSize() < 8) {
        // Move s to a registry where it fits
        ss << "\tmov" << symbolSizeChar(s.getSize()) << " " << s.getAsm() << ", " << getSubReg(reg64, s.getSize()).getAsm() << std::endl;
        // Sign-extend it to the full 64 bits registry (movsxq, with x either b, q or l depending on the symbol's size)
        ss << "\tmovs" << symbolSizeChar(s.getSize()) << "q" << " " << s.getAsm() << ", " << reg64.getAsm();
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