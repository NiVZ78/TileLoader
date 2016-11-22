#include <pebble.h>

#define tile_size 16;

static Window *s_game_window;
static Layer *s_game_layer;

static GBitmap *tile_set;
static GBitmap *tile[11][13];

static void draw_game_layer(Layer *layer, GContext *ctx) {

  // Initialise random number generator with seed
  srand(time(NULL));
  
  for (int i=0; i<9; i++){
    for (int j=0; j<11; j++){
      
      graphics_draw_bitmap_in_rect(ctx, tile[rand()%11][rand()%13], GRect(i*16,j*16,16,16));
    }
  }
  
}

static void load_tiles(){
  
  // Load the image with all the tiles
  tile_set = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TILES);
  
  // Loop through tile set rows
  for (int i=0; i<11; i++){
    // Loop through tile set cols
    for (int j=0; j<13; j++){
      // Cut out the tile
      tile[i][j] = gbitmap_create_as_sub_bitmap(tile_set, GRect( (i*16)+(i*1), (j*16)+(j*1), 16, 16 ));                                    
      
    }
  }
  
}


static void game_window_load(Window *window) {

  // Set the window background colour
  window_set_background_color(s_game_window, GColorBlack);  

  
  // Get the root window layer
  s_game_layer = window_get_root_layer(s_game_window);
  
  load_tiles();
  
  // Set the update proc
  layer_set_update_proc(s_game_layer, draw_game_layer);
  
  // Force redraw
  layer_mark_dirty(s_game_layer);
  
}


static void game_window_unload(Window *window) {
  
  
}



static void init() {
  // Create game Window element and assign to pointer
  s_game_window = window_create();
  
  
  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_game_window, (WindowHandlers) {
    .load = game_window_load,
    .unload = game_window_unload
  });
  
  // Show the Window on the watch, with animated=true
  window_stack_push(s_game_window, true);
  
}
  
  
static void deinit() {
    // Destroy Window
    window_destroy(s_game_window);
}


// MAIN PROGRAM LOOP
int main(void) {
  init();
  app_event_loop();
  deinit();
}
