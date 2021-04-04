#pragma once
#include <unordered_map>
#include <memory>
#include "type/Type.h"


typedef struct symbolTableElements{
	Type* type;
	bool isSet;
	bool isUsed;
	bool isFunction;
	int memoryOffset;

	symbolTableElements(Type* type, bool isFunction)
		: type(type), isSet(false), isUsed(false), isFunction(isFunction), memoryOffset(0) {}
	symbolTableElements(Type* type, bool isSet, bool isUsed, bool isFunction, int memoryoffset) 
		: type(type), isSet(isSet), isUsed(isUsed), isFunction(isFunction), memoryOffset(memoryoffset) {} 
} symbolTableElement;

typedef std::unordered_map<std::string, std::shared_ptr<symbolTableElement>> SymbolMap;

class SymbolTable{
	public:
		SymbolTable()
			: elements(std::unique_ptr<SymbolMap>(new SymbolMap())) {}

		virtual ~SymbolTable() {}
		
		std::shared_ptr<symbolTableElement> getSymbol(std::string name) { return elements->at(name) ; }
		void putSymbol(std::string name, std::shared_ptr<symbolTableElement> symbol) { 
			elements->emplace(name, symbol);
		 }

		void addVariable (std::string variableName, Type* variableType);
		void addFunction (std::string functionName, Type* functionReturnType);
		//const std::unique_ptr<SymbolMap> & getElements() { return elements; }

	private:
		std::unique_ptr<SymbolMap> elements;

};