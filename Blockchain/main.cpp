#include <iostream>
#include <ctime>
#include <sstream>
#include <openssl/sha.h>

using namespace std;

string sha256(const string &str);

class Block {
public:
    string prevHash;
    string bHash;
    string data;
    time_t timestamp;
    int nonce;

    Block(string data, string prevHash){
          this->data = data;
          this->prevHash = prevHash;
          this->nonce = 0;
          this->timestamp = time(nullptr);
          this->bHash = calcHash();
    }
    string calcHash()const{
        stringstream ss;
        ss<< prevHash << timestamp << data << nonce;
        return sha256(ss.str());
    }

    void mine(int diff){
        string target(diff,'0');
        while (hash.substr(0,diff) != target){
            nonce++;
            hash = calcHash();
        }
        cout << "Mined the block" << hash << endl;
    }
};

class Blockchain {
public:
    Blockchain(diff):difficulty(diff){
        chain.push_back(createGenBlock());
    }

    void addBlock(Block block){
        block.prevHash = latestBlock().hash;
        block.mine(diff);
        chain.push_back(block);
    }

    Block latestBlock(){
        return chain.back();
    }

private:
    int difficulty;
    vector<Block> chain;

    Block createGenBlock() const{
        return Block("Gen Block", "0");
    }
};
int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
