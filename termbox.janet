(import ./build/_termbox :prefix "" :export true)

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

(defn color [& kws]
  (apply bor
         (map (fn [kw]
                (if (nil? (color-map kw))
                  (errorf "unknown color/attribute %v" kw))
                (color-map kw))
              kws)))
