ArchLoader is a utility to unlock the Halo 4 Network Test for offline, system link and online use. 
The beta was designed to be a limited-time matchmaking beta, but this will allow you to play Custom Games or Forge, and use the Theater. Matchmaking is possible without the game's servers through offline hoppers. It also allows you to modify camera views (third person, flycam, etc) and change Direct X rendering modes (point or wireframe), among other tweaks such as Field of View and Time Scale. The module loads itself as a system dll (since Xbox 360 can only launch one title executable at a time) so it can run in the background while the game executes, patch it, and hook into it, so the game will jump into code in this executable, allowing you to make changes to the game in C++ instead of patching assembly instructions. 


NON-CONTROLLED PATCHES
======================
* Bypassed whitelist/authorization checks, beta allows access.
* Offline profiles appear to be online to the game, allowing access without live.
* Hooked switch lobby code to unlock multiple lobbies. Backing out will alternate them.
* Patched network status. (No ethernet = Local, Ethernet = System Link, Online = Xbox Live).
* Game will work without any game servers available now! Armor and other properties will be read from offline data. (games can still be played with friends).
* Split-screen mode enabled.
* Awarded maximum credits and unlocked all armor.
* Removed map hash and other verification checks.
* Debug output hooked to print out.



CONTROLS
========
* back+start+dpad-up = force-load longbow
* back+start+dpad-right = force-load adrift
* back+start+dpad-down = force-load haven
* back+start+dpad-left = return to mainmenu
* back+lthumb = print cam debug info toggle
* back+rthumb = fill mode toggle
* lbumper+dpad-up = first person
* lbumper+dpad-down = third person
* lbumper+dpad-right = flycam
* lbumper+dpad-left = static cam
* lthumb+rthumb = toggle time freeze
* b+dpad-right = increase game speed
* b+dpad-left = decrease game speed
* b+dpad-up = decrease field of view
* b+dpad-down = increase field of view
