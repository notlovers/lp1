/*
 * Practical 1: Design suitable Data structures and implement Pass-I and Pass-II of a two-pass assembler for pseudo-machine. Implementation should consist of a few instructions from each category and few assembler directives. The output of Pass-I (intermediate code file and symbol table) should be input for Pass-II.
 * The Text Editor: VIM - Vi IMproved 9.0
 * The Compiler: Apple clang version 13.1.6 (clang-1316.0.21.2.3)
 * The Machine: MacBook Air M1 (Running ARM64 architecture)
 */
#include <iostream>
#include <cstdio>
#include <cstring>

int main() {
    const char* code[9][4] = {
        {"PRG1", "START", "",""},
        {"", "USING", "*", "15"},
        {"", "L", "", ""},
        {"", "A", "", ""},
        {"", "ST", "", ""},
        {"FOUR", "DC", "F", ""},
        {"FIVE", "DC", "1F", ""},
        {"TEMP", "DS", "1F", ""},
        {"", "END", "", ""}
    };
    
    char av[2], avail[15] = {'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N'};
    int i, j, k, count[3], lc[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}, loc = 0;
    
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "LABEL\t\tOPCODE" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;
    
    for (i = 0; i <= 8; i++) {
        for (j = 0; j <= 3; j++) {
            std::cout << code[i][j] << "\t\t";
        }
        j = 0;
        std::cout << std::endl;
    }
    
    std::cin.get();
    
    std::cout << "--------------------------------------------------";
    std::cout << std::endl << "VALUES FOR LC:" << std::endl << std::endl;
    
    for (j = 0; j <= 8; j++) {
        if ((strcmp(code[j][1], "START") != 0) && (strcmp(code[j][1], "USING") != 0) && (strcmp(code[j][1], "L") != 0))
            lc[j] = lc[j - 1] + 4;
        std::cout << lc[j] << "\t";
    }
    
    std::cout << std::endl << std::endl << "SYMBOL TABLE:" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "SYMBOL\t\tVALUE\t\tLENGTH\t\tR/A" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;
    
    for (i = 0; i < 9; i++) {
        if (strcmp(code[i][1], "START") == 0) {
            std::cout << code[i][0] << "\t\t" << loc << "\t\t" << "4" << "\t\t" << "R" << std::endl;
        }
        else if (strcmp(code[i][0], "") != 0) {
            std::cout << code[i][0] << "\t\t" << loc << "\t\t" << "4" << "\t\t" << "R" << std::endl;
            loc = 4 + loc;
        }
        else if (strcmp(code[i][1], "USING") == 0) {
            // Emptye if-statement
        }
        else {
            loc = 4 + loc;
        }
    }
    std::cout << "--------------------------------------------------" << std::endl;
    
    std::cout << std::endl << std::endl << "BASE TABLE:" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "REG NO\t\tAVALIABILITY\tCONTENTS OF BASE TABLE" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;
    
    for (j = 0; j <= 8; j++) {
        if (strcmp(code[j][1], "USING") != 0) {
            // Empty if-statement
        }
        else {
            strcpy(av, code[j][3]);
        }
    }
    
    count[0] = (int)av[0] - 48;
    count[1] = (int)av[1] - 48;
    count[2] = count[0] * 10 + count[1];
    avail[count[2] - 1] = 'Y';
    
    for (k = 0; k < 16; k++) {
        std::cout << k << "\t\t" << avail[k - 1] << std::endl;
    }
    
    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << "Continue..??" << std::endl;
    std::cin.get();
    
    std::cout << "PASS2 TABLE:" << std::endl << std::endl;
    std::cout << "LABLE\t\tOP1\t\tLC\t\t" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;
    
    loc = 0;
    for (i = 0; i <= 8; i++) {
        for (j = 0; j <= 3; j++) {
            std::cout << code[i][j] << "\t\t";
        }
        j = 0;
        
        std::cout << std::endl;
        std::cin.get();
    }
    std::cout << "--------------------------------------------------" << std::endl;
}
