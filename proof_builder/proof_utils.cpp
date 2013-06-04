#include "syntax_tree.h"
#include "parser.h"
#include <vector>

namespace proof_utils {

const int NUMBER_OF_AXIOMS = 10;
std::vector<node*> axioms;

const std::string str_axioms[NUMBER_OF_AXIOMS] = {
	"a->b->a",
	"(a->b)->(a->b->c)->(a->c)",
	"a->b->a&b",
	"a&b->a",
	"a&b->b",
	"a->a|b",
	"b->a|b",
	"(a->c)->(b->c)->(a|b->c)",
	"(a->b)->(a->!b)->!a",
	"!!a->a"
};

void init_axioms() {
	axioms.reserve(NUMBER_OF_AXIOMS);
	for (int i = 0; i < NUMBER_OF_AXIOMS; i++) {
		axioms.push_back( parser::parse(str_axioms[i]) );
	}
}

bool equals(node const* lhs, node const* rhs) {
	return false;
}

int no_of_axiom(node const* formula) {

	return -1;
}

void find_modus_ponens() {

}

void print(std::ostream& out, std::vector<node*> const& proof,
           std::vector<node*> const& gamma = std::vector<node*>()) {
	for (size_t i = 0; i < proof.size(); i++) {
		node *formula = proof[i];
		//out << i + 1 << "\t" <<
	}
}

std::vector<node*> deduction(std::vector<node*>& gamma, node* alpha, node* beta,
                             std::vector<node*>& proof) {
	std::vector<node*> result;
	return result;
}

std::vector<node*> prove(node* formula) {
	std::vector<node*> result;
	return result;
}

}
