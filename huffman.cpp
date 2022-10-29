
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <fstream>


using namespace std;

const int MAX=256;

class huffType
{
    struct nodeType
    {
        char data;
        size_t freq;
        nodeType* left;
        nodeType* right;
        nodeType(char data, size_t freq) : data(data),
                                 freq(freq),left(NULL),right(NULL)
{}                               
        ~nodeType() 
        {
            delete left;
            delete right;
        }
};
struct compare
{
    bool operator()(nodeType* l, nodeType* r)
    {
        return (l->freq > r->freq);
    }
};

nodeType* top;

void print_Code(nodeType* root, string str)
{
    if(root == NULL)
        return;

    if(root->data == '$')
    {
        print_Code(root->left, str + "0");
        print_Code(root->right, str + "1");
    }

    if(root->data != '$')
    {
        cout << root->data <<" : " << str << "\n";
        print_Code(root->left, str + "0");
        print_Code(root->right, str + "1");
    }
}

public:
    huffType() {};
    ~huffType()
    {
        delete top;
    }

    void Generate_Huffman_tree(vector<char>& data, vector<size_t>& freq, size_t size)
    {
        nodeType* left;
        nodeType* right;
        priority_queue<nodeType*, vector<nodeType*>, compare > minHeap;

        for(size_t i = 0; i < size; ++i)
        {
            minHeap.push(new nodeType(data[i], freq[i]));
        }

        while(minHeap.size() != 1)
        {
            left = minHeap.top();
            minHeap.pop();

            right = minHeap.top();
            minHeap.pop();

            top = new nodeType('$', left->freq + right->freq);
            top->left = left;
            top->right = right;
            minHeap.push(top);
        }
        print_Code(minHeap.top(), "");
    
    }
};

int main()
{
    int len, n, f;
    int cnt=0;
    char ch;
    char line[MAX], fname[25];
    huffType set1;
    vector<char> data;
    vector<size_t> freq;

    cout<<"Enter filename: ";
    cin>>fname;
    ifstream fin;  //Takes in userfile
    fin.open(fname, ios::in);
    if(!fin)   //test if the file works
    {
        cout<<fname<<" does not exist.\n";
        exit(0);
    }
    cout<<"\nContents of file:\n\n";
    while(fin.eof() == 0)
    {
        fin.getline(line, sizeof(line));
        len=strlen(line);
        for(int i=0; i<len; ++i)
        {
            ++cnt;
        }
        cout<<line<<"\n";
    }

    cout<<"Number of elements is "<<cnt<<endl;
    n=cnt;
    cout<<"Enter the characters \n";
    for (int i=0;i<n;i++)
    {
        ch=line[i];
        data.insert(data.end(), ch);
    }
    cout<<"Enter the frequencies \n";
    for (int i=0;i<n;i++)
    {
        //cin>>f;
        freq.insert(freq.end(), f);
    }

    size_t size = data.size();
    
    set1.Generate_Huffman_tree(data, freq, size);
    return 0;
}

