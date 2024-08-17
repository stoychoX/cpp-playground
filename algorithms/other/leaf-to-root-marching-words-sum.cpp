/*
* Task given at a state exam in Sofia university.
* Rooted tree has <symbol, number> vertices.
* 
* A path from root to a leaf can yeild a word.
* Given two vertices find the sum of the numbers
* of all the leaf-to-root paths with the same words.
*/


#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

struct Node
{
    std::vector<Node*> children;
    int value;
    char symbol;

    Node(int n, char c) : value(n), symbol(c) {}
};

using container_t = std::unordered_multimap<std::string, unsigned>;

void constructWord(const Node *root, 
                   container_t &result, 
                   std::string &curentWord, 
                   unsigned number)
{
    if (!root)
    {
        return;
    }
    number += root->value;
    if (!root->children.size())
    {
        result.insert({curentWord + root->symbol, number});
        return;
    }

    curentWord.push_back('\0');

    for (const Node *c : root->children)
    {
        curentWord.back() = root->symbol;
        constructWord(c, result, curentWord, number);
    }
}

int sumVal(const Node *u, const Node *v)
{
    container_t uWords;
    container_t vWords;

    std::string buff;

    constructWord(v, vWords, buff, 0);
    buff.clear();
    constructWord(u, uWords, buff, 0);
    unsigned sum = 0;

    for (const auto &uWordData : uWords)
    {
        auto range = vWords.equal_range(uWordData.first);

        while (range.first != range.second)
        {
            sum += range.first->second + uWordData.second;
            ++range.first;
        }
    }

    return sum;
}

void free(Node *root)
{
    if(!root) return;

    for(Node* c : root->children)
    {
        free(c);
    }

    delete root;
}

int main()
{
    Node *root = new Node(1, 'a');
    root->children.push_back(new Node(2, 'b'));
    root->children.push_back(new Node(3, 'a'));

    root->children[1]->children.push_back(new Node(4, 'b'));

    std::cout << sumVal(root, root->children[1]);

    free(root);
}
