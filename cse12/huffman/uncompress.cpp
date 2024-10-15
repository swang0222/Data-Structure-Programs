#include <iostream>
#include "HCTree.hpp"
#include "Helper.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    const int argNum = 3;
    if (argc != argNum) {
        error("Incorrect number of arguments");
    }
    FancyInputStream inputStream(argv[1]);
    FancyOutputStream outputStream(argv[2]);

    HCTree hct;
    vector<int> hccode(256,0);

    if (inputStream.filesize() > 0) {
        for (int i = 0;i < 256; i++) {
            hccode[i] = inputStream.read_int();
        }
        
        hct.build(hccode);

        while(inputStream.good()) {
            unsigned char code = hct.decode(inputStream);
            if (code == '\0') {
                continue;
            }
            outputStream.write_byte(code); 
        }
    
        inputStream.reset();
        outputStream.flush();
    }

    
}
