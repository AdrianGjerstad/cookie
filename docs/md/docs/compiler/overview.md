# Overview

Writing a compiler is very tough, and generally not worth it, as I have learned
in my attempts to write other projects like compilers in the past. However, I
have a real reason for doing it this time, and that is that I both want the
experience, however painful, and want a language that I know exactly what I'm
doing in.

## Syntax

To start, I want the syntax of this language to resemble that of a combination
of C, Rust, Python, and Javascript. I need it to be clear what is happening at
all points in my code so that somebody coming from a background of only a year
or so of Python can understand what is happening without much documentation.
Lastly, I need to make it obvious that this language was built for compilation
to WebAssembly, that is, support things like importing and exporting different
symbols (functions, variables, etc.)

It would also be nice to support splitting code up into packages that I'll call
Crumbs for now, and being able to write code that uses those crumbs without
having to specify an exact file name that may or may not give complete context
as to what's going on. This mechanic works sort of like in Rust, with `use`
statements (though I may not call it that).

In addition to all of these features, I want object-oriented programming to
become somewhat of a normal occurence in this language. Because WebAssembly does
not natively support this, I will also probably have to implement some kind of
name mangling system for referencing functions instead of classes, and
vice-versa.

> :ToCPrevNext

