# 課題6 レポート
学生番号 35315020　氏名  下川大輝


## 課題
所持金1,000円でサイゼリヤに行ったとき、最大限カロリーを多く取得できるメニューの組合せを求めるプログラムを作成する。

1. 使用するデータ  
サイゼリヤのメニューデータは、saizeriya.csvに保存されている。saizeriya.csvには、csv形式で以下のデータが含まれる。
    - メニューのID
    - メニューの名前
    - カテゴリ
    - タイプ
    - 価格
    - カロリー
    - 塩分量

    サイゼリヤのメニューは、プログラム起動時に、下記の構造体配列に読み込まれる
```
typedef struct tagMenu{
    int id;         //  メニューのID
    char name[91];  //  メニューの名前
    char category[10];  //  カテゴリ
    char type[15];  //  タイプ
    int price;      //  価格
    int calorie;    //  カロリー
    float salt;     //  塩分量
} Menu;
```


所持金、メニュー数はプログラム内で下記のように定義されている。


```
#define NAP_SIZE    1000    //  所持金(1000円)
#define NUM_ITEMS   135     //  メニュー数   
```

2. 必須問題：実装する関数  
本課題では、以下の関数を実装する。  
(1) DYnaicProgLimited: 動的計画法を用いて、1,000円で最大取得可能なカロリーを求める。  
    [入力]
    - Menu arrayItem[]: メニューデータの配列  
    - int items: メニュー数  
    - int nap_size: 所有金額(1,000円)  

    [出力]  
    - なし。ただし、関数内で、printf文を用いて、最大取得可能カロリーを出力すること。  

    [その他]  
    関数内に定義してある変数は参考であり、使用しても使用しなくても良い。



3. 補助関数  
以下の関数はすでに実装されており、利用することができる。
    - LoadData: サイゼリヤのメニューをファイルから読み込み、Menu型の配列arrayItemに格納する。  
    - main: メイン関数。データのロード、最大摂取カロリーを計算する処理を呼び出す。  


4. チャレンジ問題  
(1) 最大カロリーを取得できるメニューを表示するようにプログラムを修正する。(10点)  
(2) プログラムが出力した最大カロリーが正しいか検証する方法を考え、実際に検証してみる。(15点)  



## ソースコードの説明

void DynamicProgLimited(Menu arrayItem[], int items, int nap_size)
{
    int nap_value[items+1][nap_size + 1];  
    int history[items+1][nap_size + 1];    

    int i,j,k,pre_j,cur_j;

    printf("input (items,nap_size) = (%d,%d)\n",items,nap_size);

    for(i = 0; i <= NUM_ITEMS; i++){     //表を0で初期化する。
        for(j = 0; j <= NAP_SIZE; j++){
            nap_value[i][j] = 0;   
            history[i][j] = 0;
        }
    }

    
    for(i = 0; i <= NUM_ITEMS; i++){  //表に0以外の値が入っていたらプログラムを終了する。
        for(j = 0; j <= NAP_SIZE; j++){
            if(nap_value[i][j] != 0){    
                printf("Initialization failure\n");
                exit(1);
            }
        }
    }
    


    for(i = 1; i <= NUM_ITEMS; i++){    
        for(j = 1; j < arrayItem[i-1].price; j++){  //価格が収まりきらない場所まで上の状態を引き継ぐ。
            nap_value[i][j] = nap_value[i-1][j];
            history[i][j] = j;  //historyにベースとなったセルのjを記録。
        }

        for(j; j <= NAP_SIZE; j++){     NAP_SIZE列まで処理を続ける。
            if(nap_value[i-1][j] < nap_value[i-1][j-arrayItem[i-1].price] + arrayItem[i-1].calorie){
                nap_value[i][j] = nap_value[i-1][j-arrayItem[i-1].price] + arrayItem[i-1].calorie;  //新しい商品を入れる方が大きくなる場合入れることができる。
                history[i][j] = j - arrayItem[i-1].price;
            }else{
                nap_value[i][j] = nap_value[i-1][j];
                history[i][j] = j;
            }
        }
    }

    printf("max calorie = %d\n",nap_value[NUM_ITEMS][NAP_SIZE]);

    printf("---[Included menu]---\n");

    cur_j = NAP_SIZE;
    for(i = NUM_ITEMS; i > 0; i--){
        pre_j = history[i][cur_j];

        if(pre_j != cur_j){
            printf("%d:%s\n",arrayItem[i-1].id,arrayItem[i-1].name);

            cur_j = pre_j;
        }
    }


}


## 出力結果

```
C:\Users\bb35315020\Downloads\プログラミング演習Ⅲ\2020psp3\k06>.\k06
input (items,nap_size) = (135,1000)
max calorie = 1796
---[Included menu]---
120:"ラージライス"
86:"パルマ風スパゲッティ（Wサイズ）"
```

## 修正履歴

