(import ../build/termbox)

(defn draw-string [str x y]
  (loop [i :range [0 (length str)]]
    (termbox/change-cell (+ x i) y (string/from-bytes (str i)))))

(defn box [title x y w h]
  (loop [cx :range [x (+ x w)]]
    (termbox/change-cell cx y "-")
    (termbox/change-cell cx (+ y h) "-"))
  (loop [cy :range [y (+ y h)]]
    (termbox/change-cell x cy "|")
    (termbox/change-cell (+ x w) cy "|"))
  (termbox/change-cell x y "+")
  (termbox/change-cell (+ x w) y "+")
  (termbox/change-cell x (+ y h) "+")
  (termbox/change-cell (+ x w) (+ y h) "+")
  (draw-string title (+ x 1) y))

(termbox/init)
(termbox/clear)

(box "bocs" 5 5 20 10)
(termbox/present)

(var content "")
(while true
  (def ev (termbox/poll-event))
  (case (ev :type)
    "key" (case (ev :key)
            "esc" (break)
            "space" (set content (string content " "))
            nil (set content (string content (ev :ch)))))
  (draw-string content 6 6)
  (termbox/present))

(termbox/shutdown)
