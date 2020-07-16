#ifndef TASKS_HEADER_FILE
#define TASKS_HEADER_FILE

struct Task {
  int id;
  char* name;
  char* text_content;
  char* description;
  int date_created;
  int date_updated;
  struct TaskStatus *status;
  struct TaskCreator *creator;
};

struct TaskArray {
  struct Task* tasks;
  int size;
  int used;
};

struct TaskStatus {
  char* status;
  char* color;
  char* type;
};

struct TaskCreator {
  int id;
  char* username;
  char* color;
  char* email;
};

struct TaskArray *task_array_get();
void task_array_init(struct TaskArray *, int);
void task_array_add_task(struct TaskArray *, struct Task *);
void task_array_print(struct TaskArray *);
void task_array_clear(struct TaskArray *);
#endif
