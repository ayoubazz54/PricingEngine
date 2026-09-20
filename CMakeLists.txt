cmake_minimum_required(VERSION 3.12)

project(PricingEngine CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

set(ENGINE_SOURCES
    src/option.cpp
    src/black_sholes.cpp
    src/greeks.cpp
    src/crr.cpp
    src/monte_carlo.cpp
)

add_library(PricingCore STATIC ${ENGINE_SOURCES})

add_executable(pricer src/main.cpp)
target_link_libraries(pricer PRIVATE PricingCore)

set(CONVERGENCE_SOURCES1
    benchmarks/monte_carlo/convergence.cpp
)

set(CONVERGENCE_SOURCES2
    benchmarks/monte_carlo/convergence.cpp
)

add_executable(convergenceMC ${CONVERGENCE_SOURCES1})
target_link_libraries(convergenceMC PRIVATE PricingCore)

add_executable(convergenceCRR ${CONVERGENCE_SOURCES2})
target_link_libraries(convergenceCRR PRIVATE PricingCore)