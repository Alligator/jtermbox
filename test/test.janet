(import ../termbox :as tb)

(defn draw-string [x y str]
  (loop [[idx chr] :pairs str]
    (tb/change-cell (+ x idx) y (string/from-bytes chr))))

(defn clear-line [y]
  (loop [x :range [0 (tb/width)]]
    (tb/change-cell x y " ")))

(defn draw-colours [x y]
  (loop [cx :range [x (+ x 18) 2]
         cy :range [y (+ y 9)]
         :let [fg (mod (- cx x) 8)
               bg (mod (- cy y) 8)]]
    (tb/change-cell cx cy "a" fg bg)
    (tb/change-cell (+ cx 1) cy "a" fg bg)))

(defn main [&arg]
  (tb/init)
  (tb/clear)

  (tb/select-input-mode :mouse)
  (draw-string 0 3 (string "current mode: " (tb/select-input-mode :current)))

  (draw-string 0 0 "type to see events. ctrl-c to quit")
  (draw-colours 5 5)
  (tb/present)

  (while true
    (def ev (tb/poll-event))

    (clear-line 1)
    (draw-string 0 1 (string/format "%j" ev))
    (draw-colours 5 5)

    (case (ev :type)
      "key" (case (ev :key)
              "ctrl-c" (break)))
    (tb/present))

  (tb/shutdown))
