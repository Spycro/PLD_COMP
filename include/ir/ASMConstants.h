#pragma once

#include "SymbolTableElement.h"

#include "type/Int64.h"
#include "type/Int32.h"
#include "type/Int16.h"
#include "type/Char.h"
#include "type/Void.h"

extern Void VOIDTYPE;
extern Int64 INTTYPE64;
extern Int32 INTTYPE32;
extern Int16 INTTYPE16;
extern Char CHARTYPE;

extern SymbolTableElement RAX_REGISTER;
extern SymbolTableElement RBX_REGISTER;
extern SymbolTableElement RCX_REGISTER;
extern SymbolTableElement RDX_REGISTER;

extern SymbolTableElement EAX_REGISTER;
extern SymbolTableElement EBX_REGISTER;
extern SymbolTableElement ECX_REGISTER;
extern SymbolTableElement EDX_REGISTER;

extern SymbolTableElement AX_REGISTER;
extern SymbolTableElement BX_REGISTER;
extern SymbolTableElement CX_REGISTER;
extern SymbolTableElement DX_REGISTER;

extern SymbolTableElement AL_REGISTER;
extern SymbolTableElement BL_REGISTER;
extern SymbolTableElement CL_REGISTER;
extern SymbolTableElement DL_REGISTER;

extern SymbolTableElement R8_REGISTER;
extern SymbolTableElement R9_REGISTER;
extern SymbolTableElement R8D_REGISTER;
extern SymbolTableElement R9D_REGISTER;

extern SymbolTableElement RDI_REGISTER;
extern SymbolTableElement RSI_REGISTER;