# labA

## 代码结构分析

### main.h

声明了bool型变量`gIsDebugMode`  `gIsHexMode` 分别用来标志debug和hex模式，`cmdOptionExists` `getCmdOption`函数分别用于在命令行参数中寻找某个参数是否存在以及获得参数的具体内容

在main函数中，对-h -f -d -e -o -s五个参数进行识别，分别对应帮助，输入文件路径，是否输出deubg、error信息，输出文件路径，是否以十六进制输出，完成对输入输出路径和标志的设置后，声明assembler类型的对象，调用assemble成员函数将汇编码翻译为机器码，完成后若`gIsErrorLogMode`为True，输出assemble函数的返回值

### assembler.h

声明了两个 `std::vector<std::string>`用以存储LC3指令，枚举类型`LineStatusType`来标志指令的类型

声明了`value_tp`类来存储值

声明了`label_map_tp`类来存储lable和value_tp的键值对

声明了`Trim` `RightTrim` `LeftTrim`函数以去除指令行前后的空白符

声明了`IsLC3TrapRoutine`函数判断一行指令是否是LC3指令

声明了`assembler`类将汇编码翻译为机器码

### assembler.cpp

重载了<<运算符用于输出lable的内容

声明了`RecognizeNumberValue`函数将字符串转换为int型数字

声明了`NumberToAssemble`函数将int型或字符串数字转换为16bit以字符串返回

声明了`ConvertBin2Hex`将二进制字符串转换为16进制

定义了`TranslateOprand`将操作数转换为二进制字符串

在`assemble`函数中实现了**三遍扫描**

- 第0遍：对指令进行预处理，去除首位空格，转换为大写，分离指令和注释
- 第1遍：创建符号表
- 第2遍：生成机器码

## TO BE DONE

### assembler.h

```c++
inline std::string &LeftTrim(std::string &s, const char *t = " \t\n\r\f\v") {
    // TO BE DONE
    bool tag=true;
    while (tag) {
        tag = false;
        for (int i = 0; i < 6; i++) {
            if (s[0] == t[i]) {
                tag = true;
                s = s.substr(1);
                break;
            }
        }
    }
    return s;
}

// trim from right
inline std::string &RightTrim(std::string &s, const char *t = " \t\n\r\f\v") {
    // TO BE DONE
    bool tag=true;
    while (tag) {
        tag = false;
        for (int i = 0; i < 6; i++) {
            if (s[s.length()-1] == t[i]) {
                tag = true;
                s = s.substr(0,s.length()-1);
                break;
            }
        }
    }
    return s;
}
```

分别去除字符串的左右空白符(" \t\n\r\f\v")

### assembler.cpp

```c++
int RecognizeNumberValue(std::string s) {
    // Convert string s into a number
    // TO BE DONE
    int result = 0;
    if (s[0] == 'X') {
        s = "0" + s;
        sscanf(s.c_str(), "%x", &result);
    } else if (s[0] == '#') {
        s = s.substr(1);
        sscanf(s.c_str(), "%d", &result);
    } else {
        sscanf(s.c_str(), "%d", &result);
    }
    return result;
}
```

对十六进制和十进制的表示进行识别，未指定时默认为十进制

```c++
std::string NumberToAssemble(const int &number) {
    // Convert the number into a 16 bit binary string
    // TO BE DONE
    std::string result;
    int mask = 1 << 15;
    for (int i = 0; i < 16; i++) {
        result += std::to_string((number & mask) != 0 ? 1 : 0);
        mask >>= 1;
    }
    return result;
}

std::string NumberToAssemble(const std::string &number) {
    // Convert the number into a 16 bit binary string
    // You might use `RecognizeNumberValue` in this function
    // TO BE DONE
    int num=RecognizeNumberValue(number);
    return NumberToAssemble(num);
}
```

将参数逐位与掩码求与并存入字符串中得到16bit结果

```c++
std::string ConvertBin2Hex(std::string bin)  {
    // Convert the binary string into a hex string
    // TO BE DONE
    int bit=1;
    int num = 0;
    for(int i=bin.size()-1;i>=0;i--){
        if(bin[i]=='1') num+=bit;
        bit<<=1;
    }
    std::ostringstream result;
    result<<std::hex<<num;
    return result.str();
}
```

将二进制表示的字符串转换为十六进制表示，使用std::hex实现

```c++
std::string assembler::TranslateOprand(int current_address, std::string str, int opcode_length) {
    // Translate the oprand
    std::string result;
    str = Trim(str);
    auto item = label_map.GetValue(str);
    if (!(item.getType() == vAddress && item.getVal() == -1)) {
        // str is a label
        // TO BE DONE
        int num = item.getVal() - (current_address + 1);
        int mask = 1 << (opcode_length - 1);
        for (int i = 0; i < opcode_length; i++) {
            result += std::to_string((num & mask) != 0 ? 1 : 0);
            mask >>= 1;
        }
    }
    else if (str[0] == 'R') {
        // str is a register
        // TO BE DONE
        int num=str[1]-'0';
        result+=std::to_string((num&4)!=0?1:0);
        result+=std::to_string((num&2)!=0?1:0);
        result+=std::to_string((num&1)!=0?1:0);
    } else {
        // str is an immediate number
        // TO BE DONE
        int num = RecognizeNumberValue(str);
        int mask = 1 << (opcode_length - 1);
        for (int i = 0; i < opcode_length; i++) {
            result += std::to_string((num & mask) != 0 ? 1 : 0);
            mask >>= 1;
        }
    }
    return result;
}
```

对操作数为lable、寄存器、立即数的三种情况分别转换为字符串

```c++
std::transform(line.begin(), line.end(), line.begin(), toupper);
```

使用transform函数实现大小写转换

```c++
std::string comment_str=line.substr(comment_position);
std::string content_str=line.substr(0,comment_position);
```

分离指令和注释

```c++
else if (pseudo_command == ".FILL") {
    // TO BE DONE
    file_address[line_index] = line_address;
    line_address++;
    std::string word;
    line_stringstream >> word;
    auto num_temp = RecognizeNumberValue(word);
    if (num_temp == std::numeric_limits<int>::max()) {
        // @ Error Invalid Number input @ FILL
        return -4;
    }
    if (num_temp > 65535 || num_temp < -65536) {
        // @ Error Too large or too small value  @ FILL
        return -5;
    }
} else if (pseudo_command == ".BLKW") {
    // TO BE DONE
    file_address[line_index] = line_address;
    std::string word;
    line_stringstream >> word;
    auto num_temp = RecognizeNumberValue(word);
    if (num_temp + line_address - 1 > 65535) {
        // @ Error Too large or too small value  @ BLKW
        return -5;
    }
    line_address += num_temp;
}
```

```c++
if (word == ".BLKW") {
    // modify label map
    // modify line address
    // TO BE DONE
    line_stringstream >> word;
    auto num_temp = RecognizeNumberValue(word);
    if (num_temp + line_address - 2 > 65535) {
        // @ Error Too large or too small value  @ BLKW
        return -5;
    }
    label_map.AddLabel(label_name, value_tp(vAddress, line_address - 1));
    line_address += num_temp - 1;
}
if (word == ".STRINGZ") {
    // modify label map
    // modify line address
    // TO BE DONE
    line_stringstream >> word;
    if (word[0] != '\"' || word[word.size() - 1] != '\"') {
        // @ Error String format error
        return -6;
    }
    auto num_temp = word.size() - 2;
    label_map.AddLabel(label_name, value_tp(vAddress, line_address - 1));
    line_address += num_temp;
}
```

对伪指令进行地址的计算

```c++
if (IsLC3Command(word) != -1 || IsLC3TrapRoutine(word) != -1) {
    // * This is an operation line
    // TO BE DONE
    file_tag[line_index] = lOperation;
    continue;
}
if (IsLC3Command(word) != -1 || IsLC3TrapRoutine(word) != -1 || word == "" || word == label_name) {
    // a label used for jump/branch
    // TO BE DONE
    file_tag[line_index] = lOperation;
    label_map.AddLabel(label_name, value_tp(vAddress, line_address - 1));
    if(word == label_name)
    {
        line_address--;
        file_tag[line_index] = lComment;
    }
}
```

修改代码行的tag

```c++
std::replace(parameter_str.begin(),parameter_str.end(),',',' ');
```

将指令中的逗号替换为空格以便分离操作数

后续将具体的指令转换为机器码的主要思路是获得操作码，识别出指令，获取操作数，将操作数通过`TranslateOprand`函数转换为字符串，具体实现见源码
