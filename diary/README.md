# Racing Robots Dev Diary

In the past I've found it helpful/motivating to keep track of significant 
milestones I reach when I'm working on a project. So here's where I'll do that!

I'm a little late in starting this, so the very beginning entries will be 
missing. Maybe I'll backfill them later.

## 20-02-12 / SDL2_gfx and Lobby Improvements

I wanted to render "stats cards" for each robot at various points in the game, 
so I created a `StatCard` entity and started playing with what the card would 
look like. I ended up having to grab 
[SDL2_gfx](https://sourceforge.net/projects/sdl2gfx/) in order to render 
more complex 2D primitives (like thicker lines) which took up a bunch of time 
to build. I ended up writing my own little script to build it on Windows 
[here](https://github.com/haydenmc/sdl2gfx/blob/master/windowsbuild.cmd).

It looks significantly nicer now!

![Screenshot of the new and improved lobby scene, complete with cool little 
stat cards](200212-startinglineup.png)

Soon I need to figure out core gameplay mechanics (I have a very very simple 
racing scene up and running now).

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