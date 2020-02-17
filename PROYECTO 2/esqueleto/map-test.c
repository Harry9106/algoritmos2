#include <stdio.h>
#include <stdlib.h>
#include "map.h"

#define LOG(...) fprintf(stdout, __VA_ARGS__)

/** Quick & Dirty testing **/

/* Global variables considered dangerous */
map_t map;

static void _fail_test() {
    LOG("Destroy map.\n");
    map = map_destroy(map);
    LOG("Exiting.\n\n\n");
    exit(EXIT_FAILURE);
}

static void _end_test() {
    map = map_destroy(map);
    LOG("Test OK.\n\n\n");
}

static void _assert(bool exp) {
    if (exp) {
	LOG("OK.\n");
    } else {
	LOG("FAIL.\n");
	_fail_test();
    }
}

static void _test_get_in(const char *word, const char *expected) {
    LOG("Searching %s, expected %s.\n", word, expected);
    string_t str_word = string_create(word);
    string_t str_expect = string_create(expected);
    string_t str_got = map_get(map, str_word);
    LOG("Checking if %s is in the map.\n", word);
    _assert(map_contains(map, str_word));
    LOG("Checking if value is not NULL.\n");
    _assert(str_got != NULL);
    LOG("Checking if value is %s.\n", expected);
    _assert(string_eq(str_got, str_expect));
    LOG("Destroying auxiliary strings.\n");
    str_word = string_destroy(str_word);
    str_expect = string_destroy(str_expect);
}

static void _test_get_not_in(const char *word) {
    LOG("Searching for %s, expected NULL.\n", word);
    string_t str_word = string_create(word);
    string_t str_def  = map_get(map, str_word);
    LOG("Checking that %s is not in the map.\n", word);
    _assert(!map_contains(map, str_word));
    LOG("Checking if value is NULL.\n");
    _assert(str_def == NULL);
    LOG("Destroying auxiliary strings.\n");
    str_word = string_destroy(str_word);
}

static void _test_remove(const char *word) {
    string_t str = string_create(word);
    LOG("Removing %s.\n", word);
    map = map_remove(map, str);
    _test_get_not_in(word);
    LOG("Destroying auxiliary strings.\n");
    str = string_destroy(str);
}

static void _test_put(const char *word, const char *def) {
    string_t str = string_create(word);
    string_t str_def = string_create(def);
    map = map_put(map, str, str_def);
    _test_get_in(word, def);
}

void test_put() {
    LOG("Action: [Put] some words and [get] hem\n\n");
    map = map_empty();
    _test_put("Hello", "It's me");
    _test_put("Hakuna", "Matata");
    _test_put("Vincent de Moor", "Shamu");
    _test_put("Aly & Fila", "Key of Life");
    _end_test();
}

void test_put_repeated() {
    LOG("Action: [Put] some repeated words and [get] them\n\n");
    map = map_empty();
    _test_put("Vincent de Moor", "Shamu");
    _test_put("Vincent de Moor", "Green Heaven");
    _test_put("Vincent de Moor", "Worlds of Doubts");
    _test_get_in("Vincent de Moor", "Worlds of Doubts");
    _test_remove("Vincent de Moor");
    _end_test();
}

static void _add_some() {
    map = map_empty();
    _test_put("river", "millonario");
    _test_put("boca", "xeneize");
    _test_put("instituto", "lagloria");
    _test_put("belgrano", "pirata");
    _test_put("talleres", "albiceleste");
}

void test_remove_all() {
    LOG("Action: [Put] some words, [remove] all\n\n");
    _add_some();
    _test_remove("river");
    _test_remove("boca");
    _test_remove("talleres");
    _test_remove("instituto");
    _test_remove("belgrano");
    _end_test();
}

void test_get() {
    LOG("Action: [Put] some other words and [get] them\n\n");
    _add_some();
    _test_get_in("river", "millonario");
    _test_get_in("boca", "xeneize");
    _test_get_in("instituto", "lagloria");
    _test_get_in("belgrano", "pirata");
    _test_get_in("talleres", "albiceleste");
    _end_test();
}


void test_remove_repeated() {
    LOG("Action: [Put] some words, [remove] the same word twice\n\n");
    _add_some();
    _test_remove("river");
    _test_remove("river");
    _test_remove("talleres");
    _test_remove("talleres");
    _end_test();
}

void test_remove_empty() {
    LOG("Action: [Remove] from an empty map\n\n");
    map = map_empty();
    _test_remove("Hello");
    _end_test();
}

void test_get_empty() {
    LOG("Action: [Get] from an empty map\n\n");
    map = map_empty();
    _test_get_not_in("Hello");
    _end_test();
}

void test_get_reference() {
    LOG("Action: [Get] returns a reference\n\n");
    map = map_empty();
    string_t str = string_create("Hello");
    map = map_put(map, string_clone(str), str);
    string_t def = map_get(map, str);
    LOG("Checking that get returns a reference.\n");
    _assert(def == str);
    _end_test();
}

void test_contains_empty() {
    LOG("Action: [Contains] is false in an empty map\n\n");
    map = map_empty();
    string_t str = string_create("Hello");
    bool result = map_contains(map, str);
    str = string_destroy(str);
    _assert(!result);
    _end_test();
}

void test_dump_empty() {
    LOG("Action: Call [dump] on empty map\n\n");
    map = map_empty();
    map_dump(map, stdout);
    _end_test();
}

void test_dump_some() {
    LOG("Action: Call [dump] on a non-empty map\n\n");
    _add_some();
    map_dump(map, stdout);
    _end_test();
}

void test_destroy_empty() {
    LOG("Action: Call [destroy] on empty map\n\n");
    map = map_empty();
    _end_test();
}

struct _test_t {
    void (*doit) (void); 
};

struct _test_t tests[] = {
    {test_get_reference},
    {test_put},
    {test_put_repeated},
    {test_get},
    {test_remove_all},
    {test_remove_repeated},
    {test_remove_empty},
    {test_get_empty},
    {test_contains_empty},
    {test_dump_empty},
    {test_dump_some},
    {test_destroy_empty},
    {NULL}
};

int main() {
    unsigned int i = 0;
    while (tests[i].doit != NULL) {
	LOG("TEST %d.\n", i);
	tests[i].doit();
	i++;
    }
    return (0);
}
