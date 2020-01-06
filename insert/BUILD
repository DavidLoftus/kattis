cc_library(
    name = "insert_lib",
    srcs = ["insert.cpp"],
    hdrs = ["insert.hpp"],
    copts = ["--std=c++14"],
)

cc_binary(
    name = "insert",
    srcs = ["main.cpp"],
    deps = [":insert_lib"],
)

filegroup(
    name = "insert_samples",
    srcs = glob([
        "samples/*.in",
        "samples/*.ans",
    ]),
)

cc_test(
    name = "insert_test",
    srcs = ["test.cpp"],
    data = [":insert_samples"],
    deps = [
        ":insert_lib",
        "@googletest//:gtest_main",
    ],
)
