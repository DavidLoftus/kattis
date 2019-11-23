
cc_library(
    name = "firetrucksarered_lib",
    srcs = ["firetrucksarered.cpp"],
    hdrs = ["firetrucksarered.hpp"],
)

cc_binary(
    name = "firetrucksarered",
    srcs = ["main.cpp"],
    deps = [":firetrucksarered_lib"],
)

filegroup(
    name = "firetrucksarered_samples",
    srcs = glob([
        "samples/*.in",
        "samples/*.ans",
    ]),
)

cc_test(
    name = "firetrucksarered_test",
    srcs = ["test.cpp"],
    deps = [
        ":firetrucksarered_lib",
        "@googletest//:gtest_main",
    ],
    data = [":firetrucksarered_samples"],
)