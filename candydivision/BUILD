
cc_library(
    name = "candydivision_lib",
    srcs = ["candydivision.cpp"],
    hdrs = ["candydivision.hpp"],
)

cc_binary(
    name = "candydivision",
    srcs = ["main.cpp"],
    deps = [":candydivision_lib"],
)

filegroup(
    name = "candydivision_samples",
    srcs = glob([
        "samples/*.in",
        "samples/*.ans",
    ]),
)

cc_test(
    name = "candydivision_test",
    srcs = ["test.cpp"],
    deps = [
        ":candydivision_lib",
        "@googletest//:gtest_main",
    ],
    data = [":candydivision_samples"],
)