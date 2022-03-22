#ifndef QUEEN_SOLVER_H
#define QUEEN_SOLVER_H

typedef struct {
	int row;
	int colomn;
} Cell;

Cell* queen_task_solver(unsigned size);

#endif
