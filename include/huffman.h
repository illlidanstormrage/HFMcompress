#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include <map>
#include <vector>
#include <memory>
#include <queue>
#include <iostream>

class HFMTree;
class Compare_HFMNode_Pointer;
class Compressor;

// 统计每个字符(按8位ascii码)出现的次数
class CountChar{
public:
    CountChar() = default;
    CountChar(const std::string&);
    std::vector<std::pair<int, int>> char_map;
private:
    // 辅助函数，简单计算乘方
    int pow(int base, int index);
};

// 哈夫曼节点
class HFMNode{
    friend class HFMTree;
    friend class Compare_HFMNode_Pointer;
    friend class Compressor;
public:
    HFMNode() = default;
    HFMNode(int a, 
            int b, 
            std::shared_ptr<HFMNode> left = nullptr, 
            std::shared_ptr<HFMNode> right = nullptr): 
            ascii(a), weight(b), lchild(left), rchild(right){}
private:
    int ascii;
    int weight;
    std::shared_ptr<HFMNode> lchild;
    std::shared_ptr<HFMNode> rchild;
};

// 自定义优先级比较，用于优先队列，此处定义为weight大的优先出队
class Compare_HFMNode_Pointer{
public:
    bool operator()(std::shared_ptr<HFMNode> &a, std::shared_ptr<HFMNode> &b) const{
        return a->weight > b->weight;
    }
};

// 哈夫曼树
class HFMTree{
public:
    HFMTree() = default;
    HFMTree(const std::string&);
    std::shared_ptr<HFMNode> root;

    // 层序遍历
    void level_order() const;
};


#endif
