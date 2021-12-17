#include <iostream>

#include "earley.h"
#include "grammar.h"

using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
  std::string grammar_location(".\\grammars\\grammar.txt");
  // override for the window grammar path
  if (argc > 1) {
    grammar_location = argv[1];
  }
  // TBD: Pass in the path to the grammar via 'argv'
  std::vector<std::string> loaded_gramm =
      Earley::load_grammar(grammar_location);

  if (loaded_gramm.size() == 0) {
    cout << "Could not open grammar file '" << grammar_location
         << "' -- exiting\n";
    return -1;
  }

  auto grammar = Earley::process_grammar(loaded_gramm);
  const std::array<std::string, 4> inputs{"1", "1+", "1+2", "2+3*4"};

  for (const auto &inp : inputs) {
    cout << "Input <" << inp << "> = " << std::boolalpha
         << Earley::earley_parse(inp, grammar) << endl;
  }

  return 0;
}
