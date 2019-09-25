
cc_library(
    name = "disgruntledjudge_lib",
    srcs = ["disgruntledjudge.cpp"],
    hdrs = ["disgruntledjudge.hpp"],
)

cc_binary(
    name = "disgruntledjudge",
    srcs = ["main.cpp"],
    deps = [":disgruntledjudge_lib"],
)

filegroup(
    name = "disgruntledjudge_samples",
    srcs = glob([
        "samples/*.in",
        "samples/*.ans",
    ]),
)

cc_test(
    name = "disgruntledjudge_test",
    srcs = ["test.cpp"],
    deps = [
        ":disgruntledjudge_lib",
        "@googletest//:gtest_main",
    ],
    data = [":disgruntledjudge_samples"],
)