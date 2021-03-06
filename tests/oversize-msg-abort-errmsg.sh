#!/bin/bash
# check if oversize message error is generated by receiver
. ${srcdir:=$(pwd)}/test-framework.sh
export errorlog="error.$LIBRELP_DYN.log"

startup_receiver -e $TESTDIR/$errorlog

echo 'Send Message...'
./send -t 127.0.0.1 -p $TESTPORT -m "testmessage1" -d 150000
./send -t 127.0.0.1 -p $TESTPORT -m "testmessage2"

stop_receiver
check_output "error.*frame too long"  $TESTDIR/$errorlog
check_output "testmessage2"
terminate
