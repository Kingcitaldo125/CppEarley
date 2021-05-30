#include <iostream>
#include <sstream>
#include <string>
#include <regex>

#include "grammar.h"


using std::cout;
using std::endl;

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
	std::string prod = std::get<1>(state);

	cout << "Prod " << prod << endl;
	cout << "Prod Size " << prod.size() << endl;
	cout << "DotPos " << prod.find(Earley::dot) << endl;

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


std::vector<std::string> split(const std::string& strng, const char delim)
{
	std::vector<std::string> retvec;
	std::stringstream ss(strng);
	std::string holder;

	while (ss)
	{
		std::getline(ss, holder, delim);
		retvec.push_back(holder);
	}
	retvec.pop_back(); // take out the final, extra, element

	return retvec;
}


std::vector<std::string> prod_split(const std::string& strng)
{
	std::vector<std::string> retvec;

	std::smatch match_results;
	std::regex prod_regex("^(.+)\\s[|]\\s(.+)$");

	std::regex_match(strng, match_results, prod_regex);

	for (std::smatch::iterator it = match_results.begin() + 1; it != match_results.end(); ++it)
	{
		retvec.push_back(*it);
	}

	return retvec;
}


bool predict(S_type_t& S, const int k, const std::string& nxt_elem, S_grammar_type_t& grammar)
{
	bool added = false;
	std::string nxt_production = nxt_elem;
	std::string grammar_prod = grammar[nxt_production];
	auto splits = prod_split(grammar_prod);

	for (auto& split : splits)
	{
		std::stringstream ss;
		std::string split_nows = std::regex_replace(split, std::regex("\\s"), "");

		ss << Earley::dot;
		ss << split_nows;

		std::string dSplit(ss.str());
		Earley::S_set_type_t& current_set = S[k];
		S_state_type_t set_element = std::make_tuple(nxt_production, dSplit, 0);

		// if not found: insert the tuple(set_element)
		if (current_set.find(set_element) == current_set.end())
		{
			current_set.insert(set_element);
			added = true;
		}
	}

	return added;
}


bool scan(S_type_t& S, const int k, S_state_type_t& state, const std::string& words)
{
	bool added = false;
	return added;
}


bool complete(S_type_t& S, const int k, S_state_type_t& state)
{
	bool added = false;
	return added;
}


bool earley_parse(const std::string& words, const S_grammar_type_t& grammar)
{
	std::string start_p = "S";
	start_p += Earley::dot;
	S_state_type_t expected = std::make_tuple("P", start_p, 0);

	S_type_t S = init(words.size());
	{
		std::string sp(1, Earley::dot);
		sp += "S";
		S[0].insert(std::make_tuple("P", sp, 0));
	}
	bool done = false;

	for (unsigned int k = 0; k < words.size(); ++k)
	{
		bool added = true;
		if (done)
			break;

		while (added)
		{
			added = false;

			for (Earley::S_state_type_t state : S[k])
			{
				auto end_set = S[S.size() - 1];
				if (end_set.find(expected) != end_set.end())
				{
					done = true;
					cout << "done.\n";
					break;
				}

				bool finished = is_finished(state);
				if (!finished)
				{
					auto nxt_elem = get_next_element(state);

					if (is_nonterminal(nxt_elem))
					{
						added = predict(S, k, nxt_elem, const_cast<S_grammar_type_t&>(grammar));
						if (added)
							cout << "Predicted and added to set\n";
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


int main(int argc, char*argv[])
{
	std::vector<std::string> loaded_gramm = load_grammar(".\\grammars\\grammar.txt");
	const std::string words("1+2+3");
	auto grammar = process_grammar(loaded_gramm);

	cout << std::boolalpha << earley_parse(words, grammar) << endl;

	cout << "Hello_World\n";
	
	return 0;
}
