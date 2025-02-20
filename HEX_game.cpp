/*HW 4 expectations:
1. Be able to draw the board using ASCII symbols and a given size, such as 7 by 7 or 11 by 11. CHECKED

2. Input a move and determine if a move is legal. CHECKED

3. Determine who won.*/ 

#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

class HexBoard {
    private:

        int Size; // board size 7x7 or 11x11
        vector<vector<char>> Board; 

    public:

        HexBoard(int input_size): Size(input_size){ // constructor of hex board
            Board.resize(input_size, vector<char>(input_size, 'E')); // for empty spaces I used 'E'
        }

        int getSize(){
            return Size;
        }

        void printBoard(){

            int space=0;

            for (int i=0; i<Size; i++){
                if (i==0){
                   cout << "  " << i+1; 
                }
                else{
                    cout << "   " << i+1;
                } 
            }

            cout << endl;

            for (int i=0; i<Size; i++){

                cout << i+1 << " ";

                for (int k=0; k<space; k++){
                    cout << " ";
                }
                space++;

                for (int j = 0; j < Size; j++){

                    if (Board[i][j] == 'E'){
                        cout << ". ";
                        if (j + 1 != Size){
                            cout << "- ";
                        }
                    }

                    else if (Board[i][j] == 'B'){
                        cout << "B ";
                        if (j + 1 != Size){
                            cout << "- ";
                        }
                    }

                    else {
                        cout << "R ";
                        if (j + 1 != Size){
                            cout << "- ";
                        }
                    }  
                }

                cout << endl;

                if (i+1 != Size){
                    cout << "  ";
                    for (int k=0; k<space; k++){
                        cout << " ";
                    }
                    space++;

                    for (int i=0; i < Size-1; i++){
                        cout << "\\ / ";
                    }
                    cout << "\\  ";
                    cout << endl;
                }
            }
        }
    
        bool turnRed(int i, int j){
            if (Board[i-1][j-1] == 'E'){
                Board[i-1][j-1] = 'R';
                return true;
            }

            else {
                cout << "rule violation, type different place" << endl;
                return false;
            }
        }

        bool turnBlue(int i, int j){
            if (Board[i-1][j-1] == 'E'){
                Board[i-1][j-1] = 'B';
                return true;
            }

            else {
                cout << "rule violation, type different place" << endl;
                return false;
            }
        }

        vector<vector<char>> getBoard() {
            return Board;
        }
};

class UnionFind{

    private:

        vector <int> parent, rank;
        int Size;
        
        int to_index(int i, int j){
            return i * Size + j;
        }

    public:

        UnionFind(int size): parent(size*size), rank(size*size, 0), Size(size){
            iota(parent.begin(), parent.end(),0);
        }

        int find(int x){
            if (parent[x] != x){
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }

        void unionSets(int x, int y){
            int rootX = find(x);
            int rootY = find(y);

            if (rootX != rootY) {
                if (rank[rootX] < rank[rootY]) {
                    parent[rootX] = rootY;
                } else if (rank[rootX] > rank[rootY]) {
                    parent[rootY] = rootX;
                } else {
                    parent[rootY] = rootX;
                    rank[rootX]++;
                }
            }
        }

        bool winning_condition(HexBoard &hex) {
            int size = hex.getSize();
            vector<vector<char>> board = hex.getBoard();

            // Check if Red won
            for (int j = 0; j < size; j++) {
                if (board[0][j] == 'R') {
                    for (int k = 0; k < size; k++) {
                        if (board[size - 1][k] == 'R' && find(to_index(0, j)) == find(to_index(size - 1, k))) {
                            return true; // Red wins
                        }
                    }
                }
            }

        // Check if Blue won
        for (int i = 0; i < size; i++) {
            if (board[i][0] == 'B') {
                for (int k = 0; k < size; k++) {
                    if (board[k][size - 1] == 'B' && find(to_index(i, 0)) == find(to_index(k, size - 1))) {
                        return true; // Blue wins
                    }
                }
            }
        }
        return false; // No winner yet
    }

    void unionNeighbors(HexBoard &hex, int i, int j, char color) {
        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, 1}, {1, -1}};
        vector<vector<char>> board = hex.getBoard();
        for (auto dir : directions) {
            int ni = i + dir.first, nj = j + dir.second;
            if (ni >= 0 && ni < hex.getSize() && nj >= 0 && nj < hex.getSize() && board[ni][nj] == color) {
                unionSets(to_index(i, j), to_index(ni, nj));
            }
        }
    }
};


int main() {
    HexBoard hex(9);
    UnionFind uf(hex.getSize());
    
    hex.printBoard();

    cout << endl;
    cout << "Welcome to my HEX game's early gameplay" << endl;
    cout << "I hope you all love the game" << endl;
    cout << "Board's left and right sides are blue" << endl;
    cout << "Similarly up and down sides are red" << endl;
    cout << "In order to win the game you need to construct a nonstop road between your sides" << endl;
    cout << "Both of you provide input consequently and if you violate the game rules you can try again" << endl;

    int clock = 0;

    cout << "Red can play the first move"<< endl;

    while (!uf.winning_condition(hex)) {
        int x, y;

        if (clock % 2 == 0) { // Red's turn
            cout << "Red's turn" << endl;
        }

        else{cout << "Blue's turn" << endl;} // Blue's turn
            
        
        cin >> x >> y;

        if (x > hex.getSize() || y > hex.getSize()){
            cout << "Index out of range, please type again" << endl;
            continue;
        }

        if (clock % 2 == 0) { // Red's turn
            if (hex.turnRed(x, y)) {
                uf.unionNeighbors(hex, x - 1, y - 1, 'R');
                clock++;
                hex.printBoard();
            }
        } else { // Blue's turn
            if (hex.turnBlue(x, y)) {
                uf.unionNeighbors(hex, x - 1, y - 1, 'B');
                clock++;
                hex.printBoard();
            }
        }
    }

    cout << "Game over!" << endl;
    if (clock % 2 == 0) {
        cout << "BLUE WINS!" << endl;
    } else {
        cout << "RED WINS!" << endl;
    }

    return 0;
}