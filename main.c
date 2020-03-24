#include <stdio.h>
#include <stdlib.h>
#include <openssl/crypto.h>

struct block{
    unsigned char prevHash[SHA256_DIGEST_LENGTH];
    int blockData;
    struct block *link;
}*head;

void addBlock(int data){
    if(head == NULL){
        head = malloc(sizeof(struct block))
        SHA256("", sizeof(""), head->prevHash);
        head->blockData = data;
        return;
    }
}

int main(){
    return 0;
}
