
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define KEYLENGTH 11	//关键词字符串最大长度
#define MAXTABLESIZE 1000000 //允许开辟的最大散列表长度
#define MAXD 5 //参与散列映射计算的字符个数
typedef char ElementType[KEYLENGTH + 1];
typedef int Index; //散列地址类型

//单链表定义
typedef struct LNode *PtrToLNode;
struct LNode {
    ElementType Data;
    PtrToLNode Next;
    int Count;
};
typedef PtrToLNode Position;
typedef PtrToLNode List;

//散列表结点定义
typedef struct TblNode *HashTable;	//散列表类型
struct TblNode {
    int TableSize; //表的最大长度
    List Heads;	   //指向链表头结点的数组
};

int NextPrime( int N ) {
    //返回大于N且不超过MAXTABLESIZE的最小素数
    int i, p = ( N % 2 ) ? N + 2 : N + 1;	//从大于N的下一个奇数开始
    while ( p <= MAXTABLESIZE ) {
        double q = p;
        for ( i = (int)sqrt(q); i > 2; i-- )
            if ( !(p % i) ) break; //p不是素数
        if ( i == 2 ) break; // for正常结束，说明p是素数
        else p += 2; //否则试探下一个奇数
    }
    return p;
}

HashTable CreateTable ( int TableSize ) {
    HashTable H;
    int i;
    H = (HashTable)malloc(sizeof(struct TblNode));
    H->TableSize = NextPrime(TableSize);	//保证散列表最大长度是素数
    //以下分配链表头结点数组
    H->Heads = (List)malloc(H->TableSize * sizeof(struct LNode)); //相当于H->Heads[H->TableSize]
    for ( i = 0; i < H->TableSize; i++ ) { //初始化表头结点
        H->Heads[i].Data[0] = '\0';
        H->Heads[i].Next = NULL;
        H->Heads[i].Count = 0;
    }
    return H;
}

Index Hash ( const char *Key, int TableSize ) {
    unsigned int h = 0; //散列函数值，初始化为0
    while ( *Key != '\0' ) //位移映射
        h = ( h << 5 ) + *Key++;
    return h % TableSize;
}

Position Find ( HashTable H, ElementType Key ) {
    Position P;
    Index Pos;
    Pos = Hash( Key + KEYLENGTH - MAXD, H->TableSize ); //初始散列位置
    P = H->Heads[Pos].Next; //从该链表的第1个结点开始
    while ( P && strcmp( P->Data, Key ) )
        P = P->Next;
    return P; //此时P或者指向找到的结点，或者为NULL
}

bool Insert ( HashTable H, ElementType Key ) {
    Position P, NewCell;
    Index Pos;
    P = Find( H, Key );
    if ( !P ) { //关键词未找到，可以插入
        NewCell = (Position)malloc(sizeof(struct LNode));
        strcpy(NewCell->Data, Key);
        NewCell->Count = 1;
        Pos = Hash( Key + KEYLENGTH - MAXD, H->TableSize ); //初始散列位置
        //将NewCell插入为H->Heads[Pos]链表的第一个结点
        NewCell->Next = H->Heads[Pos].Next;
        H->Heads[Pos].Next = NewCell;
        return true;
    }
    else { //关键词已存在
        P->Count++;
        return false;
    }
}

void DestroyTable( HashTable H ) {
    int i;
    Position P, Tmp;
    //释放每个链表的结点
    for( i = 0; i < H->TableSize; i++ ) {
        P = H->Heads[i].Next;
        while ( P ) {
            Tmp = P->Next;
            free( P );
            P = Tmp;
        }
    }
    free( H->Heads ); //释放头结点数组
    free( H );		  //释放散列表头结点
}

void ScanAndOutput ( HashTable H ) {
    int i, MaxCnt = 0, PCnt = 0;
    ElementType MinPhone;
    List Ptr;
    MinPhone[0] = '\0';
    for ( i = 0; i < H->TableSize; i++ ) { //扫描链表
        Ptr = H->Heads[i].Next;
        while ( Ptr ) {
            if ( Ptr->Count > MaxCnt ) { //更新最大通话次数
                MaxCnt = Ptr->Count;
                strcpy( MinPhone, Ptr->Data );
                PCnt = 1;
            }
            else if ( Ptr->Count == MaxCnt ) {
                PCnt++; //狂人计数
                if ( strcmp( MinPhone, Ptr->Data ) > 0 )
                    strcpy( MinPhone, Ptr->Data ); //更新狂人的最小手机号码
            }
            Ptr = Ptr->Next;
        }
    }
    printf("%s %d", MinPhone, MaxCnt);
    if ( PCnt > 1 )
        printf(" %d", PCnt);
    printf("\n");
}
int main () {
    int N, i;
    ElementType Key;
    HashTable H;
    scanf("%d", &N);
    H = CreateTable( N * 2 );	//创建一个散列表
    for ( i = 0; i < N; i++ ) {
        scanf("%s", Key); Insert( H, Key );
        scanf("%s", Key); Insert( H, Key );
    }
    ScanAndOutput( H );
    DestroyTable( H );
    return 0;
}
