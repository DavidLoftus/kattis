
cc_library(
    name = "unusualdarts_lib",
    srcs = ["unusualdarts.cpp"],
    hdrs = ["unusualdarts.hpp"],
)

cc_binary(
    name = "unusualdarts",
    srcs = ["main.cpp"],
    deps = [":unusualdarts_lib"],
)

filegroup(
    name = "unusualdarts_samples",
    srcs = glob([
        "samples/*.in",
        "samples/*.ans",
    ]),
)

cc_test(
    name = "unusualdarts_test",
    srcs = ["test.cpp"],
    deps = [
        ":unusualdarts_lib",
        "@googletest//:gtest_main",
    ],
    data = [":unusualdarts_samples"],
)