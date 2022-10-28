# labS

## 代码结构分析

### main.cpp

main函数中使用了boost/program_options.hpp库实现命令行指令的接受与解析，设定了帮助，输入输出文件指定，起始地址设定，执行过程输出的功能

```c++
virtual_machine_tp virtual_machine(gBeginningAddress, gInputFileName, gRegisterStatusFileName);
int halt_flag = true;
int time_flag = 0;
while(halt_flag) {
    // Single step
    // TO BE DONEd
    if (virtual_machine.NextStep() == 0)
        halt_flag = false;
    if (gIsDetailedMode)
        std::cout << virtual_machine.reg << std::endl;
    ++time_flag;
}
```

这一段中声明了`virtual_machine_tp`类型的变量，这是仿真器的核心部分，然后在while循环中执行指令直到HALT，仿真结束后输出程序运行完成后的寄存器状态和执行的指令周期数

### common.h

程序运行所需要的头文件和全局变量声明

### memory.cpp/memory.h

声明了memory_tp类用于内存的仿真，类成员函数`ReadMemoryFromFile`从文件中读取机器码到内存，`GetContent`与`operator[]`用于内存内容的获取，类外声明了函数`TranslateInstruction`将`std::string`类型的指令转换为`int16_t`类型

### register.cpp/register.h

使用`typedef`定义了`register_tp`为`std::array<int16_t, kRegisterNumber>`，用以寄存器的仿真。声明了枚举类型`RegisterName`用以寄存器的存取，声明了重载函数`operator<<`以输出寄存器的状态

### simulator.cpp/simulator.h

声明了`kOpcodeList`枚举类型以区分不同的指令，声明了`virtual_machine_tp`类来仿真指令的运行，类成员中包含仿真各个指令的对应函数，类构造函数中进行内存，寄存器的初始化，类成员函数`UpdateCondRegister`更新`CondRegister`的状态，`NextStep`执行下一步的指令

## TO BE DONE

### main.cpp

```c++
while(halt_flag) {
    // Single step
    // TO BE DONEd
    if (virtual_machine.NextStep() == 0)
        halt_flag = false;
    if (gIsDetailedMode)
        std::cout << virtual_machine.reg << std::endl;
    ++time_flag;
}
```

在运行HALT指令后，NextStep()函数会返回0，此时将halt_flag设置为false终止循环的进行

### memory.cpp

```c++
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
```

从文件中逐行读取机器码并去除中间可能的空格后存入内存

```c++
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
```

返回对应地址的内存内容

### simulator.cpp

```c++
switch (opcode) {
    case O_ADD:
    if (gIsDetailedMode) {
        std::cout << "ADD" << std::endl;
    }
    VM_ADD(current_instruct);
    break;
    case O_AND:
    // TO BE DONE
    if (gIsDetailedMode) {
        std::cout << "AND" << std::endl;
    }
    VM_AND(current_instruct);
    break;
    case O_BR:
    // TO BE DONE
    if (gIsDetailedMode) {
        std::cout << "BR" << std::endl;
    }
    VM_BR(current_instruct);
    break;
    case O_JMP:
    // TO BE DONE
    if (gIsDetailedMode) {
        std::cout << "JMP" << std::endl;
    }
    VM_JMP(current_instruct);
    break;
    case O_JSR:
    // TO BE DONE
    if (gIsDetailedMode) {
        std::cout << "JSR" << std::endl;
    }
    VM_JSR(current_instruct);
    break;
    case O_LD:
    // TO BE DONE
    if (gIsDetailedMode) {
        std::cout << "LD" << std::endl;
    }
    VM_LD(current_instruct);
    break;
    case O_LDI:
    // TO BE DONE
    if (gIsDetailedMode) {
        std::cout << "LDI" << std::endl;
    }
    VM_LDI(current_instruct);
    break;
    case O_LDR:
    // TO BE DONE
    if (gIsDetailedMode) {
        std::cout << "LDR" << std::endl;
    }
    VM_LDR(current_instruct);
    break;
    case O_LEA:
    // TO BE DONE
    if (gIsDetailedMode) {
        std::cout << "LEA" << std::endl;
    }
    VM_LEA(current_instruct);
    break;
    case O_NOT:
    // TO BE DONE
    if (gIsDetailedMode) {
        std::cout << "NOT" << std::endl;
    }
    VM_NOT(current_instruct);
    break;
    case O_RTI:
    // TO BE DONE
    if (gIsDetailedMode) {
        std::cout << "RTI" << std::endl;
    }
    VM_RTI(current_instruct);
    break;
    case O_ST:
    // TO BE DONE
    if (gIsDetailedMode) {
        std::cout << "ST" << std::endl;
    }
    VM_ST(current_instruct);
    break;
    case O_STI:
    // TO BE DONE
    if (gIsDetailedMode) {
        std::cout << "STI" << std::endl;
    }
    VM_STI(current_instruct);
    break;
    case O_STR:
    // TO BE DONE
    if (gIsDetailedMode) {
        std::cout << "STR" << std::endl;
    }
    VM_STR(current_instruct);
    break;
    case O_TRAP:
    if (gIsDetailedMode) {
        std::cout << "TRAP" << std::endl;
    }
    if ((current_instruct & 0xFF) == 0x25) {
        reg[R_PC] = 0;
    }
    VM_TRAP(current_instruct);
    break;
    default:
    VM_RTI(current_instruct);
    break;       
}
```

在各个分支执行对应的函数并在`gIsDetailedMode`为True时输出信息

```c++
inline T SignExtend(const T x) {
    // Extend the number
    // TO BE DONE
    if (((x >> (B - 1)) & 1) == 0)
        return x;
    else
        return x | ((0xffff >> (B - 1)) << (B - 1));
}
```

根据位数进行符号拓展

```c++
void virtual_machine_tp::UpdateCondRegister(int regname) {
    // Update the condition register
    // TO BE DONE
    if (reg[regname] > 0)
        reg[R_COND] = 0b1;
    else if (reg[regname] == 0)
        reg[R_COND] = 0b10;
    else
        reg[R_COND] = 0b100;
}
```

根据传入的寄存器的内容设置`CondRegister`

```c++
void virtual_machine_tp::VM_AND(int16_t inst) {
    // TO BE DONE
    int flag = inst & 0b100000;
    int dr = (inst >> 9) & 0x7;
    int sr1 = (inst >> 6) & 0x7;
    if (flag) {
        // and inst number
        int16_t imm = SignExtend<int16_t, 5>(inst & 0b11111);
        reg[dr] = reg[sr1] & imm;
    } else {
        // and register
        int sr2 = inst & 0x7;
        reg[dr] = reg[sr1] & reg[sr2];
    }
    // Update condition register
    UpdateCondRegister(dr);
}
```

从指令中获得DR和SR1对应的寄存器，并根据flag决定SR2是立即数寻址或者寄存器寻址，立即数寻址需要进行符号拓展

```c++
void virtual_machine_tp::VM_JMP(int16_t inst) {
    // TO BE DONE
    int16_t baser = (inst >> 6) & 0x7;
    if (gIsDetailedMode) {
        std::cout << reg[R_PC] << std::endl;
        std::cout << reg[baser] << std::endl;
    }
    reg[R_PC] = reg[baser];
}
```

修改PC寄存器

```c++
void virtual_machine_tp::VM_JSR(int16_t inst) {
    // TO BE DONE
    int16_t pc_offset = SignExtend<int16_t, 11>(inst & 0x7FF);
    if (gIsDetailedMode) {
        std::cout << reg[R_PC] << std::endl;
        std::cout << pc_offset << std::endl;
    }
    reg[R_R7] = reg[R_PC];
    reg[R_PC] += pc_offset;
}
```

对pcoffset进行符号拓展，修改R7为下一条指令的地址，修改PC为跳转地址

```c++
void virtual_machine_tp::VM_LDI(int16_t inst) {
    // TO BE DONE
    int16_t dr = (inst >> 9) & 0x7;
    int16_t pc_offset = SignExtend<int16_t, 9>(inst & 0x1FF);
    reg[dr] = mem[mem[reg[R_PC] + pc_offset]];
    UpdateCondRegister(dr);
}

void virtual_machine_tp::VM_LDR(int16_t inst) {
    // TO BE DONE
    int16_t dr = (inst >> 9) & 0x7;
    int16_t baser = (inst >> 6) & 0x7;
    int16_t offset = SignExtend<int16_t, 6>(inst & 0x3F);
    reg[dr] = mem[reg[baser] + offset];
    UpdateCondRegister(dr);
}

void virtual_machine_tp::VM_LEA(int16_t inst) {
    // TO BE DONE
    int16_t dr = (inst >> 9) & 0x7;
    int16_t pc_offset = SignExtend<int16_t, 9>(inst & 0x1FF);
    reg[dr] = reg[R_PC] + pc_offset;
    UpdateCondRegister(dr);
}
void virtual_machine_tp::VM_ST(int16_t inst) {
    // TO BE DONE
    int16_t sr = (inst >> 9) & 0x7;
    int16_t pc_offset = SignExtend<int16_t, 9>(inst & 0x1FF);
    mem[reg[R_PC] + pc_offset] = reg[sr];
}

void virtual_machine_tp::VM_STI(int16_t inst) {
    // TO BE DONE
    int16_t sr = (inst >> 9) & 0x7;
    int16_t pc_offset = SignExtend<int16_t, 9>(inst & 0x1FF);
    mem[mem[reg[R_PC] + pc_offset]] = reg[sr];
}

void virtual_machine_tp::VM_STR(int16_t inst) {
    // TO BE DONE
    int16_t sr = (inst >> 9) & 0x7;
    int16_t baser = (inst >> 6) & 0x7;
    int16_t offset = SignExtend<int16_t, 6>(inst & 0x3F);
    mem[reg[baser] + offset] = reg[sr];
}
```

实现不同模式的内存读取指令

```c++
void virtual_machine_tp::VM_NOT(int16_t inst) {
    // TO BE DONE
    int dr = (inst >> 9) & 0x7;
    int sr = (inst >> 6) & 0x7;
    reg[dr] = ~ reg[sr];
    UpdateCondRegister(dr);
}
```

获得DR和SR后进行NOT操作

```c++
void virtual_machine_tp::VM_TRAP(int16_t inst) {
    int16_t trapnum = inst & 0xFF;
    termios oldt,newt;
    int16_t start;
    switch (trapnum) {
    case 0x20:
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ECHO | ICANON);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        reg[R_R0] = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        break;
    case 0x21:
        std::cout << "Output:";
        putchar(reg[R_R0]);
        std::cout << std::endl;
        break;
    case 0x22:
        start = reg[R_R0];
        while (mem[start] != 0) {
            putchar(mem[start]);
            start++;
        }
        std::cout << std::endl;
        break;
    case 0x23:
        std::cout << "Input:";
        reg[R_R0] = getchar();
        break;
    case 0x24:
        start = reg[R_R0];
        while (mem[start] != 0) {
            putchar(mem[start] & 0xff);
            if ((mem[start] >> 8) != 0)
                putchar(mem[start] >> 8);
            start++;
        }
        std::cout << std::endl;
        break;
    case 0x25:
        std::cout << "Halting" << std::endl;
        break;
    default:
        break;
    }
    // TODO: build trap program
}
```

实现各条TRAP指令，其中实现x20对应指令时，为了在输出字符时不回显，使用了Linux下的termios.h设置终端参数

