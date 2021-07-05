#include <gtest/gtest.h>
#include <array>

#include "grammar.cpp"
#include "earley.cpp"


static std::string test_grammar_location;
static std::string test_grammar_name("test_grammar.txt");
static std::vector<std::string> loaded_gramm;
static Earley::S_grammar_type_t test_grammar;


TEST(BasicTest, MyTestName1)
{
  EXPECT_EQ(0,0);
}


TEST(earley, Input1Empty)
{
  std::string input_1("");

  auto parse_res = Earley::earley_parse(input_1, test_grammar);

  EXPECT_EQ(parse_res, true);
}


TEST(earley, AddPass)
{
  std::array<std::string, 6> inputs {"0+1","1+0","1+1","9+0","5+9","0+9"};
  
  for(auto& inp : inputs)
  {
    auto parse_res = Earley::earley_parse(inp, test_grammar);

    EXPECT_EQ(parse_res, true);
  }
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
  
  loaded_gramm = Earley::load_grammar(test_grammar_location);
  
  test_grammar = Earley::process_grammar(loaded_gramm);

  testing::InitGoogleTest();

  return RUN_ALL_TESTS();
}

