#!/bin/bash

setxkbmap us
xmodmap -e "keycode 66 = Escape"
xmodmap -e "remove lock = Escape"


#!/bin/bash

setxkbmap fr -variant oss
xmodmap -e "keycode 66 = Escape"
xmodmap -e "remove lock = Escape"

