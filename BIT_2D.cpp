#define N 4
struct Query { 
    int x1, y1; int x2, y2;
}; 
void updateBIT(int BIT[][N+1], int x, int y, int val) { 
    for (; x <= N; x += (x & -x)) { 
        for (; y <= N; y += (y & -y)) 
            BIT[x][y] += val; 
    } 
    return; 
} 
int getSum(int BIT[][N+1], int x, int y) { 
    int sum = 0; 
    for(; x > 0; x -= x&-x) { 
        for(; y > 0; y -= y&-y) { 
            sum += BIT[x][y]; 
        } 
    } 
    return sum; 
} 
void constructAux(int mat[][N], int aux[][N+1]) { 
    for (int i=0; i<=N; i++) 
        for (int j=0; j<=N; j++) 
            aux[i][j] = 0;        
    for (int j=1; j<=N; j++) 
        for (int i=1; i<=N; i++) 
            aux[i][j] = mat[N-j][i-1]; 
    return; 
} 
void construct2DBIT(int mat[][N], int BIT[][N+1]) { 
    int aux[N+1][N+1]; 
    constructAux(mat, aux); 
    for (int i=1; i<=N; i++) 
        for (int j=1; j<=N; j++) 
            BIT[i][j] = 0; 
    for (int j=1; j<=N; j++) { 
        for (int i=1; i<=N; i++) { 
            int v1 = getSum(BIT, i, j); 
            int v2 = getSum(BIT, i, j-1); 
            int v3 = getSum(BIT, i-1, j-1); 
            int v4 = getSum(BIT, i-1, j); 
            updateBIT(BIT, i, j, aux[i][j]-(v1-v2-v4+v3)); 
        } 
    } 
    return; 
} 
void answerQueries(Query q[], int m, int BIT[][N+1]) { 
    for (int i=0; i<m; i++) { 
        int x1 = q[i].x1 + 1; 
        int y1 = q[i].y1 + 1; 
        int x2 = q[i].x2 + 1; 
        int y2 = q[i].y2 + 1; 
        int ans = getSum(BIT, x2, y2)-getSum(BIT, x2, y1-1)- 
                  getSum(BIT, x1-1, y2)+getSum(BIT, x1-1, y1-1); 
        printf ("Query(%d, %d, %d, %d) = %d\n", 
                q[i].x1, q[i].y1, q[i].x2, q[i].y2, ans); 
    } 
    return; 
} 
int main() { 
    int mat[N][N] = {{1, 2, 3, 4}, 
                    {5, 3, 8, 1}, 
                    {4, 6, 7, 5}, 
                    {2, 4, 8, 9}}; 
    int BIT[N+1][N+1]; 
    construct2DBIT(mat, BIT); 
    Query q[] = {{1, 1, 3, 2}, {2, 3, 3, 3}, {1, 1, 1, 1}}; 
    int m = sizeof(q)/sizeof(q[0]); 
    answerQueries(q, m, BIT); 
    return(0); 
} 
