一個一維的數線，座標是[0,2n)內的整數

每次操作可能會:

新增一條線段，覆蓋[l,r)區間。

詢問某個單位區間[l,l+1)上覆蓋的線段數

移除某條先前覆蓋的區間

操作次數 <= 10^5 , n <= 5 * 10^5

如果座標不是[0,2n)，是[0,2147483647)怎麼辦?

###初始建構
data的定義改成 << 完整覆蓋當前區間的線段數量>> 和RMQ 問題的建構沒本質的不同，只是data全部初始化為0。
![image](https://user-images.githubusercontent.com/90430653/182109533-eeb84409-e926-4dea-80a2-b06e73991978.png)

###區間修改
```cpp=1
void modify(int l,int r,int v,int index){
    if(ST[index].l == l && ST[index].r == r)
        ST[index].data += v;
    else{
        int mid = (ST[index].l + ST[index].r ) / 2;
        int lson = ST[index].lson;
        int rson = ST[index].rson;
        if( r <= mid ) modify(l,r,v,lson);
        else if( l >= mid ) modify(l,r,v,rson);
        else modify(l,mid,v,lson), modify(mid,r,v,rson);
    }
}
```
![image](https://user-images.githubusercontent.com/90430653/182112268-063a20be-2497-4352-ad62-2478e2316d51.png)
###單點查詢
```cpp=1
int query(int x,int index){
    if( ST[index].l == ST[index].r - 1)
        return ST[index].index;
    else{
        int mid = (ST[index].l + ST[index].r) / 2;
        int lson = ST[index].lson;
        int rson = ST[index].rson;
        if( x < mid ) return ST[index].data + query(x,lson);
        else return ST[index].data + query(x,rson);
    }
}
```
![image](https://user-images.githubusercontent.com/90430653/182112860-e1b7f4a7-be53-415b-a3ed-b40e1dc8ecc3.png)
