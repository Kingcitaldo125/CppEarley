#pragma once


#include <set>
#include <string>
#include <sstream>
#include <map>
#include <tuple>
#include <list>
#include <vector>


namespace Earley
{
	/*
	'S_state_type_t' contains:
	1. The LHS of the production ('P')
	2. The RHS of the production ('S', 'S + M', 'M')
	3. The state number where that particular cell/item originated from (Origin)
	*/
	using S_state_type_t = std::tuple<std::string, std::string, int>;
	using S_set_type_t = std::list<S_state_type_t>;
	using S_type_t = std::vector<S_set_type_t>;
	using S_grammar_type_t = std::map<std::string, std::string>;

	const char dot = '`';
	const std::string prod_split = " | ";
	const std::set<char> nonterminals{ 'P', 'S', 'M', 'T' };
	const std::set<char> parts_of_speech{ '+', '*', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

	inline std::string state_string(const S_state_type_t& m_state)
	{
		std::stringstream ss;
		ss << ::std::get<0>(m_state) << "," << ::std::get<1>(m_state) << "," << ::std::get<2>(m_state);
		return ss.str();
	}
}
