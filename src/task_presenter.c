#include <ncurses.h>
#include <string.h>
#include <signal.h>
#include <math.h>
#include <stdlib.h>

#include "projects.h"
#include "tasks.h"
#include "task_fetcher.h"
#include "task_presenter.h"


static struct TaskArray *task_array;
static int highlight = 0;

struct Task select_task(struct Project *project_ptr) {
  task_array = malloc(sizeof(struct TaskArray));
  get_tasks(task_array, project_ptr);

  initscr();
  noecho();
  cbreak();
  curs_set(0);
  keypad(stdscr, TRUE);
  signal (SIGWINCH, NULL);
  raw();
  draw();

  chtype ch;
  int running = 1;
  while(running == 1) {
    ch = getch();

    switch(ch) {
      case KEY_UP: {
        highlight -= highlight > 0 ? 1 : 0;
        break;
      }
      case KEY_DOWN: {
        highlight += highlight < (task_array->used - 1) ? 1 : 0;
        break;
      }
      case 10: {
        running = false;
        break;
      }
    }
    draw();
  }

  endwin();
  return task_array->tasks[highlight];
}

static void draw() {
  int row, col;
  getmaxyx(stdscr, row, col);
  int start_row = (row / 2) - (task_array->used / 2);

  attron(A_STANDOUT);
  for(int i = 0; i < task_array->used; i++) {
    if(i == highlight) {
      attron(A_STANDOUT);
    } else {
      attroff(A_STANDOUT);
    }

    mvprintw(start_row + i, 0, "%s", task_array->tasks[i].name);

  }
  refresh();
}
