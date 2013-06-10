#include "syntax_tree.h"
#include <string>
#include <istream>
#include <sstream>

namespace parser {

namespace details {

enum token {
    LEFT = '(',  CONJUNCTION = '&', DISJUNCTION = '|',
    RIGHT = ')', NEGATION = '!',    IMPLICATION,
    VARIABLE,    END,               UNEXPECTED
};

std::istream *input;
token current;
char var_value;

token next_token() {
    char ch;
    do
    {
        if (!input->get(ch)) return END;
    }
    while (isspace(ch));

    switch (ch) {
    case '&':
    case '|':
    case '!':
    case '(':
    case ')':
        return current = token(ch);
    case '-':
        input->get(ch);
        if (ch == '>')
            return current = IMPLICATION;
        return UNEXPECTED;
    default:
        if (isalpha(ch)) {
            var_value = ch;
            return current = VARIABLE;
        }
        return current = UNEXPECTED;
    }
}

// read == is the first token of implication read
node* implication(bool read);

// all of these recursive functions read next token after
node* term(bool read) {
    if (!read)
        next_token();
    switch (current) {
    case LEFT:
    {
        node *result = implication(false);
        // assertion current == RIGHT
        next_token();
        return result;
    }
    case NEGATION:
    {
        node *result = new node(term(false), nullptr, ::NEGATION);
        return result;
    }
    case VARIABLE:
    {
        node *result = new node(nullptr, nullptr, ::VARIABLE, var_value);
        next_token();
        return result;
    }
    default:
        return nullptr; // error
    }
}

// todo: a bit of copy-and-paste here
node* conjunction(bool read) {
    node *left = term(read);
    if (current == CONJUNCTION) {
        return new node(left, conjunction(false), ::CONJUNCTION);
    }
    return left;
}

node* disjunction(bool read) {
    node *left = conjunction(read);
    if (current == DISJUNCTION) {
        return new node(left, disjunction(false), ::DISJUNCTION);
    }
    return left;
}

node* implication(bool read) {
    node *left = disjunction(read);
    if (current == IMPLICATION) {
        return new node(left, implication(false), ::IMPLICATION);
    }
    return left;
}

}


node* parse(std::istream *in) {
    using namespace details;
    input = in;
    next_token();
    if (current == END)
        return nullptr;
    return implication(true);
}

node* parse(std::string const& src) {
    return parse( new std::istringstream(src) );
}


}
