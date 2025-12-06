#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <climits>
#include <memory>
#include <fstream>

using namespace std;


template<typename T>
class Node {
public:
    T data;
    shared_ptr<Node<T>> next;
    
    Node(T value) : data(value), next(nullptr) {}
};

template<typename T>
class Stack {
private:
    shared_ptr<Node<T>> top;
    int size;

public:
    Stack() : top(nullptr), size(0) {}
    
    void push(T data) {
        auto newNode = make_shared<Node<T>>(data);
        newNode->next = top;
        top = newNode;
        size++;
    }
    
    T pop() {
        if (isEmpty()) {
            throw runtime_error("Stack is empty");
        }
        T data = top->data;
        top = top->next;
        size--;
        return data;
    }
    
    T peek() const {
        if (isEmpty()) {
            throw runtime_error("Stack is empty");
        }
        return top->data;
    }
    
    bool isEmpty() const {
        return top == nullptr;
    }
    
    int getSize() const {
        return size;
    }
    
    void display() const {
        auto current = top;
        cout << "Stack (top to bottom): ";
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

template<typename T>
class Queue {
private:
    shared_ptr<Node<T>> front;
    shared_ptr<Node<T>> rear;
    int size;

public:
    Queue() : front(nullptr), rear(nullptr), size(0) {}
    
    void enqueue(T data) {
        auto newNode = make_shared<Node<T>>(data);
        if (rear) {
            rear->next = newNode;
        } else {
            front = newNode;
        }
        rear = newNode;
        size++;
    }
    
    T dequeue() {
        if (isEmpty()) {
            throw runtime_error("Queue is empty");
        }
        T data = front->data;
        front = front->next;
        if (!front) {
            rear = nullptr;
        }
        size--;
        return data;
    }
    
    T getFront() const {
        if (isEmpty()) {
            throw runtime_error("Queue is empty");
        }
        return front->data;
    }
    
    bool isEmpty() const {
        return front == nullptr;
    }
    
    int getSize() const {
        return size;
    }
    
    void display() const {
        auto current = front;
        cout << "Queue (front to rear): ";
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};


template<typename T>
class TreeNode {
public:
    T data;
    shared_ptr<TreeNode<T>> left;
    shared_ptr<TreeNode<T>> right;
    int height;
    
    TreeNode(T value) : data(value), left(nullptr), right(nullptr), height(1) {}
};

template<typename T>
class BinaryTree {
protected:
    shared_ptr<TreeNode<T>> root;
    
    void insertRecursive(shared_ptr<TreeNode<T>>& node, T data) {
        if (!node) {
            node = make_shared<TreeNode<T>>(data);
            return;
        }
        
        if (data < node->data) {
            insertRecursive(node->left, data);
        } else {
            insertRecursive(node->right, data);
        }
    }
    
    bool searchRecursive(shared_ptr<TreeNode<T>> node, T data) const {
        if (!node) return false;
        if (node->data == data) return true;
        if (data < node->data) return searchRecursive(node->left, data);
        return searchRecursive(node->right, data);
    }
    
    void inorderRecursive(shared_ptr<TreeNode<T>> node, vector<T>& result) const {
        if (node) {
            inorderRecursive(node->left, result);
            result.push_back(node->data);
            inorderRecursive(node->right, result);
        }
    }

public:
    BinaryTree() : root(nullptr) {}
    
    void insert(T data) {
        insertRecursive(root, data);
    }
    
    bool search(T data) const {
        return searchRecursive(root, data);
    }
    
    vector<T> inorderTraversal() const {
        vector<T> result;
        inorderRecursive(root, result);
        return result;
    }
    
    void display() const {
        auto result = inorderTraversal();
        cout << "Binary Tree (inorder): ";
        for (const auto& item : result) {
            cout << item << " ";
        }
        cout << endl;
    }
};

template<typename T>
class AVLTree : public BinaryTree<T> {
private:
    int getHeight(shared_ptr<TreeNode<T>> node) {
        return node ? node->height : 0;
    }
    
    int getBalance(shared_ptr<TreeNode<T>> node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }
    
    shared_ptr<TreeNode<T>> rotateRight(shared_ptr<TreeNode<T>> y) {
        auto x = y->left;
        auto T2 = x->right;
        
        x->right = y;
        y->left = T2;
        
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        
        return x;
    }
    
    shared_ptr<TreeNode<T>> rotateLeft(shared_ptr<TreeNode<T>> x) {
        auto y = x->right;
        auto T2 = y->left;
        
        y->left = x;
        x->right = T2;
        
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        
        return y;
    }
    
    shared_ptr<TreeNode<T>> insertAVL(shared_ptr<TreeNode<T>> node, T data) {
        if (!node) {
            return make_shared<TreeNode<T>>(data);
        }
        
        if (data < node->data) {
            node->left = insertAVL(node->left, data);
        } else if (data > node->data) {
            node->right = insertAVL(node->right, data);
        } else {
            return node; 
        }
        
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        
      
        int balance = getBalance(node);
        
        if (balance > 1 && data < node->left->data) {
            return rotateRight(node);
        }
        
        if (balance < -1 && data > node->right->data) {
            return rotateLeft(node);
        }
        
        if (balance > 1 && data > node->left->data) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        
        if (balance < -1 && data < node->right->data) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        
        return node;
    }

public:
    void insert(T data) override {
        this->root = insertAVL(this->root, data);
    }
};


template<typename T>
class Graph {
private:
    unordered_map<T, vector<pair<T, int>>> adjList;
    bool directed;

public:
    Graph(bool isDirected = false) : directed(isDirected) {}
    
    void addVertex(T vertex) {
        if (adjList.find(vertex) == adjList.end()) {
            adjList[vertex] = vector<pair<T, int>>();
        }
    }
    
    void addEdge(T u, T v, int weight = 1) {
        addVertex(u);
        addVertex(v);
        adjList[u].push_back({v, weight});
        if (!directed) {
            adjList[v].push_back({u, weight});
        }
    }
    
    vector<T> bfs(T start) {
        vector<T> result;
        unordered_set<T> visited;
        queue<T> q;
        
        q.push(start);
        visited.insert(start);
        
        while (!q.empty()) {
            T vertex = q.front();
            q.pop();
            result.push_back(vertex);
            
            for (const auto& neighbor : adjList[vertex]) {
                if (visited.find(neighbor.first) == visited.end()) {
                    visited.insert(neighbor.first);
                    q.push(neighbor.first);
                }
            }
        }
        
        return result;
    }
    
    vector<T> dfs(T start) {
        vector<T> result;
        unordered_set<T> visited;
        stack<T> s;
        
        s.push(start);
        
        while (!s.empty()) {
            T vertex = s.top();
            s.pop();
            
            if (visited.find(vertex) == visited.end()) {
                visited.insert(vertex);
                result.push_back(vertex);
                
                for (const auto& neighbor : adjList[vertex]) {
                    if (visited.find(neighbor.first) == visited.end()) {
                        s.push(neighbor.first);
                    }
                }
            }
        }
        
        return result;
    }
    
    unordered_map<T, int> dijkstra(T start) {
        unordered_map<T, int> distances;
        priority_queue<pair<int, T>, vector<pair<int, T>>, greater<pair<int, T>>> pq;
        unordered_set<T> visited;
        
        // Initialize distances
        for (const auto& vertex : adjList) {
            distances[vertex.first] = INT_MAX;
        }
        distances[start] = 0;
        pq.push({0, start});
        
        while (!pq.empty()) {
            int currentDist = pq.top().first;
            T currentVertex = pq.top().second;
            pq.pop();
            
            if (visited.find(currentVertex) != visited.end()) {
                continue;
            }
            
            visited.insert(currentVertex);
            
            for (const auto& neighbor : adjList[currentVertex]) {
                T neighborVertex = neighbor.first;
                int weight = neighbor.second;
                int distance = currentDist + weight;
                
                if (distance < distances[neighborVertex]) {
                    distances[neighborVertex] = distance;
                    pq.push({distance, neighborVertex});
                }
            }
        }
        
        return distances;
    }
    
    void display() {
        cout << "Graph adjacency list:" << endl;
        for (const auto& vertex : adjList) {
            cout << vertex.first << " -> ";
            for (const auto& neighbor : vertex.second) {
                cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
            }
            cout << endl;
        }
    }
};


class SortingAlgorithms {
public:
    static vector<int> bubbleSort(vector<int> arr) {
        int n = arr.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
        return arr;
    }
    
    static vector<int> selectionSort(vector<int> arr) {
        int n = arr.size();
        for (int i = 0; i < n - 1; i++) {
            int minIdx = i;
            for (int j = i + 1; j < n; j++) {
                if (arr[j] < arr[minIdx]) {
                    minIdx = j;
                }
            }
            swap(arr[i], arr[minIdx]);
        }
        return arr;
    }
    
    static vector<int> insertionSort(vector<int> arr) {
        int n = arr.size();
        for (int i = 1; i < n; i++) {
            int key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
        return arr;
    }
    
    static vector<int> mergeSort(vector<int> arr) {
        if (arr.size() <= 1) return arr;
        
        int mid = arr.size() / 2;
        vector<int> left(arr.begin(), arr.begin() + mid);
        vector<int> right(arr.begin() + mid, arr.end());
        
        left = mergeSort(left);
        right = mergeSort(right);
        
        return merge(left, right);
    }
    
    static vector<int> quickSort(vector<int> arr) {
        if (arr.size() <= 1) return arr;
        
        int pivot = arr[arr.size() / 2];
        vector<int> left, middle, right;
        
        for (int x : arr) {
            if (x < pivot) left.push_back(x);
            else if (x == pivot) middle.push_back(x);
            else right.push_back(x);
        }
        
        left = quickSort(left);
        right = quickSort(right);
        
        left.insert(left.end(), middle.begin(), middle.end());
        left.insert(left.end(), right.begin(), right.end());
        return left;
    }

private:
    static vector<int> merge(const vector<int>& left, const vector<int>& right) {
        vector<int> result;
        int i = 0, j = 0;
        
        while (i < left.size() && j < right.size()) {
            if (left[i] <= right[j]) {
                result.push_back(left[i++]);
            } else {
                result.push_back(right[j++]);
            }
        }
        
        while (i < left.size()) result.push_back(left[i++]);
        while (j < right.size()) result.push_back(right[j++]);
        
        return result;
    }
};



class SearchAlgorithms {
public:
    static int linearSearch(const vector<int>& arr, int target) {
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] == target) {
                return i;
            }
        }
        return -1;
    }
    
    static int binarySearch(const vector<int>& arr, int target) {
        int left = 0, right = arr.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] == target) {
                return mid;
            } else if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return -1;
    }
};



struct ConceptInfo {
    string type;
    string description;
    unordered_map<string, string> timeComplexity;
    string spaceComplexity;
};

class DSAKnowledgeGraph {
private:
    unordered_map<string, ConceptInfo> concepts;
    Graph<string> relationships;
    
    void initializeKnowledgeBase() {
        concepts["Array"] = {
            "Linear Data Structure",
            "A collection of elements stored at contiguous memory locations",
            {{"access", "O(1)"}, {"search", "O(n)"}, {"insertion", "O(n)"}, {"deletion", "O(n)"}},
            "O(n)"
        };
        
        concepts["Stack"] = {
            "Linear Data Structure",
            "LIFO (Last In First Out) data structure",
            {{"push", "O(1)"}, {"pop", "O(1)"}, {"peek", "O(1)"}},
            "O(n)"
        };
        
        concepts["Queue"] = {
            "Linear Data Structure",
            "FIFO (First In First Out) data structure",
            {{"enqueue", "O(1)"}, {"dequeue", "O(1)"}},
            "O(n)"
        };
        
        concepts["Binary Tree"] = {
            "Hierarchical Data Structure",
            "Tree data structure where each node has at most two children",
            {{"search", "O(n)"}, {"insertion", "O(n)"}, {"deletion", "O(n)"}},
            "O(n)"
        };
        
        concepts["AVL Tree"] = {
            "Hierarchical Data Structure",
            "Self-balancing binary search tree",
            {{"search", "O(log n)"}, {"insertion", "O(log n)"}, {"deletion", "O(log n)"}},
            "O(n)"
        };
        
        concepts["Graph"] = {
            "Non-linear Data Structure",
            "Collection of vertices connected by edges",
            {{"BFS", "O(V + E)"}, {"DFS", "O(V + E)"}, {"Dijkstra", "O((V + E) log V)"}},
            "O(V + E)"
        };
        
        concepts["Merge Sort"] = {
            "Sorting Algorithm",
            "Divide and conquer sorting algorithm",
            {{"best", "O(n log n)"}, {"average", "O(n log n)"}, {"worst", "O(n log n)"}},
            "O(n)"
        };
        
        concepts["Binary Search"] = {
            "Search Algorithm",
            "Search algorithm for sorted arrays using divide and conquer",
            {{"best", "O(1)"}, {"average", "O(log n)"}, {"worst", "O(log n)"}},
            "O(1)"
        };
        
        relationships.addEdge("Stack", "Array");
        relationships.addEdge("Queue", "Linked List");
        relationships.addEdge("Binary Search Tree", "Binary Tree");
        relationships.addEdge("AVL Tree", "Binary Search Tree");
        relationships.addEdge("Merge Sort", "Divide and Conquer");
        relationships.addEdge("Binary Search", "Sorted Array");
        relationships.addEdge("DFS", "Stack");
        relationships.addEdge("BFS", "Queue");
    }

public:
    DSAKnowledgeGraph() : relationships(true) {
        initializeKnowledgeBase();
    }
    
    vector<string> searchConcepts(const string& query) {
        vector<string> results;
        string lowerQuery = query;
        transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(), ::tolower);
        
        for (const auto& concept : concepts) {
            string lowerName = concept.first;
            string lowerDesc = concept.second.description;
            transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
            transform(lowerDesc.begin(), lowerDesc.end(), lowerDesc.begin(), ::tolower);
            
            if (lowerName.find(lowerQuery) != string::npos || 
                lowerDesc.find(lowerQuery) != string::npos) {
                results.push_back(concept.first);
            }
        }
        
        return results;
    }
    
    void displayConcept(const string& name) {
        if (concepts.find(name) != concepts.end()) {
            const auto& concept = concepts[name];
            cout << "\n=== " << name << " ===" << endl;
            cout << "Type: " << concept.type << endl;
            cout << "Description: " << concept.description << endl;
            cout << "Time Complexity: ";
            for (const auto& tc : concept.timeComplexity) {
                cout << tc.first << ": " << tc.second << " ";
            }
            cout << "\nSpace Complexity: " << concept.spaceComplexity << endl;
        }
    }
    
    void exportToGraphviz(const string& filename = "knowledge_graph.dot") {
        ofstream file(filename);
        file << "digraph KnowledgeGraph {" << endl;
        file << "    rankdir=TB;" << endl;
        file << "    node [shape=box, style=filled, fillcolor=lightblue];" << endl;
        
        for (const auto& concept : concepts) {
            file << "    \"" << concept.first << "\" [label=\"" << concept.first 
                 << "\\n" << concept.second.type << "\"];" << endl;
        }
        
        file << "    // Relationships" << endl;
        file << "    \"Stack\" -> \"Array\";" << endl;
        file << "    \"Queue\" -> \"Linked List\";" << endl;
        file << "    \"Binary Search Tree\" -> \"Binary Tree\";" << endl;
        file << "    \"AVL Tree\" -> \"Binary Search Tree\";" << endl;
        file << "    \"Merge Sort\" -> \"Divide and Conquer\";" << endl;
        file << "    \"Binary Search\" -> \"Sorted Array\";" << endl;
        file << "    \"DFS\" -> \"Stack\";" << endl;
        file << "    \"BFS\" -> \"Queue\";" << endl;
        
        file << "}" << endl;
        file.close();
        cout << "Knowledge graph exported to " << filename << endl;
        cout << "Use Graphviz to visualize: dot -Tpng " << filename << " -o knowledge_graph.png" << endl;
    }
    
    void exportToJSON(const string& filename = "knowledge_graph.json") {
        ofstream file(filename);
        file << "{" << endl;
        file << "  \"nodes\": [" << endl;
        
        bool first = true;
        for (const auto& concept : concepts) {
            if (!first) file << ",";
            file << "    {" << endl;
            file << "      \"id\": \"" << concept.first << "\"," << endl;
            file << "      \"label\": \"" << concept.first << "\"," << endl;
            file << "      \"type\": \"" << concept.second.type << "\"," << endl;
            file << "      \"description\": \"" << concept.second.description << "\"," << endl;
            file << "      \"spaceComplexity\": \"" << concept.second.spaceComplexity << "\"" << endl;
            file << "    }";
            first = false;
        }
        
        file << endl << "  ]," << endl;
        file << "  \"edges\": [" << endl;
        file << "    {\"from\": \"Stack\", \"to\": \"Array\"}," << endl;
        file << "    {\"from\": \"Queue\", \"to\": \"Linked List\"}," << endl;
        file << "    {\"from\": \"Binary Search Tree\", \"to\": \"Binary Tree\"}," << endl;
        file << "    {\"from\": \"AVL Tree\", \"to\": \"Binary Search Tree\"}," << endl;
        file << "    {\"from\": \"Merge Sort\", \"to\": \"Divide and Conquer\"}," << endl;
        file << "    {\"from\": \"Binary Search\", \"to\": \"Sorted Array\"}," << endl;
        file << "    {\"from\": \"DFS\", \"to\": \"Stack\"}," << endl;
        file << "    {\"from\": \"BFS\", \"to\": \"Queue\"}" << endl;
        file << "  ]" << endl;
        file << "}" << endl;
        file.close();
        cout << "Knowledge graph data exported to " << filename << endl;
    }

    void demonstrateAll() {
        cout << "\n=== DSA Knowledge Graph Demonstration ===" << endl;
        
        cout << "\n1. Stack Operations:" << endl;
        Stack<int> stack;
        for (int i = 1; i <= 5; i++) {
            stack.push(i);
            cout << "   Pushed: " << i << endl;
        }
        stack.display();
        cout << "   Popped: " << stack.pop() << endl;
        cout << "   Top element: " << stack.peek() << endl;
        
        cout << "\n2. Queue Operations:" << endl;
        Queue<int> queue;
        for (int i = 1; i <= 5; i++) {
            queue.enqueue(i);
            cout << "   Enqueued: " << i << endl;
        }
        queue.display();
        cout << "   Dequeued: " << queue.dequeue() << endl;
        cout << "   Front element: " << queue.getFront() << endl;
        
        cout << "\n3. Binary Tree Operations:" << endl;
        BinaryTree<int> bt;
        vector<int> treeData = {50, 30, 70, 20, 40, 60, 80};
        for (int item : treeData) {
            bt.insert(item);
        }
        cout << "   Inserted: ";
        for (int item : treeData) cout << item << " ";
        cout << endl;
        bt.display();
        cout << "   Search 40: " << (bt.search(40) ? "Found" : "Not Found") << endl;
        
        cout << "\n4. Graph Operations:" << endl;
        Graph<char> graph;
        vector<pair<char, char>> edges = {{'A', 'B'}, {'B', 'C'}, {'C', 'D'}, {'A', 'C'}, {'B', 'D'}};
        for (const auto& edge : edges) {
            graph.addEdge(edge.first, edge.second);
        }
        
        auto bfsResult = graph.bfs('A');
        auto dfsResult = graph.dfs('A');
        
        cout << "   BFS from A: ";
        for (char c : bfsResult) cout << c << " ";
        cout << endl;
        
        cout << "   DFS from A: ";
        for (char c : dfsResult) cout << c << " ";
        cout << endl;
        
        cout << "\n5. Sorting Algorithms:" << endl;
        vector<int> testArray = {64, 34, 25, 12, 22, 11, 90};
        cout << "   Original array: ";
        for (int x : testArray) cout << x << " ";
        cout << endl;
        
        auto bubbleSorted = SortingAlgorithms::bubbleSort(testArray);
        auto mergeSorted = SortingAlgorithms::mergeSort(testArray);
        
        cout << "   Bubble sort: ";
        for (int x : bubbleSorted) cout << x << " ";
        cout << endl;
        
        cout << "   Merge sort: ";
        for (int x : mergeSorted) cout << x << " ";
        cout << endl;
        
        cout << "\n6. Search Algorithms:" << endl;
        vector<int> sortedArray = {11, 12, 22, 25, 34, 64, 90};
        int target = 25;
        
        cout << "   Array: ";
        for (int x : sortedArray) cout << x << " ";
        cout << endl;
        
        int linearResult = SearchAlgorithms::linearSearch(sortedArray, target);
        int binaryResult = SearchAlgorithms::binarySearch(sortedArray, target);
        
        cout << "   Linear search for " << target << ": Index " << linearResult << endl;
        cout << "   Binary search for " << target << ": Index " << binaryResult << endl;
        
        cout << "\n7. Knowledge Graph Search:" << endl;
        auto searchResults = searchConcepts("tree");
        cout << "   Search results for 'tree': " << searchResults.size() << " concepts found" << endl;
        for (const string& result : searchResults) {
            displayConcept(result);
        }
    }
};


int main() {
    try {
        DSAKnowledgeGraph kg;
        kg.demonstrateAll();
        
        kg.exportToGraphviz();
        kg.exportToJSON();
        
        cout << "\n=== DSA Knowledge Graph System Ready ===" << endl;
        cout << "All data structures and algorithms have been demonstrated successfully!" << endl;
        cout << "\nVisualization files created:" << endl;
        cout << "- knowledge_graph.dot (for Graphviz)" << endl;
        cout << "- knowledge_graph.json (for web visualization)" << endl;
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
