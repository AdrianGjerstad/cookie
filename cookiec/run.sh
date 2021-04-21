#!/bin/bash

# Run script. Invoke `./run.sh help' for help.

function run_tests {
  # run_tests - Run all (or specified) bazel tests
  # Invocation: ./run.sh tests [TARGETS...]
  #
  # Example: ./run.sh tests Filesystem SourceCodePool
  export CC="g++-8"  # Make absolutely sure we are using an up-to-date compiler.
  export BAZEL_CXXOPTS="-std=c++17"  # g++ v4 was built in 2013. It wouldn't
                                     # have this.

  bazel_targets=()

  for arg in $@; do
    bazel_targets+=("//cookiec/test:$arg")
  done

  if [[ ${#bazel_targets[@]} -eq 0 ]]; then
    echo -e "\x1b[1;33mRUNNING ALL TESTS...\x1b[0m"
    bazel test //cookiec/test:*
    return_code=$?
    
    if [[ $return_code -eq 0 ]]; then
      echo -e "\x1b[1;32mAll tests succeeded (exit 0)\x1b[0m"
    else
      echo -e "\x1b[1;31mbazel test returned exit code $return_code; failed\x1b[0m"
    fi

    return $return_code
  else
    echo -e "\x1b[1;33mRUNNING TESTS: $bazel_targets\x1b[0m"
    bazel test $bazel_targets
    return_code=$?
    
    if [[ $return_code -eq 0 ]]; then
      echo -e "\x1b[1;32mEntire subset of tests succeeded (exit 0)\x1b[0m"
    else
      echo -e "\x1b[1;31mbazel test returned exit code $return_code; failed\x1b[0m"
    fi

    return $return_code
  fi
}

function run_build {
  # run_build - Build main binary or specified targets
  # Invocation: ./run.sh build [TARGETS...]
  # 
  # Example: ./run.sh build Lexer Parser Programmer Assembler
  # 
  # NOTE: This function may also trigger the building of dependencies of the
  # targets.
  export CC="g++-8"  # Make absolutely sure we are using an up-to-date compiler.
  export BAZEL_CXXOPTS="-std=c++17"  # g++ v4 was built in 2013. It wouldn't
                                     # have this.

  bazel_targets=()
  
  for arg in $@; do
    bazel_targets+=("//cookiec:$arg")
  done

  if [[ ${#bazel_targets[@]} -eq 0 ]]; then
    bazel build //cookiec:cookiec
    return $?
  else
    bazel build $bazel_targets
    return $?
  fi
}

function print_help {
  case $1 in
    tests)
      echo "Usage: run.sh tests [TARGETS]"
      echo ""
      echo "    Run all (or specified) bazel tests"
      echo ""
      echo "Examples:"
      echo "    Run all tests:"
      echo ""
      echo "      run.sh tests  # No targets need to be specified"
      echo ""
      echo "    Run tests \"foo\" and \"bar\":"
      echo ""
      echo "      run.sh tests foo bar  # Nice and simple!"
      echo ""
      ;;

    build)
      echo "Usage: run.sh build [TARGETS]"
      echo ""
      echo "    Build main binary or specified targets"
      echo ""
      echo "Examples:"
      echo "    Build compiler as a whole:"
      echo ""
      echo "      run.sh build  # //cookiec:cookiec is implicit"
      echo ""
      echo "    Build cc_library \"foo\" and cc_library \"bar\":"
      echo ""
      echo "      run.sh build foo bar"
      echo ""
      ;;

    help)
      echo "Usage: run.sh help [COMMAND]"
      echo ""
      echo "    Display helpful information and exit"
      echo ""
      echo "Not much to explain here. Just run it with a different command to learn about"
      echo "that command."
      echo ""
      ;;

    *)
      echo "Usage: run.sh <COMMAND> [OPTIONS]"
      echo ""
      echo "    Interact with the bazel build system for the Cookie programming language"
      echo "    project."
      echo ""
      echo "Commands:"
      echo "    tests  Run all (or specified) bazel tests"
      echo "    build  Build main binary or specified targets"
      echo "    help   Display this message and exit"
      echo ""
      echo "For more help on a specific command, invoke \`run.sh help [COMMAND]'."
      
      if [[ $1 != "" ]]; then
        echo -e "\x1b[1mrun.sh: \x1b[31merror:\x1b[0m unknown command: '$1'"
      fi
      ;;

  esac
}

################
## DISPATCHER ##
################

case $1 in
  tests)
    shift
    run_tests $@
    exit $?
    ;;
  
  build)
    shift
    run_build $@
    exit $?
    ;;

  help)
    shift
    print_help $@
    exit $?
    ;;

  *)
    print_help
    echo -e "\x1b[1mrun.sh: \x1b[31merror:\x1b[0m expected one of (tests, build), got $1"
    exit 1
esac

