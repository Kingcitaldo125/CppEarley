#include <iostream>
#include <regex>
#include <sstream>
#include <string>

#include "earley.h"
#include "grammar.h"

using std::cout;
using std::endl;

using Earley::S_grammar_type_t;
using Earley::S_set_type_t;
using Earley::S_state_type_t;
using Earley::S_type_t;

inline S_type_t Earley::init(const size_t len_words) {
  S_type_t S;
  for (unsigned int i = 0; i < len_words + 1; ++i) {
    S_set_type_t s_set;
    S.push_back(s_set);
  }

  return S;
}

inline bool Earley::is_nonterminal(const char ch) {
  return Earley::nonterminals.find(ch) != Earley::nonterminals.end();
}

inline bool Earley::is_terminal(const char ch) {
  return Earley::parts_of_speech.find(ch) != Earley::parts_of_speech.end();
}

inline bool Earley::is_finished(const S_state_type_t &state) {
  std::string prod = std::get<1>(state);

  return prod.find(Earley::dot) >= prod.size() - 1;
}

// Swap with item in front of the dot by default
std::string Earley::swap_around_dot(const std::string &strng) {
  if (strng.find(Earley::dot) >= strng.size() - 1)
    return strng;

  std::string n_str(strng);
  auto dot_idx = strng.find(Earley::dot);
  auto next_item = strng.at(dot_idx + 1);

  // Swap around a/the lexeme
  if (Earley::nonterminals.find(next_item) != Earley::nonterminals.end()) {
    std::swap(n_str[dot_idx], n_str[dot_idx + 1]);
    return n_str;
  } else if (Earley::parts_of_speech.find(next_item) !=
             Earley::parts_of_speech.end()) {
    std::swap(n_str[dot_idx], n_str[dot_idx + 1]);
    return n_str;
  }

  // Swap around a/the token (take the dot, remove it from the front and append
  // to the end)
  auto indx = n_str.find(Earley::dot);
  n_str.erase(indx, indx + 1);
  n_str += Earley::dot;

  return n_str;
}

std::string Earley::get_next_element(const S_state_type_t &state) {
  auto prod = std::get<1>(state);
  auto m_index = prod.find(Earley::dot);
  std::string nxt(1, prod.at(m_index + 1));

  if (is_nonterminal(nxt.at(0)) || is_terminal(nxt.at(0)))
    return nxt; // return the thing(char) that comes just after the Earley::dot

  // return the latter portion of the string (everything after the Earley::dot)
  return prod.substr(m_index + 1, prod.size() - m_index);
}

std::vector<std::string> Earley::split(const std::string &strng,
                                       const char delim) {
  std::vector<std::string> retvec;
  std::stringstream ss(strng);
  std::string holder;

  while (ss) {
    std::getline(ss, holder, delim);
    retvec.push_back(holder);
  }
  retvec.pop_back(); // take out the final, extra, element (not needed)

  return retvec;
}

std::vector<std::string> Earley::prod_split(const std::string &strng) {
  std::smatch sm;
  std::regex rgx("(\\b([^|])+\\b([|])*)");
  std::string m_string(strng);
  std::vector<std::string> retvec;

  bool got_match = true;
  // Parse through the string, stripping the matched terminal/non-terminal from
  // the front this allows for continuous matching against one or more
  // terminals/non-terminals between the pipes/spaces
  while (got_match) {
    got_match = std::regex_search(m_string, sm, rgx);
    if (got_match) {
      retvec.push_back(sm.str());
      m_string = sm.suffix();
    }
  }

  return retvec;
}

bool Earley::predict(S_type_t &S, const unsigned int k,
                     const std::string &nxt_elem, S_grammar_type_t &grammar) {
  bool added = false;
  std::string nxt_production = nxt_elem;
  std::string grammar_prod = grammar[nxt_production];
  auto prod_splits = prod_split(grammar_prod);

  for (auto &split : prod_splits) {
    std::stringstream ss;
    std::string split_nows = std::regex_replace(split, std::regex("\\s"), "");

    ss << Earley::dot;
    ss << split_nows;

    std::string dSplit(ss.str());
    Earley::S_set_type_t &current_set = S[k];
    S_state_type_t set_element = std::make_tuple(nxt_production, dSplit, k);

    // if not found: insert the tuple(set_element)
    if (std::find(current_set.begin(), current_set.end(), set_element) ==
        current_set.end()) {
      current_set.push_back(set_element);
      added = true;
    }
  }

  return added;
}

bool Earley::scan(S_type_t &S, const unsigned int k, S_state_type_t &state,
                  const std::string &words) {
  bool added = false;

  std::string nxt_elem_scanner = get_next_element(state);

  if (k >= words.size())
    return added;

  auto words_k = words.at(k);

  {
    // Process regex information against the token/word (see if it's a number)
    std::string rgx_input(1, words_k);
    std::regex rgx("[0-9]");
    std::smatch sm;
    auto res = std::regex_match(rgx_input, sm, rgx);

    if (nxt_elem_scanner == "number" && !res) {
      cout << "Not going to add non-number to forward set:";
      cout << "Terminal symbol is not a number?";
      cout << endl;
      return added;
    }
  }

  if (k > words.size() - 1)
    return added;

  if (Earley::parts_of_speech.find(words.at(k)) !=
      Earley::parts_of_speech.end()) {
    std::string state_swapped = swap_around_dot(std::get<1>(state));

    S_state_type_t new_state =
        std::make_tuple(std::get<0>(state), state_swapped, std::get<2>(state));
    auto &nxt_set = S[k + 1];
    // If the element (new_state) is in the language, described by the grammar,
    // then add that completed terminal symbol to S[k + 1]
    if (std::find(nxt_set.begin(), nxt_set.end(), new_state) == nxt_set.end()) {
      nxt_set.push_back(new_state);
      added = true;
    }
  }

  return added;
}

bool Earley::complete(S_type_t &S, const unsigned int k,
                      S_state_type_t &state) {
  bool added = false;
  int state_origin = std::get<2>(state);

  for (Earley::S_state_type_t &t_state : S[state_origin]) {
    std::string t_state_sym = std::get<1>(t_state);
    std::string t_state_temp(t_state_sym);

    auto fnd = t_state_temp.find(Earley::dot);
    t_state_temp.erase(fnd, fnd + 1);

    if (Earley::nonterminals.find(t_state_temp.at(0)) !=
        Earley::nonterminals.end()) {
      std::string swapped_prod = swap_around_dot(t_state_sym);

      // assemble t_state with the dot after the nonterminal (completed the
      // nonterminal) then add the new, completed, t_state to S[k]
      S_state_type_t n_tuple = std::make_tuple(
          std::get<0>(t_state), swapped_prod, std::get<2>(t_state));
      auto sk = S[k];

      // If we didn't already add the completed state to the current state, do
      // so now; otherwise,ignore and continue on
      if (std::find(sk.begin(), sk.end(), n_tuple) == sk.end()) {
        S[k].push_back(n_tuple);
        added = true;
      }
    }
  }

  return added;
}

bool Earley::check_end_set(const S_type_t &S, const S_state_type_t &expected) {
  auto &end_set = S[S.size() - 1];
  if (std::find(end_set.begin(), end_set.end(), expected) != end_set.end()) {
    return true;
  }
  return false;
}

bool Earley::earley_parse(const std::string &words,
                          const S_grammar_type_t &grammar) {
  // TBD: Add full support for empty string in grammar/earley
  if (words.size() == 0)
    return true;

  std::string start_p = "S";
  start_p += Earley::dot;
  S_state_type_t expected = std::make_tuple("P", start_p, 0);

  // Create the overarching array of sets (parse table)
  S_type_t S = init(words.size());
  {
    std::string sp(1, Earley::dot);
    sp += "S";
    S[0].push_back(std::make_tuple("P", sp, 0));
  }
  bool done = false;
  bool complete_parse = false;

  for (unsigned int k = 0; k < words.size() + 1; ++k) {
    bool added = true;
    if (done)
      break;

    while (added) {
      added = false;

      for (Earley::S_state_type_t state : S[k]) {
        if (check_end_set(S, expected)) {
          done = true;
          complete_parse = true;
          break;
        }

        bool finished = is_finished(state);
        if (!finished) {
          auto nxt_elem = get_next_element(state);

          if (is_nonterminal(nxt_elem.at(0))) {
            added = predict(S, k, nxt_elem,
                            const_cast<S_grammar_type_t &>(grammar));
          } else {
            added = scan(S, k, state, words);
          }
        } else {
          added = complete(S, k, state);
        }
      }
    }
  }

  return complete_parse;
}
