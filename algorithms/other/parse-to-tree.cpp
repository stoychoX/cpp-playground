// Task 2 from https://intranet.fmi.uni-sofia.bg/index.php/s/JQZtClyby5qQrk7

// We represent rooted tree as a list of pairs [(level_i, value_i)]
// Root is unique and its level is 0.
// parent((level_i, value_i)) = (max j)[0 <= j < i & level_j + 1 = level_i]

// We get such list and have to:
// 1. Validate its correctness.
// 2. Parse it to appropriate tree structure (left_child-right_sibling chosen here).

#include <iostream>
#include <vector>
#include <unordered_set>

struct seq_node
{
    unsigned level;
    unsigned value;

    seq_node(unsigned l, unsigned v) :
        level(l),
        value(v) {}
};

using seq_node_t = seq_node;
using tree_seq   = std::vector<seq_node_t>;
 
struct tree_node
{
    unsigned value;
    tree_node* left_child = nullptr;
    tree_node* right_sibling = nullptr;
 
    tree_node(unsigned v):
        value(v) {}
};
 
// We imply that the input is correct here.
tree_node* transform_impl(const seq_node_t* nodes, 
                         int size,
                         unsigned& original_index)
{
    if(size <= 0) 
        return nullptr;
 
    unsigned current_level = nodes[0].level;
 
    tree_node* to_return = new tree_node(nodes[0].value);
    tree_node* iter = to_return;
 
    unsigned index = 1;
 
    while(index < size && current_level <= nodes[index].level)
    {
        if(current_level == nodes[index].level)
        {
            iter->right_sibling = new tree_node(nodes[index].value);
            ++index;
            iter = iter->right_sibling;
        }
        else
        {
            iter->left_child = transform_impl(nodes + index, size - index, index);
        }
    }
 
    original_index += index;
 
    return to_return;
}
 
bool is_valid(const tree_seq& tree_seq)
{
    std::unordered_set<unsigned> seen_nodes;
 
    for(int i = 0; i < tree_seq.size(); i++)
    {
        if(i == 0 && tree_seq[i].level != 0)
            return false;
 
        if(tree_seq[i].level == 0 && seen_nodes.find(0) != seen_nodes.end())
            return false;
 
        if(i != 0 && tree_seq[i].level > tree_seq[i-1].level)
        {
            if(seen_nodes.find(tree_seq[i].level - 1) == seen_nodes.end())
                return false;
        }
 
        seen_nodes.insert(tree_seq[i].level);
    }
 
    return true;
}
 
tree_node* transform(const tree_seq& tree_seq)
{
    if(!is_valid(tree_seq))
        return nullptr;
    unsigned dummy = 0;
    return transform_impl(tree_seq.data(), tree_seq.size(), dummy);
}
 
void print(tree_node* tree, unsigned level = 0)
{
    if(tree == nullptr)
        return;
 
    std::cout << "At level " << level << " value " << tree->value << std::endl;
 
    print(tree->left_child, level + 1);
    print(tree->right_sibling, level);
}

void free(tree_node* tree)
{
    if(!tree)
        return;
    
    free(tree->left_child);
    free(tree->right_sibling);

    delete tree;
}

int main()
{
    tree_seq seq;
 
    seq.push_back({0, 5});
    seq.push_back({1, 4});
    seq.push_back({1, 5});
    seq.push_back({2, 3});
    seq.push_back({1, 6});
    seq.push_back({2, 2});
    seq.push_back({3, 3});
    seq.push_back({2, 5});
 
    tree_node* result = transform(seq);
    print(result);
    free(result);
}
