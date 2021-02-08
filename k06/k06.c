#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#if 0
//  デバッグ用データ
#define NAP_SIZE    15

#define NUM_ITEMS   6
typedef struct {
    int price;
    int calorie;    
} Menu;

Menu ArrayItem[] = {
    {1, 2},
    {2, 3},
    {3, 1},
    {4, 4},
    {5, 8},
    {11, 15}
};
#endif

#if 1
#define NAP_SIZE    1000    //  所持金(1000円)
#define NUM_ITEMS   135     //  メニュー数   
typedef struct tagMenu{
    int id;         //  メニューのID
    char name[91];  //  メニューの名前
    char category[10];  //  カテゴリ
    char type[15];  //  タイプ
    int price;      //  価格
    int calorie;    //  カロリー
    float salt;     //  塩分量
} Menu;


int LoadData(Menu arrayItem[])
{
    FILE* fp;
    int cn = 0;
    char buf[256];

    fp = fopen("saizeriya.csv", "r");
    if(fp==NULL){
        fputs("File open error\n",stderr);
        return -1;
    }

    while(fgets(buf,sizeof(buf),fp) != NULL){
        sscanf(buf,"%d,%[^,],%[^,],%[^,],%d,%d,%f", 
            &(arrayItem[cn].id), arrayItem[cn].name, arrayItem[cn].category, arrayItem[cn].type, 
            &(arrayItem[cn].price), &(arrayItem[cn].calorie), &(arrayItem[cn].salt));
        cn++;
    }

    if(fclose(fp) == EOF){
        fputs("file close error\n",stderr);
        return -1;
    }

    return cn;
}
#endif


void DynamicProgLimited(Menu arrayItem[], int items, int nap_size)
{
    int nap_value[items+1][nap_size + 1];  
    int history[items+1][nap_size + 1];    

    int i,j,k,pre_j,cur_j;

    printf("input (items,nap_size) = (%d,%d)\n",items,nap_size);

    for(i = 0; i <= NUM_ITEMS; i++){   
        for(j = 0; j <= NAP_SIZE; j++){
            nap_value[i][j] = 0;   
            history[i][j] = 0;
        }
    }



    for(i = 1; i <= NUM_ITEMS; i++){    
        for(j = 1; j < arrayItem[i-1].price; j++){ 
            nap_value[i][j] = nap_value[i-1][j];
            history[i][j] = j; 
        }

        for(j; j <= NAP_SIZE; j++){   
            if(nap_value[i-1][j] < nap_value[i-1][j-arrayItem[i-1].price] + arrayItem[i-1].calorie){
                nap_value[i][j] = nap_value[i-1][j-arrayItem[i-1].price] + arrayItem[i-1].calorie; 
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


int main(void)
{
    Menu* arrayItem;
    int cnt;

    arrayItem = (Menu*)malloc(sizeof(Menu) * NUM_ITEMS);
    cnt = LoadData(arrayItem);

    //  動的プログラムで最大摂取カロリーを求める
    DynamicProgLimited(arrayItem, cnt, NAP_SIZE);

    return 0;
}