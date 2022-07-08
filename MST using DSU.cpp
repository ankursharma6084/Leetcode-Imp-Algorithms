You are given an array points representing integer coordinates of some points on a 2D-plane, where points[i] = [xi, yi].

The cost of connecting two points [xi, yi] and [xj, yj] is the manhattan distance between them: |xi - xj| + |yi - yj|, where |val| denotes the absolute value of val.

Return the minimum cost to make all points connected. All points are connected if there is exactly one simple path between any two points.


Input: points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
Output: 20

Input: points = [[3,12],[-2,5],[-4,1]]
Output: 18
 
Constraints:

1 <= points.length <= 1000
-106 <= xi, yi <= 106
All pairs (xi, yi) are distinct.


class Solution {
    
    private:
    vector<int> par , size ;
    
    static bool comp(vector<int> &a, vector<int> &b){
        return a[2] < b[2] ;
    }
    
    int find(int a)
    {
        if(par[a] == a) return a ;
        return par[a] = find(par[a]) ;
    }
    
    void uni(int a , int b)
    {
        a = par[a] ;
        b = par[b] ;
        
        if(size[a] < size[b]){
           size[b] += size[a] ;
           par[a] = b ;
        }
        
        else{
            size[a] += size[b] ;
            par[b] = a ;
        }
    }

    
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        
        int n = points.size() ;

        par.resize(n) ;
        size.resize(n , 1) ;
        iota(begin(par) , end(par) , 0) ;
        
        priority_queue<vector<int> > pq ;
        
        for(int i=0; i<n; i++)
        {
            for(int j=i+1; j<n; j++)
            {
                int dist = abs( points[j][0] - points[i][0] ) + abs( points[j][1] - points[i][1] ) ;
                pq.push({ -dist , i , j }) ;
            }
        }
        
        int count = 0 ;
        
        int sum = 0 ;
        
        while(pq.size() > 0)
        {
            vector<int> v = pq.top() ; pq.pop() ;
            int d = -v[0] ;
            int a = find(v[1]) ;
            int b = find(v[2]) ;
            
            if(a != b)
            {
                count++ ;
                uni(a , b) ;
                sum+= d ;
            }
            
            if(count == n-1) break;
        }
        return sum ;
    }
};
