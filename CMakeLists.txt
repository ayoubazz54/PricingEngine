add_executable(pricing_engine
    src/main.cpp
    src/option.cpp
    src/black_scholes.cpp
)


add_executable(delta
    benchmarks/analytical_vs_numerical/delta.cpp
)

add_executable(gamma
    benchmarks/analytical_vs_numerical/gamma.cpp)
