
cc_library(
    name = "mandelbrot_lib",
    srcs = ["mandelbrot.cpp"],
    hdrs = ["mandelbrot.hpp"],
)

cc_binary(
    name = "mandelbrot",
    srcs = ["main.cpp"],
    deps = [":mandelbrot_lib"],
)

filegroup(
    name = "mandelbrot_samples",
    srcs = glob([
        "samples/*.in",
        "samples/*.ans",
    ]),
)

cc_test(
    name = "mandelbrot_test",
    srcs = ["test.cpp"],
    deps = [
        ":mandelbrot_lib",
        "@googletest//:gtest_main",
    ],
    data = [":mandelbrot_samples"],
)