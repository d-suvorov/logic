#include "syntax_tree.h"
#include "parser.h"
#include <vector>
#include <string>

namespace proof_utils {

const std::string AXIMOM_REF = "axiom ";
const std::string MODUS_PONENS_REF = "m.p. ";
const std::string SUGGEST_REF = "suggested";

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

void diff(node* lhs, node* rhs, std::map<char, node*>& chg) {
    if (lhs == nullptr && rhs == nullptr)
        return;
    if (rhs->left == nullptr) { // rhs is variable
        chg.insert( std::pair<char, node*>(rhs->variable, lhs) );
        return;
    }
    if (lhs->operation != rhs->operation)
        return;
    diff(lhs->left, rhs->left, chg);
    diff(lhs->right, rhs->right, chg);
}

int no_of_axiom(node* formula) {
    std::map<char, node*> chg;
    node *axiom;
    for (size_t i = 0; i < axioms.size(); i++) {
        chg.clear();
        axiom = axioms[i];
        diff(formula, axiom, chg);
        if (formula->equals( axiom->change(chg) ))
            return i;
    }
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
