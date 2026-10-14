#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Maze{
private:
    vector<vector<int>> grid;
    
public:

    Maze(vector<vector<int>> or_grid)
        : grid(or_grid){}

    int row = grid.size();
    int col = grid[0].size();

    bool check_wall(pair<int,int> cord) const {
        int r = cord.first;
        int c = cord.second;
        if(grid[r][c]==1){
            return true;
        }
        else return false;
    }

    bool in_cp (pair<int,int> cordi) const{
        int r = cordi.first;
        int c = cordi.second;

        if((r>=0 && r<row) && (c>=0 && c<col)){
            return true;
        }
        else return false;
    }

    void put_color(vector<pair<int,int>> way, pair<int,int> start, pair<int,int> end){
        vector<vector<bool>> way_check (row, vector<bool>(col,false));
        for(int i =0; i<static_cast<int>(way.size()); i++){
            int x = way[i].first;
            int y = way[i].second;
            way_check[x][y]= true;
        }
        for(int i =0; i<row; i++){
            for(int j =0; j<col; j++){
                if(i==start.first && j==start.second){
                    cout<<"\033[42m"<<"  "<<"\033[0m";
                    continue;
                }
                if(i==end.first && j==end.second){
                    cout<<"\033[41m"<<"  "<<"\033[0m";
                    continue;
                }

                if(grid[i][j]==0 && way_check[i][j]==true){
                    cout<<"\033[43m"<<"  "<<"\033[0m";
                    continue;
                }
                if(grid[i][j]==0 && way_check[i][j]==false){
                    cout<<"\033[47m"<<"  "<<"\033[0m";
                    continue;
                }
                if(grid[i][j]==1){
                    cout<<"\033[100m"<<"  "<<"\033[0m";
                    continue;
                }

            }
            cout<<endl;
        }
    }

};


class Robot{
    private:
        pair<int,int> start;
        int direct;
    public:
        Robot(pair<int,int> starting, int direction)
            :start(starting), direct(direction) {}
};


class Solver{
private:
    Maze maze;

public:
    Solver(const Maze& or_maze)
        : maze(or_maze){}

    pair<int,vector<pair<int,int>>> return_bfs(vector<vector<int>> grid, pair<int,int> start, pair<int,int> end);
    vector<int> robot_move(vector<pair<int,int>> way);


};

pair<int,vector<pair<int,int>>> Solver::return_bfs(vector<vector<int>> grid, pair<int,int> start, pair<int,int> end){
    int r = grid.size();
    int c = grid[0].size();
    queue<pair<int,int>> q;
    vector<vector<int>> dist(r, vector<int>(c, -1));
    vector<vector<pair<int,int>>> ancestor(r, vector<pair<int,int>>(c, {-1,-1}));
    vector<pair<int,int>> loca;

    int x = start.first;
    int y = start.second;
    q.push({x,y});
    dist[x][y]= dist[x][y]+1;
    while(q.empty() != true){
        x=q.front().first;
        y=q.front().second;
        q.pop();

        if(x==end.first && y==end.second) break;

        
        int dx[4]= {-1, 0 , 1, 0};
        int dy[4]= {0, 1, 0, -1};

        for(int i =0; i<4; i++){
            int nx = x + dx[i];      
            int ny = y + dy[i];
            if ( maze.in_cp({nx,ny})&&maze.check_wall({nx,ny}) != true && dist[nx][ny]==-1){
                dist[nx][ny]=dist[x][y]+1;
                ancestor[nx][ny]={x,y};
                q.push({nx,ny});
            }
        }
        
    }
    int x_orig = x;
    int y_orig = y;
    loca.push_back({x,y});
    while(x != start.first || y!= start.second){
        int tmp_x = x;
        x=ancestor[x][y].first;
        y=ancestor[tmp_x][y].second;
        loca.push_back({x,y});
    }

    if(x_orig!=end.first || y_orig!=end.second){
        return{-1,loca};
    }
    else{
        return {dist[x_orig][y_orig], loca};
    }
}

vector<int> Solver::robot_move(vector<pair<int,int>> way){
    vector<int> rm_direct;
    int dir = 1;
    int cur_dir =1;
    const int F = 1, R = 2, L = 3;
    for(int i = 0; i < static_cast<int>(way.size())-1; i++){
        int dx = way[i+1].first-way[i].first; 
        int dy = way[i+1].second-way[i].second; 
        if(dx == -1){
            cur_dir = 0;
        }
        if(dx == 1){
            cur_dir = 2;
        }
        if(dy == 1){
            cur_dir = 1;
        }
        if(dy == -1){
            cur_dir = 3;
        }
        int check = (cur_dir - dir+4)%4;

        if( check == 0){
            rm_direct.push_back(F);
        }

        else if (check ==1){
            rm_direct.push_back(R);
            rm_direct.push_back(F);
        }

        else {
            rm_direct.push_back(L);
            rm_direct.push_back(F);
        }

        dir = cur_dir;
        
    }

    return rm_direct;
}

int main() {
    vector<vector<int>> maze_grid = {
        {0, 0, 0, 1, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0}
    };
    pair <int,int> start ={0,0};
    pair <int,int> end ={4,4};
    int num = 0;
    vector<pair<int,int>> stor_way;


    Maze test(maze_grid);
    Solver test_solver(test);
    pair<int,vector<pair<int,int>>> test_holder= test_solver.return_bfs(maze_grid, start, end );
    num = test_holder.first;
    stor_way= test_holder.second;
    reverse(stor_way.begin(), stor_way.end());

    for(int i=0; i<static_cast<int>(stor_way.size()); i++){
        cout<<stor_way[i].first<<","<<stor_way[i].second<<endl;
    }

    test.put_color(stor_way, start, end);

    cout <<num<<endl;
    


    return 0;
}