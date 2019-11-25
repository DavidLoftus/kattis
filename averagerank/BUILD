
cc_library(
    name = "averagerank_lib",
    srcs = ["averagerank.cpp"],
    hdrs = ["averagerank.hpp"],
)

cc_binary(
    name = "averagerank",
    srcs = ["main.cpp"],
    deps = [":averagerank_lib"],
)

filegroup(
    name = "averagerank_samples",
    srcs = glob([
        "samples/*.in",
        "samples/*.ans",
    ]),
)

cc_test(
    name = "averagerank_test",
    srcs = ["test.cpp"],
    deps = [
        ":averagerank_lib",
        "@googletest//:gtest_main",
    ],
    data = [":averagerank_samples"],
)