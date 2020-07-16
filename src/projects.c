#include "projects.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void project_array_init(struct ProjectArray *a, int initial_size) {
  a->projects = malloc(initial_size * sizeof(struct Project));
  a->used = 0;
  a->size = initial_size;
}

void project_array_add_project(struct ProjectArray *a, struct Project *project) {
  if(a->used == a->size) {
    a->size *= 2;
    int new_size = a->size * sizeof(struct Project);
    a->projects = realloc(a->projects, new_size);
  }
  a->projects[a->used] = *project;
  a->used++;
}

void project_array_print(struct ProjectArray *a) {
  printf("size: %d\t used: %d\n", (int) a->size, (int) a->used);
  for(int i = 0; i < a->used; i++) {
    printf("%s\n", a->projects[i].id);
    printf("%.50s\n\n", a->projects[i].name);
  }
  printf("\n");
}

void project_array_clear(struct ProjectArray *a) {
  free(a->projects);
  a->projects = NULL;
  a->used = a->size = 0;
}
