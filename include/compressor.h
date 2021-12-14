#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include "huffman.h"
#include <map>
#include <bitset>

// 压缩器
class Compressor{
public:
    Compressor() = default;
    Compressor(const std::string&);
    virtual void operate(); //压缩函数
    virtual void get_content() const; //获取文件内容
    std::map<int, std::string> code_book; //哈夫曼编码

private:
    // 辅助函数，获取哈夫曼编码
    void getHFMCode(std::shared_ptr<HFMNode> node, std::string HFMCode);

protected:
    std::string in; //文件输入
    std::string file_name; //文件名    
    
    // 辅助函数，计算乘方
    int pow(int base, int index);
};

// 解压器
class DeCompressor : public Compressor{
public:
    DeCompressor() = default;
    DeCompressor(const std::string&);
    virtual void operate() override;
    virtual void get_content() const override;

private:
    std::string main_str;
    void getHFMCode(const std::string&);
    inline std::string itobs(int n){
        std::bitset<8> bit(n);
        return bit.to_string();
    } //辅助函数，将读取的整数（字符串）转为二进制字符串
};


#endif
