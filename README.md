# Hex
Hex is a strategy board game played on a hexagonal grid, theoretically of any size and several possible shapes, but traditionally as an 11×11 rhombus.
Through the Hex Algorithm we can predict and counter the moves of the opponent and establish an all-time winning scenario. 
This self developed algorithm encompasses the use of Breadth-First-Search. Having visualized the whole 7 X 7 hex board as an array , 
the implementation of graph algorithms give us the desired result of obtaining a winning strategy . The basic game is that each player has an allocated color,
conventionally Red and Blue. Players take turns placing a stone of their color on a single cell (hex)within the overall playing board.
The goal for each player is to form a connected path of their own stones linking the opposing sides of the board marked by their colors,
before their opponent connects his or her sides in a similar fashion. The first player to complete his or her connection wins the game. 
The four corner hexagons each belong to both adjacent sides.

The HEX Algorithm
1. Find a node which is nearest to either 0th right or 0th left or in middle.
2. Find the end point from the 0th (which we can be either right or left or middle, got from step1).
3. If the endpoint is in middle diagonal then check its neighbour (both up and down) diagonal point, if it is filled then fill the extreme corner on the growing side of the diagonal side.
4. If the neighbouring (up and down) Hex is not filled then:
4.1) If the opponent point is having continuous path from 0th node fill the end of node
Then 2 possibilities occur:
a.) Find the shortest path from end node to then end of 0th source and fill the 1st node which is part of shortest path.
b.) Find the shortest path from end point from the 0th source (which we found in the 2nd point) and fill the node which is the first newest to end point.
5. Goto step 2
