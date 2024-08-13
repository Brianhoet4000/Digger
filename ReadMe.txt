Engine specifics:
Game Objects and Components:
In this engine, everything in the game are objects and are represented as Game Objects.
To make these Game Objects alive in the game, we use components.
Components are like specialized functions that give these game elements unique abilities.


The engine has other features, including:
-Audio Service -> This helps the game play sounds, like music or special effects
It can do loading, playing music, playing sound and it can mute all sounds.

-Input manager + Commands -> used to bind actions to keys/Controllers
when playing single -> Player can play with keyboard and controller.
when playing coop/versus -> the first controller is binded to the second player and the second controller to the first player.

-Observers -> are used to check when an emerald is picked up or all enemies are killed to advance to the next level. Also when the player dies it goes through the observer, same things for gaining points.

-States -> The goldbag uses states such as idle, hover, falling and coin. it switches between states depending on what happens.

https://github.com/Brianhoet4000/Digger