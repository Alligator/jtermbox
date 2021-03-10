(declare-project
  :name "jtermbox"
  :description "termbox bindings for janet")

(declare-source
  :source @["jtermbox.janet"])

(declare-native
  :name "_jtermbox"
  :source @["termbox.c" "utf8.c" "main.c"]
  # ternbox causes no unused result warnings with -Wall, hide them
  :cflags [;default-cflags "-std=gnu99" "-D_XOPEN_SOURCE" "-Wno-unused-result"])

(phony "get-termbox" []
       (os/shell "curl -LO https://raw.githubusercontent.com/termbox/termbox/master/termbox.c")
       (os/shell "curl -LO https://raw.githubusercontent.com/termbox/termbox/master/termbox.h")
       (os/shell "curl -LO https://raw.githubusercontent.com/termbox/termbox/master/utf8.c"))

(phony "generate-docs" []
       # auto-generate docs from docstrings in the module
       (def tb (require "jtermbox"))
       (def sorted-keys (sort (keys tb)))
       (loop [k :in sorted-keys
              :let [v (tb k)]
              :when (not (nil? (get v :doc)))]
         (def [func doc] (string/split "\n\n" (v :doc) 0 2))
         (printf "\n%s\n  %s" func (string/replace-all "\n" "\n  " doc))))

(phony "find-missing" []
       # find functions in termbox.h that aren't in the module
       (def header-funcs
         (filter (partial string/has-prefix? "SO_IMPORT") (string/split "\n" (slurp "termbox.h"))))
       (def termbox-funcs
         (map (fn [s] (->> s (string/replace-all "-" "_") (string "tb_"))) (keys (require "jtermbox"))))
       (loop [header-func :in header-funcs]
         (if (nil? (find (fn [tf] (not (nil? (string/find tf header-func)))) termbox-funcs))
           (print header-func))))
