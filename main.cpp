#include <iostream>
#include <map>
#include <string>
#include<fstream>
#include<sstream>
#include "GrammerAnalyzer.h"
using namespace  std;


int main() {
    GrammerAnalyzer analyzer;
    analyzer.init();
    analyzer.read_source_code();
    analyzer.lexicalAnalysis();
    analyzer.show();
    analyzer.inference();
}
