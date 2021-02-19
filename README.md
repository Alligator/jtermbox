# termbox janet bindings

These are quite unfinished, but the basics are there.

```clojure
(import termbox :as tb)

(defn draw-string [x y str]
  (loop [[idx chr] :pairs str]
    (tb/change-cell (+ x idx) y (string/from-bytes chr))))

(defn main [& args]
  (tb/init)
  (tb/clear)

  (draw-string 0 0 "type to see events. ctrl-c to quit")
  (tb/present)

  (while true
    (def ev (tb/poll-event))
    (draw-string 0 1 (string/format "%j" ev))
    (case (ev :type)
      "key" (case (ev :key)
              "ctrl-c" (break)))
    (tb/present))

  (tb/shutdown))
```

It sticks pretty closely to the termbox API. `termbox/color` is provided to create colors.

## functions

```
(termbox/init)
  initialize the termbox library.
  must be called before any other functions.
  
(termbox/shutdown)
  restore the terminal to it's initial state.

(termbox/clear)
  clear the internal terminal buffer.

(termbox/set-clear-attributes fg bg)
  set the attributes used when clearing the screen with clear.

(termbox/change-cell x y ch &opt fg bg)
  change a cell in the internal bufffer at the specified position.
  fg and bg default to (tb/color :default).

(termbox/color & kws)
  create a termbox color. accepts a color followed by any number of modifiers.
  
  valid keywords are :default :black :red :green :yellow :blue :magenta :cyan
  :white :bold :underline :reverse
  
  in 256 color, 216 color and grayscale modes, use numbers rather than keywords
  to select colors.

(termbox/present)
  sync the internal buffer with the terminal.

(termbox/height)
  return the height of the terminal

(termbox/width)
  return the width of the terminal

(termbox/poll-event)
  wait for an event and return it.
  
  there are three types of event.
  key events, which contain either a character or a key name:
  
  @{:type "key" :ch "a" :key "arrow-down"}
  
  resize events, which contain a width and height:
  
  @{:type "resize" :w 640 :h 480}
  
  and mouse events, which contain x and y co-ordinates:
  
  @{:type "mouse" :x 20 :y 60}

(termbox/selet-output-mode)
  set the output mode.
  valid modes are :normal :256 :216 :grayscale and :current.
  when called with :current, will return the current mode as a keyword.

(termbox/set-cursor cx cy)
  set the position of the cursor. pass -1 for both cx and cy to hide the cursor.
```

## events

The result from `(termbox/poll-event)` can be one of three things.

Key events, which contain either a character or a key name:
```clojure
@{:type "key" :ch "a" :key "arrow-down"}
```
Resize events, which contain a width and height:
```clojure
@{:type "resize" :w 640 :h 480}
```
Mouse events, which contain x and y co-ordinates:
```clojure
@{:type "mouse" :x 20 :y 60}
```
