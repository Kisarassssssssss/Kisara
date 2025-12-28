char a[1001][1001];
int count=0;//squre个数
int SearchSqure(int k,int i)
{
    char left_c=a[k+1][i-1],right_c=a[k+1][i+2];
    int row=k+1;
    int lc=i-1;
    int rc=i+2;
    int len=1;//长度
    int pc=0;//检测到正方形个数
    while(left_c=='/'&&right_c== '\\'  )// '\'有歧义，反斜杠使用\\"表示
        {
        len++;
        left_c=a[++row][--lc];
        right_c=a[row][++rc];
        int lsrow=len,lsc=lc,lsr=rc;//暂时记录行数，避免回溯后被覆盖
        if(a[row][lc+1]=='\\'&&a[row][rc-1]=='/')//检测到有左右顶点，开始回溯检测下面的三角形
        {
            lc++;
            rc--; 
          while(left_c=='\\'&&right_c== '/'  )
        {
        left_c=a[++row][++lc];
        right_c=a[row][--rc];
        len--;
        if(len==0)
        {
            pc++;
        }
        }
        row=lsrow;
        lc=lsc;
        rc=lsr;//恢复记录的行数与列数，方便继续向下索引上三角形
        }
        }
   
    
        return pc;//不是squre
}
    
int main()
{for (;;)
    count+=SearchSqure(k,i);//累加当前顶点个数

}
