# CMake generated Testfile for 
# Source directory: /Users/bolt/git/crow-template
# Build directory: /Users/bolt/git/crow-template/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(crow_test "/Users/bolt/git/crow-template/build/tests/unittest")
add_test(template_test "/Users/bolt/git/crow-template/build/tests/template/test.py")
set_tests_properties(template_test PROPERTIES  WORKING_DIRECTORY "/Users/bolt/git/crow-template/build/tests/template")
subdirs("src")
subdirs("tests")
