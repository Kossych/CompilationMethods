#include "../lib/Analyzer.h"

Grammar::Grammar() {
    
}

Grammar::Grammar(std::set<char> terms, std::set<char> nonterms, std::map<char, std::vector<std::string>> rules) {
    this->terms = terms;
    this->nonterms = nonterms;
    this->rules = rules;
}

void Grammar::addRule(char from, std::string to) {
    this->rules[from].push_back(to);
}

int Grammar::getIndex(Element elem) {
    if(elem.index == -1) return -1;
    int index = elem.index + 1;
    for(auto nonterm: nonterms) {
        if(nonterm == elem.symbol) {
            return index;
        }
        index += rules[nonterm].size();
    }
    throw "Not find rule for given term";
}

bool Grammar::isNonTerm(char symbol) {
    for(auto it: nonterms) {
        if(it == symbol) return true;
    }
    for(auto it: terms) {
        if(it == symbol) return false;
    }
    throw "Given symbol is not in the grammar";
}

std::map<int, std::string> Grammar::getRuleIndexes() {
    std::map<int, std::string> ruleIndexes{};
    int index = 1;
    for(auto rule: rules) {
        for(auto alternative: rule.second) {
            std::string ruleStr = "";
            ruleStr+=rule.first;
            ruleStr+=(" = " + alternative);
            ruleIndexes[index] = ruleStr;
            index++;
        }
    }
    return ruleIndexes;
}

std::map<int, std::string> Analyzer::getRuleIndexes() {
    return grammar.getRuleIndexes();
}

Analyzer::Analyzer(Grammar grammar) {
    this->grammar = grammar;
}

void Analyzer::addRule(char from, std::string to) {
    this->grammar.addRule(from, to);
}

std::vector<int> Analyzer::analyze(std::string str) {
    std::stack<Element> l1{};
    std::stack<char> l2{};
    l2.push((*(grammar.rules.begin())).first);
    State state = Action;
    int i = 0;
    int strLength = str.length();
    while(true) {
        switch (state) {
            case Action:
            {
                if(i == strLength) {
                    if(l2.size() == 0) { // step 3
                        state = Exit;
                        break;
                    } else { // step 3'
                        state = Goto;
                        break;
                    }
                }
                auto nonterm = l2.top();
                if(grammar.isNonTerm(nonterm)){ //step 1
                    l2.pop();
                    l1.push(Element(nonterm, 0));
                    pushRule(l2, l1.top());
                    break;
                }
            
                char symbol = l2.top();
                if(str[i] == symbol) { // step 2
                    i++;
                    l1.push(Element(symbol, -1));
                    l2.pop();
                    break;
                } else { // step 4
                    state = Goto;
                    break;
                }
            }
            case Goto: 
            {
                if(!grammar.isNonTerm(l1.top().symbol)) { // step 5
                    i--;
                    l2.push(l1.top().symbol);
                    l1.pop();
                    break;
                }
                
                if(grammar.rules[l1.top().symbol].size() > (l1.top().index + 1)) { // step 6a
                    Element elem = l1.top();
                    popRule(l2, elem);
                    l1.pop();

                    elem.index++;
                    l1.push(elem);
                    pushRule(l2, elem);

                    state = Action;
                    break;
                } else {
                    if(i == 0) { // step 6b
                        throw "Couldn't find the output for given string";
                        break;
                    } else { // step 6c
                        popRule(l2, l1.top());
                        l2.push(l1.top().symbol);
                        l1.pop();
                        break;
                    }
                }
                break;
            }
            case Exit: 
            {
                std::vector<int> result;
                while(l1.size() != 0) {
                    int index = grammar.getIndex(l1.top());
                    l1.pop();
                    if(index == -1) continue;
                    result.push_back(index);
                }
                std::reverse(result.begin(), result.end());
                return result;
            }
        }
    }

}

void Analyzer::popRule(std::stack<char> &l2, Element elem) {
    std::string rule = grammar.rules[elem.symbol][elem.index];
    for(auto it: rule) {
        if(l2.top() != it) {
            throw "Trying to pop nonterminal when it's missing";
        }
        l2.pop();
    }
    return;
}

void Analyzer::pushRule(std::stack<char> &l2, Element elem) {
    std::string rule = grammar.rules[elem.symbol][elem.index];
    for(auto it = rule.rbegin(); it != rule.rend(); ++it) {
        l2.push(*it);
    }
}

void printStack(std::stack<char> l2) {
    std::cout<<"L2: ";
    while(l2.size() != 0) {
        std::cout << l2.top();
        l2.pop();
    }
    std::cout<<std::endl;
}
void printStack2(std::stack<Element> l1) {
    std::cout<<"L1: ";
    while(l1.size() != 0) {
        std::cout << l1.top().symbol;
        if(l1.top().index != -1) std::cout << l1.top().index;
        l1.pop();
    }
    std::cout<<std::endl;
}