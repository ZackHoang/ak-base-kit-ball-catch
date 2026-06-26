# Runtime sequence

## Overview

This document aims to explain Ball Catch's runtime sequence for each screen and how each object in each screens are handled.

Typically, games developed on the AK Base Kit would benefit from a seperate doc which explains the sequence of each object in a given game ([see Buu Quoc Phan's Archery Game](https://github.com/the-ak-foundation/archery-game)). However, this game is compact enough and only contain, practically speaking, two objects that has any substantial interaction. The crux of the entire game lies in the ball object which reads data from other objects and monitor its own behaviour. Thus, a seperate doc for objects' sequences might not be necessary.

## Screens

### Title & Game Over & Settings

```mermaid
sequenceDiagram
  participant Display Task
  participant Screen
  participant Button Callback
  participant Cursor
  participant Options
  Display Task->>Screen: SCREEN_ENTRY
  activate Screen
  Note right of Screen: Render title screen
  deactivate Screen
  Button Callback->>Cursor: AC_DISPLAY_BUTTON_UP_PRESSED
  activate Cursor
  Note right of Cursor: Move cursor up
  deactivate Cursor
  Button Callback->>Cursor: AC_DISPLAY_BUTTON_DOWN_PRESSED
  activate Cursor
  Note right of Cursor: Move cursor down
  deactivate Cursor
  Button Callback->>Options: AC_DISPLA_BUTTON_MODE_PRESSED
  activate Options
  Note right of Options: Confirm screen option<br/>or change setting
  deactivate Options
```

These screen's operation is quite straightforward: move the cursor up and down and select your screen that you want.

### Game

The core screen of the entire program (because what is a game without a screen of actual gameplay?).

There are three key stages for a ball catch's game play loop

- Initialization
- Gameplay loop
- Game over

#### Initialization

The beginning of the game, where all data must be properly set up each and everytime we enter our game screen. It does a few things:

- Reset score back to 0
- Reset target score
- Set the first ball's position
- Set the bar's position
- Set game over status
- Kick start two timers
  - Render timer (RENDER_GAME)
  - Gameplay timer (CHANGE_POS)

#### Gameplay loop

The gameplay loops continously runs as long as the game is not over. During this phase, balls will keep bouncing around the screen. Bar is controllable through up and down buttons. After every 5 points, an additional ball will spawn. There could only be five balls in total in a single game. Should a single be dropped, it's game over.

#### Game over

Once it's game over, the game will freeze and a small explosion sprite will be drawn over the dropped ball. A two seconds timer will kick in and user will be redirected to the game over screen, where they can either play again or exit.

```mermaid
sequenceDiagram
    participant Ball Timer (80ms)
    participant Display Task
    participant Button Callback
    participant Game Task
    participant Ball
    participant Wall
    participant Bar
    participant Score
    participant Target Score
    participant Buzzer
    participant EXIT
    participant EEPROM
    Button Callback->>Bar: AC_DISPLAY_BUTTON_UP_PRESSED
    activate Bar
    Note right of Bar: Move bar to the right
    deactivate Bar
    Button Callback->>Bar: AC_DISPLAY_BUTTON_DOWN_PRESSED
    activate Bar
    Note right of Bar: Move bar to the left
    deactivate Bar
    Ball Timer (80ms)->>Display Task: RENDER_GAME
    Display Task->>Game Task: SCREEN_ENTRY
    Note right of Game Task: init_game()
    Game Task->>Ball: Set first ball position
    Game Task->>Bar: Set bar position
    Game Task->>Score: Set score to 0
    Game Task->>Target Score: Set target score to 5
    loop Every 80ms<br/>while game_over = false
      Display Task->>Game Task: CHANGE_POS
      activate Game Task
      loop for every ball
        activate Ball
        Note right of Ball: change_ball_coords()
        Bar->>Ball: Read bar position
        Note right of Ball: is_touching_bar()
        Wall->>Ball: Read wall position
        Note right of Ball: is_touching_side_wall()
        Note right of Ball: is_touching_ceiling()
        Ball->>Buzzer: Play Buzzer
        Note right of Ball: is_ball_spawning()
        Ball->>Score: Increase score
        Ball->>Target Score: Increase target score
        Note right of Ball: is_game_over()
        Ball->>EXIT: is_game_over() == true
        activate EXIT
        Note right of EXIT: Render explosion sprite
        Note right of EXIT: game_over = true
        deactivate EXIT
        deactivate Ball
      end
      deactivate Game Task
    end
    EXIT->>EEPROM: Read and write best score
```
