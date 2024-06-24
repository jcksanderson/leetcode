#include <stdio.h>
#include <stdlib.h>

typedef struct sudoku_game {
  uint16_t* rows;
  uint16_t* cols;
  uint16_t* squares;
  uint8_t** board;
} sudoku_game;

uint16_t number_bit(char num) {
  switch (num) {
  case '.':
    return 0;
  case '1':
    return 0x1;
  case '2':
    return 0x2;
  case '3':
    return 0x4;
  case '4':
    return 0x8;
  case '5':
    return 0x10;
  case '6':
    return 0x20;
  case '7':
    return 0x40;
  case '8':
    return 0x80;
  case '9':
    return 0x100;
  default:
    fprintf(stderr, "number bit: must be between 0 and 9\n");
    exit(1);
  }
}

void read_board(char** brd, sudoku_game game) {
  int idx = 0;
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      uint16_t bit = number_bit(brd[i][j]);
      game.rows[i] += bit;
      game.cols[j] += bit;
      game.squares[3 * (idx / 27) + ((idx / 3) - (3 * (idx / 9)))] +=
        bit;
      game.board[i][j] = brd[i][j] == '.' ? 0 : brd[i][j] - '0';
      idx++;
    }
  }
}

uint8_t* generate_options(uint16_t possible, uint8_t* len) {
  for (char i = '1'; i <= '9'; i++) {
    if (possible & number_bit(i))
      (*len)++;
  }
  if (!len)
    return NULL;

  uint8_t* opts = malloc(sizeof(uint8_t) * (*len));
  int idx = 0;
  for (char i = '1'; i <= '9'; i++) {
    if (possible & number_bit(i)) {
      opts[idx] = i - 48;
      idx++;
    }
  }
  return opts;
}

uint8_t possible_options(uint16_t possible) {
  int options = 0;
  for (int i = '1'; i <= '9'; i++) {
    if (possible & number_bit(i))
      options++;
  }
  return options;
}

int solve_board_fastest(sudoku_game game) {
  uint8_t idx[2] = {0};
  uint8_t curr_min = 10;
  uint16_t min_poss = 0x1FF;

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (game.board[i][j] != 0)
        continue;
      int sqr = 3 * (i / 3) + (j / 3);

      uint16_t possible =
        (0x1FF & ~(game.rows[i] | game.cols[j] | game.squares[sqr]));
      if (possible == 0)
        return 0;
      uint8_t num_opts = possible_options(possible);
      if (num_opts < curr_min) {
        curr_min = num_opts;
        idx[0] = i;
        idx[1] = j;
        min_poss = possible;
      }
    }
  }
  // if we didn't find a tile that had any options, then the puzzle is solved
  if (curr_min == 10)
    return 1;

  uint8_t i = idx[0];
  uint8_t j = idx[1];
  int sqr = 3 * (idx[0] / 3) + (idx[1] / 3);
  uint8_t len = 0;
  uint8_t* opts = generate_options(min_poss, &len);

  for (int k = 0; k < len; k++) {
    // fprintf(stderr, "Loc: (%d, %d) | Opt: %d\n\n", i, j, opts[k]);
    uint16_t bit = number_bit(opts[k] + 48);
    game.board[i][j] = opts[k];
    game.rows[i] += bit;
    game.cols[j] += bit;
    game.squares[sqr] += bit;

    int status = solve_board_fastest(game);

    // if we received a fail, try the next number
    if (!status) {
      game.rows[idx[0]] -= bit;
      game.cols[idx[1]] -= bit;
      game.squares[sqr] -= bit;
      continue;
    }
    // if we received success, propogate the success down
    return 1;
  }
  game.board[i][j] = 0;
  return 0;
}

void solveSudoku(char** board, int boardSize, int* boardColSize) {
  sudoku_game game_1;
  game_1.rows = calloc(9, sizeof(uint16_t));
  game_1.cols = calloc(9, sizeof(uint16_t));
  game_1.squares = calloc(9, sizeof(uint16_t));
  game_1.board = calloc(9, sizeof(uint8_t*));
  for (int i = 0; i < 9; i++) {
    game_1.board[i] = calloc(9, sizeof(uint8_t));
  }

  read_board(board, game_1);
  solve_board_fastest(game_1);

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      board[i][j] = game_1.board[i][j] + '0';
    }
  }
}

int main()
{
  char board_fill[][9] = {
    {'5','3','.','.','7','.','.','.','.'},
    {'6','.','.','1','9','5','.','.','.'},
    {'.','9','8','.','.','.','.','6','.'},
    {'8','.','.','.','6','.','.','.','3'},
    {'4','.','.','8','.','3','.','.','1'},
    {'7','.','.','.','2','.','.','.','6'},
    {'.','6','.','.','.','.','2','8','.'},
    {'.','.','.','4','1','9','.','.','5'},
    {'.','.','.','.','8','.','.','7','9'}
  };
  char **board = malloc(sizeof(char *) * 9);
  for (int i = 0; i < 9; i++) {
    board[i] = malloc(sizeof(char) * 9);
  }
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      board[i][j] = board_fill[i][j];
    }
  }

  int temp;
  solveSudoku(board, 9, &(temp));

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      printf("%c", board[i][j]);
    }
    printf("\n");
  }
  return 0;
}
