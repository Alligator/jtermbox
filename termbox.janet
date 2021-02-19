(import _termbox :prefix "" :export true)

(def- color-map
  @{:default    0
    :black      1
    :red        2
    :green      3
    :yellow     4
    :blue       5
    :magenta    6
    :cyan       7
    :white      8
    :bold       0x0100
    :underline  0x0200
    :reverse    0x0400})

(defn color
  ``create a termbox color. accepts a color followed by any number of modifiers.

  valid keywords are :default :black :red :green :yellow :blue :magenta :cyan
  :white :bold :underline :reverse

  in 256 color, 216 color and grayscale modes, use numbers rather than keywords
  to select colors.
  ``
  [& kws]
  (apply bor
         (map (fn [kw]
                (cond
                  (int? kw) kw
                  (nil? (color-map kw)) (errorf "unknown color/attribute %v" kw)
                  (color-map kw)))
              kws)))
