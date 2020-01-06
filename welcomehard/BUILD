
cc_library(
    name = "welcomehard_lib",
    srcs = ["welcomehard.cpp"],
    hdrs = ["welcomehard.hpp"],
)

cc_binary(
    name = "welcomehard",
    srcs = ["main.cpp"],
    deps = [":welcomehard_lib"],
)

filegroup(
    name = "welcomehard_samples",
    srcs = glob([
        "samples/*.in",
        "samples/*.ans",
    ]),
)

cc_test(
    name = "welcomehard_test",
    srcs = ["test.cpp"],
    deps = [
        ":welcomehard_lib",
        "@googletest//:gtest_main",
    ],
    data = [":welcomehard_samples"],
)