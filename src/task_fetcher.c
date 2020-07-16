#include <stdio.h>
#include <json-c/json.h>
#include "http_helper.h"
#include "task_fetcher.h"
#include "tasks.h"


struct TaskArray task_array;
struct json_object *current_json;
struct Task current_task;

void get_tasks() {
  struct json_object *json;
  json = http_helper_get_json("https://api.clickup.com/api/v2/list/8212783/task?archived=false");

  struct json_object *tasks;
  tasks = json_object_object_get(json, "tasks");
  //printf("%s", json_object_get_string(tasks));

  int n_tasks = json_object_array_length(tasks);
  task_array_init(&task_array, n_tasks);

  for(int i = 0; i < n_tasks; i++) {

    current_json = json_object_array_get_idx(tasks, i);
    parse_json_task();
    task_array_add_task(&task_array, &current_task);
  }

  task_array_print(&task_array);
}

struct Task *parse_json_task() {
  struct json_object *id = json_object_object_get(current_json, "id");
  struct json_object *name = json_object_object_get(current_json, "name");
  struct json_object *text_content = json_object_object_get(current_json, "text_content");
  struct json_object *description = json_object_object_get(current_json, "description");
  struct json_object *date_created = json_object_object_get(current_json, "date_created");
  struct json_object *date_updated = json_object_object_get(current_json, "date_updated");

  struct json_object *status = json_object_object_get(current_json, "status");
  struct json_object *status_status = json_object_object_get(status, "status");
  struct json_object *status_color = json_object_object_get(status, "color");
  struct json_object *status_type = json_object_object_get(status, "type");

  struct json_object *creator = json_object_object_get(current_json, "creator");
  struct json_object *creator_id = json_object_object_get(creator, "id");
  struct json_object *creator_username = json_object_object_get(creator, "username");
  struct json_object *creator_color = json_object_object_get(creator, "color");
  struct json_object *creator_email = json_object_object_get(creator, "email");

  current_task.id = json_object_get_int(id);
  current_task.name = (char *) json_object_get_string(name);
  current_task.text_content = (char *) json_object_get_string(text_content);
  current_task.description = (char *) json_object_get_string(description);
  current_task.date_created = json_object_get_int(date_created);
  current_task.date_updated = json_object_get_int(date_updated);

  current_task.status = malloc(sizeof(struct TaskStatus));
  current_task.status->status = (char *) json_object_get_string(status_status);
  current_task.status->color = (char *) json_object_get_string(status_color);
  current_task.status->type = (char *) json_object_get_string(status_type);

  current_task.creator = malloc(sizeof(struct TaskCreator));
  current_task.creator->id = json_object_get_int(creator_id);
  current_task.creator->username = (char *) json_object_get_string(creator_username);
  current_task.creator->color = (char *) json_object_get_string(creator_color);
  current_task.creator->email = (char *) json_object_get_string(creator_email);

  return &current_task;
}
