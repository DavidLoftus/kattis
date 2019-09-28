
cc_library(
    name = "statisticians_lib",
    srcs = ["statisticians.cpp"],
    hdrs = ["statisticians.hpp"],
)

cc_binary(
    name = "statisticians",
    srcs = ["main.cpp"],
    deps = [":statisticians_lib"],
)

filegroup(
    name = "statisticians_samples",
    srcs = glob([
        "samples/*.in",
        "samples/*.ans",
    ]),
)

cc_test(
    name = "statisticians_test",
    srcs = ["test.cpp"],
    deps = [
        ":statisticians_lib",
        "@googletest//:gtest_main",
    ],
    data = [":statisticians_samples"],
)