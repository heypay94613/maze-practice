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



};


class Solver{
private:
    Maze maze;

public:
    Solver(const Maze& or_maze)
        : maze(or_maze){}

    pair<int,vector<pair<int,int>>> return_bfs(vector<vector<int>> grid, pair<int,int> start, pair<int,int> end);


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
