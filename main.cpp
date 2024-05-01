#include <iostream>
#include <stack>
#include <algorithm>
#include <set>
#include <map>
#include <list>

using namespace std;

std::string reverseString(std::string input);

list<int> topological_sort (vector<vector<int>> graph, int n);


std::string reverseStringInPlace(std::string input);


list<string> getFunctionOrder(std::map<std::string, std::set<std::string>> dependencies);

int main() {
    std::cout << "Hello, World!" << std::endl;

    std::string reversedString = reverseString("ABCD");
    std::cout << "Reversed String: " << reversedString << std::endl;
    std::cout << "****************" << std::endl;

    std::cout << reverseStringInPlace("ABCDEF") << std::endl;
    std::cout << reverseStringInPlace("ABCDE") << std::endl;
    std::string input = "ABCDE";
    std::reverse(input.begin(), input.end());
    std::cout << "using std lib: "<< input << std::endl;

    //"ABCDEF" even  "ABCDE"
    // 012345         01234   //5/2 = 2
    // swap(A,F)

    /**
     * Takes a map of function dependencies and generates a list of functions in the order in
     * which they must be instantiated.
     *
     * Function depends on another if the other function is called in its body.
     * Function must be instantiated before all its dependencies.
     *
     * If it is not possible to find a suitable function order, the function should throw
     * the std::logic_error exception.
     */

    std::map<std::string, std::set<std::string>> mapInput = {
            {"foo", {"bar"}},
            {"bar", {"baz", "toot"}},
            {"baz", {}},
            {"toot", {"baz"}},
    };

    list<string> topSortNamed = getFunctionOrder(mapInput);
    cout << "Topological sort result: " << endl;
    for (string cur: topSortNamed) {
        cout << cur << " " ;
    }
    cout << endl;





    return 0;
}

void dfs_visit (vector<vector<int>> graph, int u, list<int> &ts, vector<bool> &visited) {
    int aux = graph[u].size();
    for (int i = 0; i < aux; i++) {
        int v = graph[u][i];
        if (!visited[v]) {
            visited[v] = true;
            dfs_visit(graph, v, ts, visited);
            ts.push_front(v);
        }
    }
}





std::string reverseString(std::string input) {
    // TODO: return the reversed string
    // example: input = "abc" -> return "cba"

    std::stack<char> letterStack;
    for (int i = 0; i < input.size(); i++) {
        letterStack.push(input[i]);
    }

    std::string result;

    while (!letterStack.empty()) {
        char cur = letterStack.top();
        letterStack.pop();
        result.push_back(cur);
    }

    return result;
}

std::string reverseStringInPlace(std::string input) {
    int stringSize = input.size();
    for (int i = 0; i < stringSize/2; i++) { //6/2 = 3
        int correspondentIndex = stringSize - i - 1;
        std::swap(input[i], input[correspondentIndex]);
    }
    return input;
}

list<int> topological_sort(vector<vector<int>> graph, int n) {
    list<int> ts;
    // int n = graph.size();
    vector<bool> visited(n, false);
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            visited[i] = true;
            dfs_visit(graph, i, ts, visited);
            ts.push_front(i);
        }
    }
    return ts;
}

list<string> getFunctionOrder(std::map<std::string, std::set<std::string>> dependencies) {

    vector<vector<int>> graph = vector<vector<int>>(dependencies.size(), vector<int>());
    int i = 0;
    map<string, int> stringToInt;
    map<int, string> intToString;
    for (auto it = dependencies.begin(); it != dependencies.end(); it++) {
        std::string curFunc = it->first;
        stringToInt.insert(pair<string,int>(curFunc, i));
        intToString.insert(pair<int, string>(i, curFunc));
        i++;
    }
    i = 0;
    for (auto it = dependencies.begin(); it != dependencies.end(); it++) {
        std::string curFunc = it->first;
        std::set<std::string> functions = it->second;

        for (std::string function : functions) {
            graph[stringToInt.at(function)].push_back(i);
        }
        i++;
    }

    list<int> topSort = topological_sort(graph, graph.size());
    list<string> topSortNamed;
    for (int cur: topSort) {
        topSortNamed.push_back(intToString.at(cur));
    }

    return topSortNamed;


}




