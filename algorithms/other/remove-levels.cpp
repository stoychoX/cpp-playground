/*
Passed a tree and vector with numbers:

1. Print the first  index of level, which spelled left to right, 
   is equal to the passed vector. -1 if no such level exists.

2. Remove all such levels from the tree.
*/
#include <iostream>
#include <vector>
#include <set>

struct TreeNode
{
    int data;
    std::vector<TreeNode*> nodes;

    void absorbeChildren()
    {
        unsigned size = nodes.size();

        for(size_t i = 0; i < size; i++)
        {
            nodes.insert(nodes.end(), 
                         nodes[i]->nodes.begin(), 
                         nodes[i]->nodes.end());
            
            delete nodes[i];
        }

        nodes.erase(nodes.begin(), nodes.begin() + size);
    }
};

using level_t = std::vector<int>;
using levelsContainer = std::vector<level_t>;

void collectLevels(const TreeNode* root, 
                   levelsContainer& levels,
                   unsigned level = 0)
{
    if(!root) return;

    if(levels.size() <= level)
        levels.emplace_back();
    
    levels[level].push_back(root->data);

    for(const TreeNode* node : root->nodes)
        collectLevels(node, levels, level + 1);
}

bool equalLevels(const level_t& left, const level_t& right)
{
    if(left.size() != right.size())
        return false;
    
    for (size_t i = 0; i < left.size(); i++)
    {
        if(left[i] != right[i])
            return false;
    }
    return true;    
}

int findLevel(const TreeNode* root, const std::vector<int>& numbers)
{
    levelsContainer levels;
    collectLevels(root, levels);

    for(size_t i = 0; i < levels.size(); i++)
    {
        if(equalLevels(levels[i], numbers))
            return i;
    }
    return -1;
}

void removeAllLevelsRec(TreeNode* root,
                        const std::set<int>& levels,
                        unsigned level = 0)
{
    if(!root) return;

    while(levels.find(level + 1) != levels.end())
    {
        root->absorbeChildren();
        level += 1;
    }

    for(TreeNode* child : root->nodes)
        removeAllLevelsRec(child, levels, level + 1);
}

void removeAllLevels(TreeNode* root, const std::vector<int>& numbers)
{
    levelsContainer levels;
    collectLevels(root, levels);
    std::set<int> remove;

    for(int i = 1; i < levels.size(); i++)
    {
        if(equalLevels(numbers, levels[i]))
            remove.insert(i);
    }

    removeAllLevelsRec(root, remove);
}

void printLevels(const levelsContainer& container)
{
    for(const auto& level : container)
    {
        for(int x : level)
            std::cout << x << ' ';

        std::cout << std::endl;
    }
}

TreeNode* create(int data, std::initializer_list<TreeNode*> children = {})
{
    TreeNode* n = new TreeNode;
    n->data = data;

    for(TreeNode* c : children)
        n->nodes.push_back(c);

    return n;
}

void runExample(TreeNode* example, const std::vector<int>& numbers)
{
    removeAllLevels(example, numbers);
    levelsContainer l;
    collectLevels(example, l);
    printLevels(l);
    std::cout << std::endl;
}

void free(TreeNode* root)
{
    if(!root) return;

    for(TreeNode* c : root->nodes)
        free(c);
    
    delete root;
}

int main()
{
    TreeNode* example1 = create(3,
        {
            create(4,
                { 
                    create(1, { create(9), create(5), create(6) }),
                    create(2, { create(2) }),
                    create(8, { create(3), create(7) })
                }),
            create(7, {create(6, {create(9), create(2)})})
        }
    );

    runExample(example1, {1, 2, 8, 6});

    free(example1);

    TreeNode* example2 = create(1,
        {
            create(2,
            {
                create(2, {create(3), create(4)}),
            }
            ),
            create(2,
            {
                create(2, {create(5), create(6), create(7, { create(8) })}),
            }
            )
        }
    );

    runExample(example2, {2, 2});
    free(example2);
}
