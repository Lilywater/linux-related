#!/bin/sh 
grep -nH -r  -e  "^[[:space:]]*function[[:space:]]*[^[:space:]]\+[[:space:]]*("   --include=*.ttcn ~/ttcn/MME_SGSN_tester/  >~/ttcn/MME_SGSN_tester/tags_ttcn


grep -r -nH -e  "^[[:space:]]*template[[:space:]]\+[^[:space:]]\+[[:space:]]\+[^[:space:]]\+[[:space:]]*("  --include=*.ttcn  ~/ttcn/MME_SGSN_tester/  >~/ttcn/MME_SGSN_tester/tags_ttcn_temp
grep -r -nH -e "^[[:space:]]*type[[:space:]]\+[^[:space:]]\+[[:space:]]\+[^[:space:]]\+" --include=*.ttcn  ~/ttcn/MME_SGSN_tester/ >~/ttcn/MME_SGSN_tester/tags_ttcn_type
  
