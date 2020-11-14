//
//  main.cpp
//  ai_8puzzle
//
//  Created by Berke Yavas on 14.11.2020.
//


#include <iostream>
#include <array>
#include <deque>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <random>
#include <stack>

class _8puzzle {
    // std::pair<std::array<int, 9>, int depth>
    std::pair<std::array<int, 9>, int> currentState;
    const std::array<int, 9> goalState {0,1,2,3,4,5,6,7,8};
    long long nodesExpanded = 0;
    long long maximumSizeOfFringe = 0;
    
    
    std::pair<std::array<int, 9>, int> move(std::pair<std::array<int, 9>, int>, int direction);
    std::vector<std::pair<std::array<int, 9>, int>> moveAllDirection(std::pair<std::array<int, 9>, int> currentState);
    std::string transformArrayToString(std::array<int,  9> arr);
    
public: // {7,2,4,5,0,6,8,3,1}
    _8puzzle():currentState(std::make_pair(std::array<int, 9> {7,2,4,5,0,6,8,3,1}, 0)){
    }
    
    _8puzzle(const char * argv){
        int index = 0;
        for (; argv[index] != '\0'; ++index) {
        }
        
        assert(index-1 == 8 && "invalid argument");
        
        index = 0;
        
        for(; index < 9; ++index){
            currentState.first[index] = argv[index] - '0';
        }
        
        currentState.second = 0;
        
    }
    

    void DFS();
    
    void BFS();
    
    void DLS(int depth, bool IDS = false);
    
    void IDS(int depth);
    

    void randomProblemGenerator();
    
    
    friend std::ostream &operator<<(std::ostream &output,const _8puzzle &puzz){
        for (auto &ii : puzz.currentState.first) {
            output << ii << " ";
        }
        return output;
    }
};




int main(int argc, const char * argv[]) {
    // insert code here...
    /*
    _8puzzle p;
    for(int i = 0; i < 10; i++){
        p.randomProblemGenerator();
        p.DFS();
    }
    */
    if(argc == 1){
        _8puzzle p;
        p.BFS();
        p.DFS();
        p.DLS(10);
        p.DLS(30);
        p.DLS(80);
        p.IDS(20);
        std::cout << "\n\n";
        for (int i = 0; i <= 10; ++i) {
            std::cout << "RANDOM PROBLEM NO: " << i << "\n";
            p.randomProblemGenerator();
            p.BFS();
            p.DFS();
            p.DLS(10);
            p.DLS(30);
            p.DLS(80);
            p.IDS(20);
            std::cout << "\n\n";
        }
    }
    
    if(argc == 2){
        _8puzzle p(argv[1]);
        p.DFS();
        p.BFS();
    }
    if(argc == 3){
        int depth = std::stoi(argv[2]);
        
        _8puzzle p(argv[1]);
        p.BFS();
        p.DFS();
        p.DLS(depth);
        p.IDS(depth);
    }
    
    return 0;
}


// -----------------------------------------PUBLIC MEMBER FUNCTIONS---------------------------------------------------

void _8puzzle::BFS(){
    std::deque<std::pair<std::array<int, 9>, int>> q; // queue for BFS
    std::unordered_set<std::string> set; // keep visited list
    bool solutionFind = false;
    int depth = -1;
    
    q.push_front(this->currentState);
    
    while (!q.empty()) {
        std::pair<std::array<int, 9>, int> m = q.back();
        q.pop_back();
        
        // check if goal state reached
        set.insert(transformArrayToString(m.first));
        if(std::equal(std::begin(m.first), std::end(m.first), std::begin(goalState))){
            solutionFind = true;
            depth = m.second;
            break;
        }
        
        // find next possible paths
        auto possiblePaths = moveAllDirection(m);
        
        // possible path is not in set so add in queue
        for(auto& i: possiblePaths){
            std::string temp = transformArrayToString(i.first);
            if(set.find(temp) == set.end()){
                q.push_front(i);
                set.insert(temp);
                
            }
        }
        
        // update maximum size of fridge if current stack size is bigger than previous
        if(this->maximumSizeOfFringe < q.size())
            maximumSizeOfFringe = q.size();
    }
    
    std::cout << (solutionFind ? "BFS Solution find for ": "BFS Solution not find for ") << *this <<  " Nodes expanded: " << nodesExpanded << " Maximum Size of Fringe: " << maximumSizeOfFringe << " Depth: " << depth << "\n";
    nodesExpanded = 0;
    maximumSizeOfFringe = 0;
}




void _8puzzle::DFS(){
    std::stack<std::pair<std::array<int, 9>, int>> s; // stack for DFS
    std::unordered_set<std::string> set; // keep visited list
    bool solutionFind = false;
    int depth = -1;
    
    s.push(this->currentState);
    
    while (!s.empty()) {
        std::pair<std::array<int, 9>, int> m = s.top();
        s.pop();
        
        // check if goal state reached
        set.insert(transformArrayToString(m.first));
        if(std::equal(std::begin(m.first), std::end(m.first), std::begin(goalState))){
            solutionFind = true;
            depth = m.second;
            break;
        }
        
        // find next possible paths
        auto possiblePaths = moveAllDirection(m);
         std::reverse(possiblePaths.begin(), possiblePaths.end());
        
        // possible path is not in set so add in stack
        for(auto& i: possiblePaths){
            std::string temp = transformArrayToString(i.first);
            if(set.find(temp) == set.end()){
                s.push(i);
                set.insert(transformArrayToString(i.first));
                
            }
        }
        
        // update maximum size of fridge if current stack size is bigger than previous
        if(this->maximumSizeOfFringe < s.size())
            maximumSizeOfFringe = s.size();
    }
    
    std::cout << (solutionFind ? "DFS Solution find for ": "DFS Solution not find for ") << *this <<  " Nodes expanded: " << nodesExpanded << " Maximum Size of Fringe: " << maximumSizeOfFringe << " Depth: " << depth << "\n";
    nodesExpanded = 0;
    maximumSizeOfFringe = 0;
}




void _8puzzle::DLS(int depth, bool IDS){
    std::stack<std::pair<std::array<int, 9>, int>> s; // stack for DFS
    std::unordered_set<std::string> set; // keep visited list
    bool solutionFind = false;
    
    s.push(this->currentState);
    
    while (!s.empty()) {
        std::pair<std::array<int, 9>, int> m = s.top();
        s.pop();
        /*
        // depth control part
        if(m.second - 1 >= depth){
            continue;
        }
        
        */
        
        // check if goal state reached
        set.insert(transformArrayToString(m.first));
        if(std::equal(std::begin(m.first), std::end(m.first), std::begin(goalState))){
            solutionFind = true;
            std::cout << (IDS ? "IDS":"DLS") << (solutionFind ? " Solution find for ": " Solution not find for ") << *this <<  " Nodes expanded:" << nodesExpanded << " Maximum Size of Fringe:" << maximumSizeOfFringe << " Depth:" << m.second << " Iterative Depth:" << depth << "\n";
            break;
        }
        
        // find next possible paths
        auto possiblePaths = moveAllDirection(m);
         std::reverse(possiblePaths.begin(), possiblePaths.end());
        
        // possible path is not in set so add in stack
        for(auto& i: possiblePaths){
            // depth control part
            if(i.second - 1 >= depth){
                continue;
            }
            
            std::string temp = transformArrayToString(i.first);
            if(set.find(temp) == set.end()){
                s.push(i);
                set.insert(transformArrayToString(i.first));
                
            }
        }
        
        // update maximum size of fridge if current stack size is bigger than previous
        if(this->maximumSizeOfFringe < s.size())
            maximumSizeOfFringe = s.size();
    }
    

    if(!solutionFind)
        std::cout << (IDS ? "IDS":"DLS") << " Solution not find for " << *this << " Depth: " << depth <<"\n";
    currentState.second = 0;
    nodesExpanded = 0;
    maximumSizeOfFringe = 0;
}


void _8puzzle::IDS(int depth){
    for(int i = 0; i <= depth; i++){
        DLS(i, true);
    }
}


void _8puzzle::randomProblemGenerator(){
    std::array<int, 9> m;
    int index = 0;
    
    // random number generator
    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_int_distribution<int> distribution(0,8);
    // keep list of randomed values
    std::unordered_set<int> s;
    
    // insert first number
    int randomNumber = distribution(generator);
    s.insert(randomNumber);
    m[index++] = randomNumber;
    
    // insert other numbers
    while(s.size() < 9){
        randomNumber = distribution(generator);
        if (s.find(randomNumber) == s.end()) {
            m[index++] = randomNumber;
            s.insert(randomNumber);
        }
    }
    
    this->currentState.first = m;
}




// -----------------------------------------PRIVATE MEMBER FUNCTIONS---------------------------------------------------

std::pair<std::array<int, 9>, int> _8puzzle::move(std::pair<std::array<int, 9>, int> currentState, int direction){
    std::pair<std::array<int, 9>, int> m(currentState);
    auto it = std::find(currentState.first.begin(), currentState.first.end(), 0);
    auto index = it - currentState.first.begin();
    m.second++;
    
    assert(direction > 0 && direction < 5 && "INVALID MOVE");
    
    switch (direction) {
        case 1: // up
            if(index > 2){
                std::swap(m.first[index], m.first[index-3]);
            }
            return m;
            
        case 2: // down
            if(index < 6){
                std::swap(m.first[index], m.first[index+3]);
            }
            return m;
            
        case 3: // left
            if(index % 3 > 0){
                std::swap(m.first[index], m.first[index-1]);
            }
            return m;
        case 4: // right
            if(index % 3 < 2){
                std::swap(m.first[index], m.first[index+1]);
            }
            return m;
            
        default:
            break;
    }
    
    return m;
}




std::vector<std::pair<std::array<int, 9>, int>> _8puzzle::moveAllDirection(std::pair<std::array<int, 9>, int> currentState){
    // expand nodes
    std::vector<std::pair<std::array<int, 9>, int>> paths;
    for (int i = 1; i != 5; i++) {
        auto arr = move(currentState, i);
        if(arr == currentState)
            continue;
        paths.push_back(arr);
    }
    
    // increment counter
    ++this->nodesExpanded;
    return paths;
}




std::string _8puzzle::transformArrayToString(std::array<int,  9> arr){
    std::string s;
    std::transform(arr.begin(), arr.end(), std::back_inserter(s), [](int const &i){
        return i  + '0';
    });
    return s;
}

