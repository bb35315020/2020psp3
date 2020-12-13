#include <stdio.h>
#include <string.h>

#define DEBUG

#define ALPHABET_LEN    255

char StrOriginal[] = "On a dark deseart highway, cool wind in my hair.";
char StrKey[] = "wind";

char* ForceSearch(char text[], char key[])
{
    int start = 0;
    int pos = 0;
    int find = 0;
    int text_len = strlen(text);
    int key_len = strlen(key);

    for(start; start < (text_len - key_len); start++){
        for(pos; pos < key_len; pos++){
            if(text[start+pos] == key[pos]){
                if(pos==key_len - 1){
                    find=1;
                    break;
                }
            }
            else{
                break;
            }
        }
        if(find==1){
            break;
        }
    }
    if(pos==key_len-1){
        return text + start;
    }
    else{
        return NULL;
    }
    //  ここを実装する
}

char* BMSearch(char text[], char key[])
{
    int index = 0;
    int key_index = 0;
    int find = 0;
    int index_bf;
    int text_len = strlen(text);
    int key_len = strlen(key);
    int table[ALPHABET_LEN];

    for(index; index < ALPHABET_LEN; index++)  {
        table[index]=key_len;
    }
    for(key_index; key_index < key_len; key_index++){
        table[(int)key[key_index]]=key_len - 1 - key_index;
    }

    index = key_len - 1;

    while(index < text_len){
        index_bf=index;
        for(key_index=key_len-1; key_index >= 0; key_index--){
            if(text[index]==key[key_index]){
                
                index=index-1;

                if(key_index == 0){
                    find=1;
                    break;
                }
            }
            else{
                index = index + table[(int)text[index]];

                if(index <= index_bf){
                    index = index_bf +1;
                }
                break;
            }
        }
        if(find==1){
            break;
        }
    }
    if(key_index==0){
        return text + index+1;
    }
    else{ 
        return NULL;
    }
    //  ここを実装する
}

int main(void)
{
    char*   str;
    str = ForceSearch(StrOriginal, StrKey);
    printf("Force Search. Find keyword at:%s\n", str);

    str = BMSearch(StrOriginal, StrKey);
    printf("BM Search. Find keyword at:%s\n", str);

    return 0;
}