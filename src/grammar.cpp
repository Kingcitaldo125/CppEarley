#include <fstream>
#include <iostream>
#include <regex>

#include "grammar.h"

using std::cout;
using std::endl;

std::vector<std::string> Earley::load_grammar(const std::string &location) {
  std::ifstream iff(location.c_str(), std::ios::in);
  std::vector<std::string> mvec;

  if (iff.is_open()) {
    while (iff) {
      std::string holder;
      std::getline(iff, holder);
      mvec.push_back(holder);
    }
    mvec.pop_back();
    mvec.shrink_to_fit();
    iff.close();
  } else
    cout << "Failed to open grammar file '" << location << "'\n";

  return mvec;
}

Earley::S_grammar_type_t
Earley::process_grammar(const std::vector<std::string> &gramm_raw) {
  Earley::S_grammar_type_t gramm_struct;

  for (auto &prod : gramm_raw) {
    std::smatch match_results;
    std::regex prod_regex("^(.*)\\s->\\s(.*)$");
    if (std::regex_match(prod, match_results, prod_regex)) {
      std::string prod_name = match_results[1];
      std::string prod_value = match_results[2];

      // Check to see if the production maps to a terminal symbol(s)
      std::regex number_regex("(\\d\\s[|]\\s)+\\d");
      if (std::regex_match(prod_value, number_regex))
        prod_value = "number";

      gramm_struct.insert(std::make_pair(prod_name, prod_value));
    }
  }

  return gramm_struct;
}
