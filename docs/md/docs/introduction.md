# Introduction

Introducing a project which I have only ambitions so far for is kind of
difficult, although I have written a proof of concept in JavaScript. Here we go
anyway.

## Examples

Just to give you an idea of what you might be able to do with this project, I
have written a standalone and module-like set of examples here.

Note that these examples currently do not work. There is no utility called
`cookiec` or `cookie` available for installation yet or a `cookie-lang` npm
package ready for download. It is currently being worked on
[here](https://github.com/AdrianGjerstad/cookie), so if you want come and
contribute to speed along the process of writing a full blown compiler in C++,
along with all of the utilities shown in action here.

The rest of this documentation is written like they already exist.

### Standalone Application

This is an example application written in Cookie that prints the command line
arguments it is given.

``` cookie | standalone.cookie | --safe-highlight
import void sys::print(const str);

export i32 main(str[] argv) {
  for(str arg : argv) {
    sys::print(arg);
  }

  return 0;
}
```

``` bash
cookiec standalone.cookie -o standalone.wasm
cookie standalone.wasm "these are" "command arguments"
> standalone.wasm
> these are
> command arguments
> 
> [ Exited with code 0 ]
```

### Module Application

This is an example application written in Cookie that gives JavaScript some
basic math functions

``` cookie | math.cookie | --safe-highlight
export f64 square(f64 x) {
  return x * x;
}

export f64 add42(f64 x) {
  return x + 42;
}

export f64 sum(f64[] values) {
  f64 result = 0;
  
  for(f64 x : values) {
    result += x;
  }

  return result;
}

export f64 PI = 3.141592653589793;  // Approximately...
```

``` javascript | math.js
const Cookie = require('cookie-lang');

async function main() {
  let math = await Cookie.load('math.wasm');

  console.log('Pi is approximately ' + math.PI);
  console.log('Adding 42 to pi gives you ' + math.add42(math.PI);
  console.log('The square of pi is approximately ' + math.square(math.PI));
}

main();
```

```bash
cookiec math.cookie -o math.wasm
node math.js
> Pi is approximately 3.141592653589793
> Adding 42 to pi gives you 45.1415926535898
> The square of pi is approximately 9.869604401089358
```

## Why do we need another language?

Being entirely honest, this project is more being done just for the experience.
I have never written a complete compiler before, and would love to dive in deep
with what WebAssembly has to offer in its capabilities.

On the other hand, though, I have always been just a little bit disappointed in
the small number of tools available for WebAssembly development. Yes, Emscripten
exists, and so do online exploration tools like
[WebAssembly Studio](https://webassembly.studio), but there is nothing that was
designed from scratch to compile to WebAssembly. I was also a bit tired of
dealing with complicated features of C like c-style strings and lack of memory
management. That is where the idea of dedicated and builtin `str` objects and
array (`type[]`) modifiers came from.

But to answer this question directly: not necessarily. If you don't feel like
supporting it, then don't. I am just a developer with something I want to fix.

> :ToCPrevNext

