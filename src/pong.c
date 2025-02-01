#include <stdio.h>

#define WIDTH 80
#define HEIGHT 25
#define PADDLE_SIZE 3

void clearScreen() {
    printf("\033[H\033[J");  // Очищает экран
}

void draw_field(int paddle1_pos, int paddle2_pos, int ball_x, int ball_y) {
    clearScreen();

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == WIDTH / 2 && y != 0 && y != HEIGHT - 1) {
                if (x == WIDTH / 2 && (x == ball_x && y == ball_y)) {
                    printf("O");
                } else {
                    printf("|");
                }
            } else if (y == 0 || y == HEIGHT - 1) {
                printf("-");  // Верхняя и нижняя границы
            } else if (x == 1 && y >= paddle1_pos && y < paddle1_pos + PADDLE_SIZE) {
                printf("|");  // Ракетка игрока 1
            } else if (x == WIDTH - 2 && y >= paddle2_pos && y < paddle2_pos + PADDLE_SIZE) {
                printf("|");  // Ракетка игрока 2
            } else if (x == ball_x && y == ball_y) {
                printf("O");  // Мяч
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int player_score(int ps1, int ps2) {
    for (int i = 0; i < 37; i++) {
        printf(" ");
    }
    return printf("\"%d   %d\"\n", ps1, ps2);
}

//Функция для ввода данных в консоль
char get_input(int paddle1_pos, int paddle2_pos) {
    char ch;
    do {
        printf(
            "Print control Player 1: a, z\nPlayer 2: m, k\nSystem: 1 for exit, "
            "Space for pass): ");
        ch = getchar();
        // Игнорируем оставшиеся символы в буфере
        while (getchar() != '\n')
            ;
        // Проверяем ввод
        if (ch == 'a' && paddle1_pos > 1) {
            return 'a';  // Игрок 1 движется вверх
        } else if (ch == 'z' && paddle1_pos < HEIGHT - PADDLE_SIZE - 1) {
            return 'z';  // Игрок 1 движется вниз
        } else if (ch == 'k' && paddle2_pos > 1) {
            return 'k';  // Игрок 2 движется вверх
        } else if (ch == 'm' && paddle2_pos < HEIGHT - PADDLE_SIZE - 1) {
            return 'm';  // Игрок 2 движется вниз
        } else if (ch == '1') {
            printf("GAME OVER!!!\n");
            return '1';  // Возвращаем символ для выхода
        } else if (ch == ' ' || ch == '\n') {
            return ' ';  // Игнорируем пробел и Enter
        } else {
            printf(
                "Error: Invalid character '%c'. Enter a character (valid: a, "
                "z, m, k)\n",
                ch);
        }
    } while (1);

    return ch;  // Возвращаем последний введённый символ
}

void out_of_score(int player_number) {
    clearScreen();
    for (int i = 0; i < 37; i++) {
        printf(" ");
    }
    printf("Player %d win!", player_number);
};

int main() {
    int paddle1_pos = (HEIGHT - PADDLE_SIZE) / 2;
    int paddle2_pos = (HEIGHT - PADDLE_SIZE) / 2;
    int ball_x = WIDTH / 2;
    int ball_y = HEIGHT / 2;
    int velocityX = 1;
    int velocityY = 1;
    int player1_score = 0;
    int player2_score = 0;
    int player_number;

    while (1) {
        draw_field(paddle1_pos, paddle2_pos, ball_x, ball_y);
        player_score(player1_score, player2_score);

        // Обновление позиции мяча
        ball_x += velocityX;
        ball_y += velocityY;
        // Проверка столкновения с границами
        if (ball_y <= 1 || ball_y >= HEIGHT - 2) {
            velocityY = -velocityY;  // Отражение от границ
        }
        // Проверка столкновения с ракетками
        if (ball_x == 2 && ball_y >= paddle1_pos && ball_y < paddle1_pos + PADDLE_SIZE) {
            velocityX = -velocityX;  // Отражение от ракетки 1
        }
        if (ball_x == WIDTH - 3 && ball_y >= paddle2_pos && ball_y < paddle2_pos + PADDLE_SIZE) {
            velocityX = -velocityX;  // Отражение от ракетки 2
        }
        if (ball_x == WIDTH - 1) {
            player1_score++;
            velocityY = -velocityY;
            velocityX = -velocityX;
            ball_x = WIDTH / 2;
            ball_y = HEIGHT / 2;
            if (player1_score == 21) {
                player_number = 1;
                out_of_score(player_number);
                return 0;
            }
        }
        if (ball_x == 0) {
            player2_score++;
            velocityY = -velocityY;
            velocityX = -velocityX;
            ball_x = WIDTH / 2;
            ball_y = HEIGHT / 2;
            if (player2_score == 21) {
                player_number = 2;
                out_of_score(player_number);
                return 0;
            }
        }
        // Считываем символ
        char input = get_input(paddle1_pos, paddle2_pos);
        if (input == '1') {
            break;
        }
        // Обновление позиций ракеток
        if (input == 'a') {
            paddle1_pos--;
        } else if (input == 'z') {
            paddle1_pos++;
        } else if (input == 'k') {
            paddle2_pos--;
        } else if (input == 'm') {
            paddle2_pos++;
        }
    }
    //Задание сделано!
    return 0;
}
