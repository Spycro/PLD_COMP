#include "SymbolTableElement.h"
#include "type/Int64.h"
#include "type/Int32.h"

SymbolTableElement RAX_REGISTER (&INTTYPE64, "rax", true);
SymbolTableElement RBX_REGISTER (&INTTYPE64, "rbx", true);
SymbolTableElement RCX_REGISTER (&INTTYPE64, "rcx", true);
SymbolTableElement RDX_REGISTER (&INTTYPE64, "rdx", true);
SymbolTableElement R8_REGISTER (&INTTYPE64, "r8", true);
SymbolTableElement R9_REGISTER (&INTTYPE64, "r9", true);

SymbolTableElement EAX_REGISTER (&INTTYPE32, "eax", true);
SymbolTableElement EBX_REGISTER (&INTTYPE32, "ebx", true);
SymbolTableElement ECX_REGISTER (&INTTYPE32, "ecx", true);
SymbolTableElement EDX_REGISTER (&INTTYPE32, "edx", true);
SymbolTableElement R8D_REGISTER (&INTTYPE32, "r8d", true);
SymbolTableElement R9D_REGISTER (&INTTYPE32, "r9d", true);