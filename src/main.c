#include <stdio.h>
#include <string.h>
#include <json-c/json.h>

#include "main.h"

#include "task_fetcher.h"
#include "task_presenter.h"
#include "projects.h"
#include "project_presenter.h"
#include "projects.h"
#include "tasks.h"

struct Project project;

int main() {
  select_project(&project);
  //select_task(&project);

  return 0;
}
