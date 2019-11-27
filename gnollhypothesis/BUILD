
cc_library(
    name = "gnollhypothesis_lib",
    srcs = ["gnollhypothesis.cpp"],
    hdrs = ["gnollhypothesis.hpp"],
)

cc_binary(
    name = "gnollhypothesis",
    srcs = ["main.cpp"],
    deps = [":gnollhypothesis_lib"],
)

filegroup(
    name = "gnollhypothesis_samples",
    srcs = glob([
        "samples/*.in",
        "samples/*.ans",
    ]),
)

cc_test(
    name = "gnollhypothesis_test",
    srcs = ["test.cpp"],
    deps = [
        ":gnollhypothesis_lib",
        "@googletest//:gtest_main",
    ],
    data = [":gnollhypothesis_samples"],
)