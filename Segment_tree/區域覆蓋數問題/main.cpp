struct Node{
    int chg,data;
}ST[MAX_N*4];

void add(int a,int b,int i,int l,int r,int x){
    if(a <= l && r <= b) ST[i].chg += x;
    else if(r < a || b < l) return;
    else{
        int m = (l + r) / 2, lson = i * 2 + 1,rson = i * 2 + 2;
        add(a, b, lson, l, m, x);
        add(a, b, rson, m+1, r, x);
        ST[i].data = max(ST[lson].data + ST[lson].chg, ST[rson].data + ST[rson].chg];
    }
}
                         
int query(int a,int b,int i,int l,int r){
  if(a <= l && r <= b) return ST[i].data + ST[i].chg;
  else if(r < a || b < l) return -1;  //沒交集 回傳不影響答案的值
  else{
      int m = (l + r)/2, lson = i * 2 + 1, rson = i * 2 + 2;
      int x1 = query( a, b, lson, l, m);
      int x2 = qurey( a, b, rson, m+1, r);
      return max(x1,x2) + ST[i].chg;
  }
}
                         
/************************************************************/
// chg1 : 加值的修改，chg2 : 改值的修改(以chg1 = 0,chg2 = 0 表示沒有要被修改)
struct Node{
  int chg1, chg2, data;
}ST[MAX_N*4];
                         
void push(int i,int lson,int rson){
    if(ST[i].chg2 > 0){
        ST[i].data = ST[i].chg2;
        if(lson >= 0) ST[lson].chg2 = ST[i].chg2, ST[lson].chg1 = 0;
        if(rson >= 0) ST[rson].chg2 = ST[i].chg2, ST[rson].chg1 = 0;
        ST[i].chg2 = 0;
    }
    if(ST[i].chg1 > 0){
        ST[i].data += ST[i].chg1;
        if(lson >= 0) ST[lson].chg1 += ST[i].chg1;
        if(rson >= 0) ST[rson].chg1 += ST[i].chg1;
        ST[i].chg1 = 0;
    }
}
