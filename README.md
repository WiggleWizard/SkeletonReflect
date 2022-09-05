# SkeletonReflect
**NOTE: SkeletonReflect is still WIP software**

SkeletonReflect is a highly programmable reflection tool for C++ codebases. It utilizes "decorators" and employs a rudimentary C++ header parser in order to generate headers and sources for reflection data to be available to programmers at runtime.

# Objectives & Intentions
SkeletonReflect's main objective is to provide flexible reflection tooling and systems for C++ codebases to integrate directly into their existing build pipeline. Beyond this main objective, SkeletonReflect aims to provide the following features:
- Sane defaults for generating reflection code (in this case, very UE4-like).
- Solid, reliable C++ header parsing.
- Scriptable pipeline programming.
- Ability to write in your favorite scripting language with integrated Scripting Engines.

As part of being a tool to use during build time, SkeletonReflect aims to also provide a minimal API for accessing reflected classes, properties and functions.

The aim is to also make all of these programmable via any number of scripting languages.

## Intended default usage summary
**NOTE: This is the final desired default usage, the software is still WIP**

You write your header files like normal, except you you "decorators" in the form of C macros to direct generated output code:
```cpp
#include "MyBoringClass.generated.h"

SKCLASS(DisplayName = "MyAwesomeClass")
class MyBoringClass : public Object
{
    SK_GENERATED_BODY()

public:
    SKFUNCTION(ScriptCallable, AutoBind)
    void Foo();

    SKPROPERTY(Replicated, CustomMeta = { ShowInDebug = true })
    int myCustomPropertyl = 0;
};
```

You invoke the tool during your pre-build step with a command:
```shell
srg --inputdir include --outputdir intermediate/debug/Win64/generated
```

Adjust your CMake scripts:
```cmake
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${SKR_SOURCES})
include_directories(${PROJECT_NAME} ${SKR_INCLUDE_DIR})
```

Magic occurs, and you have reflection with the ability to query classes, class names, list properties and functions on classes, etc.

# Tasks
- [ ] Finish core features.
    - [x] Wren script engine basics.
    - [x] Scanning lexer.
    - [x] Script engine access for custom keywords.
    - [ ] Code generation.
    - [ ] Script engine access for code generation.
- [ ] Documentation.
- [ ] DLL supported scripting engine.
- [ ] LUA scripting engine.
