# **Chess in C**

This here is a simple chess program I wrote in C. It utilizes ANSI color sequences to print the board and
pieces.  

**Instructions included in project menu**  


This project includes two useful header files:
* standard_color.h
* standard.h

### standard_color.h 
is a simple program for formatting text (Colors, bold, italics, and underline). Using it is pretty straightforward:  
The file is made up of functions that you can call to change the color or format of the following text. 
* CLEAR_FORMAT clears all previous formatting
* NCLEAR_FORMAT clears all previous formatting and writes a newline (this is useful)
* BIU allows you to change formatting (ie bold, italics, underline)
* COLOR allows you to change the color of the text to a default color (look in enum colors)
* BG_COLOR allows you to change the background color of the text (highlights) using default background clors (look in enum bg_colors)
* RGB allows you to change the color of the text to some mix of red, green and blue
* BG_RGB allows you to change the background of the text to some RGB color.

BIU, COLOR, and BG_COLOR are all interchangeable (ie COLOR(BOLD) is valid) I added seperate functions in order to organize code better.  
It is my personal preferance to keep the color and formatting of the text on the same line as the printf function (ie. COLOR(BLUE); printf("HI\n); NCLEAR_FORMAT() )  
In the future, this file will change drastically.
  
### standard.h 
has functions that I find handy in many of my programs, but are not included in standard libraries.  

As a whole, this isn't a super complicated project. But it is free to use and copy. Enjoy!


