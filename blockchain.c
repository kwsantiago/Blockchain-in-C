#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/crypto.h>

struct block{
    unsigned char prevHash[SHA256_DIGEST_LENGTH];
    int blockData;
    struct block *link;
}*head;

void addBlock(int data);
void verifyChain();
void alterNthBlock(int n, int newData);
void attackChain();
int hashCompare(unsigned char*, unsigned char*);
void hashPrinter(unsigned char hash[], int length){
unsigned char* toString(struct block);
void printBlock(struct block *b){
void printAllBlocks();

void addBlock(int data){
    if(head == NULL){
        head = malloc(sizeof(struct block));
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

void alterNthBlock(int n, int newData){
    struct block *curr = head;
    if(curr == NULL){
        printf("%n block does not exist.\n", n);
        return;
    }

    while(count != n){
        if(curr->link == NULL && count != n){
            printf("%n block does not exist.\n", n);
            return;
        }
        else if(count == n)
            break;
        curr = curr->link;
        count++;
    }
    printf("Before: ");
    curr->blockData = newData;
    printf("After: ");
        printBlock(curr);
    printf("\n");
}

void attackChain(){
    struct block *curr = head, *prev = NULL;
    if(curr == NULL){
        printf("Blockchain is empty! Try again after adding blocks");
        return;
    }
    while(1){
        prev = curr;
        curr = curr->link;
        if(curr == NULL)
            return;
        if(!hashCompare(SHA256(toString(*prev), sizeof(*prev), NULL), curr->prevHash)){
            hashPrinter(
                    SHA256(toString(*prev), curr->prevHash),
                    SHA256_DIGEST_LENGTH
            );
            printf("\n");
        }
    }
}

unsigned char* toString(struct block b){
    unsigned char *str = malloc(sizeof(unsigned char)*sizeof(b));
    memcpy(str, &b, sizeof(b));
    return str;
}

void hashPrinter(unsigned char hash[], int length){
    for(int i = 0; i < length; i++)
        printf("%02x", hash[i]);
}

int hashCompare(unsigned char &str1, unsigned char *str2){
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        if(str1[i] != str2[i])
            return 0;
    return 1;
}

void printBlock(struct block *b){
    printf("%p]t", b);
    hashPrinter(b->prevHash, sizeof(b->prevHash));
    printf("\t[%d]\t", b->blockData);
    printf("%p\n", b->link);
}

void printAllBlocks(){
    struct block *curr = head;
    int count = 0;
    while(curr){
        printBlock(curr);
        curr = curr->next;
    }
}

void main(){
    int choice, n , r;
    printf("1: Add Block\n2: Add n random blocks\n3: Alter Nth block\n4: Print all blocks\n5: Verify Chain\n6: Attack Chain");
    while(1){
        printf("> ");
        scanf("%d", &choice);
        switch(choice){
            case 1: 
                printf("Enter data: ");
                scanf("%d", &n);
                break;
            case 2:
                printf("Amount of blocks to add: ");
                scanf("%d", choice);
                for(int i = 0; i < n; i++){
                    r = rand() % (n * 10);
                    printf("Entering: %d", r);
                    addBlock(r);
                }
                break;
            case 3:
                printf("Block to alter: ");
                scanf("%d", &n);
                printf("Enter value: ");
                scanf("%d", &r);
                alterNthBlock(n, r);
                break;
            case 4:
                printAllBlocks();
                break;
            case 5:
                verifyChain();
                break;
            case 6:
                attackChain();
                break;
            default:
                printf("Pick something!");
                break;
        }
    }
}
