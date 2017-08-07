set nocompatible            " 关闭 vi 兼容模式
"set number                  " 显示行号
noremap <C-C> "*y             
"noremap <C-C> "+y 
"noremap <C-Insert> "+y  
  
 " CTRL-V and SHIFT-Insert are Paste  
"noremap <C-V>        "+gP  
map <S-Insert>        "*gP 
let &termencoding=&encoding
set fileencodings=utf-8,gbk
"nmap  <silent> <F4> :vimgrep  ".expand("<cword>")<CR> i
filetype plugin indent on
set mouse=""
"set mouse=a
"noremap <F4> <ESC> :execute ":lvimgrep  " .expand("<cword>"). "  **/*.cpp **/*.h **/*.hpp **/*.c"<CR><ESC>:lw<CR>


let g:CurrentPath = expand("%:p:h")
let g:roottesterpath = substitute(g:CurrentPath, 'MME_SGSN_tester.*', "MME_SGSN_tester", "g") 
let g:SearchPath= g:roottesterpath . "/**"
"let  &path= g:SearchPath
let &path = &path .  g:SearchPath 
let g:InitialPath = g:CurrentPath
noremap <F11> <ESC>:echomsg "thisis:" . g:SearchPath <CR>
"noremap <F11> :run macros/gdb_mappings.vim <CR><ESC>:bel 20vsplit gdb-variables<CR>
"<ESC>:bel 20vsplit gdb-variables<CR>
noremap <F4> <ESC>:let @*=expand("%")<CR>
noremap <C-N> :bn<CR>
noremap <C-B> :lne<CR>
noremap <F2> <ESC>:set number<CR>
"noremap <F4> <ESC>:lcd %:p:h<CR><ESC> :execute ":lvimgrep  /\\<" .expand("<cword>"). "\\>/j  *.{c,h,ttcn}"<CR><ESC>:lcd  ~/ttcn/MME_SGSN_tester<CR><ESC>:lw<CR>
noremap <Leader>f   <ESC> :execute ":!grep -w  " .expand("<cword>").  " "  .g:roottesterpath.  "/tags_ttcn >/tmp/fl"<CR><ESC>:lfile /tmp/fl<CR>
noremap <Leader>d   <ESC> :execute ":!grep -w  " .expand("<cword>").  " "  .g:roottesterpath.  "/tags_ttcn_type >/tmp/fl"<CR><ESC>:lfile /tmp/fl<CR>
noremap <Leader>t   <ESC> :execute ":!grep -w  " .expand("<cword>").  " "  .g:roottesterpath.  "/tags_ttcn_temp >/tmp/fl"<CR><ESC>:lfile /tmp/fl<CR>
"noremap <F5> <ESC> :execute ":lvimgrep  /\\<" .expand("<cword>"). "\\>/j  ~/ttcn/MME_SGSN_tester/ttcn/mme/**/*.ttcn"<CR><ESC>:lw<CR>
"set shellquote=\"
"noremap <F5> <ESC> :execute "!~/.vim/tips  " .expand("<cword>"). "   "<CR><ESC>:lfile /tmp/result<CR><ESC>:lw<CR>
noremap <F7> <ESC>:run macros/gdb_mappings.vim<CR>
noremap <F12> <ESC> :OpEr<CR>
noremap B :make<CR><ESC>:copen<CR>
noremap C :lclose<CR>
set dictionary+=/usr/share/dict/words
set thesaurus+=~/.vim/thesaurus/mthesaur.txt
syntax on
au BufRead,BufNewFile *.ttcn            set filetype=ttcn

set updatetime=4000
"Mappings to jump to the definition of type,function and template
"nnoremap <Leader>f  :execute ":!grep -w  " .expand("<cword>"). "  ~/ttcn/MME_SGSN_tester/tags_ttcn >/tmp/fl"<CR><ESC>:lfile /tmp/fl<CR>
"nnoremap <Leader>d  :execute ":!grep -w  " .expand("<cword>"). "  ~/ttcn/MME_SGSN_tester/tags_ttcn_type >/tmp/fl"<CR><ESC>:lfile /tmp/fl<CR>
"nnoremap <Leader>t  :execute ":!grep -w  " .expand("<cword>"). "  ~/ttcn/MME_SGSN_tester/tags_ttcn_temp >/tmp/fl"<CR><ESC>:lfile /tmp/fl<CR>

" Mappings to access buffers (don't use "\p" because a
" delay before pressing "p" would accidentally paste).
" \l       : list buffers
" \b \f \g : go back/forward/last-used
" \1 \2 \3 : go to buffer 1/2/3 etc
nnoremap <Leader>l :ls<CR>
nnoremap <Leader>b :bp<CR>
"nnoremap <Leader>f :bn<CR>
nnoremap <Leader>p :tabn<CR>
nnoremap <Leader>g :e#<CR>
nnoremap <Leader>1 :1b<CR>
nnoremap <Leader>2 :2b<CR>
nnoremap <Leader>3 :3b<CR>
nnoremap <Leader>4 :4b<CR>
nnoremap <Leader>5 :5b<CR>
nnoremap <Leader>6 :6b<CR>
nnoremap <Leader>7 :7b<CR>
nnoremap <Leader>8 :8b<CR>
nnoremap <Leader>9 :9b<CR>
nnoremap <Leader>0 :10b<CR>
" It's useful to show the buffer number in the status line.
set laststatus=2 statusline=%02n:%<%F\ %h%m%r%=%-14.(%l,%c%V%)\ %P
au BufRead,BufNewFile *.ywtxt set ft=ywtxt 
"to avoid the ATTEntion to tip you swap file
"set shm=A
set noswapfile
set nobackup
"set backupdir=$VIMDATA/backup 
"set directory=$VIMDATA/temp
set autowrite
"one line break into several lines without add \n
"set nowrap
autocmd InsertEnter * set number
autocmd InsertLeave * set nonumber
"autocmd VisualEnter * set number
"autocmd VisualEnter * set nonumber
"set autochdir 
autocmd BufEnter * cd %:p:h
set errorformat+=%f(%l)\ :\ column\ %c\ :\ %m
set ignorecase
""vimgdb setting
let g:vimgdb_debug_file = ""
set tags=tags;/
nmap ^L :!lynx -accept_all_cookies http://us2.php.net/^R^W\#function.^R^W<CR>
"run macros/gdb_mappings.vim 
set paste
