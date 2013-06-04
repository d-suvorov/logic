#pragma once

#include "syntax_tree.h"
#include <vector>

namespace proof_utils {

void init_axioms();
void print(std::ostream& out, std::vector<node*> const& proof,
           std::vector<node*> const& gamma = std::vector<node*>());
std::vector<node*> deduction(std::vector<node*>& gamma, node* alpha, node* beta,
                             std::vector<node*>& proof);
std::vector<node*> prove(node* formula);
}
