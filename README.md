# GTK Checkers
Checkers implemented as a C++ GUI application with GTK

## Build Instructions
Create and navigate to a build folder in the top directory of the repository.

`$ mkdir PATH-TO-REPO/build && cd PATH-TO-REPO/build`

Run the release build script (or debug script if developing)

`$ ../build-release`

Launch the binary and have fun!

`$ ./checkers`


## How to Play
2 Players

On a player's turn, the board will highlight the possible movesets for their pieces. The player must click one of the highlighted squares to see the possible destinations for the selected piece. If the player is satisfied with the move, they must click one of the highlighted destinations to complete the turn. Note: if the player does not want to commit the selected move, they can click the source square again to go back to the previous state. 

Sometimes a multi-part move is required when a player's piece must jump over more than one of the opponent's pieces. The board will indicate this by highlighting the same piece again, forcing the player to confirm the next jump until all jumps are satisified. 

When a player's piece reaches the end of the opponent's side of the board, a crown image will be displayed in the center of the piece indicating that piece has become a king. The piece may move both forward and backward as described in the standard Checkers ruleset.

The game follows the standard checkers ruleset. A player wins the game when all of the opponent's pieces have been wiped from the board. 
