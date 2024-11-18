TESTS_ENVIRONMENT = CK_VERBOSITY=$(CK_VERBOSITY)
TESTS = test_clear_noop test_grow_trunc test_init_free test_pop test_push_[]
check_PROGRAMS = test_clear_noop test_grow_trunc test_init_free test_pop test_push_[]

AM_CFLAGS = -I$(top_builddir)/src
LDADD = $(top_builddir)/src/libbuf.la
