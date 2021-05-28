#include <iostream>
#include <algorithm>
#include <array>
#include <chrono>
#include <fstream>
#include <set>
#include <sstream>
#include <string>
#include <map>
#include <thread>
#include <tuple>
#include <vector>


using std::cout;
using std::endl;


namespace Earley
{
	using S_state_type_t = std::tuple<std::string, std::string, int>;
	using S_set_type_t = std::set<S_state_type_t>;
	using S_type_t = std::vector<S_set_type_t>;
	using S_grammar_type_t = std::multimap<std::string, std::string>;

	const char dot = '`';
	const std::string prod_split = " | ";
	const std::set<std::string> nonterminals{ "P", "S", "M", "T" };
	const std::set<std::string> parts_of_speech{ "+", "*", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
}

using Earley::S_state_type_t;
using Earley::S_set_type_t;
using Earley::S_type_t;
using Earley::S_grammar_type_t;


S_type_t init(const size_t len_words)
{
	S_type_t S;
	for (int i = 0; i < len_words; ++i)
	{
		S_set_type_t s_set;
		S.push_back(s_set);
	}

	return S;
}


bool is_nonterminal(const std::string& strng)
{
	return Earley::nonterminals.find(strng) != Earley::nonterminals.end();
}


bool is_terminal(const std::string& strng)
{
	return Earley::parts_of_speech.find(strng) != Earley::parts_of_speech.end();
}


bool is_finished(const S_state_type_t& state)
{
	auto prod = std::get<1>(state);
	return prod.find(Earley::dot) >= prod.size() - 1;
}


// Swap with item in front of the dot by default
std::string swap_around_dot(const std::string& strng)
{
	if (strng.find(Earley::dot) >= strng.size() - 1)
		return strng;

	std::string n_str(strng);
	auto dot_idx = strng.find(Earley::dot);
	std::swap(n_str[dot_idx], n_str[dot_idx + 1]);

	return n_str;
}


std::string get_next_element(const S_state_type_t& state)
{
	auto prod = std::get<1>(state);
	auto m_index = prod.find(Earley::dot);
	std::string nxt(1, prod.at(m_index + 1));

	if (is_nonterminal(nxt) || is_terminal(nxt))
		return nxt; // return the thing(char) that comes just after the Earley::dot

	return prod.substr(m_index + 1, prod.size() - m_index); // return the latter portion of the string (everything after the Earley::dot)
}


bool predict(S_type_t& S, const int k, const std::string& elem, S_state_type_t& state, const std::string& words)
{
	return true;
}


bool scan(S_type_t& S, const int k, S_state_type_t& state, const std::string& words)
{
	return true;
}


bool complete(S_type_t& S, const int k, S_state_type_t& state)
{
	S.emplace_back(S_set_type_t{ std::make_tuple("ABC", "123", 0) });
	return true;
}


bool earley_parse(const std::string& words, const S_grammar_type_t& grammar)
{
	std::string start_p = "S";
	start_p += Earley::dot;
	S_state_type_t expected = std::make_tuple("P",start_p,0);

	S_type_t S = init(words.size());
	bool done = false;
	for (unsigned int k = 0; k < words.size() + 1; ++k)
	{
		bool added = true;
		if (done)
			break;

		while (added)
		{
			added = false;

			Earley::S_set_type_t c_set = S[k];
			for (Earley::S_state_type_t state : S[k])
			{
				auto end_set = S[S.size() - 1];
				if (end_set.find(expected) != end_set.end())
				{
					done = true;
					break;
				}

				if (!is_finished(state))
				{
					auto nxt_elem = get_next_element(state);

					if (is_nonterminal(nxt_elem))
					{
						added = predict(S, k, nxt_elem, state, words);
					}
					else
					{
						added = scan(S, k, state, words);
					}
				}
				else
				{
					added = complete(S, k, state);
				}
			}
		}
	}

	return true;
}


std::vector<std::string> split(const std::string& strng, const char delim)
{
	std::vector<std::string> retvec;
	return retvec;
}


std::vector<std::string> load_grammar(const std::string& location)
{
	std::ifstream iff(location.c_str(), std::ios::in);
	std::vector<std::string> mvec;

	if (iff.is_open())
	{
		while (iff)
		{
			std::string holder;
			std::getline(iff, holder);
			mvec.push_back(holder);
		}
		mvec.pop_back();
		mvec.shrink_to_fit();
		iff.close();
	}

	return mvec;
}


S_grammar_type_t process_grammar(const std::vector<std::string>& gramm_raw)
{
	S_grammar_type_t gramm_struct;

	for (auto& prod : gramm_raw)
	{
		std::smatch match_results;
		std::regex prod_regex("^(.*)\\s->\\s(.*)$");
		std::regex_match(prod, match_results, prod_regex);

		std::string prod_name = match_results[1];
		std::string prod_value = match_results[2];

		gramm_struct.insert(std::make_pair(prod_name, prod_value));
	}

	return gramm_struct;
}


int main(int argc, char*argv[])
{
	return 0;
}
