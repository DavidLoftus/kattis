
cc_library(
    name = "loowater_lib",
    srcs = ["loowater.cpp"],
    hdrs = ["loowater.hpp"],
)

cc_binary(
    name = "loowater",
    srcs = ["main.cpp"],
    deps = [":loowater_lib"],
)

filegroup(
    name = "loowater_samples",
    srcs = glob([
        "samples/*.in",
        "samples/*.ans",
    ]),
)

cc_test(
    name = "loowater_test",
    srcs = ["test.cpp"],
    deps = [
        ":loowater_lib",
        "@googletest//:gtest_main",
    ],
    data = [":loowater_samples"],
)