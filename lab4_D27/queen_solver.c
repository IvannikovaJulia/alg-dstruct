#include <stdlib.h>
#include <string.h>

#include "queen_solver.h"

typedef enum {
	EMPTY_CELL = 0,
	QUEEN_CELL = 1
} CellInfo;

typedef struct {
	CellInfo* columns;
	CellInfo* left_diagonals;
	CellInfo* right_diagonals;
	unsigned size;
} QeenSolverChessBoardImage;


static unsigned find_solve(QeenSolverChessBoardImage* board, unsigned n, Cell* solve) {
	if (n == board->size)
		return n;

	for (unsigned i = 0; i < board->size; i++) {
		unsigned left_diagonal_index = n + i;
		unsigned right_diagonal_index = (board->size - 1 - n) + i;

		if (board->columns[i] != QUEEN_CELL &&
			board->left_diagonals[left_diagonal_index] != QUEEN_CELL &&
			board->right_diagonals[right_diagonal_index] != QUEEN_CELL
			) {
			board->columns[i] = QUEEN_CELL;
			board->left_diagonals[left_diagonal_index] = QUEEN_CELL;
			board->right_diagonals[right_diagonal_index] = QUEEN_CELL;

			unsigned ans = find_solve(board, n + 1, solve);
			if (ans == board->size) {
				solve[n].colomn = i;
				solve[n].row = n;
				return ans;
			}

			board->columns[i] = EMPTY_CELL;
			board->left_diagonals[left_diagonal_index] = EMPTY_CELL;
			board->right_diagonals[right_diagonal_index] = EMPTY_CELL;
		}
	}
	return 0;
}

Cell* queen_task_solver(unsigned size) {
	if (size < 4)
		return NULL;

	QeenSolverChessBoardImage board;

	Cell* solve = (Cell*)malloc(sizeof(Cell) * size);
	if (solve == NULL)
		return NULL;

	board.size = size;

	board.columns = (CellInfo*)malloc(sizeof(CellInfo) * size);
	if (board.columns == NULL) {
		free(solve);
		return NULL;
	}

	board.left_diagonals = (CellInfo*)malloc(sizeof(CellInfo) * (size * 2 - 1));
	if (board.left_diagonals == NULL) {
		free(board.columns);
		return NULL;
	}

	board.right_diagonals = (CellInfo*)malloc(sizeof(CellInfo) * (size * 2 - 1));
	if (board.right_diagonals == NULL) {
		free(solve);
		free(board.columns);
		free(board.left_diagonals);
		return NULL;
	}

	memset(board.columns, 0, sizeof(CellInfo) * size);
	memset(board.left_diagonals, 0, sizeof(CellInfo) * (size * 2 - 1));
	memset(board.right_diagonals, 0, sizeof(CellInfo) * (size * 2 - 1));

	find_solve(&board, 0, solve);

	free(board.columns);
	free(board.left_diagonals);
	free(board.right_diagonals);

	return solve;
}
