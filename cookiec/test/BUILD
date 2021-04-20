################################################################################
################################ TEST BINARIES #################################
################################################################################

cc_test(
  name = "Filesystem",
  srcs = [ "fs.cc" ],
  deps = [
    "//cookiec:Filesystem"
  ],
  timeout = "short"
)

cc_test(
  name = "SourceCodePool",
  srcs = [ "source-code-pool.cc" ],
  deps = [
    "//cookiec:SourceCodePool"
  ],
  data = [
    "data/code.txt"
  ],
  timeout = "short"
)

