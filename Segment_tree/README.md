### 初始建立
```cpp=1
int array[MAX_N];
Node ST[MAX_N*2];
int stptr = 0;
void build(int l,int r,int index){
  ST[index].l = l, ST[index].r = r;
  if(l == r-1)
    ST[index].data = array[l];
  else{
    int lson = ST[index].lson = ++stptr;
    int rson = ST[index].rson = ++stptr;
    build(l,(l+r)/2,lson);
    build((l+r)/2,r,rson);
    ST[index].data = max(ST[lson].data,ST[rson].data);
  }
}
```
![image](https://user-images.githubusercontent.com/90430653/182100756-ea218771-7328-4ac2-9b40-24c5aa36c833.png)

### 單點修改
```cpp=1
void modify(int x,int v,int index){
  if( ST[index].l == ST[index].r-1)
      ST[index].data = v;
  else{
      int mid = (ST[index].l + ST[index].r) / 2;
      int lson = ST[index].lson;
      int rson = ST[index].rson;
      if( x < mid ) modify(x ,v ,lson);
      else modify(x ,v ,rson);
      ST[index].data = max(ST[lson].data,ST[rson].data);
  }
}
```
![image](https://user-images.githubusercontent.com/90430653/182102721-77250d9b-8be0-4da1-83de-e4029c72ee3f.png)

### 區間查詢
```cpp=1
int query(int l,int r,int index){
  if( ST[index].l == l && ST[index].r == r )
      return ST[index].data;
  else{
      int mid = ( ST[index].l + ST[index].r )/2;
      int lson = ST[index].lson;
      int rson = ST[index].rson;
      if( r <= mid ) return query(l,r,lson);
      else if(l >= mid) return query(l,r,rson);
      else return max(query(l,mid,lson),query(mid,r,rson));
  }
}
```
![image](https://user-images.githubusercontent.com/90430653/182103742-de36a3fa-c0fc-4d07-94d8-16f811c17b41.png)

只要把握每個節點data的定義，就能輕鬆掌握

空間複雜度 : 可以證明節點數為 2n * O(n)

時間複雜度 : 

初始建構: 所有節點恰會建構一次，每個節點 O (1)，配合節點樹可得為 O (n)。

單點修改: 該點的所有祖先節點都會被修改到，其他都不會被修改到，O (log n)。

區間查詢: 每筆詢問最多詢問到深度為 O (log n)的節點，在一次詢問中，每一層不會有超過2個節點被詢問(想一想，為什麼?)，總複雜度 O (log n)
