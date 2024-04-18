#include "../lib/Analyzer.h"

int main() {
    std::string str = "(a+b*a)*(b*b+a*(a+b+a))";
    std::set<char> terms{'a', 'b', '+', '*', '!', '(', ')'};
    std::set<char> nonterms{'B', 'T', 'M', 'A'};
    std::map<char, std::vector<std::string>> rules{
        {'A', {"!B!"}},
        {'B', {"T", "T+B"}}, 
        {'T', {"M", "M*T"}}, 
        {'M', {"a", "b", "(B)"}}};
    Analyzer Analyzer(Grammar(terms, nonterms, rules));
    try{
    auto res = Analyzer.analyze(str);
    for(auto it: res) {
        std::cout<<(it);
    }
    std::cout<<std::endl;
    auto ruleIndexes = Analyzer.getRuleIndexes();
    for(auto it: ruleIndexes) {
        std::cout<<it.first<< ") " << it.second;
        std::cout<<std::endl;
    }
    } catch(std::string message) {
        std::cout<<message;
    }
}