# 실습 준비
os - Ubuntu-20.04\
cmake version 3.16.3\
cmake version이 낮아 수동 설치를 필요로 하는 경우도 있다.
```bash
$ sudo apt install cmake
# sudo snap install cmake

$ cmake --version
cmake version 3.16.3

CMake suite maintained and supported by Kitware (kitware.com/cmake).
```

## CMake Tutorial
https://cmake.org/cmake/help/latest/guide/tutorial/index.html  
https://junstar92.tistory.com/204  

## CMake build
CMakeLists.txt가 있는 디렉토리로 이동하여 다음 명령어를 실행한다.
```bash
$ cmake -S ./ -B build
$ cmake --build build -j
```
이 두 명령어는은 다음과 같다.\
Run cmake to configure the project and generate a native build system\
Then call that build system to actually compile/link the project