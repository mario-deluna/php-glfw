## How to contribute

This project can benefit from all questions, suggestions, help requests, bug reports, crash reports, feature requests you may have. If you have anything to contribute along these lines, please [open a GitHub issue](https://github.com/jpaver/voxeltools/issues/new). 
Issues are the primary mechanism we'll use to communicate existing issues and fixes to those monitoring this library. Be sure to include information about your system, compile toolchain, or your data when seeing problems.

You are always welcome to [open a pull request](https://help.github.com/articles/about-pull-requests/) to submit fixes for open issues, but please expect that feedback and edits on your PRs.

If you wish to contribute new tools, please first discuss the change you wish to make via issue or email with the owners of this repository. Generally though, contributions are welcome provided they are related to the tools in the library, follow the standards and provide demo usage code. 

## Why contribute?

I have benefited enormously from people who have released their code to be used, and I'd like to pay it forward which is the reason I'm releasing this code.

You can be part of that too. This library is useful to me and tested on my toolchain, but it can become more useful to yourself and others with your active help, questions, observations or suggestions. No contribution is too small or unappreciated.

If you use this code in your game projects - please drop me a line and I'll link to them from the projects section of the [README.md](https://github.com/jpaver/opengametools/blob/master/README.md)

## Code of conduct

Provide positive constructive criticism, and provide feedback on ideas and implementation -- NEVER on the person behind them. In short: be helpful and inclusive, stop on topic and don't be a jerk. 

## Code Style philosophy.

The underlying philosophy of the code in this library is to make integration easy. There are a number of implications to this:

1. There no make files in this project:

  You shouldn't need make files if we are succeeding with this philosophy. The simplest way to integrate code should be to #include the implementation once in one of your code modules (ie not in a header!):
  
```c++
#define OGT_VOX_IMPLEMENTATION
#include "opengametools/src/ogt_vox.h"
```

  ...then #include the header/interface where ever you need to use it.
  
```c++
#include "opengametools/src/ogt_vox.h"
```

2. No third party library dependencies in this project:

   This allows these tools to be useful standalone and without fear of cascading dependencies.

3. Coding Standards:

   We aim to maximize compatibility. This means:
   - No use of STL 
   - No RTTI
   - No exceptions
   - No C++11 features (or beyond). 
   
   This is mostly a C99 interface for all APIs / headers and in the implementation mostly C99 with C++ operators and references. This should allow the code to be used in most projects where these features are not available or prohibited eg. in game codebases, legacy or embedded toolchains. 
   (If your codebase required to be C99 only or pre-C99, the code should be fairly simple to port too)
   
4. Code Style

   In terms of code style, use local conventions when touching existing code. If you see something inconsistent, please contribute a fix!
   
   Otherwise, go wild as long as it is readable, follows the standards and is compatible.

## Documentation

Documentation for each tool lives in the source code header eg. `src\ogt_vox.h` with example code in the `demos` folder. eg `demo\demo_vox.cpp`.

You are welcome to make changes to documentation and use issues/pull requests to do so.

