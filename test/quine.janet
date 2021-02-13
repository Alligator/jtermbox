# this program prints itself using termbox, with dodgy syntax highlighting
# up/down arrows to scroll
# any other key to quit
(import ../termbox :as tb)

(defn draw-src [src yoffset]
  (var x 0)
  (var y yoffset)

  (def src-array (reverse (map string/from-bytes src)))
  (defn consume [] (array/pop src-array))
  (defn peek [] (array/peek src-array))

  (defn show [chr &opt color]
    (default color (tb/color :default))
    (if (= "\n" chr)
      (do
        (set x 0)
        (set y (+ y 1)))
      (do
        (tb/change-cell x y chr color)
        (set x (+ x 1)))))

  (defn show-until [chr &opt color]
    (while (not= (peek) chr)
      (show (consume) color)))

  (while (def chr (peek))
    (cond
      # parens
      (index-of chr ["(" ")"])
      (show (consume) (tb/color :red))

      # string
      (index-of chr [`"` "`"])
      (do
        (show (consume) (tb/color :green))
        (show-until chr (tb/color :green))
        (show (consume) (tb/color :green)))

      # comment
      (= chr "#")
      (do
        (show-until "\n" (tb/color :cyan))
        (show (consume))) # show the newline

      # else
      (do
        (show chr)
        (consume))))

  (tb/present))

(defn main [& args]
  (def src (slurp "test/quine.janet"))
  (def num-lines (length (string/find-all "\n" src)))
  (def max-yoffset (max 0 (- num-lines (tb/height))))
  (var yoffset 0)

  (tb/init)
  (tb/clear)

  (while true
    (tb/clear)
    (draw-src src yoffset)
    (def ev (tb/poll-event))
    (case (ev :key)
      "arrow-up" (set yoffset (+ yoffset 1))
      "arrow-down" (set yoffset (- yoffset 1))
      (break)))

  (tb/shutdown))
