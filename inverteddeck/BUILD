
cc_library(
    name = "inverteddeck_lib",
    srcs = ["inverteddeck.cpp"],
    hdrs = ["inverteddeck.hpp"],
)

cc_binary(
    name = "inverteddeck",
    srcs = ["main.cpp"],
    deps = [":inverteddeck_lib"],
)

filegroup(
    name = "inverteddeck_samples",
    srcs = glob([
        "samples/*.in",
        "samples/*.ans",
    ]),
)

cc_test(
    name = "inverteddeck_test",
    srcs = ["test.cpp"],
    deps = [
        ":inverteddeck_lib",
        "@googletest//:gtest_main",
    ],
    data = [":inverteddeck_samples"],
)