cmake_minimum_required(VERSION 3.12)

project(Exercise2 CXX)
#[[
CMake has some special variables that are either created behind the scenes or have meaning to CMake when set by project code.
Many of these variables start with CMAKE_. Avoid this naming convention when creating variables for your projects.
Two of these special user settable variables are CMAKE_CXX_STANDARD and CMAKE_CXX_STANDARD_REQUIRED.
These may be used together to specify the C++ standard needed to build the project.

CXX_STANDARD
버전 3.1의 새로운 기능.

이 대상을 빌드하기 위해 기능이 요청 된 C ++ 표준입니다.

이 특성은이 대상을 빌드하기 위해 기능이 요청 된 C ++ 표준을 지정합니다. 일부 컴파일러의 경우 컴파일 라인에 -std=gnu++11 과 같은 플래그가 추가 됩니다. 2015 업데이트 3 이전의 Microsoft Visual C ++와 같이 표준 수준의 개념이없는 컴파일러의 경우에는 효과가 없습니다.

지원되는 값은 다음과 같습니다.

98
C++98

11
C++11

14
C++14

17
버전 3.8의 새로운 기능.

C++17

20
버전 3.12의 새로운 기능.

C++20

23
버전 3.20의 새로운 기능.

C++23

요청 된 값으로 인해 사용중인 컴파일러에 대해 컴파일 플래그가 추가되지 않으면 이전 표준 플래그가 대신 추가됩니다. 이것은 다음을 사용하는 것을 의미합니다.

set_property(TARGET tgt PROPERTY CXX_STANDARD 11)
-std=gnu++11 또는 이와 동등한 플래그를 지원하지 않는 컴파일러를 사용 하면 오류나 경고가 발생하지 않지만 지원되는 경우 대신 -std=gnu++98 플래그 를 추가합니다 . 이 "감쇠"동작은 CXX_STANDARD_REQUIRED 대상 속성 으로 제어 할 수 있습니다 . 또한 CXX_EXTENSIONS 대상 속성을 사용하여 컴파일러 관련 확장을 대상별로 활성화할지 여부를 제어 할 수 있습니다.

컴파일 기능 및 지원되는 컴파일러 목록에 대한 정보 는 cmake-compile-features(7) 매뉴얼을 참조하십시오.

이 특성은 대상을 작성할 때 설정된 경우 CMAKE_CXX_STANDARD 변수 의 값으로 초기화됩니다 .
]]
# https://cmake.org/cmake/help/latest/manual/cmake-compile-features.7.html#manual:cmake-compile-features(7)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(
    Kookmin
    Exercise2.cxx
)