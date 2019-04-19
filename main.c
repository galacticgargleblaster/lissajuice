#include <simple2d.h>
#include "liblist/liblist.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#ifndef NAME
# define NAME "lissajuice"
#endif

S2D_Window *window;

S2D_Text   *fps;
S2D_Text   *fps_val;
int font_size = 20;
const char *font = "vera.ttf";


#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define NUM_LINES 2000
t_doubly_linked_list *lines;


typedef struct s_color
{
  GLfloat r;
  GLfloat g;
  GLfloat b;
  GLfloat a;
} t_color;

typedef struct s_line
{
  GLfloat x1;
  GLfloat y1;
  GLfloat x2;
  GLfloat y2;
  GLfloat width;
  t_color c[4];
} t_line;

t_line *new_line(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat width)
{
  t_line *line = malloc(sizeof(t_line));
  line->x1 = x1;
  line->x2 = x2;
  line->y1 = y1;
  line->y2 = y2;
  line->width = width;
  for (int i = 0; i < 4; i++)
  {
    line->c[i].r = 0;
    line->c[i].g = 0;
    line->c[i].b = 1;
    line->c[i].a = 1;
  }
  return (line);
}

void drawline(t_line *line)
{
  S2D_DrawLine(
    line->x1,
    line->y1,
    line->x2,
    line->y2,
    line->width,
    line->c[0].r,
    line->c[0].g,
    line->c[0].b,
    line->c[0].a,
    line->c[1].r,
    line->c[1].g,
    line->c[1].b,
    line->c[1].a,
    line->c[2].r,
    line->c[2].g,
    line->c[2].b,
    line->c[2].a,
    line->c[3].r,
    line->c[3].g,
    line->c[3].b,
    line->c[3].a
  );
}

#define MIDDLE_WIDTH ((double)WINDOW_WIDTH / 2)
#define MIDDLE_HEIGHT ((double)WINDOW_HEIGHT / 2)


#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))
#define AMPLITUDE (((double)MIN(WINDOW_WIDTH, WINDOW_HEIGHT)) * 0.1)

#define TIMESTEP 0.01f

void render() {
  S2D_DrawText(fps);
  S2D_SetText(fps_val, "%f", window->fps);
  S2D_DrawText(fps_val);

  // Draw all the lines in the list
  t_element_container *container = lines->head;
  t_line *line;
  float color = 1;
  float increment = 1 / ((float)(lines->size));
  while (container)
  {
    line = container->element;
    for (int i = 0; i < 4; i++)
    {
      line->c[i].r = color;
      line->c[i].g = color;
      line->c[i].b = color;
      line->c[i].a = 1;
    }
    color -= increment;
    drawline(line);
    container = container->prev;
  }
}

unsigned long ticks = 0;

void calculate_lines_for_time(double t)
{
  t_line *line;
  double x1, x2, y1, y2;

  double tmp_x, tmp_y;
  // Calculate the next position
  tmp_x = sin(2.0f * t) + sin(3.05f * t);
  tmp_y = sin(3.0f * t) + sin(4.55f * t);

  x2 = AMPLITUDE * tmp_x + MIDDLE_WIDTH;
  y2 = AMPLITUDE * tmp_y + MIDDLE_HEIGHT;

  line = list_get_head(lines);
  x1 = (double)line->x2;
  y1 = (double)line->y2;

  // Pop the last line off the list, and calculate a new line
  if (lines->size < NUM_LINES)
  {
    line = new_line((GLfloat)x1, (GLfloat)y1, (GLfloat)x2, (GLfloat)y2, 1.0f);
    list_push_head(lines, line);
  }
  if (lines->size == NUM_LINES)
  {
    line = list_pop_tail(lines);
    free(line);
  }
}

double global_t = 0;

void update()
{
  // I think the units of ticks are milliseconds
  while (ticks < SDL_GetTicks())
  {
    calculate_lines_for_time(global_t);
    ticks+= (unsigned long)(1);
    global_t += TIMESTEP;
  }
}

int main() {

  window = S2D_CreateWindow(NAME, WINDOW_WIDTH, WINDOW_HEIGHT, update, render, 0);

  fps = S2D_CreateText(font, "FPS:", font_size);
  fps->x = 430;
  fps->y = 400;

  fps_val = S2D_CreateText(font, "", font_size);
  fps_val->x = 480;
  fps_val->y = 400;

  lines = new_doubly_linked_list();
  list_push_head(lines, new_line(MIDDLE_WIDTH, MIDDLE_HEIGHT, MIDDLE_WIDTH, MIDDLE_HEIGHT, 10.0f));


  S2D_Show(window);
  return 0;
}
