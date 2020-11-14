<div align="center">

# AI_8puzzle
### Istanbul University - Cerrahpasa Computer Engineering Department 
#### Artifical Intelligence TERM PROJECTS – Assignment 1 Fall 2020-2021

</div>

###### In this project you will use uninformed search methods to solve an 8-puzzle


- Consists of a 3x3 board with 8 numbered tiles and a blank space.
- A tile adjacent to the blank space can slide into the space.
- The object is to reach a specified goal state, such as the one shown on the right.

Implement an agent to solve an 8-puzzle with the following search methods: 
1. Breadth-first
2. Depth-first
3. Depth limited (depth limit must be an argument, try different depth limits) 
3. Iterative deepening search



# HOW TO RUN
###### Compile file, must add compiler flag -std=c++17
**g++ -o m main.cpp -std=c++17**

##### There is 3 option to run file. 
1. Default one : **./m**
2. Pass 1 Argument to Run DFS and BFS on your 8puzzle: **./m "\<board_state>**
3. Pass 2 Argument to Run DFS,BFS,DLS and Iterative Deepening Search: **./m \<board_state> \<depth>**


