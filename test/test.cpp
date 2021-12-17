#include <array>
#include <gtest/gtest.h>
#include <iostream>

#include "earley.cpp"
#include "grammar.cpp"

static std::string test_grammar_location;
static std::string test_grammar_name("test_grammar.txt");
static std::vector<std::string> loaded_gramm;
static Earley::S_grammar_type_t test_grammar;

TEST(earley, Input1Empty) {
  const std::string input_1("");

  auto parse_res = Earley::earley_parse(input_1, test_grammar);

  EXPECT_EQ(parse_res, true);
}

TEST(earley, AddPass) {
  const std::array<std::string, 6> inputs{"0+1", "1+0", "1+1",
                                          "9+0", "5+9", "0+9"};

  for (auto &inp : inputs) {
    auto parse_res = Earley::earley_parse(inp, test_grammar);

    EXPECT_EQ(parse_res, true);
  }
}

TEST(earley, AddFail) {
  const std::array<std::string, 5> inputs{"0+", "+0", "1+", "+1", "+"};

  for (auto &inp : inputs) {
    auto parse_res = Earley::earley_parse(inp, test_grammar);

    std::cout << std::boolalpha << "parse_res (" << parse_res << ")"
              << std::endl;

    EXPECT_EQ(parse_res, false);
  }
}

TEST(earley, MulPass) {
  const std::array<std::string, 6> inputs{"0*1", "1*0", "1*1",
                                          "9*0", "5*9", "0*9"};

  for (auto &inp : inputs) {
    auto parse_res = Earley::earley_parse(inp, test_grammar);

    EXPECT_EQ(parse_res, true);
  }
}

TEST(earley, MulFail) {
  const std::array<std::string, 5> inputs{"0*", "*0", "1*", "*1", "*"};

  for (auto &inp : inputs) {
    auto parse_res = Earley::earley_parse(inp, test_grammar);

    std::cout << std::boolalpha << "parse_res (" << parse_res << ")"
              << std::endl;

    EXPECT_EQ(parse_res, false);
  }
}

TEST(earley, BadOpFail1) {
  const std::array<std::string, 5> inputs{"0-", "-0", "1-", "-1", "-"};

  for (auto &inp : inputs) {
    auto parse_res = Earley::earley_parse(inp, test_grammar);

    std::cout << std::boolalpha << "parse_res (" << parse_res << ")"
              << std::endl;

    EXPECT_EQ(parse_res, false);
  }
}

TEST(earley, BadOpFail2) {
  const std::array<std::string, 5> inputs{"0/", "/0", "1/", "/1", "/"};

  for (auto &inp : inputs) {
    auto parse_res = Earley::earley_parse(inp, test_grammar);

    std::cout << std::boolalpha << "parse_res (" << parse_res << ")"
              << std::endl;

    EXPECT_EQ(parse_res, false);
  }
}

TEST(earley, AllNumbersPass1) {
  const std::array<std::string, 2> inputs{"0+1+2+3+4+5+6+7+8+9",
                                          "0*1*2*3*4*5*6*7*8*9"};

  for (auto &inp : inputs) {
    auto parse_res = Earley::earley_parse(inp, test_grammar);

    std::cout << std::boolalpha << "parse_res (" << parse_res << ")"
              << std::endl;

    EXPECT_EQ(parse_res, true);
  }
}

TEST(earley, AllNumbersPass2) {
  const std::array<std::string, 2> inputs{"0+1*2+3*4+5*6+7*8+9",
                                          "0*1+2*3+4*5+6*7+8*9"};

  for (auto &inp : inputs) {
    auto parse_res = Earley::earley_parse(inp, test_grammar);

    std::cout << std::boolalpha << "parse_res (" << parse_res << ")"
              << std::endl;

    EXPECT_EQ(parse_res, true);
  }
}

int main(int argc, char **argv) {
  if (argc < 2) {
    cout << "ERROR: Not enough args to set path to test grammar - failing.\n";
    return -1;
  }

  test_grammar_location = argv[1];
  test_grammar_location += test_grammar_name;

  cout << "test_grammar_location " << test_grammar_location << "\n";

  loaded_gramm = Earley::load_grammar(test_grammar_location);

  test_grammar = Earley::process_grammar(loaded_gramm);

  testing::InitGoogleTest();

  return RUN_ALL_TESTS();
}
