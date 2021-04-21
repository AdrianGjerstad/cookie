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

cc_test(
  name = "Token",
  srcs = [ "token.cc" ],
  deps = [
    "//test:TestFramework",
    "//cookiec:Token",
    "//cookiec:TokenType",
    "//cookiec:Position",
    "//cookiec:SourceCodePool"
  ],
  data = [
    "data/example.cookie"
  ],
  timeout = "short"
)

