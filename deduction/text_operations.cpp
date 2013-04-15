#include "text_operations.h"

#include <string>

// surrounds expr with brackets
std::string br(std::string const& expr)
{
	return expr.size() > 1 ? "(" + expr + ")" : expr;
}

std::string implication(std::string const& a, std::string const& b)
{
	return br(a) + " -> " + br(b);
}

std::string first_axiom(std::string const& a, std::string const& b)
{
	return br(a) + " -> (" + implication(b, a) + ")";
}

std::string second_axiom_end(std::string const& a, std::string const& b,
		std::string const& c)
{
	return "(" + br(a) + " -> (" + br(b) + " -> " + br(c) + ")) -> "
			"(" + implication(a, c) + ")";
}

std::string second_axiom(std::string const& a, std::string const& b,
		std::string const& c)
{
	return "(" + implication(a, b) + ") -> (" + second_axiom_end(a, b, c) + ")";
}

void trim_leading_whitespaces(std::string& src)
{
    static const std::string whitespaces = " \t";
    size_t pos = src.find_first_not_of(whitespaces);
    if (pos == std::string::npos)
        return;
    src.erase(0, pos);
}
