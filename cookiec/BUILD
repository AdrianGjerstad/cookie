# cookiec WebAssembly compiler
package(
  default_visibility = [ "//visibility:public" ]
)

# cookiec [OPTIONS] FILE
# 
# Build WebAssembly binaries from Cookie source code files. Build using the
# following command:
# 
#   bazel build //cookiec:cookiec
# 
# And then run `cookiec --help' for help with the compiler.
cc_binary(
  name = "cookiec",
  srcs = [ "src/main.cc" ],
  deps = [
    ":CommandLineInterface",
    ":CommandLineArguments",
    ":SourceCodePool",
    ":Filesystem",
    ":Token",
    ":Lexer",
    ":Parser",
    ":ParserResult",
    ":AbstractSyntaxTree"
  ]
)

################################################################################
######################### COMMAND LINE INTERFACE (CLI) #########################
################################################################################

# CommandLineInterface is the brains behind the CLI operation, iterating over
# the command line arguments and producing output, such as the names of files to
# be working with, optimization levels, warning settings, and more.
cc_library(
  name = "CommandLineInterface",
  srcs = [ "src/impl/cli/CommandLineInterface.cc" ],
  hdrs = [ "src/include/cli/CommandLineInterface.h" ],
  deps = [
    ":CommandLineArguments"
  ]
)

# CommandLineArguments is a simple data struct containing all of the information
# ingested by CommandLineInterface so that cookiec can do exactly what it is
# told to do.
cc_library(
  name = "CommandLineArguments",
  hdrs = [ "src/include/structs/CommandLineArguments.h" ]
)

################################################################################
################### UTILITIES AND INTERNAL LIBRARIES (UTIL) ####################
################################################################################

# Filesystem is a collection of functions inside cookie::fs that allow for
# various operations on the filesystem, like iterating over every character in
# a file or manipulating path strings.  This utility also defines the class
# cookie::fs::Path for easier work with paths.
# 
# Why not use std::filesystem? Because that means explicitly specifying the use
# of <filesystem>, which I neither know how to do nor want to do using Bazel.
cc_library(
  name = "Filesystem",
  srcs = [ "src/impl/util/Filesystem.cc" ],
  hdrs = [ "src/include/util/Filesystem.h" ]
)

# SourceCodePool is a class that supports carrying a pool of raw source code for
# every file used in the compilation process.  The necessity of this class comes
# in because of the fact that storing a copy of the entire contents of a source
# code file twice over in every single token lexed into existance is not memory-
# efficient.  This class not only allows you to add files to the pool just by
# mention of their filenames, but also get constant pointers to the underlying
# string that are stored on the heap for any part of the program to access.
cc_library(
  name = "SourceCodePool",
  srcs = [ "src/impl/util/SourceCodePool.cc" ],
  hdrs = [ "src/include/util/SourceCodePool.h" ],
  deps = [
    ":Filesystem"
  ]
)

# Position is just a simple class that can traverse over an entry from a
# SourceCodePool and store line and column information for all of those errors
# it will need to print once it realizes just how bad your code is.
cc_library(
  name = "Position",
  srcs = [ "src/impl/util/Position.cc" ],
  hdrs = [ "src/include/util/Position.h" ],
  deps = [
    ":SourceCodePool"
  ]
)

################################################################################
#################################### ERRORS ####################################
################################################################################

# Error is the base class of all cookie compiler error types. It implements a
# constructor taking in a start position, end position, and message. It also
# implements a simple to_string method that formats the contents of the error
# object into the format you see in the compiler's output
cc_library(
  name = "Error",
  srcs = [ "src/impl/errors/Error.cc" ],
  hdrs = [ "src/include/errors/Error.h" ],
  deps = [
    ":Position"
  ]
)

# IllegalCharacterError is a derived class of Error that represents the lexer's
# inability to interpret your garbled mess of code.
cc_library(
  name = "IllegalCharacterError",
  srcs = [ "src/impl/errors/IllegalCharacterError.cc" ],
  hdrs = [ "src/include/errors/IllegalCharacterError.h" ],
  deps = [
    ":Error",
    ":Position"
  ]
)

# CommentError is a derived class of Error that represents a special error case
# when the lexer is still waiting for a block comment to be closed when it hits
# the end of lexing the file.
cc_library(
  name = "CommentError",
  srcs = [ "src/impl/errors/CommentError.cc" ],
  hdrs = [ "src/include/errors/CommentError.h" ],
  deps = [
    ":Error",
    ":Position"
  ]
)

# SyntaxError is a derived class of Error that represents errors encountered
# during parsing.
cc_library(
  name = "SyntaxError",
  srcs = [ "src/impl/errors/SyntaxError.cc" ],
  hdrs = [ "src/include/errors/SyntaxError.h" ],
  deps = [
    ":Error",
    ":Position"
  ]
)

################################################################################
################################### WARNINGS ###################################
################################################################################



################################################################################
#################################### LEXER #####################################
################################################################################

# Tokens are an essential part of the compiler, because they are the building
# blocks of what is to come. They are the output type of the Lexer, and so they
# are defined here.
cc_library(
  name = "Token",
  srcs = [ "src/impl/lexer/Token.cc" ],
  hdrs = [ "src/include/lexer/Token.h" ],
  deps = [
    ":TokenType",
    ":Position"
  ]
)

# Continuation of Token: Token types are what differentiate a number from a
# keyword, and, as you may imagine, are very important.
cc_library(
  name = "TokenType",
  srcs = [ "src/impl/lexer/TokenType.cc" ],
  hdrs = [ "src/include/lexer/TokenType.h" ]
)

# LexerResult is pretty self-explanatory. It's a data struct containing a list
# of errors and tokens produced as an output by cookie::Lexer::lex.
cc_library(
  name = "LexerResult",
  hdrs = [ "src/include/structs/LexerResult.h" ],
  deps = [
    ":Token",
    ":Error"
  ]
)

# Lexer is the first stage in compilation. Its job is to take in the raw source
# code as a string (allocated on the heap), and convert it to bite-sized pieces
# called tokens, which are what the Token and TokenType targets above are for.
cc_library(
  name = "Lexer",
  srcs = [ "src/impl/lexer/Lexer.cc" ],
  hdrs = [ "src/include/lexer/Lexer.h" ],
  deps = [
    ":Token",
    ":TokenType",
    ":Position",
    ":SourceCodePool",
    ":LexerResult",
    ":IllegalCharacterError",
    ":CommentError"
  ]
)

################################################################################
#################################### PARSER ####################################
################################################################################

# Node is the base class of all AST nodes.
cc_library(
  name = "Node",
  srcs = [ "src/impl/ast/Node.cc" ],
  hdrs = [ "src/include/ast/Node.h" ]
)

# BinaryOperationNode encompasses every operation that takes two operands and
# produces one result.
cc_library(
  name = "BinaryOperationNode",
  srcs = [ "src/impl/ast/BinaryOperationNode.cc" ],
  hdrs = [ "src/include/ast/BinaryOperationNode.h" ],
  deps = [
    ":Node",
    ":Token"
  ]
)

# UnaryOperationNode is the same as BinaryOperationNode, only, there is only one
# operand to operate on.
cc_library(
  name = "UnaryOperationNode",
  srcs = [ "src/impl/ast/UnaryOperationNode.cc" ],
  hdrs = [ "src/include/ast/UnaryOperationNode.h" ],
  deps = [
    ":Node",
    ":Token"
  ]
)

# LiteralNode stores a single token corresponding to some form of literal,
# wether that is a number, or string.
cc_library(
  name = "LiteralNode",
  srcs = [ "src/impl/ast/LiteralNode.cc" ],
  hdrs = [ "src/include/ast/LiteralNode.h" ],
  deps = [
    ":Node",
    ":Token"
  ]
)

# CodeBodyNode stores a list of statements to be put into a signle body of code.
# This could be a function body, loop body, conditional body, etc.
cc_library(
  name = "CodeBodyNode",
  srcs = [ "src/impl/ast/CodeBodyNode.cc" ],
  hdrs = [ "src/include/ast/CodeBodyNode.h" ],
  deps = [
    ":Node",
    ":Token"
  ]
)

# NoOperationNode stores and does absolutely nothing. It represents a statement
# with nothing in it; a nop.
cc_library(
  name = "NoOperationNode",
  srcs = [ "src/impl/ast/NoOperationNode.cc" ],
  hdrs = [ "src/include/ast/NoOperationNode.h" ],
  deps = [
    ":Node",
    ":Token"
  ]
)

# FunctionNode stores a function return type, name, ArgumentListNode, and
# CodeBodyNode.
cc_library(
  name = "FunctionNode",
  srcs = [ "src/impl/ast/FunctionNode.cc" ],
  hdrs = [ "src/include/ast/FunctionNode.h" ],
  deps = [
    ":Node",
    ":Token"
  ]
)

# ArgumentListNode stores a list of data type-argument name pairs for functions.
# This node DOES NOT represent calling a method, only defining it.
cc_library(
  name = "ArgumentListNode",
  srcs = [ "src/impl/ast/ArgumentListNode.cc" ],
  hdrs = [ "src/include/ast/ArgumentListNode.h" ],
  deps = [
    ":Node",
    ":Token"
  ]
)

# ParserResult represents a simple lightweight struct for storing errors and, on
# success, a node.
cc_library(
  name = "ParserResult",
  srcs = [ "src/impl/structs/ParserResult.cc" ],
  hdrs = [ "src/include/structs/ParserResult.h" ],
  deps = [
    ":Node",
    ":Error"
  ]
)

# AbstractSyntaxTree is a special derived class of Node that stores an index of
# all functions, global variables, etc. It is intended to be the highest node in
# the entire AST.
cc_library(
  name = "AbstractSyntaxTree",
  srcs = [ "src/impl/ast/AbstractSyntaxTree.cc" ],
  hdrs = [ "src/include/ast/AbstractSyntaxTree.h" ],
  deps = [
    ":Node",
    ":Token"
  ]
)

# SymbolReferenceNode is a node type designated for referencing local,
# parameter, and global variables.
cc_library(
  name = "SymbolReferenceNode",
  srcs = [ "src/impl/ast/SymbolReferenceNode.cc" ],
  hdrs = [ "src/include/ast/SymbolReferenceNode.h" ],
  deps = [
    ":Node",
    ":Token"
  ]
)

# SymbolDefinitionNode represents the action of defining or setting the value of
# a local, parameter, or global variable.
cc_library(
  name = "SymbolDefinitionNode",
  srcs = [ "src/impl/ast/SymbolDefinitionNode.cc" ],
  hdrs = [ "src/include/ast/SymbolDefinitionNode.h" ],
  deps = [
    ":Node",
    ":Token"
  ]
)

# ReturnNode represents the literal "return ..." statement.
cc_library(
  name = "ReturnNode",
  srcs = [ "src/impl/ast/ReturnNode.cc" ],
  hdrs = [ "src/include/ast/ReturnNode.h" ],
  deps = [
    ":Node",
    ":Token"
  ]
)

# GlobalDefinitionNode represents the definition of a global symbol. Duh.
cc_library(
  name = "GlobalDefinitionNode",
  srcs = [ "src/impl/ast/GlobalDefinitionNode.cc" ],
  hdrs = [ "src/include/ast/GlobalDefinitionNode.h" ],
  deps = [
    ":Node",
    ":Token"
  ]
)

# The Parser takes in a list of tokens generated by the lexer. Its job is to
# create an Abstract Syntax Tree of nodes representing the code that was written
# in a hierarchical format.
cc_library(
  name = "Parser",
  srcs = [ "src/impl/parser/Parser.cc" ],
  hdrs = [ "src/include/parser/Parser.h" ],
  deps = [
    ":Node",
    ":Token",
    ":AbstractSyntaxTree",
    ":BinaryOperationNode",
    ":UnaryOperationNode",
    ":LiteralNode",
    ":CodeBodyNode",
    ":NoOperationNode",
    ":FunctionNode",
    ":ArgumentListNode",
    ":SymbolReferenceNode",
    ":SymbolDefinitionNode",
    ":ReturnNode",
    ":GlobalDefinitionNode",
    ":ParserResult",
    ":SyntaxError"
  ]
)

