#include "check.h"
#include "../src/hash_table.h"

START_TEST(test_insert_and_lookup) {
    // Test inserting and looking up a person
    person stefano = {.name = "Stefano", .age = 22};
    ck_assert_msg(hash_table_insert(&stefano), "Insert failed");

    person* result = hash_table_lookup("Stefano");
    ck_assert_msg(result != NULL, "Lookup failed");
    ck_assert_str_eq(result->name, "Stefano");
    ck_assert_int_eq(result->age, 22);
}

START_TEST(test_delete) {
    // Test deleting a person
    person stefano = {.name = "Stefano", .age = 22};
    ck_assert_msg(hash_table_insert(&stefano), "Insert failed");

    person* result = hash_table_delete("Stefano");
    ck_assert_msg(result != NULL, "Delete failed");
    ck_assert_str_eq(result->name, "Stefano");
    ck_assert_int_eq(result->age, 22);

    result = hash_table_lookup("Stefano");
    ck_assert_msg(result == NULL, "Lookup after delete failed");
}

Suite* test_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("TestSuite");

    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_insert_and_lookup);
    tcase_add_test(tc_core, test_delete);

    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = test_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}