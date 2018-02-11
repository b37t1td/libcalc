add_library(parser parser.cxx)
add_library(tokenizer tokenizer.cxx)
add_library(evaluator evaluator.cxx)
add_library(calc SHARED libcalc.cxx)
target_link_libraries(calc parser tokenizer evaluator)

