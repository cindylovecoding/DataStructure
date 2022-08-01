```cpp=1
int array[MAX_N];
Node ST[MAX_N*2];
int stptr = 0;
void build(int l,int r,int index){
  ST[index].l = l, ST[index].r = r;
  if(l == r-1)
    ST[index].data = array[l];
  else{
    int lson = ST[index].lson = stptr++;
    int rson = ST[index].rson = stptr++;
    build(l,(l+r)/2,lson);
    build((l+r)/2,r,rson);
    ST[index].data = max(ST[lson].data,ST[rson].data);
  }
}
```
![image](https://user-images.githubusercontent.com/90430653/182100756-ea218771-7328-4ac2-9b40-24c5aa36c833.png)
