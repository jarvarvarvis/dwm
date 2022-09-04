# dwm configuration tutorial

## Terminology

A tag refers to a collection of clients or simply said, a workspace that contains multiple windows.
A client refers to a singular window in some tag.

## Keybinds

Modifier Key: Mod4 (Windows Key)


### Programs

Mod + d                     | Start dmenu
Mod + a                     | Start dmenu desktop file launcher
Mod + t                     | Start terminal (kitty)
Mod + Alt + h               | Show this help document

### Focus

Mod + j                     | Change focus to next client
Mod + k                     | Change focus to previous client

### Stack

Mod + Shift + j             | Rotate the stack forwards, cycling all clients in the current tag
Mod + Shift + k             | Rotate the stack backwards, cycling all clients in the current tag

Mod + Shift + z             | Move the focused client to the master area, the previous master client is pushed on the stack

### Master area

Mod + Ctrl + h              | Decrement the factor of the master area
Mod + Ctrl + l              | Increment the factor of the master area

Mod + Ctrl + i              | Increment number of clients in the master area
Mod + Ctrl + d              | Decrement number of clients in the master area
Mod + Ctrl + 0              | Reset the number of clients in the master area to 0

### Client factor

Mod + Ctrl + j              | Increment the factor of the focused client
Mod + Ctrl + k              | Decrement the factor of the focused client
Mod + Ctrl + o              | Reset factor of the focused client

### Floating client position

Mod + ArrowLeft             | Move the currently focused client (floating) left
Mod + ArrowRight            | Move the currently focused client (floating) right
Mod + ArrowUp               | Move the currently focused client (floating) up
Mod + ArrowDown             | Move the currently focused client (floating) down

### Floating client scale

Mod + Shift + ArrowLeft     | Scale the currently focused client (floating) to the left
Mod + Shift + ArrowRight    | Scale the currently focused client (floating) to the right by
Mod + Shift + ArrowUp       | Scale the currently focused client (floating) upwards by
Mod + Shift + ArrowDown     | Scale the currently focused client (floating) downwards by

### Gaps

Mod + Plus                  | Increment gap size
Mod + Minus                 | Decrement gap size
Mod + 0                     | Reset gap size

### Clients

Mod + q                     | Kill the currently focused client
Mod + Space                 | Toggle floating for the currently focused client
Mod + F11                   | Toggle client fullscreen state when F11 is not supported

### Layout switching

Mod + Alt + t               | Tiling layout (windows are oriented in a grid-like fashion)
Mod + Alt + f               | Floating layout (windows can be moved around freely)
Mod + Alt + m               | Monocle layout (only the focused window is visible in fullscreen)

### Tags

Available tags: 1 - 9

Mod + [tag]                 | Switch to tag [tag]
Mod + Shift + [tag]         | Move the focused client to tag [tag]
Mod + Ctrl + [tag]          | Toggle view for tag [tag] in the current tag
Mod + Ctrl + Shift + [tag]  | Make the focused client also available in tag [tag]

### Session

Mod + Shift + e             | Quit session
Mod + Shift + r             | Restart session
