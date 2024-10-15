#include <iostream>
#include "HCTree.hpp"
#include "Helper.hpp"

using namespace std;

int main(int argc, char* argv[]) {

    const int argNum = 3;
    if (argc != argNum) {
        error("Incorrect number of arguments");
    }

    HCTree hct;
    vector<int> freq(256, 0);

    FancyInputStream inputStream(argv[1]);
    FancyOutputStream outputStream(argv[2]);

    while(inputStream.good()) {
        int symbol = inputStream.read_byte();
        if (symbol == -1) {
            break;
        }
        freq[symbol] ++;
    }
    if (inputStream.filesize() > 0) {
        for (unsigned int i = 0; i < freq.size(); i++) {
            outputStream.write_int(freq[i]);
        }
    }
    
    for (unsigned int i = 0; i < freq.size(); i++) {
        cout << freq[i] << " ";
    }
    int curr_symbol;
    hct.build(freq);

    inputStream.reset();
    while (inputStream.good()) {
        curr_symbol = inputStream.read_byte();
        if (curr_symbol == -1) {
            break;
        }
        hct.encode(curr_symbol, outputStream);
    }
    
    inputStream.reset();
    outputStream.flush();
}
