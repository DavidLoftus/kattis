
cc_library(
    name = "otherside_lib",
    srcs = ["otherside.cpp"],
    hdrs = ["otherside.hpp"],
)

cc_binary(
    name = "otherside",
    srcs = ["main.cpp"],
    deps = [":otherside_lib"],
)

filegroup(
    name = "otherside_samples",
    srcs = glob([
        "samples/*.in",
        "samples/*.ans",
    ]),
)

cc_test(
    name = "otherside_test",
    srcs = ["test.cpp"],
    deps = [
        ":otherside_lib",
        "@googletest//:gtest_main",
    ],
    data = [":otherside_samples"],
)