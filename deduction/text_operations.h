#ifndef H_TEXT_OPERATIONS
#define H_TEXT_OPERATIONS

#include <string>

// surrounds expr with brackets
std::string br(std::string const& expr);

std::string implication(std::string const& a, std::string const& b);

std::string first_axiom(std::string const& a, std::string const& b);
std::string second_axiom_end(std::string const& a, std::string const& b,
		std::string const& c);
std::string second_axiom(std::string const& a, std::string const& b,
		std::string const& c);

#endif