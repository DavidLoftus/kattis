
cc_library(
    name = "dyslectionary_lib",
    srcs = ["dyslectionary.cpp"],
    hdrs = ["dyslectionary.hpp"],
)

cc_binary(
    name = "dyslectionary",
    srcs = ["main.cpp"],
    deps = [":dyslectionary_lib"],
)

filegroup(
    name = "dyslectionary_samples",
    srcs = glob([
        "samples/*.in",
        "samples/*.ans",
    ]),
)

cc_test(
    name = "dyslectionary_test",
    srcs = ["test.cpp"],
    deps = [
        ":dyslectionary_lib",
        "@googletest//:gtest_main",
    ],
    data = [":dyslectionary_samples"],
)