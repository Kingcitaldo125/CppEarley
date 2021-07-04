#pragma once

#include "earley_utils.h"

std::vector<std::string> load_grammar(const std::string&);
Earley::S_grammar_type_t process_grammar(const std::vector<std::string>&);

