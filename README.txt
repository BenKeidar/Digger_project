Digger - README:
Written By:
Ben Keidar : 208308817 
Alexander  Bord : 319263836
===========================================================================
General Description of program:
to win the digger needs to eat all diamonds of all the levels before it's life value is set to 0, the victory window is oppened and the player can choose to quit or play again.
if the life value is set to 0 the game is over and a game over window is opened to choose if the player wants to play again or quit.
===========================================================================
Design
"Digger" game, using the "SFML" Graphic Library. 
The program defines the following 19 classes: 
object, dynamicObject, digger, sample, staticObject, diamond, wall, stone, MenuButton, ExitButton, HelpButton, StartButton, Board, Controller, Menu, Singleton, Toolbar, keep_info (struct), directions_t (enum).
Inheritance:
Object <== DynamicObject, StaticObject 
DynamicObject <== Digger, Monster
StaticObject <==  Diamond, Wall, Stone
===========================================================================
Level Format
the level format is "level num.txt".
example: 1.txt
List of files
1) Controller.cpp - runs the menu window and the main function, runs alongside the other classes as well, and also it runs all nesting classes.
2) Menu.cpp – the purpose of this class is to have a menu in which the player can choose if he wants to play or help or quit.
3) Board.cpp– the purpose of this class is to upload from map the level .
4) Object.cpp  – it's purpose is to hold the virtual draw function.
5) DynamicObject.cpp - base class for all dynamic objects.
6) Digger.cpp - Dynamic object.
7) Monster.cpp - Dynamic object.
8) StaticObject.cpp - base class for all dynamic objects.
9) Diamond.cpp - Static Object.
10) Wall.cpp - Static Object.
11) Stone.cpp - Static Object.
12) MenuButton.cpp - base class for specific button.
13) StartButton.cpp - specific button.
14) HelpButton.cpp - specific button.
14) Exit.cpp - specific button.
15) Menu.cpp - will manage the menu.
16) Singleton.cpp - hold the pictures.
17) Toolbar.cpp - will manage all the clocks in the game.
18)keep_info - holds the icon and location of creature
===========================================================================
algorithms: 
Manhattan Algorithm for Smart Demon AI.
===========================================================================
Known Bugs: ===========================================================================

