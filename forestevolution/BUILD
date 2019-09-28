
cc_library(
    name = "forestevolution_lib",
    srcs = ["forestevolution.cpp"],
    hdrs = ["forestevolution.hpp"],
)

cc_binary(
    name = "forestevolution",
    srcs = ["main.cpp"],
    deps = [":forestevolution_lib"],
)

filegroup(
    name = "forestevolution_samples",
    srcs = glob([
        "samples/*.in",
        "samples/*.ans",
    ]),
)

cc_test(
    name = "forestevolution_test",
    srcs = ["test.cpp"],
    deps = [
        ":forestevolution_lib",
        "@googletest//:gtest_main",
    ],
    data = [":forestevolution_samples"],
)