#include "huffman.h"
#include <fstream>
#include <algorithm>

int CountChar::pow(int base, int index){
    if(index == 0){
        return 1;
    }
    return pow(base, index-1) * base;
}

CountChar::CountChar(const std::string& s){
    char_map.resize(256);
    for(int i=0; i<256; i++){
        char_map[i] = std::pair<int, int>(i, 0);
    }
    int size = s.size();
    int count = 0;
    for(int i=0; i<size; i++){
        int index = i%8;
        if(s[i] == '1'){
            count += pow(2, 7-index);
        }
        if(index == 7){
            char_map[count].second++;
            count = 0;
        }
    }
}

HFMTree::HFMTree(const std::string &in){
    std::priority_queue<std::shared_ptr<HFMNode>, 
                        std::vector<std::shared_ptr<HFMNode>>,
                        Compare_HFMNode_Pointer> HFMqueue;
    CountChar CC(in);
    std::vector<std::pair<int, int>> &char_map = CC.char_map;
    for(auto it : char_map){
        if(it.second == 0){
            continue;
        }
        HFMqueue.push(std::make_shared<HFMNode>(it.first, it.second));
    }
    while(HFMqueue.size() > 1){
        std::shared_ptr<HFMNode> left = HFMqueue.top();
        HFMqueue.pop();
        std::shared_ptr<HFMNode> right = HFMqueue.top();
        HFMqueue.pop();
        std::shared_ptr<HFMNode> new_node = std::make_shared<HFMNode>(-1, left->weight+right->weight, left, right);
        HFMqueue.push(new_node);
    }
    root = HFMqueue.top();
    HFMqueue.pop();
}

void HFMTree::level_order() const{
    std::queue<std::shared_ptr<HFMNode>> q;
    q.push(root);
    int flag = 0;
    int end = 1;
    int count = 1;
    while(!q.empty()){
        auto node = q.front();
        q.pop();
        std::cout << node->ascii << " ";
        flag++;
        if(node->lchild){
            q.push(node->lchild);
            end++;
        }
        if(node->rchild){
            q.push(node->rchild);
            end++;
        }
        if(flag == count){
            std::cout << std::endl;
            count = end;
        }
    }
}