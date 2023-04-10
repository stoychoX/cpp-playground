// Problem and solution I've seen at leetcode.
#include<vector>
#include<stack>

int trap(const std::vector<int>& height) {
    std::stack<int> indexStack;
    int res = 0;

    for (size_t i = 0; i < height.size(); i++) {
        while(!indexStack.empty() && height[i] > height[indexStack.top()]) {
            int top = indexStack.top();
            indexStack.pop();

            if(indexStack.empty()) break;

            int distance = i - indexStack.top() - 1;
            int heigth = std::min(height[indexStack.top()], height[i]) - height[top];
            res += distance * heigth;
        }
        indexStack.push(i);
    }
    return res;
}
