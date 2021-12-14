#include "compressor.h"
#include <fstream>
#include <vector>

void Compressor::getHFMCode(std::shared_ptr<HFMNode> node, std::string HFMCode){
    if(node->lchild==nullptr && node->rchild==nullptr){
        code_book[node->ascii] = HFMCode;
        return;
    }
    getHFMCode(node->lchild, HFMCode+"0");
    getHFMCode(node->rchild, HFMCode+"1");
}

int Compressor::pow(int base, int index){
    if(index == 0){
        return 1;
    }
    return pow(base, index-1) * base;
}

Compressor::Compressor(const std::string &file_name){
    this->file_name = file_name.substr(0, file_name.find('.'));
    std::ifstream ifs(file_name, std::ios::binary);
    ifs >> in;
    HFMTree ht(in);
    auto node = ht.root;
    getHFMCode(node, std::string());
}

void Compressor::operate(){
    std::ofstream ofs(file_name + ".huf", std::ios::binary);
    ofs << code_book.size() << "\n";
    for(auto pair : code_book){
        ofs << pair.first << " " << pair.second << "\n";
    }
    int size = in.size();
    int count = 0;
    for(int i=0; i<size; i++){
        int index = i%8;
        if(in[i] == '1'){
            count += pow(2, 7-index);
        }
        if(index == 7){
            ofs << code_book[count];
            count = 0;
        }
    }
    ofs.close();
}

void Compressor::get_content() const{
    std::cout << in << std::endl;
}

void DeCompressor::get_content() const{
    std::cout << in << std::endl;
}

void DeCompressor::getHFMCode(const std::string& file_name){
    std::ifstream ifs(file_name, std::ios::binary);
    std::string line_1;
    std::getline(ifs, line_1);
    int n = stoi(line_1);
    for(int i=0; i<n; i++){
        std::string temp, temp_1, temp_2;
        std::getline(ifs, temp);
        int space_pos = temp.find(' ');
        temp_1 = temp.substr(0, space_pos);
        temp_2 = temp.substr(space_pos+1);
        code_book.insert(std::make_pair(stoi(temp_1), temp_2));
    }
    std::getline(ifs, this->main_str);
}   

DeCompressor::DeCompressor(const std::string& file_name){
    this->file_name = file_name.substr(0, file_name.find('.'));
    getHFMCode(file_name);
}

void DeCompressor::operate(){
    HFMTree ht(code_book);
    std::string out;
    std::ofstream ofs("testout.txt");
    std::shared_ptr<HFMNode> node = ht.root;
    for(auto ch : this->main_str){
        if(ch == '0'){
            node = node->lchild;
        }
        else if(ch == '1'){
            node = node->rchild;
        }
        if(!node->lchild && !node->rchild){
            out += itobs(node->ascii);
            node = ht.root;
            continue;
        }
    }
    ofs << out;
}


