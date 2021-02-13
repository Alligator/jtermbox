# termbox janet bindings

These are quite unfinished, but the basics are there.

```clojure
(import termbox :as tb)

(defn draw-string [x y str]
  (loop [[idx chr] :pairs str]
    (tb/change-cell (+ x idx) y (string/from-bytes chr))))

(defn main [&arg]
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
  init the library. must be called before anytihng else.
  
(termbox/shutdown)
  clean-up the library (restore terminal state, etc).
  
(termbox/clear)
  clear the internal buffer.
  
(termbox/present)
  sync the internal buffer with the terminal.
  
(termbox/change-cell x y ch &opt fg bg)
  change the cell at x, y to the character ch with fg and bg colours.

(termbox/color & kws)
  create a termbox color. see docs or termbox.janet for valids keyword arguments.
  
(termbox/poll-event)
  wait for an event. see below.
  
(termbox/set-cursor cx cy)
  set the cursor position. pass cx and cy as -1 to hide it.
  
(termbox/width)
  get the terminal width.
  
(termbox/height)
  get the terminal height.
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
