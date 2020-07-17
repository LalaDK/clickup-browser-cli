#include <ncurses.h>
#include <string.h>
#include <signal.h>
#include <math.h>
#include <stdlib.h>
#include "projects.h"
#include "project_fetcher.h"
#include "project_presenter.h"


static struct ProjectArray *project_array;
static int highlight = 0;

void select_project(struct Project *project_ptr) {

  project_array = malloc(sizeof(struct ProjectArray));
  get_projects(project_array);
    
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
        highlight += highlight < (project_array->used - 1) ? 1 : 0;
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
  project_ptr = &project_array->projects[highlight];
}

static void draw() {
  int row, col;
  getmaxyx(stdscr, row, col);
  int start_row = (row / 2) - (project_array->used / 2);

  attron(A_STANDOUT);
  for(int i = 0; i < project_array->used; i++) {
    if(i == highlight) {
      attron(A_STANDOUT);
    } else {
      attroff(A_STANDOUT);
    }

    mvprintw(start_row + i, (col / 2) - (strlen(project_array->projects[i].name) / 2), "%s", project_array->projects[i].name);

  }
  refresh();
}
