#include <pebble.h>
#include "elements.h"
void chime_layer_set(int i);
void tick_handler(struct tm *tick_time, TimeUnits units_changed);
	
static TextLayer* text_layer_init(GRect location, GColor background, GTextAlignment alignment, int font)
{
	TextLayer *layer = text_layer_create(location);
	text_layer_set_text_color(layer, GColorBlack);
	text_layer_set_background_color(layer, background);
	text_layer_set_text_alignment(layer, alignment);
	if(font == 1){
		text_layer_set_font(layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	}
	else if(font == 2){
		text_layer_set_font(layer, fonts_get_system_font(FONT_KEY_GOTHIC_28));
	}
	return layer;
}

void found_time(int amounttovibe){
	if(amounttovibe == 1){
		vibes_enqueue_custom_pattern(vibe_segments_1);
	}
	else if(amounttovibe == 2){
		vibes_enqueue_custom_pattern(vibe_segments_2);
	}
	else if(amounttovibe == 3){
		vibes_enqueue_custom_pattern(vibe_segments_3);
	}
	else if(amounttovibe == 4){
		vibes_enqueue_custom_pattern(vibe_segments_4);
	}
	else if(amounttovibe == 5){
		vibes_enqueue_custom_pattern(vibe_segments_5);
	}
	else if(amounttovibe == 6){
		vibes_enqueue_custom_pattern(vibe_segments_6);
	}
	else if(amounttovibe == 7){
		vibes_enqueue_custom_pattern(vibe_segments_7);
	}
	else if(amounttovibe == 8){
		vibes_enqueue_custom_pattern(vibe_segments_8);
	}
	//Prevent any weird values seeping through
	if(amounttovibe > 0 && amounttovibe < 9){
		chime_layer_set(amounttovibe);
	}
}

int get_chimes(int fixed_m8){
	int returnvalue = 20;
	if(hour > 15 && hour < 20){
		//Dog watch(s) - 2 hours
		int i, j;
		// for loops 4 life
		for(j = 0; j < 1; j++){
			for(i = 0; i < 4; i++){
				if(dog_watch[j][i] == fixed_m8){
					//APP_LOG(APP_LOG_LEVEL_INFO, "Yep!");
					returnvalue = i;
					i = 9;
				}
				else{
					//APP_LOG(APP_LOG_LEVEL_INFO, "%d != %d. J == %d, I == %d", dog_watch[j][i], fixed_m8, j, i);
				}
			}
		}
	}
	else{
		//Normal watch(s) - 4 hours
		int i, j;
		for(j = 0; j < 5; j++){
			for(i = 0; i < 8; i++){
				if(normal_watch[j][i] == fixed_m8){
					//APP_LOG(APP_LOG_LEVEL_INFO, "%d == %d", normal_watch[j][i], fixed_m8);
					returnvalue = i;
					i = 11;
				}
				else{
					//APP_LOG(APP_LOG_LEVEL_INFO, "%d != %d. J == %d, I == %d", normal_watch[j][i], fixed_m8, j, i);
				}
			}
		}
	}
	//APP_LOG(APP_LOG_LEVEL_INFO, "Return value of: %d", returnvalue+1);
	return returnvalue+1;
}

void chime_layer_set(int oh_baby_a_triple){
	if(oh_baby_a_triple != 1){
		snprintf(buzz_buffer, sizeof(buzz_buffer), "Last chimed %d times", oh_baby_a_triple);
	}
	else{
		snprintf(buzz_buffer, sizeof(buzz_buffer), "Last chimed %d time", oh_baby_a_triple);
	}
	text_layer_set_text(last_buzz_layer, buzz_buffer);
}

void update_chimed_layer(){
	if(minute > 30){
		custommin = 30;
	}
	else if(minute < 30){
		custommin = 0;
	}
	customfix = (hour*100)+custommin;
	chimes = get_chimes(customfix);
	if(chimes != 1){
		snprintf(buzz_buffer, sizeof(buzz_buffer), "Last chimed %d times", chimes);
	}
	else{
		snprintf(buzz_buffer, sizeof(buzz_buffer), "Last chimed %d time", chimes);
	}
	text_layer_set_text(last_buzz_layer, buzz_buffer);
	//APP_LOG(APP_LOG_LEVEL_WARNING, "customfix: %d, chimes: %d", customfix, chimes);
}
	
void window_load(Window *window){
	Layer *window_layer = window_get_root_layer(window);
	watch_layer = text_layer_init(GRect(0, 20, 144, 168), GColorClear, GTextAlignmentCenter, 1);
	last_buzz_layer = text_layer_init(GRect(0, 100, 144, 168), GColorClear, GTextAlignmentCenter, 2);
	text_layer_set_text(watch_layer, "First watch");
	text_layer_set_text(last_buzz_layer, "Last chimed ? times");
	theme = inverter_layer_create(GRect(0, 0, 144, 168));
	layer_add_child(window_layer, text_layer_get_layer(watch_layer));
	layer_add_child(window_layer, text_layer_get_layer(last_buzz_layer));
	layer_add_child(window_layer, inverter_layer_get_layer(theme));
	
	struct tm *t;
  	time_t temp;        
  	temp = time(NULL);        
  	t = localtime(&temp);
	
	tick_handler(t, MINUTE_UNIT);
	
	update_chimed_layer();
}

void window_unload(Window *window){
	
}

void update_watch_layer(){
	int oi_oi_m8 = 0;
	if(hour >= 0 && hour < 4){
		oi_oi_m8 = 0;
	}
	else if(hour > 3 && hour < 8){
		oi_oi_m8 = 1;
	}
	else if(hour > 7 && hour < 12){
		oi_oi_m8 = 2;
	}
	else if(hour > 11 && hour < 16){
		oi_oi_m8 = 3;
	}
	else if(hour > 15 && hour < 18){
		oi_oi_m8 = 6;
		snprintf(watch_buffer, sizeof(watch_buffer), "%s", dog_char[0]);
	}
	else if(hour > 17 && hour < 20){
		oi_oi_m8 = 7;
		snprintf(watch_buffer, sizeof(watch_buffer), "%s", dog_char[1]);
	}
	else if(hour > 19 && hour < 24){
		oi_oi_m8 = 4;
	}
	
	if(oi_oi_m8 != 6 && oi_oi_m8 != 7){
		snprintf(watch_buffer, sizeof(watch_buffer), "%s", watch_char[oi_oi_m8]);
	}
	text_layer_set_text(watch_layer, watch_buffer);
}

void tick_handler(struct tm *tick_time, TimeUnits units_changed){
	second = tick_time->tm_sec;
	minute = tick_time->tm_min;
	hour = tick_time->tm_hour;
	
	fixed = (hour*100)+minute;
	found_time(get_chimes(fixed));
	update_watch_layer();
}
	
void init(void){
	window = window_create();
	window_set_window_handlers(window, (WindowHandlers){
		.load = window_load,
		.unload = window_unload,
	});
	tick_timer_service_subscribe(MINUTE_UNIT, &tick_handler);
	window_stack_push(window, true);
}

void deinit(void){
	
}

int main(){
	init();
	app_event_loop();
	deinit();
}