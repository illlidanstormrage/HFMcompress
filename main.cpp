#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "huffman.h"
#include "compressor.h"

// inline int pow(int base, int index){
//     if(index == 0){
//         return 1;
//     }
//     return pow(base, index-1) * base;
// }

// void transfer(const std::string &file_name){
//     std::ifstream ifs(file_name, std::ios::binary);
//     std::string s;
//     ifs >> s;
//     std::ofstream ofs("transfered_compression", std::ios::binary);
//     int size = s.size();
//     int count = 0;
//     for(int i=0; i<size; i++){
//         int index = i%8;
//         if(s[i] == '1'){
//             count += pow(2, 7-index);
//         }
//         if(index == 7){
//             char temp = count;
//             ofs << temp;
//             count = 0;
//         }
//     }
//     ofs.close();
// }

// 查看字符频度顺序
void show_freq(){
    std::string file_name = "origin_compression.txt";
    std::ifstream ifs(file_name, std::ios::binary);
    std::string s;
    ifs >> s;
    CountChar CC(s);
    std::vector<std::pair<int, int>> char_map = CC.char_map;
    std::sort(char_map.begin(), char_map.end(), [](const std::pair<int, int> &a, const std::pair<int, int> &b){
        return a.second > b.second;
    });
    for(auto v : char_map){
        std::cout << v.first << " " << v.second << std::endl;
    }
}

int main()
{
    std::string file_name;
    std::cout << "enter file name:\n";
    std::cin >> file_name;

    // Compressor compressor(file_name);
    // compressor.operate();

    DeCompressor decompressor(file_name);
    decompressor.operate();

    return 0;
}
