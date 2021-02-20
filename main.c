#include "termbox.h"
#include <janet.h>

#define create_no_arg_func(name, fn) \
    static Janet name(int32_t argc, Janet *argv) { \
        (void) argv;                               \
        janet_fixarity(argc, 0);                   \
        fn();                                      \
        return janet_wrap_nil();                   \
    }                                              \

static Janet get_key_str(uint16_t key) {
    switch (key) {
        case TB_KEY_F1:
            return janet_cstringv("f1");
        case TB_KEY_F2:
            return janet_cstringv("f2");
        case TB_KEY_F3:
            return janet_cstringv("f3");
        case TB_KEY_F4:
            return janet_cstringv("f4");
        case TB_KEY_F5:
            return janet_cstringv("f5");
        case TB_KEY_F6:
            return janet_cstringv("f6");
        case TB_KEY_F7:
            return janet_cstringv("f7");
        case TB_KEY_F8:
            return janet_cstringv("f8");
        case TB_KEY_F9:
            return janet_cstringv("f9");
        case TB_KEY_F10:
            return janet_cstringv("f10");
        case TB_KEY_F11:
            return janet_cstringv("f11");
        case TB_KEY_F12:
            return janet_cstringv("f12");
        case TB_KEY_INSERT:
            return janet_cstringv("insert");
        case TB_KEY_DELETE:
            return janet_cstringv("delete");
        case TB_KEY_HOME:
            return janet_cstringv("home");
        case TB_KEY_END:
            return janet_cstringv("end");
        case TB_KEY_PGUP:
            return janet_cstringv("pgup");
        case TB_KEY_PGDN:
            return janet_cstringv("pgdn");
        case TB_KEY_ARROW_UP:
            return janet_cstringv("arrow-up");
        case TB_KEY_ARROW_DOWN:
            return janet_cstringv("arrow-down");
        case TB_KEY_ARROW_LEFT:
            return janet_cstringv("arrow-left");
        case TB_KEY_ARROW_RIGHT:
            return janet_cstringv("arrow-right");
        case TB_KEY_MOUSE_LEFT:
            return janet_cstringv("mouse-left");
        case TB_KEY_MOUSE_RIGHT:
            return janet_cstringv("mouse-right");
        case TB_KEY_MOUSE_MIDDLE:
            return janet_cstringv("mouse-middle");
        case TB_KEY_MOUSE_RELEASE:
            return janet_cstringv("mouse-release");
        case TB_KEY_MOUSE_WHEEL_UP:
            return janet_cstringv("mouse-wheel-up");
        case TB_KEY_MOUSE_WHEEL_DOWN:
            return janet_cstringv("mouse-wheel-down");
        case TB_KEY_CTRL_TILDE:
            return janet_cstringv("ctrl-tilde");
        case TB_KEY_CTRL_A:
            return janet_cstringv("ctrl-a");
        case TB_KEY_CTRL_B:
            return janet_cstringv("ctrl-b");
        case TB_KEY_CTRL_C:
            return janet_cstringv("ctrl-c");
        case TB_KEY_CTRL_D:
            return janet_cstringv("ctrl-d");
        case TB_KEY_CTRL_E:
            return janet_cstringv("ctrl-e");
        case TB_KEY_CTRL_F:
            return janet_cstringv("ctrl-f");
        case TB_KEY_CTRL_G:
            return janet_cstringv("ctrl-g");
        case TB_KEY_BACKSPACE:
            return janet_cstringv("ctrl-backspace");
        case TB_KEY_TAB:
            return janet_cstringv("tab");
        case TB_KEY_CTRL_J:
            return janet_cstringv("ctrl-j");
        case TB_KEY_CTRL_K:
            return janet_cstringv("ctrl-k");
        case TB_KEY_CTRL_L:
            return janet_cstringv("ctrl-l");
        case TB_KEY_ENTER:
            return janet_cstringv("enter");
        case TB_KEY_CTRL_N:
            return janet_cstringv("ctrl-n");
        case TB_KEY_CTRL_O:
            return janet_cstringv("ctrl-o");
        case TB_KEY_CTRL_P:
            return janet_cstringv("ctrl-p");
        case TB_KEY_CTRL_Q:
            return janet_cstringv("ctrl-q");
        case TB_KEY_CTRL_R:
            return janet_cstringv("ctrl-r");
        case TB_KEY_CTRL_S:
            return janet_cstringv("ctrl-s");
        case TB_KEY_CTRL_T:
            return janet_cstringv("ctrl-t");
        case TB_KEY_CTRL_U:
            return janet_cstringv("ctrl-u");
        case TB_KEY_CTRL_V:
            return janet_cstringv("ctrl-v");
        case TB_KEY_CTRL_W:
            return janet_cstringv("ctrl-w");
        case TB_KEY_CTRL_X:
            return janet_cstringv("ctrl-x");
        case TB_KEY_CTRL_Y:
            return janet_cstringv("ctrl-y");
        case TB_KEY_CTRL_Z:
            return janet_cstringv("ctrl-z");
        case TB_KEY_ESC:
            return janet_cstringv("esc");
        case TB_KEY_CTRL_BACKSLASH:
            return janet_cstringv("ctrl-backslash");
        case TB_KEY_CTRL_RSQ_BRACKET:
            return janet_cstringv("ctrl-rsq-bracket");
        case TB_KEY_CTRL_6:
            return janet_cstringv("ctrl-6");
        case TB_KEY_CTRL_UNDERSCORE:
            return janet_cstringv("ctrl-underscore");
        case TB_KEY_SPACE:
            return janet_cstringv("space");
        case TB_KEY_BACKSPACE2:
            return janet_cstringv("backspace");
        default:
            return janet_wrap_nil();
    }
}

//
// termbox API functions
//
static Janet termbox_init(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    int ret = tb_init();
    if (ret) {
        tb_shutdown();
        janet_panicf("tb_init failed with error code %d\n", ret);
    }
    return janet_wrap_nil();
}

// void tb_change_cell(int x, int y, uint32_t ch, uint16_t fg, uint16_t bg);
static Janet termbox_change_cell(int32_t argc, Janet *argv) {
    janet_arity(argc, 3, 5);

    int32_t x = janet_getinteger(argv, 0);
    int32_t y = janet_getinteger(argv, 1);

    const uint8_t *chu = janet_getstring(argv, 2);
    uint32_t ch;
    tb_utf8_char_to_unicode(&ch, (char *)chu);

    uint16_t fg = janet_optinteger(argv, argc, 3, TB_DEFAULT);
    uint16_t bg = janet_optinteger(argv, argc, 4, TB_DEFAULT);

    tb_change_cell(x, y, ch, fg, bg);

    return janet_wrap_nil();
}

static Janet create_tb_event_struct(struct tb_event ev) {
    JanetKV *jt = janet_struct_begin(3);
    Janet type;
    switch (ev.type) {
        case TB_EVENT_KEY:
            type = janet_cstringv("key");

            if (ev.ch) {
                char str[2] = { (char)ev.ch, 0 };
                janet_struct_put(jt, janet_ckeywordv("ch"), janet_cstringv(str));
            } else {
                janet_struct_put(jt, janet_ckeywordv("ch"), janet_wrap_nil());
                janet_struct_put(jt, janet_ckeywordv("key"), get_key_str(ev.key));
            }

            break;
        case TB_EVENT_RESIZE:
            type = janet_cstringv("resize");
            janet_struct_put(jt, janet_ckeywordv("w"), janet_wrap_integer(ev.w));
            janet_struct_put(jt, janet_ckeywordv("h"), janet_wrap_integer(ev.h));
            break;
        case TB_EVENT_MOUSE:
            type = janet_cstringv("mouse");
            janet_struct_put(jt, janet_ckeywordv("x"), janet_wrap_integer(ev.x));
            janet_struct_put(jt, janet_ckeywordv("y"), janet_wrap_integer(ev.y));
            break;
    }
    janet_struct_put(jt, janet_ckeywordv("type"), type);

    return janet_wrap_struct(janet_struct_end(jt));
}

// int tb_poll_event(struct tb_event *event);
static Janet termbox_poll_event(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);

    struct tb_event ev;
    tb_poll_event(&ev);
    return create_tb_event_struct(ev);
}

// int tb_peek_event(struct tb_event *event, int timeout);
static Janet termbox_peek_event(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    int32_t timeout = janet_getinteger(argv, 0);

    struct tb_event ev;
    int result = tb_peek_event(&ev, timeout);
    if (result == -1) {
        janet_panicf("tb_peek_event returned -1");
    } else if (result == 0) {
        return janet_wrap_nil();
    }

    return create_tb_event_struct(ev);
}

// void tb_set_cursor(int cx, int cy);
static Janet termbox_set_cursor(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    uint32_t cx = janet_getinteger(argv, 0);
    uint32_t cy = janet_getinteger(argv, 1);
    tb_set_cursor(cx, cy);
    return janet_wrap_nil();
}

// int tb_width(void);
static Janet termbox_width(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    return janet_wrap_integer(tb_width());
}

// int tb_height(void);
static Janet termbox_height(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    return janet_wrap_integer(tb_height());
}

// void tb_set_clear_attributes(uint16_t fg, uint16_t bg);
static Janet termbox_set_clear_attributes(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    uint16_t fg = janet_getinteger(argv, 0);
    uint16_t bg = janet_getinteger(argv, 1);
    tb_set_clear_attributes(fg, bg);
    return janet_wrap_nil();
}

static int kw_to_tb_output_mode(JanetKeyword mode_kw) {
    if (janet_cstrcmp(mode_kw, "normal") == 0) {
        return TB_OUTPUT_NORMAL;
    } else if (janet_cstrcmp(mode_kw, "256") == 0) {
        return TB_OUTPUT_256;
    } else if (janet_cstrcmp(mode_kw, "216") == 0) {
        return TB_OUTPUT_216;
    } else if (janet_cstrcmp(mode_kw, "grayscale") == 0) {
        return TB_OUTPUT_GRAYSCALE;
    } else if (janet_cstrcmp(mode_kw, "current") == 0) {
        return TB_OUTPUT_CURRENT;
    } else {
        janet_panicf("unrecognized output mode %s, expected one of :normal :256 :216 :grayscale :current\n", mode_kw);
    }
}

static Janet kw_from_tb_output_mode(int mode) {
    switch (mode) {
        case TB_OUTPUT_NORMAL:
            return janet_ckeywordv("normal");
        case TB_OUTPUT_256:
            return janet_ckeywordv("256");
        case TB_OUTPUT_216:
            return janet_ckeywordv("216");
        case TB_OUTPUT_GRAYSCALE:
            return janet_ckeywordv("grayscale");
        default:
            return janet_wrap_integer(mode);
    }
}

// int tb_select_output_mode(int mode);
static Janet termbox_select_output_mode(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 1);
    JanetKeyword mode_kw = janet_getkeyword(argv, 0);

    int mode = kw_to_tb_output_mode(mode_kw);
    int result = tb_select_output_mode(mode);

    if (mode == TB_OUTPUT_CURRENT) {
        return kw_from_tb_output_mode(result);
    }

    return janet_wrap_nil();
}

static int kw_to_tb_input_mode(JanetKeyword mode_kw) {
    if (janet_cstrcmp(mode_kw, "current") == 0) {
        return TB_INPUT_CURRENT;
    } else if (janet_cstrcmp(mode_kw, "esc") == 0) {
        return TB_INPUT_ESC;
    } else if (janet_cstrcmp(mode_kw, "alt") == 0) {
        return TB_INPUT_ALT;
    } else if (janet_cstrcmp(mode_kw, "mouse") == 0) {
        return TB_INPUT_MOUSE;
    } else {
        janet_panicf("unrecognized input mode %s, expected one of :current :esc :alt :mouse\n", mode_kw);
    }
}

static Janet kw_from_tb_input_mode(int mode) {
    switch (mode) {
        case TB_INPUT_CURRENT:
            return janet_ckeywordv("current");
        case TB_INPUT_ESC:
            return janet_ckeywordv("esc");
        case TB_INPUT_ALT:
            return janet_ckeywordv("alt");
        case TB_INPUT_MOUSE:
            return janet_ckeywordv("mouse");
        default:
            return janet_wrap_integer(mode);
    }
}

// int tb_select_input_mode(int mode);
static Janet termbox_select_input_mode(int32_t argc, Janet *argv) {
    janet_arity(argc, 1, -1);

    int mode = 0;
    for (int i = 0; i < argc; i++) {
        JanetKeyword mode_kw = janet_getkeyword(argv, i);
        mode |= kw_to_tb_input_mode(mode_kw);
    }

    int result = tb_select_input_mode(mode);

    if (mode == TB_INPUT_CURRENT) {
        return kw_from_tb_input_mode(result);
    }

    return janet_wrap_nil();
}

create_no_arg_func(termbox_shutdown, tb_shutdown);
create_no_arg_func(termbox_clear, tb_clear);
create_no_arg_func(termbox_present, tb_present);

static const JanetReg cfuns[] = {
    {"init",        termbox_init,
        "(init)\n\n"
        "initialize the termbox library.\n"
        "must be called before any other functions."
    },
    {"shutdown",    termbox_shutdown,
        "(shutdown)\n\n"
        "restore the terminal to it's initial state."
    },
    {"clear",       termbox_clear,
        "(clear)\n\n"
        "clear the internal terminal buffer."
    },
    {"set-clear-attributes", termbox_set_clear_attributes,
        "(set-clear-attributes fg bg)\n\n"
        "set the attributes used when clearing the screen with clear."
    },
    {"present",     termbox_present,
        "(present)\n\n"
        "sync the internal buffer with the terminal."
    },
    {"change-cell", termbox_change_cell,
        "(change-cell x y ch &opt fg bg)\n\n"
        "change a cell in the internal bufffer at the specified position.\n"
        "fg and bg default to (tb/color :default)."
    },
    {"poll-event",  termbox_poll_event,
        "(poll-event)\n\n"
        "wait for an event and return it.\n\n"
        "there are three types of event.\n"
        "key events, which contain either a character or a key name:\n\n"
        "@{:type \"key\" :ch \"a\" :key \"arrow-down\"}\n\n"
        "resize events, which contain a width and height:\n\n"
        "@{:type \"resize\" :w 640 :h 480}\n\n"
        "and mouse events, which contain x and y co-ordinates:\n\n"
        "@{:type \"mouse\" :x 20 :y 60}"
    },
    {"peek-event",  termbox_peek_event,
        "(peek-event timeout)\n\n"
        "wait for an event up to timeout milliseconds.\n"
        "returns the event, or nil if no event happened before the timeout.\n\n"
        "see poll-event for info on the returned value."
    },
    {"set-cursor",  termbox_set_cursor,
        "(set-cursor cx cy)\n\n"
        "set the position of the cursor. pass -1 for both cx and cy to hide the cursor."
    },
    {"width",       termbox_width,
        "(width)\n\n"
        "return the width of the terminal"
    },
    {"height",      termbox_height,
        "(height)\n\n"
        "return the height of the terminal"
    },
    {"select-output-mode",      termbox_select_output_mode,
        "(select-output-mode kw)\n\n"
        "set the output mode.\n"
        "valid modes are :normal :256 :216 :grayscale and :current.\n"
        "when called with :current, will return the current mode as a keyword."
    },
    {"select-input-mode",      termbox_select_input_mode,
        "(select-input-mode & kws)\n\n"
        "set the input mode.\n"
        "valid modes are :current :esc :alt :mouse.\n"
        "multiple modes are ORed together.\n"
        "when called with :current, will return the current mode as a keyword."
    },
    {NULL, NULL, NULL}
};

JANET_MODULE_ENTRY(JanetTable *env) {
    janet_cfuns(env, "termbox", cfuns);
}
