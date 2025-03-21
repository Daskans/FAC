#include "cpustat.h"
#include "debug.h"
#include "error.h"
#include "ezp_colors.h"
#include "ezv_rgba.h"
#include "global.h"
#include "gpu.h"
#include "time_macros.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <hwloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/mman.h>

#define HISTOGRAM_WIDTH 256
#define HISTOGRAM_HEIGHT 100
#define BAR_WIDTH 4
#define BAR_HEIGHT HISTOGRAM_HEIGHT
#define PERFMETER_WIDTH HISTOGRAM_WIDTH
#define RIGHT_MARGIN 16
#define LEFT_MARGIN 80
#define TOP_MARGIN 16
#define BOTTOM_MARGIN 16

static unsigned PERFMETER_HEIGHT = 16;
static unsigned INTERMARGIN      = 8;

static unsigned MAX_WINDOW_HEIGHT     = 0;
static unsigned WINDOW_HEIGHT         = 0;
static unsigned WINDOW_WIDTH          = 0;
static unsigned INITIAL_WINDOW_HEIGHT = 0;

#define RMASK ezv_red_mask ()
#define GMASK ezv_green_mask ()
#define BMASK ezv_blue_mask ()
#define AMASK ezv_alpha_mask ()
#define BLACK_COL ezv_rgb (0, 0, 0)
#define WHITE_COL ezv_rgb (255, 255, 255)

static SDL_Window *win           = NULL;
static SDL_Renderer *ren         = NULL;
static SDL_Texture **perf_frame  = NULL;
static SDL_Texture **perf_fill   = NULL;
static SDL_Texture *text_texture = NULL;
static SDL_Texture *idle_texture = NULL;

static Uint32 *restrict idle_img = NULL;

typedef struct
{
  long start_time, end_time, cumulated_work, cumulated_idle, nb_tiles;
} cpu_stat_t;

static unsigned NBCORES = 1;
static unsigned NBGPUS  = 0;

static cpu_stat_t *cpu_stats = NULL;

float cpustat_activity_ratio (int who);

static float idle_total (void)
{
  long total = 0, idle = 0;

  for (int c = 0; c < NBCORES + NBGPUS; c++) {
    idle  = idle + cpu_stats[c].cumulated_idle;
    total = total + cpu_stats[c].cumulated_work + cpu_stats[c].cumulated_idle;
  }
  return (float)idle / total;
}

static void cpustat_create_cpu_textures (void)
{
  Uint32 *restrict img =
      malloc (PERFMETER_WIDTH * PERFMETER_HEIGHT * sizeof (Uint32));

  perf_frame = malloc (EZP_MAX_COLORS * sizeof (SDL_Texture *));
  perf_fill  = malloc (EZP_MAX_COLORS * sizeof (SDL_Texture *));

  SDL_Surface *s = SDL_CreateRGBSurfaceFrom (
      img, PERFMETER_WIDTH, PERFMETER_HEIGHT, 32,
      PERFMETER_WIDTH * sizeof (Uint32), RMASK, GMASK, BMASK, AMASK);
  if (s == NULL)
    exit_with_error ("SDL_CreateRGBSurfaceFrom failed: %s", SDL_GetError ());

  for (int c = 0; c < EZP_MAX_COLORS; c++) {
    bzero (img, PERFMETER_WIDTH * PERFMETER_HEIGHT * sizeof (Uint32));

    for (int i = 0; i < PERFMETER_HEIGHT; i++)
      for (int j = 0; j < PERFMETER_WIDTH; j++)
        img[i * PERFMETER_WIDTH + j] = ezp_cpu_colors[c];

    perf_fill[c] = SDL_CreateTextureFromSurface (ren, s);

    for (int i = 1; i < PERFMETER_HEIGHT - 1; i++)
      for (int j = 1; j < PERFMETER_WIDTH - 1; j++)
        img[i * PERFMETER_WIDTH + j] = 0;

    perf_frame[c] = SDL_CreateTextureFromSurface (ren, s);
  }

  SDL_FreeSurface (s);
  free (img);
}

static void cpustat_create_idleness_textures (void)
{
  idle_img = mmap (NULL, HISTOGRAM_WIDTH * HISTOGRAM_HEIGHT * sizeof (Uint32),
                   PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

  idle_texture =
      SDL_CreateTexture (ren, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC,
                         HISTOGRAM_WIDTH, HISTOGRAM_HEIGHT);

  if (idle_texture == NULL)
    exit_with_error ("SDL_CreateTexture failed: %s", SDL_GetError ());
}

static void cpustat_create_text_texture (void)
{
  SDL_Color col = {255, 255, 255, 255};

  SDL_Surface *surface = SDL_CreateRGBSurface (0, LEFT_MARGIN, WINDOW_HEIGHT,
                                               32, RMASK, GMASK, BMASK, AMASK);
  if (surface == NULL)
    exit_with_error ("SDL_CreateRGBSurface failed: %s", SDL_GetError ());

  TTF_Font *font =
      TTF_OpenFont ("fonts/FreeSansBold.ttf", PERFMETER_HEIGHT - 2);

  if (font == NULL)
    exit_with_error ("TTF_OpenFont failed: %s", SDL_GetError ());

  for (int c = 0; c <= NBCORES + NBGPUS; c++) {
    char msg[32];
    SDL_Rect dst;
    if (c < NBCORES) {
      snprintf (msg, 32, "CPU %2d ", c);
    } else if (c < NBCORES + NBGPUS) {
      snprintf (msg, 32, "GPU %2d ", c - NBCORES);
    } else {
      snprintf (msg, 32, "Idleness ");
    }
    SDL_Surface *s = TTF_RenderUTF8_Blended (font, msg, col);
    if (s == NULL)
      exit_with_error ("TTF_RenderText_Solid failed: %s", SDL_GetError ());

    dst.x = LEFT_MARGIN - s->w;
    dst.y = TOP_MARGIN + (PERFMETER_HEIGHT + INTERMARGIN) * c +
            (PERFMETER_HEIGHT / 2) - (s->h / 2);
    if (c == NBCORES + NBGPUS)
      dst.y += HISTOGRAM_HEIGHT / 2 - PERFMETER_HEIGHT / 2;

    SDL_BlitSurface (s, NULL, surface, &dst);
    SDL_FreeSurface (s);
  }

  TTF_CloseFont (font);

  text_texture = SDL_CreateTextureFromSurface (ren, surface);
  if (text_texture == NULL)
    exit_with_error ("SDL_CreateTexture failed: %s", SDL_GetError ());

  SDL_FreeSurface (surface);
}

static void cpustat_draw_text (void)
{
  SDL_Rect dst;

  dst.x = 0;
  dst.y = 0;
  dst.w = LEFT_MARGIN;
  dst.h = WINDOW_HEIGHT;

  SDL_RenderCopy (ren, text_texture, NULL, &dst);
}

static void cpustat_draw_perfmeters (void)
{
  SDL_Rect src, dst;

  src.x = 0;
  src.y = 0;
  src.w = PERFMETER_WIDTH;
  src.h = PERFMETER_HEIGHT;

  dst.x = LEFT_MARGIN;
  dst.y = TOP_MARGIN;
  dst.w = PERFMETER_WIDTH;
  dst.h = PERFMETER_HEIGHT;

  for (int c = 0; c < NBCORES + NBGPUS; c++) {
    SDL_RenderCopy (ren, perf_frame[c % EZP_MAX_COLORS], &src, &dst);
    dst.w = cpustat_activity_ratio (c) * PERFMETER_WIDTH;
    src.w = dst.w;
    SDL_RenderCopy (ren, perf_fill[c % EZP_MAX_COLORS], &src, &dst);
    dst.w = PERFMETER_WIDTH;
    src.w = dst.w;
    dst.y += PERFMETER_HEIGHT + INTERMARGIN;
  }
}

static void cpustat_draw_idleness (void)
{
  SDL_Rect src, dst;

  for (int i = 0; i < HISTOGRAM_HEIGHT; i++) {
    // Shift previous bars to the left
    for (int j = 0; j < HISTOGRAM_WIDTH - BAR_WIDTH; j++)
      idle_img[i * HISTOGRAM_WIDTH + j] =
          idle_img[i * HISTOGRAM_WIDTH + j + BAR_WIDTH];

    // Clear last (right) slot
    for (int j = HISTOGRAM_WIDTH - BAR_WIDTH; j < HISTOGRAM_WIDTH; j++)
      idle_img[i * HISTOGRAM_WIDTH + j] = 0;
  }

  {
    float idleness  = idle_total ();
    unsigned HEIGHT = idleness * BAR_HEIGHT;
    uint8_t red     = idleness * 255;
    uint8_t green   = (1.0 - idleness) * 255;
    uint32_t color  = ezv_rgb (red, green, 0);

    for (int i = HISTOGRAM_HEIGHT - HEIGHT; i < HISTOGRAM_HEIGHT; i++)
      for (int j = HISTOGRAM_WIDTH - BAR_WIDTH; j < HISTOGRAM_WIDTH - 1; j++)
        idle_img[i * HISTOGRAM_WIDTH + j] = color;
  }

  SDL_UpdateTexture (idle_texture, NULL, idle_img,
                     HISTOGRAM_WIDTH * sizeof (Uint32));

  src.x = 0;
  src.y = 0;
  src.w = HISTOGRAM_WIDTH;
  src.h = HISTOGRAM_HEIGHT;

  // On redimensionne l'image pour qu'elle occupe toute la fenêtre
  dst.x = LEFT_MARGIN;
  dst.y = INITIAL_WINDOW_HEIGHT;
  dst.w = HISTOGRAM_WIDTH;
  dst.h = HISTOGRAM_HEIGHT;

  SDL_RenderCopy (ren, idle_texture, &src, &dst);
}

void cpustat_init (int x, int y)
{
  SDL_DisplayMode dm;

  if (SDL_GetDesktopDisplayMode (0, &dm) != 0)
    exit_with_error ("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError ());

  MAX_WINDOW_HEIGHT = dm.h - 128; // to account for headers, footers, etc.

  NBCORES = easypap_requested_number_of_threads ();
  if (gpu_used)
    NBGPUS = easypap_number_of_gpus ();

  cpu_stats = malloc ((NBCORES + NBGPUS) * sizeof (cpu_stat_t));

  for (;;) {
    WINDOW_WIDTH          = LEFT_MARGIN + PERFMETER_WIDTH + RIGHT_MARGIN;
    INITIAL_WINDOW_HEIGHT = TOP_MARGIN + BOTTOM_MARGIN +
                            (NBCORES + NBGPUS) * PERFMETER_HEIGHT +
                            (NBCORES + NBGPUS - 1) * INTERMARGIN;
    WINDOW_HEIGHT = INITIAL_WINDOW_HEIGHT + INTERMARGIN + HISTOGRAM_HEIGHT;

    if (WINDOW_HEIGHT <= MAX_WINDOW_HEIGHT)
      break;

    if (INTERMARGIN > 1)
      INTERMARGIN -= 1;
    else if (PERFMETER_HEIGHT > 4)
      PERFMETER_HEIGHT -= 2;
    else
      exit_with_error ("Sorry, I'm unable to display so many CPU meters");
  }

  win = SDL_CreateWindow ("Activity Monitor", x, y, WINDOW_WIDTH, WINDOW_HEIGHT,
                          SDL_WINDOW_SHOWN);
  if (win == NULL)
    exit_with_error ("SDL_CreateWindow failed: %s", SDL_GetError ());

  // Initialisation du moteur de rendu
  ren = SDL_CreateRenderer (
      win, -1, SDL_RENDERER_ACCELERATED /*| SDL_RENDERER_PRESENTVSYNC*/);
  if (ren == NULL)
    exit_with_error ("SDL_CreateRenderer failed: %s", SDL_GetError ());

  SDL_RendererInfo info;
  SDL_GetRendererInfo (ren, &info);
  PRINT_DEBUG ('g', "Activity window renderer: [%s]\n", info.name);

  if (TTF_Init () < 0)
    exit_with_error ("TTF_Init failed (%s)", TTF_GetError ());

  cpustat_create_text_texture ();

  cpustat_create_cpu_textures ();

  cpustat_create_idleness_textures ();

  TTF_Quit ();
}

void cpustat_reset (long now)
{
  for (int c = 0; c < NBCORES + NBGPUS; c++) {
    cpu_stats[c].cumulated_idle = cpu_stats[c].cumulated_work =
        cpu_stats[c].nb_tiles   = 0;
    cpu_stats[c].start_time     = 0;
    cpu_stats[c].end_time       = now;
  }
}

void cpustat_start_work (long now, int who)
{
  // How long did the cpu sleep?
  cpu_stats[who].cumulated_idle += (now - cpu_stats[who].end_time);
  cpu_stats[who].nb_tiles++;
  cpu_stats[who].start_time = now;
}

long cpustat_finish_work (long now, int who)
{
  long duration = now - cpu_stats[who].start_time;

  // How long did the cpu work?
  cpu_stats[who].cumulated_work += duration;
  cpu_stats[who].end_time = now;

  return duration;
}

void cpustat_deduct_idle (long duration, int who)
{
  cpu_stats[who].cumulated_idle -= duration;
}

void cpustat_freeze (long now)
{
  for (int c = 0; c < NBCORES + NBGPUS; c++)
    cpu_stats[c].cumulated_idle += (now - cpu_stats[c].end_time);
}

float cpustat_activity_ratio (int who)
{
  long total = cpu_stats[who].cumulated_work + cpu_stats[who].cumulated_idle;

  if (total == 0)
    return 0.0;

  return (float)cpu_stats[who].cumulated_work / total;
}

void cpustat_display_stats (void)
{
  SDL_RenderClear (ren);

  cpustat_draw_text ();

  cpustat_draw_perfmeters ();

  cpustat_draw_idleness ();

  SDL_RenderPresent (ren);

  // for (int c = 0; c < NBCORES; c++)
  //   PRINT_DEBUG ('p', "CPU Utilization for core %2d: %3.2f\n", c,
  //                100.0 * cpustat_activity_ratio (c));
}

void cpustat_clean (void)
{
  if (cpu_stats != NULL) {
    free (cpu_stats);
    cpu_stats = NULL;
  }
  if (idle_texture != NULL) {
    SDL_DestroyTexture (idle_texture);
    idle_texture = NULL;
  }

  if (text_texture != NULL) {
    SDL_DestroyTexture (text_texture);
    text_texture = NULL;
  }

  if (perf_fill != NULL) {
    for (int c = 0; c < EZP_MAX_COLORS; c++)
      free (perf_fill[c]);
    free (perf_fill);
    perf_fill = NULL;
  }

  if (perf_frame != NULL) {
    for (int c = 0; c < EZP_MAX_COLORS; c++)
      free (perf_frame[c]);
    free (perf_frame);
    perf_frame = NULL;
  }
}
