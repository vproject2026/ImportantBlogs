/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <bits/stdc++.h>

using namespace std;

int g=0;

void printBoard(vector<string> &board,int i,int j){
    for(auto bb:board){
        cout<<bb<<endl;
    }
    g++;
    cout<<i<<" "<<j<<endl;
}
void printBoard(vector<string> &board){
    for(auto bb:board){
        cout<<bb<<endl;
    }
    cout<<endl;
}

bool isValid(vector<string> &board,int icol,int nqueens){
    bool flag=true;
    // For row wise check
    for(int j=0;j<nqueens;j++){
        int count=0;
        for(int i=0;i<=icol;i++){
            if(board[j][i]=='Q'){
                count++;
            }
            // if(icol+i<nqueens && board[j][icol+i]=='Q'){
            //     count++;
            // }
            // if(i-icol>0 && board[j][i-icol]=='Q'){
            //     count++;
            // }
        }
        if(count>1){
            flag=false;
            return flag;
        }
    }
    
    // For lower left diagonals 
    for(int j=0;j<nqueens;j++){
        int count=0;
        for(int i=0;i<=icol;i++){
            if(j+i<nqueens && board[j+i][i]=='Q'){
                count++;
            }
        }
        if(count>1){
            flag=false;
            return flag;
        }
    }
    
    // For upper left-right diagonals 
    for(int i=1;i<icol;i++){
        int count=0;
        for(int j=0;j<=nqueens;j++){
            if(j+i<nqueens && board[j][j+i]=='Q'){
                count++;
            }
        }
        if(count>1){
            flag=false;
            return flag;
        }
    }
    
    // For right  diagonals 
    for(int i=nqueens-1;>0;j--){
        int count=0;
        for(int j=0;i<=icol;i++){
            if(j+i<j && board[j-i][i]=='Q'){
                count++;
            }
        }
        if(count>1){
            flag=false;
            return flag;
        }
    }
    
    // For upper left-right diagonals 
    for(int i=1;i<icol;i++){
        int count=0;
        for(int j=0;j<=nqueens;j++){
            if(j+i<nqueens && board[j][j+i]=='Q'){
                count++;
            }
        }
        if(count>1){
            flag=false;
            return flag;
        }
    }

    return flag;
}

void helper(vector<vector<string>> &boardlist,vector<string> &board,int nqueens,int icol,int jrow){
    if(nqueens==icol){
        printBoard(board,icol,jrow);
        boardlist.push_back(board);
        return;
    }
    
    for(int j=0;j<nqueens;j++){
        board[j][icol]='Q';
        if(isValid(board,icol,nqueens)){
            helper(boardlist,board,nqueens,icol+1,j);
        }
        board[j][icol]='.';
    }
}


int main()
{
    // cout<<"Hello World";
    int n=4;
    vector<string> board(4,"....");
    vector<vector<string>> boardlist;
    
    helper(boardlist,board,n,0,0);
    
    // for(auto aa:boardlist){
        
    // }
    

    return g;
}
