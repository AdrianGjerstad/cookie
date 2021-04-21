################################################################################
################################ TEST BINARIES #################################
################################################################################

cc_test(
  name = "Filesystem",
  srcs = [ "fs.cc" ],
  deps = [
    "//test:TestFramework",
    "//cookiec:Filesystem"
  ],
  timeout = "short"
)

cc_test(
  name = "SourceCodePool",
  srcs = [ "source-code-pool.cc" ],
  deps = [
    "//test:TestFramework",
    "//cookiec:SourceCodePool"
  ],
  data = [
    "data/code.txt"
  ],
  timeout = "short"
)

