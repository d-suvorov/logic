#include "syntax_tree.h"
#include <string>

std::string get_string(logical_operation operation) {
	switch (operation) {
	case CONJUNCTION:
		return " & ";
	case DISJUNCTION:
		return " | ";
	case IMPLICATION:
        return " -> ";
	case NEGATION:
		return "!";
	default:
		return "";
	}
}

std::string node::to_string() const {
	if (operation == VARIABLE) {
		return std::string(1, variable);
	}
	if (operation == NEGATION) {
		return "!(" + left->to_string_impl() + ")";
	}
	return left->to_string_impl() + get_string(operation) +
	      right->to_string_impl();
}

std::string node::to_string_impl() const {
	if (operation == VARIABLE) {
		return std::string(1, variable);
	}
	if (operation == NEGATION) {
		return "!(" + left->to_string_impl() + ")";
	}
	return "(" + left->to_string_impl() + get_string(operation) +
	            right->to_string_impl() + ")";
}

node* node::change(std::map<char, node*> chg) const {
    if (left == nullptr)
        return chg[variable];
    return new node(left, right ? right->change(chg) : nullptr, operation, variable);
}

bool node::equals(node const* rhs) const {
	if (rhs == nullptr)
		return false;
	if (operation != rhs->operation || variable != rhs->variable)
		return false;
	if (left == nullptr && rhs->left != nullptr ||
	        left != nullptr && !(left == rhs->left))
		return false;
	if (right == nullptr && rhs->right != nullptr ||
	        right != nullptr && !(right == rhs->right))
		return false;
	return true;
}
