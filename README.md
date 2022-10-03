# Air-racing

**Technologies:** C++, Python, Ubisoft Hacker's Nest API, Google Mediapipe

This was my solo project for Hack the North 2022. I was trying to build a simple racing game using Ubisoft's Hacker's Nest API which is a simple game engine written in C++.

## Idea

The idea was to have two components: the game (written in C++) and the controls (written in Python). The player would be able to control the car with their hand that would be detected by the device's camera. This part was made using Google Mediapipe's features for detecting landmarks on hands. The corresponding hand movements were then mapped to keystrokes to control the game.

(Originally, I'd planned to have controls that would resemble the steering wheel of cars. This would be achieved by calculating the slope of the line found by joining two specific points in the two hands. While this approach worked, it restricted me to only one axis, whereas the game was built around two axes, so I abandoned this approach.)

## Challenges

- One of the first challenges was displaying all the textures for the entities and background in a way that looked natural. Sizing was an issue that was eventually fixed.
- Randomly spawning obstacles and getting the car to shoot projectiles were also issues that I ran into but fixed eventually.
- The two parts of the project worked independently - i.e. the game could be controlled using the keyboard, and the hand's landmark features were being detected and keystrokes replicated. However, I was not able to get the two parts to interact with each other seamlessly (and hence was not able to submit the project for judging).

## What I learnt

- I learnt about Google Mediapipe's amazing features and to use them to do different kinds of things. I played around with calculating which direction the car should move in by normalizing the coordinates of the palm, calculating deviations from the "center", and making decisions accordingly. This was my first time working with Mediapipe and I'm excited to design more applications with it in the future.

- I learnt about the Entity-Component model that is used in video-game design - it resembles the concept of inheritance but they are not quite the same. I learnt that Components have to be added to Entities for the Entities to exhibit certain kinds of behavior outlined in the corresponding Components.
