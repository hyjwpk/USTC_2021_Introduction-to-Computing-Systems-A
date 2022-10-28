/*
 * @Author       : Chivier Humber
 * @Date         : 2021-09-15 21:15:24
 * @LastEditors  : Chivier Humber
 * @LastEditTime : 2021-11-23 16:08:51
 * @Description  : file content
 */
#include "common.h"
#include "memory.h"

namespace virtual_machine_nsp {
    void memory_tp::ReadMemoryFromFile(std::string filename, int beginning_address) {
        // Read from the file
        // TO BE DONE
        std::ifstream input_file;
        input_file.open(filename);
        std::string line;
        if (input_file.is_open()) {
            while (std::getline(input_file, line)) {
                // Remove Space
                size_t nPos = 0;
                nPos = line.find(" ", nPos);
                while (nPos != std::string::npos) {
                    line.replace(nPos, 1, "");
                    nPos = line.find(" ", nPos);
                }
                memory[beginning_address++] = strtol(line.c_str(), NULL, 2);
            };
        }
    }

    int16_t memory_tp::GetContent(int address) const {
        // get the content
        // TO BE DONE
        return memory[address];
    }

    int16_t& memory_tp::operator[](int address) {
        // get the content
        // TO BE DONE
        return memory[address];
    }    
}; // virtual machine namespace
