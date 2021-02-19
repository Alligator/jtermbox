(declare-project
  :name "termbox"
  :description "termbox bindings for janet")

(declare-source
  :source @["termbox.janet"])

(declare-native
  :name "_termbox"
  :source @["termbox.c" "utf8.c" "main.c"]
  # ternbox causes no unused result warnings with -Wall, hide them
  :cflags [;default-cflags "-std=gnu99" "-D_XOPEN_SOURCE" "-Wno-unused-result"])

(phony "get-termbox" []
       (os/shell "curl -LO https://raw.githubusercontent.com/termbox/termbox/master/termbox.c")
       (os/shell "curl -LO https://raw.githubusercontent.com/termbox/termbox/master/termbox.h")
       (os/shell "curl -LO https://raw.githubusercontent.com/termbox/termbox/master/utf8.c"))
