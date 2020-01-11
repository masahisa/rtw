# Reinventing the wheel

This is a minimal C++ template library, named rtw (reinventing the wheel).

## Project Structure

The project structure is shown below.

```
rtw/
    CMakeLists.txt
    bin/
    build/
    cov/
        CMakeLists.txt
        lcov/
    doc/
        CMakeLists.txt
        Doxyfile.in
        doxygen/
    include/
        algorithm/
            *.hpp
    lib/
    src/
        CMakeLists.txt
        main.cpp
    test/
        CMakeLists.txt
        run_all_tests.cpp
        test_*.cpp
```

## Dependencies
This project depends on `cmake`, `googletest`, `doxygen`, `graphviz` and `lcov`.  

## Build

1. cmake  
Make and move to the `build` directory and cmake the top level `CMakeLists.txt`.  
If `Release` or `Debug` option is needed, use the `-DCMAKE_BUILD_TYPE` option.  
```
$ mkdir build
$ cd build
$ cmake ..
or
$ cmake -DCMAKE_BUILD_TYPE=Release ..
or
$ cmake -DCMAKE_BUILD_TYPE=Debug ..
```

2. make  
Make the targets.  
Executables `rtw` and `run_all_tests` are made in the `bin` directory.
```
$ make
```

3. ctest  
Run all the tests.  
If the detail info is needed, use `-V` option.  
```
$ ctest
or
$ ctest -V
or
$ GTEST_COLOR=1 ctest -V
```

4. make doc  
Make documents by doxygen.  
You can read the generated document `doc/doxygen/html/index.html` with browser.  
```
$ make doc
```

5. make cov  
Make the test coverage report by lcov after running ctest.  
You can check the coverage report `cov/lcov/index.html` with browser.  
The coverage report is made when using cmake `-DCMAKE_BUILD_TYPE=Debug` option.  
NOTICE: The coverage of header-only functions or classes are NOT reported.
```
$ make cov
```

## License
MIT License

## References

Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest and Clifford Stein, [*Introduction to Algorithms, Third Edition*](https://mitpress.mit.edu/books/introduction-algorithms-third-edition), The MIT Press, 2009.