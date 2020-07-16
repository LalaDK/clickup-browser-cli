#include "tasks.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void task_array_init(struct TaskArray *a, int initial_size) {
  a->tasks = malloc(initial_size * sizeof(struct Task));
  a->used = 0;
  a->size = initial_size;
}

void task_array_add_task(struct TaskArray *a, struct Task *task) {
  if(a->used == a->size) {
    a->size *= 2;
    int new_size = a->size * sizeof(struct Task);
    a->tasks = realloc(a->tasks, new_size);
  }
  a->tasks[a->used] = *task;
  a->used++;
}

void task_array_print(struct TaskArray *a) {
  printf("size: %d\t used: %d\n", (int) a->size, (int) a->used);
  for(int i = 0; i < a->used; i++) {
    printf("%i\n", a->tasks[i].id);
    printf("%.50s\n\n", a->tasks[i].creator->username);
  }
  printf("\n");
}

void task_array_clear(struct TaskArray *a) {
  free(a->tasks);
  a->tasks = NULL;
  a->used = a->size = 0;
}
