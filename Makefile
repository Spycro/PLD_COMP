GRAMMAR=ifcc.g4

GENERATED=antlr4-generated

TESTS_DIR=tests

SRCS_DIR=src
INCLUDE_DIR=include
GEN_SRCS_DIR=$(SRCS_DIR)/$(GENERATED)
GEN_INCLUDE_DIR=$(INCLUDE_DIR)/$(GENERATED)

BUILD_DIR=build
GEN_BUILD_DIR=$(BUILD_DIR)/$(GENERATED)

SRCS := $(shell find $(SRCS_DIR)/ -name "*.cpp" -not -path "$(GEN_SRCS_DIR)/*")
HEADERS := $(shell find $(INCLUDE_DIR)/ -name "*.h" -not -path "$(GEN_INCLUDE_DIR)/*")
OBJECTS := $(SRCS:$(SRCS_DIR)/%.cpp=$(BUILD_DIR)/%.o)

GEN_SRCS := $(GEN_SRCS_DIR)/ifccBaseVisitor.cpp $(GEN_SRCS_DIR)/ifccLexer.cpp $(GEN_SRCS_DIR)/ifccParser.cpp $(GEN_SRCS_DIR)/ifccVisitor.cpp
GEN_HEADERS := $(GEN_INCLUDE_DIR)/ifccBaseVisitor.h $(GEN_INCLUDE_DIR)/ifccLexer.h $(GEN_INCLUDE_DIR)/ifccParser.h $(GEN_INCLUDE_DIR)/ifccVisitor.h
GEN_OBJECTS := $(GEN_SRCS:$(GEN_SRCS_DIR)/%.cpp=$(GEN_BUILD_DIR)/%.o)

AST_TESTS_OBJECTS := $(BUILD_DIR)/$(TESTS_DIR)/test_ast.o $(filter-out $(BUILD_DIR)/main.o,$(OBJECTS))
IR_TESTS_OBJECTS := $(BUILD_DIR)/$(TESTS_DIR)/test_ir.o $(filter-out $(BUILD_DIR)/main.o,$(OBJECTS))

ANTLR4_BINDIR=/usr/bin
ANTLR4_INCDIR=/usr/include/antlr4-runtime
ANTLR4_LIBDIR=/usr/lib/x86_64-linux-gnu

CC=clang++
CCARGS=-g -std=c++11 -Wno-defaulted-function-deleted -Wno-unknown-warning-option
LDARGS=-g

all: ifcc

ifcc: $(GEN_OBJECTS) $(GEN_HEADERS) $(OBJECTS) $(HEADERS)
	@mkdir -p $(BUILD_DIR) $(GEN_BUILD_DIR)
	$(CC) $(LDARGS) $(OBJECTS) $(GEN_OBJECTS) $(ANTLR4_LIBDIR)/libantlr4-runtime.a -o $(BUILD_DIR)/ifcc

test_ast: $(GEN_OBJECTS) $(GEN_HEADERS) $(AST_TESTS_OBJECTS) $(HEADERS)
	@mkdir -p $(BUILD_DIR) $(GEN_BUILD_DIR) $(BUILD_DIR)/$(TESTS_DIR)
	$(CC) $(LDARGS) $(AST_TESTS_OBJECTS) $(GEN_OBJECTS) $(ANTLR4_LIBDIR)/libantlr4-runtime.a -o $(BUILD_DIR)/test_ast

test_ir: $(GEN_OBJECTS) $(GEN_HEADERS) $(IR_TESTS_OBJECTS) $(HEADERS)
	@mkdir -p $(BUILD_DIR) $(GEN_BUILD_DIR) $(BUILD_DIR)/$(TESTS_DIR)
	$(CC) $(LDARGS) $(IR_TESTS_OBJECTS) $(GEN_OBJECTS) $(ANTLR4_LIBDIR)/libantlr4-runtime.a -o $(BUILD_DIR)/test_ir

$(BUILD_DIR)/$(TESTS_DIR)/%.o: $(TESTS_DIR)/%.cpp
	@mkdir -p $(shell dirname $@)
	$(CC) $(CCARGS) -I $(ANTLR4_INCDIR) -I $(INCLUDE_DIR) -I $(GEN_INCLUDE_DIR) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.cpp
	@mkdir -p $(shell dirname $@)
	$(CC) $(CCARGS) -I $(ANTLR4_INCDIR) -I $(INCLUDE_DIR) -I $(GEN_INCLUDE_DIR) -c $< -o $@

$(GEN_BUILD_DIR)/%.o: $(GEN_SRCS)/%.cpp
	@mkdir -p $(shell dirname $@)
	$(CC) $(CCARGS) -I $(ANTLR4_INCDIR) -I $(INCLUDE_DIR) -I $(GEN_INCLUDE_DIR) -c $< -o $@

$(GEN_SRCS): $(GRAMMAR)
	@mkdir -p /tmp/antlr4-generated
	@$(ANTLR4_BINDIR)/antlr4 -visitor -no-listener -Dlanguage=Cpp -o /tmp/antlr4-generated $(GRAMMAR)
	@mkdir -p $(GEN_SRCS_DIR) $(GEN_INCLUDE_DIR)
	@mv /tmp/antlr4-generated/*.cpp $(GEN_SRCS_DIR)
	@mv /tmp/antlr4-generated/*.h $(GEN_INCLUDE_DIR)
	@rm -rf /tmp/antlr4-generated

test: ifcc test_ast test_ir
	@cd $(TESTS_DIR) && python3 pld-test.py . && exit $?

clean:
	@rm -rf $(BUILD_DIR)
	@rm -rf $(GEN_SRCS_DIR) $(GEN_INCLUDE_DIR)
	@rm -rf $(TESTS_DIR)/pld-test-output

.PHONY: clean