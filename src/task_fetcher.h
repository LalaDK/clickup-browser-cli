#ifndef TASK_FETCHER_HEADER_FILE
#define TASK_FETCHER_HEADER_FILE

#include "projects.h"
#include "tasks.h"

void get_tasks();
void get_tasks(struct TaskArray *task_array, struct Project *project);
struct Task *parse_json_task();
#endif
