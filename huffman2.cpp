//Tyler Schnitzer. Huffman . 04/15/2022
#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

#define MAX_TREE_HT 256

using namespace std;

map<char, string> codes;   // Declare map for each character its huffman var



map<char, int> freq; // Declare storage for freqs



struct MinHeapNode //Tree node

{

    char data; // One of the input characters

    int freq; // Frequency of the character

    MinHeapNode *left, *right; // Left and right child

  

    MinHeapNode(char data, int freq)

    {

        left = right = NULL;

        this->data = data;

        this->freq = freq;

    }

};


struct compare 
{

    bool operator()(MinHeapNode* l, MinHeapNode* r)
    {
        return (l->freq > r->freq);
    }

};

void printCodes(struct MinHeapNode* root, string str) //print characters and their huffman values
{

    if (!root)

    return;

    if (root->data != '$')

    cout << root->data << ": " << str << "\n";

    printCodes(root->left, str + "0");

    printCodes(root->right, str + "1");

}

void storeCodes(struct MinHeapNode* root, string str) //store charachters and ther huffman values

{

    if (root==NULL)

    return;

    if (root->data != '$')

    codes[root->data]=str;

    storeCodes(root->left, str + "0");

    storeCodes(root->right, str + "1");

}

  

// STL priority queue to store heap tree, with respect to their heap root node value

priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;

  


void HuffmanCodes(int size) // Builds Huffman tree

{

    struct MinHeapNode *left, *right, *top;

    for (map<char, int>::iterator v=freq.begin(); v!=freq.end(); v++)

        minHeap.push(new MinHeapNode(v->first, v->second));

    while (minHeap.size() != 1)

    {

        left = minHeap.top();

        minHeap.pop();

        right = minHeap.top();
        
        minHeap.pop();

        top = new MinHeapNode('$', left->freq + right->freq);  
        
        top->left = left;

        top->right = right;

        minHeap.push(top);

    }

    storeCodes(minHeap.top(), "");

}

void calcFreq(string str, int n) //maps up each character with their freq

{
    for(int i=0; i<n; i++)
    {
        freq[str[i]]++;
    }

}

  
string decode_file(struct MinHeapNode* root, string s)

{

    string ans = "";

    struct MinHeapNode* curr = root;

    for (int i=0;i<s.size();i++)

    {

        if (s[i] == '0')
            curr = curr->left;

        else
            curr = curr->right;

        if (curr->left==NULL and curr->right==NULL)
        {

            ans += curr->data;

            curr = root;

        }

    }

    return ans+'\0';

}


int main(int argc, char *argv[])

{
    vector<string> textLines;
    string userFile, line;
    cout<<"Enter in text file: ";
    cin>>userFile;

    std::ifstream inputFile(userFile);
    std::stringstream buffer;
    buffer<<inputFile.rdbuf();

    std::string content(buffer.str());

    if(!inputFile.good())
    {
        cout<<"File failed to load\n";

        exit(1);
    }
    while(getline(inputFile, line))
    {
        textLines.push_back(line);

    }

    string encodedString, decodedString;

    calcFreq(content, content.size());

    HuffmanCodes(sizeof(content));

    cout << "Character With there Frequencies:\n";

    for (auto v=codes.begin(); v!=codes.end(); v++)

    cout << v->first <<' ' << v->second << endl;

  

    for (auto i: content)
        encodedString+=codes[i];

    cout << "\nEncoded Huffman data:\n" << encodedString << endl;

  

    decodedString = decode_file(minHeap.top(), encodedString);

    cout << "\nDecoded Huffman Data:\n" << decodedString << endl;

    return 0;

}