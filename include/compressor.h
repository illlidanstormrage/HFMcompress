#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include "huffman.h"
#include <map>

// 压缩器
class Compressor{
public:
    Compressor() = default;
    Compressor(const std::string&);
    void compress(); //压缩函数
    void decompress(); //解压函数

private:
    std::map<int, std::string> code_book; //哈夫曼编码
    std::string in; //文件输入
    std::string file_name; //文件名
    
    // 辅助函数，获取哈夫曼编码
    void getHFMCode(std::shared_ptr<HFMNode> node, std::string HFMCode);    
    // 辅助函数，计算乘方
    int pow(int base, int index);
};


#endif
