# Compiler Options

If you do not have a copy of the compiler installed on your system, you may need
to build it from scratch. I only develop on Linux, so Windows isn't a priority
for me, though I do attempt to make things as universal as possible. This
project uses the
[Bazel](https://docs.bazel.build/versions/master/bazel-overview.html) C++ build
system, so all code compilation (besides Cookie) goes through it.

Once you do get a working copy of `cookiec`, you can run `cookiec -h` to see
what it has in store for you. This page goes over the contents of that output in
finer detail.

## Input and Output

Because of the nature of this language, only one input file may be specified,
and all dependencies of the input file should be written as such inside the
file. Because the compiler can't function without source code to operate on, the
input file does not require a flag to specify.

On the other hand, the output filename should be specified with a `-o` flag.
However, the output filename has defaults: `a.out.wasm` for WebAssembly modules,
and `a.out.wat` for WebAssembly text files when requested. Because I come from a
Linux background where not everything is required to have an exact format, this
compiler does not complain if you give it a file that does not end in `.cookie`,
or tell it to output a file that does not end with the proper file extension.

These options are the simplest of all, and follow the same syntax as with common
C/C++ compilers like `g++` and `clang`. In addition to these simple features,
however, input and output filenames have special cases.

### Using the Terminal to Write Code

Although this method is not recommended, it is useful for testing. With this,
you can paste code into the compiler to have it compile, and optionally, spit
back out on the terminal. All you need to do to tell the compiler to do this is
pass a *single* dash (`-`) in place of the file you wish to replace, and this
will tell the compiler to interact with the terminal instead of the filesystem.

```bash
cookiec - -o standalone.wasm
> {blueBright import void} {white env}{magentaBright ::}{white print}{yellowBright (}{blueBright str}{yellowBright )}{magentaBright ;}
> 
> {blueBright export i32} {white main}{yellowBright (}{blueBright str}{white [] argv}{yellowBright )} {white \{}
>   {white env}{magentaBright ::}{white print}{yellowBright (}{greenBright "Hello, world!"}{yellowBright )}{magentaBright ;}
>   
>   {blueBright return} {yellowBright 0}{magentaBright ;}
> {white \}}{redBright ^D}
cookie standalone.wasm
> Hello, world!
> 
> [ Exited with code 0 ]
```

> Caret notation is shown in use in the snippet above, and, in this case, it is
> telling the compiler that input is over, because Ctrl-D translates, in ASCII,
> to EOT, or End of Transmission. It's basically an end-of-file for signal for
> the terminal.

> <span class="icon-font" style="vertical-align: sub; color: #ffa41b">warning</span>
> <span style="color: #ffa41b;">**CAUTION**</span>
> <span class="icon-font" style="vertical-align: sub; color: #ffa41b">warning</span>
> 
> Be careful when sending compiler output to the terminal, because, if you are
> not redirecting `stdout` output and you fail to tell the compiler to output
> WebAssembly text code, you can mess up your terminal with all sorts of random
> characters spewing on to the terminal. Don't believe me? Look up ANSI escape
> codes.

## Controlling the Output

There are two different kinds of output that the compiler can give. It can
output a binary WebAssembly module (default behavior), or can be told to output
the text representation of the code in the module. This action is called (or at
least I'm calling it) a compiler stage cutoff, where the compiler stops
processing the code at a certain point to give the output to the user. In this
case, it stops the compiler just before the last stage, the Assembler, which
takes a list of instructions and builds the binary module that you see normally.

This behavior can be triggered by passing the `-s` flag to the compiler. For
example, if the compiler is invoked with a simple program that just exits with
code 42, this is what the text format would show (assuming you haven't told the
compiler to strip all debug symbols out).

```wasm | compiler-out.wat
(module
  (type 0 (func (param i32 i32)))
  (type 1 (func (param i32) (result i32)))
  (type 2 (func (param i32)))
  (memory (export ".MEMORY") 2)
  (global (export ".INIT_VEC") i32 (i32.const 0))
  (func $.INIT_HEAP (export ".INIT_HEAP") (type 0) (param i32 i32)
    (; ... ;))
  (func $.malloc (export ".malloc") (type 1) (param i32) (result i32)
    (; Lots and lots of super-optimized memory management code ;))
  (func $.free (export ".free") (type 2) (param i32)
    (; More memory management code written by hand ;))
/*!*/  (func $F4mainPSA (export "F4mainPSA") (type 1) (param $argv i32) (result i32)
/*!*/    i32.const 42))
```

Of course optimizing the output to the maximum could see that this program never
uses the heap and therefore not include some of that code, but this is just a
basic look at what the compiler supports. In general, by the way, the heap is
used for storing objects. These objects are then deleted when they fall out of
scope, just like a garbage collector, although actually allocating memory on the
heap for your own use does not behave like this.

## Code Optimization

While the compiler can't fix your bugs for you, it can at least make them appear
faster than before, by optimizing the output code. The compiler has two stages
of optimization available for use depending on what you have set the
optimization level. This level can be one of four numbers between zero and three
inclusive, and may be specified with `-On` where `n` is the level of
optimization. The default level is 1.

Because there are two stages of optimization, and four numbers, this parameter
sort of acts like a set of two binary flags, where the least significant bit
determines whether or not the instructions will get optimized, and the most
significant bit will determine if the AST gets optimized. Optimization is very
mundane, yet so useful that you have already seen it alter the output. From the
code snippet above, there would be an additional `return` instruction after the
`i32.const` instruction if `-O0` or `-O2` were being used. However, because we
did not specify a level of optimization, and the default is level 1, the
compiler optimized the instruction list and came up with that code as the
result.

## Verbosity

If you of the curious type, and want to know what is happening when the compiler
is building your WebAssembly module for you, you can specify `-v` or `--verbose`
to have it do just that. Because a compiler is a very complicated system, there
are multiple levels of verbosity. These levels are as such:

1. Output some basic information about the intermediate data structures, such as
   the number of tokens being read, or the level of optimization that was
   accomplished during optimization.
2. Output **everything**. This means printing out a list of all of the tokens
   encountered, printing out the full abstract syntax tree, and all of the
   instructions that are generated from this. The optimization stages will still
   only print what it has optimized and by how much.
3. Same as level 2, however the optimization stages also get the chance to be
   particularly noisy here, because they will print every optimization chance
   they find to the terminal.

The default verbosity level is 0, or brief mode, in which no additional
information about the compilation process will be printed. If there is no level
specified, the level will be set to 1.

> It is worth mentioning, by the way, that this verbose output will be put on
> the `stderr` stream, and therefore not collide with output of code to `stdout`
> if it is what the compiler is being told what to do.

Verbosity may also be turned off, or set to level zero, explicitly, by passing
the `--brief` argument after any mentions of `--verbose` on the command line.

## Warnings

By default, the compiler will print out warnings for every issue it finds. These
warnings mean nothing to the success of the compilation. To mute certain types
of warnings, you may pass `-W`, followed by the type of warning specified when
you get one. If you want to specify that certain warnings should be treated as
errors, just do the same thing, but with `-E`. In addition to this, the wildcard
`all` can be used to refer to all warnings.

> [info](:Icon) **Notice**
> 
> It is generally considered a bad idea to pass `-Wall` to the compiler, as this
> will mute all warning and completely thwart any chance you have of debugging
> a small bug.

For example, if you want to compile code for a Continuous Integration test, just
invoke the compiler with something like this:

```bash
cookiec lib/main.cookie -o test/lib.wasm -Eall -v2
> ... Endless compiler output ...
```

> :ToCPrevNext

