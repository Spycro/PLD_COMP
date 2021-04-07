#pragma once
#include <unordered_map>
#include <memory>
#include "type/Type.h"
#include <string>
#include "SymbolTableElement.h"

typedef std::unordered_map<std::string, std::shared_ptr<SymbolTableElement>> SymbolMap;

class SymbolTable{
	public:
		SymbolTable()
			: elements(std::unique_ptr<SymbolMap>(new SymbolMap())) {}

		virtual ~SymbolTable() {}
		
		std::shared_ptr<SymbolTableElement> getSymbol(std::string name) { return elements->at(name) ; }
		bool symbolInTable(std::string name){return elements->find(name) != elements->end();}
		/*
		void putSymbol(std::string name, std::shared_ptr<SymbolTableElement> symbol) { 
			elements->emplace(name, symbol);
		}*/

		
		int get_var_index(std::string name);
		
		VarType::Type* get_var_type(std::string name);

		std::shared_ptr<SymbolTableElement> addVariable (std::string variableName, const VarType::Type* variableType, int mem64);
		std::shared_ptr<SymbolTableElement> addFunction (std::string functionName, const VarType::Type* functionReturnType, int mem64);
		//const std::unique_ptr<SymbolMap> & getElements() { return elements; }

	private:
		std::unique_ptr<SymbolMap> elements;

};