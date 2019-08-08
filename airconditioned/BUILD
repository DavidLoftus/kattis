
cc_library(
    name = "airconditioned_lib",
    srcs = ["airconditioned.cpp"],
    hdrs = ["airconditioned.hpp"],
)

cc_binary(
    name = "airconditioned",
    srcs = ["main.cpp"],
    deps = [":airconditioned_lib"],
)

filegroup(
    name = "airconditioned_samples",
    srcs = glob([
        "samples/*.in",
        "samples/*.ans",
    ]),
)

cc_test(
    name = "airconditioned_test",
    srcs = ["test.cpp"],
    deps = [
        ":airconditioned_lib",
        "@googletest//:gtest_main",
    ],
    data = [":airconditioned_samples"],
)