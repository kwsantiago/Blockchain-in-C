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
    struct block *currentBlock = head;
    while(currentBlock->link)
        currentBlock = currentBlock->link;
    struct block *newBlock = malloc(sizeof(struct block));
    currentBlock->link = newBlock;
    newBlock->blockData = data;
    SHA256(toString("*currentBlock"), sizeof(*currentBlock), newBlock->prevHash);
}

void verifyChain(){
    if(head == NULL){
        printf("Blockchain is empty! Try again after adding blocks");
        return;
    }
    struct block *curr = head->link, *prev = head;
    int count = 1;
    while(curr){
        printf("%d\t[%d]\t", count++, curr->blockData);
        hashPrinter(SHA256(toString(*prev), sizeof(*prev), NULL));
        printf("\n");
        hashPrinter(curr->prevHash, SHA256_DIGEST_LENGTH);
        if(hashCompare(SHA256(toString(*prev), sizeof(*prev), NULL), curr->prevHash))
            printf("Verification has succeeded!\n");
        else
            printf("Verification has failed.\n");
        prev = curr;
        curr = curr->link;
    }
}

int main(){
    return 0;
}
