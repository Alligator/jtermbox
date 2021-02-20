(import ../termbox :as tb)

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

  (tb/put-string 0 0 "type to see events. ctrl-c to quit" (tb/color :yellow))

  (tb/select-input-mode :mouse)
  (tb/put-string 0 3 (string "current mode: " (tb/select-input-mode :current)))

  (draw-colours 5 5)
  (tb/present)

  (while true
    (def ev (tb/peek-event 500))

    (clear-line 2)
    (tb/put-string 0 2 (string "time: " (os/time)))

    (if-not (nil? ev)
      (do
        (clear-line 1)
        (tb/put-string 0 1 (string/format "%j" ev) (tb/color :black) (tb/color :green))
        (draw-colours 5 5)

        (case (ev :type)
          "key" (case (ev :key)
                  "ctrl-c" (break)))))
    (tb/present))

  (tb/shutdown))
