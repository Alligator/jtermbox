(import termbox :as tb)

(defn main [& args]
  (tb/select-output-mode :256)
  (tb/init)
  (tb/clear)

  (loop [[idx chr] :pairs "256 color test. press any key to quit"]
    (tb/change-cell idx 0 (string/from-bytes chr)))

  (def width 40)

  (loop [c :range [0 256]
         :let [y (math/floor (/ (* c 4) width))
               x (% (* c 4) width)
               cstr (string c)]]
    (loop [[idx chr] :pairs cstr]
      (tb/change-cell (+ x idx) (+ y 1) (string/from-bytes chr) c)))

  (tb/present)

  (def ev (tb/poll-event))
  (tb/shutdown))
