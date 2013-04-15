#include "text_operations.h"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
// typedef std::vector<proof_item> proof

std::string suggestion;

enum premiss
{
    AXIOM, SUGGESTION, MODUS_PONENS
};

// single expression in a proof
struct proof_item
{
    std::string expr;
    premiss from;

    // expressions numbers used in modus ponens if from == MODUS_PONENS
    // num1 is an axiom number if from == AXIOM
    int num_1, num_2;

    proof_item(std::string ex, premiss fr, int n1 = -1, int n2 = -1)
        : expr(ex), from(fr), num_1(n1), num_2(n2) {}
};

std::vector<proof_item> input_proof, output_proof;

void print_proof(std::vector<proof_item> const& proof, std::ofstream& out)
{
    for (size_t i = 0; i < proof.size(); i++)
    {
        out << i << " ";
        switch (proof[i].from)
        {
        case AXIOM:
            out << "ax\t\t";
            break;
        case SUGGESTION:
            out << "sg\t\t";
            break;
        case MODUS_PONENS:
            out << "mp " << proof[i].num_1 << " " <<
                proof[i].num_2 << '\t';
            break;
        }
        out << proof[i].expr << std::endl;
    }
}

std::vector<proof_item> read_proof(int n, std::ifstream& in)
{
    std::vector<proof_item> result;
    std::string from, expr;
    int num_1, num_2;
    int tmp_num; char tmp;
    for (int i = 0; i < n; i++)
    {
        in >> tmp_num >> from;
        switch(from.at(0))
        {
        case 'a': // axiom
            getchar(); getchar();
            getline(in, expr);
            result.push_back( proof_item(expr, AXIOM) );
            break;
        case 's': // suggestion
            getchar(); getchar();
            getline(in, expr);
            result.push_back( proof_item(expr, SUGGESTION) );
            break;
        case 'm': // modus ponens
            in >> num_1 >> num_2;
            getchar();
            getline(in, expr);
            result.push_back( proof_item(expr, MODUS_PONENS, num_1, num_2) );
            break;
        }
    }

    return result;
}

void make_proof(std::string sgst, std::vector<proof_item> const& input,
        std::vector<proof_item>& output)
{
    std::vector<int> new_num; // number of expression in a new

    int curr_num = 0;
    for (std::vector<proof_item>::const_iterator i = input.begin(); i != input.end(); i++)
    {
        switch(i->from)
        {
        case AXIOM:
            output.push_back( proof_item(i->expr, AXIOM) );
            output.push_back( proof_item(first_axiom(i->expr, sgst), AXIOM) );
            output.push_back( proof_item(implication(sgst, i->expr), MODUS_PONENS,
                curr_num, curr_num + 1) );
            curr_num += 3;
            break;
        case SUGGESTION: // A -> A proof here
            output.push_back( proof_item(first_axiom(sgst, sgst), AXIOM) );
            output.push_back( proof_item(second_axiom(sgst, implication(sgst, sgst), sgst),
                AXIOM) );
            output.push_back( proof_item(second_axiom_end(sgst, implication(sgst, sgst), sgst),
                MODUS_PONENS, curr_num, curr_num + 1) );
            output.push_back( proof_item(first_axiom(sgst, implication(sgst, sgst)), AXIOM) );
            output.push_back( proof_item(implication(sgst, sgst), MODUS_PONENS,
                curr_num + 3, curr_num + 2) );
            curr_num += 5;
            break;
        case MODUS_PONENS:
            {
                int n1 = i->num_1; int n2 = i->num_2;
                output.push_back( proof_item(second_axiom(sgst, input[n1].expr, i->expr),
                    AXIOM) );
                output.push_back( proof_item(second_axiom_end(sgst, input[n1].expr, i->expr), MODUS_PONENS,
                    new_num[n1], curr_num) );
                output.push_back( proof_item(implication(sgst, i->expr), MODUS_PONENS,
                    new_num[n2], curr_num + 1) );
                curr_num += 3;
            }
            break;
        }

        new_num.push_back(curr_num - 1);
    }
}

int main()
{
    std::ifstream in("input.txt");
    std::ifstream out("output.txt");

    int n;
    std::string suggestion;
    in >> suggestion >> n;

    input_proof = read_proof(n, in);
    out << suggestion << " " << n << std::endl;
    return 0;
    make_proof(suggestion, input_proof, output_proof);
    print_proof(output_proof, out);

    return 0;
}
