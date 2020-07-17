#include <stdio.h>
#include <json-c/json.h>
#include "http_helper.h"
#include "projects.h"
#include "project_fetcher.h"

struct json_object *current_json;
struct Project current_project;

void get_projects(struct ProjectArray *project_array) {
  struct json_object *json;
  json = http_helper_get_json("https://api.clickup.com/api/v2/team/2496314/space?archived=false");
  struct json_object *projects;
  projects = json_object_object_get(json, "spaces");


  int n_projects = json_object_array_length(projects);
  project_array_init(project_array, n_projects);

  for(int i = 0; i < n_projects; i++) {
    current_json = json_object_array_get_idx(projects, i);
    parse_json_project();
    project_array_add_project(project_array, &current_project);
  }
}

struct Project *parse_json_project() {
  struct json_object *id = json_object_object_get(current_json, "id");
  struct json_object *name = json_object_object_get(current_json, "name");

  current_project.id = (char *) json_object_get_string(id);
  current_project.name = (char *) json_object_get_string(name);

  return &current_project;
}
