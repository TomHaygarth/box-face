# box-face
BoxFace (Xbox Controller Interface) is a simple win32 app for mapping controller input to keyboard and mouse input

The project was originally written in 2013 to learn about and create a nice XInput controller interface. After creating the controller interface I decided to expand the application to start mapping keyboard and mouse input to various controller buttons and inserting them into the Windows message loop of the application.
### note: At the moment (apart from mouse movement) only keyboard and mouse input can be passed into the window when it has been selected in the app (see 'Current button mapping')

## Requirements
Requires the DirectX SDK to get the XInput API

## Current features
* Basic FPS button mappings
* Adjustable mouse sensitivity

## Current button mapping
* Back Button: Selects the window that currently has the mouse over it to send input to 
* Right analogue stick: controls mouse (No inverted support)
* Left analogue stick: Sends W,A,S,D key presses (when the corresponding axis is > 60%)
* Start: sends Escape button presses
* A: Sends spacebar
* B: Sends E
* Left Shoulder: Sends Left shift
* Up/Down D-pad: Adjusts mouse movement sensitivity
* Left/Right D-pad: Sends mouse scrollwheel
* Right Trigger: Over 60% sends left mouse down
* Left Trigger: Over 60% sends right mouse down
