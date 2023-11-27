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

// This functon discard a line in the input file
void discardLine(ifstream& inFile) {
    string tmp;
    getline(inFile, tmp);
}

/// This function discard a word (a string without space)
void discardWord(ifstream& inFile) {
    inFile.ignore();
    string tmp;
    getline(inFile, tmp, ' ');
}

void string_pop(string& str, int times) {
    while (times-- > 0 && !str.empty()) {
        str.pop_back();
    }
}

// Read Huffman Tree
MinHeapNode* readHuffmanTree(string& HuffmanTreeDescription) {
    char sign = HuffmanTreeDescription.back();
    string_pop(HuffmanTreeDescription, 2); // pop out sign and the space
    if (sign == '0')
        return nullptr;

    char data = HuffmanTreeDescription.back();
    string_pop(HuffmanTreeDescription, 2); // pop out data(character) and space
    int freq = 0;
    while (HuffmanTreeDescription.back() != ' ') {
        freq = freq*10 + (HuffmanTreeDescription.back() - '0');
        string_pop(HuffmanTreeDescription, 1);
    }
    string_pop(HuffmanTreeDescription, 1); // pop out the space

    MinHeapNode* top = new MinHeapNode(data, freq);
    top->left = readHuffmanTree(HuffmanTreeDescription);
    top->right = readHuffmanTree(HuffmanTreeDescription);

    return top;
}

// Decoding base on Huffman Tree
string HuffmanDecoding(MinHeapNode* root, const string &encoded_txt) {
    string decoded_txt = "";
    MinHeapNode* itr = root;
    for (auto c : encoded_txt) {
        itr = (c == '0' ? itr->left : itr->right);
        if (itr->data != '$') {
            decoded_txt += itr->data;
            itr = root;
        }
    }
    return decoded_txt;
}

// Driver Code 
int main() 
{ 
    // Open encoded file
    ifstream inFile("encoded_text.txt");

    // Read the Huffman Tree
    discardLine(inFile); // First line is the Introduce, we don't need that
    string HuffmanTreeDescription;
    getline(inFile, HuffmanTreeDescription);
    reverse(HuffmanTreeDescription.begin(), HuffmanTreeDescription.end());
    MinHeapNode* root = readHuffmanTree(HuffmanTreeDescription);

    // Read the Encoded text
    discardWord(inFile); // This word is a introduce too
    string encoded_txt;
    getline(inFile, encoded_txt);

    // Open decoded file
    ofstream outFile("decoded_text.txt");
    // Decoding
    string decoded_txt = HuffmanDecoding(root, encoded_txt);
    outFile << "Decoded text: " << decoded_txt << endl;

    return 0; 
} 
