#pragma once
#define TEXTLENGTH 50 
#define horizontal_line  "--------------------------------------------" 
int menu(const char* menu_list[], int menu_length, const char* quit_key, bool alpha = false,
	bool case_sensitive = false, const char* prompt = "«Î÷ÿ–¬ ‰»Î",
	const char* header = horizontal_line, const char* bottom = horizontal_line);
