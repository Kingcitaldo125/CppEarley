#pragma once

#include "earley_utils.h"

namespace Earley
{
	inline S_type_t init(const size_t len_words);

	inline bool is_nonterminal(const char ch);

	inline bool is_terminal(const char ch);

	inline bool is_finished(const S_state_type_t& state);

	std::string swap_around_dot(const std::string& strng);

	std::string get_next_element(const S_state_type_t& state);

	std::vector<std::string> split(const std::string& strng, const char delim);

	std::vector<std::string> prod_split(const std::string& strng);

	bool predict(S_type_t& S, const unsigned int k, const std::string& nxt_elem, S_grammar_type_t& grammar);

	bool scan(S_type_t& S, const unsigned int k, S_state_type_t& state, const std::string& words);

	bool complete(S_type_t& S, const unsigned int k, S_state_type_t& state);

	bool check_end_set(const S_type_t& S, const S_state_type_t& expected);

	bool earley_parse(const std::string& words, const S_grammar_type_t& grammar);
}

