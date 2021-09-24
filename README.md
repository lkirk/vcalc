# vcalc

vcalc is an array-oriented, procedural programming language.

## building

```console
mkdir build
cd build
cmake ..
make
```

## dev notes

https://www.oreilly.com/library/view/flex-bison/9780596805418/ch01.html
https://github.com/lkirk/vcfql/blob/master/src/lexer.l
https://github.com/lkirk/vcfql/blob/master/src/parser.y
https://www.gnu.org/software/bison/manual/bison.html#Concepts
https://github.com/simd-everywhere/simde

https://lloydrochester.com/post/flex-bison/json-parse-ast/
https://efxa.org/2014/05/25/how-to-create-an-abstract-syntax-tree-while-parsing-an-input-stream/

https://www.codeproject.com/Articles/874396/Crunching-Numbers-with-AVX-and-AVX
https://www.cs.uaf.edu/courses/cs441/notes/sse-avx/
https://software.intel.com/content/www/us/en/develop/documentation/cpp-compiler-developer-guide-and-reference/top/compiler-reference/intrinsics/details-about-intrinsics.html

https://www.cs.yale.edu/homes/aspnes/pinewiki/C(2f)HashTables.html?highlight=%28CategoryAlgorithmNotes%29
https://benhoyt.com/writings/hash-table-in-c/


## design

Goal: create a small, array-oriented procedural programming language.

This will not your typical array-oriented programming language, littered with meta syntax.
Instead the approach is to create a small, simple programming language that reprensents the feel of numpy.

Language extensions will be written in C

Array operations will be written with simd support, using the simde library.
