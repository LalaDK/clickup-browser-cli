#ifndef PROJECTS_HEADER_FILE
#define PROJECTS_HEADER_FILE

struct Project {
  char* id;
  char* name;
};

struct ProjectArray {
  struct Project* projects;
  int size;
  int used;
};

struct ProjectArray *project_array_get();
void project_array_init(struct ProjectArray *, int);
void project_array_add_project(struct ProjectArray *, struct Project *);
void project_array_print(struct ProjectArray *);
void project_array_clear(struct ProjectArray *);
#endif
