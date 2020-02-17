#include <stdio.h>
#include <stdlib.h>
#include "dict.h"
#include "dict_helpers.h"

#define LOG(...) fprintf(stdout, __VA_ARGS__)
#define TEST_FILE "input/do-not-touch.dic"

/** Quick & Dirty testing **/

/* Global variables considered dangerous */
dict_t dict;

static void _fail_test() {
    LOG("Destroy dict.\n");
    dict = dict_destroy(dict);
    LOG("Exiting.\n\n\n");
    exit(EXIT_FAILURE);
}

static void _end_test() {
    dict = dict_destroy(dict);
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

static void _open_file(const char *filename) {
    string_t str = string_create(filename);
    LOG("Loading file %s.\n", filename);
    dict = dict_from_file(str);
    if (dict == NULL) {
	LOG("Could not open file.\n");
	exit(EXIT_FAILURE);
    }
    str = string_destroy(str);
}

static void _test_search_in(const char *word, const char *expected) {
    LOG("Searching %s, expected %s.\n", word, expected);
    string_t str_word = string_create(word);
    string_t str_expect = string_create(expected);
    string_t str_got = dict_search(dict, str_word);
    LOG("Checking if %s exists.\n", word);
    _assert(dict_exists(dict, str_word));
    LOG("Checking if definition is not NULL.\n");
    _assert(str_got != NULL);
    LOG("Checking if definition is %s.\n", expected);
    _assert(string_eq(str_got, str_expect));
    LOG("Destroying auxiliary strings.\n");
    str_word = string_destroy(str_word);
    str_expect = string_destroy(str_expect);
}

static void _test_search_not_in(const char *word) {
    LOG("Searching for %s, expected NULL.\n", word);
    string_t str_word = string_create(word);
    string_t str_def  = dict_search(dict, str_word);
    LOG("Checking that %s not exists.\n", word);
    _assert(!dict_exists(dict, str_word));
    LOG("Checking if definition is NULL.\n");
    _assert(str_def == NULL);
    LOG("Destroying auxiliary strings.\n");
    str_word = string_destroy(str_word);
}

static void _test_remove_in(const char *word) {
    LOG("Saving length.\n");
    unsigned int length_1 = dict_length(dict);
    string_t str = string_create(word);
    LOG("Removing %s.\n", word);
    dict = dict_remove(dict, str);
    unsigned int length_2 = dict_length(dict);
    LOG("Checking if length decreased.\n");
    _assert(length_2 + 1 == length_1);
    _test_search_not_in(word);
    LOG("Destroying auxiliary strings.\n");
    str = string_destroy(str);
}

static void _test_remove_not_in(const char *word) {
    LOG("Checking length.\n");
    unsigned int length_1 = dict_length(dict);
    string_t str = string_create(word);
    LOG("Removing %s (not in dict).\n", word);
    dict = dict_remove(dict, str);
    unsigned int length_2 = dict_length(dict);
    LOG("Checking if length is unchanged.\n");
    _assert(length_1 == length_2);
    LOG("Destroying auxiliary strings.\n");
    str = string_destroy(str);
}

static void _test_add_not_in(const char *word, const char *def) {
    LOG("Saving length.\n");
    unsigned int length_1 = dict_length(dict);
    string_t str = string_create(word);
    string_t str_def = string_create(def);
    dict = dict_add(dict, str, str_def);
    unsigned int length_2 = dict_length(dict);
    LOG("Checking that length increased\n");
    _assert(length_1 + 1 == length_2);
    _test_search_in(word, def);
}

static void _test_add_in(const char *word, const char *def) {
    LOG("Saving length.\n");
    unsigned int length_1 = dict_length(dict);
    string_t str = string_create(word);
    string_t str_def = string_create(def);
    dict = dict_add(dict, str, str_def);
    unsigned int length_2 = dict_length(dict);
    LOG("Checking that length is unchanged\n");
    _assert(length_1 == length_2);
    _test_search_in(word, def);
}

void test_empty() {
    LOG("Action: Check length of an empty dictionary\n\n");
    LOG("Creating an empty dictionary.\n");
    dict = dict_empty();
    LOG("Checking if length is 0.\n");
    _assert(dict_length(dict) == 0);
    _end_test();
}

void test_add() {
    LOG("Action: Add some words, search them\n\n");
    dict = dict_empty();
    _test_add_not_in("Hello", "It's me");
    _test_add_not_in("Hakuna", "Matata");
    _test_add_not_in("Vincent de Moor", "Shamu");
    _test_add_not_in("Aly & Fila", "Key of Life");
    _end_test();
}

void test_add_repeated() {
    LOG("Action: Add some repeated words, search them\n\n");
    dict = dict_empty();
    _test_add_not_in("Vincent de Moor", "Shamu");
    _test_add_in("Vincent de Moor", "Green Heaven");
    _test_add_in("Vincent de Moor", "Worlds of Doubts");
    _test_remove_in("Vincent de Moor");
    _end_test();
}

void test_search() {
    LOG("Action: Add some other words, search them\n\n");
    _open_file(TEST_FILE);
    _test_search_in("river", "millonario");
    _test_search_in("boca", "xeneize");
    _test_search_in("instituto", "lagloria");
    _test_search_in("belgrano", "pirata");
    _test_search_in("talleres", "albiceleste");
    _end_test();
}

void test_remove() {
    LOG("Action: Add some words, remove them all\n\n");
    _open_file(TEST_FILE);
    _test_remove_in("river");
    _test_remove_in("boca");
    _test_remove_in("talleres");
    _test_remove_in("instituto");
    _test_remove_in("belgrano");
    _end_test();
}

void test_remove_repeated() {
    LOG("Action: Remove the same word twice\n\n");
    _open_file(TEST_FILE);
    _test_remove_in("river");
    _test_remove_not_in("river");
    _test_remove_in("talleres");
    _test_remove_not_in("talleres");
    _end_test();
}

void test_remove_empty() {
    LOG("Action: Remove from an empty dictionary\n\n");
    dict = dict_empty();
    _test_remove_not_in("Hello");
    _end_test();
}

void test_remove_all() {
    LOG("Action: Add some words and call [remove_all]\n\n");
    _open_file(TEST_FILE);
    LOG("Removing all the words.\n");
    dict = dict_remove_all(dict);
    LOG("Checking that length is 0.\n");
    _assert(dict_length(dict) == 0);
    _end_test();
}

void test_search_reference() {
    LOG("Action: Check if [search] returns a reference\n\n");
    dict = dict_empty();
    string_t str = string_create("Hello");
    dict = dict_add(dict, string_clone(str), str);
    string_t def = dict_search(dict, str);
    LOG("Checking that search returns a reference.\n");
    _assert(def == str);
    _end_test();
}

struct _test_t {
    void (*doit) (void); 
};

struct _test_t tests[] = {
    {test_empty},
    {test_search_reference},
    {test_add},
    {test_add_repeated},
    {test_search},
    {test_remove},
    {test_remove_repeated},
    {test_remove_empty},
    {test_remove_all},
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
