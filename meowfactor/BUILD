
cc_library(
    name = "meowfactor_lib",
    srcs = ["meowfactor.cpp"],
    hdrs = ["meowfactor.hpp"],
)

cc_binary(
    name = "meowfactor",
    srcs = ["main.cpp"],
    deps = [":meowfactor_lib"],
)

filegroup(
    name = "meowfactor_samples",
    srcs = glob([
        "samples/*.in",
        "samples/*.ans",
    ]),
)

cc_test(
    name = "meowfactor_test",
    srcs = ["test.cpp"],
    deps = [
        ":meowfactor_lib",
        "@googletest//:gtest_main",
    ],
    data = [":meowfactor_samples"],
)