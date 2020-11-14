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
    std::array<int, 9> currentState;
    const std::array<int, 9> goalState {0,1,2,3,4,5,6,7,8};
    long long nodesExpanded = 0;
    long long maximumSizeOfFringe = 0;
    
    
    std::array<int, 9> move(std::array<int, 9> currentState, int direction);
    std::vector<std::array<int, 9>> moveAllDirection(std::array<int, 9> currentState);
    std::string transformArrayToString(std::array<int,  9> arr);
    
public:
    _8puzzle():currentState{7,2,4,5,0,6,8,3,1}{
    }
    
    _8puzzle(const char * argv){
        int index = 0;
        for (; argv[index] != '\0'; ++index) {
        }
        
        assert(index-1 == 8 && "invalid argument");
        
        index = 0;
        
        for(; index < 9; ++index){
            currentState[index] = argv[index] - '0';
        }
        
    }
    

    void DFS();
    
    void BFS();
    
    // TODO:: implement Depth Limited Search
    std::array<int, 9> DLS();
    
    // TODO:: implement iterative deepening search
    std::array<int, 9> IDS();
    

    void randomProblemGenerator();
    
    
    friend std::ostream &operator<<(std::ostream &output,const _8puzzle &puzz){
        for (auto &ii : puzz.currentState) {
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
 
    
    if(argc == 2){
        _8puzzle p(argv[1]);
        p.DFS();
        p.BFS();
    }
    if(argc == 3){
        _8puzzle p(argv[1]);
        p.BFS();
    }
    
    return 0;
}


// -----------------------------------------PUBLIC MEMBER FUNCTIONS---------------------------------------------------

void _8puzzle::BFS(){
    std::deque<std::array<int, 9>> q;
    std::unordered_set<std::string> set; // keep visited list
    bool solutionFind = false;
    
    q.push_front(this->currentState);
    
    while (!q.empty()) {
        std::array<int, 9> m = q.back();
        q.pop_back();
        
        set.insert(transformArrayToString(m));
        if(std::equal(std::begin(m), std::end(m), std::begin(goalState))){
            solutionFind = true;
            break;
        }
        
        auto possiblePaths = moveAllDirection(m);
        
        // possible path is not in set so add in queue
        for(auto& i: possiblePaths){
            std::string temp = transformArrayToString(i);
            if(set.find(temp) == set.end()){
                q.push_front(i);
                set.insert(transformArrayToString(i));
                
            }
        }
        
        if(this->maximumSizeOfFringe < q.size())
            maximumSizeOfFringe = q.size();
    }
    
    std::cout << (solutionFind ? "Solution find for ": " Solution not find for ") << *this <<  " Nodes expanded: " << nodesExpanded << " Maximum Size of Fringe: " << maximumSizeOfFringe << "\n";
    nodesExpanded = 0;
    maximumSizeOfFringe = 0;
}




void _8puzzle::DFS(){
    std::stack<std::array<int, 9>> s;
    std::unordered_set<std::string> set; // keep visited list
    bool solutionFind = false;
    
    s.push(this->currentState);
    
    while (!s.empty()) {
        std::array<int, 9> m = s.top();
        s.pop();
        
        set.insert(transformArrayToString(m));
        if(std::equal(std::begin(m), std::end(m), std::begin(goalState))){
            solutionFind = true;
            break;
        }
        
        auto possiblePaths = moveAllDirection(m);
         std::reverse(possiblePaths.begin(), possiblePaths.end());
        // possible path is not in set so add in stack
        for(auto& i: possiblePaths){
            std::string temp = transformArrayToString(i);
            if(set.find(temp) == set.end()){
                s.push(i);
                set.insert(transformArrayToString(i));
                
            }
        }
        if(this->maximumSizeOfFringe < s.size())
            maximumSizeOfFringe = s.size();
    }
    
    std::cout << (solutionFind ? "Solution find for ": " Solution not find for ") << *this <<  " Nodes expanded: " << nodesExpanded << " Maximum Size of Fringe: " << maximumSizeOfFringe << "\n";
    nodesExpanded = 0;
    maximumSizeOfFringe = 0;
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
    
    this->currentState = m;
}




// -----------------------------------------PRIVATE MEMBER FUNCTIONS---------------------------------------------------

std::array<int, 9> _8puzzle::move(std::array<int, 9> currentState, int direction){
    std::array<int, 9> m(currentState);
    auto it = std::find(currentState.begin(), currentState.end(), 0);
    auto index = it - currentState.begin();
    
    assert(direction > 0 && direction < 5 && "INVALID MOVE");
    
    switch (direction) {
        case 1: // up
            if(index > 2){
                std::swap(m[index], m[index-3]);
            }
            return m;
            
        case 2: // down
            if(index < 6){
                std::swap(m[index], m[index+3]);
            }
            return m;
            
        case 3: // left
            if(index % 3 > 0){
                std::swap(m[index], m[index-1]);
            }
            return m;
        case 4: // right
            if(index % 3 < 2){
                std::swap(m[index], m[index+1]);
            }
            return m;
            
        default:
            break;
    }
    
    return m;
}




std::vector<std::array<int, 9>> _8puzzle::moveAllDirection(std::array<int, 9> currentState){
    // expand nodes
    std::vector<std::array<int, 9>> paths;
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

