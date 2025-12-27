# C++ Examples of Copy Semantics, Move Semantics, and Perfect Forwarding

## Description
This repository contains practical examples demonstrating key C++11 and later features: **copy semantics, move semantics, and perfect forwarding**. These examples help illustrate the differences between copy and move operations, resource management in classes, and how perfect forwarding preserves argument value categories.

The project includes three main demonstrations:
- `copyable_array.cpp`: Shows proper implementation of copy semantics (copy constructor and copy assignment operator) for a dynamic array class, emphasizing deep copying of resources.
- `movable_array.cpp`: Demonstrates move semantics (move constructor and move assignment operator) to optimize resource transfers between objects, avoiding unnecessary copying.
- `perfect_forwarding.cpp`: Illustrates how to preserve lvalue/rvalue characteristics when passing arguments through function wrappers, enabling more flexible and efficient code.

In addition, Japanese cultural memes associated with these core concepts are provided as supplementary materials at the bottom of this README file, aiming to facilitate a more intuitive comprehension for both Japanese anime fans and beginners in C++ and programming.

## Understanding Value Categories
In C++, every expression has a **value category**, which determines how it can be used in expressions and which operations are allowed on it. These categories are critical for understanding copy semantics, move semantics, and perfect forwarding. The primary value categories are:

### Lvalues (Left Values)
- **Definition**: Expressions that refer to a memory location and can appear on the left side of an assignment (`=`). They represent "objects with identity" (i.e., you can take their address with `&`).
- **Examples**:
  - Variables (e.g., `int x = 5; x` is an lvalue)
  - Functions or data members accessed via `.` or `->` (e.g., `obj.member`, `ptr->data`)
  - String literals (e.g., `"hello"` is an lvalue of type `const char[]`)
- **Behavior**: When passed to a function, lvalues bind to lvalue references (`T&`).

### Rvalues (Right Values)
Temporary expressions that do not have a persistent memory location and cannot appear on the left side of an assignment. They represent "values without identity." Rvalues are further divided into:

#### Prvalues ("Pure" Rvalues)
- **Definition**: Literals or temporary objects created during expression evaluation.
- **Examples**:
  - Numeric literals (e.g., `42`, `3.14`)
  - Return values of functions that return by value (e.g., `int add(int a, int b) { return a + b; }`; the result of `add(2, 3)` is a prvalue)
  - Temporary objects (e.g., `std::string("temporary")`)
- **Behavior**: Bind to rvalue references (`T&&`) or `const` lvalue references (`const T&`).

#### Xvalues ("eXpiring" Values)
- **Definition**: Rvalues that refer to objects whose resources can be "stolen" (typically because they are no longer needed). They are often the result of casting an lvalue to an rvalue reference.
- **Examples**:
  - Results of `std::move(x)` (casts an lvalue `x` to an xvalue)
  - Return values of functions that return an rvalue reference (e.g., `T&& func() { ... }`)
- **Behavior**: Like prvalues, they bind to rvalue references (`T&&`), enabling move operations to transfer their resources.

### Key Relationship to Semantics
- **Copy Semantics**: Operates on lvalues, where resources are duplicated (e.g., copying an lvalue into a new object).
- **Move Semantics**: Operates on rvalues (xvalues and prvalues), where resources are transferred from the source object (which is no longer needed) to the destination, avoiding duplication.
- **Perfect Forwarding**: Preserves the original value category (lvalue/rvalue) of an argument when passing it through functions, ensuring the correct overload (copy or move) is selected.

## Installation & Usage
``` bash
git clone https://github.com/Pac-Dessert1436/cpp-copy-move-forwarding
cd cpp-copy-move-forwarding
```
- **For Windows System**:
  - Install MSYS2 (for GCC compiler) or Visual Studio with C++ support
  - Run all programs using `run_all_programs.bat` (double-click or execute from command prompt)
- **For Linux System**:
  - Ensure GCC compiler is installed (typically pre-installed; if not, install with `sudo apt install g++` on Debian/Ubuntu or `sudo dnf install gcc-c++` on Fedora)
  - Make the script executable: `chmod +x run_all_programs.sh` (create this script with contents below)
  - Run all programs: `./run_all_programs.sh`

*Linux `run_all_programs.sh` content:*
```bash
#!/bin/bash
g++ copyable_array.cpp -o copyable_array -std=c++11
g++ movable_array.cpp -o movable_array -std=c++11
g++ perfect_forwarding.cpp -o perfect_forwarding -std=c++11
echo "Running CopyableArray Demo..."
./copyable_array
echo
echo "Running MovableArray Demo..."
./movable_array
echo
echo "Running Perfect Forwarding Demo..."
./perfect_forwarding
echo
echo "All programs executed."
```

## Japanese Memes for These Semantics
### Copy Semantics
- 「コピー許可：資産を複製せよ・代償は性能だ！」
  - **Meme Translation**: Copying permitted: Duplicate the assets, but performance is the price!
  - **Technical Note**: Copy semantics duplicates all resources of an object, which incurs performance overhead.

### Move Semantics
- 「コピー禁止：複製はダメ・奪うのが忍者！」
  - **Meme Translation**: Copying prohibited: Replication is forbidden; seizing is the ninja way!
  - **Technical Note**: Move semantics "seizes" resources from the source object instead of copying, avoiding performance cost.

### Perfect Forwarding
- 「std::forward：真実の型を映す鏡・偽りなき転送！」
  - **Meme Translation**: `std::forward`: A mirror that reflects the true type; forwarding without deceit!
  - **Technical Note**: `std::forward` preserves the original value category (lvalue/rvalue) of arguments for perfect forwarding.

## License
This project is licensed under the MIT license. See the [LICENSE](LICENSE) file for details.