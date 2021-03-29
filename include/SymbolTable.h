#pragma once
#include <unordered_map>
#include <memory>
#include "type/Type.h"
#include <string>

typedef struct symbolTableElements{
	Type* type;
	bool isSet;
	bool isUsed;
	int memoryOffset;
	
	bool isConst;
	std::string constValue;

	symbolTableElements(Type* type, bool isSet, bool isUsed, int memoryoffset) 
		: type(type), isSet(isSet), isUsed(isUsed), memoryOffset(memoryoffset) {isConst = false; constValue = "";} 
	symbolTableElements(Type* _type, std::string _constValue)
		: type(_type), isSet(false), isUsed(false), memoryOffset(false), isConst(true), constValue(_constValue){}
} symbolTableElement;

typedef std::unordered_map<std::string, std::shared_ptr<symbolTableElement>> SymbolMap;

class SymbolTable{
	public:
		SymbolTable() {}

		virtual ~SymbolTable() {}
		
		std::shared_ptr<symbolTableElement> getSymbol(std::string name) { return elements->at(name) ; }
		void putSymbol(std::string name, std::shared_ptr<symbolTableElement> symbol) { 
			elements->emplace(name, symbol);
		 }

		 std::string create_new_tempvar(Type* t);
		
		int get_var_index(std::string name);
		
		Type* get_var_type(std::string name);

		//const std::unique_ptr<SymbolMap> & getElements() { return elements; }

	private:
		std::unique_ptr<SymbolMap> elements;

};