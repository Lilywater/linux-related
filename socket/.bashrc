# .bashrc

# User specific aliases and functions

# Source global definitions
if [ -f /etc/bashrc ]; then
	. /etc/bashrc
fi

export ROOT=/home/guolili/MME_SGSN_tester
export OSTYPE=linux-gnu
export TAUTESTER_DIR=/opt/software/tautester
export PATH=/opt/software/tautester/bin:$PATH
export LD_LIBRARY_PATH=:/opt/tools/openssl/lib:/opt/tools/gmp/lib:/opt/tools/mpfr/lib:/opt/tools/gcc-4.3.2/lib
export PATH=/opt/tools/gcc-4.3.2/bin:$PATH
export PATH=/opt/tools/openssl/bin:$PATH
export PATH=~/bin:$PATH
export TTCN3_ENV=Verification
export CVS_RSH=ssh
export CVSROOT=:ext:glili@cvse1.access.nokiasiemensnetworks.com:/isource/cvsroot/ttcn3
export IPR_INITPORT=45011
export SVN_EDITOR=vi
alias 'cd3=cd /home/guolili/ttcn/MME_SGSN_tester/ttcn3libs/ttcn/'
alias 'cdt=cd /home/guolili/ttcn/MME_SGSN_tester/ttcn'
alias 'grep=grep --color'
alias 'make=~/specm/make'
alias 'vncp=vncconfig -nowin &'
alias 'vncs=vncserver -geometry 1200x950'
alias 'mmm=~/.vim/mm'
alias 'vim=/usr/local/bin/vim'
alias 'ctbp=cp ../debug/linux-gcc/*.a ~/ttcn/MME_SGSN_tester/ttcn3libs/lib/linux-gcc/'
alias getregres='wget -r -l1 --no-parent -nH --cut-dir=4 -A*.TTCN3.*'
alias getregstk='wget http://10.102.125.102:8011/results/ns40triplexs/2014-06-18--1735/ttcn3_dir/stacklogs_'
