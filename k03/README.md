# 課題3 レポート
学生番号　35315020  氏名  下川大輝


## 課題  

以下の2つのアルゴリズムで文字列を検索するプログラムを作成する。  
- 力ずく法
- BM法

1. 使用するデータ  
以下のデータを使用する。ただし、検索対象文字列、検索する文字列は変更しても良い。  
    - StrOriginal: 検索対象データ
    - StrKey: 検索する文字列

2. 必須問題：実装する関数  
本課題では、以下の関数を実装する。C言語の標準ライブラリは使用しないこと。  
    (1) ForceSearch: 力ずく法で文字列を検索する。  
    [入力]  
    - char text[]: 検索対象文字列  
    - char key[]: 検索する文字列  

    [出力]  
    - return値：検索する文字列が出現した場所(ポインタ)。ただし、検索する文字列が見つからない場合はNULL。  

    (2) BMSearch: BM法で文字列を検索する。  
    [入力]  
    - char text[]: 検索対象文字列  
    - char key[]: 検索する文字列  
 
    [出力]  
    - return値：検索する文字列が出現した場所(ポインタ)。ただし、検索する文字列が見つからない場合はNULL。  

3. 補助関数  
なし

## ソースコードの説明
char* ForceSearch(char text[], char key[]) //力ずく法で文字列を検索
{
    int start = 0;
    int pos = 0;
    int find = 0;
    　　　　　　　　　　//変数の定義
    int text_len = strlen(text);
    int key_len = strlen(key);
                      //文字列の長さの調査
    for(start; start < (text_len - key_len); start++){　//検索する文字列より小さい間繰り返す
        for(pos; pos < key_len; pos++){
            if(text[start+pos] == key[pos]){
                if(pos==key_len - 1){
                    find=1;
                    break;　//findが1の時繰り返しを抜ける
                }
            }
            else{
                break;
            }
        }
        if(find==1){
            break;　//findが１の時繰り返しを抜け出す
        }
    }
    if(pos==key_len-1){
        return text + start;
    }
    else{
        return NULL;　//検索する文字列がない場合ＮＵＬＬを返す
    }
}

char* BMSearch(char text[], char key[])　//ＢＭ法で文字列を検索する
{
    int index = 0;
    int key_index = 0;
    int find = 0;
    int index_bf;
    int text_len = strlen(text);
    int key_len = strlen(key);
    int table[ALPHABET_LEN];
    　　　　　　　　　　　　//変数の定義

    for(index; index < ALPHABET_LEN; index++)  {
        table[index]=key_len;
    }
    for(key_index; key_index < key_len; key_index++){
        table[(int)key[key_index]]=key_len - 1 - key_index;
    }
　　　　　　　　　　　　　//ずらし量テーブルの作成
    index = key_len - 1;

    while(index < text_len){
        index_bf=index;
        for(key_index=key_len-1; key_index >= 0; key_index--){　//key_indexが0以上の間繰り返す
            if(text[index]==key[key_index]){
                
                index=index-1;

                if(key_index == 0){
                    find=1;
                    break;
                }　　　　//検索する文字列の1部があったら1文字前も確認し一致していた場合findを1として、繰り返しを抜ける
            }
            else{
                index = index + table[(int)text[index]];

                if(index <= index_bf){
                    index = index_bf +1;
                }
                break;
            }　//検索する文字列の一部がない場合ずらし量テーブルにより次の開始位置を決め、indexが開始位置より前にあったら1つずらす
        }
        if(find==1){
            break;　//findが1のとき繰り返しを抜ける
        }
    }
    if(key_index==0){
        return text + index+1;
    }
    else{ 
        return NULL; //検索する文字列がなければＮＵＬＬを返す
    }
}



## 出力結果

```
C:\Users\bb35315020\Downloads\プログラミング演習Ⅲ\2020psp3\k03>.\k03
Force Search. Find keyword at:wind in my hair.
BM Search. Find keyword at:wind in my hair.

```

## 修正履歴

