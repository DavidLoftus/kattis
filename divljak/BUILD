cc_library(
    name = "divljak_lib",
    srcs = ["divljak.cpp"],
    hdrs = ["divljak.hpp"],
    copts = ["-std=c++17"],
)

cc_binary(
    name = "divljak",
    srcs = ["main.cpp"],
    deps = [":divljak_lib"],
)

filegroup(
    name = "divljak_samples",
    srcs = glob([
        "samples/*.in",
        "samples/*.ans",
    ]),
)

cc_test(
    name = "divljak_test",
    srcs = ["test.cpp"],
    data = [":divljak_samples"],
    deps = [
        ":divljak_lib",
        "@googletest//:gtest_main",
    ],
)
