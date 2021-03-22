#include "ir/operations/Copy.h"

Copy::Copy(BasicBlock* bb, Type* t, std::string inputD, std::string inputX) : IRInstr(bb,t), d(inputD), x(inputX){}

