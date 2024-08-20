/*
    Task given at state exam of Sofia University
    https://intranet.fmi.uni-sofia.bg/index.php/s/o1mQN0S3lmXkfEJ - task 2

    We have to print words spelled by each level of the tree.
    
    If at some level there is a vertex missing, which would be there in case of
    complete binary tree, we should print ' '.

    Printing is stopped when we print the last node's data.
*/

#include <iostream>
#include <vector>
#include <queue>

struct Node
{
    char text;
    Node *left, *right;

    Node(char t, Node* l = nullptr, Node* r = nullptr) :
        text(t),
        left(l),
        right(r) {}
};

unsigned count(Node* t)
{
    if(t == nullptr)
        return 0;
        
    return 1 + count(t->left) + count(t->right);
}

bool isPowerOfTwo(unsigned n)
{
    return ((n != 0) && ((n & (n - 1)) == 0));
}

void printText(Node* tree)
{
    unsigned nodesCount = count(tree);
    unsigned iterations = 0;
    std::queue<Node*> q;
    q.push(tree);

    while(nodesCount)
    {
        Node* top = q.front();
        q.pop();
        
        if(top == nullptr)
        {
            q.push(nullptr);
            q.push(nullptr);
            std::cout << ' ';
        }
        else
        {
            --nodesCount;
            std::cout << top->text;
            q.push(top->left);
            q.push(top->right);
        }

        if(isPowerOfTwo(++iterations + 1))
            std::cout << std::endl;
    }
}

void free(Node* tree)
{
    if(!tree)
        return;
    
    free(tree->left);
    free(tree->right);

    delete tree;
}

int main()
{
    Node* example = new Node(
        'I',
        new Node('a',
            new Node('g',
                new Node('a',
                    new Node('n', new Node('s'), nullptr),
                    new Node('g', nullptr, new Node('!'))),
                new Node('t', nullptr, new Node('p'))),
            new Node('o', 
                nullptr,
                new Node('s', new Node('r'), new Node('o')))),
        new Node('m',
            new Node('o',
                new Node('o', new Node('b'), new Node('l')),
                new Node('l', new Node('e'), new Node('m'))),
            new Node('d', new Node('v'), new Node('i')))
    );

    printText(example);
}
