# 課題5 レポート
学生番号　35315020  氏名 下川大輝


## 課題
本課題では、以下の3つのプログラムを作成する。なお、出発駅、到着駅は、適宜変更しても良い。
- 赤迫駅を出発点として、深さ優先探索ですべての駅に到達可能なことを確認するプログラム。到達した駅名を出力するなど、各駅に1回到達したことを確認すること。  
- 赤迫駅を出発点として、幅優先探索ですべての駅に到達可能なことを確認するプログラム。到達した駅名を出力するなど、各駅に1回到達したことを確認すること。  
- 赤迫駅を出発点として、蛍茶屋駅までの最短所要時間ルートをダイクストラ法で見つけ、出力するプログラム
路線図、および、駅間の所要時間は下記のようになっている。  

1.使用するデータ  
路線図、及び、駅間の所要時間は下記のようになっている。なお、プログラムにおいて、駅名はArrayStation、グラフは隣接行列AdjacencyMatrixに保存されている。  

<img src=images/routemap.png width=600>  

```
typedef struct tagStation {
    char name[20];
    char kanji[16];
} Station;

Station ArrayStation[MAX_STATIONS] = {
    {"akasako", "赤迫"},
    {"nagasakidaigakumae", "長崎大学前"},
    {"nagasakiekimae", "長崎駅前"},
    {"shinchichukagai", "新地中華街"},
    {"ishibashi", "石橋"},
    {"sofukuji", "崇福寺"},
    {"shiminkaikan", "市民会館"},
    {"hotarujaya", "蛍茶屋"},
};

int AdjacencyMatrix[MAX_STATIONS][MAX_STATIONS] = {
    {0,  5,  0,  0,  0,  0,  0,  0},
    {5,  0, 16,  0,  0,  0,  0,  0},
    {0, 16,  0,  7,  0,  0,  5,  0},
    {0,  0,  7,  0,  7,  6, 10,  0},
    {0,  0,  0,  7,  0,  0,  0,  0},
    {0,  0,  0,  6,  0,  0, 10,  0},
    {0,  0,  5, 10,  0, 10,  0,  6},
    {0,  0,  0,  0,  0,  0,  6,  0},
};
```


2. 必須問題：実装する関数  
本課題では、以下の関数を実装する。  
(1) DepthFirstSearch: 深さ優先探索ですべての駅に到達可能なことを確認する  
    [入力]
    - int size: 駅の数　　
    - int matrix[size][size]: 隣接行列
    - int start: 出発駅のインデックス  

    [出力]  
    - なし。関数の出力はないが、関数内でprintf文を使うなど、すべての駅に到達可能なことをチェックすること。  


    (2) BreadthFirstSearch: 幅優先探索ですべての駅に到達可能なことを確認する  
    [入力]
    - int size: 駅の数　　
    - int matrix[size][size]: 隣接行列
    - int start: 出発駅のインデックス  

    [出力]  
    - なし。関数の出力はないが、関数内でprintf文を使うなど、すべての駅に到達可能なことをチェックすること。

    (3) SearchGraphByDijkstra: ダイクストラ法で、出発駅から到着駅までの最短所要時間ルートを探索する。  
    [入力]  
    - int start: 出発駅のインデックス
    - int goal: 到着駅のインデックス  
    - int size: 駅数  
    - int matrix[size][size]: 隣接行列  
    - NodeInfo arrayNodeInfo[size]:  

    [出力]  
    - return値: 出発駅から到着駅までの所要時間 
    - 関数内でprintf文を使い、最短ルートを出力すること

3. 補助関数  
以下の関数はすでに実装されており、利用することができる。
- PrintStationName: indexで指定される駅名を出力する
- StackInit: スタックを初期化する
- StackPush: スタックに値をプッシュする
- StackPop: スタックから値をポップする
- StackTop: スタックの先頭の値を取得する(スタックポインタは移動しない)
- StackIsEmpty: スタックが空か判断する。空の場合はTRUE、空でなければFALSEを返す。
- InitQueue: キューを初期化する
- EnQueue: キューに値を入れる
- DeQueue: キューから値を取り出す
- QueueIsEmpty: キューが空か判断する。空の場合はTRUE、空でなければFALSEを返す。
- main: メイン関数。深さ優先探索、幅優先探索、ダイクストラ法による最短経路探索処理を呼び出す。

4. チャレンジ課題  
赤迫駅を起点として、各駅にたどり着くまでのルートを、深さ優先探索、幅優先探索のそれぞれの場合で出力するようにプログラムを修正する。  
- 深さ優先探索のルート表示(10点)
- 幅優先探索のルート表示(10点)

## ソースコードの説明
void DepthFirstSearch(int size, int matrix[size][size], int start)
{
    int visited[size];
    int i;
    int index;  // 変数の宣言
    
    for(i=0;i<MAX_STATIONS;i++){
        visited[i] = UNVISITED;  //visitedを初期化させる
    }

    StackInit();
    StackPush(start); //startのpushを行う

    while(StackIsEmpty() == FALSE){ //index番目がUNVISITEDのときIDSITEDを代入
        index = StackPop();
        if(visited[index] == UNVISITED){
            visited[index] = VISITED;

            for(i=0;i<MAX_STATIONS;i++){
                if(matrix[index][i] != 0){ //その場所から行くことが可能な場所をindexへと代入
                    StackPush(i);
                }
            }
        }
    }

    for(i=0;i<MAX_STATIONS;i++){
        if(visited[i] == VISITED){
            printf("(DepthFirst)%s is visited\n", ArrayStation[i].kanji); //全てがVISITEDになったら出力
        }
    }
	
    //  ここを実装する

}



void BreadthFirstSearch(int size, int matrix[size][size], int start)
{
   int visited[size];
   int i;
   int index;  //変数宣言

   for(i=0;i<MAX_STATIONS;i++){　//visitedの初期化
       visited[i] = UNVISITED;
   }

   InitQueue(); // キューの初期化
   EnQueue(start);  //出発点のstartをキューにpush

   while(QueueIsEmpty() == FALSE){
       index = DeQueue();
       if(visited[index] == UNVISITED){  //index番目がUNVISITEDならばVISITEDを代入する
           visited[index] = VISITED;

           for(i=0;i<MAX_STATIONS;i++){
               if(matrix[index][i] != 0){ //その場所から行くことが可能な場所をキューへ
                   EnQueue(i);
               }
           }
       }
   }

   for(i=0;i<MAX_STATIONS; i++){
       if(visited[i] == VISITED){ 　　　//すべてがVISITEDになったら出力する
           printf("(BreadthFirst)%s is visited\n", ArrayStation[i].kanji);
       }
   }
    //  ここを実装する
}



## 出力結果

```
C:\Users\bb35315020\Downloads\プログラミング演習Ⅲ\2020psp3\k05>.\k05
(DepthFirst)赤迫 is visited
(DepthFirst)長崎大学前 is visited
(DepthFirst)長崎駅前 is visited
(DepthFirst)新地中華街 is visited
(DepthFirst)石橋 is visited
(DepthFirst)崇福寺 is visited
(DepthFirst)市民会館 is visited
(DepthFirst)蛍茶屋 is visited
(BreadthFirst)赤迫 is visited
(BreadthFirst)長崎大学前 is visited
(BreadthFirst)長崎駅前 is visited
(BreadthFirst)新地中華街 is visited
(BreadthFirst)石橋 is visited
(BreadthFirst)崇福寺 is visited
(BreadthFirst)市民会館 is visited
(BreadthFirst)蛍茶屋 is visited
Time Required: 4194432
```

## 修正履歴

