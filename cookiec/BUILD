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
    ":Filesystem"
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
################################### LEXER ######################################
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

