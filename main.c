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

static Janet termbox_poll_event(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);

    struct tb_event ev;
    tb_poll_event(&ev);

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

static Janet termbox_set_cursor(int32_t argc, Janet *argv) {
    janet_fixarity(argc, 2);
    uint32_t cx = janet_getinteger(argv, 0);
    uint32_t cy = janet_getinteger(argv, 1);
    tb_set_cursor(cx, cy);
    return janet_wrap_nil();
}

static Janet termbox_width(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    return janet_wrap_integer(tb_width());
}
static Janet termbox_height(int32_t argc, Janet *argv) {
    (void) argv;
    janet_fixarity(argc, 0);
    return janet_wrap_integer(tb_height());
}

create_no_arg_func(termbox_shutdown, tb_shutdown);
create_no_arg_func(termbox_clear, tb_clear);
create_no_arg_func(termbox_present, tb_present);

static const JanetReg cfuns[] = {
    {"init",        termbox_init, ""},
    {"shutdown",    termbox_shutdown, ""},
    {"clear",       termbox_clear, ""},
    {"present",     termbox_present, ""},
    {"change-cell", termbox_change_cell, ""},
    {"poll-event",  termbox_poll_event, ""},
    {"set-cursor",  termbox_set_cursor, ""},
    {"width",       termbox_width, ""},
    {"height",      termbox_height, ""},
    {NULL, NULL, NULL}
};

JANET_MODULE_ENTRY(JanetTable *env) {
    janet_cfuns(env, "termbox", cfuns);
}
