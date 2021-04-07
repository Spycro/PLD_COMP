#include "SymbolTableElement.h"
#include "ir/ASMConstants.h"

VarType::Void VOIDTYPE;
VarType::Int64 INTTYPE64;
VarType::Int32 INTTYPE32;

SymbolTableElement RAX_REGISTER (&INTTYPE64, "rax", true);
SymbolTableElement RBX_REGISTER (&INTTYPE64, "rbx", true);
SymbolTableElement RCX_REGISTER (&INTTYPE64, "rcx", true);
SymbolTableElement RDX_REGISTER (&INTTYPE64, "rdx", true);

SymbolTableElement EAX_REGISTER (&INTTYPE32, "eax", true);
SymbolTableElement EBX_REGISTER (&INTTYPE32, "ebx", true);
SymbolTableElement ECX_REGISTER (&INTTYPE32, "ecx", true);
SymbolTableElement EDX_REGISTER (&INTTYPE32, "edx", true);

SymbolTableElement AX_REGISTER (&INTTYPE16, "ax", true);
SymbolTableElement BX_REGISTER (&INTTYPE16, "bx", true);
SymbolTableElement CX_REGISTER (&INTTYPE16, "cx", true);
SymbolTableElement DX_REGISTER (&INTTYPE16, "dx", true);

SymbolTableElement AL_REGISTER (&CHARTYPE, "al", true);
SymbolTableElement BL_REGISTER (&CHARTYPE, "bl", true);
SymbolTableElement CL_REGISTER (&CHARTYPE, "cl", true);
SymbolTableElement DL_REGISTER (&CHARTYPE, "dl", true);

SymbolTableElement R8_REGISTER (&INTTYPE64, "r8", true);
SymbolTableElement R9_REGISTER (&INTTYPE64, "r9", true);
SymbolTableElement R8D_REGISTER (&INTTYPE32, "r8d", true);
SymbolTableElement R9D_REGISTER (&INTTYPE32, "r9d", true);

SymbolTableElement RDI_REGISTER (&INTTYPE64, "rdi", true);
SymbolTableElement RSI_REGISTER (&INTTYPE64, "rsi", true);