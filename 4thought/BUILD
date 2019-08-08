
cc_library(
    name = "4thought_lib",
    srcs = ["4thought.cpp"],
    hdrs = ["4thought.hpp"],
)

cc_binary(
    name = "4thought",
    srcs = ["main.cpp"],
    deps = [":4thought_lib"],
)

filegroup(
    name = "4thought_samples",
    srcs = glob([
        "samples/*.in",
        "samples/*.ans",
    ]),
)

cc_test(
    name = "4thought_test",
    srcs = ["test.cpp"],
    deps = [
        ":4thought_lib",
        "@googletest//:gtest_main",
    ],
    data = [":4thought_samples"],
)