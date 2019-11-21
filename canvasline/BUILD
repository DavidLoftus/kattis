
cc_library(
    name = "canvasline_lib",
    srcs = ["canvasline.cpp"],
    hdrs = ["canvasline.hpp"],
)

cc_binary(
    name = "canvasline",
    srcs = ["main.cpp"],
    deps = [":canvasline_lib"],
)

filegroup(
    name = "canvasline_samples",
    srcs = glob([
        "samples/*.in",
        "samples/*.ans",
    ]),
)

cc_test(
    name = "canvasline_test",
    srcs = ["test.cpp"],
    deps = [
        ":canvasline_lib",
        "@googletest//:gtest_main",
    ],
    data = [":canvasline_samples"],
)