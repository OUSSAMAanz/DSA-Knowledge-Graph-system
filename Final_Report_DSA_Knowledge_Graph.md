# Data Structures and Algorithms Final Report
## DSA Knowledge Graph Implementation

**Course:** Data Structures and Algorithms  
**Student:** OUSSAMA ANEZHA   
**Programming Language:** C++

---

## 1. Problem Description

This report implements a DSA Knowledge Graph system that connects various data structures and algorithms. The system includes:

- **Linear Data Structures**: Stack (LIFO), Queue (FIFO), Array operations
- **Hierarchical Data Structures**: Binary Tree, AVL Tree (self-balancing)
- **Graph Operations**: BFS, DFS traversal algorithms
- **Sorting Algorithms**: Bubble Sort, Merge Sort, Quick Sort
- **Search Algorithms**: Linear Search, Binary Search
- **Knowledge Graph**: Search functionality with concept relationships

**Search Function Example**: Input "stack" → Output: Linear Data Structure, operations include push(), pop(), peek(), isEmpty()

## 2. Data Structure and Algorithm Design

The system uses template-based C++ classes with smart pointer memory management:

**Linear Structures:**
- Stack: LIFO operations using linked list
- Queue: FIFO operations with front/rear pointers

**Hierarchical Structures:**
- Binary Tree: Basic insertion and search
- AVL Tree: Self-balancing with rotations

**Graph Algorithms:**
- BFS: Uses queue for level-order traversal
- DFS: Uses stack for deep exploration

**Knowledge Graph:**
- Stores concepts with complexity information
- Maps relationships between data structures

---

## 3. Implementation

The system is implemented code including:

**Key Classes:**
```cpp
template<typename T> class Stack    
template<typename T> class Queue      
template<typename T> class AVLTree  
template<typename T> class Graph    
class DSAKnowledgeGraph            
```

**Core Algorithms:**
- **Merge Sort**: O(n log n) divide-and-conquer sorting
- **Binary Search**: O(log n) search in sorted arrays
- **BFS/DFS**: O(V + E) graph traversal algorithms
- **Dijkstra**: Shortest path algorithm using priority queue

**Knowledge Graph Search:**
```cpp
vector<string> searchConcepts(const string& query) {
    
}
```

---

## 4. Experiment Result and Analysis

**Testing Results:**

**Stack Operations:**
```
Pushed: 1, 2, 3, 4, 5
Stack size: 5
Popped: 5
Top element: 4
```

**Sorting Performance:**
```
Original array: [64, 34, 25, 12, 22, 11, 90]
Bubble sort result: [11, 12, 22, 25, 34, 64, 90]
Merge sort result: [11, 12, 22, 25, 34, 64, 90]
```

**Graph Traversal:**
```
BFS from A: [A, B, C, D]
DFS from A: [A, C, D, B]
```

**Knowledge Graph Search:**
```
Input: "tree"
Output: 2 concepts found
- AVL Tree: Self-balancing binary search tree
- Binary Tree: Tree where each node has at most two children
```

**Performance Analysis:**

| Data Structure | Time Complexity | Space Complexity |
|---------------|-----------------|------------------|
| Stack         | Push/Pop: O(1)  | O(n)            |
| Queue         | Enqueue/Dequeue: O(1) | O(n)     |
| AVL Tree      | Search/Insert: O(log n) | O(n)   |
| Binary Search | O(log n)        | O(1)            |
| Merge Sort    | O(n log n)      | O(n)            |

---

## 5. Conclusion

This project successfully implemented a DSA Knowledge Graph system that meets all teacher requirements:

**Achievements:**
- ✅ **Linear Data Structures**: Stack, Queue with O(1) operations
- ✅ **Hierarchical Structures**: Binary Tree, AVL Tree with self-balancing
- ✅ **Graph Algorithms**: BFS, DFS traversal implementations
- ✅ **Sorting Algorithms**: Bubble Sort, Merge Sort, Quick Sort
- ✅ **Search Functionality**: "Input = stack, output = linear structure, operations include push, pop, top"
- ✅ **Knowledge Graph**: Concept storage and relationship mapping
- ✅ **Original Implementation**: 877 lines of C++ code written from scratch

**Technical Results:**
- All algorithms achieve expected time complexity bounds
- Knowledge graph successfully connects related DSA concepts
- Search functionality returns accurate concept information
- System demonstrates practical understanding of data structures

**Educational Value:**
The knowledge graph approach effectively shows relationships between DSA concepts, helping understand how Stack uses Array, AVL Tree extends Binary Tree, and BFS uses Queue while DFS uses Stack.

---

## How to Run the Program

**Method 1: Using CMake (Recommended)**
```bash
mkdir build
cd build
cmake ..
cmake --build .
./dsa_knowledge_graph
```

**Method 2: Direct Compilation**
```bash
g++ -std=c++14 -o dsa_knowledge_graph dsa_knowledge_graph.cpp
./dsa_knowledge_graph
```

**About CMakeLists.txt:**
The CMakeLists.txt file is a build configuration that:
- Sets C++14 standard required for template features
- Handles cross-platform compilation (Windows/Linux/Mac)
- Adds compiler warnings for code quality
- Creates portable build system that works on any machine with CMake installed

**Step 3: View the Knowledge Graph**
- The program generates `knowledge_graph.json` and `visualization.html`
- Open `visualization.html` in any web browser
- Interactive graph shows DSA concepts and their relationships
- Click nodes to see details, use filters to explore specific categories

**Expected Output:**
- Console displays test results for all data structures
- Graph visualization opens in browser showing connected DSA concepts
- Search functionality allows querying concepts (e.g., "stack" → "LIFO operations")

---

**Files Submitted:**
- `Final_Report_DSA_Knowledge_Graph.md` - This report
- `dsa_knowledge_graph.cpp` - Complete C++ implementation
- `CMakeLists.txt` - Build configuration
