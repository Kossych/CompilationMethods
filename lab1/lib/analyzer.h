#pragma once

#include <map>
#include <string>
#include <set>
#include <vector>
#include <stack>
#include <iostream>
#include <algorithm>

struct Element;

struct Grammar {
    std::set<char> terms;
    std::set<char> nonterms;
    std::map<char, std::vector<std::string>> rules;

    Grammar();
    
    Grammar(std::set<char>, std::set<char>, std::map<char, std::vector<std::string>>);

    void addRule(char, std::string);
    int getIndex(Element);
    bool isNonTerm(char);
    std::map<int, std::string> getRuleIndexes();
};

struct Element {
    char symbol;
    int index;
    Element(char symbol, int index) {
        this->symbol = symbol;
        this->index = index;
    }
};

enum State {
    Action,
    Goto,
    Exit
};

class Analyzer {
    Grammar grammar;

    public:
        Analyzer(Grammar);

        void addRule(char, std::string);
        std::map<int, std::string> getRuleIndexes();
        std::vector<int> analyze(std::string);
    private:
        void popRule(std::stack<char>&, Element);
        void pushRule(std::stack<char>&, Element);
};