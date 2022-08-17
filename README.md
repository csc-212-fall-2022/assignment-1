# Assignment 1: Getting Started

The purpose of this assignment is to make sure that you have a development environment set up and
have basic familiarity with working with git.

## Environment Setup

You are welcome to use whatever tools you want, though I recommend getting comfortable with some form of \*nix command line, be that Mac OS, Linux or WSL.

Make sure you have the following installed:
- A compiler that supports C++17 (just about everything)
- git
- clang-format
- clang-tidy
- cmake
- make

## Getting the Assignment

The assignment is set up as a "template" in Github. If you want to keep your homework on Github, click the "Use this template" button,
create a repository and then clone it as below, but swap in the URL of your repo.

If you don't want to use Github, in the terminal, go to the directory where you want to work and clone the assignment:
```
git clone https://github.com/csc-212-fall-2022/assignment-1.git
```

See "The Basics of GitHub" below for more information on git and Github.

## A Tour of the Assignment

The basic pattern for using `cmake` is to create a `build` directory:
```
mkdir build
```
Then, we change to the `build` directory and run `cmake ..` (the `..` points `cmake` to a project in the parent directory, i.e. the main assignment directory, where our `CMakeLists.txt` is.)
Unfortunately, we get an error!
```
 csar@sebastian : ~/Documents/teaching/fall22/csc212-assignment1/build : cmake ..
-- The C compiler identification is GNU 12.1.0
-- The CXX compiler identification is GNU 12.1.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Excluding/home/csar/Documents/teaching/fall22/csc212-assignment1/build/CMakeFiles/3.23.2/CompilerIdCXX/CMakeCXXCompilerId.cpp
-- Excluding/home/csar/Documents/teaching/fall22/csc212-assignment1/external/doctest/doctest.h
-- Configuring done
CMake Error at CMakeLists.txt:19 (add_library):
  Cannot find source file:

    assignment1/MergeSort.cpp

  Tried extensions .c .C .c++ .cc .cpp .cxx .cu .mpp .m .M .mm .ixx .cppm .h
  .hh .h++ .hm .hpp .hxx .in .txx .f .F .for .f77 .f90 .f95 .f03 .hip .ispc


CMake Error at CMakeLists.txt:20 (add_library):
  Cannot find source file:

    assignment1/BinarySearch.cpp

  Tried extensions .c .C .c++ .cc .cpp .cxx .cu .mpp .m .M .mm .ixx .cppm .h
  .hh .h++ .hm .hpp .hxx .in .txx .f .F .for .f77 .f90 .f95 .f03 .hip .ispc


CMake Error at CMakeLists.txt:19 (add_library):
  No SOURCES given to target: MergeSort


CMake Error at CMakeLists.txt:20 (add_library):
  No SOURCES given to target: BinarySearch


CMake Generate step failed.  Build files cannot be regenerated correctly.
```

What happened? The output says we're missing `assingment1/MergeSort.cpp` and `assignment1/BinarySearch.cpp`.
If we take a look at `CMakeLists.txt`, we can see that there are two library "targets" declared:
```cmake
add_library(MergeSort assignment1/MergeSort.hpp assignment1/MergeSort.cpp)
add_library(BinarySearch assignment1/BinarySearch.cpp assignment1/BinarySearch.hpp)
```
Each looks for the appropriate `*.hpp` and `*.cpp` files. If I look at the contents of the `assignment1` directory,
I see the `*.cpp` files are missing. This is the output of `tree assignment1`. There are some `*.cpp` files, but they have `test` in the name.
(If you look at `CMakeLists.txt` again, you'll notice that they get used to define test targets.)
```bash
assignment1
├── BinarySearch.hpp
├── BinarySearch.test.cpp
├── MergeSort.hpp
└── MergeSort.test.cpp
```

In future assignments, I'll do my best to remember to create the `.cpp` files in the template too. I left them out
to give you a tour of `CMakeLists.txt`.

### Getting the Build Working

Now that we saw why `cmake` failed, we need to fix it. Let's just create the missing files:
```bash
touch assignment1/MergeSort.cpp
touch assignment1/BinarySearch.cpp
```
Change back to your `build` directory and run `cmake ..` again. This time, it should succeed.

What have we done so far? Surely our project shouldn't compiled, we haven't actually implemented anything.
`cmake` hasn't actually compiled anything, it's generated a Makefiles in the `build` directory (and some additional Makefiles in the subdirectories of `build`).
CMake supports a number of different [generators](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html), but
make is the default. You can try to compile the project by running `cmake --build .`. Unsurprisingly, this will fail,
since we didn't write any code in those `cpp` files.

Why are we bothering with CMake? It's true, in this class, we're probably not going to have any projects so large
that we couldn't just compile manually. However, it's good to get familiar with some standard tools of the C++ world.
It also means that we can easily run tests and tools like `clang-tidy` and `clang-format`.

### The Coding Part

For this assigment, you need to implement the two functions described in `MergeSort.hpp` and `BinarySearch.hpp`:

```c++
std::vector<int> MergeSort(const std::vector<int> &);

int BinarySearch(const std::vector<int> &, int);
```

When you're ready, build everything with `cmake --build .`. You should see output that looks like:
```
Consolidate compiler generated dependencies of target MergeSort
[ 12%] Building CXX object CMakeFiles/MergeSort.dir/assignment1/MergeSort.cpp.o
[ 25%] Linking CXX static library libMergeSort.a
[ 25%] Built target MergeSort
Consolidate compiler generated dependencies of target BinarySearch
[ 37%] Building CXX object CMakeFiles/BinarySearch.dir/assignment1/BinarySearch.cpp.o
[ 50%] Linking CXX static library libBinarySearch.a
[ 50%] Built target BinarySearch
Consolidate compiler generated dependencies of target MergeSortTests
[ 62%] Building CXX object CMakeFiles/MergeSortTests.dir/assignment1/MergeSort.test.cpp.o
[ 75%] Linking CXX executable MergeSortTests
[ 75%] Built target MergeSortTests
[ 87%] Building CXX object CMakeFiles/BinarySearchTests.dir/assignment1/BinarySearch.test.cpp.o
[100%] Linking CXX executable BinarySearchTests
[100%] Built target BinarySearchTests
```

If you're working on (say) the MergeSort function and haven't touched BinarySearch yet, you can build only the MergeSort target
by running `cmake --build . --target MergeSort`.

### Run the tests

Since we built all the targets above, we built the two test binaries. We could run them individually (e.g. `./MergeSortTests`),
but we can also run them all with CTest. Below is the verbose CTest output (from `ctest -V`).
```

UpdateCTestConfiguration  from :/home/csar/Documents/teaching/fall22/csc212-assignment1/build/DartConfiguration.tcl
UpdateCTestConfiguration  from :/home/csar/Documents/teaching/fall22/csc212-assignment1/build/DartConfiguration.tcl
Test project /home/csar/Documents/teaching/fall22/csc212-assignment1/build
Constructing a list of tests
Done constructing a list of tests
Updating test list for fixtures
Added 0 tests to meet fixture requirements
Checking test dependency graph...
Checking test dependency graph end
test 1
    Start 1: MergeSortTests

1: Test command: /home/csar/Documents/teaching/fall22/csc212-assignment1/build/MergeSortTests
1: Test timeout computed to be: 10000000
1: [doctest] doctest version is "2.4.9"
1: [doctest] run with "--help" for options
1: ===============================================================================
1: [doctest] test cases: 1 | 1 passed | 0 failed | 0 skipped
1: [doctest] assertions: 2 | 2 passed | 0 failed |
1: [doctest] Status: SUCCESS!
1/2 Test #1: MergeSortTests ...................   Passed    0.01 sec
test 2
    Start 2: BinarySearchTests

2: Test command: /home/csar/Documents/teaching/fall22/csc212-assignment1/build/BinarySearchTests
2: Test timeout computed to be: 10000000
2: [doctest] doctest version is "2.4.9"
2: [doctest] run with "--help" for options
2: ===============================================================================
2: [doctest] test cases: 1 | 1 passed | 0 failed | 0 skipped
2: [doctest] assertions: 4 | 4 passed | 0 failed |
2: [doctest] Status: SUCCESS!
2/2 Test #2: BinarySearchTests ................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 2

Total Test time (real) =   0.02 sec
```

### Code Quality, Memory Leaks and the Like

## 📚  Resources 
* [A short video explaining what GitHub is](https://www.youtube.com/watch?v=w3jLJU7DT5E&feature=youtu.be) 
* [Git and GitHub learning resources](https://docs.github.com/en/github/getting-started-with-github/git-and-github-learning-resources) 
* [Understanding the GitHub flow](https://guides.github.com/introduction/flow/)
* [How to use GitHub branches](https://www.youtube.com/watch?v=H5GJfcp3p4Q&feature=youtu.be)
* [Interactive Git training materials](https://githubtraining.github.io/training-manual/#/01_getting_ready_for_class)
* [GitHub's Learning Lab](https://lab.github.com/)
* [Education community forum](https://education.github.community/)
* [GitHub community forum](https://github.community/)
