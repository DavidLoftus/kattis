
cc_library(
    name = "expeditiouscubing_lib",
    srcs = ["expeditiouscubing.cpp"],
    hdrs = ["expeditiouscubing.hpp"],
)

cc_binary(
    name = "expeditiouscubing",
    srcs = ["main.cpp"],
    deps = [":expeditiouscubing_lib"],
)

filegroup(
    name = "expeditiouscubing_samples",
    srcs = glob([
        "samples/*.in",
        "samples/*.ans",
    ]),
)

cc_test(
    name = "expeditiouscubing_test",
    srcs = ["test.cpp"],
    deps = [
        ":expeditiouscubing_lib",
        "@googletest//:gtest_main",
    ],
    data = [":expeditiouscubing_samples"],
)