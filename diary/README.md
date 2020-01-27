# Racing Robots Dev Diary

In the past I've found it helpful/motivating to keep track of significant 
milestones I reach when I'm working on a project. So here's where I'll do that!

I'm a little late in starting this, so the very beginning entries will be 
missing. Maybe I'll backfill them later.

## 20-01-26 / Lobby Scene

Today I added a Lobby scene! This is where you'll be able to see a summary 
of the starting lineup for the upcoming race. Eventually, this is where 
spectators will be able to see stats, submit bets, and potentially rig the 
race in various other ways.

For now, though, it's just a rudimentary screen that just paints the robots 
from the current lineup (plus some header text).

I've also added the logic to calculate the current lineup 
(just a simple shuffle), plus some helpful additions to the `Scene` object 
to enable behaviors when the scene is shown by the game, and when it has been 
hidden.

![Screenshot of the current state of the lobby scene](200126-lobby.png)