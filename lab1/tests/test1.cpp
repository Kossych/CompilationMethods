#include "../lib/Analyzer.h"

int main() {
    std::string str = "a+b";
    std::set<char> terms{'a', 'b', '+', '*'};
    std::set<char> nonterms{'B', 'T', 'M'};
    std::vector<char> nontermsSequence{'B', 'T', 'M'};
    std::map<char, std::vector<std::string>> rules{
        {'B', {"T+B", "T"}}, 
        {'T', {"M", "M*T"}}, 
        {'M', {"a", "b"}}};
    Analyzer Analyzer(Grammar(terms, nonterms, rules, nontermsSequence));
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