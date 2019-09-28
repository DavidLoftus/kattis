
cc_library(
    name = "divljak_lib",
    srcs = ["divljak.cpp"],
    hdrs = ["divljak.hpp"],
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
    deps = [
        ":divljak_lib",
        "@googletest//:gtest_main",
    ],
    data = [":divljak_samples"],
)