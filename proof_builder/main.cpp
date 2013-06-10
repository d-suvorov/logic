#include "syntax_tree.h"
#include "parser.h"
#include "proof_utils.h"

#include <iostream>
#include <fstream>
#include <string>

void solve_task_2_1(std::ifstream& in, std::ofstream& out) {

}

void solve_task_2_2(std::ifstream& in, std::ofstream& out) {
	using namespace proof_utils;
    print( out, prove(parser::parse(&in)) );
}

int main() {
	std::ifstream in("input.txt");
	std::ofstream out("output.txt");

	proof_utils::init_axioms();

    solve_task_2_2(in, out);



	return 0;
}
