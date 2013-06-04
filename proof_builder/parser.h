#pragma once

#include "syntax_tree.h"
#include <string>
#include <istream>

/*formal grammar:

implication: disjunction [ -> implication ]
disjunction: conjunction [ | disjunction ]
conjunction: term [ & conjunction ]
       term: (implication)
	         !term
			 variable
*/

namespace parser {

node* parse(std::istream* input);
node* parse(std::string const& src);

}
