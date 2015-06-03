#!/bin/bash
grep -w Error /home/liguo/ttcn/MME_SGSN_tester/project/erlog >/tmp/erl
vim --cmd "set errorformat+=%f(%l)\ :\ column\ %c\ :\ %m" --cmd "cfile /tmp/erl"  --cmd "copen"

