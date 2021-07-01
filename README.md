# CppEarley
Basic C++ Earley Parser, based heavily on the [Earley parser](https://en.wikipedia.org/wiki/Earley_parser) article found on Wikipedia.
This is meant to be a very simplistic implementation of the Earley algorithm and pseudocode found in that article.

## Usage

### Linux

Either `git clone https://github.com/Kingcitaldo125/CppEarley.git` to a directory of your choice, or retrieve the source code from a release of your choice.

To build using CMake:

``` bash
mkdir build
cd build
cmake ..
make
```

To run using the basic Earley grammar found in the Wikipedia article:

``` bash
./main ../grammars/grammar.txt
```

The output from pointing the main target to the basic Earley grammar should be similar to the following:

``` bash
../grammars/grammar.txt
Input <1> = true
Input <1+> = false
Input <1+2> = true
Input <2+3*4> = true
```

### Windows

Coming Soon - Windows is still in `Dev`.

## License

See the [LICENSE](https://github.com/Kingcitaldo125/CppEarley/blob/main/LICENSE) file for details

