#include "../lib/parser.h"

int main() {
    std::string str = "a+b";
    std::set<char> terms{'a', 'b', '+', '*'};
    std::set<char> nonterms{'B', 'T', 'M'};
    std::map<char, std::vector<std::string>> rules{
        {'B', {"T+B", "T"}}, 
        {'T', {"M", "M*T"}}, 
        {'M', {"a", "b"}}};
    Parser parser(Grammar(terms, nonterms, rules));
    try{
    auto res = parser.analyze(str);
    for(auto it: res) {
        std::cout<<(it);
    }
    std::cout<<std::endl;
    auto ruleIndexes = parser.getRuleIndexes();
    for(auto it: ruleIndexes) {
        std::cout<<it.first<< ") " << it.second;
        std::cout<<std::endl;
    }
    } catch(std::string message) {
        std::cout<<message;
    }
}