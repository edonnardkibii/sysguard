add_executable(sysguard_tests
    test_main.cpp
)

add_test(
    NAME sysguard_tests
    COMMAND sysguard_tests
)