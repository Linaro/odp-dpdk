include $(top_srcdir)/example/Makefile.inc

bin_PROGRAMS = odp_switch

odp_switch_SOURCES = odp_switch.c

if test_example
if ODP_PKTIO_PCAP
TESTS = switch_run.sh
endif
endif
EXTRA_DIST = switch_run.sh udp64.pcap empty.pcap

# If building out-of-tree, make check will not copy the scripts and data to the
# $(builddir) assuming that all commands are run locally. However this prevents
# running tests on a remote target using LOG_COMPILER.
# So copy all script and data files explicitly here.
all-local:
	if [ "x$(srcdir)" != "x$(builddir)" ]; then \
		for f in $(EXTRA_DIST); do \
			if [ -e $(srcdir)/$$f ]; then \
				mkdir -p $(builddir)/$$(dirname $$f); \
				cp -f $(srcdir)/$$f $(builddir)/$$f; \
			fi \
		done \
	fi
	ln -f -s $(top_srcdir)/platform/$(with_platform)/test/example/switch/pktio_env \
		pktio_env
clean-local:
	if [ "x$(srcdir)" != "x$(builddir)" ]; then \
		for f in $(EXTRA_DIST); do \
			rm -f $(builddir)/$$f; \
		done \
	fi
