
cc_library(
    name = "glyphrecognition_lib",
    srcs = ["glyphrecognition.cpp"],
    hdrs = ["glyphrecognition.hpp"],
)

cc_binary(
    name = "glyphrecognition",
    srcs = ["main.cpp"],
    deps = [":glyphrecognition_lib"],
)

filegroup(
    name = "glyphrecognition_samples",
    srcs = glob([
        "samples/*.in",
        "samples/*.ans",
    ]),
)

cc_test(
    name = "glyphrecognition_test",
    srcs = ["test.cpp"],
    deps = [
        ":glyphrecognition_lib",
        "@googletest//:gtest_main",
    ],
    data = [":glyphrecognition_samples"],
)