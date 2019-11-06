
cc_library(
    name = "dunglish_lib",
    srcs = ["dunglish.cpp"],
    hdrs = ["dunglish.hpp"],
)

cc_binary(
    name = "dunglish",
    srcs = ["main.cpp"],
    deps = [":dunglish_lib"],
)

filegroup(
    name = "dunglish_samples",
    srcs = glob([
        "samples/*.in",
        "samples/*.ans",
    ]),
)

cc_test(
    name = "dunglish_test",
    srcs = ["test.cpp"],
    deps = [
        ":dunglish_lib",
        "@googletest//:gtest_main",
    ],
    data = [":dunglish_samples"],
)