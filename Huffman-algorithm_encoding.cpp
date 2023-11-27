#include <bits/stdc++.h> 

using namespace std; 

// This is data type of a heap node
struct MinHeapNode { 
    // Character data of this node
    char data; 
    // Frequency of the character 
    unsigned freq; 
    // Pointer to its Left and right child 
    MinHeapNode *left, *right; 
    // Constructor
    MinHeapNode(char data, unsigned freq)  { 
        left = right = NULL; // at beginning, we just construct
        this->data = data;   // the leaves
        this->freq = freq; 
    } 
}; 
 
// For comparison of two heap nodes (needed in min heap) 
struct compare { 
    bool operator()(MinHeapNode* l, MinHeapNode* r) { 
        return (l->freq > r->freq); 
    } 
};

// Get Frequency of each character in the original text
map<char, int> getCharsFrequency(const string& str) {
    map<char, int> data;
    for (auto c : str)
        data[c]++;
    return data;
} 

// The function that builds a Huffman Tree
MinHeapNode* HuffmanCoding(const map<char, int>& data) {
    // Special case, when just 1 character in original text
    if (data.size() == 1) {
        MinHeapNode* root = new MinHeapNode('$', data.begin()->second);
        root->left = new MinHeapNode(data.begin()->first, data.begin()->second);
        return root;
    }
    // Create a min heap & inserts all characters of data[] 
    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap; 

    // Construct all charater as a leave node and push them to minHeap
    for (const auto &p : data)
        minHeap.push(new MinHeapNode(p.first, p.second)); 

    // Iterate while size of heap doesn't become 1 
    while (minHeap.size() != 1) { 
        struct MinHeapNode *left, *right, *top; 
        // Extract the two minimum freq items from min heap 
        left = minHeap.top();
        minHeap.pop(); // Pop out of min Heap
        right = minHeap.top();
        minHeap.pop(); // Pop out of min Heap
 
        // Create a new internal node with frequency equal to the sum of the 
        // two nodes frequencies. Make the two extracted node as left and right 
        // children of this new node. 

        // Add this node to the min heap '$' is a special value 
        // for internal nodes, mark that it doesn't contain the our data
        top = new MinHeapNode('$', left->freq + right->freq); 
        top->left = left, top->right = right; 

        minHeap.push(top); 
    }  
    // This function will return the root of Huffman Tree
    return minHeap.top();
} // Time conplexity: O(nlog(n)), Cuz we use min-heap, this is pretty small.

// Traveling on Huffman tree to build codebook
void traversal(MinHeapNode* top, map<char, string> &codebook, string collect) {
    if (top == nullptr)
        return;
    if (top->data != '$') // If this is not internal node, It's carrying our data
        codebook[top->data] = collect;
    traversal(top->left, codebook, collect + '0');
    traversal(top->right, codebook, collect + '1');
}

// This function to get the codebook from the Huffman tree
map<char, string> getCodebook(MinHeapNode* rootOfHuffmanTree) {
    map<char, string> codebook;
    traversal(rootOfHuffmanTree, codebook, "");
    return codebook;
}

// Encoding the original text base on codebook
string encode(const string &original_text, MinHeapNode* rootOfHuffmanTree) {
    map<char, string> codebook = getCodebook(rootOfHuffmanTree);
    string result = "";
    for (const auto &c : original_text)
        result += codebook[c];
    return result;
}

// Function to print the Huffman tree
void printHuffmanTree(MinHeapNode* root, ofstream& outFile) {
    if (root == nullptr) {
        outFile << "0 "; // Indicate a null pointer
        return;
    }

    outFile << "1 " << root->data << " " << root->freq << " ";
    printHuffmanTree(root->left, outFile);
    printHuffmanTree(root->right, outFile);
}

// Driver Code 
int main() 
{ 
    // Read the Original text
    ifstream inFile("original_text.txt");
    string original_text;
    getline(inFile, original_text);

    // Build the Huffman Tree
    MinHeapNode* root = HuffmanCoding(getCharsFrequency(original_text));

    // Print Huffman Tree and Encoded text
    ofstream outFile("encoded_text.txt");
    // outFile << "original_text: " << original_text << endl;
    outFile << "Huffman Tree (Preorder Traversal): \n";
    printHuffmanTree(root, outFile);
    outFile << "\nEncoded: " << encode(original_text, root) << endl;

    return 0; 
} 
 
