//
// Created by Administrator on 2020/11/6.
//
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#ifndef FORMALSEMANTIC_GRAMMERANALYZER_H
#define FORMALSEMANTIC_GRAMMERANALYZER_H

#endif //FORMALSEMANTIC_GRAMMERANALYZER_H
enum{
    delimiter=0,keywords,identifer,constant,op
};//token_type
enum{
    IF=5,ELSE=6,WHILE=7,FOR=8,COMMA=9,SEMI=10,LBRACKET=11,RBRACKET=12,LBRACE=13,RBRACE=14,INT=15,
    CHAR=16,BOOLEAN=17,PLUS=18,MINUS=19,TIMES=20,DIVIDE=21,OR=22,XOR=23,AND=24,EQUAL=25,LESSEQ=26,
    LARGEEQ=27,LESS=28,LARGE=29,ASSIG=30,NUM=31,ID=32,MAIN=33,END,NOT,NOTEQ
};//token_value
struct TOKEN
{
    int type;
    int value;
    std::string name;//the name of identifer
    int const_value;
};
class GrammerAnalyzer{
private:
    std::ifstream infile;
    std::string source_code;
    std::vector<TOKEN> token_list;
    char delimiter_array[6]={',',';','(',')','{','}'};
    char single_op[10]={'=','+','-','*','/','<','>','!','|','&'};
    std::string keywords_arrry[6]={"if","else","while","int","bool","main"};
    std::string double_op[6]={"==","<=",">=","!=","||","&&"};
    std::set<char> delimiter_set;
    std::set<char> single_op_set;
    std::set<std::string> double_op_set;
    std::set<std::string> keywords_set;
    int index=0;
    TOKEN token_now;
    std::map<std::string,int> id_map;
public:void init();
       void read_source_code();
       void lexicalAnalysis();
       void show();
       std::string  toString(int);
       void next();
       void inference();
       void statement();
       void match(int);
       int expression();
       int term();
       int factor();
       bool boolexp();
       bool boolOR();
       bool boolAND();
       void skip();
};