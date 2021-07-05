#include <gtest/gtest.h>
#include "grammar.cpp"
#include "earley.cpp"


static std::string test_grammar_location;
static std::string test_grammar_name("test_grammar.txt");


TEST(BasicTest, MyTestName1)
{
  EXPECT_EQ(0,0);
}


TEST(earley, Input1Empty)
{
  std::string input_1("");

  std::vector<std::string> loaded_gramm = Earley::load_grammar(test_grammar_location);

  auto grammar = Earley::process_grammar(loaded_gramm);
  auto parse_res = Earley::earley_parse(input_1, grammar);

  EXPECT_EQ(parse_res, true);
}


int main(int argc, char** argv)
{
  if (argc < 2)
  {
    cout << "ERROR: Not enough args to set path to test grammar - failing.\n";
    return -1;
  }

  test_grammar_location = argv[1];
  test_grammar_location += test_grammar_name;

  cout << "test_grammar_location " << test_grammar_location << "\n";

  testing::InitGoogleTest();

  return RUN_ALL_TESTS();
}

