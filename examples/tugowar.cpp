#include "hexxx.h"
#include "buffer.h"

void logic_thread() {
  
  ws2811_led_t c = COLOR_WHITE;
  Buffer* buffer = new Buffer();
  
  while (1) {
    
    ws2811_led_t winner = 0;
    int position = 0; // start in the center of the hexagon
    
    reset_button_states();
    while( winner == 0 ) {
      
      // players tug the center LED to get it to their homebases
      if( button_rising[ 0 ] )
        position = neighbor( position, 4 );
      if( button_rising[ 1 ] )
        position = neighbor( position, 5 );
      if( button_rising[ 2 ] )
        position = neighbor( position, 2 );
      if( button_rising[ 3 ] )
        position = neighbor( position, 3 );
      if( button_rising[ 4 ] )
        position = neighbor( position, 0 );
      if( button_rising[ 5 ] )
        position = neighbor( position, 1 );
    
      reset_button_states(); // make sure to clear out button states everytime after having handled all of them in the current iteration
    
      buffer->fill( 0 );
      for( int i = 0; i < 12; i++ ) {
        buffer->setPixel( polar2led( 11, i ), COLOR_RED );
        buffer->setPixel( polar2led( 11, 22 + i ), COLOR_GREEN );
        buffer->setPixel( polar2led( 11, 44 + i ), COLOR_BLUE );
      }
      winner = buffer->getPixel( position );
      buffer->setPixel( position, c );
      buffer->render();

      usleep(10000); // 100 per second
      
    }
    
    for( int i = 0; i < 5; i++ ) {
      buffer->fill( winner, 0.5 );
      buffer->render();
      usleep(200000);
      buffer->fill( COLOR_BLACK );
      buffer->render();
      usleep(200000);
    }
    
  }
  
}
