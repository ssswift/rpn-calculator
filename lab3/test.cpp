#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

using Matrix = vector<vector<int>>;

// 1. Создание игрового поля
Matrix create_game_board(int rows, int cols, int default_value) {
    return Matrix(rows, vector<int>(cols, default_value));
}

// 2. Вывод поля (упрощzная версия)
void print_board(const Matrix& m) {
    cout << "\nИгровое поле:" << endl;
    for (int row = 0; row < m.size(); ++row) {
        for (int col = 0; col < m[row].size(); ++col) {
            cout << setw(3) << m[row][col] << " ";
        }
        cout << endl;
    }
}

// 3. Размещение элемента
void place_element(Matrix* m, int row, int col, int value) {
    if (row >= 0 && row < m->size() && col >= 0 && col < (*m)[0].size()) {
        (*m)[row][col] = value;
    }
}

// Тестирование
int main() {
    // Создаем поле 5x5
    Matrix board = create_game_board(5, 5, 0);
    
    // Размещаем элементы как в примере
    place_element(&board, 1, 1, 1);
    place_element(&board, 1, 2, 1);
    place_element(&board, 1, 3, 1);
    place_element(&board, 3, 2, -1);
    
    // Выводим результат
    print_board(board);
    
    return 0;
}
