//
// Created by Administrator on 2020/11/6.
//
#include "GrammerAnalyzer.h"
void GrammerAnalyzer::read_source_code() {
    std::string file_name;
    while(1)
    {
        std::cout<<"Please input file name";
        std::cin>>file_name;
        infile.open(file_name);
        if(infile.fail())
        {
            std::cout<<"open failed";
        }
        else
            break;
    }
    char temp;
    while(infile.get(temp))
    {
        source_code+=temp;
    }
    std::cout<<source_code;
}
void GrammerAnalyzer::init() {
    for(auto i:delimiter_array)
    {
        delimiter_set.insert(i);
    }
    for(auto i:single_op)
    {
        single_op_set.insert(i);
    }
    for(auto i:double_op)
        double_op_set.insert(i);
    for(auto i:keywords_arrry)
        keywords_set.insert(i);
}
void GrammerAnalyzer::lexicalAnalysis() {
    int i=0;
    char ch;
    int state=0;
    std::string token;
    while(i<=source_code.length())
    {
        if(i!=source_code.length())
            ch=source_code[i];
        else
            ch=' ';
        switch(state) {
            case 0:
                token.clear();
                if (ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r' || ch == '\0') {
                    i++;
                    continue;
                } else if (delimiter_set.count(ch)) {
                    state = 1;
                    token = token + ch;
                    continue;
                } else if (single_op_set.count(ch)) {
                    state = 2;
                    token = token + ch;
                    continue;
                } else
                 if(ch>='0'&&ch<='9')
                 {   token+=ch;
                     state=3;continue;
                 }
                 else
                     if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||ch=='_')
                     {   state=4;
                         token=token+ch;
                         //i++;
                         continue;
                     }
                     else {
                         token += ch;
                         i++;
                         state = 0;
                         continue;
                     }
               case 1:{
                            TOKEN temp;
                            temp.type = delimiter;
                            temp.name =token;
                            switch (ch) {
                                case ';':
                                    temp.value = SEMI;
                                    break;
                                case ',':
                                    temp.value = COMMA;
                                    break;
                                case '{':
                                    temp.value = LBRACE;
                                    break;
                                case '}':
                                    temp.value = RBRACE;
                                    break;
                                case '(':
                                    temp.value = LBRACKET;
                                    break;
                                case ')':
                                    temp.value = RBRACKET;
                                    break;
                            }
                            token_list.push_back(temp);
                            i++;
                            state = 0;
                            continue;
                           }
            case 2: if(double_op_set.count(token+source_code[i+1]))
                    {
                          state=0;
                          token=token+source_code[i+1];
                          TOKEN temp;
                          temp.type=op;
                          temp.name=token;
                          if(token=="==")
                              temp.value=EQUAL;
                          else
                          if(token=="<=")
                              temp.value=LESSEQ;
                          else
                          if(token==">=")
                              temp.value=LARGEEQ;
                          else
                          if(token=="!=")
                              temp.value=NOTEQ;
                          else
                          if(token=="||")
                              temp.value=OR;
                          else
                          if(token=="&&")
                              temp.value=AND;
                          else
                          {
                              std::cout<<"unexcepted symbol"+token<<std::endl;
                              exit(-1);
                          }
                          token_list.push_back(temp);
                          i=i+2;
                         continue;
                    }
                    else
                    {
                            state=0;
                            i++;
                            TOKEN temp;
                            temp.type=op;
                            temp.name=token;
                            switch(ch){
                                case '=':temp.value=ASSIG;
                                        break;
                                case '+':temp.value=PLUS;
                                         break;
                                case '-':temp.value=MINUS;
                                        break;
                                case '*':temp.value=TIMES;
                                        break;
                                case '/':temp.value=DIVIDE;
                                        break;
                                case '<':temp.value=LESS;
                                        break;
                                case '>':temp.value=LARGE;
                                        break;
                                case '!':temp.value=NOT;
                                        break;
                                default: break;
                            }
                            token_list.push_back(temp);
                            continue;
                   }
            case 3: {
                int num = ch - '0';
                while (source_code[i + 1] >= '0' && source_code[i + 1] <= '9') {

                    i++;
                    ch = source_code[i];
                    token+=ch;
                    num = num * 10 + ch - '0';
                }
                i++;
                TOKEN temp;
                temp.type = constant;
                temp.name=token;
                temp.value = NUM;
                temp.const_value = num;
                token_list.push_back(temp);
                state = 0;
                continue;
            }
            case 4:
                   while((source_code[i+1]>='a'&&source_code[i+1]<='z')||(source_code[i+1]>='A'&&source_code[i+1]<='Z')||source_code[i+1]=='_')
                   {
                       i++;
                       token+=source_code[i];
                   }

                   if(keywords_set.count(token))
                   {
                       TOKEN temp;
                       temp.type=keywords;
                       temp.name=token;
                       if(token=="if")
                           temp.value=IF;
                       if(token=="else")
                           temp.value=ELSE;
                       if(token=="while")
                           temp.value=WHILE;
                       if(token=="int")
                           temp.value=INT;
                       if(token=="bool")
                           temp.value=BOOLEAN;
                       if(token=="main")
                           temp.value=MAIN;
                       token_list.push_back(temp);
                   }
                   else
                   {
                       TOKEN temp;
                       temp.type=identifer;
                       temp.value=ID;
                       temp.name=token;
                       token_list.push_back(temp);
                   }
                   i++;
                   state=0;
                   continue;
        }
    }
    TOKEN temp;
    temp.type=0;
    temp.value=END;
    token_list.push_back(temp);
}
void GrammerAnalyzer::show() {
    for(auto i:token_list)
        std::cout<<i.type<<"  "<<toString(i.value)<<"  "<<i.name<<"  "<<i.const_value<<std::endl;
}
void GrammerAnalyzer::next()
{
     if(index<token_list.size())
     {    ++index;
         token_now=token_list[index];
     }
}
void GrammerAnalyzer::match(int i) {
    if(token_now.value==i)
      next();
    else
       std::cout<<"meeting an unexcepted symbol"<<std::endl;
}
std::string GrammerAnalyzer::toString(int i) {
        switch(i)
        {
            case 5:return "if";
            case 6:return "else";
            case 7:return "while";
            case 8:return "for";
            case 9:return "comma";
            case 10:return "semi";
            case 11:return "lbracket";
            case 12:return "rbracket";
            case 13:return "lbrace";
            case 14:return "rbrace";
            case 15:return "int";
            case 16:return "char";
            case 17:return "boolean";
            case 18:return "plus";
            case 19:return "minus";
            case 20:return "times";
            case 21:return "divide";
            case 22:return "or";
            case 23:return "xor";
            case 24:return "and";
            case 25:return "equal";
            case 26:return "lesseq";
            case 27:return "largeeq";
            case 28:return  "less";
            case 29:return "large";
            case 30:return "assign";
            case 31:return "num";
            case 32:return "id";
            case 33:return "main";
        }
}
void GrammerAnalyzer::statement() {
    if(token_now.value==LBRACE)
    {
        match(LBRACE);
        while(token_now.value!=RBRACE)
             statement();
        match(RBRACE);
    }else
    if(token_now.value==INT)
    {
        match(INT);
        std::string id_name=token_now.name;
        match(ID);
        match(ASSIG);
        int rvalue=expression();
        id_map[id_name]=rvalue;
        match(SEMI);
    }
    else
    if(token_now.value==ID)
    {
        std::string id_name=token_now.name;
        match(ID);
        match(ASSIG);
        int rvalue=expression();
        id_map[id_name]=rvalue;
        match(SEMI);
    }
    else
        if(token_now.value==IF)
        {
            match(IF);
            match(LBRACKET);
            bool flag=boolOR();
            match(RBRACKET);
            if(flag) {
                statement();
                if(token_now.value==ELSE) {
                    match(ELSE);
                    skip();
                }
                return;
            }
            else
            {
                skip();
                if(token_now.value==ELSE)
                {
                    match(ELSE);
                    statement();
                }
            }
        }
}
int GrammerAnalyzer::expression() {
      int temp=term();
      while(token_now.value==PLUS||token_now.value==MINUS)
      {
          if(token_now.value==PLUS) {
              match(PLUS);
              temp += term();
          }
          else {
              match(MINUS);
              temp -= term();
          }
      }
      return temp;
}
int GrammerAnalyzer::term() {
    int temp=factor();
    while(token_now.value==TIMES||token_now.value==DIVIDE)
    {
        if(token_now.value==TIMES) {
            match(TIMES);
            temp *= factor();
        }
        else {
            match(DIVIDE);
            temp /= factor();
        }
    }
    return temp;
}
int GrammerAnalyzer::factor()
{
    if(token_now.value==NUM) {
        match(NUM);
        return token_now.const_value;
    }
    else
        if(token_now.value==ID)
        {  std::string id_name=token_now.name;
           match(ID);
            return id_map[id_name];
        }

        else
            if(token_now.value=LBRACKET)
            {
                match(LBRACKET);
                int temp=expression();
                match(RBRACKET);
                return temp;
            }
            else
                return 0;
}
bool GrammerAnalyzer::boolexp() {
    int lvalue = expression();
    if (token_now.value == LESS) {
        match(LESS);
        int rvalue = expression();
        return lvalue < rvalue;
    } else if (token_now.value == LARGE)
            {
               match(LARGE);
               int rvalue=expression();
               return lvalue>rvalue;
             }
    else if(token_now.value==LESSEQ)
    {
        match(LESSEQ);
        int rvalue=expression();
        return lvalue<=rvalue;
    }
    else
        if(token_now.value==LARGEEQ)
        {
            match(LARGEEQ);
            int rvalue=expression();
            return lvalue>=rvalue;
        }
}
void GrammerAnalyzer::inference() {
    token_now=token_list[index];
    while(token_now.value!=END)
        statement();
}
void GrammerAnalyzer::skip() {
    int count=0;
    if(token_now.value==LBRACE) {
        match(LBRACE);
        count++;
        while (1) {
            if (token_now.value == LBRACE) {
                match(LBRACE);
                count++;
            } else if (token_now.value == RBRACE) {
                match(RBRACE);
                count--;
                if (!count)
                    break;
            } else
                next();
        }
    }
}


bool GrammerAnalyzer::boolOR() {
    bool flag=boolAND();
    while(token_now.value==OR)
    {
        match(OR);
       // if(flag) return flag;
        bool flag2=boolAND();
        flag=flag||flag2;
    }
    return flag;
}
bool GrammerAnalyzer::boolAND() {
    bool flag=boolexp();
    while(token_now.value==AND)
    {
        match(AND);
        flag=flag&&boolAND();
    }
    return flag;
}