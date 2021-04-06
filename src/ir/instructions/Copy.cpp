#include "ir/instructions/Copy.h"

Copy::Copy(BasicBlock* bb, SymbolTableElement inputX, SymbolTableElement inputD) : IRInstr(bb), d(inputD), x(inputX){}


void Copy::gen_asm(std::ostream &o) {

    std::string val, dest;

    val = x.getAsm();
    dest = d.getAsm();

    if(x.getSize() == 1) { // move 8 bits

        if(dest.size() == 1) {
            // Extend val to 32 bits with zeroes and put it in eax (32 bits register). We are forced to do this because we don't have 1 byte register.
            // Then we get least significant byte of eax (from %al) and put it in the destination
            o << "\tmovzbl " << val << ", \%eax" << std::endl;
            o << "\tmovb \%al, " << dest << std::endl;
        } else if(dest.size() == 2) {
            // Extend byte to 16 bits with zeroes and put it in %ax (16 bits register)
            // Then we move %ax into the destination
            o << "\tmovsbw " << val << ", \%ax" << std::endl;
            o << "\tmovw \%ax, " << dest << std::endl;
        } else if(dest.size() == 4) {
            // Extend byte to 32 bits with zeroes and put it in %eax (32 bits register)
            // Then we move %eax into the destination
            o << "\tmovsbl " << val << ", \%eax" << std::endl;
            o << "\tmovl \%eax, " << dest << std::endl;
        } else if(dest.size() == 8) {
            // Extend byte to 64 bits with zeroes and put it in %rax (64 bits register)
            // Then we move %rax into the destination
            o << "\tmovsbq " << val << ", \%rax" << std::endl;
            o << "\tmovq \%rax, " << dest << std::endl;
        }

    } else if(x.getSize() == 2) { // move 16 bits

        if(dest.size() == 1) {
            // We truncate and only keep the 8 lsb
            o << "\tmovzwl " << val << ", \%eax" << std::endl;
            o << "\tmovb \%al, " << dest << std::endl;
        } else if(dest.size() == 2) {
            o << "\tmovzwl " << val << ", \%eax" << std::endl;
            o << "\tmovw \%ax, " << dest << std::endl;
        } else if(dest.size() == 4) {
            // Extend to 32 bits with zeroes and copy in dest
            o << "\tmovswl " << val << ", \%eax" << std::endl;
            o << "\tmovl \%eax, " << dest << std::endl;
        } else if(dest.size() == 8) {
            // Extend to 64 bits with zeroes and copy in dest
            o << "\tmovzwq " << val << ", \%rax" << std::endl;
            o << "\tmovq \%rax, " << dest << std::endl;
        }

    } else if(x.getSize() == 4) { // move 32 bits

        if(dest.size() == 1) {
            // We truncate and only keep the 8 lsb
            o << "\tmovl " << val << ", \%eax" << std::endl;
            o << "\tmovb \%al, " << dest << std::endl;
        } else if(dest.size() == 2) {
            // We truncate and only keep the 16 lsb
            o << "\tmovl " << val << ", \%eax" << std::endl;
            o << "\tmovw \%ax, " << dest << std::endl;
        } else if(dest.size() == 4) {
            o << "\tmovl " << val << ", \%eax" << std::endl;
            o << "\tmovl \%eax, " << dest << std::endl;
        } else if(dest.size() == 8) {
            o << "\tmovzwq " << val << ", \%eax" << std::endl;
            o << "\tcltq" << std::endl; // sign-extends eax to a quadword
            o << "\tmovq \%rax, " << dest << std::endl;
        }

    } else if(x.getSize() == 8) { // move 64 bits

        if(dest.size() == 1) {
            // We truncate and only keep the 8 lsb
            o << "\tmovq " << val << ", \%rax" << std::endl;
            o << "\tmovb \%al, " << dest << std::endl;
        } else if(dest.size() == 2) {
            // We truncate and only keep the 16 lsb
            o << "\tmovq " << val << ", \%rax" << std::endl;
            o << "\tmovw \%ax, " << dest << std::endl;
        } else if(dest.size() == 4) {
            // We truncate and only keep the 32 lsb
            o << "\tmovq " << val << ", \%rax" << std::endl;
            o << "\tmovl \%eax, " << dest << std::endl;
        } else if(dest.size() == 8) {
            o << "\tmovq " << val << ", \%rax" << std::endl;
            o << "\tmovq \%rax, " << dest << std::endl;
        }

    } else {
        throw "Unsupported size.";
    }

    
}