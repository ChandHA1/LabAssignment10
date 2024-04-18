#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie{	
    int count;
    struct Trie * children[26];
};

// Initializes a trie structure
struct Trie *createTrie(){
    struct Trie * t = (struct Trie *)malloc(sizeof(struct Trie));
    if(t == NULL)exit(-1);
    for(int i = 0; i < 26; i++){
        t->children[i] = NULL;
    }    
    t->count = 0;
    return t;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word){
    //increases the root count if the string is empty
    if(strcmp(word,"") == 0)
        pTrie->count += 1;

    //iterates through a temp tree for the word length
    struct Trie * temp = pTrie;
    for(int i = 0; i < strlen(word); i++){
        if(temp->children[word[i] - 97] == NULL){
            temp->children[word[i] - 97] = createTrie();
        }
        temp = temp->children[word[i] - 97];
    }
    temp->count += 1;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word){
    //temp pointer to iterate through trie
    struct Trie * temp = pTrie;
    for(int i = 0; i < strlen(word); i++){
        if(temp->children[word[i]-97] == NULL){
            return 0;
        }
        temp = temp->children[word[i]-97];
    }
    return temp->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie){
    if(pTrie == NULL){
        return pTrie;
    }
    for(int i = 0; i < 26; i++){
        if(pTrie->children[i] != NULL){
            return deallocateTrie(pTrie->children[i]);
        }
    }
    free(pTrie);
    pTrie = NULL;
    return pTrie;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords){
    //varible to store the number of words
    int num;

    
    //file pointer
    FILE * dict = fopen(filename, "r");
    if(dict == NULL)return -1;

    //scans the number of words an loops to scan each word
    fscanf(dict, "%d", &num);
    for(int i = 0; i < num; i++){
        pInWords[i] = (char*)malloc(sizeof(char)*256);
        if(pInWords[i] == NULL)return -1;
        fscanf(dict, "%s", pInWords[i]);
    }

    return num;
}

int main(void){
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}